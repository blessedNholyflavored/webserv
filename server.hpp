# include <iostream>
# include <fstream>
# include <sstream>
# include <string>
# include <cstdlib>
# include <unistd.h>
#include <vector>
# define WHITESPACES "; \t"
# ifndef SERVER_HPP
# define SERVER_HPP


class Server
{
	private:
	public:
	Server();
	~Server();
	size_t max_client_body_size;
	std::string name_server;
	std::string root;
	std::string ip;

	int parser_le_server(std::string res[], size_t *nbligne, int j);
	int parser(std::string str);

};

#endif
