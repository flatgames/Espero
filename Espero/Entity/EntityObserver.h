/*
 * Espero Entity Framework for Cocos2d-x 3.0
 *
 * Author: Anh N. Dang
 * Date  : 2014-04-18
 *
**/

#ifndef __ESPERO_ENTITYOBSERVER_H__
#define __ESPERO_ENTITYOBSERVER_H__

#include "../Config.h"

BEGIN_NS_ESPERO

	class Entity;
	
	class EntityObserver
	{
	public:
		virtual void added(Entity *entity) =0;
		virtual void changed(Entity *entity) =0;
		virtual void deleted(Entity *entity) =0;
		virtual void enabled(Entity *entity) =0;
		virtual void disabled(Entity *entity) =0;
	};

END_NS_ESPERO

#endif//__ESPERO_ENTITYOBSERVER_H__
