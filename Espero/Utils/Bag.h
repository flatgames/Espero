/*
 * Espero Entity Framework for Cocos2d-x 3.0
 *
 * Author: Anh N. Dang
 * Date  : 2014-04-18
 *
**/

#ifndef __ESPERO_BAG_H__
#define __ESPERO_BAG_H__

#include <memory.h>
#include <cocos2d.h>

#include "../Common.h"

BEGIN_NS_ESPERO

	template<typename T>
	class Bag : public cocos2d::Ref
	{
	public:
		typedef size_t SizeType;

		typedef       T ** iterator;
		typedef const T ** const_iterator;

	protected:
		T **      container;
		SizeType  size;
		SizeType  count;

	public:
		static Bag * create(void)
		{
			Bag<T> *bag = new Bag<T>();
			if (bag)
				return static_cast<Bag<T>*>(bag->autorelease());

			return nullptr;
		}

		Bag(void)
			: container(nullptr), size(0), count(0)
		{
		}

		virtual ~Bag(void)
		{
			if (this->container)
			{
				this->clearObjects();

				delete []this->container;
				this->container = nullptr;
				this->size = 0;
			}
		}

	public:
		void addObject(SizeType index, T * obj)
		{
			this->ensureSizeForIndex(index);
			T * oldObj = this->container[index];

			if (oldObj)
				oldObj->release();
			else
				++this->count;

			this->container[index] = obj;
			if (obj)
				obj->retain();
		}

		void removeObject(SizeType index)
		{
			if (index < this->size)
			{
				T * obj = this->container[index];
				if (obj)
				{
					obj->release();
					--this->count;
				}

				this->container[index] = nullptr;
			}
		}

		T * getObject(SizeType index)
		{
			if (index < this->size)
				return this->container[index];

			return nullptr;
		}

		T * getObjectUnsafe(SizeType index)
		{
			return this->container[index];
		}

		SizeType findObject(T * obj)
		{
			for (SizeType i = 0, size = this->size; i < size; ++i)
				if (this->container[i] == obj)
					return i;

			return Bag::noIndex();
		}

		bool hasObject(T * obj)
		{
			return this->findObject() != Bag::noIndex();
		}

		inline static SizeType noIndex(void)
		{
			return (SizeType)(-1);
		}

		void clearObjects(void)
		{
			for (SizeType i = 0, size = this->size; i < size; ++i)
			{
				T * element = this->container[i];
				if (element)
					element->release();

				this->container[i] = nullptr;
			}
		}

		SizeType getSize(void) const
		{
			return this->size;
		}

		SizeType getCount(void) const
		{
			return this->count;
		}

	protected:
		void ensureSizeForIndex(SizeType index)
		{
			if (index >= this->size)
			{
				// find the smallest power of two that is bigger than `index`
				SizeType c = 0;
				SizeType n = index;
				while (n)
				{
					n >>= 1;
					++c;
				}

				if (!c)
					c = 1;

				//FIXME: check if newSize==noIndex(), which is too big
				SizeType     newSize      = 1 << c;
				T * *newContainer = new T *[newSize];
				
				if (newContainer)
				{
					const SizeType sizeInBytes = this->size * sizeof(T *);

					// copy from old container
					if (this->container)
						memcpy(newContainer, this->container, sizeInBytes);

					// clear the rest
					memset(newContainer + this->size, 0, (newSize - this->size) * sizeof(T *));

					if (this->container)
						delete []this->container;

					this->container = newContainer;
					this->size      = newSize;
				}
			}
		}
	};

END_NS_ESPERO

#endif//__ESPERO_BAG_H__
