#pragma once

#include <cstddef>
#include <memory>
#include <initializer_list>
#include <algorithm>
#include <cassert>
#include <stdexcept>
#include <iterator>

namespace ReImplSTL
{

template<typename T>
class vector
{
public:
	using value_type = T;
	using size_type = std::size_t;
	using difference_type = std::ptrdiff_t;
	using reference = value_type&;
	using const_reference = const value_type&;
	using pointer = T*;
	using const_pointer = const T*;
	using iterator = T*;
	using const_iterator = const T*;
	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;

	// Constructors
	vector()
	: m_data{ new value_type[10] {} }, m_length{0}, m_capacity{10}	// default size of 10
	{	
	}
	
	// Constructor with initial size
	vector(int size)
	: m_data{ new value_type[static_cast<std::size_t>(size)] {} },
	  m_length{0}, 
	  m_capacity{static_cast<size_type>(size)}
	{
	}
	
	// Constructor with intitializer list
	vector(std::initializer_list<value_type> list)
	: vector( static_cast<int>(list.size()*2) )	// delegate to other constructor
	{
		std::copy(list.begin(), list.end(), m_data); // Copy the list into the array
		m_length = static_cast<size_type>( list.size() ); // set the length
	}

	// Copy Constructor for deep copying
	vector(const vector& vecCopy)
	{
		m_data = new value_type[static_cast<std::size_t>(vecCopy.m_capacity)];
		
		// Perform deep copy of the data
		std::copy_n(vecCopy.m_data, static_cast<int>(vecCopy.m_length), m_data);
		
		m_length = vecCopy.m_length;
		m_capacity = vecCopy.m_capacity;
	}
	
	// Move Constructor
	vector(vector&& vecMove) 
	{
		m_data = vecMove.m_data;	// point to the data

		// set size and capacity
		m_length =  vecMove.m_length;
		m_capacity = vecMove.m_capacity;

		// zero out the other vector
		vecMove.m_data = nullptr;
		vecMove.m_capacity = 0;
		vecMove.m_length = 0;
	}

	~vector()
	{
		// Free memory
		deallocate();
	}

	// Overload the assignment operator for deep copying
	vector& operator=(const vector& vecCopy)
	{
		// check for self assignment
		if (this == &vecCopy)
			return *this;

		// Check if the length of the copy is greater than the capacity
		if (vecCopy.m_length > m_capacity) {
			
			// deallocate old memory
			deallocate();

			// allocate new memory with the same capacity of the copy
			m_data = new value_type[static_cast<std::size_t>(vecCopy.m_capacity)]{};
		}

		// deep copy data
		std::copy_n(vecCopy.m_data, static_cast<int>(vecCopy.m_length), m_data);

		m_length = vecCopy.m_length;
		m_capacity = vecCopy.m_capacity;
		
		// for chaining
		return *this;
		
	}

	// Overload the assignment operator for deep copying initializer lists
	vector& operator=(std::initializer_list<value_type> list)
	{	
		std::size_t capacity{ list.size() * 2 };

		// deallocate old memory
		deallocate();
		
		// allocate new memory based on the size of the list
		m_data = new value_type[capacity*2] {};

		// deep copy data
		std::copy_n(list.begin(), static_cast<int>(list.size()), m_data);

		m_length = static_cast<size_type>(list.size());
		m_capacity = capacity;

		// for chaining
		return *this;
	}

	// Overload the assignment operator for moving r values
	vector& operator=(vector&& rvec)
	{	
		// check for self assignment
		if (this == &rvec)
			return *this;
		
		// Move the resources
		m_data = rvec.m_data;
		m_capacity = rvec.m_capacity;
		m_length = rvec.m_length;

		// Set rvec to an invalid state
		rvec.m_data = nullptr;
		rvec.m_capacity = 0;
		rvec.m_length = 0;

		// for chaining
		return *this;
	}

	//  ======================
	//  Element access
	//  ======================
	
	// non-const overload of operator[] for element access
	reference operator[](int index)
	{
		// make sure the index is in bounds
		assert( (index >= 0 && index < m_length) && "Index Out of Bounds" );
		
		// Return Element at that index
		return m_data[static_cast<std::size_t>(index)];

	}
	
	// const overload of operator[] for element access
	const_reference operator[](int index) const
	{
		// make sure the index is in bounds
		assert((index >= 0 && index < m_length) && "Index Out of Bounds");

		// Return Element at that index
		return m_data[static_cast<std::size_t>(index)];
	}

	reference at(int index)
	{
		// Out of Bounds! Throw Exception
		if (index < 0 || index >= m_length) {
			throw std::out_of_range("Index Out of Bounds");
		}

		// Return Element at that index
		return m_data[static_cast<std::size_t>(index)];
	}

	const_reference at(int index) const
	{
		// Out of Bounds! Throw Exception
		if (index < 0 || index >= m_length) {
			throw std::out_of_range("Index Out of Bounds");
		}

		// Return Element at that index
		return m_data[static_cast<std::size_t>(index)];
	}
	
