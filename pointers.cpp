#include <iostream>

int main()
{

    // pointers = variable that stores a memory address of another variable
    //            sometimes it's easier to work with an address

    // & address-of operator
    // * dereference operator

    std::string name = "Bro";
    int age = 21;
    std::string freePizzas[5] = {"pizza1", "pizza2", "pizza3", "pizza4", "pizza5"};

    std::string *pName = &name;
    int *pAge = &age;
    std::string *pFreePizzas = freePizzas;

    // p（假设p是一个指针）存储的是一个地址。
    // *p 访问的是指针 p 所指向的地址上的值。
    std::cout << pName << '\n';
    std::cout << *pName << '\n';
    std::cout << pAge << '\n';
    std::cout << *pAge << '\n';
    std::cout << pFreePizzas << '\n';
    // 訪問array[0]
    std::cout << *pFreePizzas << '\n';
    // 訪問array[1]
    std::cout << *(pFreePizzas + 1) << '\n';

    return 0;
}