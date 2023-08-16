#ifndef WET2CPP_DOUBLYLINKEDLIST_H
#define WET2CPP_DOUBLYLINKEDLIST_H

#include <iostream>

typedef enum {
    KEY_DOES_NOT_EXIST = -100,
    KEY_EXISTS = 100
} DoublyLinkedListStatus;

template <class DataType>
struct Node {
    int key;
    DataType data;
    Node *prev, *next;

    Node(int key, DataType data, Node* prev, Node* next)
            : key(key), data(data), prev(prev), next(next) {}
};

template <class DataType>
class DoublyLinkedList{
public:

    Node<DataType> *head, *tail;

    Node<DataType>* searchNode(int key);

    /* delete the given node from the list */
    void deleteNode(Node<DataType>* to_delete_node);

    /* list constructor */
    DoublyLinkedList();

    /* list destructor */
    ~DoublyLinkedList();

    DoublyLinkedList(const DoublyLinkedList& list) = delete;
    DoublyLinkedList& operator=(const DoublyLinkedList& list);

    /* add a new node with key and data to the end of the list */
    Node<DataType>* pushBack(int key, DataType data);

    /* return true if the list is empty or false if the list is not empty */
    bool isEmpty();

    bool keyExists(int key);

    DoublyLinkedListStatus getData(int key, DataType* data);

    void deleteKey(int key);

    void pushBackNode(Node<DataType>* node);

    void printList();
};

template<class DataType>
DoublyLinkedList<DataType>::DoublyLinkedList()
        : head(nullptr), tail(nullptr) {}

template<class DataType>
DoublyLinkedList<DataType>::~DoublyLinkedList()  {
    /* deallocating every node in the list from head to tail */
    while(head != nullptr) {
        Node<DataType>* temp = head;
        head = head->next;
        delete temp;
    }
}

template<class DataType>
DoublyLinkedList<DataType>& DoublyLinkedList<DataType>::operator=
        (const DoublyLinkedList &list) {
    return *this;
}

template<class DataType>
void DoublyLinkedList<DataType>::deleteNode(Node<DataType>* to_delete_node) {
    if(head == nullptr || tail == nullptr || to_delete_node == nullptr){
        return;
    }

    if(to_delete_node == head){
        head = head->next;
    }
    if(to_delete_node == tail){
        tail = tail->prev;
    }
    if(to_delete_node->next != nullptr){
        /* updating the node after to_delete_node to point to to_delete_node's
         * previous node */
        to_delete_node->next->prev = to_delete_node->prev;
    }
    if(to_delete_node->prev != nullptr){
        /* updating the node before to_delete_node to point to to_delete_node's
         * next node */
        to_delete_node->prev->next = to_delete_node->next;
    }

    /* deallocating the node */
    delete to_delete_node;
}

template<class DataType>
bool DoublyLinkedList<DataType>::isEmpty() {
    return head == nullptr || tail == nullptr;
}

template<class DataType>
Node<DataType>* DoublyLinkedList<DataType>::pushBack(int key, DataType data) {
    /* create new node and set it's prev to be the current tail */
    auto * new_node = new Node<DataType>(key, data, tail, nullptr);
    /* update tail to be the new node */
    tail = new_node;

    if(tail->prev == nullptr){
        /* means that beforehand there list was empty, therefore the the new
         * node is the only one in the list and the head should point to it */
        head = tail;
    } else{
        /* means that beforehand the list had a node, therefore the former
         * tail's "next" pointer should point to the new node */
        tail->prev->next = tail;
    }

    return tail;
}

template<class DataType>
bool DoublyLinkedList<DataType>::keyExists(int key) {
    return searchNode(key) != nullptr;
}

template<class DataType>
DoublyLinkedListStatus DoublyLinkedList<DataType>::getData(int key,
        DataType *data) {
    Node<DataType>* node = searchNode(key);

    if(node == nullptr){
        return KEY_DOES_NOT_EXIST;
    }

    *data = node->data;
    return KEY_EXISTS;
}

template<class DataType>
void DoublyLinkedList<DataType>::deleteKey(int key) {
    Node<DataType>* to_delete_node = searchNode(key);

    if(to_delete_node == nullptr){
        return;
    }

    deleteNode(to_delete_node);
}

template<class DataType>
Node<DataType>* DoublyLinkedList<DataType>::searchNode(int key) {
    Node<DataType>* curr_node = head;

    while(curr_node != nullptr) {
        if(curr_node->key == key) {
            return curr_node;
        }
        curr_node = curr_node->next;
    }

    return nullptr;
}

template<class DataType>
void DoublyLinkedList<DataType>::printList() {
    Node<DataType>* curr_node = head;

    while(curr_node != nullptr) {
        std::cout << curr_node->key << std::endl;
        curr_node = curr_node->next;
    }
}

template<class DataType>
void DoublyLinkedList<DataType>::pushBackNode(Node<DataType>* node) {
    pushBack(node->key, node->data);
}

#endif //WET2CPP_DOUBLYLINKEDLIST_H
