#include <iostream>
#include <string>

struct Test
{
    static std::string name()
    {
        return "Test";
    }
};

int main()
{

    Test test_1;
    Test test_2;

    std::cout << test_1.name() << '\n';
    std::cout << test_2.name();

    return 0;
}