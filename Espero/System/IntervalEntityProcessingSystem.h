/*
 * Espero Entity Framework for Cocos2d-x 3.0
 *
 * Author: Anh N. Dang
 * Date  : 2014-04-18
 *
**/

#ifndef __ESPERO_INTERVALENTITYPROCESSINGSYSTEM_H__
#define __ESPERO_INTERVALENTITYPROCESSINGSYSTEM_H__

#include "IntervalEntitySystem.h"

BEGIN_NS_ESPERO
	
	__IClassNameInternalDefine(IntervalEntityProcessingSystem);

	class IntervalEntityProcessingSystem : public IntervalEntitySystem
	{
	public:
		IClassNameImplement(IntervalEntityProcessingSystem);

	public:
		IntervalEntityProcessingSystem(Aspect *aspect, float interval)
			: IntervalEntitySystem(aspect, interval)
		{
		}

		virtual ~IntervalEntityProcessingSystem(void)
		{
		}

	protected:
		void processEntities(const EntitySet &entities);

	protected:
		virtual void process(Entity *entity) =0;
	};

END_NS_ESPERO

#endif//__ESPERO_INTERVALENTITYPROCESSINGSYSTEM_H__

