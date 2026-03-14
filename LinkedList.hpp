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
			Node* newNode { new Node{ value, nullptr, nullptr }};

			// Set the previous node
			newNode->prev = lastNode;
			
			// Case: This is the first element, set the head to our newNode
			if (m_head == nullptr) {
				m_head = newNode;
			}
			
			// There is only one Make sure that there is more than one node
			if (m_head != newNode) {
				// Set the next pointer for the previous node
				lastNode->next = newNode;
			}
		
			// This is the most recent node! Set the tail to our new Node
			m_tail = newNode;
			
			// Increment the size
			++m_size;
			
			// Set our last node for next iteration
			lastNode = newNode;
		}
	}
	
	// Copy Constructor For Deep Copying
	linkedlist(const linkedlist& listCopy) {
		
		// Temporary pointer to keep track of the previous node
		Node* lastNode{ nullptr };
		
		for (Node* tnd{ listCopy.m_head }; tnd != nullptr; tnd = tnd->next) {
			
			// Create a new node for our original linkedlist with the same data as the copy.
			Node* newNode { new Node{tnd->data, nullptr, nullptr} };
			
			// Case: First Node, point head to newNode
			if (m_head == nullptr) {
				m_head = newNode; 
			}
			
			// make sure there is more than one node
			
			if (m_head != newNode) {
				// Set the previous node's next to our new node
				lastNode->next = newNode;
			}

			// Set the previous node
			newNode->prev = lastNode;
			
			// Most recently added Node, make tail point to this node 
			m_tail = newNode;
			
			// Increment the size
			++m_size;
			
			// Set the most recent node
			lastNode = newNode;
		}
	}

	// Copy assignment overload for deep copy
	linkedlist& operator=(const linkedlist& listCopy) {
		
		// Check for self assignment
		if (&listCopy == this) {
			return *this;
		}
		
		// Deallocate old linked list and put in empty state
		deallocate();

		// Temporary pointer to keep track of the previous node
		Node* lastNode{ nullptr };

		for (Node* tnd{ listCopy.m_head }; tnd != nullptr; tnd = tnd->next) {

			// Create a new node for our original linkedlist with the same data as the copy.
			Node* newNode{ new Node{tnd->data, nullptr, nullptr} };

			// Case: First Node, point head to newNode
			if (m_head == nullptr) {
				m_head = newNode;
			}

			// make sure there is more than one node

			if (m_head != newNode) {
				// Set the previous node's next to our new node
				lastNode->next = newNode;
			}

			// Set the previous node
			newNode->prev = lastNode;

			// Most recently added Node, make tail point to this node 
			m_tail = newNode;

			// Increment the size
			++m_size;

			// Set the most recent node
			lastNode = newNode;
		}

		return *this;
	}

	// Destructor
	~linkedlist() {
		
		//Deallocates all the nodes in the linked list
		deallocate();
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

	// Deallocates all the nodes in the linked list and leave the linkedlist in an empty state
	void deallocate() {

		// Temporary to save a pointer to the next node
		Node* nextNode{ nullptr };

		// Deallocate every node in the linkedlist
		for (Node* tnd{ m_head }; tnd != nullptr; tnd = nextNode) {

			// Save the pointer to the next node 
			nextNode = tnd->next;

			// Deallocate our current Node
			delete[] tnd;
		}
		
		// Set all the members to an empty state
		m_head = nullptr;
		m_tail = nullptr;
		m_size = 0;
	}
};

} // namespace ReImplSTL