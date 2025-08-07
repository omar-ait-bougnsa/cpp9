
#ifndef BitcoinExchange_hpp
#define BitcoinExchange_hpp
#include <iostream>
#include <exception>
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <map>
class BitcoinExchange
{
    private:
        int day;
        int month;
        int year;
        double Bitcoin;
        int date_input;
        // std::string *date;
        std::map<std::string, double> Map;
    public :
        void    parsing_line(std::string line);
        void    validate_bitcoin_value(std::string str);
        void	processData(std::ifstream &file);
        int    parse_data_line(std::string line);
        std::string    parseInputData(std::string dataStr);
        int    parsing_date(std::string datafile);
        BitcoinExchange();
};
int	is_intger(std::string str);
std::string *split(std::string line, char target);
#endif