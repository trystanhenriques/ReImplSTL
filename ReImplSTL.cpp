// ReImplSTL.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "myVector.hpp"
#include <vector>

template <typename T>
void printVec(const ReImplSTL::vector<T>& vec)
{
	for (int i{}; i < vec.size(); i++) {
		std::cout << vec[i] << " ";
	}
	std::cout << '\n';
}


int main()
{
	ReImplSTL::vector<int> vec1 (10);
	ReImplSTL::vector<int> vec2 {2,3,4,5,6};
	ReImplSTL::vector<int> vec3 {vec2};
	ReImplSTL::vector<int> vec4 = vec3;
	ReImplSTL::vector vec5 = {2,3,4,2,1,3,4};
	
	std::cout << "Capacity: " << vec2.capacity() << '\n';
	printVec(vec2);

	vec2.reserve(400);
	

	std::cout << "Capacity: " << vec2.capacity() << '\n';
	printVec(vec2);

	vec2.shrink_to_fit();

		
	std::cout << "Capacity: " << vec2.capacity() << '\n';
	printVec(vec2);

	
}

