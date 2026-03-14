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
	ReImplSTL::linkedlist<int> list {5, 666};
	list.print();
		
	ReImplSTL::linkedlist<int> list2 = std::move(list);
	list2.print();

	list.print();

}

