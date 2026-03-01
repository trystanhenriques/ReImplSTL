#pragma once

#include <cstddef>
#include <memory>
#include <initializer_list>
#include <algorithm>

template<typename T>
class myVector
{
public:
	using value_type = T;
	using size_type = std::size_t;
	using difference_type = std::ptrdiff_t;
	using reference = value_type&;
	using const_reference = const value_type&;

	// Constructors
	myVector()
	: m_data{ new value_type[10] {} }, m_length{0}, m_capacity{10}	// default size of 10
	{	
	}
	
	// Constructor with initial size
	myVector(int size)
	: m_data{ new value_type[static_cast<std::size_t>(size)] {} },
	  m_length{0}, 
	  m_capacity{static_cast<size_type>(size)}
	{
	}
	
	// Constructor with intitializer list
	myVector(const std::initializer_list<value_type>& list)
	: myVector( static_cast<int>(list.size()*2) )	// delegate to other constructor
	{
		std::copy(list.begin(), list.end(), m_data); // Copy the list into the array
		m_length = static_cast<size_type>( list.size() ); // set the length
	}

	// Copy Constructor for deep copying
	myVector(const myVector& vecCopy)
	{
		m_data = new value_type[static_cast<std::size_t>(vecCopy.m_capacity)];
		
		// Perform deep copy of the data
		std::copy_n(vecCopy.m_data, static_cast<int>(vecCopy.m_length), m_data);
		
		m_length = vecCopy.m_length;
		m_capacity = vecCopy.m_capacity;
	}

	~myVector()
	{
		delete[] m_data;	// deallocate memory
	}

	// Overload the assignment operator for deep copying
	myVector& operator=(const myVector& vecCopy)
	{
		// check for self assignment
		if (this == &vecCopy)
			return *this;

		// deallocate old memory
		delete[] m_data;

		// allocate new memory 
		m_data = new value_type[ static_cast<std::size_t>(vecCopy.m_capacity) ] {};
		
		// deep copy data
		std::copy_n(vecCopy.m_data, static_cast<int>(vecCopy.m_length), m_data);

		m_length = vecCopy.m_length;
		m_capacity = vecCopy.m_length;
		
		// for chaining
		return *this;
		
	}

	// Overload the assignment operator for deep copying initializer lists
	myVector& operator=(const std::initializer_list<value_type>& list)
	{	
		std::size_t capacity{ list.size() * 2 };

		// deallocate old memory
		delete[] m_data;
		
		// allocate new memory based on the size of the list
		m_data = new value_type[capacity] {};

		// deep copy data
		std::copy_n(list.begin(), static_cast<int>(list.size()), m_data);

		m_length = static_cast<size_type>(list.size());
		m_capacity =  capacity;

		// for chaining
		return *this;
	}



private:
	value_type* m_data{};
	size_type m_length{};
	size_type m_capacity{};

};