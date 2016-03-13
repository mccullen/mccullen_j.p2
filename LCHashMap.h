/**
Name: Jeff McCullen and Emma Elliott
Date: March 1, 2016
Description: Prototype and implementation for LCHashMap. This map 
uses a hash table to store key-value pairs. It is implemented using
the chaining method for hashing. The Key type is the 
key, which must be unique. The Value is the the value that the
Key maps to. The HashFn type is a functor that returns the
hash code for the Key. The Equator type is a functor used
to determine if two keys are equivalent.
*/
#ifndef LC_HASH_MAP_H
#define LC_HASH_MAP_H

#include <map>
#include <vector>
#include <list>
#include <math.h>
#include <algorithm>
#include <iostream>

template <typename Key, typename Value, typename HashFn,
	typename Equator>
class LCHashMap
{
public:
	/* constructor */
	LCHashMap();

	/* inserts the key value pair 
	  take in a const reference so you can take in literals like 7.
	*/
	virtual bool insert(const Key& key, const Value& value);

	/* erases key value pair referenced by key */
	virtual bool erase(const Key& key);

	/* lookup the value associated with a key. if the key is not in the
	map, insert it with default value. Should provide l-value access to
	value.*/
	virtual Value& operator[](const Key& key);

	/* returns true if this key maps to a value */
	virtual bool in(const Key& key) const;

	/* returns true if the map is empty */
	virtual bool empty();

	/* number of key value pairs stored */
	virtual int size();

	/* empties the map */
	virtual void clear();

	/* cleans up all memory for storage and calls the destructor for
	the keys and values stored */
	virtual ~LCHashMap();

	virtual int tsize();

private:

	// Variable for the hash table
	std::vector<std::list<std::pair<Key, Value> > > table_;

	// Variable for the size of the table. This stores
	// the number of key-value pairs that have been inserted
	// into the table. 
	size_t size_;

	// Functor to get the hash code for the key.
	HashFn hashFn_;

	// Functor to determine if two keys are equivalent. 
	Equator equal_;

	// Large prime number to determine the inital size
	// of the table.
	static const int LARGE_PRIME = 5;//16908799;

	/**
	rehash
	*/
	virtual void rehash();

	/**
	Compress the hashCode so it will fit in the table_
	*/
	virtual size_t compress(size_t hashCode) const;

	/**
	Return true if the key is in the table_
	*/
	virtual bool contains(const std::list<std::pair<Key,Value> >& bucket,
		const Key& key) const;

	/**
	Get the next prime number larger than the number parameter.

	@param number The number to find the next prime of.
	@return The next prime number after number.
	*/
	virtual size_t nextPrime(int number) const;

	/**
	Determine wheather or not the number parameter is prime.

	@param number The number to determine.
	@return True if the number is prime.
	*/
	virtual bool isPrime(int number) const;
};

template <typename Key, typename Value, typename HashFn,
	typename Equator>
int LCHashMap<Key,Value,HashFn,Equator>::tsize()
{
	return table_.size();
}

/**
rehash
*/
template <typename Key, typename Value, typename HashFn,
	typename Equator>
void LCHashMap<Key, Value, HashFn, Equator>::rehash()
{
	// Create a new table that is a copy of the original.
	std::vector<std::list<std::pair<Key, Value> > > oldTable = table_;

	//std::vector<std::list<std::pair<Key, Value> > > oldTable;
	//std::swap(oldTable, table_);

	// Resize the table to the next prime above the doubled size.
	table_.resize(nextPrime(2 * table_.size()));
	
	// Clear the table so it is not empty and at least twice the size.
	clear();

	// Insert all the entries back into the table. Note that inserting
	// will result in rehashing each one in accordance with the new
	// table size.

	// For every bucket in the old table
	for (size_t i = 0; i < oldTable.size(); ++i)
	{
		typename std::list<std::pair<Key,Value> >& bucket = oldTable[i];
		// For every link in the bucket
		for (typename std::list<std::pair<Key,Value> >::
			const_iterator iter = bucket.begin();
			iter != bucket.end(); ++iter)
		{
			// insert it into the table.
			insert((*iter).first, (*iter).second);
		}
	}
}

/**
Compress the hashCode so it will fit in the table_
*/
template <typename Key, typename Value, typename HashFn,
	typename Equator>
size_t LCHashMap<Key, Value, HashFn, Equator>::compress(
	size_t hashCode) const
{
	return hashCode % table_.size();
}

/**
Return true if the key is in the bucket.
*/
template <typename Key, typename Value, typename HashFn,
	typename Equator>
bool LCHashMap<Key,Value,HashFn,Equator>::contains(
	const std::list<std::pair<Key,Value> >& bucket,
	const Key& key) const
{
	bool retVal = false;
	typename std::list<std::pair<Key,Value> >::const_iterator iter = 
		bucket.begin();

	// While not at the end of the bucket AND
	// you have not yet found the key in the bucket.
	// [jrm] flag.
	while (iter != bucket.end() && !retVal)// && !equal_((*iter).first, key))
	{
		// if the key is in the bucket, return true
		if (equal_((*iter).first,key))
		{
			retVal = true;
		}
		++iter;
	}
	return retVal;//iter != bucket.end();
}

/* constructor [jrm] can you resize in a more efficient way? */
template <typename Key, typename Value, typename HashFn,
	typename Equator>
LCHashMap<Key, Value, HashFn, Equator>::LCHashMap() : size_(0)
{
	table_.resize(LARGE_PRIME);
}

/* inserts the key value pair 
  take in a const reference so you can take in literals like 7.
*/
template <typename Key, typename Value, typename HashFn,
	typename Equator>
