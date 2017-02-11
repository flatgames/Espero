/*
 * Espero Entity Framework for Cocos2d-x 2.x
 *
 * Author: Anh N. Dang
 * Date  : 2014-01-14
 *
**/

#ifndef __ESPERO_MAP_H__
#define __ESPERO_MAP_H__

#include <map>
#include <cocos2d.h>

#include "../Common.h"

BEGIN_NS_ESPERO

	template<typename Tkey, typename Tvalue>
	class Map : public cocos2d::Ref
	{
	public:
		typedef std::less<ClassName>     ComparerType;

		typedef std::map<Tkey, Tvalue *, ComparerType> MapType;

		typedef typename MapType::iterator       iterator;
		typedef typename MapType::const_iterator const_iterator;

	protected:
		MapType map;

	public:
		static Map * create(void)
		{
			Map<Tkey, Tvalue> *map = new Map<Tkey, Tvalue>();
			if (map)
			{
				map->autorelease();
				return map;
			}

			return nullptr;
		}

		Map(void)
		{
		}

		virtual ~Map(void)
		{
			this->clearObjects();
		}

		void setObject(Tkey key, Tvalue *value)
		{
			const_iterator it = this->map.find(key);
			if (it != this->map.end())
				CC_SAFE_RELEASE(it->second);

			CC_SAFE_RETAIN(value);
			this->map[key] = value;
		}
	
		void removeObject(Tkey key)
		{
			iterator it = this->map.find(key);
			if (it != this->map.end())
			{
				CC_SAFE_RELEASE(it->second);
				this->map.erase(it);
			}
		}

		void removeObject(iterator it)
		{
			if (it != this->map.end())
			{
				CC_SAFE_RELEASE(it->second);
				this->map.erase(it);
			}
		}
	
		void clearObjects(void)
		{
			for (auto it = this->map.begin(), itEnd = this->map.end(); it != itEnd; ++it)
				CC_SAFE_RELEASE(it->second);

			this->map.clear();
		}

		Tvalue * objectForKey(Tkey key)
		{
			const_iterator it = this->map.find(key);
			if (it != this->map.end())
				return it->second;
			else
				return nullptr;
		}

		const_iterator begin(void) const
		{
			return this->map.begin();
		}

		const_iterator end(void) const
		{
			return this->map.end();
		}

		const_iterator find(Tkey key) const
		{
			return this->map.find(key);
		}

		iterator begin(void)
		{
			return this->map.begin();
		}

		iterator end(void)
		{
			return this->map.end();
		}

		iterator find(Tkey key)
		{
			return this->map.find(key);
		}

		bool has(Tkey key)
		{
			return this->find(key) != this->map.end();
		}

		size_t getSize(void)
		{
			return this->map.size();
		}
	};

END_NS_ESPERO

#endif//__ESPERO_MAP_H__
