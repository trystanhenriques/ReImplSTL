#include <cstddef>
#include <iostream>
#include <initializer_list>
#include <memory>

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

	// Move Constructor
	linkedlist(linkedlist&& rList) {

		// Steal the data that rList has
		m_head = rList.m_head;
		m_tail = rList.m_tail;
		m_size = rList.m_size;

		// Leave the other list in an empty but valid state
		rList.m_head = nullptr;
		rList.m_tail = nullptr;
		rList.m_size = 0;
	}

	// Inititalizer List Constructor
	linkedlist(std::initializer_list<value_type> iList) {
		
		// Temporary pointer to keep track of the previous node
		Node* lastNode{ nullptr };

		// Iterate through the initializer list using iterator
		for (auto it{ iList.begin() }; it != iList.end(); ++it) {
		
			// Create new Node 
			Node* newNode { new Node{*it, nullptr, nullptr} };
			
			// First Node! Set head
			if (m_head == nullptr) {
				m_head = newNode;
			}
			
			// make sure there is more than one node
			if (m_head != newNode) {
				// Set the previous node's next to our new node
				lastNode->next = newNode;
			}
			
			// Set our previous node
			newNode->prev = lastNode;

			// Most recent Node so Set the Tail
			m_tail = newNode;

			// Set Most Recent Node for next iteration
			lastNode = newNode;
			
			// Increment the size
			++m_size;
		}
	}

	// Destructor
	~linkedlist() {

		//Deallocates all the nodes in the linked list
		deallocate();
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

	// Overload assignment operator for move semantics
	linkedlist& operator=(linkedlist** rList) {
		
		// Check for self assignment
		if (this == &rList) {
			return &this;
		}

		// Deallocate the old linkedlist
		deallocate();

		// Steal the data that rList has
		m_head = rList.m_head;
		m_tail = rList.m_tail;
		m_size = rList.m_size;

		// Leave the other list in an empty but valid state
		rList.m_head = nullptr;
		rList.m_tail = nullptr;
		rList.m_size = 0;

		return *this;
		
	}

	// Overload assignment operator for initializer list
	linkedlist& operator=(std::initializer_list<value_type> iList) {
		
		// Deallocate old linked list and put in empty state
		deallocate();

		// Temporary pointer to keep track of the previous node
		Node* lastNode{ nullptr };

		// Iterate through the initializer list using iterator
		for (auto it{ iList.begin() }; it != iList.end(); ++it) {

			// Create new Node 
			Node* newNode{ new Node{*it, nullptr, nullptr} };

			// First Node! Set head
			if (m_head == nullptr) {
				m_head = newNode;
			}

			// make sure there is more than one node
			if (m_head != newNode) {
				// Set the previous node's next to our new node
				lastNode->next = newNode;
			}

			// Set our previous node
			newNode->prev = lastNode;

			// Most recent Node so Set the Tail
			m_tail = newNode;

			// Set Most Recent Node for next iteration
			lastNode = newNode;

			// Increment the size
			++m_size;
		}

		return *this;

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

	// =========================
	// Element Access
	// =========================
	reference front() { return *m_head; }
	const_reference front() const { return *m_head; }
	reference back() { return *m_tail; }
	const_reference back() const { return *m_head; }

	// =========================
	// Capacity
	// =========================
	bool empty() const {
		return !m_size;
	}
	
	int size() {
		return static_cast<int>(m_size);
	}

	// =========================
	// Modifiers
	// =========================
	
	// Appends a copy of value to the end of the container.
	void push_back(const_reference val) {

		// Create New Node to contain our value
		Node* newNode { new Node{val, nullptr, nullptr} };

		// Case Where the linked list is empty
		if (empty()) {
			m_head = newNode;
			m_tail = newNode;
			++m_size;
			return;
		}
		
		// Set our old tail's next to point to our new Node
		m_tail->next = newNode;

		// Set the new Nodes previous to point at the old tail
		newNode->prev = m_tail;

		// Set the new tail
		m_tail = newNode;

		// Increase the size to account for new Node
		++m_size;
	}

	// Appends a move of value to the end of the container.
	void push_back(value_type&& rval) {

		// Create New Node to contain our value
		Node* newNode{ new Node{std::move(rval), nullptr, nullptr} };

		// Case Where the linked list is empty
		if (empty()) {
			m_head = newNode;
			m_tail = newNode;
			++m_size;
			return;
		}

		// Set our old tail's next to point to our new Node
		m_tail->next = newNode;

		// Set the new Nodes previous to point at the old tail
		newNode->prev = m_tail;

		// Set the new tail
		m_tail = newNode;

		// Increase the size to account for new Node
		++m_size;
	}
	
	// Prepends a copy of value to the beginning of the container.
	void push_front(const_reference val) {
		
		// Create new Node
		Node* newNode { new Node {val, nullptr, nullptr} };
		
		// if empty, set head and tail to new Node
		if (empty()) {
			m_head = newNode;
			m_tail = newNode;
			++m_size;	
		}

		// Make the previous head point to the new Node
		m_head->prev = newNode;

		// Set the newNodes next to point at the old head
		newNode->next = m_head;

		// Set the new head
		m_head = newNode;

		// Increase size
		++m_size;	
	}

	// Prepends a move of value to the beginning of the container.
	void push_front(value_type&& rval) {

		// Create new Node
		Node* newNode{ new Node {std::move(rval), nullptr, nullptr} };

		// if empty, set head and tail to new Node
		if (empty()) {
			m_head = newNode;
			m_tail = newNode;
			++m_size;
		}

		// Make the previous head point to the new Node
		m_head->prev = newNode;

		// Set the newNodes next to point at the old head
		newNode->next = m_head;

		// Set the new head
		m_head = newNode;

		// Increase size
		++m_size;
	}

	
	// Removes the last element of the container.
	void pop_back() {
		
		// Check if linked list is empty. IF so, Return
		if (empty()) {
			return;
		}
	
		// Check if there is only one node in the linkedlist
		if (m_size == 1) {
			delete m_head;
			m_head = nullptr;
			m_tail == nullptr;
			--m_size;
			return;
		}
		
		// Get a pointer to the Node before m_tail
		Node* prevNode {m_tail->prev};
		
		// Deallocate the node
		delete m_tail;

		// Make Previous Node -> next point to nulltptr
		prevNode->next = nullptr;
		
		// Set m_tail to the previous node
		m_tail = prevNode;

		// Dec size
		--m_size;
	}

	void pop_front() {
		
		// Check if the list is empty, if so, return early
		if (empty()) {
			return;
		}

		// Case where there is only one element
		if (m_size == 1) {
			delete m_head;
			m_head = nullptr;
			m_tail = nullptr;
			--m_size;
			return;
		}
	
		// Save the pointer to the next element
		Node* nextNode {m_head->next};

		// Deallocate the data at head 
		delete m_head;
	
		// Remove the link to the old head
		nextNode->prev = nullptr;

		// Set the new head
		m_head = nextNode;
		
		// dec the size
		--m_size;
	}
	
	// Resizes the container to contain newSize elements:
	void resize(size_type newSize) {
		
		// Check if the newSize is 0, if so , deallocate all the nodes and return
		if (newSize == 0) {
			deallocate();
			return;
		}
		// Check if newSize is equal to current size, if so, do nothing
		else if (m_size == newSize) {
			return;
		}
		// Case where the newSize is greater than the size: Allocate more nodes!
		else if (newSize > m_size) {

			// Start tracker node at tail
			Node* tnd {m_tail};
			
			// Find the difference between newSize and m_size
			size_type num_nodes_to_add { newSize - m_size };	// Disclaimer, we DONT need to use std::ptrdiff_t here because we explicity checked if newSize > m_size 
			
			// Pointer for the new Node
			Node* newNode {};
			
			for (size_type i{}; i < num_nodes_to_add; ++i) {
				
				// save pointer to the previous tail
				Node* oldTail {m_tail};

				// Allocate the new node with default data
				newNode = new Node {};

				// Set the new tail to the new Node
				m_tail = newNode;

				// Set the head as well if the linkedlist was empty
				if (empty()) {
					m_head = newNode;
				}
				
				// Make sure the old tail was not null. An example of this occures when the linked list was empty before this
				if (oldTail != nullptr) {
					oldTail->next = newNode;
				}
				
				// Set the previous for the new Node
				newNode->prev = oldTail;
	
				// inc the size
				++m_size;
			}
		}
		// Case where the newSize is smaller than the current size: Deallocate nodes!
		else if (newSize < m_size) {
			
			// Set Tracker Node to point to the (newSize) Node
			Node* tnd{ m_head };
			for (size_type i{}; i < newSize; ++i) {
				tnd = tnd->next;
			}

			// Set new tail
			m_tail = tnd->prev;	// We are doing tnd->prev here because tnd is currently at (m_size) node, so we need to go back one node. We are goint to deallocate from [list[newsize], list[oldSize)

			// Poitner to save pointer to the next node
			Node* nextNode { nullptr };

			// Deallocate all the nodes from [newSize, m_size)
			// Reminder that tnd is currently at the (newSize) node, so we are deallocating from tnd to the end of the list
			for (; tnd != nullptr; tnd = nextNode) {
				
				// Save pointer to the next node
				nextNode = tnd->next;

				// Deallocte node
				delete tnd;

				// decrease the size
				--m_size;
			}
			
			// Make sure the new tail isnt pointing to deallocated memory
			m_tail->next = nullptr;
		}	
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