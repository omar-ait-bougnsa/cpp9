#include <iostream>
#include <stack>
#include <exception>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <string>

int  solve(std::string str)
{
    std::stringstream ss(str);
    std::string word;
    int number;
    std::stack <int> Stack;
    char *end;
    while (ss >> word)
    {
        if (word == "*" || word == "-" || word == "+" || word == "/")
        {
            if (Stack.size() < 2)
                throw std::logic_error("Error: too few values before operator");
            int b = Stack.top();
            Stack.pop ();
            int a = Stack.top();
            Stack.pop ();
            if (word == "+")
                Stack.push(a + b);
            else if (word == "/")
                Stack.push(a / b);
            else if (word == "*")
                Stack.push(a * b);
            else if (word == "-")
                Stack.push(a - b);
        }
        else
        {
            number = std::strtol(word.c_str(), &end, 10);
            if (end[0] != '\0')
                throw std::logic_error ("Error : must just entiger");
            if (number >= 10)
                throw std::logic_error ("input numbers must less then 10");
            Stack.push(number);
        }
    }
    if (Stack.size() != 1)
        throw std::logic_error ("Error logic");
    return Stack.top();
    
}
int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cerr << "just tow args\n";
        return 0;
       // std::cerr << "arguments must less than 10" <<std::endl;
    }
    try
    {
        std::cout << solve(av[1]);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    

}
