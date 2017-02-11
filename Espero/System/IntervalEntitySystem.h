/*
 * Espero Entity Framework for Cocos2d-x 3.0
 *
 * Author: Anh N. Dang
 * Date  : 2014-04-18
 *
**/

#ifndef __ESPERO_INTERVALENTITYSYSTEM_H__
#define __ESPERO_INTERVALENTITYSYSTEM_H__

#include "../Entity/EntitySystem.h"

BEGIN_NS_ESPERO

	__IClassNameInternalDefine(IntervalEntitySystem);

	class IntervalEntitySystem : public EntitySystem
	{
	protected:
		float interval;
		float acct;

	public:
		IClassNameImplement(IntervalEntitySystem);

	public:
		IntervalEntitySystem(Aspect *aspect, float interval)
			: EntitySystem(aspect), interval(interval), acct(0)
		{
		}

		virtual ~IntervalEntitySystem(void)
		{
		}

	protected:
		bool checkProcessing(void);
	};

END_NS_ESPERO

#endif//__ESPERO_INTERVALENTITYSYSTEM_H__

