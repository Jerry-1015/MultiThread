#include <iostream>
#include <thread>
using namespace std;

void func(int a) {
    cout << "hello world!" << endl;
    this_thread::sleep_for(chrono::milliseconds(50));
}

int main() {
    int a = 0;
    cout << "hello" << endl;
    thread thread1(func, a);

    while (true);
}