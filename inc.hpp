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
Server *parser_le_server(const std::vector<std::string> configfile, size_t *nbligne);

#endif