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
	size_t port;
	std::vector<std::string> cgi_exec;
	std::vector<std::string> cgi_address;
	std::string index;

	std::vector<std::string> error_page;
	std::vector<std::string> error_name;

	int parser_le_server(std::string res[], size_t *nbligne, int j);
	int parser(std::string str);

};

#endif
