// ReImplSTL.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <memory>
#include "myVector.hpp"
#include "LinkedList.hpp"



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
	ReImplSTL::linkedlist<int> list {4, 2, 3, 4, 1, 1};
	list.print();

	list = {1, 5, 2, 1, 2, 5};
	list.print();

}