bool LCHashMap<Key, Value, HashFn, Equator>::insert(
	const Key& key, const Value& value)
{
	bool retVal = false;

	// Compute the key's hash code
	size_t hashCode = hashFn_(key);

	// Compress it to determine the bucket
	size_t index = compress(hashCode);

	typename std::list<std::pair<Key,Value> >& bucket = table_[index];
	// If not in bucket
	if (!contains(bucket, key))
	{
		//insert the entry into the bucket's chain.
		bucket.push_back(std::pair<Key,Value>(key,value));
		retVal = true;
		++size_;

		// If the size_ is greater than the table's size.
		if (size_ > table_.size())
		{
			// rehash
			rehash();
		}
	}
	return retVal;
}

/* erases key value pair referenced by key */
template <typename Key, typename Value, typename HashFn,
	typename Equator>
bool LCHashMap<Key, Value, HashFn, Equator>::erase(const Key& key)
{
	// Hash the key
	size_t hashCode = hashFn_(key);

	// Compress it to determine the bucket
	size_t index = compress(hashCode);

	std::list<std::pair<Key,Value> >& bucket = table_[index];
	typename std::list<std::pair<Key,Value> >::iterator iter = 
		bucket.begin();

	// [jrm] this is probably wrong...should probably put the if
	// statement in the body of this loop.
	// While 
	while (iter != bucket.end() && !equal_((*iter).first, key))
	{
		++iter;
	}


	// Search chain for entry with given key.
	// If found, erase
	if (equal_((*iter).first, key))
	{
		bucket.erase(iter);
		--size_;
	}
	return iter != bucket.end();

}

/* lookup the value associated with a key. if the key is not in the
map, insert it with default value. Should provide l-value access to
value.*/
template <typename Key, typename Value, typename HashFn,
	typename Equator>
Value& LCHashMap<Key, Value, HashFn, Equator>::operator[](const Key& key)
{
	// Hash the key
	size_t hashCode = hashFn_(key);

	// Compress it
	size_t index = compress(hashCode);

	// Get bucket.
	std::list<std::pair<Key, Value> >& bucket = table_[index];
	typename std::list<std::pair<Key, Value> >::iterator iter = 
		bucket.begin();

	// [jrm] the if statement should probably be in the body of this
	// loop.
	while (iter != bucket.end() && !equal_((*iter).first, key))
	{
		++iter;
	}
	// If the key was not found, insert it into the table
	if (iter == bucket.end())
	{
		bucket.push_back(std::pair<Key,Value>(key, Value()));
		iter = --bucket.end();
		++size_;
	}
	return (*iter).second;
}

/* returns true if this key maps to a value */
template <typename Key, typename Value, typename HashFn,
	typename Equator>
bool LCHashMap<Key, Value, HashFn, Equator>::in(const Key& key) const
{
	bool retVal = false;

	// Hash the key
	size_t hashCode = hashFn_(key);

	// Compress it
	size_t index = compress(hashCode);

	// Search chain for entry with given key.
	// If found, return true
	if (contains(table_[index], key))
	{
		retVal = true;
	}
	return retVal;
}

/* returns true if the map is empty */
template <typename Key, typename Value, typename HashFn,
	typename Equator>
bool LCHashMap<Key, Value, HashFn, Equator>::empty()
{
	return size_ == 0;
}

/* number of key value pairs stored */
template <typename Key, typename Value, typename HashFn,
	typename Equator>
int LCHashMap<Key, Value, HashFn, Equator>::size()
{
	return size_;
}

/* empties the map */
template <typename Key, typename Value, typename HashFn,
	typename Equator>
void LCHashMap<Key, Value, HashFn, Equator>::clear()
{
	// For every chain in the table, clear it.
	for (typename std::vector<std::list<std::pair<Key,Value> > >::
		iterator iter = table_.begin();
		iter != table_.end(); ++iter)
	{
		(*iter).clear();
	}
	size_ = 0;
}

/**
Get the next prime number larger than the number parameter.

@param number The number to find the next prime of.
@return The next prime number after number.
*/
template <typename Key, typename Value, typename HashFn,
	typename Equator>
size_t LCHashMap<Key, Value, HashFn, Equator>::nextPrime(int number) const
{
	size_t nextPrimeNum;
	// If the number is negative, 0, or 1, the next prime is 2.
	if (number <= 1)
	{
		nextPrimeNum = 2;
	}
	// Else, keep incrementing number until you find a number that
	// is prime.
	else
	{
		nextPrimeNum = number + 1;
		while (!isPrime(nextPrimeNum))
		{
			++nextPrimeNum;
		}
	}
	return nextPrimeNum;
}

/**
Determine wheather or not the number parameter is prime.

@param number The number to determine.
@return True if the number is prime.
*/
template <typename Key, typename Value, typename HashFn,
	typename Equator>
bool LCHashMap<Key, Value, HashFn, Equator>::isPrime(int number) const
{
	bool numberIsPrime = true;

	// If number is 1, 0, or negative it is not prime.
	if (number == 1 || number <= 0)
	{
		numberIsPrime = false;
	}

	// Check to see if any number can divide number other than 1
	// and itself.

	// Note: A number can divide it if (number % someNumber == 0).

	int i = 2;
	while (i <= sqrt(number) && numberIsPrime)
	{
		if (number% i == 0)
		{
			numberIsPrime = false;
		}
		++i;
	}

	return numberIsPrime;
}

/* cleans up all memory for storage and calls the destructor for the
keys and values stored */
template <typename Key, typename Value, typename HashFn,
	typename Equator>
LCHashMap<Key, Value, HashFn, Equator>::~LCHashMap()
{
}

#endif // LC_HASH_MAP_H
