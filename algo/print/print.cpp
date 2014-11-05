#include <iostream>
using namespace std;

void print() {
    cout << endl;
}
template<typename T, typename ... Args>
void print(T t, Args ... args) {
    cout << t << " ";
    print(args...);
}

int main() {
    print(1, 2, "fds", 3);
}
