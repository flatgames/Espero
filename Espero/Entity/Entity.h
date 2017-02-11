/*
 * Espero Entity Framework for Cocos2d-x 3.0
 *
 * Author: Anh N. Dang
 * Date  : 2014-04-18
 *
**/

#ifndef __ESPERO_ENTITY_H__
#define __ESPERO_ENTITY_H__

#include <cocos2d.h>

#include "../Config.h"
#include "../IClassName.h"
#include "../Component/Component.h"
#include "../Manager/ComponentManager.h"

BEGIN_NS_ESPERO

	class World;
	class EntityManager;

	__IClassNameInternalDefine(Entity);

	class Entity : public IClassName, public cocos2d::Ref
	{
		friend class EntityManager;

	protected:
		EntityId id;
		BitSet componentBits;
		BitSet systemBits;
		
		World            *world;
		EntityManager    *entityManager;
		ComponentManager *componentManager;

		bool deleted;

		void *userData;
		
	public:
		IClassNameImplement(Entity);

	public:
		static Entity * create(World *world, EntityId id);

	protected:
		Entity(World *world, EntityId id);

	public:
		virtual ~Entity(void);
		
	public:
		inline EntityId getId(void) const
		{
			return this->id;
		}
		
		inline BitSet & getComponentBits(void)
		{
			return this->componentBits;
		}
		
		inline const BitSet & getComponentBits(void) const
		{
			return this->componentBits;
		}
		
		inline BitSet & getSystemBits(void)
		{
			return this->systemBits;
		}
		
		inline const BitSet & getSystemBits(void) const
		{
			return this->systemBits;
		}
		
		Entity * addComponent(Component *component);
		Entity * addComponent(Component *component, ComponentType *type);
		
		Entity * removeComponent(Component *component);
		Entity * removeComponent(ComponentType *type);
		Entity * removeComponent(ClassName classType);
		
		Component * getComponent(ComponentType *type);
		Component * getComponent(ClassName classType);

		template<typename T>
		T * getComponent(void)
		{
			static_assert(std::is_convertible<T *, Espero::Component *>::value, "T is not Component.");
			return static_cast<T*>(this->componentManager->getComponent(this, ComponentType::getTypeFor(sharedclassof(T))));
		}

		template<typename T>
		Entity * removeComponent(void)
		{
			static_assert(std::is_convertible<T *, Espero::Component *>::value, "T is not Component.");

			this->componentManager->removeComponent(this, ComponentType::getTypeFor(sharedclassof(T)));
			return this;
		}

		ComponentMap * getComponents(ComponentMap &fillSet);
		
		bool isActive(void) const;
		bool isEnabled(void) const;
		bool isDeleted(void) const;
		void setDeleted(bool value);
		
		void addToWorld(void);
		void changedInWorld(void);
		void deleteFromWorld(void);
		
		void enable(void);
		void disable(void);
		
		inline World * getWorld(void)
		{
			return this->world;
		}
		
		inline const World * getWorld(void) const
		{
			return this->world;
		}

		inline void * getUserData(void)
		{
			return this->userData;
		}

		inline void setUserData(void *data)
		{
			this->userData = data;
		}
		
	protected:
		void reset(void);
	};
	
END_NS_ESPERO

#endif//__ESPERO_ENTITY_H__
