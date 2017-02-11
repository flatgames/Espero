/*
 * Espero Entity Framework for Cocos2d-x 3.0
 *
 * Author: Anh N. Dang
 * Date  : 2014-04-18
 *
**/

#ifndef __ESPERO_COMPONENT_H__
#define __ESPERO_COMPONENT_H__

#include <cocos2d.h>

#include "../Config.h"
#include "../IClassName.h"

BEGIN_NS_ESPERO

	class Entity;
	class ComponentManager;
	
	__IClassNameInternalDefine(Component);

	// Component base class. All component types should derive from this and override IClassName methods.
	class Component : public IClassName, public cocos2d::Ref
	{
		friend class ComponentManager;

	protected:
		Entity *entity;
		bool active;

#if ESPERO_COMPONENT_POOLING
		Pool<Component> *pool;
#endif//ESPERO_COMPONENT_POOLING

	public:
		IClassNameImplement(Component);

		Component(void)
			: entity(nullptr), active(true)
#if ESPERO_COMPONENT_POOLING
			, pool(nullptr)
#endif//ESPERO_COMPONENT_POOLING
		{
		}
		
		virtual ~Component(void)
		{
		}

	public:

#if ESPERO_COMPONENT_POOLING

		// Raised when the component is put into a component pool.
		virtual void onIntoPool(ComponentManager *mananger)
		{
		}

		// Raised when the component is taken out of a component pool.
		virtual void onOutOfPool(ComponentManager *manager)
		{
			this->active = true;
			this->entity = nullptr;
		}

#endif//ESPERO_COMPONENT_POOLING

	public:
		inline Entity * getEntity(void)
		{
			return this->entity;
		}

		inline bool isActive(void) const
		{
			return this->active;
		}

		inline void setActive(bool active)
		{
			this->active = active;
		}

	protected:
		inline void setEntity(Entity *entity)
		{
			this->entity = entity;
		}
	};

// The following macroes serve 2 purposes:
// - Providing semantic meaning.
// - Making code cleaner.

#define ComponentVar(__type__, __var__) \
	protected: \
		__type__ __var__;

#define ComponentVarObject(__type__, __var__) \
	protected: \
		__type__ * __var__;

#define InitVar(__var__) __var__(decltype(__var__)())

#define ComponentProperty(__type__, __name__, __var__) \
	protected: \
		__type__ __var__; \
	public: \
		inline const __type__ get##__name__(void) const { return this->__var__; } \
		inline __type__ get##__name__(void) { return this->__var__; } \
		inline void set##__name__(__type__ value) { this->__var__ = value; }

#define ComponentPropertyBool(__type__, __name__, __var__) \
	protected: \
	__type__ __var__; \
	public: \
	inline const __type__ is##__name__(void) const { return this->__var__; } \
	inline __type__ is##__name__(void) { return this->__var__; } \
	inline void set##__name__(__type__ value) { this->__var__ = value; }

#define ComponentPropertyByRef(__type__, __name__, __var__) \
	protected: \
		__type__ __var__; \
	public: \
		inline const __type__ & get##__name__(void) const { return this->__var__; } \
		inline __type__ & get##__name__(void) { return this->__var__; } \
		inline void set##__name__(const __type__ & value) { this->__var__ = value; }

#define ComponentPropertyObject(__type__, __name__, __var__) \
	protected: \
		__type__ * __var__; \
	public: \
		inline const __type__ * get##__name__(void) const { return this->__var__; } \
		inline __type__ * get##__name__(void) { return this->__var__; } \
		inline void set##__name__(__type__ *value) { CC_SAFE_RELEASE_NULL(this->__var__); this->__var__ = value; CC_SAFE_RETAIN(value); }

#define ComponentReadOnlyProperty(__type__, __name__, __var__) \
	protected: \
		__type__ __var__; \
	public: \
		inline const __type__ get##__name__(void) const { return this->__var__; } \
		inline __type__ get##__name__(void) { return this->__var__; }

#define ComponentReadOnlyPropertyByRef(__type__, __name__, __var__) \
	protected: \
		__type__ __var__; \
	public: \
		inline const __type__ & get##__name__(void) const { return this->__var__; } \
		inline __type__ & get##__name__(void) { return this->__var__; }

#define ComponentReadOnlyPropertyObject(__type__, __name__, __var__) \
	protected: \
		__type__ * __var__; \
	public: \
		inline const __type__ * get##__name__(void) const { return this->__var__; } \
		inline __type__ * get##__name__(void) { return this->__var__; }

#define ComponentReadOnlyPropertyBool(__type__, __name__, __var__) \
	protected: \
	__type__ __var__; \
	public: \
	inline const __type__ is##__name__(void) const { return this->__var__; } \
	inline __type__ is##__name__(void) { return this->__var__; }

#define InitProperty(__var__) InitVar(__var__)

#define ReleaseProperty(__name__) CC_SAFE_RELEASE_NULL(__name__)

END_NS_ESPERO

#endif//__ESPERO_COMPONENT_H__
