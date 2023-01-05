#include <iostream>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <sys/wait.h>
#include <fstream>
#include <fcntl.h>
#include <dirent.h>
#include <vector>
#include "server.hpp"
#include "functions.h"
#include <cmath>


std::string	Server::execGET(void)
{
	int fd1;
	this->vectorenv.push_back((char *)("REQUEST_METHOD=GET"));
	this->vectorenv.push_back((char *)"PATH_INFO=./html/upload_img.php");
	this->vectorenv.push_back((char *)"PATH_TRANSLATED=./html/upload_img.php");
	this->vectorenv.push_back((char *)"PATH_NAME=./html/upload_img.php");
	this->vectorenv.push_back((char *)"SCRIPT_NAME=./html/upload_img.php");
	this->vectorenv.push_back((char *)"SCRIPT_FILENAME=./html/upload_img.php");
	char	**cmd = (char **)malloc(3);;
	cmd[0] = strdup("/usr/bin/php-cgi");
	cmd[1] = strdup("./html/upload_img.php");
	cmd[2] = 0;
	int i = 0 ;
	char **recup = ft_split(this->newIndex.c_str(), '?');
	i = 0;
	while (recup[i])
	{
		if (strncmp(recup[i], "fileToUpload", 12) == 0)
			break ;
		i++;
	}
	int tmp = open(".tmp", O_CREAT | O_WRONLY | O_TRUNC, 0666);
	write(tmp, recup[i], ft_strlen(recup[i]));
	lseek(tmp, 0, SEEK_SET);
	fd1 = open("lucieCGI", O_CREAT | O_RDONLY | O_WRONLY | O_TRUNC, 0666);
	std::string len = "CONTENT_LENGTH=" + intToString(ft_strlen(recup[i]));
	std::string res = recup[i];
	std::string query = "QUERY_STRING=" + res;
	this->vectorenv.push_back((char *)query.c_str());
	this->vectorenv.push_back((char *)len.c_str());
	this->env =  ft_regroup_envVector(this->vectorenv);
	int frk = fork();
	if (frk == 0)
	{
		dup2(tmp, 0);
		close(tmp);
		dup2(fd1, 1);
		close(fd1);
		execve("/usr/bin/php-cgi", cmd, this->env);
	}
	else
		wait(NULL);
	std::string str1 = fileToString("lucieCGI");
	//std::string skip = "Content-type: text/html; charset=UTF-8 ";
	//str1 = str1.substr(skip.length(), str1.length());
	return (str1);
}

std::string	Server::execPOST(void)
{
	int fd1;
	this->vectorenv.push_back((char *)("REQUEST_METHOD=GET"));
	this->vectorenv.push_back((char *)"PATH_INFO=./reponse.php");
	this->vectorenv.push_back((char *)"PATH_TRANSLATED=./reponse.php");
	this->vectorenv.push_back((char *)"PATH_NAME=./reponse.php");
	this->vectorenv.push_back((char *)"SCRIPT_NAME=./reponse.php");
	this->vectorenv.push_back((char *)"SCRIPT_FILENAME=./reponse.php");
	char	**cmd = (char **)malloc(3);;
	cmd[0] = strdup("/usr/bin/php-cgi");
	cmd[1] = strdup("./reponse.php");
	cmd[2] = 0;
	int i = 0 ;
	char **recup = ft_split(this->newIndex.c_str(), '?');
	i = 0;
	while (recup[i])
	{
		if (strncmp(recup[i], "fname", 5) == 0)
			break ;
		i++;
	}
	int tmp = open(".tmp", O_CREAT | O_WRONLY | O_TRUNC, 0666);
	write(tmp, recup[i], ft_strlen(recup[i]));
	lseek(tmp, 0, SEEK_SET);
	fd1 = open("lucieCGI", O_CREAT | O_RDONLY | O_WRONLY | O_TRUNC, 0666);
	std::string len = "CONTENT_LENGTH=" + intToString(ft_strlen(recup[i]));
	std::string res = recup[i];
	std::string query = "QUERY_STRING=" + res;
	this->vectorenv.push_back((char *)query.c_str());
	this->vectorenv.push_back((char *)len.c_str());
	this->env =  ft_regroup_envVector(this->vectorenv);
	int frk = fork();
	if (frk == 0)
	{
		dup2(tmp, 0);
		close(tmp);
		dup2(fd1, 1);
		close(fd1);
		execve("/usr/bin/php-cgi", cmd, this->env);
	}
	else
		wait(NULL);
	std::string str1 = fileToString("lucieCGI");
	std::string skip = "Content-type: text/html; charset=UTF-8 ";
	str1 = str1.substr(skip.length(), str1.length());
	return (str1);
}