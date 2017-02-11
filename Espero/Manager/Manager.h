/*
 * Espero Entity Framework for Cocos2d-x 3.0
 *
 * Author: Anh N. Dang
 * Date  : 2014-04-18
 *
**/

#ifndef __ESPERO_MANAGER_H__
#define __ESPERO_MANAGER_H__

#include <cocos2d.h>

#include "../Config.h"
#include "../IClassName.h"
#include "../Entity/EntityObserver.h"

BEGIN_NS_ESPERO

	class World;

	__IClassNameInternalDefine(Manager);
	
	class Manager : public EntityObserver, public IClassName, public cocos2d::Ref
	{
	protected:
		World *world;

	public:
		IClassNameImplement(Manager);
		
	public:
		virtual void initialize(void) =0;
		
	public:
		inline World * getWorld(void)
		{
			return this->world;
		}
		
		inline const World * getWorld(void) const
		{
			return this->world;
		}

		inline void setWorld(World *world)
		{
			this->world = world;
		}
		
	public:
		virtual void added(Entity *entity)
		{
		}
		
		virtual void changed(Entity *entity)
		{
		}
		
		virtual void deleted(Entity *entity)
		{
		}
		
		virtual void disabled(Entity *entity)
		{
		}
		
		virtual void enabled(Entity *entity)
		{
		}
	};

END_NS_ESPERO

#endif//__ESPERO_MANAGER_H__
