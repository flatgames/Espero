/*
 * Espero Entity Framework for Cocos2d-x 3.0
 *
 * Author: Anh N. Dang
 * Date  : 2014-04-18
 *
**/

#ifndef __ESPERO_ENTITYSYSTEM_H__
#define __ESPERO_ENTITYSYSTEM_H__

#include <cocos2d.h>

#include "../Config.h"
#include "EntityObserver.h"

BEGIN_NS_ESPERO

	class World;
	class Aspect;

	__IClassNameInternalDefine(EntitySystem);

	class EntitySystem : public EntityObserver, public IClassName, public cocos2d::Ref
	{
	private:
		CommonIndex systemIndex;

	protected:
		World *world;

		EntitySet *activeEntities;

		Aspect *aspect;

		BitSet allSet;
		BitSet exclusionSet;
		BitSet oneSet;

	private:
		bool passive;
		bool dummy;

	public:
		IClassNameImplement(EntitySystem);

		EntitySystem(Aspect *aspect);
		virtual ~EntitySystem(void);

	protected:
		virtual void begin(void);
		virtual void end(void);

	public:
		void process(void);

	protected:
		virtual void processEntities(const EntitySet &entities) =0;
		virtual bool checkProcessing(void) =0;

	public:
		virtual void initialize(void);

	protected:
		virtual void inserted(Entity *entity);
		virtual void removed(Entity *entity);

		void check(Entity *entity);

	private:
		void removeFromSystem(Entity *entity);
		void insertToSystem(Entity *entity);

	public:
		void added(Entity *entity);
		void changed(Entity *entity);
		void deleted(Entity *entity);
		void enabled(Entity *entity);
		void disabled(Entity *entity);

	public:
		void setWorld(World *world);
		void initIndex(void);

	public:
		inline virtual bool isPassive(void) const
		{
			return this->passive;
		}

		inline virtual void setPassive(bool value)
		{
			this->passive = value;
		}

	public:
		inline EntitySet * getActiveEntities(void)
		{
			return this->activeEntities;
		}

	private:
		class SystemIndexManager
		{
		private:
			static CommonIndex INDEX;
			static std::map<ClassName, CommonIndex> indices;

		public:
			static CommonIndex getIndexFor(ClassName type);
		};
	};

#define BeginForEachEntity(_entity_) \
	for (auto __it = entities.begin(), __itEnd = entities.end(); __it != __itEnd; ++__it) \
	{ \
		auto _entity_ = *__it;

#define EndForEachEntity }

END_NS_ESPERO

#endif//__ESPERO_ENTITYSYSTEM_H__
