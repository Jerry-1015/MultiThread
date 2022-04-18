#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <deque>
#include <condition_variable>
#include <semaphore>

using namespace std;

// LeastMaxValue
std::counting_semaphore<3> csem(0);

std::binary_semaphore bsem(0);

// release notify
// acquire wait

void task() {

    std::cout << "ready to recv signal: acquire\n";

    csem.acquire();

    std::cout << "acquire end\n";
}

int main() {
    std::thread t0(task);
    std::thread t1(task);
    std::thread t2(task);
    std::thread t3(task);
    std::thread t4(task);
    std::cout << "ready to signal: release\n";

    csem.release(3 );

    std::cout << "signal end\n";

    t0.join();
    t1.join();
    t2.join();
    t3.join();
    t4.join();
}



