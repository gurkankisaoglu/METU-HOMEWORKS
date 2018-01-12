#ifndef _title_h__
#define _title_h__

#include "book.hpp"
#include <cstring>

class TitleComparator
{
  public:
    bool operator( ) (const Book::SecondaryKey & key1, 
                      const Book::SecondaryKey & key2) const
    {	
    	std::string str1(key1.getTitle());
    	std::string str2(key2.getTitle());
    	for(size_t i=0 ;i<str1.size() ; i++){
    		if(str1[i]>=65 && str1[i]<=90) {
    			str1[i]+=32;
    		}
    	}
    	for(size_t i=0 ;i<str2.size() ; i++){
    		if(str2[i]>=65 && str2[i]<=90) {
    			str2[i]+=32;
    		}
    	}
    	if(str1!=str2){
    		return str1<str2;
    	}else{
    		std::string str3(key1.getAuthor());
    		std::string str4(key2.getAuthor());
    		for(size_t i=0 ; i<str3.size() ; i++){
    	    	if(str3[i]>=65 && str3[i]<=90) {
    	    		str3[i]+=32;
    	    	}
    		}
    		for(size_t i=0 ; i<str4.size() ; i++){
    			if(str4[i]>=65 && str4[i]<=90) {
    			    str4[i]+=32;
    	    	}
    		}
    		return str3<str4;
    	}
    }
};

#endif
