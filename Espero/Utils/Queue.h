/*
* Espero Entity Framework for Cocos2d-x 3.0
*
* Author: Anh N. Dang
* Date  : 2014-04-18
*
**/

#ifndef __ESPERO_QUEUE_H__
#define __ESPERO_QUEUE_H__

#include <cocos2d.h>
#include <deque>

#include "../Common.h"

BEGIN_NS_ESPERO

	template<typename T>
	class Queue : public cocos2d::Ref
	{
	public:
		typedef std::deque<T *> QueueType;

		typedef typename QueueType::iterator       iterator;
		typedef typename QueueType::const_iterator const_iterator;

	protected:
		QueueType queue;

	public:
		static Queue * create(void)
		{
			Queue<T> *queue = new Queue<T>();
			if (queue)
			{
				queue->autorelease();
				return queue;
			}

			return nullptr;
		}

		Queue(void)
		{
		}

		virtual ~Queue(void)
		{
			this->clearObjects();
		}

	public:
		void pushFront(T *obj)
		{
			this->queue.push_front(obj);
			CC_SAFE_RETAIN(obj);
		}

		T * getBack(void)
		{
			if (this->queue.size())
			{
				auto obj = this->queue.back();
				return obj;
			}

			return nullptr;
		}

		void popBack(void)
		{
			if (this->queue.size())
			{
				auto obj = this->queue.back();
				this->queue.pop_back();
				obj->release();
			}
		}

		void clearObjects(void)
		{
			for (auto it = this->queue.begin(), itEnd = this->queue.end(); it != itEnd; ++it)
				CC_SAFE_RELEASE(*it);

			this->queue.clear();
		}

	public:
		const_iterator begin(void) const
		{
			return this->queue.begin();
		}

		const_iterator end(void) const
		{
			return this->queue.end();
		}

		const_iterator find(T *obj) const
		{
			return this->queue.find(obj);
		}

		iterator begin(void)
		{
			return this->queue.begin();
		}

		iterator end(void)
		{
			return this->queue.end();
		}

		iterator find(T *obj)
		{
			return this->queue.find(obj);
		}

		bool has(T *obj)
		{
			return this->find(obj) != this->queue.end();
		}

		size_t getSize(void)
		{
			return this->queue.size();
		}
	};

END_NS_ESPERO

#endif//__ESPERO_QUEUE_H__
