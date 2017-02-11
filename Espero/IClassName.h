/*
 * Espero Entity Framework for Cocos2d-x 3.0
 *
 * Author: Anh N. Dang
 * Date  : 2014-04-18
 *
**/

#ifndef __ESPERO_ICLASSNAME_H__
#define __ESPERO_ICLASSNAME_H__

#include "Common.h"

BEGIN_NS_ESPERO

	typedef unsigned int ClassName;

	static ClassName ICLASSNAME_INDEX_BASE = 0;

	class IClassName
	{
	public:
		virtual ClassName getClass(void) const =0;
	};

#define IClassName_VarNameOf(_name_) __IClassName_for_##_name_

#define IClassNameImplement_Instance(_name_) \
	public: inline virtual Espero::ClassName getClass(void) const \
	{ \
		return IClassName_VarNameOf(_name_); \
	}

#define IClassNameImplement_Shared(_name_) \
	public: inline static Espero::ClassName getClassShared(void) \
	{ \
		return IClassName_VarNameOf(_name_); \
	}

#define IClassNameImplement(_name_) \
	IClassNameImplement_Instance(_name_) \
	IClassNameImplement_Shared(_name_)

#define classof(_obj_) ((_obj_)->getClass())
#define sharedclassof(_type_) (_type_::getClassShared())

// This is for internal usage.
// For your project, use IClassNameDeclare and IClassNameDefine.
#define __IClassNameInternalDefine(_name_) \
	static Espero::ClassName IClassName_VarNameOf(_name_) = Espero::ICLASSNAME_INDEX_BASE++
	
// Declares an extern ClassName variable representing the class declared in the current header.
// Put this in the header file, before the declaration of the class.
#define IClassNameDeclare(__name__) extern const Espero::ClassName IClassName_VarNameOf(__name__)

// Defines a ClassName variable representing the class declared in the corresponding header.
// Put this in a source file.
#define IClassNameDefine(__name__) const Espero::ClassName IClassName_VarNameOf(__name__) = Espero::ICLASSNAME_INDEX_BASE++

}

#endif//__ESPERO_ICLASSNAME_H__
