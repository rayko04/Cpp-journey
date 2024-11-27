#include <iostream>

int getInteger()
{
    int x{};

    std::cout << "Value: ";
    std::cin >> x;

    return x;
}

char getOp()
{
    char op{};
    do
    {
        std::cout << "Operation (symbol): ";
        std::cin >> op;
    }
    while(op != '+' && op != '-' && op != '*' && op != '/');

    return op;
}

int add(int x, int y)
{
    return x+y;
}

int sub(int x, int y)
{
    return x-y;
}

int mult(int x, int y)
{
    return x*y;
}

int divi(int x, int y)
{
    return x/y;
}

using ArithmeticFunction = int(*)(int, int);
//using ArithmeticFunction = std::function<int(int, int)>;  // in functional header

ArithmeticFunction getArithmeticFunction(char op)
{
    switch (op)
    {
        case '+': return &add;
        case '-': return &sub;
        case '*': return &mult;
        case '/': return &divi;
    }

    return nullptr;
}

int main()
{
    int x{getInteger()}, y{getInteger()};
    char op{getOp()};

    ArithmeticFunction funcPtr {getArithmeticFunction(op)};
    if(funcPtr)
    {
        int result{ funcPtr(x, y)};
        std::cout << result;
    }
    else
    {
        std::cout << "invalid";
    }

    return 0;
}
