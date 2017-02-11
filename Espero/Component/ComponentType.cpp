/*
 * Espero Entity Framework for Cocos2d-x 3.0
 *
 * Author: Anh N. Dang
 * Date  : 2014-04-18
 *
**/

#include "ComponentType.h"
#include "Component.h"
#include "../Entity/Entity.h"

using namespace cocos2d;

BEGIN_NS_ESPERO

	CommonIndex        ComponentType::INDEX = 0;
	Bag<ComponentType> ComponentType::componentTypes;

	//public static
	ComponentType * ComponentType::create(ClassName type)
	{
		auto ct = new ComponentType(type);
		if (ct)
			return static_cast<ComponentType *>(ct->autorelease());

		return nullptr;
	}

	//private
	ComponentType::ComponentType(ClassName type)
	{
		this->index = ComponentType::INDEX++;
		this->type = type;
	}

	//public virtual
	ComponentType::~ComponentType(void)
	{
	}

	//public static
	void ComponentType::cleanUp(void)
	{
		ComponentType::componentTypes.clearObjects();
		ComponentType::INDEX = 0;
	}

	//public static
	ComponentType * ComponentType::getTypeFor(ClassName type)
	{
		auto componentType = ComponentType::componentTypes.getObject(type);
		if (componentType)
			return componentType;

		componentType = ComponentType::create(type);
		ComponentType::componentTypes.addObject(type, componentType);

		return componentType;
	}

	//public static
	CommonIndex ComponentType::getIndexFor(ClassName type)
	{
		return ComponentType::getTypeFor(type)->getIndex();
	}

END_NS_ESPERO
