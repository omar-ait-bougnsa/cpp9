
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
        int date_input;
        std::string *date;
    public :
        void    parsing_line(std::string line,std::map<int, double> Map);
        void    validate_bitcoin_value(std::string str);
        void	processData(std::ifstream &file);
        void    parse_data_line(std::string line, std::map<int, double> &Map);
        void    parsing_date();
        BitcoinExchange();
};
int	is_intger(std::string str);
std::string *split(std::string line, char target);
#endif