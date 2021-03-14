#ifndef INCLUDED_QUEUE_PROJECTILE_H
#define INCLUDED_QUEUE_PROJECTILE_H

#include "Queue.h"
#include "Projectile.h"

class QueueProjectile {
private:
    Queue<ent::cha::Projectile> munition;

public:
    QueueProjectile();
    ~QueueProjectile();

    const unsigned long int getSize () const { return ( munition.getSize() ); }
    void enqueue (ent::cha::Projectile* p) { munition.enqueue(p); }
    void dequeue () { return munition.dequeue(); }
    ent::cha::Projectile* front () { return ( munition.front() ); }
    ent::cha::Projectile* back () { return  ( munition.back() ); }
    ent::cha::Projectile* operator [] (const unsigned long int i) { return ( munition[i] ); }
    void Draw () {


    }
    void Update () {}

};

#endif // INCLUDED_QUEUE_PROJECTILE_H
