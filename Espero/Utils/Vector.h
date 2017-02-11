/*
 * Espero Entity Framework for Cocos2d-x 2.x
 *
 * Author: Anh N. Dang
 * Date  : 2014-01-22
 *
**/

#ifndef __ESPERO_VECTOR_H__
#define __ESPERO_VECTOR_H__

#include <cocos2d.h>

#include "../Common.h"

BEGIN_NS_ESPERO

	template<typename T>
	class Vector : public cocos2d::Ref
	{
	public:
		typedef T **   ContainerType;
		typedef size_t SizeType;

	protected:
		ContainerType container;
		SizeType      capacity;
		SizeType      size;

	public:
		static Vector * create(void)
		{
			auto vector = new Vector();
			if (vector)
				return static_cast<Vector *>(vector->autorelease());

			return vector;
		}

		Vector(void)
			: container(nullptr), capacity(0), size(0)
		{
			this->reserve(16);
		}

		virtual ~Vector(void)
		{
			this->clean();
		}

	public:
		void addObject(T *obj)
		{
			this->reserve(this->size + 1);
			this->container[this->size++] = obj;
			obj->retain();
		}

		T * getObject(SizeType index)
		{
			if (index < this->size)
				return this->container[index];
			else
				return nullptr;
		}

		T * getObjectUnsafe(SizeType index)
		{
			return this->container[index];
		}

		T * getLastObject(void)
		{
			if (this->size)
				return this->container[this->size - 1];
			else
				return nullptr;
		}

		void removeObject(T *obj)
		{
			SizeType i = 0, c = this->size;
			ContainerType container = this->container;
			for (; i < c; ++i)
			{
				if (container[i] == obj)
				{
					obj->release();
					for (SizeType j = i + 1; j < c; ++j)
						container[j - 1] = container[j];

					--this->size;
					break;
				}
			}
		}

		void removeAt(SizeType index)
		{
			if (index < this->size)
			{
				SizeType c = this->size;
				ContainerType container = this->container;
				
				T * obj = container[index];
				if (obj)
					obj->release();

				for (SizeType j = index + 1; j < c; ++j)
					container[j - 1] = container[j];
			}
		}

		void removeLastObject(void)
		{
			if (this->size)
			{
				auto obj = this->container[this->size - 1];
				if (obj)
					obj->release();
				this->container[--this->size] = nullptr;
			}
		}

		SizeType getCapacity(void) const
		{
			return this->capacity;
		}

		SizeType getSize(void) const
		{
			return this->size;
		}

		ContainerType & getContainer(void)
		{
			return this->container;
		}

		const ContainerType & getContainer(void) const
		{
			return this->container;
		}

	public:
		void clearObjects(void)
		{
			if (this->container)
			{
				for (SizeType i = 0, c = this->size; i < c; ++i)
				{
					auto obj = this->container[i];
					obj->release();
				}

				this->size = 0;
			}
		}

		void clean(void)
		{
			if (this->container)
			{
				for (SizeType i = 0, c = this->size; i < c; ++i)
				{
					auto obj = this->container[i];
					obj->release();
				}
				delete []this->container;
				this->container = nullptr;
				this->capacity = 0;
				this->size = 0;
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

				ContainerType newContainer = new T *[newCapacity];
				CCAssert(newContainer, "Vector allocation failed.");
				
				const SizeType sizeInBytes = this->capacity * sizeof(T *);

				// copy from old container
				if (this->container)
					memcpy(newContainer, this->container, sizeInBytes);

				// clear the rest
				memset(newContainer + this->capacity, 0, (newCapacity - this->capacity) * sizeof(T *));

				if (this->container)
					delete []this->container;

				this->container = newContainer;
				this->capacity  = newCapacity;
			}
		}
	};

END_NS_ESPERO

#endif//__ESPERO_VECTOR_H__
