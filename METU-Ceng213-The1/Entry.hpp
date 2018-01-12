#ifndef _ENTRY_H_
#define _ENTRY_H_

#include <cstdlib>
#include <iostream>
#include <string>

class Entry {
private:
	std::string title;
	std::string genre;
	std::string year;
public:
	Entry();  

	Entry(std::string _title, std::string _genre="", std::string _year="");

	std::string getTitle() const;
	
	std::string getGenre() const;

	std::string getYear() const;

	bool operator==(const Entry & rhs) const; 
        
	friend std::ostream &operator<<(std::ostream &out, const Entry& t);
};


#endif
