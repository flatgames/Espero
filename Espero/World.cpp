/*
 * Espero Entity Framework for Cocos2d-x 3.0
 *
 * Author: Anh N. Dang
 * Date  : 2014-04-18
 *
**/

#include "World.h"
#include "Entity/Entity.h"
#include "Entity/EntitySystem.h"
#include "Component/Aspect.h"
#include "Component/Component.h"
#include "Component/ComponentType.h"
#include "Manager/EntityManager.h"
#include "Manager/ComponentManager.h"

#include <algorithm>

using namespace cocos2d;

BEGIN_NS_ESPERO

	//private static
	World * World::instance = nullptr;

	//public static
	World * World::getInstance(void)
	{
		if (!World::instance)
		{
			World::instance = World::create();
			World::instance->retain();
		}

		return World::instance;
	}

	//public static
	void World::cleanInstance(void)
	{
		CC_SAFE_RELEASE_NULL(World::instance);
	}

	//public static
	World * World::create(void)
	{
		auto world = new World();
		if (world)
			return static_cast<World *>(world->autorelease());

		return nullptr;
	}

	//public
	World::World(void)
		: dt(0), running(false), initialized(false)
	{
		this->managers = ManagerMap::create();
		this->managers->retain();

		this->managerSet = Vector<Manager>::create();
		this->managerSet->retain();

		this->systems = SystemMap::create();
		this->systems->retain();

		this->systemSet = Vector<EntitySystem>::create();
		this->systemSet->retain();

		this->addedEntities = EntityVector::create();
		this->addedEntities->retain();

		this->changedEntities = EntityVector::create();
		this->changedEntities->retain();

		this->deletedEntities = EntityVector::create();
		this->deletedEntities->retain();

		this->enabledEntities = EntityVector::create();
		this->enabledEntities->retain();

		this->disabledEntities = EntityVector::create();
		this->disabledEntities->retain();

		this->componentManager = ComponentManager::create();
		this->componentManager->retain();
		this->setManager(this->componentManager);

		this->entityManager = EntityManager::create();
		this->entityManager->retain();
		this->setManager(this->entityManager);
	}

	//public virtual
	World::~World(void)
	{
		CC_SAFE_RELEASE_NULL(this->managers);
		CC_SAFE_RELEASE_NULL(this->managerSet);

		CC_SAFE_RELEASE_NULL(this->systems);
		CC_SAFE_RELEASE_NULL(this->systemSet);

		CC_SAFE_RELEASE_NULL(this->addedEntities);
		CC_SAFE_RELEASE_NULL(this->changedEntities);
		CC_SAFE_RELEASE_NULL(this->deletedEntities);
		CC_SAFE_RELEASE_NULL(this->enabledEntities);
		CC_SAFE_RELEASE_NULL(this->disabledEntities);

		CC_SAFE_RELEASE_NULL(this->componentManager);
		CC_SAFE_RELEASE_NULL(this->entityManager);
	}

	//public
	void World::initialize(void)
	{
		if (this->initialized)
			return;

		{
			auto container = this->managerSet->getContainer();
			for (Vector<Manager>::SizeType i = 0, c = this->managerSet->getSize(); i < c; ++i)
				container[i]->initialize();
		}

		{
			auto container = this->systemSet->getContainer();
			for (Vector<EntitySystem>::SizeType i = 0, c = this->systemSet->getSize(); i < c; ++i)
				container[i]->initialize();
		}

		this->initialized = true;
	}
	
	//public
	Manager * World::setManager(Manager *manager)
	{
		this->managers->setObject(manager->getClass(), manager);
		this->managerSet->addObject(manager);
		manager->setWorld(this);

		return manager;
	}
	
	//public
	Manager * World::getManager(ClassName classType)
	{
		return static_cast<Manager *>(this->managers->objectForKey(classType));
	}
	
	//public
	void World::deleteManager(Manager *manager)
	{
		this->managers->removeObject(manager->getClass());
		this->managerSet->removeObject(manager);
	}
	
	//public
	void World::update(float dt)
	{
		this->dt = dt;
		this->process();
	}
	
	//public
	void World::start(void)
	{
		CCAssert(this->initialized, "World has not been initialized.");
		if (!this->running)
		{
			Director::getInstance()->getScheduler()->scheduleUpdate(this, 0, false);
			this->running = true;
		}
	}

	//public
	void World::stop(void)
	{
		CCAssert(this->initialized, "World has not been initialized.");
		if (this->running)
		{
			Director::getInstance()->getScheduler()->unscheduleUpdate(this);
			this->running = false;
		}
	}

	//public
	void World::addEntity(Entity *entity)
	{
		this->addedEntities->addObject(entity);
	}
	
	//public
	void World::changedEntity(Entity *entity)
	{
		this->changedEntities->addObject(entity);
	}
	
	//public
	void World::deleteEntity(Entity *entity)
	{
		entity->setDeleted(true);
		this->deletedEntities->addObject(entity);
	}
	
	//public
	void World::enable(Entity *entity)
	{
		this->enabledEntities->addObject(entity);
	}
	
	//public
	void World::disable(Entity *entity)
	{
		this->disabledEntities->addObject(entity);
	}
	
	//public
	Entity * World::createEntity(void)
	{
		return this->entityManager->createEntityInstance();
	}
	
	//public
	Entity * World::getEntity(EntityId id)
	{
		return this->entityManager->getEntity(id);
	}
	
	//public
	EntitySystem * World::addSystem(EntitySystem *system)
	{
		return this->addSystem(system, /*passive=*/ false);
	}
	
	//public
	EntitySystem * World::addSystem(EntitySystem *system, bool passive)
	{
		system->setWorld(this);
		system->setPassive(passive);
		system->initIndex();

		this->systems->setObject(classof(system), system);
		this->systemSet->addObject(system);

		return system;
	}
	
	//public
	void World::deleteSystem(EntitySystem *system)
	{
		this->systems->removeObject(classof(system));
		this->systemSet->removeObject(system);
	}
	
	//public
	EntitySystem * World::getSystem(ClassName classType)
	{
		return this->systems->objectForKey(classType);
	}
	
	//protected
	void World::notifySystems(Performer performer, Entity *entity)
	{
		auto container = this->systemSet->getContainer();
		for (Vector<EntitySystem>::SizeType i = 0, c = this->systemSet->getSize(); i < c; ++i)
			performer(container[i], entity);
	}
	
	//protected
	void World::notifyManagers(Performer performer, Entity *entity)
	{
		auto container = this->managerSet->getContainer();
		for (Vector<Manager>::SizeType i = 0, c = this->managerSet->getSize(); i < c; ++i)
			performer(container[i], entity);
	}
	
	//protected
	void World::check(EntityVector *entities, Performer performer)
	{
		if (entities->getSize() != 0)
		{
			auto container = entities->getContainer();
			for (EntityVector::SizeType i = 0, c = entities->getSize(); i < c; ++i)
			{
				auto e = container[i];
				this->notifySystems(performer, e);
				this->notifyManagers(performer, e);
			}

			entities->clearObjects();
		}
	}

	//protected
	void World::process(void)
	{
		this->check(this->addedEntities,
			[](EntityObserver *observer, Entity *entity)
			{
				observer->added(entity);
			});

		this->check(this->changedEntities,
			[](EntityObserver *observer, Entity *entity)
			{
				observer->changed(entity);
			});
		
		this->check(this->enabledEntities,
			[](EntityObserver *observer, Entity *entity)
			{
				observer->enabled(entity);
			});
		
		this->check(this->disabledEntities,
			[](EntityObserver *observer, Entity *entity)
			{
				observer->disabled(entity);
			});

		this->check(this->deletedEntities,
			[](EntityObserver *observer, Entity *entity)
			{
				observer->deleted(entity);
			});

		this->componentManager->clean();

		auto container = this->systemSet->getContainer();
		for (Vector<EntitySystem>::SizeType i = 0, c = this->systemSet->getSize(); i < c; ++i)
			if (!container[i]->isPassive())
				container[i]->process();
	}

END_NS_ESPERO
