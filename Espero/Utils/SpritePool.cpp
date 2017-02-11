/*
 * Espero Entity Framework for Cocos2d-x 3.0
 *
 * Author: Anh N. Dang
 * Date  : 2014-04-18
 *
**/

#include "SpritePool.h"

using namespace cocos2d;

BEGIN_NS_ESPERO

	SpritePool * SpritePool::create(void)
	{
		return SpritePool::createWithDelegates(nullptr, nullptr, nullptr);
	}

	SpritePool * SpritePool::createWithDelegates(
		Pool<cocos2d::Sprite>::PoolDelegate onIntoPool,
		Pool<cocos2d::Sprite>::PoolDelegate onOutOfPool,
		Pool<cocos2d::Sprite>::PoolDelegate onCleaned)
	{
		auto pool = new SpritePool(onIntoPool, onOutOfPool, onCleaned);
		if (pool)
		{
			pool->autorelease();
			return pool;
		}
		
		return nullptr;
	}

	SpritePool::SpritePool(
		Pool<cocos2d::Sprite>::PoolDelegate onIntoPool,
		Pool<cocos2d::Sprite>::PoolDelegate onOutOfPool,
		Pool<cocos2d::Sprite>::PoolDelegate onCleaned)
		: onIntoPool(onIntoPool), onOutOfPool(onOutOfPool), onCleaned(onCleaned)
	{
		this->poolsByTag = Bag<Pool<Sprite>>::create();
		this->poolsByTag->retain();
	}

	SpritePool::~SpritePool(void)
	{
		CC_SAFE_RELEASE_NULL(this->poolsByTag);
	}

	void SpritePool::setDelegates(
			Pool<cocos2d::Sprite>::PoolDelegate onIntoPool,
			Pool<cocos2d::Sprite>::PoolDelegate onOutOfPool,
			Pool<cocos2d::Sprite>::PoolDelegate onCleaned,
			bool onlyNewPools)
	{
		this->onIntoPool = onIntoPool;
		this->onOutOfPool = onOutOfPool;
		this->onCleaned = onCleaned;

		if (!onlyNewPools)
		{
			for (Bag<Pool<Sprite>>::SizeType i = 0, c = this->poolsByTag->getSize(); i < c; ++i)
			{
				auto pool = this->poolsByTag->getObjectUnsafe(i);
				if (pool)
					pool->setDelegates(onIntoPool, onOutOfPool, onCleaned);
			}
		}
	}

	Pool<cocos2d::Sprite> * SpritePool::getPoolByTag(int tag)
	{
		auto pool = this->poolsByTag->getObject(tag);
		if (!pool)
		{
			pool = Pool<Sprite>::createWithDelegates(this->onIntoPool, this->onOutOfPool, this->onCleaned, tag);
			this->poolsByTag->addObject(tag, pool);
		}

		return pool;
	}

	Sprite * SpritePool::give(int tag)
	{
		auto pool = this->getPoolByTag(tag);
		if (pool && pool->getSize())
		{
			auto sprite = pool->give();
			return sprite;
		}

		return nullptr;
	}

	void SpritePool::take(Sprite *sprite, int tag)
	{
		auto pool = this->getPoolByTag(tag);
		pool->take(sprite);
	}

	Sprite * SpritePool::createWithFileName(const char *fileName, int tag)
	{
		auto sprite = this->give(tag);
		if (!sprite)
			sprite = Sprite::create(fileName);

		return sprite;
	}

	Sprite * SpritePool::createWithSpriteFrame(SpriteFrame *frame, int tag)
	{
		auto sprite = this->give(tag);
		if (!sprite)
			sprite = Sprite::createWithSpriteFrame(frame);

		return sprite;
	}

	Sprite * SpritePool::createWithSpriteFrameName(const char *frameName, int tag)
	{
		auto sprite = this->give(tag);
		if (!sprite)
			sprite = Sprite::createWithSpriteFrameName(frameName);

		return sprite;
	}

END_NS_ESPERO
