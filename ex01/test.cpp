#include <iostream>
#include <new>
#include <vector>
#include <stack>
#include <algorithm>
class MinStack {
    private :
        std::stack<int> a,min;
    public:
        MinStack()
        {
            
        }
        void push(int val)
        {
            if(min.empty())
            min.push(val);
            a.push(val);
            if (a.top())
        }
        void pop()
        {
            if ()
            a.pop();
        }
        int top()
        {
            return a.top();
        }
        int getMin()
        {
        }
    };
int main ()
{
    //Input: ["MinStack", "push", 1, "push", 2, "push", 0, "getMin", "pop", "top", "getMin"]

    //Output: [null,null,null,null,0,null,2,1]
    
    //Explanation:
    MinStack minStack;
    minStack.push(1);
    minStack.push(2);
    minStack.push(0);
    std::cout <<minStack.getMin(); // return 0
    minStack.pop();
    minStack.top();    // return 2
   std::cout << minStack.getMin(); // return 1
    return (0);
}
    ;