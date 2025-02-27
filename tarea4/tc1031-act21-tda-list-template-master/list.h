// =================================================================
//
// File: list.h
// Author:
// Date:
// 
// =================================================================
#ifndef LIST_H
#define LIST_H

#include <string>
#include <sstream>
#include "exception.h"
#include "header.h"

template <class T> class List;

// =================================================================
// Definition of the Node class
// =================================================================
template <class T>
class Node {
private:
	Node(T);
	Node(T, Node<T>*);

	T	    value;
	Node<T> *next;

	friend class List<T>;
};

// =================================================================
// Constructor. Initializes the value of the node. The variable next
// is initialized to null.
//
// @param val, stored value in the node.
// =================================================================
template <class T>
Node<T>::Node(T val) : value(val), next(NULL) {
}

// =================================================================
// Constructor. Initializes both instance variables.
//
// @param val, stored value in the node.
// @param nxt, the next node.
// =================================================================
template <class T>
Node<T>::Node(T val, Node* nxt) : value(val), next(nxt) {
}

// =================================================================
// Definition of the List class
// =================================================================
template <class T>
class List {
private:
	Node<T> *head;
	uint 	size;

public:
	List();
	~List();

	uint  length() const;
	bool empty() const;
	bool contains(T) const;
	void clear();
	std::string toString() const;

	T    front() const;
	T    last() const;
	T    get(uint) const;

	void push_front(T);
	void push_back(T);
	void insert_at(T, uint);

	T    pop_front();
	T 	 pop_back();
	T    remove_at(uint);

	long int  indexOf(T) const;
};

// =================================================================
// Constructor. Initializes both instance variables to zero.
// =================================================================
template <class T>
List<T>::List() :head(NULL), size(0) {
}

// =================================================================
// Destructor. Remove all items from the list.
// =================================================================
template <class T>
List<T>::~List() {
	clear();
}

// =================================================================
// Returns if the list is empty or not
//
// @returns true if the list is empty, false otherwise.
// =================================================================
template <class T>
bool List<T>::empty() const {
	return (head == NULL);
}

// =================================================================
// Returns the number of items in the list.
//
// @returns size, the number of items in the list.
// =================================================================
template <class T>
uint List<T>::length() const {
	return size;
}

// =================================================================
// Determines if an item is in the list.
//
// @returns true if val is in the list, false otherwise
// =================================================================
template <class T>
bool List<T>::contains(T val) const {
	Node<T> *p;

	p = head;
	while (p != NULL) {
		if(p->value == val) {
			return true;
		}
		p = p->next;
	}
	return false;
}

// =================================================================
// Remove all items from the list.
// =================================================================
template <class T>
void List<T>::clear() {
	Node<T> *p, *q;

	p = head;
	while (p != NULL){
		q = p->next;
		delete p;
		p = q;
	}

	head = NULL;
	size = 0;
}

// =================================================================
// String representation of the elements in the list.
//
// @returns a string containing all the elements of the list.
// =================================================================
template <class T>
std::string List<T>::toString() const {
	std::stringstream aux;
	Node<T> *p;

	p = head;
	aux << "[";
	while (p != NULL) {
		aux << p->value;
		if (p->next != NULL) {
			aux << ", ";
		}
		p = p->next;
	}
	aux << "]";
	return aux.str();
}

// =================================================================
// Returns the first item in the list.
//
// @returns the object T at the beginning of the list.
// @throws NoSuchElement, if the list is empty.
// =================================================================
template <class T>
T List<T>::front() const {
	if (empty()) {
		throw NoSuchElement();
	}

	return head->value;
}

// =================================================================
// Returns the last item in the list.
//
// @returns the object T at the end of the list.
// @throws NoSuchElement, if the list is empty.
// =================================================================
template <class T>
T List<T>::last() const {
	Node<T> *p;

	if (empty()) {
		throw NoSuchElement();
	}

	p = head;
	while (p->next != NULL) {
		p = p->next;
	}
	return p->value;
}

// =================================================================
// Returns the element that is in the position indicated by index.
//
// @returns the element in index
// @throws IndexOutOfBounds, if index >= size.
// =================================================================
template <class T>
T List<T>::get(uint index) const {
	// Que pasa antes de que entre la función

	if (index >= size){
		throw IndexOutOfBounds();
	}


	T position;
	Node<T> *p; 
	int contador = 0;
	p = head;
	

	while(p != NULL){
			if(contador == index){
				position = p->value;
				break;
		}	

		contador++;
		p = p->next;


	}
	return position;
}

