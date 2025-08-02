#include "PmergeMe.hpp"

template <typename T>
T ft_parsing(char **av)
{
    int i = 1;
    char * check;
    int value;
    std::string str;
    T v;
    while (av[i])
    {
        str = av[i];
        value = std::strtold(av[i],&check);
        if (check[0] != '\0' || value < 0 )
            throw (std::logic_error("Error"));
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
    if (ac < 2)
    {
        std::cout << "error : at least two argument\n";
        return 0;
    }
    try
    {   
        v = ft_parsing<std::vector<int> >(av);
        std::cout <<"Before: ";
        ft_print(v);
        clock_t start = clock();
        v = sort_vector(v);
        double Time = static_cast<double>(std::clock() - start) / CLOCKS_PER_SEC * 1000;
        std::cout <<"after: ";
        ft_print(v);
        std::cout << std::fixed << "Time to process a range of " << v.size() <<" elements with std::vector "<<Time <<std::endl;
        d = ft_parsing<std::deque<int> >(av);
        start = clock();
        d = sort_deque(d);
        double Time1 = static_cast<double>(std::clock() - start) / CLOCKS_PER_SEC * 1000;
        std::cout <<"Time to process a range of " << v.size() <<" elements with std::deque  "<<Time1<< std::fixed <<std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}