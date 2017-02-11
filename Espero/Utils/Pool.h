/*
 * Espero Entity Framework for Cocos2d-x 3.0
 *
 * Author: Anh N. Dang
 * Date  : 2014-04-18
 *
**/

#ifndef __ESPERO_POOL_H__
#define __ESPERO_POOL_H__

#include <cocos2d.h>

#include "../Common.h"

BEGIN_NS_ESPERO

	template<typename T>
	class Pool : public cocos2d::Ref
	{
	public:
		typedef T **   PoolType;
		typedef size_t SizeType;

		typedef void (*PoolDelegate)(T *obj, Pool<T> *pool);

	protected:
		PoolType pool;
		SizeType capacity;
		SizeType ptr;
		
		PoolDelegate onIntoPool;
		PoolDelegate onOutOfPool;
		PoolDelegate onCleaned;
		int tag;

	public:
		static Pool * create(void)
		{
			return Pool::createWithDelegates(nullptr, nullptr, nullptr);
		}

		static Pool * createWithDelegates(PoolDelegate onIntoPool, PoolDelegate onOutOfPool, PoolDelegate onCleaned, int tag = 0)
		{
			auto pool = new Pool(onIntoPool, onOutOfPool, onCleaned, tag);
			if (pool)
				return static_cast<Pool *>(pool->autorelease());

			return pool;
		}

		Pool(PoolDelegate onIntoPool, PoolDelegate onOutOfPool, PoolDelegate onCleaned, int tag)
			: pool(nullptr), capacity(0), ptr(0),
			onIntoPool(onIntoPool), onOutOfPool(onOutOfPool), onCleaned(onCleaned), tag(tag)
		{
			this->reserve(16);
		}

		virtual ~Pool(void)
		{
			this->clean();
		}

	public:
		inline void setDelegates(PoolDelegate onIntoPool, PoolDelegate onOutOfPool, PoolDelegate onCleaned)
		{
			this->onIntoPool = onIntoPool;
			this->onOutOfPool = onOutOfPool;
			this->onCleaned = onCleaned;
		}

		inline int getTag(void) const
		{
			return this->tag;
		}

		inline void setTag(int tag)
		{
			this->tag = tag;
		}

	public:
		T * give(void)
		{
			if (this->ptr)
			{
				auto obj = this->pool[--this->ptr];

				if (this->onOutOfPool)
					this->onOutOfPool(obj, this);

				return obj;
			}

			return nullptr;
		}

		void take(T * obj)
		{
			this->reserve(this->ptr + 1);
			this->pool[this->ptr++] = obj;
			obj->retain();

			if (this->onIntoPool)
				this->onIntoPool(obj, this);
		}

		SizeType getCapacity(void) const
		{
			return this->capacity;
		}

		SizeType getSize(void) const
		{
			return this->ptr;
		}

		PoolType & getInnerPool(void)
		{
			return this->pool;
		}

		const PoolType & getInnerPool(void) const
		{
			return this->pool;
		}

	public:
		void clean(void)
		{
			if (this->pool)
			{
				for (SizeType i = 0, c = this->ptr; i < c; ++i)
				{
					auto obj = this->pool[i];

					if (this->onCleaned)
						this->onCleaned(obj, this);

					obj->release();
				}
				delete []this->pool;
				this->pool = nullptr;
				this->capacity = 0;
				this->ptr = 0;
			}
		}

	public:
		void reserve(SizeType capacity)
		{
			if (capacity > this->capacity)
			{
				// find the smallest power of two that is bigger than or equal to `capacity`
				SizeType newCapacity;

				if ((capacity & 1) == 0) //capacity is a power of two
				{
					newCapacity = capacity;
				}
				else
				{
					SizeType c = 0;
					SizeType n = capacity;
					while (n)
					{
						n >>= (SizeType)1;
						++c;
					}

					if (!c)
						c = 1;

					newCapacity = (SizeType)1 << c;
				}

				PoolType newPool = new T *[newCapacity];
				CCAssert(newPool, "Pool allocation failed.");
				
				const SizeType sizeInBytes = this->capacity * sizeof(T *);

				// copy from old container
				if (this->pool)
					memcpy(newPool, this->pool, sizeInBytes);

				// clear the rest
				memset(newPool + this->capacity, 0, (newCapacity - this->capacity) * sizeof(T *));

				if (this->pool)
					delete []this->pool;

				this->pool     = newPool;
				this->capacity = newCapacity;
			}
		}
	};

END_NS_ESPERO

#endif//__ESPERO_POOL_H__
