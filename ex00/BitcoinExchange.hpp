
#ifndef BitcoinExchange_hpp
#define BitcoinExchange_hpp
#include <iostream>
#include <exception>
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <map>
class BitcoinExchange
{
    private:
        int day;
        int month;
        int year;
        double Bitcoin;
        int date_number;
        std::string *date;
    public :
        void parsing_line(std::string line,std::map<int, double> Map);
        void  parsing_Bitcoin(std::string str);
        void parsing_date();
        BitcoinExchange();
};
int	is_intger(std::string str);
std::string *split(std::string line, char target);
#endif