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

std::vector<int> Jacobsthal_sequence(int n)
{
    std::vector<int> jacob;
    jacob.push_back (0);
    jacob.push_back (1);
    while (jacob.back() < n)
    {
        int next = jacob.back() + 2 * jacob[jacob.size() - 2];
        jacob.push_back(next);
    }

    // std::vector <int>::iterator it = jacob.begin ();
    // while (it != jacob.end())
    // {
    //     std::cout << *it <<" ";
    //     it++;
    // }
    // std::cout <<std::endl;
     return jacob;
}
std::vector<int> sort(std::vector<int> value)
{
    if (value.size() <= 1)
        return value;
    std::vector<std::pair<int, int> > pairs;
    int odd_element;
    int has_odd = 0;
    if (value.size() % 2 != 0)
    {
        has_odd = 1;
        odd_element = value.back();
    }
    for (size_t i = 0; i < value.size() - has_odd; i += 2)
    {
        if (value[i] < value[i + 1])
        pairs.push_back(std::make_pair(value[i + 1], value[i]));
    else
        pairs.push_back(std::make_pair(value[i], value[i + 1]));
    }

    std::vector<int> larger;
    std::vector<int> pend;
    std::vector<std::pair<int, int> >::iterator it = pairs.begin();
    while (it != pairs.end())
    {
        larger.push_back(it->first);
        pend.push_back(it->second);
        std::cout << "first = "<< it->first <<" second = " << it->second <<std::endl;
        it++;
    }
    larger = sort(larger);
    std::vector<int> jacob = Jacobsthal_sequence(pend.size());

    size_t inserted = 0;
    for (size_t k = 0; k < jacob.size(); ++k)
    {
        int start = 0;
        if (k != 0)
            start = jacob[k - 1];
        int end = jacob[k];
        for (int i = end; i > start; --i)
        {
            if (i - 1 < pend.size())
            {
                std::vector<int>::iterator pos =std::lower_bound(larger.begin(), larger.end(), pend[i - 1]);
                larger.insert(pos, pend[i - 1]);
                inserted++;
            }
        }
    }

    if (has_odd)
    {
        std::vector<int>::iterator pos = std::lower_bound(larger.begin(), larger.end(), odd_element);
        larger.insert(pos, odd_element);
    }

    return larger;
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
    std::vector <int>::iterator it = v.begin ();
    while (it != v.end())
    {
        std::cout << *it <<"-";
        it++;
    }
}