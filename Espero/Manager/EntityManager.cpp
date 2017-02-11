/*
 * Espero Entity Framework for Cocos2d-x 3.0
 *
 * Author: Anh N. Dang
 * Date  : 2014-04-18
 *
**/

#include "EntityManager.h"

#include "../Entity/Entity.h"
#include "../Utils/IdentifierPool.h"

using namespace cocos2d;

BEGIN_NS_ESPERO

	//public static
	EntityManager * EntityManager::create(void)
	{
		auto manager = new EntityManager();
		if (manager)
			return static_cast<EntityManager *>(manager->autorelease());

		return nullptr;
	}

	//public
	EntityManager::EntityManager(void)
	{
		this->entities.clearObjects();
		this->disabledEntities.clearObjects();
		this->identifierPool = new IdentifierPool();

		this->nActive = 0;
		this->nAdded = 0;
		this->nCreated = 0;
		this->nDeleted = 0;

#if ESPERO_ENTITY_POOLING
		this->entityPool.reserve(16);
		this->onEntityIntoPool = nullptr;
		this->onEntityOutOfPool = nullptr;
		this->onEntityCleaned = nullptr;
#endif
	}

	//public virtual
	EntityManager::~EntityManager(void)
	{
		this->entities.clearObjects();
		this->disabledEntities.clearObjects();

		CC_SAFE_DELETE(this->identifierPool);

#if ESPERO_ENTITY_POOLING
		auto cleanEntity = this->onEntityCleaned;
		for (auto it = this->entityPool.begin(), itEnd = this->entityPool.end(); it != itEnd; ++it)
		{
			auto e = *it;
			if (cleanEntity)
				cleanEntity(this, e);

			e->release();
		}
		this->entityPool.clear();
#endif
	}

	//protected
	void EntityManager::initialize(void)
	{
	}

	//public
	Entity * EntityManager::createEntityInstance(void)
	{
		Entity *entity;

#if ESPERO_ENTITY_POOLING
		if (this->entityPool.size())
		{
			entity = this->entityPool.back();
			this->entityPool.pop_back();

			entity->world = this->world;
			entity->id = this->identifierPool->checkOut();
			entity->setDeleted(false);
			entity->reset();

			if (this->onEntityOutOfPool)
				this->onEntityOutOfPool(this, entity);
		}
		else
		{
			entity = Entity::create(this->world, this->identifierPool->checkOut());
		}
#else
		entity = Entity::create(this->world, this->identifierPool->checkOut());
#endif

		++this->nCreated;

		return entity;
	}

	//public
	void EntityManager::removeAllEntities(void)
	{
		for (EntityBag::SizeType i = 0, c = this->entities.getSize(); i < c; ++i)
		{
			auto e = this->entities.getObjectUnsafe(i);
			if (e)
				e->deleteFromWorld();
		}
	}
	
	//public
	void EntityManager::added(Entity *entity)
	{
		++this->nActive;
		++this->nAdded;

		this->entities.addObject(entity->getId(), entity);
	}
	
	//public
	void EntityManager::enabled(Entity *entity)
	{
		this->disabledEntities.removeObject(entity->getId());
	}
	
	//public
	void EntityManager::disabled(Entity *entity)
	{
		this->disabledEntities.addObject(entity->getId(), entity);

	}
	
	//public
	void EntityManager::deleted(Entity *entity)
	{
		this->entities.removeObject(entity->getId());
		this->disabledEntities.removeObject(entity->getId());

		this->identifierPool->checkIn(entity->getId());

		--this->nActive;
		++this->nDeleted;

#if ESPERO_ENTITY_POOLING
		this->entityPool.push_back(entity);
		entity->retain();

		if (this->onEntityIntoPool)
			this->onEntityIntoPool(this, entity);
#endif
	}

	//public
	bool EntityManager::isActive(EntityId id)
	{
		return this->entities.getObject(id) != nullptr;
	}

	//public
	bool EntityManager::isEnabled(EntityId id)
	{
		return this->disabledEntities.getObject(id) == nullptr;
	}

	//public
	Entity * EntityManager::getEntity(EntityId id)
	{
		return this->entities.getObject(id);
	}

END_NS_ESPERO
