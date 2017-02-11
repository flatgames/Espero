/*
 * Espero Entity Framework for Cocos2d-x 3.0
 *
 * Author: Anh N. Dang
 * Date  : 2014-04-18
 *
**/

#ifndef __ESPERO_SPRITEPOOL_H__
#define __ESPERO_SPRITEPOOL_H__

#include <cocos2d.h>

#include "../Common.h"
#include "../IClassName.h"
#include "Bag.h"
#include "Pool.h"

BEGIN_NS_ESPERO

	__IClassNameInternalDefine(SpritePool);

	class SpritePool : public IClassName, public cocos2d::Ref
	{
	protected:
		Bag<Pool<cocos2d::Sprite>> *poolsByTag;
		Pool<cocos2d::Sprite>::PoolDelegate onIntoPool;
		Pool<cocos2d::Sprite>::PoolDelegate onOutOfPool;
		Pool<cocos2d::Sprite>::PoolDelegate onCleaned;

	public:
		IClassNameImplement(SpritePool);

		static SpritePool * create(void);

		static SpritePool * createWithDelegates(
			Pool<cocos2d::Sprite>::PoolDelegate onIntoPool = nullptr,
			Pool<cocos2d::Sprite>::PoolDelegate onOutOfPool = nullptr,
			Pool<cocos2d::Sprite>::PoolDelegate onCleaned = nullptr);

		SpritePool(
			Pool<cocos2d::Sprite>::PoolDelegate onIntoPool,
			Pool<cocos2d::Sprite>::PoolDelegate onOutOfPool,
			Pool<cocos2d::Sprite>::PoolDelegate onCleaned);

		virtual ~SpritePool(void);

	public:
		void setDelegates(
			Pool<cocos2d::Sprite>::PoolDelegate onIntoPool,
			Pool<cocos2d::Sprite>::PoolDelegate onOutOfPool,
			Pool<cocos2d::Sprite>::PoolDelegate onCleaned,
			bool onlyNewPools = true);

	public:
		Pool<cocos2d::Sprite> * getPoolByTag(int tag);

		cocos2d::Sprite * give(int tag);

		void take(cocos2d::Sprite *sprite, int tag);

		cocos2d::Sprite * createWithFileName(const char *fileName, int tag);
		cocos2d::Sprite * createWithSpriteFrame(cocos2d::SpriteFrame *frame, int tag);
		cocos2d::Sprite * createWithSpriteFrameName(const char *frameName, int tag);
	};

END_NS_ESPERO

#endif//__ESPERO_SPRITEPOOL_H__
