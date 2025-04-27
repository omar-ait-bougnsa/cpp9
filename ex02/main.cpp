#include "PmergeMe.hpp"

template <typename T>
T ft_parsing(char **av)
{
    int i = 1;
    char * check;
    int value;
    T v;
    while (av[i])
    {
        value = std::strtold(av[i],&check);
        if (check[0] != '\0' || value < 0)
            throw (std::logic_error("error"));
        else
            v.push_back (value);
        i++;
    }
    return v;
}
void ft_print(std::vector<int> v)
{
    std::vector<int>::iterator it = v.begin();
    while (it != v.end())
    {
        std::cout << *it << " ";
        it++;
    }
    std::cout <<std::endl;
}
int main(int ac, char **av)
{
    std::vector<int> v;
    std::deque<int> d;
    std::vector <std::pair<int, int> > v1;
    if (ac == 1)
    {
        std::cout << "error : at least two argument\n";
        return 0;
    }
    try
    {
        v = ft_parsing<std::vector<int> >(av);
        std::cout <<"Before: ";
        ft_print(v);
        time_t Time = time(NULL);
        v = sort_vector(v);
        long n = Time - time(NULL);
        std::cout <<"after: ";
        ft_print(v);
        std::cout <<n <<std::endl;
        d = ft_parsing<std::deque<int> >(av);
        Time = time(NULL);
        d = sort_deque(d);
        n = Time - time(NULL);
        std::cout <<n<< std::fixed <<std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}