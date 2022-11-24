# include <iostream>
# include <fstream>
# include <sstream>
# include <string>
# include <cstdlib>
#include <cmath>
# include <unistd.h>
#include <vector>
# define WHITESPACES "; \t"

#ifndef INC_HPP
# define INC_HPP

extern std::string res[4096];


class Server;
class Location;

void ft_split1(std::string str, std::string charset);
std::string get_file( std::string file);
int check_int(std::string str);

#endif