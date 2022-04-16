#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <deque>
#include <condition_variable>

std::mutex mtx;
std::deque<int> q;

std::condition_variable cv;

// producer
void task1() {
    int i = 0;
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);

        q.push_back(i);

        cv.notify_one();
        // cv.notify_all(); //唤醒所有
        // std::this_thread::sleep_for(std::chrono::microseconds(10));
        if (i < 99999999) {
            i++;
        } else {
            i = 0;
        }
    }
}

// consumer 1
void task2() {
    int data = 0;
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);

        while (q.empty()) {
            cv.wait(lock);
            // lock.unlock();
            // cv.wait();
        }

        data = q.front();
        q.pop_front();
        std::cout << "Get value from que:" << data << std::endl;

        // std::this_thread::sleep_for(std::chrono::microseconds(10));

    }
}

// consumer 2
void task3() {
    int data = 0;
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);

        while (q.empty()) {
            cv.wait(lock);
            // lock.unlock();
            // cv.wait();
        }

        
        data = q.front();
        q.pop_front();
        std::cout << "Get value from que:" << data << std::endl;

        // std::this_thread::sleep_for(std::chrono::microseconds(10));

    }
}

int main() {
    std::thread t1(task1);
    std::thread t2(task2);
    std::thread t3(task3);


    t1.join();
    t2.join();
    t3.join();
}