/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkhamlac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:00:40 by lkhamlac          #+#    #+#             */
/*   Updated: 2023/01/11 14:00:44 by lkhamlac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
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
#include <sys/socket.h>
#include <netinet/in.h>
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
	struct sockaddr_in addrstruct;
	std::string					root;
	std::string					cwd;
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
	Location		loc;
	char **env;
	Request						*request;
	std::string			newIndex;

	int							epoll_fd;
	int							server_fd;
	
	std::string FirstPage(std::string filePath);
	int	sendConnection(int fd);
	int	recvConnection(int fd);
	int	newConnection(struct epoll_event event, int fd);
	int	init_serv();
	int	event_receptor(struct epoll_event events[5], int event_count);
	int parser_le_server(std::string res[], size_t nbligne, int j, int max);
	int parser(std::string str);
	void	parsLoc(int i);
	void transfer_location(Location location);
	bool autoindexed() const;
	void CheckRequest(char *buffer, int fd, int ret);
	void splitString(const char *buf, std::string deli, int fd, int ret, std::string buffer);
	std::string	execFile(std::string file);
	std::string	execFile_py(std::string file);
	std::string     execPOST(void);
	std::string     execGET(void);
	std::string	recupHeader(int ret, std::string index);
	std::string	execGETpy(void);
	char    **ft_regroup_envVector(std::vector<char *> vec);
	std::string basicsummary( std::string filePath);


};

size_t countEndl(std::string content);
#endif
