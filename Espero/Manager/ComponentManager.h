/*
 * Espero Entity Framework for Cocos2d-x 3.0
 *
 * Author: Anh N. Dang
 * Date  : 2014-04-18
 *
**/

#ifndef __ESPERO_COMPONENTMANAGER_H__
#define __ESPERO_COMPONENTMANAGER_H__

#include <cocos2d.h>

#include "../Config.h"
#include "../Utils/IdentifierPool.h"
#include "../Component/ComponentType.h"

#include "Manager.h"

BEGIN_NS_ESPERO
	class Entity;
	class Component;
	class ComponentType;

	__IClassNameInternalDefine(ComponentManager);

	class ComponentManager : public Manager
	{
	private:
		typedef Bag<ComponentBag>    ComponentBagBag;
		typedef Bag<Pool<Component>> ComponentPoolBag;
	
	private:
		ComponentBagBag  componentsByType;
		EntitySet        deletedEntities;

#if ESPERO_COMPONENT_POOLING
		ComponentPoolBag componentPoolsByType;
#endif

	public:
		IClassNameImplement(ComponentManager);

	public:
		static ComponentManager * create(void);

		ComponentManager(void);
		virtual ~ComponentManager(void);
		
	protected:
		void initialize(void);
		
	private:
		void removeComponentsOfEntity(Entity *entity);
	
	public:
		void addComponent(Entity *entity, ComponentType *type, Component *component);
		void removeComponent(Entity *entity, ComponentType *type);
		
		ComponentBag * getComponentsByType(ComponentType *type);
		
		Component * getComponent(Entity *entity, ComponentType *type);

	public:

#if ESPERO_COMPONENT_POOLING
		
		Pool<Component> * getPoolForType(ComponentType *type);

		Component * takeComponentFromPool(ComponentType *type);

		void giveComponentToPool(Component *component);

#endif//ESPERO_COMPONENT_POOLING

		template<typename T>
		T * getPooledComponentOrCreateNew(void)
		{
#if ESPERO_COMPONENT_POOLING
			auto type = ComponentType::getTypeFor(sharedclassof(T));
			auto component = static_cast<T*>(this->takeComponentFromPool(type));
			if (!component)
			{
				component = new T();
				component->pool = this->getPoolForType(type);
				component->autorelease();
			}

#else
			auto component = new T();
			component->autorelease();

#endif//ESPERO_COMPONENT_POOLING

			return component;
		}
		
	public:
		ComponentMap * getComponentsFor(Entity *entity, ComponentMap &fillSet);
		
		void deleted(Entity *entity);
		
	public:
		void clean(void);
	};

END_NS_ESPERO

#endif//__ESPERO_COMPONENTMANAGER_H__
