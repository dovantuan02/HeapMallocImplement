#pragma once
#include <stdexcept>
#include "stdint.h"
#include <bits/stdc++.h>
#include "heap_4.h"

template<class T>
class Vector
{
public:
    /* ----- Constructors ----- */

    // Default constructor
    Vector();

    explicit Vector(int s);

    // Copy constructor
    Vector(const Vector& arg);

	Vector(T* first, T* last);

    // Copy Assignment
    Vector<T>& operator=(const Vector<T>& arg);

    // Destructor
    ~Vector();

    /*----------------------------*/


    /* -------- ITERATORS --------*/

    class iterator;

    iterator begin();

    iterator end();

    /*----------------------------*/

    /* -------- CAPACITY -------- */

    bool empty() const;

    // Returns size of allocated storage capacity
    size_t capacity() const;

    // Requests a change in capacity
    void reserve(int newmalloc);

    // Changes the Vector's size.
    void resize(int newsize, T val = T());

    // Returns the size of the Vector (number of elements). 
    size_t size() const;

    /*----------------------------*/


    /* -------- MODIFIERS --------*/

    // Removes all elements from the Vector
    void clear();

    // Inserts element at the back
    void push_back(const T& d);

    // Removes the last element from the Vector
    void pop_back();

	void erase(int position);

	void erase(iterator first, iterator last);

	void erase(size_t first, size_t last);

	void shrink_to_fit() ;


	/*----------------------------*/

    /* ----- ELEMENT ACCESS ----- */

    T& at(int n);

    const T& at(int n) const;

    T& operator[](int i);

    const T& operator[](int i) const;

    T& front();

    const T& front() const;

    T& back();

    const T& back() const;

    T* data();

    const T* data() const;

    /*----------------------------*/

private:
    size_t  _size;      // Number of elements in Vector
    T*      _elements;  // Pointer to first element of Vector
    size_t  _space;     // Total space used by Vector including
                        // elements and free space.
};

template<class T> 
class Vector<T>::iterator
{
public:
    iterator(T* p)
        :_curr(p)
    {}

    iterator& operator++()
    {
        _curr++;
        return *this;
    }

    iterator& operator--()
    {
        _curr--;
        return *this;
    }

    T& operator*()
    {
        return *_curr;
    }

    bool operator==(const iterator& b) const
    {
        return *_curr == *b._curr;
    }

    bool operator!=(const iterator& b) const
    {
        return *_curr != *b._curr;
    }

	iterator operator+(size_t n) const {
		return iterator(_curr + n);
    }

	ptrdiff_t operator-(const iterator& other) const {
		return _curr - other._curr;
	}


private:
    T* _curr;
};

// Constructors/Destructor
template<class T>
Vector<T>::Vector()
    :_size(0), _elements(nullptr), _space(0)
{}

template<class T>
inline Vector<T>::Vector(int s)
    :_size(s), _elements((T*)pvSafeMalloc(s * sizeof(T))), _space(s)
{
    for (int index = 0; index < _size; ++index)
        new (&_elements[index]) T(); // Placement new to construct T objects
}

template<class T>
inline Vector<T>::Vector(const Vector & arg)
    :_size(arg._size), _elements((T*)pvSafeMalloc(arg._size * sizeof(T))), _space(arg._size)
{
    for (int index = 0; index < arg._size; ++index)
        _elements[index] = arg._elements[index];
}

template<class T>
Vector<T>::Vector(T* first, T* last) {
    _size = last - first;
    _space = _size;

    _elements = (T*)pvSafeMalloc(_size * sizeof(T));

    if (_elements == nullptr) {
        throw std::bad_alloc();
    }

    for (size_t i = 0; i < _size; ++i) {
        _elements[i] = first[i];
    }
}

template<class T>
inline Vector<T>& Vector<T>::operator=(const Vector<T>& a)
{
    if (this == &a) return *this;    // Self-assignment check

    // If the current Vector has enough space, reuse it
    if (a._size <= _space)
    {
        for (int index = 0; index < a._size; ++index)
        {
            _elements[index] = a._elements[index];
        }
        _size = a._size;
        return *this;
    }

    // Allocate new memory and copy elements
    T* p = (T*)pvSafeMalloc(a._size * sizeof(T));
    for (int index = 0; index < a._size; ++index)
        p[index] = a._elements[index];

    vPortFree(_elements);
    _elements = p;
    _size = a._size;
    _space = a._size;
    return *this;
}

