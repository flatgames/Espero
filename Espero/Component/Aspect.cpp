/*
 * Espero Entity Framework for Cocos2d-x 3.0
 *
 * Author: Anh N. Dang
 * Date  : 2014-04-18
 *
**/

#include "Aspect.h"
#include <stdarg.h>

#include "ComponentType.h"

using namespace cocos2d;

BEGIN_NS_ESPERO

	//private
	Aspect::Aspect(void)
	{
		this->allSet.clearAll();
		this->exclusionSet.clearAll();
		this->oneSet.clearAll();
	}

	//protected
	void Aspect::all(ClassName class1, va_list list)
	{
		this->allSet.set(ComponentType::getIndexFor(class1));

		ClassName cls = va_arg(list, ClassName);
		while (cls)
		{
			this->allSet.set(ComponentType::getIndexFor(cls));
			cls = va_arg(list, ClassName);
		}
	}

	//protected
	void Aspect::exclude(ClassName class1, va_list list)
	{
		this->exclusionSet.set(ComponentType::getIndexFor(class1));

		ClassName cls = va_arg(list, ClassName);
		while (cls)
		{
			this->exclusionSet.set(ComponentType::getIndexFor(cls));
			cls = va_arg(list, ClassName);
		}
	}

	//protected
	void Aspect::one(ClassName class1, va_list list)
	{
		this->oneSet.set(ComponentType::getIndexFor(class1));

		ClassName cls = va_arg(list, ClassName);
		while (cls)
		{
			this->oneSet.set(ComponentType::getIndexFor(cls));
			cls = va_arg(list, ClassName);
		}
	}

	//public
	Aspect * Aspect::allAspects(ClassName class1, ...)
	{
		va_list list;
		va_start(list, class1);
		this->all(class1, list);
		va_end(list);
		
		return this;
	}

	//public
	Aspect * Aspect::excludeAspects(ClassName class1, ...)
	{
		va_list list;
		va_start(list, class1);
		this->exclude(class1, list);
		va_end(list);
		
		return this;
	}

	//public
	Aspect * Aspect::oneAspect(ClassName class1, ...)
	{
		va_list list;
		va_start(list, class1);
		this->one(class1, list);
		va_end(list);
		
		return this;
	}

	//public static
	Aspect * Aspect::getAspectForAll(ClassName class1, ...)
	{
		auto aspect = new Aspect();
		
		if (aspect)
		{
			va_list list;
			va_start(list, class1);
			aspect->all(class1, list);
			va_end(list);

			aspect->autorelease();
		}

		return aspect;
	}

	//public static
	Aspect * Aspect::getAspectForOne(ClassName class1, ...)
	{
		auto aspect = new Aspect();
		
		if (aspect)
		{
			va_list list;
			va_start(list, class1);
			aspect->one(class1, list);
			va_end(list);

			aspect->autorelease();
		}

		return aspect;
	}

	//public static
	Aspect * Aspect::getEmpty(void)
	{
		auto aspect = new Aspect();
		if (aspect)
			return static_cast<Aspect *>(aspect->autorelease());
		else
			return nullptr;
	}

END_NS_ESPERO
