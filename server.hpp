# ifndef SERVER_HPP
# define SERVER_HPP
# include <iostream>
# include <fstream>
# include <sstream>
# include <string>
# include <cstdlib>
# include <cstring>
# include <dirent.h> 
# include <unistd.h>
# include "location.hpp"
# include "parsing_request.hpp"
# include <vector>
# include "functions.h"
#include <sys/types.h>
#include <sys/stat.h>
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
	std::vector<std::string>	vectorname_server;
	
	std::string					root;
	std::vector<std::string>	vectorroot;

	std::string 				ip;
	
	std::vector<std::string>	cgi_exec;
	std::vector<std::string>	cgi_address;
	
	std::string 				nom_index;
	std::vector<std::string>	index;

	std::vector<std::string>	error_page;
	std::vector<std::string>	error_name;
	
	int							port;
	std::vector<int>			nbport;
	
	std::vector<int>	vectorauto;
	int							autoindex;
	std::vector<Location>		location;
	char **env;
	Request						*request;
	std::string			newIndex;

	int							epoll_fd;
	int							server_fd;

	int	sendConnection(int fd);
	int	recvConnection(int fd);
	int	newConnection(struct epoll_event event, int fd);
	int	init_serv();
	int	event_receptor(struct epoll_event events[5], int event_count);
	int parser_le_server(std::string res[], size_t nbligne, int j);
	int parser(std::string str);
	void	parsLoc(int i);
	void transfer_location(Location location);
	bool autoindexed() const;
	void CheckRequest(char *buffer, int fd);
	void splitString(const char *buf, std::string deli, int fd);
};

size_t countEndl(std::string content);
#endif
