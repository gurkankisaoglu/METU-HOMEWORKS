#ifndef _PLAYLIST_H_
#define _PLAYLIST_H_

#include <string>
#include "LinkedList.hpp"
#include "Entry.hpp"
#include "HistoryRecord.hpp"
#include "MyStack.hpp"


class Playlist {
private:
	LinkedList<Entry> entries;	
	MyStack< HistoryRecord > history; 

	int getRandomNumber(int i, int n) const; 
public:	
	Playlist();

	void load(std::string fileName);

	void insertEntry(const Entry &e); 
	
	void deleteEntry(const std::string &_title);

	void moveLeft(const std::string &title); 

	void moveRight(const std::string &title);

	void reverse(); 

	void sort(); 

	void merge(const Playlist & pl); 

	void shuffle(); 

	void undo(); 

	void print();

	void printHistory();
};



#endif

