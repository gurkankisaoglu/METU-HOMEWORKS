#include "HistoryRecord.hpp"

std::ostream & operator<<(std::ostream &out, const HistoryRecord& t){
    out <<"<";
    if (t.operation==INSERT) out <<"INSERT:";
    if (t.operation==DELETE) out <<"DELETE:";
    if (t.operation==REVERSE) out <<"REVERSE:";
    out << t.entry <<">";
    return out;
};

HistoryRecord::HistoryRecord(){
	
}

HistoryRecord::HistoryRecord(Operation oper, Entry e){

	this->entry=e;
	this->operation=oper;
}

Operation HistoryRecord::getOperation() const{
	return this->operation;
}



Entry HistoryRecord::getEntry() const{
	return this->entry;
}

