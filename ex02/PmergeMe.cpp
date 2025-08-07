
#include "PmergeMe.hpp"

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
    return jacob;
}

std::vector<int> sort_vector(std::vector<int> value)
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
    std::vector<int> smaller;
    std::vector<std::pair<int, int> >::iterator it = pairs.begin();
    while (it != pairs.end())
    {
        larger.push_back(it->first);
        smaller.push_back(it->second);
        it++;
    }
    larger = sort_vector(larger);
    std::vector<int> jacob = Jacobsthal_sequence(smaller.size());

    for (size_t k = 0; k < jacob.size(); ++k)
    {
        int start = 0;
        if (k != 0)
            start = jacob[k - 1];
        int end = jacob[k];
        for (int i = end - 1; i >= start; --i)
        {
            if (i < static_cast<int>(smaller.size()))
            {
                std::vector<int>::iterator pos =std::lower_bound(larger.begin(), larger.end(), smaller[i]);
                larger.insert(pos, smaller[i]);
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

std::deque<int> Jacobsthal_sequence1(int n)
{
    std::deque<int> jacob;
    jacob.push_back (0);
    jacob.push_back (1);
    while (jacob.back() < n)
    {
        int next = jacob.back() + 2 * jacob[jacob.size() - 2];
        jacob.push_back(next);
    }
    return jacob;
}

std::deque<int> sort_deque(std::deque<int> value)
{
    if (value.size() <= 1)
        return value;
    std::deque<std::pair<int, int> > pairs;
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

    std::deque<int> larger;
    std::deque<int> smaller;
    std::deque<std::pair<int, int> >::iterator it = pairs.begin();
    while (it != pairs.end())
    {
        larger.push_back(it->first);
        smaller.push_back(it->second);
        it++;
    }
    larger = sort_deque(larger);
    std::deque<int> jacob = Jacobsthal_sequence1(smaller.size());

    for (size_t k = 0; k < jacob.size(); ++k)
    {
        int start = 0;
        if (k != 0)
            start = jacob[k - 1];
        int end = jacob[k];
        for (int i  = end - 1; i >= start; --i)
        {
            if (i < static_cast<int>(smaller.size()))
            {
                std::deque<int>::iterator pos =std::lower_bound(larger.begin(), larger.end(), smaller[i]);
                larger.insert(pos, smaller[i]);
            }
        }
    }

    if (has_odd)
    {
        std::deque<int>::iterator pos = std::lower_bound(larger.begin(), larger.end(), odd_element);
        larger.insert(pos, odd_element);
    }
    return larger;
}