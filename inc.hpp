# include <iostream>
# include <fstream>
# include <sstream>
# include <string>
# include <cstdlib>
# include <unistd.h>
#include <vector>
# define WHITESPACES "; \t"

#ifndef INC_HPP
# define INC_HPP
class Server;
Server *parser_le_server(std::string res[], size_t *nbligne, int j);
void ft_split1(std::string str, std::string charset);
#endif