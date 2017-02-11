LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := espero_static

LOCAL_MODULE_FILENAME := libespero

LOCAL_SRC_FILES := \
	Espero/Component/Aspect.cpp \
	Espero/Component/ComponentType.cpp \
	Espero/Entity/Entity.cpp \
	Espero/Entity/EntitySystem.cpp \
	Espero/Manager/ComponentManager.cpp \
	Espero/Manager/EntityManager.cpp \
	Espero/System/EntityProcessingSystem.cpp \
	Espero/System/IntervalEntityProcessingSystem.cpp \
	Espero/System/IntervalEntitySystem.cpp \
	Espero/Utils/BitSet.cpp \
	Espero/Utils/IdentifierPool.cpp \
	Espero/Utils/SpritePool.cpp \
	Espero/World.cpp

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/..

LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)/../cocos2d \
	$(LOCAL_PATH)/../cocos2d/cocos \
	$(LOCAL_PATH)/../cocos2d/cocos/platform/android \
	$(LOCAL_PATH)/../libFloreto

include $(BUILD_STATIC_LIBRARY)

