/*
 * Espero Entity Framework for Cocos2d-x 3.0
 *
 * Author: Anh N. Dang
 * Date  : 2014-04-18
 *
**/

#include "IdentifierPool.h"

BEGIN_NS_ESPERO

	IdentifierPool::IdentifierPool(void)
		: firstAvailableId(0), nextAvailableId(0)
	{
		this->ids.clear();
	}

	IdentifierPool::IdentifierPool(EntityId firstAvailableId)
		: firstAvailableId(firstAvailableId), nextAvailableId(firstAvailableId)
	{
		this->ids.clear();
	}
		
	EntityId IdentifierPool::checkOut(void)
	{
		if (this->ids.size() > 0)
		{
			auto id = this->ids.back();
			this->ids.pop_back();
			return id;
		}
			
		return this->nextAvailableId++;
	}
		
	void IdentifierPool::checkIn(EntityId id)
	{
		this->ids.push_back(id);
	}

	void IdentifierPool::reset(void)
	{
		this->ids.clear();
		this->nextAvailableId = this->firstAvailableId;
	}

END_NS_ESPERO
