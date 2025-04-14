#include <iostream>
#include <stack>
#include <exception>
#include <vector>
class Solution 
{
public:
    int evalRPN(std::vector<std::string>& tokens)
    {
        std::stack<int> Stack;
        char *pos;
        std::vector<std::string>::iterator it = tokens.begin();
        while (it != tokens.end())
        {
            std::string str = *it;
            if (str == "*" || str == "-" || str == "+" || str == "/")
            {
                int b = Stack.top();
                Stack.pop ();
                int a = Stack.top();
                Stack.pop ();
                if (str == "+")
                    Stack.push(a + b);
                else if (str == "/")
                    Stack.push(a / b);
                else if (str == "*")
                    Stack.push(a * b);
                else if (str == "-")
                    Stack.push(a - b);
            }
            else
                Stack.push(std::strtold(str.c_str(),&pos));
            if (pos != '\0')
                throw std::logic_error ("error : must just entiger");
            it++;
        }
        if (Stack.size() != 1)
        throw std::logic_error ("error logic");
        return (Stack.top());
    }
};
int main()
{
    std::vector<std::string> b;
    Solution obj;
    b.push_back("10");
    b.push_back("6");
    b.push_back("-");
    try
    {
        std::cout << obj.evalRPN(b);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    

}
