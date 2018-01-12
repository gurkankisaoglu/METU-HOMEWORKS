#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#include <iostream>
#include "Node.hpp"

using namespace std;

template <class T>
class LinkedList {
    private:
        Node<T>* head;
        Node<T>* tail;
	size_t  size;
    public:

        LinkedList();
        LinkedList(const LinkedList<T>& ll);
        LinkedList<T>& operator=(const LinkedList<T>& ll);
        ~LinkedList();

        Node<T>* getHead() const;

        Node<T>* setHead(Node<T>* n);

        Node<T>* getTail() const;

        Node<T>* setTail(Node<T>* n);

        Node<T>* findPrev(const T& data) const;

        Node<T>* findNode(const T& data) const;

        void insertNode(Node<T>* prev, const T& data);

        void deleteNode(Node<T>* prevNode);

        void clear();

        bool isEmpty() const;

        size_t getSize() const;

        void print() const;
};

template <class T>
void LinkedList<T>::print() const{
    const Node<T>* node = head;
    while (node) {
        std::cout << node->getData();
        node = node->getNext();
    }
    cout<<std::endl;
}


template <class T>
LinkedList<T>::LinkedList(){
    head=NULL;
    tail=NULL;
    size=0;
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& ll){
	Node<T>  *traveller= ll.getHead();
	if(!traveller) return;
	Node<T> *copiedTraveller=new Node<T>(traveller->getData());
	this->setHead(copiedTraveller);

	while(traveller->getNext()){
		traveller=traveller->getNext();
		Node<T> *newNode = new Node<T>(traveller->getData());
		newNode->setNext(NULL);
		copiedTraveller->setNext(newNode);
		copiedTraveller=copiedTraveller->getNext();
	    this->setTail(copiedTraveller);
	}
}

template <class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& ll){
	if(this==&ll) return *this;

	this->clear();
	Node<T>  *traveller= ll.getHead();
    if(!traveller) return *this;
    Node<T> *copiedTraveller=new Node<T>(traveller->getData());
    this->setHead(copiedTraveller);

    while(traveller->getNext()){
        traveller=traveller->getNext();
        Node<T> *newNode = new Node<T>(traveller->getData());
        newNode->setNext(NULL);
        copiedTraveller->setNext(newNode);
        copiedTraveller=copiedTraveller->getNext();
        this->setTail(copiedTraveller);
    }
	return *this;
}

template <class T>
LinkedList<T>::~LinkedList(){
    this->clear();
}

template <class T>
Node<T>* LinkedList<T>::getHead() const{
    return this->head;
}

template <class T>
Node<T>* LinkedList<T>::setHead(Node<T>* n){
    
    head=n;

    return head;
}

template <class T>
Node<T>* LinkedList<T>::getTail() const{
    return this->tail;
}

template <class T>
Node<T>* LinkedList<T>::setTail(Node<T>* n){
    n->setNext(NULL);
    this->tail=n;
    return tail;
}

template <class T>
Node<T>* LinkedList<T>::findPrev(const T& data) const{
    if(head->getData()==data){
        return NULL;
    }
    Node<T> *front,*back;
    front=head->getNext();
    back=head;
    while(front){
        if(front->getData()==data){
            return back;
        }
        front=front->getNext();
        back=back->getNext();
    }
    return NULL;
}

template <class T>
Node<T>* LinkedList<T>::findNode(const T& data) const{
    Node<T> *searcher=head;

    while(searcher){
        
        if(searcher->getData()==data){
            return searcher;
        }
    	searcher=searcher->getNext();
    }
    return NULL;
}

template <class T>
void LinkedList<T>::insertNode(Node<T>* prev, const T& data){
    if(prev==NULL){
    	Node<T> *newNode = new Node<T>(data);
   	newNode->setNext(this->getHead());
	this->setHead(newNode);
	
	Node<T> *searcher=this->head;
	while(searcher->getNext()){
	    searcher=searcher->getNext();
	}
	this->setTail(searcher);
	(this->size)+=1;
	return;
    }   
    Node<T> *newNode = new Node<T>(data);
    newNode->setNext(prev->getNext());
    prev->setNext(newNode);
    Node<T> *searcher = this->head;
    while(searcher->getNext()){
        searcher=searcher->getNext();
    }
    this->setTail(searcher);
    (this->size)+=1;
}

template <class T>
void LinkedList<T>::deleteNode(Node<T>* prevNode){
    if(prevNode && !findNode(prevNode->getData())) return ; 
    if(prevNode && findNode(prevNode->getData())==this->getTail()) return; 
    if(prevNode==NULL){
        Node<T> *tmp=this->getHead();
        this->setHead(tmp->getNext());
        delete tmp;
        (this->size)-=1;
        return;
    }
    Node<T> *tmp=prevNode->getNext();
    prevNode->setNext(prevNode->getNext()->getNext());
    tmp->setNext(NULL);
    delete tmp;
    Node<T> *searcher=this->head;
    while(searcher->getNext()) searcher=searcher->getNext();
    this->setTail(searcher);
    (this->size)-=1;
}

template <class T>
void LinkedList<T>::clear(){
    if(!this->head) return;
    Node<T> *back=head;
    while(head){
        head=head->getNext();
        delete back;
        back=head;
    }
    this->head=NULL;
    this->tail=NULL;
    this->size=0;
}

template <class T>
bool LinkedList<T>::isEmpty() const{
    if(!head){
        return true;
    }
    return false;
}

template <class T>
size_t LinkedList<T>::getSize() const{
    return this->size;
}



#endif
