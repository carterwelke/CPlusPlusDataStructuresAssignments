#include "sequence1.h"
#include <cassert>;

//Carter Welke CIST004B Spring 2020
//Implements sequence1.h functions according to header file

namespace main_savitch_3
{
	sequence::sequence()
	{
		current_index = 0;
		used = 0;
		
	}

	void sequence::start(){
		if(used > 0)
			current_index = 0;
	}

	void sequence::advance(){
		assert(is_item());
		++current_index;
	}

	void sequence::insert(const value_type & entry){
		assert(size() < CAPACITY);
		if (!is_item())
		{
			current_index = 0;
		}
		++used;
		for (size_type i = used-1; i > current_index; --i){
			data[i] = data[i-1];
		}
		data[current_index] = entry;
	}

	void sequence::attach(const value_type& entry){
		assert(size() < CAPACITY);
		if (!is_item())
		{
			current_index = used - 1;
		}
		++used;
		for (size_type i = used-1; i > current_index; --i) {
			data[i] = data[i-1];
		}
		data[++current_index] = entry;
	}

	void sequence::remove_current(){
		assert(is_item());
		for (size_t i = current_index + 1; i < used; ++i)
		{
			data[i-1] = data[i];
		}
		--used;
	}

	sequence::size_type sequence::size() const{
		return used;
	}

	bool sequence::is_item() const{
		return (current_index < used);
	}

	sequence::value_type sequence::current() const{
		assert(is_item());
		return data[current_index];
	}
};