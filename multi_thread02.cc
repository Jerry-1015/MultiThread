#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx1;
std::mutex mtx2;

int global_variable = 0;

// class A {
//     A(std::mutex &mtx) {
//         mtx.lock();
//     }
//     ~A() {
//         mtx.unlock();
//     }
// };

void task1() {
    for (int i = 0; i < 1000000; ++i) {
        // 解决上锁但不解锁的问题
        // RAII(Resource Acquisition Is Initialization)
        // std::lock_guard<std::mutex> lock1(mtx1);
        // std::lock_guard<std::mutex> lock2(mtx2);

        // 实现中途解锁
        std::unique_lock<std::mutex> lock3(mtx1);

        lock3.unlock();
        // 保证上锁顺序一致
        std::lock(mtx1, mtx2);
        // mtx1.lock();
        // mtx2.lock();
        ++global_variable;
        --global_variable;

        // callAFUNC(); throw

        // if (1 == 1) {
        //     return;
        // }

        // mtx1.unlock();
        // mtx2.unlock();
    }
}

void task2() {
    for (int i = 0; i < 1000000; ++i) {
        std::lock(mtx1, mtx2);
        // mtx2.lock();
        // mtx1.lock();
        ++global_variable;
        --global_variable;

        // callAFUNC(); throw

        // if (1 == 1) {
        //     return;
        // }

        mtx2.unlock();
        mtx1.unlock();
    }
}



int main() {
    std::thread t1(task1);
    std::thread t2(task2);

    t1.join();
    t2.join();

    std::cout << "current value is: " << global_variable << std::endl;

}