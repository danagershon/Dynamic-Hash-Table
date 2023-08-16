#ifndef WET2CPP_DYNAMICHASHTABLE_H
#define WET2CPP_DYNAMICHASHTABLE_H

#include "DoublyLinkedList.h"
#include <iostream>

typedef enum {
    ELEMENT_DOES_NOT_EXIST = 110,
    ELEMENT_EXISTS = 111,
    HASHTABLE_SUCCESS = 222
} DynamicHashtableStatus;

template <class DataType>
class DynamicHashtable {
    int table_size;
    int elements_num;
    DoublyLinkedList<DataType>* table;

    int hashFunction(int element);

    double getLoadFactor();

    void resizeTable(int new_size);

    void disassembleList(DoublyLinkedList<DataType>* new_table, int new_size,
            DoublyLinkedList<DataType>& list);

public:
    DynamicHashtable();

    ~DynamicHashtable();

    DynamicHashtableStatus getData(int element, DataType* data);

    DynamicHashtableStatus addElement(int element, DataType data);

    DynamicHashtableStatus deleteElement(int element);

    void printTable();
};

template<class DataType>
DynamicHashtable<DataType>::DynamicHashtable()
    : table_size(1), elements_num(0), table(new DoublyLinkedList<DataType>[1])
{}

template<class DataType>
DynamicHashtable<DataType>::~DynamicHashtable() {
    delete[] table;
}

template<class DataType>
DynamicHashtableStatus DynamicHashtable<DataType>::getData(int element,
        DataType* data) {
    DoublyLinkedList<DataType>& list = table[hashFunction(element)];

    if(list.getData(element, data) == KEY_DOES_NOT_EXIST){
        return ELEMENT_DOES_NOT_EXIST;
    }

    return ELEMENT_EXISTS;
}

template<class DataType>
double DynamicHashtable<DataType>::getLoadFactor() {
    return elements_num/table_size;
}

template<class DataType>
DynamicHashtableStatus DynamicHashtable<DataType>::addElement(int element,
        DataType data) {

    DoublyLinkedList<DataType>& list = table[hashFunction(element)];

    if(list.keyExists(element)) {
        return ELEMENT_EXISTS;
    }

    list.pushBack(element, data);
    elements_num++;

    if((int)getLoadFactor() == 1) {
        resizeTable(2*table_size);
    }

    return HASHTABLE_SUCCESS;
}

template<class DataType>
DynamicHashtableStatus DynamicHashtable<DataType>::deleteElement(int element) {

    DoublyLinkedList<DataType>& list = table[hashFunction(element)];

    if(!list.keyExists(element)) {
        return ELEMENT_DOES_NOT_EXIST;
    }

    list.deleteKey(element);
    elements_num--;

    if(getLoadFactor() == 0.25) {
        int new_size = table_size/2;
        if(new_size > 0) {
            resizeTable(new_size);
        }
    }

    return HASHTABLE_SUCCESS;
}

template<class DataType>
int DynamicHashtable<DataType>::hashFunction(int element) {
    return element%table_size;
}

template<class DataType>
void DynamicHashtable<DataType>::resizeTable(int new_size) {
    auto * new_table = new DoublyLinkedList<DataType>[new_size];

    for(int list_index = 0; list_index < table_size; list_index++) {
        DoublyLinkedList<DataType>& list = table[list_index];
        disassembleList(new_table, new_size, list);
    }

    delete[] table;
    table = new_table;
    table_size = new_size;
}

template<class DataType>
void DynamicHashtable<DataType>::disassembleList(DoublyLinkedList<DataType> *new_table,
        int new_size, DoublyLinkedList<DataType> &list) {

    Node<DataType>* curr_node = list.head;

    while(curr_node != nullptr) {
        int new_index = (curr_node->key)%new_size;
        new_table[new_index].pushBackNode(curr_node);
        curr_node = curr_node->next;
    }
}

template<class DataType>
void DynamicHashtable<DataType>::printTable() {
    for(int i = 0; i < table_size; i++) {
        std::cout << "\nlist " << i << std::endl;
        table[i].printList();
    }
}

#endif //WET2CPP_DYNAMICHASHTABLE_H
