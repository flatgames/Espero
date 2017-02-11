/*
 * Espero Entity Framework for Cocos2d-x 3.0
 *
 * Author: Anh N. Dang
 * Date  : 2014-04-18
 *
**/

#include "Entity.h"
#include "../World.h"
#include "../Manager/EntityManager.h"
#include "../Manager/ComponentManager.h"
#include "../Component/Component.h"
#include "../Component/ComponentType.h"

using namespace cocos2d;

BEGIN_NS_ESPERO

	//public static
	Entity * Entity::create(World *world, EntityId id)
	{
		auto entity = new Entity(world, id);
		if (entity)
		{
			entity->autorelease();
			return entity;
		}

		return nullptr;
	}

	//protected
	Entity::Entity(World *world, EntityId id)
		: id(0), world(nullptr), entityManager(nullptr), componentManager(nullptr),
		deleted(false), userData(nullptr)
	{
		this->world = world;
		this->id = id;
		this->entityManager = world->getEntityManager();
		this->componentManager = world->getComponentManager();

		this->reset();
	}

	//public virtual
	Entity::~Entity(void)
	{
	}

	//public
	Entity * Entity::addComponent(Component *component)
	{
		return this->addComponent(component, ComponentType::getTypeFor(component->getClass()));
	}

	//public
	Entity * Entity::addComponent(Component *component, ComponentType *type)
	{
		this->componentManager->addComponent(this, type, component);
		return this;
	}

	//public
	Entity * Entity::removeComponent(Component *component)
	{
		return this->removeComponent(component->getClass());
	}

	//public
	Entity * Entity::removeComponent(ComponentType *type)
	{
		this->componentManager->removeComponent(this, type);
		return this;
	}

	//public
	Entity * Entity::removeComponent(ClassName classType)
	{
		return this->removeComponent(ComponentType::getTypeFor(classType));
	}
	
	//public
	Component * Entity::getComponent(ComponentType *type)
	{
		return this->componentManager->getComponent(this, type);
	}

	//public
	Component * Entity::getComponent(ClassName classType)
	{
		return this->componentManager->getComponent(this, ComponentType::getTypeFor(classType));
	}

	//public
	ComponentMap * Entity::getComponents(ComponentMap &fillSet)
	{
		return this->componentManager->getComponentsFor(this, fillSet);
	}
	
	//public
	bool Entity::isActive(void) const
	{
		return this->entityManager->isActive(this->id);
	}

	//public
	bool Entity::isEnabled(void) const
	{
		return this->entityManager->isEnabled(this->id);
	}

	//public
	bool Entity::isDeleted(void) const
	{
		return this->deleted;
	}

	//public
	void Entity::setDeleted(bool value)
	{
		this->deleted = value;
	}
	
	//public
	void Entity::addToWorld(void)
	{
		this->world->addEntity(this);
	}

	//public
	void Entity::changedInWorld(void)
	{
		this->world->changedEntity(this);
	}

	//public
	void Entity::deleteFromWorld(void)
	{
		if (!this->deleted)
			this->world->deleteEntity(this);
	}
		
	//public
	void Entity::enable(void)
	{
		this->world->enable(this);
	}
		
	//public
	void Entity::disable(void)
	{
		this->world->disable(this);
	}

	//protected
	void Entity::reset(void)
	{
		this->componentBits.clearAll();
		this->systemBits.clearAll();
	}

END_NS_ESPERO
