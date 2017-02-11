/*
 * Espero Entity Framework for Cocos2d-x 3.0
 *
 * Author: Anh N. Dang
 * Date  : 2014-04-18
 *
**/

#include "EntityProcessingSystem.h"

#include "../Entity/Entity.h"

BEGIN_NS_ESPERO

void EntityProcessingSystem::processEntities(const EntitySet &entities)
{
	BeginSetForEach(e, entities, _)
		this->process(e);
	EndForEach
}

END_NS_ESPERO