// =================================================================
// Add an item to the beginning of the list. Increase the size of
// the list.
// =================================================================
template <class T>
void List<T>::push_front(T val) {
	Node<T> *q;

	q = new Node<T>(val);
	q->next = head;
	head = q;
	size++;
}

// =================================================================
// Add an item to the end of the list. Increase the size of
// the list.
// =================================================================
template <class T>
void List<T>::push_back(T val) {
	Node<T> *p, *q;

	if (empty()) {
		push_front(val);
		return;
	}

	p = head;
	while (p->next != NULL) {
		p = p->next;
	}

	q = new Node<T>(val);
	q->next = p->next;
	p->next = q;
	size++;
}

// =================================================================
// Add an element in index (0 <= index <= size). The element that
// was in that position is shifted to the right.
//
// @throws IndexOutOfBounds, if index > size.
// =================================================================
template <class T>
void List<T>::insert_at(T val, uint index) {
	// Especie de contador para saber cuántas veces he brincado
	// Al llegar a esa cantidad, jugar con los intercambios con los apuntadores
	// TO DO
	
	//Creamos otra vez los lodos
	Node <T> *p, *q, *nodo_temp;

	int contador = 0;

		if (empty() || index == 0) {
		push_front(val);
		return;
	}

	if (index == size) {
		push_back(val);
		return;
	}

	//Respetamos los límites
	if(index > size)
	{
		throw IndexOutOfBounds();
	}

	//Como es líneal lo asignamos como head
	//Creamos el nodo temporal
	p = head;
	nodo_temp = new Node<T>(0);

	//contador para realizar los "brincos"

	
	while(p->next != NULL){
		if(contador == index-1){
			nodo_temp = p;			
		}
		contador++;
		p = p->next;
	}
	
	//cambiamos el valor sustitudi a la derecha.
	p = head;
	q = new Node<T>(val);
	q->next = nodo_temp->next;
	nodo_temp->next = q;
	size++;	
}

// =================================================================
// Delete the item at the beginning of the list.
//
// @returns the element that was at the beginning of the list.
// @throws NoSuchElement if the list is empty
// =================================================================
template <class T>
T List<T>::pop_front() {
	T val;
	Node<T> *p;

	if (empty()) {
		throw NoSuchElement();
	}

	p = head;

	head = p->next;
	val = p->value;

	delete p;
	size--;
	return val;
}

// =================================================================
// Delete the item at the end of the list.
//
// @returns the element that was at the end of the list.
// @throws NoSuchElement if the list is empty
// =================================================================
template <class T>
T List<T>::pop_back() {
	Node<T> *p, *q;
	T val;

	if (empty()) {
		throw NoSuchElement();
	}

	if (size == 1) {
		return pop_front();
	}

	q = NULL;
	p = head;
	while (p->next != NULL) {
		q = p;
		p = p->next;
	}

	q->next = p->next;
	val = p->value;

	delete p;
	size--;

	return val;
}

// =================================================================
// Delete the element found in index (0 <= index <size).
//
// @returns the element that was in index.
// @throws IndexOutOfBounds, if index >= size.
// =================================================================
template <class T>
T List<T>::remove_at(uint index) {
	// Se parece mucho al anterior que hicimos, solo que ahora borramos y no recorremos
	T aux;
	Node<T> *p, *q;
	int contador=0;
	p = head;

	//Condición de inicio
	if(index > size){
		throw IndexOutOfBounds();
	}

	if (0 <= index < size) {
		if (index == size-1){
		return pop_back();
	}

	if (index == 0) {
		return pop_front();
	}


	while(p != NULL){
		if(contador == index-1){
			q = p;
			p = q->next;
			break;
		}
		p = p->next;
		contador ++;
	}
	q->next = p->next;
	aux = p->value;

	//borramos y reducimos
	delete p;
	size--;
	return aux;
	}
}
// =================================================================
// Returns the position of an item in the list.
//
// @returns the position of an item in the list, -1 otherwise.
// @throws IndexOutOfBounds, if index >= size.
// =================================================================
template <class T>
long int List<T>::indexOf(T val) const {
	// TO DO
	
	Node<T> *p;
	int contador = 0;

	
	if (empty()){
		std::cout << "Error, you have no elements in the list" << std::endl;
	}
	

	
	p = head;
	while(p->next != NULL || val == p->value){
		if(val == p->value){
			return contador;
		}
		p = p->next;
		contador++;
	}
	return -1;
}


#endif /* LIST_H */
