#include <iostream>
#include <thread>

void func(int a) {
     {
        // std::cout << "hello world!" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    
    }
}

int main() {
    int a = 0;
    std::thread thread1(func, a);


    std::cout << "the thread id is :" << thread1.get_id() << std::endl;
    std::cout << "support num is " << thread1.hardware_concurrency();
    // 第一种方法  子线程执行完毕才会执行下面代码

    thread1.join(); 
    

    // 第二种方法  两个线程分离开 尽量少用 保证没有悬空指针
    // thread1.detach();

    // while (true) {
    //     std::cout << "Cat !\n";
    //     std::this_thread::sleep_for(std::chrono::milliseconds(50));
    // }
    //while (true);
}