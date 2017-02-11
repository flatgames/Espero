/*
 * Espero Entity Framework for Cocos2d-x 3.0
 *
 * Author: Anh N. Dang
 * Date  : 2014-04-18
 *
**/

#include "ComponentManager.h"
#include "../Entity/Entity.h"
#include "../Component/Component.h"
#include "../Component/ComponentType.h"

using namespace cocos2d;

BEGIN_NS_ESPERO

	//public static
	ComponentManager * ComponentManager::create(void)
	{
		auto manager = new ComponentManager();
		if (manager)
			return static_cast<ComponentManager *>(manager->autorelease());

		return nullptr;
	}

	//public
	ComponentManager::ComponentManager(void)
	{
		this->componentsByType.clearObjects();
		this->deletedEntities.clearObjects();

#if ESPERO_COMPONENT_POOLING
		this->componentPoolsByType.clearObjects();
#endif
	}

	//public virtual
	ComponentManager::~ComponentManager(void)
	{
#if ESPERO_COMPONENT_POOLING
		this->componentPoolsByType.clearObjects();
#endif
	}

	//protected
	void ComponentManager::initialize(void)
	{
	}

	//private
	void ComponentManager::removeComponentsOfEntity(Entity *entity)
	{
		BitSet &componentBits = entity->getComponentBits();

		for (BitSet::IndexType i = 0, c = componentBits.getBitCount(); i < c; ++i)
		{
			if (componentBits.checkUnsafe(i) && i < this->componentsByType.getSize())
			{
				auto bag = this->componentsByType.getObject(i);
				auto component = bag->getObject(entity->getId());

#if ESPERO_COMPONENT_POOLING
				this->giveComponentToPool(component);
#endif

				bag->removeObject(entity->getId());
				component->setEntity(nullptr);
			}
		}

		componentBits.clearAll();
	}
	
	//public
	void ComponentManager::addComponent(Entity *entity, ComponentType *type, Component *component)
	{
		ComponentBag *bag = nullptr;

		bag = this->componentsByType.getObject(type->getIndex());
		if (bag == nullptr)
		{
			bag = ComponentBag::create();
			this->componentsByType.addObject(type->getIndex(), bag);
		}

		bag->addObject(entity->getId(), component);

		entity->getComponentBits().set(type->getIndex());
		component->setEntity(entity);
	}

	//public
	void ComponentManager::removeComponent(Entity *entity, ComponentType *type)
	{
		if (entity->getComponentBits().check(type->getIndex()))
		{
			auto bag = this->componentsByType.getObject(type->getIndex());
			auto component = bag->getObject(entity->getId());

#if ESPERO_COMPONENT_POOLING
			this->giveComponentToPool(component);
#endif

			bag->removeObject(entity->getId());

			entity->getComponentBits().clear(type->getIndex());
			component->setEntity(nullptr);
		}
	}
		
	//public
	ComponentBag * ComponentManager::getComponentsByType(ComponentType *type)
	{
		ComponentBag *bag = nullptr;

		bag = this->componentsByType.getObject(type->getIndex());
		if (bag == nullptr)
		{
			bag = ComponentBag::create();
			this->componentsByType.addObject(type->getIndex(), bag);
		}

		return bag;
	}
		
	//public
	Component * ComponentManager::getComponent(Entity *entity, ComponentType *type)
	{
		ComponentBag *bag = nullptr;
		
		bag = this->componentsByType.getObject(type->getIndex());
		if (bag)
			return bag->getObject(entity->getId());

		return nullptr;
	}

#if ESPERO_COMPONENT_POOLING

	//public
	Pool<Component> * ComponentManager::getPoolForType(ComponentType *type)
	{
		Pool<Component> *pool = nullptr;

		pool = this->componentPoolsByType.getObject(type->getIndex());
		if (pool == nullptr)
		{
			pool = Pool<Component>::create();
			this->componentPoolsByType.addObject(type->getIndex(), pool);
		}

		return pool;
	}

	//public
	Component * ComponentManager::takeComponentFromPool(ComponentType *type)
	{
		Pool<Component> *pool = nullptr;

		pool = this->componentPoolsByType.getObject(type->getIndex());
		if (pool == nullptr)
		{
			pool = Pool<Component>::create();
			this->componentPoolsByType.addObject(type->getIndex(), pool);
		}

		auto component = pool->give();
		if (component)
			component->onOutOfPool(this);

		return component;
	}

	//public
	void ComponentManager::giveComponentToPool(Component *component)
	{
		auto pool = component->pool;
		component->onIntoPool(this);
		pool->take(component);
	}

#endif//ESPERO_COMPONENT_POOLING
		
	//public
	ComponentMap * ComponentManager::getComponentsFor(Entity *entity, ComponentMap &fillSet)
	{
		const BitSet &componentBits = entity->getComponentBits();
		
		for (BitSet::IndexType i = 0, c = componentBits.getBitCount(); i < c; ++i)
		{
			if (componentBits.checkUnsafe(i))
			{
				auto component = this->componentsByType.getObject(i)->getObject(entity->getId());
				fillSet.setObject(classof(component), component);
			}
		}

		return &fillSet;
	}
		
	//public
	void ComponentManager::deleted(Entity *entity)
	{
		this->deletedEntities.addObject(entity);
	}
		
	//public
	void ComponentManager::clean(void)
	{
		if (this->deletedEntities.getSize() > 0)
		{
			BeginSetForEach(e, this->deletedEntities, _)
				this->removeComponentsOfEntity(e);
			EndForEach

			this->deletedEntities.clearObjects();
		}
	}

END_NS_ESPERO
