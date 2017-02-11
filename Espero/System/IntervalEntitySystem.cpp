/*
 * Espero Entity Framework for Cocos2d-x 3.0
 *
 * Author: Anh N. Dang
 * Date  : 2014-04-18
 *
**/

#include "IntervalEntitySystem.h"

#include "../World.h"
#include "../Entity/Entity.h"

BEGIN_NS_ESPERO

bool IntervalEntitySystem::checkProcessing(void)
{
	this->acct += this->world->getDelta();
	if (this->acct >= this->interval)
	{
		this->acct -= this->interval;
		return true;
	}

	return false;
}

END_NS_ESPERO
