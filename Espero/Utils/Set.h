/*
 * Espero Entity Framework for Cocos2d-x 3.0
 *
 * Author: Anh N. Dang
 * Date  : 2014-04-18
 *
**/

#ifndef __ESPERO_SET_H__
#define __ESPERO_SET_H__

#include <set>
#include <cocos2d.h>

#include "../Common.h"

BEGIN_NS_ESPERO

	template<typename T>
	class Set : public cocos2d::Ref
	{
	public:
		typedef std::set<T *> SetType;

		typedef typename SetType::iterator       iterator;
		typedef typename SetType::const_iterator const_iterator;

	protected:
		SetType set;

	public:
		static Set * create(void)
		{
			Set<T> *set = new Set<T>();
			if (set)
			{
				set->autorelease();
				return set;
			}

			return nullptr;
		}

		Set(void)
		{
		}

		virtual ~Set(void)
		{
			this->clearObjects();
		}

		void addObject(T *obj)
		{
			const_iterator it = this->set.find(obj);
			if (it == this->set.end())
			{
				this->set.insert(obj);
				CC_SAFE_RETAIN(obj);
			}
		}

		void removeObject(T *obj)
		{
			const_iterator it = this->set.find(obj);
			if (it != this->set.end())
			{
				CC_SAFE_RELEASE(*it);
				this->set.erase(it);
			}
		}

		void removeObject(iterator it)
		{
			if (it != this->set.end())
			{
				CC_SAFE_RELEASE(*it);
				this->set.erase(it);
			}
		}

		void clearObjects(void)
		{
			for (auto it = this->set.begin(), itEnd = this->set.end(); it != itEnd; ++it)
				CC_SAFE_RELEASE(*it);

			this->set.clear();
		}

		const_iterator begin(void) const
		{
			return this->set.begin();
		}

		const_iterator end(void) const
		{
			return this->set.end();
		}
		
		const_iterator find(T *obj) const
		{
			return this->set.find(obj);
		}

		iterator begin(void)
		{
			return this->set.begin();
		}

		iterator end(void)
		{
			return this->set.end();
		}
		
		iterator find(T *obj)
		{
			return this->set.find(obj);
		}

		bool has(T *obj)
		{
			return this->find(obj) != this->set.end();
		}

		size_t getSize(void)
		{
			return this->set.size();
		}
	};

}

#endif//__ESPERO_SET_H__
