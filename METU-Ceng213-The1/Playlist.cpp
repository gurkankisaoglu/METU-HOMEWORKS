#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Playlist.hpp"
#include "Entry.hpp"

using namespace std;


Playlist::Playlist()
{
    srand(15);
}

int Playlist::getRandomNumber(int i, int n) const
{
    int range=n-i;
    int random = rand() % range + i;
    return random;
}

void Playlist::print()
{
    cout << "[PLAYLIST SIZE=" << entries.getSize() <<"]";
    entries.print();
}
void Playlist::printHistory()
{
    cout<<"[HISTORY]";
    history.print();
}

void swapNodes( LinkedList<Entry> & ll, int x , int y){

	if(x==y) return;


	Node<Entry> *prevX=NULL;
	Node<Entry> *currX=ll.getHead();
	for(int t=0 ; t<x ; t++){
			prevX=currX;
			currX=currX->getNext();
	}

	Node<Entry> *prevY=NULL;
	Node<Entry> *currY=ll.getHead();
	for(int t=0 ; t<y ; t++){
			prevY=currY;
			currY=currY->getNext();
	}

	
	if(prevX != NULL){
       prevX->setNext(currY);
	}
   	else{ 
       ll.setHead(currY);  
 	}

  	if(prevY != NULL){
       prevY->setNext(currX);
	}
   	else{
       ll.setHead(currX);  
 	}
   
    Node<Entry> *temp = currY->getNext();
    currY->setNext(currX->getNext());
    currX->setNext(temp);
   	Node<Entry> *setter=ll.getHead();
	while(setter->getNext()) setter=setter->getNext();
	ll.setTail(setter);
	
}

void Playlist::load(std::string fileName){
	ifstream file;
	file.open(fileName.c_str());
	string line;
	char delim=';';
	int pos=0;
	int counter=1;
	string title,genre,year;
	while(file.good()){
		counter=1;
		getline(file,line);
		while((pos=line.find(delim))!=string::npos){
			if(counter==1) title=line.substr(0,pos);
			if(counter==2) genre=line.substr(0,pos);
			if(counter==3) year=line.substr(0,pos);
			counter++;
			line.erase(0,pos+1);
		}
		year=line;
		Entry e(title,genre,year);
		this->insertEntry(e);
	}

}


void Playlist::insertEntry(const Entry &e){
	HistoryRecord hist(INSERT,e);
	history.push(hist);

	this->entries.insertNode(this->entries.getTail(),e);

}



void Playlist::deleteEntry(const std::string &_title){
	Node<Entry>*searcher=this->entries.getHead();
	Node<Entry>*prev=NULL;
	int flag=0;
	
	while(searcher){
		if(searcher->getData().getTitle()==_title){
		    flag++;
			break;
		}
		prev=searcher;
		searcher=searcher->getNext();
	}
	if(prev==NULL && flag){
	    HistoryRecord hist(DELETE,this->entries.getHead()->getData());
	    history.push(hist);
        this->entries.deleteNode(NULL);
	}else if(flag){
	    HistoryRecord hist(DELETE,searcher->getData());
	    history.push(hist);
	    this->entries.deleteNode(prev);
	}
}



void Playlist::moveLeft(const std::string &title){
	Node<Entry> *searcher=this->entries.getHead();
	Node<Entry> *prev=NULL;
	Node<Entry> *prev2=NULL;
	while(searcher){
		prev2=prev;
		prev=searcher;
		searcher=searcher->getNext();
		if(searcher && searcher->getData().getTitle()==title && prev==this->entries.getHead()){
			prev->setNext(searcher->getNext());
			searcher->setNext(prev);
			this->entries.setHead(searcher);
			return;
		}
		if(searcher && searcher->getData().getTitle()==title){
			prev2->setNext(searcher);
			prev->setNext(searcher->getNext());
			searcher->setNext(prev);
		}
	}
	Node<Entry> *setter=this->entries.getHead();
	while(setter->getNext()){
		setter=setter->getNext();
	}
	this->entries.setTail(setter);
}

void Playlist::moveRight(const std::string &title){
	Node<Entry> *searcher=this->entries.getHead();
	int i=0;
	if(this->entries.getTail()->getData().getTitle()==title) return;
	while(searcher){
		if(searcher->getData().getTitle()==title){
			i++;
			break;
		}
		searcher=searcher->getNext();
	}
	if(!i) return;
	this->moveLeft(searcher->getNext()->getData().getTitle());
}


void Playlist::reverse(){
	HistoryRecord hist(REVERSE);
	history.push(hist);
	Node<Entry> *current=this->entries.getHead();
	Node<Entry> *prev=NULL;
	Node<Entry> *next;

	while(current){
		next=current->getNext();
		current->setNext(prev);
		prev=current;
		current=next;
	}
	this->entries.setHead(prev);
	Node<Entry> *setter=this->entries.getHead();
	while(setter->getNext()){
		setter=setter->getNext();
	}
	this->entries.setTail(setter);
}

void Playlist::sort(){

	Node<Entry> *ptr1=this->entries.getHead();
	Node<Entry> *min,*ptr2;
	int i,j,minIndex;

	for(i = 0 , ptr1; ptr1 && ptr1->getNext() ; i++ , ptr1=ptr1->getNext()){
		
		minIndex=i;
		min=ptr1;
		
		for(j=i+1 ,ptr2=ptr1->getNext() ; ptr2 ;j++,  ptr2=ptr2->getNext()){
			if(ptr2->getData().getTitle() < min->getData().getTitle()){
				min=ptr2;
				minIndex=j;
			}
			
		}

		if(min!=ptr1){
			swapNodes(this->entries,i,minIndex);		
		}
		ptr1=min;
	}
} 

void Playlist::merge(const Playlist & pl){
	Node<Entry> *list2=pl.entries.getHead();
    Node<Entry> *list1=this->entries.getHead();
	while(list2 ){
	    Entry e(list2->getData().getTitle(),list2->getData().getGenre(),list2->getData().getYear());
	    while(list1){
	        if(e.getTitle() < list1->getData().getTitle()){
	            Node<Entry> *prev=this->entries.findPrev(list1->getData());
	            this->entries.insertNode(prev,e);
	            break;
	        }
	        list1=list1->getNext();
	    }
	    list2=list2->getNext();
		if(!list1)break;
	}
	while(list2){
        Entry e(list2->getData().getTitle(),list2->getData().getGenre(),list2->getData().getYear());
        this->entries.insertNode(this->entries.getTail(),e);
        list2=list2->getNext();
	}
}



void Playlist::shuffle(){
	int j;
	for(int i=0 ; i<this->entries.getSize()-1 ; i++){
		j=getRandomNumber(i, this->entries.getSize());
		swapNodes(this->entries,i,j);
	}
}

void Playlist::undo(){
	Node<HistoryRecord> *hist=history.Top();
	history.pop();
	switch(hist->getData().getOperation()){
		case 0:
			this->deleteEntry(hist->getData().getEntry().getTitle());
			history.pop();
			break;
		case 1:
			this->insertEntry(hist->getData().getEntry());
			history.pop();
			break;
		case 2:
			this->reverse();
			history.pop();
			break;
		default:
			break;
	}
}
