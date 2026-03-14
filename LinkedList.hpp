#include <cstddef>
#include <iostream>

namespace ReImplSTL
{

template <typename T>
class linkedlist {
public:
	using value_type = T;
	using size_type = std::size_t;
	using difference_type = std::ptrdiff_t;
	using reference = value_type&;
	using const_reference = const value_type&;
	using pointer = T*;
	using const_pointer = const T*;
	
	// Default Constructor
	linkedlist() 
	: m_head {nullptr}, m_tail {nullptr}, m_size {0}
	{
	}

	// Fill Constructor
	linkedlist(int size, value_type value) {
		
		// Temporary node to keep track of the pointer to the previous node
		Node* lastNode { nullptr };
		
		for (int i{}; i < size; i++) {
			
			// Initialize new Node with the value
			Node* newNode { new Node{ value }};

			// Set the previous node
			newNode->prev = lastNode;
			
			// Case: This is the first element, set the head to our newNode
			if (m_head == nullptr) {
				m_head = newNode;
			}
			
			// There is only one Make sure that there is more than one node
			if (m_head != newNode) {
				// Set the next pointer for the previous node
				newNode->prev->next = newNode;
			}
		
			// This is the most recent node! Set the tail to our new Node
			m_tail = newNode;
			
			// Increment the size
			++m_size;
			
			// Set our last node for next iteration
			lastNode = newNode;
		}
	}

	// Function to print out a linkedlist just for testing
	void print() const {
		
		std::cout << "{ ";
		// Start at head and loop until last node
		for (Node* tnd{ m_head }; tnd != nullptr; tnd = tnd->next) {
			
			// print the data at tnd
			std::cout << tnd->data << " ";
		}

		std::cout << "}\n";
	}

private:
	//  Inner Node Class
	struct Node {
		value_type data {};
		Node* next {};	// pointer to the next node
		Node* prev {}; // pointer to the previous node
	};

	Node* m_head {};
	Node* m_tail {};
	size_type m_size {};
};

} // namespace ReImplSTL