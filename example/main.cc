#include <iostream>
#include "urmem/urmem.hpp"

#ifdef _WIN32
#pragma optimize("", off)
#endif

#ifdef _WIN32
_declspec(noinline)
#endif
int
#ifdef _WIN32
__cdecl
#endif
Sum(int a, int b) {
    return a + b;
}

class Adder {
public:
    Adder(int a) : _a(a) {};
#ifdef _WIN32
    _declspec(noinline)
#endif
    int Sum(int b) {
        return _a + b;
    }
private:
    int _a{};
};

urmem::hook hook_sum, hook_adder_sum;

int MySum(int a, int b) {
    return hook_sum.call<urmem::calling_convention::cdeclcall, int>(a, b) * 2;
}

class Test {
public:
    static int
    #ifdef _WIN32
    __thiscall
    #endif
    MyAdder_Sum(void *_this, int b) {
        return hook_adder_sum.call<urmem::calling_convention::thiscall, int>(_this, b) * 10;
    }
};

int main() {
    // 1) Function
    hook_sum.install(urmem::get_func_addr(&Sum), urmem::get_func_addr(&MySum));

    std::cout << Sum(2, 3) << std::endl; // will print '10'

    // 2) Method
    Adder adder(10);

    hook_adder_sum.install(urmem::get_func_addr(&Adder::Sum), urmem::get_func_addr(&Test::MyAdder_Sum));

    std::cout << adder.Sum(10) << std::endl; // will print '200'

    return 0;
}
