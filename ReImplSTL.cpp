// ReImplSTL.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "myVector.hpp"
#include <vector>

template <typename T>
void printVec(const ReImplSTL::vector<T>& vec)
{
	std::cout << "{ ";
	for (int i{}; i < vec.size(); i++) {
		std::cout << vec[i] << " ";
	} 
	std::cout << "}\n";
}

template <typename T>
void iteratorTestPrintVec(const ReImplSTL::vector<T>& vec)
{
	std::cout << "{ ";
	auto it = vec.cbegin();
	for (;it != vec.cend(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << "}\n";
}

int main()
{
	ReImplSTL::vector<int> vec1 (10);
	ReImplSTL::vector<int> vec2 {2,3,4,5,6};
	ReImplSTL::vector<int> vec3 {vec2};
	ReImplSTL::vector<int> vec4 = vec3;
	ReImplSTL::vector vec5 = {2,3,4,2,1,3,4};
	
	vec5.push_back(5);
	printVec(vec5);

	iteratorTestPrintVec(vec5);

	std::cout << vec5.front();
	std::cout << vec5.back();
	
}

