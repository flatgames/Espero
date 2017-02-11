/*
 * Espero Entity Framework for Cocos2d-x 3.0
 *
 * Author: Anh N. Dang
 * Date  : 2014-04-18
 *
**/

#ifndef __ESPERO_IDENTIFIERPOOL_H__
#define __ESPERO_IDENTIFIERPOOL_H__

#include <vector>

#include "../Config.h"

BEGIN_NS_ESPERO

	class IdentifierPool
	{
	private:
		std::vector<EntityId> ids;
		EntityId firstAvailableId;
		EntityId nextAvailableId;
	
	public:
		IdentifierPool(void);
		IdentifierPool(EntityId firstAvailableId);
		
		EntityId checkOut(void);
		void checkIn(EntityId id);
		void reset(void);
	};

END_NS_ESPERO

#endif//__ESPERO_IDENTIFIERPOOL_H__