template<class T>
Vector<T>::~Vector()
{
    vPortFree(_elements);
}

// Iterators
template<class T>
inline typename Vector<T>::iterator Vector<T>::begin()
{    
    return Vector<T>::iterator(&_elements[0]);
}

template<class T>
inline typename Vector<T>::iterator Vector<T>::end()
{
    return Vector<T>::iterator(&_elements[_size]);
}

// Capacity
template<class T>
inline bool Vector<T>::empty() const
{
    return (_size == 0);
}

template<class T>
inline size_t Vector<T>::capacity() const
{
    return _space;
}

template<class T>
inline void Vector<T>::reserve(int newalloc)
{
    if (newalloc <= _space) return;

    T* p = (T*)pvSafeMalloc(newalloc * sizeof(T));

    for (int i = 0; i < _size; ++i)
        p[i] = _elements[i];

    vPortFree(_elements);
    _elements = p;
    _space = newalloc;
}

template<class T>
inline void Vector<T>::resize(int newsize, T val)
{
    reserve(newsize);

    for (int index = _size; index < newsize; ++index)
        _elements[index] = val;

    _size = newsize;
}

template<class T>
inline size_t Vector<T>::size() const
{
    return _size;
}



// Modifiers
template<class T>
inline void Vector<T>::push_back(const T& d)
{
    if (_space == 0)
        reserve(8);
    else if (_size == _space)
        reserve(2 * _space);

    _elements[_size] = d;

    ++_size;
}

template<class T>
inline void Vector<T>::pop_back() {
	--_size;
}

template<class T>
inline void Vector<T>::clear() {
	_size = 0;
}

template<class T>
void Vector<T>::erase(int position) {
    if (position < 0 || position >= _size) {
        throw std::runtime_error("Index out of range");
    }

    for (int i = position; i < _size - 1; ++i) {
        _elements[i] = _elements[i + 1];
    }

    --_size;
}

template<class T>
void Vector<T>::erase(iterator first, iterator last) {
    size_t num_to_erase = last - first;
	if (num_to_erase <= 0) return;

	printf("Num Erase: %d\n", num_to_erase);
    T* new_end = &(*first);
    T* move_start = &(*last);

    for (T* it = move_start; it != &_elements[_size]; ++it) {
        *new_end = *it;
        ++new_end;
    }

    _size -= num_to_erase;
}

template<class T>
void Vector<T>::erase(size_t first, size_t last) {
    if (first == last) return;

    ptrdiff_t num_to_erase = last - first;

    T* new_end = 	&_elements[first];
    T* move_start = &_elements[last];

    for (T* it = move_start; it != &_elements[_size]; ++it) {
        *new_end = *it;
        ++new_end;
    }

    _size -= static_cast<size_t> (num_to_erase);
}

template<class T>
inline void Vector<T>::shrink_to_fit() {
	if (_space > _size) {
		T *new_elements = (T *)pvSafeMalloc(_size * sizeof(T));
		for (size_t i = 0; i < _size; ++i) {
			new_elements[i] = _elements[i];
		}
		vPortFree(_elements);
		_elements = new_elements;
		_space	  = _size;
	}
}

// Accessors
template<class T>
inline T & Vector<T>::at(int n)
{
    if (n < 0 || _size <= n) throw std::runtime_error("Index out of range");
    return _elements[n];
}

template<class T>
inline const T & Vector<T>::at(int n) const
{
    if (n < 0 || _size <= n) throw std::runtime_error("Index out of range");
    return _elements[n];
}

template<class T>
inline T & Vector<T>::operator[](int i)
{
    return _elements[i];
}

template<class T>
inline const T & Vector<T>::operator[](int i) const
{
    return _elements[i];
}

template<class T>
inline T& Vector<T>::front()
{
    return _elements[0];
}

template<class T>
inline const T& Vector<T>::front() const
{
    return _elements[0];
}

template<class T>
inline T& Vector<T>::back()
{
    return _elements[_size - 1];
}

template<class T>
inline const T& Vector<T>::back() const
{
    return _elements[_size - 1];
}

template<class T>
inline T* Vector<T>::data()
{
    return _elements;
}

template<class T>
inline const T* Vector<T>::data() const
{
    return _elements;
}

