/*
 * Espero Entity Framework for Cocos2d-x 3.0
 *
 * Author: Anh N. Dang
 * Date  : 2014-04-18
 *
**/

#ifndef __ESPERO_WORLD_H__
#define __ESPERO_WORLD_H__

#include <cocos2d.h>

#include "Config.h"
#include "Manager/EntityManager.h"
#include "Manager/ComponentManager.h"

BEGIN_NS_ESPERO

	template<typename T>
	class ComponentMapper;

	class World : public cocos2d::Ref
	{
	public:
		typedef void (*Performer)(EntityObserver *observer, Entity *entity);
		typedef Vector<Entity> EntityVector;

	private:
		static World *instance;

	protected:
		EntityManager    *entityManager;
		ComponentManager *componentManager;

		EntityVector  *addedEntities;
		EntityVector  *changedEntities;
		EntityVector  *deletedEntities;
		EntityVector  *enabledEntities;
		EntityVector  *disabledEntities;

		ManagerMap      *managers;
		Vector<Manager> *managerSet;

		SystemMap            *systems;
		Vector<EntitySystem> *systemSet;

		float dt;
		bool running;
		bool initialized;

	public:
		static World * getInstance(void);
		static void cleanInstance(void);

	public:
		static World * create(void);

		World(void);
		virtual ~World(void);

	public:
		virtual void initialize(void);

		inline bool isInitialized(void) const
		{
			return this->initialized;
		}

		inline EntityManager * getEntityManager(void)
		{
			return this->entityManager;
		}

		inline ComponentManager * getComponentManager(void)
		{
			return this->componentManager;
		}

		Manager * setManager(Manager *manager);

		Manager * getManager(ClassName classType);

		void deleteManager(Manager *manager);

	public:
		inline float getDelta(void) const
		{
			return this->dt;
		}

		inline bool isRunning(void) const
		{
			return this->running;
		}

		void update(float dt);

		void start(void);
		void stop(void);

	public:
		void addEntity(Entity *entity);
		void changedEntity(Entity *entity);
		void deleteEntity(Entity *entity);
		void enable(Entity *entity);
		void disable(Entity *entity);

		Entity * createEntity(void);

		Entity * getEntity(EntityId id);

	public:
		inline Vector<EntitySystem> * getSystems(void)
		{
			return this->systemSet;
		}

		EntitySystem * addSystem(EntitySystem *system);

		EntitySystem * addSystem(EntitySystem *system, bool passive);

		void deleteSystem(EntitySystem *system);

		EntitySystem * getSystem(ClassName classType);

	protected:
		void notifySystems(Performer performer, Entity *entity);
		void notifyManagers(Performer performer, Entity *entity);

		void check(EntityVector *entities, Performer performer);

	protected:
		void process(void);
	};

END_NS_ESPERO

#endif//__ESPERO_WORLD_H__
