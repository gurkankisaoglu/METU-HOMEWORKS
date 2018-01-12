#ifndef _HISTORY_RECORD_H_
#define _HISTORY_RECORD_H_
#include "Entry.hpp"
#include "MyStack.hpp"

enum Operation
{
	INSERT,
	DELETE,
	REVERSE,
};

class HistoryRecord 
{
private:
	Entry entry;
	Operation operation;
	
public:

	HistoryRecord();

	HistoryRecord(Operation oper, Entry e=Entry());

	Operation getOperation() const;

	Entry getEntry() const;


	friend std::ostream &operator<<(std::ostream &out, const HistoryRecord& t);
};

#endif
