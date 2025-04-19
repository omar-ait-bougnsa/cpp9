#include <iostream>
#include <vector>

std::vector <int> ft_parsing(char **av)
{
    int i = 0;
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
std::vector <std::pair<int, int> > sort(std::vector<int> value)
{
    std::vector <int>::iterator it = value.begin();
    std::pair<int, int> Pair;
    std::vector <std::pair<int, int> > v;
    while (it < value.end())
    {
        v.push_back(std::make_pair(*it, *(it + 1)));
        it +=2;
    }
    return v;
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
    v1 = sort (v);



}