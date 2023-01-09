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
	this->vectorenv.push_back((char *)"PATH_INFO=./html/upload.php");
	this->vectorenv.push_back((char *)"PATH_TRANSLATED=./html/upload.php");
	this->vectorenv.push_back((char *)"PATH_NAME=./html/upload.php");
	this->vectorenv.push_back((char *)"SCRIPT_NAME=./html/upload.php");
	this->vectorenv.push_back((char *)"SCRIPT_FILENAME=./html/upload.php");
	char	**cmd = new char*[3];
	cmd[0] = new char[16];
	cmd[0] = (char *)"/usr/bin/php-cgi";
	cmd[1] = new char[16];
	cmd[1] = (char *)("./html/upload.php");
	cmd[2] = new char[1];
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
	//std::string skip = "Status: 500 Internal Server Error\n";
	//skip += "Content-type: text/html; charset=UTF-8 ";
	//str1 = str1.substr(skip.length(), str1.length());
	delete [] cmd;
	//std::cerr << "STR11111111111111 ---> " << str1 << std::endl;
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
	char	**cmd = new char*[3];
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
	freeTab2(recup);
	std::string str1 = fileToString("lucieCGI");
	std::string skip = "Content-type: text/html; charset=UTF-8 ";
	str1 = str1.substr(skip.length(), str1.length());
	free(cmd[0]);
	free(cmd[1]);
	delete [] cmd;
	return (str1);
}

std::string	Server::execGETpy(void)
{
	int fd1;
	this->vectorenv.push_back((char *)("REQUEST_METHOD=GET"));
	this->vectorenv.push_back((char *)"PATH_INFO=./html/py/post.py");
	this->vectorenv.push_back((char *)"PATH_TRANSLATED=./html/py/post.py");
	this->vectorenv.push_back((char *)"PATH_NAME=./html/py/post.py");
	this->vectorenv.push_back((char *)"SCRIPT_NAME=./html/py/post.py");
	this->vectorenv.push_back((char *)"SCRIPT_FILENAME=./html/py/post.py");
	char	**cmd = new char*[3];
	cmd[0] = new char[16];
	cmd[0] = (char *)"/usr/bin/python";
	cmd[1] = new char[13];
	cmd[1] = (char *)("./html/py/post.py");
	cmd[2] = new char[1];
	cmd[2] = 0;
	int i = 0 ;
	char **recup = ft_split(this->newIndex.c_str(), '?');
	i = 0;
	while (recup[i])
	{
		if (strncmp(recup[i], "f_name", 6) == 0)
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
		execve(cmd[0], cmd, this->env);
	}
	else
		wait(NULL);
	std::string str1 = fileToString("lucieCGI");
	std::string skip = "Content-type:text/html";
	str1 = str1.substr(skip.length(), str1.length());
	delete [] cmd;
	return (str1);
}
