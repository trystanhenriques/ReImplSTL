// ReImplSTL.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <memory>
#include <iterator>
#include "myVector.hpp"
#include "LinkedList.hpp"


template<typename T>
void printList(const ReImplSTL::linkedlist<T>& list) {
	
	std::cout << "{ ";
	for (auto it{ list.begin() }; it != list.end(); ++it) {
		std::cout << *it << ' ';
	}
	
	std::cout << "}\n";
}


int main()
{
	ReImplSTL::linkedlist<int> list {4, 2, 3, 4, 1, 1};
	printList(list);

	auto it { list.begin() };
	//it = std::next(it, 3);

	list.insert(it, 444);
	printList(list);

}

