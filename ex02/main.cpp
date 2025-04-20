#include <iostream>
#include <vector>
#include <cstdlib>

std::vector <int> ft_parsing(char **av)
{
    int i = 1;
    char * check;
    int value;
    std::vector <int> v;
    while (av[i])
    {
        value = std::strtold(av[i],&check);
        if (check[0] != '\0')
        {
            v.push_back (-1);
            return (v);
        }
        else
            v.push_back (value);
        i++;
    }
    return v;
}
void swap(int &a,int &b)
{
    int p;
    p = a;
    a = b;
    b = p;
}
std::vector <int> sort(std::vector<int> value)
{
    if (value.size() < 4)
        return value;
    std::vector <int>::iterator it = value.begin();
    std::pair<int, int> Pair;
    std::vector <std::pair<int, int> > v;
    while (it != value.end())
    {
        int a = *it;
        ++it;
        if (it == value.end())
            break;
        int b = *it;
        v.push_back(std::make_pair(a, b));
        ++it;
    }
    std::vector <std::pair<int, int> >::iterator it1 = v.begin();
    std::vector <int> large;
    std::vector <int> lower;
    while (it1 != v.end())
    {
        if (it1->first < it1->second)
            swap(it1->first,it1->second);
        large.push_back(it1->first);
        lower.push_back(it1->second);
        it1++;
    }
    sort(large);
    
    
    // merge_sort()
    //return v;
}
int main(int ac, char **av)
{
    std::vector<int> v;
    std::vector <std::pair<int, int> > v1;
    if (ac == 1)
    {
        std::cout << "error : at least two argument\n";
        return 0;
    }
    v = ft_parsing(av);
    v = sort (v);
    
}