// FILE: table2.tpp.h
// TEMPLATE CLASS IMPLEMENTED: Table (see table2.h for documentation)
// INVARIANT for the Table ADT:
//   1. The number of records in the Table is in the member variable
//      total_records.
//   2. The actual records of the table are stored in a chained hash table.
//      An entry with key i is stored on the linked list with the head
//      pointer at data[hash(i)].

//Carter Welke CIST 004B Spring 2020

#include <assert.h> // Provides assert
#include <stdlib.h> // Provides nullptr, size_t
#include "link2.h"  // Provides the linked list toolkit

template <class RecordType>
Table<RecordType>::Table( )
// Library facilities used: stdlib.h
{
    size_t i;

    total_records = 0;
    for (i = 0; i < TABLE_SIZE; i++)
        hashTable[i] = nullptr;
}

template <class RecordType>
Table<RecordType>::Table(const Table<RecordType>& source) 
// Library facilities used: link2.h, stdlib.h 
{
    size_t i;
    Node<RecordType>* tail_ptr; // Needed for list_copy

    for (i = 0; i < TABLE_SIZE; i++)
        list_copy(source.hashTable[i], hashTable[i], tail_ptr);
    total_records = source.total_records;
}

template <class RecordType>
Table<RecordType>::~Table( )
// Library facilities used: link2.h
{
    size_t i;

    total_records = 0;
    for (i = 0; i < TABLE_SIZE; i++)
        list_clear(hashTable[i]);
}

template <class RecordType>
void Table<RecordType>::insert(const RecordType& entry)
// Library facilities used: assert.h, link2.h
{
    Node<RecordType>* cursor; // set to point to existing Node with given key
    assert(entry.key >= 0);
    // Set cursor to point to existing Node with given key (if there is one)
    // To be implemented by students
    if (is_present(entry.key)) {
        find_node(entry.key)->data = entry;
    }
    else {
        list_head_insert(hashTable[hash(entry.key)], entry);
        ++total_records;
    }
    return;
}

template <class RecordType>
void Table<RecordType>::remove(int key)
// Library facilities used: assert.h, link2.h
{
    Node<RecordType> *cursor;    // Points to existing Node with given key
    //Node<RecordType> *precursor; // Points to node before the cursor
    assert(key >= 0);
    // Set cursor to point to existing Node with given key (if there is one)
    // To be implemented by students
    if (is_present(key)) {
        size_t i = hash(key);
        find_node(key)->data = hashTable[i]->data; //originally looked like this: find_node(key)->data = data[i]->data;
        list_head_remove(hashTable[i]);
        --total_records;
    }
    return;
}

template <class RecordType>
void Table<RecordType>::operator =(const Table<RecordType>& source) 
// Library facilities used: link2.h, stdlib.h 
{
    size_t i;
    Node<RecordType>* tail_ptr; // Needed for list_copy
	// To be implemented by students

    if (this == &source) {
        return;
    }

    for (i = 0; i < TABLE_SIZE; i++)
        list_clear(hashTable[i]);

    for (i = 0; i < TABLE_SIZE; i++)
        list_copy(source.hashTable[i], hashTable[i], tail_ptr);
    total_records = source.total_records;
}

template <class RecordType>
bool Table<RecordType>::is_present(int key) const
// Library facilities used: assert.h, stdlib.h
{
    assert(key >= 0);
	// To be implemented by students
    return find_node(key) != nullptr;

}

template <class RecordType>
void Table<RecordType>::find(int key, bool& found, RecordType& result) const
// Library facilities used: stdlib.h
{
    Node<RecordType> *cursor;
	// To be implemented by students
    cursor = find_node(key);
    if (cursor != nullptr) {
        found = true;
        result = cursor->data;
    }
    else {
        found = false;
    }
}

template <class RecordType>
size_t Table<RecordType>::hash(int key) const
// Library facilities used: stdlib.h
{
    return (key % TABLE_SIZE);
}

template <class RecordType>
Node<RecordType>* Table<RecordType>::find_node(int key) const
// Postcondition: The return value is a pointer to the record with the
// specified key (if there is one). If there is no such node, the return value
// is the nullptr pointer.
// Library facilities used: link2.h, stdlib.h
{
    Node<RecordType>* cursor;
	// To be implemented by students
    cursor = hashTable[hash(key)];
    while (cursor != nullptr) {
        if (key == cursor->data.key) {
            return cursor;
        }
        cursor = cursor->link;
    }
    return nullptr;
}

