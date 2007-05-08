/***************************************************************************
 *   Copyright (C) 2007 by                                       *
 *                                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Library General Public License as       *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 ***************************************************************************/
 
#ifndef B_LOCK_VECTOR_H
#define B_LOCK_VECTOR_H

#include <vector>
#include <iterator>

/**
    @brief Locking Vector
    @author Tomasz Huczek & Andrzej Jasiñski <thuczek@gmail.com>
 */

template <typename T, typename IT=std::vector<T>::iterator, 
	typename RIT=std::vector<T>::reverse_iterator>
class bLockVector
{
public:
	typedef IT  iterator;
	typedef RIT reverse_iterator;

public:
	bLockVector();
	virtual ~bLockVector();

	void lock();
	void unlock();
	bool is_locked();

public:
	void push_back( T val );
	void erase( iterator it );
	inline void clear() { list.clear(); }
	inline size_t size() const { return list.size(); }

	inline IT begin() { return list.begin(); }
	inline IT end() { return list.end(); }

	inline RIT rbegin() { return list.rbegin(); }
	inline RIT rend() { return list.rend(); }

public:
	std::vector<T> list;

protected:
	bool islocked;
	std::vector<T> list_pending;
	std::vector<IT> to_remove;
};


template <typename T, typename IT, typename RIT>
bLockVector<T, IT, RIT>::bLockVector() : islocked(false)
{
}

template <typename T, typename IT, typename RIT>
bLockVector<T, IT, RIT>::~bLockVector()
{
}

template <typename T, typename IT, typename RIT>
void bLockVector<T, IT, RIT>::push_back( T val )
{
	if( !islocked ) {
		list.push_back( val );
	} else {
		list_pending.push_back( val );
	}
}

template <typename T, typename IT, typename RIT>
void bLockVector<T, IT, RIT>::erase( IT it )
{
	if( !islocked ) {
		list.erase( it );
	} else {
		to_remove.push_back( it );
	}
}

template <typename T, typename IT, typename RIT>
void bLockVector<T, IT, RIT>::lock()
{
	islocked = true;
}

template <typename T, typename IT, typename RIT>
void bLockVector<T, IT, RIT>::unlock()
{
	islocked = false;

	size_t psize = list_pending.size();
	size_t rsize = to_remove.size();

	for ( size_t i=0; i<rsize; ++i ) {
		list.erase( to_remove[i] );
	}

	for ( size_t i=0; i<psize; ++i ) {
		list.push_back( list_pending[i] );
	}

	list_pending.clear();
	to_remove.clear();
}

template <typename T, typename IT, typename RIT>
bool bLockVector<T, IT, RIT>::is_locked()
{
	return islocked;
}


#endif // B_LOCK_VECTOR_H
