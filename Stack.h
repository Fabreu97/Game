#ifndef INCLUDED_STACK_H
#define INCLUDED_STACK_H

#include "List.h"

template<class TS> class Stack {
private:
    List<TS> s;
public:
    Stack  () : s() {}
    ~Stack () {}

    void push (TS* element) { s.insertList(element); }
    void pop  () { s.pop(); }
    TS* front () { return s.front(); }
    TS* back  () { return s.back(); }
    const bool empty () const { return s.empty(); }
};

#endif // INCLUDED_STACK_H
