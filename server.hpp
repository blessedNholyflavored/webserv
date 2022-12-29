# ifndef SERVER_HPP
# define SERVER_HPP
# include <iostream>
# include <fstream>
# include <sstream>
# include <string>
# include <cstdlib>
# include <cstring>
# include <unistd.h>
# include "location.hpp"
# include "parsing_request.hpp"
# include <vector>
# include "functions.h"
# define WHITESPACES "; \t"
struct s_list;

class Server
{
	private:
	public:
	Server();
	~Server();
	s_list *lst;
	std::vector<char *> vectorenv;
	std::vector<char *> vectorenvcpy;
	std::string					max_client_body_size;
	std::string					name_server;
	std::string					root;
	std::string 				ip;
	size_t						port;
	std::vector<std::string>	cgi_exec;
	std::vector<std::string>	cgi_address;
	std::string					index;
	std::vector<std::string>	error_page;
	std::vector<std::string>	error_name;
	bool						autoindex;
	std::vector<Location>		location;
	char **env;
	Request						*request;

	int							epoll_fd;
	int							server_fd;

	int	sendConnection(int fd);
	int	recvConnection(int fd);
	int	newConnection(struct epoll_event event, int fd);
	int	init_serv();
	int	event_receptor(struct epoll_event events[5], int event_count);
	int parser_le_server(std::string res[], size_t nbligne, int j);
	int parser(std::string str);
	void transfer_location(Location location);

};

size_t countEndl(std::string content);
#endif
