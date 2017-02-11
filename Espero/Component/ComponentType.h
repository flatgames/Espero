/*
 * Espero Entity Framework for Cocos2d-x 3.0
 *
 * Author: Anh N. Dang
 * Date  : 2014-04-18
 *
**/

#ifndef __ESPERO_COMPONENTTYPE_H__
#define __ESPERO_COMPONENTTYPE_H__

#include <stdint.h>
#include <map>
#include <cocos2d.h>

#include "../Config.h"

BEGIN_NS_ESPERO

	__IClassNameInternalDefine(ComponentType);

	class ComponentType : public IClassName, public cocos2d::Ref
	{
	private:
		static CommonIndex INDEX;
		static Bag<ComponentType> componentTypes;
		
	private:
		CommonIndex index;
		ClassName   type;

	public:
		IClassNameImplement(ComponentType);
		
	private:
		static ComponentType * create(ClassName type);
	
	private:
		ComponentType(ClassName type);

	public:
		virtual ~ComponentType(void);

	public:
		void cleanUp(void);
		
	public:
		inline CommonIndex getIndex(void) const
		{
			return this->index;
		}

		inline ClassName getComponentClass(void) const
		{
			return this->type;
		}
		
		// Returns the ComponentType instance corresponding to the given Component class.
		static ComponentType * getTypeFor(ClassName type);
		
		// Returns the unique index of the ComponentType instance corresponding to the given Component class.
		static CommonIndex getIndexFor(ClassName type);
	};

END_NS_ESPERO

#endif//__ESPERO_COMPONENTTYPE_H__