	// return reference to the front element
	reference front()
	{
		return *m_data;
	}

	// return const reference to the front element
	const_reference front() const
	{
		return *m_data;
	}

	// return reference to the last element
	reference back()
	{
		// Vector is empty, UNDEFINED BEHAVIOR: Just return reference to the first element	
		if (empty()) {
			return *m_data;
		}
		
		// return reference to last element
		return m_data[m_length-1];
	}

	// return const reference to the last element
	const_reference back() const
	{
		// Vector is empty, UNDEFINED BEHAVIOR: Just return reference to the first element	
		if (empty()) {
			return *m_data;
		}

		// retrun reference to last element
		return m_data[m_length - 1];
	}

	// return reference to data
	pointer data()
	{
		return m_data;
	}

	const_pointer data() const
	{
		return m_data;
	}
	

	//  ======================
	//  Iterator
	//  ======================

	iterator begin() {return m_data;}
	const_iterator begin() const { return m_data; }
	const_iterator cbegin() const {return m_data;}
	
	iterator end() {return m_data + (m_length);}							// return a pointer to one past last element
	const_iterator end() const { return m_data + (m_length); }
	const_iterator cend() const {return m_data + (m_length);}	

	// Reverse iterators
	reverse_iterator rbegin() { return m_data + (m_length-1); }				// return a pointer to the last element
	const_reverse_iterator rbegin() const { return m_data + (m_length - 1); }
	const_reverse_iterator crbegin() const { return m_data + (m_length-1); }

	reverse_iterator rend() {return m_data-1;}							// return a pointer to (m_data - 1)
	const_reverse_iterator rend() const { return m_data - 1; }
	const_reverse_iterator crend() const { return m_data - 1; }
	


	//  ======================
	//  Capacity
	//  ======================

	int size() const
	{
		return (static_cast<int>(m_length));
	}
	
	bool empty() const
	{
		return (m_length == 0);
	}

	int capacity() const
	{
		return (static_cast<int>(m_capacity));
	}

	void reserve(int newCapacity)
	{
		// Check whether current capacity is greater than the new capacity. If so, return
		if (m_capacity >= newCapacity)
			return;
		
		// allocate new memory
		value_type* tempData { new value_type[static_cast<std::size_t>(newCapacity)] {} };

		// move the old data into the new data
		for (size_type i{}; i < m_length; i++) {
			tempData[i] = std::move(m_data[i]);
		}
		
		// deallocate old data
		deallocate();
		
		// point to the new Data
		m_data = tempData;
		
		// set new capacity
		m_capacity = newCapacity;

	}
		
	void shrink_to_fit()
	{
		// Allocate new memory the size of our length
		value_type* tempData { new value_type[static_cast<std::size_t>(m_length)] };
		
		// move the old data into the new data
		for (size_type i{}; i < m_length; i++) {
			tempData[i] = std::move(m_data[i]);
		}
		
		// deallocate old data
		deallocate();

		// point to the new Data
		m_data = tempData;
		
		// set new capacity
		m_capacity = m_length;

	}



	//  ======================
	//  Modifiers
	//  ======================
	
	void clear()
	{
		// Destroy all the elements inside the vector
		for (size_type i{}; i < m_length; i++) {
			m_data[i].~value_type();
		}
		
		// Set the size of vec to 0
		m_length = 0;
	}
	

	void push_back(const_reference element)
	{
		// check the capacity
		if (m_length == m_capacity) {

			// Allocate more memory with double the size
			reallocate();
		}
	

		// Copy element to last index
		m_data[m_length] = element;
		
		// Increment the length to indicate our new element was added
		m_length++;
		
	}

	void push_back(value_type&& r_elem) {
		
		// check the capacity
		if (m_length == m_capacity) {

			// Allocate more memory with double the size
			reallocate();
		}

		// move the element into last index
		m_data[m_length] = std::move(r_elem);

		// Increment the length to indicate our new element was added
		m_length++;
	}
	


private:
	value_type* m_data{};
	size_type m_length{};
	size_type m_capacity{};
	
	// ======================
	// Helpers
	// ======================
	
	// Frees the memory of the vector and prevents memory leaks
	void deallocate()
	{
		// Call destructors on all the elements in the container from [0, capacity)
		for (size_type i{}; i < m_capacity; i++) {
			m_data[i].~value_type();
		}

		// Deallocate vectors memory
		delete[] m_data;
	}

	// Case where the vector runs out of memory and we need to allocate more memory
	void reallocate()
	{
		// New capacity
		size_type newCapacity {m_capacity * 2};
		
		// allocate double the memory of our past capacity
		value_type* tempData { new value_type[static_cast<std::size_t>(newCapacity)] {} };

		// Move / Copy the data over to our newly allocated memory
		for (size_type i{}; i < m_length; i++) {
			tempData[i] = std::move(m_data[i]);
		}
		
		// deallocate old data
		deallocate();

		// Point to our new data
		m_data = tempData;
		
		// Set new capacity
		m_capacity = newCapacity;
	}
};

} // namespace ReImplSTL