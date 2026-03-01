// ReImplSTL.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "myVector.hpp"

int main()
{
	myVector<int> vec1 (10);
	myVector<int> vec2 {2,3,4,5,6};
	myVector<int> vec3 {vec2};
	myVector<int> vec4 = vec3;
	myVector<int> vec5 = {2,3,4,2,1,3,4};
	
}

