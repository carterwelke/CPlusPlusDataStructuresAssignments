// FILE: Stack1.template
// TEMPLATE CLASS IMPLEMENTED: Stack<Item> (see Stack1.h for documentation)
// This file is included in the header file, and not compiled separately.
// INVARIANT for the Stack class:
//   1. The number of items in the Stack is in the member variable used.
//   2. The actual items of the Stack are stored in a partially-filled
//      array data[0]..data[used-1]. The Stack elements appear from the
//      bottom (at data[0]) to the top (at data[used-1]).

#include <cassert>  // Provides assert

namespace main_savitch_7A
{
	//const typename Stack<Item>::size_type Stack<Item>::CAPACITY;
	
	template <class Item>
	void Stack<Item>::push(const Item& entry)
	// Library facilities used: cassert
	{
		
		//make new Node
		Node<Item>* newItem = new Node<Item>;
		newItem->data = entry;
		newItem->link = head_ptr;
		head_ptr = newItem;

		++used;
		return;
	}
	
	template <class Item>
	Item Stack<Item>::pop( )
	// Library facilities used: cassert
	{
		assert(size() > 0);

		Node<Item>* removePtr = head_ptr;
		head_ptr = head_ptr->link;

		Item dataItem = removePtr->data;
		delete removePtr;

		--used;
		return dataItem;
	}
	
	template <class Item>
	Item Stack<Item>::top( ) const
	// Library facilities used: cassert
	{
		assert(size() > 0);
		return head_ptr->data;
	}
	
	template <class Item>
	Item Stack<Item>::peek(size_type i) //const
	// Library facilities used: cassert
	{
		assert(size() >= i && i > 0);
		Node<Item>* cursor = head_ptr;
		for (unsigned int j = 1; j < i; ++j) {
			cursor = cursor->link;
		}
		return cursor->data;
	}
}