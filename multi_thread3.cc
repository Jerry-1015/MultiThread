#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>

std::mutex mtx1;
std::mutex mtx2;

// 不能使用拷贝构造
std::atomic<int> global_variable(0);

// int global_variable = 0;

// std::lock_guard
// std::unique_lock
// std::scoped_lock

void task1() {
    for (int i = 0; i < 1000000; ++i) {
        global_variable++;
        global_variable--;
    }
}

int main() {
    std::thread t1(task1);
    std::thread t2(task1);

    t1.join();
    t2.join();

    std::cout << "current value is: " << global_variable << std::endl;
}