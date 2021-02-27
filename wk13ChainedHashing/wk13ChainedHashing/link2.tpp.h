// FILE: link2.tpp.h
// IMPLEMENTS: The ten template functions of the linked list toolkit
// (see link2.h). Note that this file is not compiled on its own.
// Instead, this file is included with an include directive at the bottom
// of link2.h.

#include <assert.h>    // Provides assert
#include <stdlib.h>    // Provides NULL and size_t

template <class Item>
size_t list_length(Node<Item>* head_ptr)
// Library facilities used: stdlib.h
{
    Node<Item> *cursor;
    size_t answer;

    answer = 0;
    for(cursor = head_ptr; cursor != NULL; cursor = cursor->link)
        answer++;

    return answer;
}

template <class Item>
void list_head_insert(Node<Item>*& head_ptr, const Item& new_item)
{
    Node<Item> *insert_ptr;

    insert_ptr = new Node<Item>;
    insert_ptr->data = new_item;
    insert_ptr->link = head_ptr;
    head_ptr = insert_ptr;
}

template <class Item>
void list_insert(Node<Item>* previous_ptr, const Item& new_item)
{
    Node<Item> *insert_ptr;

    insert_ptr = new Node<Item>;
    insert_ptr->data = new_item;
    insert_ptr->link = previous_ptr->link;
    previous_ptr->link = insert_ptr;
}

template <class Item>
Node<Item>* list_search(Node<Item>* head_ptr, const Item& target)
{
    Node<Item> *cursor;

    for (cursor = head_ptr; cursor != nullptr; cursor = cursor->link)
        if (cursor->data == target)
            return cursor;

    return nullptr;
}

template <class Item, class SizeType>
Node<Item>* list_locate(Node<Item>* head_ptr, SizeType position)
// Library facilities  assert.h, stdlib.h
{
    Node<Item> *cursor;
    size_t i;

    assert(position > 0);
    
    cursor = head_ptr;
    for(i = 1; (i != position) && (cursor != nullptr); i++)
        cursor = cursor->link;
    return cursor;
}

template <class Item>
void list_head_remove(Node<Item>*& head_ptr)
{
    Node<Item> *remove_ptr;

    remove_ptr = head_ptr;
    head_ptr = head_ptr->link;
    delete remove_ptr;
}

template <class Item>
void list_remove(Node<Item>* previous_ptr)
{
    Node<Item> *remove_ptr;

    remove_ptr = previous_ptr->link;
    previous_ptr->link = remove_ptr->link;
    delete remove_ptr;
}

template <class Item>
void list_clear(Node<Item>*& head_ptr)
// Library facilities used: stdlib.h
{
    while (head_ptr != NULL)
        list_head_remove(head_ptr);
}

template <class Item>
void list_copy
(Node<Item>* source_ptr, Node<Item>*& head_ptr, Node<Item>*& tail_ptr)
// Library facilities used: stdlib.h
{
    head_ptr = NULL;
    tail_ptr = NULL;

    // Handle the case of the empty list
    if (source_ptr == NULL)
        return;

    // Make the head node for the newly created list, and put data in it
    list_head_insert(head_ptr, source_ptr->data);
    tail_ptr = head_ptr;

    // Copy the rest of the nodes one at a time, adding at the tail of new list
    for (source_ptr = source_ptr->link; source_ptr != NULL; source_ptr = source_ptr->link)
    {
        list_insert(tail_ptr, source_ptr->data);
        tail_ptr = tail_ptr->link;
    }
}

template <class Item>
void list_piece
(Node<Item>* start_ptr, Node<Item>* end_ptr, Node<Item>*& head_ptr, Node<Item>*& tail_ptr)
// Library facilities used: assert.h, stdlib.h
{
    head_ptr = NULL;
    tail_ptr = NULL;

    // Handle the case of the empty list
    if (start_ptr == NULL)
        return;
    
    // Make the head node for the newly created list, and put data in it
    list_head_insert(head_ptr, start_ptr->data);
    tail_ptr = head_ptr;
    if (start_ptr == end_ptr)
        return;
    
    // Copy the rest of the nodes one at a time, adding at the tail of new list
    for (start_ptr = start_ptr->link; start_ptr != NULL; start_ptr = start_ptr->link)
    {
        list_insert(tail_ptr, start_ptr->data);
        tail_ptr = tail_ptr->link;
        if (start_ptr == end_ptr) 
            return;
    }
}
