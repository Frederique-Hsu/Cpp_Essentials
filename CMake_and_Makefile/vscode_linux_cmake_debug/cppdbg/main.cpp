/*!
 *  \file       main.cpp
 *  \brief      Learn how to debug the C++ program with VS Code in Linux environment.
 *  \author     Frederique Hsu
 *  \date       Wed.    21 Feb. 2024
 *  \copyright  2024    All rights reserved.
 *  
 */


#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>

static int rangeMax = 100;

std::mutex mutexForQueue;
std::queue<int> dataQueue;
std::condition_variable cv;

void producerThread();
void consumerThread();


int main(int argc, char* argv[])
{
    if (argc > 1)
    {
        rangeMax = std::stoi(argv[1]);
    }

    std::srand(std::time(NULL));

    std::thread producer(producerThread);
    std::thread consumer(consumerThread);

    producer.join();
    consumer.join();

    return 0;
}

void producerThread()
{
    while (true)
    {
        int randomNumber = std::rand() % rangeMax;
        {
            std::lock_guard<std::mutex> lock(mutexForQueue);
            dataQueue.push(randomNumber);
            std::cout << "Produced: " << randomNumber << std::endl;
        }

        cv.notify_one();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void consumerThread()
{
    while (true)
    {
        std::unique_lock<std::mutex> lock(mutexForQueue);

        cv.wait(lock, [](){ return !dataQueue.empty(); });
        int data = dataQueue.front();
        dataQueue.pop();

        std::cout << "Consumed: " << data << std::endl;

        lock.unlock();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}