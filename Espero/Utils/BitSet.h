/*
 * Espero Entity Framework for Cocos2d-x 3.0
 *
 * Author: Anh N. Dang
 * Date  : 2014-04-18
 *
**/

#ifndef __ESPERO_BITSET_H__
#define __ESPERO_BITSET_H__

#include <stdint.h>
#include <memory.h>
#include <limits.h>
#include <cocos2d.h>

#include "../Common.h"

BEGIN_NS_ESPERO

	class BitSet : public cocos2d::Ref
	{
	public:
		typedef size_t IndexType;

	protected:
		typedef IndexType  SizeType;
		typedef uintptr_t  PackType;
		typedef PackType  *SetType;

	protected:
		PackType *packs;
		size_t    packCount;

	public:
		static BitSet * create(void);

		BitSet(void);
		BitSet(const BitSet &other);
		virtual ~BitSet(void);

	public:
		void swap(BitSet &other);

		BitSet & operator=(const BitSet &other);

		bool operator==(const BitSet &other);
		bool operator!=(const BitSet &other);

	public:
		void intersectWith(const BitSet &other);
		void unionWith(const BitSet &other);
		void exclude(const BitSet &other);
		void inverse(void);

		bool any(void) const;
		bool none(void) const;

	public:
		bool check(IndexType index) const;
		bool checkUnsafe(IndexType index) const;

		void set(IndexType index);

		void clear(IndexType index);

		void flip(IndexType index);

		void setAll(void);

		void clearAll(void);

		IndexType getBitCount(void) const;

	protected:
		void getIndicies(IndexType index, IndexType &packIndex, IndexType &bitIndex) const;
		void ensurePacksForIndex(IndexType index);
	};

END_NS_ESPERO

#endif//__ESPERO_BITSET_H__
