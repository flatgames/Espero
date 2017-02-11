/*
 * Espero Entity Framework for Cocos2d-x 3.0
 *
 * Author: Anh N. Dang
 * Date  : 2014-04-18
 *
**/

#ifndef __ESPERO_ENTITYMANAGER_H__
#define __ESPERO_ENTITYMANAGER_H__

#include <cocos2d.h>
#include <vector>

#include "../Config.h"
#include "Manager.h"

BEGIN_NS_ESPERO

	class IdentifierPool;

	__IClassNameInternalDefine(EntityManager);

	class EntityManager : public Manager
	{
	public:
#if ESPERO_ENTITY_POOLING
		typedef void (*PoolDelegate)(EntityManager *manager, Entity *entity);
#endif

	private:
		EntityBag entities;
		EntityBag disabledEntities;
		
		Int32 nActive;
		Int64 nAdded;
		Int64 nCreated;
		Int64 nDeleted;
		
		IdentifierPool *identifierPool;

#if ESPERO_ENTITY_POOLING
		std::vector<Entity *> entityPool;
		PoolDelegate onEntityIntoPool;
		PoolDelegate onEntityOutOfPool;
		PoolDelegate onEntityCleaned;
#endif
		
	public:
		IClassNameImplement(EntityManager);

	public:
		static EntityManager * create(void);

		EntityManager(void);
		virtual ~EntityManager(void);
	
	protected:
		void initialize(void);
	
	public:
		Entity * createEntityInstance(void);
		void removeAllEntities(void);
		
	public:
		void added(Entity *entity);
		void enabled(Entity *entity);
		void disabled(Entity *entity);
		void deleted(Entity *entity);
	
	public:
		bool isActive(EntityId id);
		bool isEnabled(EntityId id);
		
		Entity * getEntity(EntityId id);
		
	public:
		inline Int32 getActiveEntityCount(void) const
		{
			return this->nActive;
		}
		
		inline Int64 getTotalCreated(void) const
		{
			return this->nCreated;
		}
		
		inline Int64 getTotalAdded(void) const
		{
			return this->nAdded;
		}
		
		inline Int64 getTotalDeleted(void) const
		{
			return this->nDeleted;
		}

	public:

#if ESPERO_ENTITY_POOLING

		PoolDelegate getOnEntityIntoPool(void) const
		{
			return this->onEntityIntoPool;
		}

		void setOnEntityIntoPool(PoolDelegate onEntityIntoPool)
		{
			this->onEntityIntoPool = onEntityIntoPool;
		}
		
		PoolDelegate getOnEntityOutOfPool(void) const
		{
			return this->onEntityOutOfPool;
		}

		void setOnEntityOutOfPool(PoolDelegate onEntityOutOfPool)
		{
			this->onEntityOutOfPool = onEntityOutOfPool;
		}
		
		PoolDelegate getOnEntityCleaned(void) const
		{
			return this->onEntityCleaned;
		}

		void setOnEntityCleaned(PoolDelegate onEntityCleaned)
		{
			this->onEntityCleaned = onEntityCleaned;
		}

#endif//ESPERO_ENTITY_POOLING

	};

END_NS_ESPERO

#endif//__ESPERO_ENTITYMANAGER_H__
