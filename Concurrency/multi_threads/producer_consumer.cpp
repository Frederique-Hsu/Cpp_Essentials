/*!
 *  \file       producer_consumer.cpp
 *  \brief
 *
 */


#include "producer_consumer.hpp"

Producer::Producer(Sync_queue<Message>& q) : tail{q}
{
}

Consumer::Consumer(Sync_queue<Message>& q) : head{q}
{
}

Message Consumer::operator()()
{
    return head.get();
}

void Producer::operator()(const Message& mesg)
{
    tail.put(mesg);
}
