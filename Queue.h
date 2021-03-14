#ifndef INCLUDED_QUEUE_H
#define INCLUDED_QUEUE_H

#include "List.h"

template <class TQ> class Queue : public List<TQ> {
public:
    Queue()  {}
    ~Queue() {}

    void enqueue (TQ* data) { this->insertList(data); }
    void dequeue () { this->deleteData(0lu); }
};

#endif // INCLUDED_QUEUE_H
