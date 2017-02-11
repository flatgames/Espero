/*
 * Espero Entity Framework for Cocos2d-x 3.0
 *
 * Author: Anh N. Dang
 * Date  : 2014-04-18
 *
**/

#ifndef __ESPERO_CONFIG_H__
#define __ESPERO_CONFIG_H__

#include <stdint.h>
#include <set>

#include <cocos2d.h>

#include "Common.h"
#include "IClassName.h"
#include "Utils/Vector.h"
#include "Utils/Map.h"
#include "Utils/Set.h"
#include "Utils/Bag.h"
#include "Utils/BitSet.h"
#include "Utils/Queue.h"
#include "Utils/Pool.h"

BEGIN_NS_ESPERO

	// Standard 32-bit signed integer.
	typedef int32_t Int32;
	
	// Standard 64-bit signed integer.
	typedef int64_t Int64;
	
	// Standard type for object indices.
	typedef uintptr_t CommonIndex;

	// Standard type for entity id's.
	typedef CommonIndex EntityId;

	// Standard Set type for common indices.
	typedef std::set<CommonIndex> CommonIndexSet;

	// Standard Set type for class names.
	typedef std::set<ClassName> ClassNameSet;

	class Entity;
	class EntitySystem;
	class Component;
	class ComponentType;
	class Manager;

	typedef Map<ClassName, Entity>        EntityMap;
	typedef Map<ClassName, EntitySystem>  SystemMap;
	typedef Map<ClassName, Component>     ComponentMap;
	typedef Map<ClassName, ComponentType> ComponentTypeMap;
	typedef Map<ClassName, Manager>       ManagerMap;

	typedef Set<Entity>        EntitySet;
	typedef Set<EntitySystem>  SystemSet;
	typedef Set<Component>     ComponentSet;
	typedef Set<ComponentType> ComponentTypeSet;
	typedef Set<Manager>       ManagerSet;

	typedef Bag<Entity>        EntityBag;
	typedef Bag<EntitySystem>  SystemBag;
	typedef Bag<Component>     ComponentBag;
	typedef Bag<ComponentType> ComponentTypeBag;
	typedef Bag<Manager>       ManagerBag;

#define BeginSetForEach(__obj__, __container__, __itSuffix) \
	for (auto it##__itSuffix = __container__.begin(), itEnd##__itSuffix = __container__.end(); \
		it##__itSuffix != itEnd##__itSuffix; ++it##__itSuffix) \
		{ \
		auto __obj__ = *it##__itSuffix; \

#define BeginMapForEach(__obj__, __container__, __itSuffix) \
	for (auto it##__itSuffix = __container__.begin(), itEnd##__itSuffix = __container__.end(); \
		it##__itSuffix != itEnd##__itSuffix; ++it##__itSuffix) \
		{ \
		auto __obj__ = it##__itSuffix->second; \

#define EndForEach }

// Enable or disable pooling for entities
#define ESPERO_ENTITY_POOLING    0

// Enable or disable pooling for components
#define ESPERO_COMPONENT_POOLING 1

END_NS_ESPERO

#endif//__ESPERO_CONFIG_H__
