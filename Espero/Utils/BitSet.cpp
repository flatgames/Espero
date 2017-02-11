/*
 * Espero Entity Framework for Cocos2d-x 3.0
 *
 * Author: Anh N. Dang
 * Date  : 2014-04-18
 *
**/

#include "BitSet.h"

using namespace cocos2d;

BEGIN_NS_ESPERO

	//public static
	BitSet * create(void)
	{
		BitSet *bitset = new BitSet();
		if (bitset)
			return static_cast<BitSet *>(bitset->autorelease());

		return nullptr;
	}

	//public
	BitSet::BitSet(void)
		: packs(nullptr), packCount(0)
	{
	}

	//public
	BitSet::BitSet(const BitSet &other)
	{
		this->packCount = other.packCount;
		this->packs = new PackType[this->packCount];
		memcpy(this->packs, other.packs, this->packCount * sizeof(PackType));
	}

	//public virtual
	BitSet::~BitSet(void)
	{
		if (this->packs)
		{
			delete []this->packs;
			this->packs = nullptr;
			this->packCount = 0;
		}
	}
	
	//public
	void BitSet::swap(BitSet &other)
	{
		auto packs = this->packs;
		auto packCount = this->packCount;

		this->packs = other.packs;
		this->packCount = other.packCount;

		other.packs = packs;
		other.packCount = packCount;
	}
	
	//public
	BitSet & BitSet::operator=(const BitSet &other)
	{
		if (this != &other)
		{
			BitSet bitset(other);
			this->swap(bitset);
		}

		return *this;
	}
	
	//public
	bool BitSet::operator==(const BitSet &other)
	{
		if (this == &other)
			return true;
		else if (this->packCount != other.packCount)
			return false;

		for (size_t i = 0, c = this->packCount; i < c; ++i)
			if (this->packs[i] != other.packs[i])
				return false;

		return true;
	}
	
	//public
	bool BitSet::operator!=(const BitSet &other)
	{
		if (this == &other)
			return false;
		else if (this->packCount != other.packCount)
			return true;

		for (size_t i = 0, c = this->packCount; i < c; ++i)
			if (this->packs[i] != other.packs[i])
				return true;

		return false;
	}
	
	//public
	void BitSet::intersectWith(const BitSet &other)
	{
		auto thisPacks = this->packs;
		auto thisPackCount = this->packCount;

		auto otherPacks = other.packs;
		auto otherPackCount = other.packCount;

		size_t minCount;
		if (thisPackCount > otherPackCount)
			minCount = otherPackCount;
		else
			minCount = thisPackCount;

		for (size_t i = 0; i < minCount; ++i)
			thisPacks[i] &= otherPacks[i];

		for (size_t i = minCount; i < thisPackCount; ++i)
			thisPacks[i] = 0;
	}

	//public
	void BitSet::unionWith(const BitSet &other)
	{
		auto thisPacks = this->packs;
		auto thisPackCount = this->packCount;

		auto otherPacks = other.packs;
		auto otherPackCount = other.packCount;

		size_t minCount;
		if (thisPackCount > otherPackCount)
		{
			minCount = otherPackCount;
		}
		else
		{
			minCount = thisPackCount;

			// since it is OR, and `other` has more packs
			// => add the extended packs to this
			auto packs = new PackType[otherPackCount];
			// copy old values
			memcpy(packs, thisPacks, thisPackCount * sizeof(PackType));
			// copy extended values from `other`
			memcpy(packs + thisPackCount, otherPacks, (otherPackCount - thisPackCount) * sizeof(PackType));

			this->packs = packs;
			thisPacks = packs;
		}

		for (size_t i = 0; i < minCount; ++i)
			thisPacks[i] |= otherPacks[i];
	}

	//public
	void BitSet::exclude(const BitSet &other)
	{
		auto thisPacks = this->packs;
		auto thisPackCount = this->packCount;

		auto otherPacks = other.packs;
		auto otherPackCount = other.packCount;

		size_t minCount;
		if (thisPackCount > otherPackCount)
			minCount = otherPackCount;
		else
			minCount = thisPackCount;

		for (size_t i = 0; i < minCount; ++i)
			thisPacks[i] &= otherPacks[i];

		for (size_t i = minCount; i < thisPackCount; ++i)
			thisPacks[i] = (PackType)(~0);
	}

	//public
	void BitSet::inverse(void)
	{
		auto thisPacks = this->packs;
		auto thisPackCount = this->packCount;

		for (size_t i = 0; i < thisPackCount; ++i)
			thisPacks[i] = ~thisPacks[i];
	}
	
	//public
	bool BitSet::any(void) const
	{
		for (size_t i = 0, c = this->packCount; i < c; ++i)
			if (this->packs[i])
				return true;

		return false;
	}
	
	//public
	bool BitSet::none(void) const
	{
		for (size_t i = 0, c = this->packCount; i < c; ++i)
			if (this->packs[i])
				return false;

		return true;
	}

	//public
	bool BitSet::check(IndexType index) const
	{
		if (index < this->getBitCount())
		{
			IndexType packIndex, bitIndex;
			this->getIndicies(index, packIndex, bitIndex);

			PackType v = (PackType)1 << bitIndex;
			return (this->packs[packIndex] & v) != 0;
		}
		else
		{
			return false;
		}
	}

	//public
	bool BitSet::checkUnsafe(IndexType index) const
	{
		IndexType packIndex, bitIndex;
		this->getIndicies(index, packIndex, bitIndex);

		PackType v = (PackType)1 << bitIndex;
		return (this->packs[packIndex] & v) != 0;
	}
	
	//public
	void BitSet::set(IndexType index)
	{
		this->ensurePacksForIndex(index);

		IndexType packIndex, bitIndex;
		this->getIndicies(index, packIndex, bitIndex);
			
		PackType v = (PackType)1 << bitIndex;
		this->packs[packIndex] |= v;
	}
	
	//public
	void BitSet::clear(IndexType index)
	{
		this->ensurePacksForIndex(index);

		IndexType packIndex, bitIndex;
		this->getIndicies(index, packIndex, bitIndex);
			
		PackType v = ~((PackType)1 << bitIndex);
		this->packs[packIndex] &= v;
	}

	//public
	void BitSet::flip(IndexType index)
	{
		if (index < this->getBitCount())
		{
			IndexType packIndex, bitIndex;
			this->getIndicies(index, packIndex, bitIndex);

			PackType v = (PackType)1 << bitIndex;

			// if set
			if ((this->packs[packIndex] & v) != 0)
				// clear
				this->packs[packIndex] &= (~v);
			else
				// otherwise, set
				this->packs[packIndex] |= v;
		}
	}
	
	//public
	void BitSet::setAll(void)
	{
		if (this->packs)
			memset(this->packs, 1, this->packCount * sizeof(PackType));
	}
	
	//public
	void BitSet::clearAll(void)
	{
		if (this->packs)
			memset(this->packs, 0, this->packCount * sizeof(PackType));
	}
	
	//public
	BitSet::IndexType BitSet::getBitCount(void) const
	{
		return this->packCount * sizeof(PackType) * CHAR_BIT;
	}

	//protected
	void BitSet::getIndicies(IndexType index, IndexType &packIndex, IndexType &bitIndex) const
	{
		const SizeType bitsPerPack = sizeof(PackType) * CHAR_BIT;
		
		//assumed that bitsPerPack is a power of two
		packIndex = index / bitsPerPack;
		bitIndex  = index & (bitsPerPack - 1); //essentially (index % bitsPerPack)
	}

	//protected
	void BitSet::ensurePacksForIndex(IndexType index)
	{
		SizeType byteCount = this->packCount * sizeof(PackType);
		SizeType bitCount  = byteCount * CHAR_BIT;
		if (index >= bitCount)
		{
			SizeType newPackCount = this->packCount + 1;
			PackType *newPacks    = new PackType[newPackCount];

			if (this->packs)
				memcpy(newPacks, this->packs, byteCount);

			memset(newPacks + this->packCount, 0, 1 * sizeof(PackType));

			if (this->packs)
				delete []this->packs;

			this->packs     = newPacks;
			this->packCount = newPackCount;
		}
	}

END_NS_ESPERO
