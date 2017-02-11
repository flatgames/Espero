/*
 * Espero Entity Framework for Cocos2d-x 3.0
 *
 * Author: Anh N. Dang
 * Date  : 2014-04-18
 *
**/

#ifndef __ESPERO_COMPONENTMMAPPER_H__
#define __ESPERO_COMPONENTMMAPPER_H__

#include <set>
#include <cocos2d.h>

#include "../Config.h"
#include "../Entity/Entity.h"
#include "../World.h"
#include "Component.h"
#include "ComponentType.h"

BEGIN_NS_ESPERO

	__IClassNameInternalDefine(ComponentMapper);

	// A mapping from Component class to instance.
	// Type parameter T should be a derived class of class Component.
	template<typename T>
	class ComponentMapper : public IClassName, public cocos2d::Ref
	{
	private:
		// The ComponentType instance corresponding to the specified Component class.
		ComponentType *type;
		
		// The specified Component class.
		ClassName classType;

		// A collection of Component instances corresponding to their owners' id.
		ComponentBag *components;

	public:
		// Creates a mapper from the given Component class to owner Entities, for the given World instance.
		inline static ComponentMapper<T> * create(ClassName classType, World *world)
		{
			static_assert(std::is_convertible<T, Espero::Component>::value, "T is not Component.");

			auto mapper = new ComponentMapper<T>(classType, world);
			if (mapper)
				return static_cast<ComponentMapper<T>*>(mapper->autorelease());
			
			return nullptr;
		}

		IClassNameImplement(ComponentMapper);

	private:
		ComponentMapper(ClassName classType, World *world)
		{
			this->type = ComponentType::getTypeFor(classType);
			this->type->retain();

			this->classType = classType;
			this->components = world->getComponentManager()->getComponentsByType(this->type);
		}
		
	public:
		virtual ~ComponentMapper(void)
		{
			CC_SAFE_RELEASE_NULL(this->type);
		}

	public:
		// Returns a Component instance for the given owner entity.
		// If there is no such instance, returned value is NULL.
		inline T * get(Entity *entity)
		{
			static_assert(std::is_convertible<T, Espero::Component>::value, "T is not Component.");

			return static_cast<T *>(this->components->getObject(entity->getId()));
		}

		// Returns true if there is a Component instance for the given owner entity. Otherwise, false.
		inline bool has(Entity *entity)
		{
			return this->components.has(entity->getId());
		}
	};

#define MapComponentClass(_mapper_, _classname_) \
	do { \
		_mapper_ = ComponentMapper<_classname_>::create(sharedclassof(_classname_), this->world); \
		CC_SAFE_RETAIN(_mapper_); \
	} while (false)

END_NS_ESPERO

#endif//__ESPERO_COMPONENTMMAPPER_H__
