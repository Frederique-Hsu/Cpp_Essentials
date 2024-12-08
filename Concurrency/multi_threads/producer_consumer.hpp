/*!
 *  \file       producer_consumer.hpp
 *  \brief      Define a Producer & Consumer model.
 *
 */



#pragma once

#include <queue>
#include <string>

/* Decalaration ==================================================================================*/
template<typename T>
class Sync_queue
{
private:
    std::queue<T> message_queue;
public:
    void put(const T& message);
    T get();
};

struct Message
{
    /* Define you message fields here */
    std::string name;
    int         salary;
};

class Consumer
{
public:
    Consumer(Sync_queue<Message>& q);
    Message operator()();
private:
    Sync_queue<Message>& head;
};

class Producer
{
public:
    Producer(Sync_queue<Message>& q);
    void operator()(const Message& mesg);
private:
    Sync_queue<Message>& tail;
};


/* Implementation ================================================================================*/
template<typename T> void Sync_queue<T>::put(const T& message)
{
    message_queue.push(message);
}

template<typename T> T Sync_queue<T>::get()
{
    T message = message_queue.front();
    message_queue.pop();
    return message;
}
