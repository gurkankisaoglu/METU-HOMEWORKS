#ifndef MYSTACK_HPP
#define MYSTACK_HPP
#include "Node.hpp"

template <class T>
class MyStack{
    private:
    Node<T> *top;                
    public:

    MyStack();                     					

    MyStack(const MyStack<T>& rhs);  				

    ~MyStack(); 

    MyStack<T>& operator=(const MyStack<T>& rhs);  	

    bool isEmpty() const;

    void push(const T& newItem);

    void pop();

    Node<T>* Top() const;

    void print() const;
};

template <class T>
void MyStack<T>::print() const{
    const Node<T>* node = top;
    while (node) {
        std::cout << node->getData();
        node = node->getNext();
    }
    cout<<std::endl;
}


template <class T>
MyStack<T>::MyStack(){
	top=NULL;
}


template <class T>
MyStack<T>::MyStack(const MyStack<T>& rhs){
	*this=rhs;
}

template <class T>
MyStack<T>::~MyStack(){
	while(this->Top()){
		this->pop();	
	}
}

template <class T>
MyStack<T>& MyStack<T>::operator=(const MyStack<T>& rhs){
	if(this!=&rhs){
		while(!isEmpty()) this->pop();
		if(!rhs.top){
			this->top=NULL;
		}
		else{
			Node<T>* traveller=rhs.Top();
			Node<T>* copied= new Node<T>(traveller->getData());
			this->top=copied;
			while(traveller->getNext()){
				traveller=traveller->getNext();
				Node<T>* newItem = new Node<T>(traveller->getData());
				newItem->setNext(NULL);
				copied->setNext(newItem);
				copied=copied->getNext();
			}
			copied->setNext(NULL);
		}
	}
	return *this;
}

template <class T>
bool MyStack<T>::isEmpty() const{
	if(top){
		return false;
	}
    return true;
}

template <class T>
void MyStack<T>::push(const T& newItem){
   Node<T> *itemToPush = new Node<T>(newItem);
   itemToPush->setNext(top);
   top=itemToPush;
}

template <class T>
void MyStack<T>::pop(){
    if(!top) return;
	Node<T> *tmp=top;
	top=top->getNext();
	delete tmp;
}

template <class T>
Node<T>* MyStack<T>::Top() const{
	return this->top;
}

#endif 

