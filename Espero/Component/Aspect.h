/*
 * Espero Entity Framework for Cocos2d-x 3.0
 *
 * Author: Anh N. Dang
 * Date  : 2014-04-18
 *
**/

#ifndef __ESPERO_ASPECT_H__
#define __ESPERO_ASPECT_H__

#include <stdarg.h>
#include <cocos2d.h>

#include "../Config.h"

BEGIN_NS_ESPERO

	class Aspect : public cocos2d::Ref
	{
	private:
		BitSet allSet;
		BitSet exclusionSet;
		BitSet oneSet;

	private:
		Aspect(void);

	public:
		inline BitSet & getAllSet(void)
		{
			return this->allSet;
		}

		inline BitSet & getExclusionSet(void)
		{
			return this->exclusionSet;
		}

		inline BitSet & getOneSet(void)
		{
			return this->oneSet;
		}

	protected:
		void all(ClassName class1, va_list list);
		void exclude(ClassName class1, va_list list);
		void one(ClassName class1, va_list list);

	public:
		Aspect * allAspects(ClassName class1, ...);
		Aspect * excludeAspects(ClassName class1, ...);
		Aspect * oneAspect(ClassName class1, ...);

	public:
		static Aspect * getAspectForAll(ClassName class1, ...);
		static Aspect * getAspectForOne(ClassName class1, ...);
		static Aspect * getEmpty(void);
	};

END_NS_ESPERO

#define AllAspects1(_cls1_) Espero::Aspect::getAspectForAll(sharedclassof(_cls1_), 0)
#define AllAspects2(_cls1_, _cls2_) Espero::Aspect::getAspectForAll(sharedclassof(_cls1_), sharedclassof(_cls2_), 0)
#define AllAspects3(_cls1_, _cls2_, _cls3_) Espero::Aspect::getAspectForAll(sharedclassof(_cls1_), sharedclassof(_cls2_), sharedclassof(_cls3_), 0)
#define AllAspects4(_cls1_, _cls2_, _cls3_, _cls4_) Espero::Aspect::getAspectForAll(sharedclassof(_cls1_), sharedclassof(_cls2_), sharedclassof(_cls3_), sharedclassof(_cls4_), 0)

#define OneAspect1(_cls1_) Espero::Aspect::getAspectForOne(sharedclassof(_cls1_), 0)
#define OneAspect2(_cls1_, _cls2_) Espero::Aspect::getAspectForOne(sharedclassof(_cls1_), sharedclassof(_cls2_), 0)
#define OneAspect3(_cls1_, _cls2_, _cls3_) Espero::Aspect::getAspectForOne(sharedclassof(_cls1_), sharedclassof(_cls2_), sharedclassof(_cls3_), 0)
#define OneAspect4(_cls1_, _cls2_, _cls3_, _cls4_) Espero::Aspect::getAspectForOne(sharedclassof(_cls1_), sharedclassof(_cls2_), sharedclassof(_cls3_), sharedclassof(_cls4_), 0)

#define __AspectVaArgsExpand(__x__) __x__
#define __GetAspectName(_1, _2, _3, _4, __name, ...) __name

#define AllAspects(...) __AspectVaArgsExpand(__GetAspectName(__VA_ARGS__, AllAspects4, AllAspects3, AllAspects2, AllAspects1)(__VA_ARGS__))
#define OneAspect(...) __AspectVaArgsExpand(__GetAspectName(__VA_ARGS__, OneAspect4, OneAspect3, OneAspect2, OneAspect1)(__VA_ARGS__))

#endif//__ESPERO_ASPECT_H__
