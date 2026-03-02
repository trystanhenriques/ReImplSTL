// ReImplSTL.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "myVector.hpp"
#include <vector>

template <typename T>
void printVec(const myVector<T>& vec)
{
	for (int i{}; i < vec.size(); i++) {
		std::cout << vec[i] << " ";
	}
	std::cout << '\n';
}


int main()
{
	myVector<int> vec1 (10);
	myVector<int> vec2 {2,3,4,5,6};
	myVector<int> vec3 {vec2};
	myVector<int> vec4 = vec3;
	myVector vec5 = {2,3,4,2,1,3,4};
	
	std::cout << "Capacity: " << vec2.capacity() << '\n';
	printVec(vec2);

	vec2.reserve(400);
	

	std::cout << "Capacity: " << vec2.capacity() << '\n';
	printVec(vec2);

	vec2.shrink_to_fit();

		
	std::cout << "Capacity: " << vec2.capacity() << '\n';
	printVec(vec2);

	
}

