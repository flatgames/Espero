/*
 * Espero Entity Framework for Cocos2d-x 3.0
 *
 * Author: Anh N. Dang
 * Date  : 2014-04-18
 *
**/

#ifndef __ESPERO_ENTITYPROCESSINGSYSTEM_H__
#define __ESPERO_ENTITYPROCESSINGSYSTEM_H__

#include "../Entity/EntitySystem.h"

BEGIN_NS_ESPERO

	__IClassNameInternalDefine(EntityProcessingSystem);

	class EntityProcessingSystem : public EntitySystem
	{
	public:
		IClassNameImplement(EntityProcessingSystem);

	public:
		EntityProcessingSystem(Aspect *aspect)
			: EntitySystem(aspect)
		{
		}

		virtual ~EntityProcessingSystem(void)
		{
		}

	protected:
		void processEntities(const EntitySet &entities);

		virtual bool checkProcessing(void)
		{
			return true;
		}

	protected:
		virtual void process(Entity *entity) =0;
	};

END_NS_ESPERO

#endif//__ESPERO_ENTITYPROCESSINGSYSTEM_H__

