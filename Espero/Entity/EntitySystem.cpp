/*
 * Espero Entity Framework for Cocos2d-x 3.0
 *
 * Author: Anh N. Dang
 * Date  : 2014-04-18
 *
**/

#include "EntitySystem.h"
#include "Entity.h"
#include "Entity.h"
#include "../Component/Aspect.h"
#include "../World.h"

#include <algorithm>

using namespace cocos2d;

BEGIN_NS_ESPERO

	//public
	EntitySystem::EntitySystem(Aspect *aspect)
		: passive(false), dummy(false)
	{
		this->activeEntities = EntitySet::create();
		this->activeEntities->retain();

		this->activeEntities->clearObjects();

		this->aspect = aspect;
		this->aspect->retain();

		this->allSet = aspect->getAllSet();
		this->exclusionSet = aspect->getExclusionSet();
		this->oneSet = aspect->getOneSet();

		this->dummy = this->allSet.none() && this->oneSet.none();
	}
	
	//public virtual
	EntitySystem::~EntitySystem(void)
	{
		CC_SAFE_RELEASE_NULL(this->activeEntities);
		CC_SAFE_RELEASE_NULL(this->aspect);
	}

	//protected virtual
	void EntitySystem::begin(void)
	{
	}

	//protected virtual
	void EntitySystem::end(void)
	{
	}

	//public
	void EntitySystem::process(void)
	{
		if (this->checkProcessing())
		{
			this->begin();
			this->processEntities(*this->activeEntities);
			this->end();
		}
	}

	//public
	void EntitySystem::initialize(void)
	{
	}

	//protected virtual
	void EntitySystem::inserted(Entity *entity)
	{
	}

	//protected virtual
	void EntitySystem::removed(Entity *entity)
	{
	}

	//protected
	void EntitySystem::check(Entity *entity)
	{
		if (this->dummy)
			return;

		bool contains = entity->getSystemBits().check(this->systemIndex);
		bool interested = true;

		const BitSet &componentBits = entity->getComponentBits();

		if (this->allSet.any())
		{
			for (BitSet::IndexType i = 0, c = this->allSet.getBitCount(); i < c; ++i)
			{
				if (this->allSet.checkUnsafe(i)
					&& componentBits.check(i) == false)
				{
					interested = false;
					break;
				}
			}
		}

		if (interested && this->exclusionSet.any())
		{
			BitSet set = componentBits;
			set.intersectWith(this->exclusionSet);

			interested = set.none();
		}

		if (this->oneSet.any())
		{
			BitSet set = componentBits;
			set.intersectWith(this->oneSet);

			interested = set.any();
		}

		if (interested && !contains)
			this->insertToSystem(entity);
		else if (!interested && contains)
			this->removeFromSystem(entity);
	}

	//private
	void EntitySystem::removeFromSystem(Entity *entity)
	{
		this->activeEntities->removeObject(entity);
		entity->getSystemBits().clear(this->systemIndex);
		
		this->removed(entity);
	}
	
	//private
	void EntitySystem::insertToSystem(Entity *entity)
	{
		this->activeEntities->addObject(entity);
		entity->getSystemBits().set(this->systemIndex);
		
		this->inserted(entity);
	}

	//protected
	void EntitySystem::added(Entity *entity)
	{
		this->check(entity);
	}

	//protected
	void EntitySystem::changed(Entity *entity)
	{
		this->check(entity);
	}

	//protected
	void EntitySystem::deleted(Entity *entity)
	{
		if (entity->getSystemBits().check(this->systemIndex))
			this->removeFromSystem(entity);
	}

	//protected
	void EntitySystem::enabled(Entity *entity)
	{
		this->check(entity);
	}

	//protected
	void EntitySystem::disabled(Entity *entity)
	{
		if (entity->getSystemBits().check(this->systemIndex))
			this->removeFromSystem(entity);
	}

	//public
	void EntitySystem::setWorld(World *world)
	{
		this->world = world;
	}

	//public
	void EntitySystem::initIndex(void)
	{
		this->systemIndex = SystemIndexManager::getIndexFor(classof(this));
	}

END_NS_ESPERO

BEGIN_NS_ESPERO
	CommonIndex EntitySystem::SystemIndexManager::INDEX = 0;
	std::map<ClassName, CommonIndex> EntitySystem::SystemIndexManager::indices;

	CommonIndex EntitySystem::SystemIndexManager::getIndexFor(ClassName type)
	{
		auto it = indices.find(type);
		if (it != indices.end())
			return it->second;

		CommonIndex index = INDEX++;
		indices[type] = index;

		return index;
	}
END_NS_ESPERO
