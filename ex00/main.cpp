#include <algorithm>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <new>
#include <sstream>
// #include <string>
#include <map>
#include <vector>

std::string *split(std::string line, char target)
{
	size_t	pos;
	int		i;

	std::string token;
	std::stringstream ss(line);
	std::string *str = new std::string[5];
	pos = 1;
	i = 0;
	while (std::getline(ss, token, target))
	{
		if (i >= 5)
		{
			break ;
		}
		str[i] = token;
		i++;
	}
	return (str);
}

void	add_line_in_map(std::string line, std::map<int, double> *Map)
{
	size_t	pos;
	int		value;

	pos = line.find(',');
	std::string str = line.substr(0, pos);
	std::string *newstr = split(str, '-');
	value = atoi(newstr[0].c_str()) * 10000 + atoi(newstr[1].c_str()) * 100
		+ atoi(newstr[2].c_str());
	std::pair<int, double> Pair = std::pair<int, double>(value,
			std::atof(line.substr(pos + 1).c_str()));
	Map->insert(Pair);
	delete[] newstr;
}

int	lenth(std::string *str)
{
	int	i;

	i = 0;
	while (!str[i].empty())
	{
		i++;
	}
	return (i);
}

int	is_intger(std::string str)
{
	int			i;
	char const	*s;

	i = 0;
	s = str.c_str();
	if (str.empty())
	{
		return (0);
	}
	while (s[i])
	{
		if (!isdigit(str[i]))
		{
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_is_valid(std::string *str)
{
	int		year;
	int		month;
	int		day;
	int		value;
	char	*pos;
	int		maxDay;

	if (str[1][0] != ' ' || str[0][str[0].length() - 1] != ' ')
		throw std::logic_error("Error: valide line must be 'Year-Month-Day | value' ");
	str[0].erase(str->size() - 1, 1);
	str[1].erase(0, 1);
	std::string *date = split(str[0], '-');
	if (lenth(date) != 3)
		throw std::logic_error("Error: valide date must be 'Year-Month-Day' ");
	if (!is_intger(date[0]) || !is_intger(date[1]) || !is_intger(date[2]))
		throw std::logic_error("Error: valide line must be 'Year-Month-Day | value' ");
	if (date[1].size() != 2 || date[2].size() != 2)
		throw std::logic_error("Error: month and day must two character");
	year = atoi(date[0].c_str());
	month = atoi(date[1].c_str());
	day = atoi(date[2].c_str());
	if (std::strtold(str[1].c_str(), &pos) > 1000 || *pos != '\0')
		throw std::logic_error("Error: too large a number.");
	if (atof(str[1].c_str()) <= 0)
		throw std::logic_error("Error: not a positive number.");
	if (month > 12)
		throw std::logic_error("Error: month => " + str[0]);
	if (month == 2)
	{
		maxDay = 28;
		if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))
			maxDay = 29;
	}
	else if (month == 4 || month == 6 || month == 11 || month == 9)
	{
		maxDay = 30;
	}
	else
		maxDay = 31;
	if (day > maxDay)
		throw std::logic_error("Error: this day is not in this month.");
	value = year * 10000 + month * 100 + day;
	return (value);
}
void	read_file(std::ifstream &file)
{
	double	date;
	std::ifstream data("data.csv");
	std::string line;
	std::string *str;
	std::string *newstr;
	std::map<int, double> Map;
	if (!data.is_open())
	{
		std::cout << "can't open file data.csv" << std::endl;
		return ;
	}
	while (std::getline(data, line))
	{
		add_line_in_map(line, &Map);
	}
	std::getline(file, line);
	if (line != "date | value")
	{
		std::cout << "error: first line must 'date | value'\n";
		return ;
	}
	while (std::getline(file, line))
	{
		str = split(line, '|');
		if (lenth(str) == 2)
		{
			try
			{
				date = check_is_valid(str);
				std::map<int, double>::iterator it = Map.begin();
				while (it != Map.end())
				{
					if (it->first == date)
					{
						std::cout << str[0] << " => " << str[1] << " = " << it->second * atoi(str[1].c_str()) << std::endl;
						break ;
					}
					else if (it->first > date)
					{
						it--;
						if (it == Map.begin())
							std::cout << "Error: this date doesn't have Bitcoin" << std::endl;
						else
							std::cout << str[0] << " => " << str[1] << " = " << it->second * atoi(str[1].c_str()) << std::endl;
						break ;
					}
					it++;
				}
			}
			catch (const std::exception &e)
			{
				std::cerr << e.what() << '\n';
			}
		}
	}
	delete[] str;
}
int	main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << "Error: could not open file.\n";
		return (0);
	}
	std::ifstream file(av[1]);
	if (!file.is_open())
	{
		std::cout << "can't open file\n";
	}
	read_file(file);
}