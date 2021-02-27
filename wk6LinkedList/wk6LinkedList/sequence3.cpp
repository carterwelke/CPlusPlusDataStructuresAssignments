#include "sequence3.h"
#include <cassert>

namespace main_savitch_5 {
	sequence::sequence(){
		head_ptr = nullptr;
		tail_ptr = nullptr;
		cursor = nullptr;
		precursor = nullptr;
		many_nodes = 0;
	}

	sequence::sequence(const sequence& source){
		head_ptr = nullptr;
		tail_ptr = nullptr;
		cursor = nullptr;
		precursor = nullptr;
		many_nodes = source.many_nodes;

		node *source_ptr = source.head_ptr;

		// Handle the case of the empty list.
		if (source_ptr == nullptr)
			return;

		// Make the head node for the newly created list, and put data in it.
		list_head_insert(head_ptr, source_ptr->data());
		tail_ptr = head_ptr;
		if (source_ptr == source.cursor) start();
		// Copy the rest of the nodes one at a time, adding at the tail of new list.
		//Check for precursor and cursor
		source_ptr = source_ptr->link();
		while (source_ptr != nullptr)
		{
			list_insert(tail_ptr, source_ptr->data());

			if (source_ptr == source.cursor)
			{
				precursor = tail_ptr;
				cursor = tail_ptr->link();
			}

			tail_ptr = tail_ptr->link();
			source_ptr = source_ptr->link();
		}
	}

	sequence::~sequence(){
		list_clear(head_ptr);
		many_nodes = 0;
	}

	void sequence::start(){
		cursor = head_ptr;
		precursor = nullptr;
	}

	void sequence::advance(){
		assert(is_item());
		precursor = cursor;
		cursor = cursor->link();
	}

	void sequence::insert(const value_type& entry){
		if (cursor == nullptr || precursor == nullptr) {
			list_head_insert(head_ptr, entry);
			cursor = head_ptr;
			if (many_nodes == 0) tail_ptr = head_ptr;
		} else {
			list_insert(precursor, entry);
			cursor = precursor->link();
		}
		++many_nodes;
	}

	void sequence::attach(const value_type& entry){
		if (many_nodes == 0) {
			list_head_insert(head_ptr, entry);
			tail_ptr = head_ptr;
			cursor = head_ptr;
		}
		else if(is_item()){
			list_insert(cursor, entry);
			advance();
		}
		else {
			list_insert(precursor, entry);
			cursor = precursor->link();
		}
		++many_nodes;
	}

	void sequence::operator=(const sequence& source){
		if (this == &source) return;
		
		//clear list
		list_clear(head_ptr);

		//reset private values
		head_ptr = nullptr;
		tail_ptr = nullptr;
		cursor = nullptr;
		precursor = nullptr;
		many_nodes = source.many_nodes;

		node* source_ptr = source.head_ptr;
		// Handle the case of the empty list.
		if (source_ptr == nullptr)
			return;

		// Make the head node for the newly created list, and put data in it.
		list_head_insert(head_ptr, source_ptr->data());
		tail_ptr = head_ptr;
		if (source_ptr == source.cursor) start();
		// Copy the rest of the nodes one at a time, adding at the tail of new list.
		//Check for precursor and cursor
		source_ptr = source_ptr->link();
		while (source_ptr != nullptr)
		{
			list_insert(tail_ptr, source_ptr->data());

			if (source_ptr == source.cursor)
			{
				precursor = tail_ptr;
				cursor = tail_ptr->link();
			}

			tail_ptr = tail_ptr->link();
			source_ptr = source_ptr->link();
		}
	}

	void sequence::remove_current(){
		assert(is_item());
		if (cursor == head_ptr) {
			if (many_nodes == 1) {
				cursor = nullptr;
				tail_ptr = nullptr;
			}
			else {
				cursor = cursor->link();
			}
			list_head_remove(head_ptr);
		}
		else {
			if (cursor == tail_ptr) tail_ptr = precursor;
			cursor = cursor->link();
			list_remove(precursor);
		}
		--many_nodes;
	}

	sequence::value_type sequence::current() const{
		assert(is_item());
		return cursor->data();
	}
}
