#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <new>
// #include <string>
#include <vector>
#include <map>

// int check_valid(std::string line)
// {
    //     int year;
    //     int month;
    //     int day;
    //     int betcoin;
    //     int pos;
    //     try
    //     {
        //     pos = line.find('|');
        //     std::string str = line.substr(pos+ 1);
        //     betcoin = std::atoi(str.c_str());
        //     str = line.substr (0,pos);
        //     pos = str.find ('-');
        //     str = line.substr (pos + 1);
        //     day = std::atoi(str.c_str());
        //     str = line.substr (0,pos);
        //     pos = str.find ('-');
        //     str = line.substr (pos + 1);
        //     month = std::atoi(str.c_str());
        //     str = line.substr (0,pos);
        //     year = std::atoi(str.c_str());
        //     std::cout <<"std :"<<str <<"\n";
        // }
        // catch(const std::exception& e)
        // {
            //     std::cerr << e.what() << '\n';
            // }
            //     return (0);
            // }

std::string *split(std::string line,char target)
            {
    std::string token;
    std::stringstream ss(line);
    std::string *str = new std::string[5];
    size_t pos = 1;
     int i = 0;
    while (std::getline(ss,token,target))
    {
        if (i >= 5)
        {
            break;
        }
        str[i] = token;
        i++;
    }
    // while (pos - 1 != std::string::npos)
    // {

    //     pos =  line.find(target,pos);
    //     std::cout <<"pos = " <<pos <<std::endl;
    //     str[i]=line.substr(0,pos);
    //     pos += 1;
    //     line=line.substr(pos);
    //     std::cout <<line << " : line :" <<str[i] <<std::endl;
    //     i++;
    // }
    return (str);
}
void add_line_in_map(std::string line ,std::map<int,double> *Map)
{
     int pos;
     pos = line.find(',');
     std:: string str = line.substr(0,pos);
     std::string  *newstr = split(str,'-');
     int value = atoi(newstr[0].c_str()) * 10000 + atoi(newstr[1].c_str()) * 100 + atoi(newstr[2].c_str());
     Map->insert ({value,std::atof(line.substr(pos + 1).c_str())});
}
int lenth (std::string *str)
{
    int i = 0;
    while (!str[i].empty())
    {
        i++;
    }
    return (i);
}
int is_intger(std::string str)
{
    // int i = 0;
    // char const *s = str.c_str();
    // if (str.empty())
    // {
    //     return (0);
    // }
    // while (s[i])
    // {
    //     if(!isdigit(str[i]))
    //     {
    //         return (0);
    //     }
    //     i++;
    // }
    // return (1);
    return !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);
}
int check_is_valid (std::string *str)
{
    int year;
    int month;
    int day;
    int value;
     if (str[1].front() != ' ' || str[0].back() != ' ')
     {
        std::cout <<"Error: valide line must be 'Year-Month-Day | value' " <<std::endl;
        return (-1);
     }
    str[0].erase(str->size() -1,1);
    str[1].erase(0,1);
    std::string *date = split(str[0],'-');
   if (lenth (date) != 3)
   {
    std::cout <<"Error: valide date must be 'Year-Month-Day' " <<std::endl;
    return (0);
   }
   if (!is_intger (date[0]) || !is_intger (date[1]) || !is_intger (date[2]) || !is_intger (str[1]) )
   {
    std::cout <<"Error: valide line must be 'Year-Month-Day | value' " <<std::endl;
    return (-1);
   }
   if (date[1].size() != 2 || date[2].size() != 2)
   {
    std::cout <<"Error: month and day must two character" <<std::endl;
   }
    year = atoi (date[0].c_str());
    month = atoi (date[1].c_str());
    day = atoi (date[2].c_str());
    if (atof(str[1].c_str()) > 1000)
    {
        std::cout <<"Error: too large a number.\n";
        return (-1);
    }
    if (atof(str[1].c_str()) <= 0)
    {
        std::cout <<"Error: not a positive number.\n";
        return (-1);
    }
    if (month > 12)
    {
        std::cout <<"Error: month => " << str[0] <<std::endl;
        return (-1);
    }
    int maxDay;
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
      if(day > maxDay)
      {
        return (0);
      }
      value = year * 10000  + month * 100 + day;
      return (value);
}
void read_file(std::ifstream &file)
{
    std::ifstream data("data.csv");
    std::string line;
    std::string *str;
    std::string *newstr;
    std::map<int,double> Map;
    if (!data.is_open())
    {
        std::cout << "can't open file data.csv" <<std::endl;
        return;
    }
    while (std::getline(data,line))
    {
        add_line_in_map(line ,&Map);
    }
    while (std::getline(file,line))
    {
       str = split(line,'|');
       if (lenth(str) == 2)
       {
    double b = check_is_valid(str);
    std::map<int,double>::iterator it = Map.begin();
    while (it != Map.end() && b != -1) 
    {
        if (it->first == b)
        {
            std::cout <<str[0] << " => "<<str[1] << " = " << it->second * atoi(str[1].c_str()) <<std::endl;
            break;
        }
        else if (it->first > b)
        {
            it--;
            if (it == Map.begin())
                std::cout <<"Error: this date doesn't have Bitcoin" <<std::endl;
            else 
                std::cout <<str[0] << " => "<<str[1] << " = " << it->second * atoi(str[1].c_str()) <<std::endl;
            break;
        }
        // else 
        // {
        //   std::cout <<"Error in this date dosn't has Bitcoin" <<std::endl;
        //   break;
        // }
        it++;
    }
       }
    }
}
int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cout <<"Error: could not open file.\n";
        return (0);
    }
    std::ifstream file(av[1]);
    if (!file.is_open())
    {
        std::cout << "can't open file\n";
    }
    read_file(file);
}