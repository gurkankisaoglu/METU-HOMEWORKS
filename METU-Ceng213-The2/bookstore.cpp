#include "bookstore.hpp"

BookStore::BookStore( ) //implemented, do not change
{
}

void
BookStore::insert(const Book & book)
{
  primaryIndex.insert(book.getISBN(),book);
  Book::SecondaryKey Skey(book.getTitle(),book.getAuthor());
  BSTP::Iterator it=primaryIndex.find(book.getISBN());
  secondaryIndex.insert(Skey,&*it);
  ternaryIndex.insert(Skey,&*it);

}

void
BookStore::remove(const std::string & isbn)
{
  BSTP::Iterator it=primaryIndex.find(isbn);
  if(it == primaryIndex.end()) return;
  Book::SecondaryKey Skey(*it);
  ternaryIndex.remove(Skey);
  secondaryIndex.remove(Skey);
  primaryIndex.remove(isbn);
}


void
BookStore::remove(const std::string & title,
                  const std::string & author)
{
  Book::SecondaryKey Skey(title,author);
  BSTT::Iterator it=ternaryIndex.find(Skey);
  if(it==ternaryIndex.end()) return;
  std::string isbn=(*(*it)).getISBN();
  primaryIndex.remove(isbn);
  secondaryIndex.remove(Skey);
  ternaryIndex.remove(Skey);

}

void
BookStore::removeAllBooksWithTitle(const std::string & title)
{
  std::list<std::string> deleted;
  BSTT::Iterator it=ternaryIndex.begin();
  while(it!=ternaryIndex.end()){
    std::string title2=(*it)->getTitle();

    for(size_t i=0 ; i<title2.size() ; i++){
      if(title2[i]<=90 && title2[i]>=65) title2[i]+=32;
    }
    if(title2==title) deleted.push_back((*it)->getISBN());

    ++it;
  }
  while(!deleted.empty()){
    this->remove(deleted.front());
    deleted.pop_front();
  }
}

void
BookStore::makeAvailable(const std::string & isbn)
{
  BSTP::Iterator it=primaryIndex.find(isbn);
  if(it!=primaryIndex.end()) {
    (*it).setAvailable();
    Book::SecondaryKey Skey((*it).getTitle(),(*it).getAuthor());
  

    BSTT::Iterator it3=ternaryIndex.find(Skey);
    if(it3!=ternaryIndex.end()) (*it3)->setAvailable();
  }
}

void
BookStore::makeUnavailable(const std::string & title,
                           const std::string & author)
{
  Book::SecondaryKey Skey(title,author);
  BSTT::Iterator it=ternaryIndex.find(Skey);
  std::string isbn;
  if(it!=ternaryIndex.end()){
    (*it)->setUnavailable();
    isbn=(*(*it)).getISBN();
  }
  BSTP::Iterator it2=primaryIndex.find(isbn);
  if(it2!=primaryIndex.end()) (*it2).setUnavailable();
  
}

void
BookStore::updatePublisher(const std::string & author, 
                           const std::string & publisher)
{
  BSTT::Iterator it=ternaryIndex.begin();
  std::string str1(author);
  for(size_t i = 0; i< str1.size(); i++){
    if(str1[i]>=65 && str1[i]<=90){
      str1[i]+=32;
    }
  }

  while(it!=ternaryIndex.end()){
    std::string str2((*(*it)).getAuthor());
    for(size_t i=0 ; i<str2.size() ; i++){
      if(str2[i]>=65 && str2[i]<=90){
        str2[i]+=32;
      }
    }

    if(!str1.compare(str2)){
      (*(*it)).setPublisher(publisher);
    }
    ++it;
  }
}

void
BookStore::printBooksWithISBN(const std::string & isbn1,
                              const std::string & isbn2,
                              unsigned short since) const
{
  std::list<BSTP::Iterator> list=primaryIndex.find(isbn1,isbn2);

  while(!list.empty()){
    if(since <= (*(list.front())).getYear()){

      std::cout << *(list.front()) << std::endl;
    }
    
    list.pop_front();
  }
}

void
BookStore::printBooksOfAuthor(const std::string & author,
                              const std::string & first,
                              const std::string & last) const
{
    SKey key1(first,author);
    SKey key2(last,author);
    std::list<BSTS::Iterator> list=secondaryIndex.find(key1,key2);
    while(!list.empty()){
        std::cout << *(*(list.front())) << std::endl;
        list.pop_front();
    }
}

void 
BookStore::printPrimarySorted( ) const
{
  BSTP::Iterator it;

  for (it=primaryIndex.begin(); it != primaryIndex.end(); ++it)
  {
    std::cout << *it << std::endl;
  }
}

void 
BookStore::printSecondarySorted( ) const
{
  BSTS::Iterator it;

  for (it = secondaryIndex.begin(); it != secondaryIndex.end(); ++it)
  {
    std::cout << *(*it) << std::endl;
  }
}

void 
BookStore::printTernarySorted( ) const
{
  BSTT::Iterator it;

  for (it = ternaryIndex.begin(); it != ternaryIndex.end(); ++it)
  {
    std::cout << *(*it) << std::endl;
  }
}

