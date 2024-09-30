#include <iostream>

struct student
{
    std::string name;
    double gpa;
    bool enrolled = true;
};

int main()
{
    student student1;
    student1.name = 'Spongebob';
    student1.gpa = 3.2;

    std::cout << student1.name << '\n';
    std::cout << student1.gpa << '\n';
    std::cout << student1.enrolled << '\n';
}