/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execFile.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 11:03:05 by jtaravel          #+#    #+#             */
/*   Updated: 2023/01/04 19:01:17 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

std::string	Server::execFile(std::string file)
{
	int tmp;
	std::string recup = file;
	tmp = open(recup.c_str(), O_RDONLY, 0644);
	int lucie = open("lucieCGI", O_CREAT | O_WRONLY | O_RDONLY | O_TRUNC, 0644);
	char	**cmd = (char **)malloc(3);;
	cmd[0] = strdup("/usr/bin/php-cgi");
	cmd[1] = strdup(file.c_str());
	cmd[2] = 0;
	this->vectorenv.push_back((char *)("REQUEST_METHOD=GET"));
	this->vectorenv.push_back((char *)("REQUEST_METHOD=POST"));
	std::string res = "PATH_INFO=" + file;
	this->vectorenv.push_back((char *)(res.c_str()));
	res = "PATH_TRANSLATED=" + file;
	this->vectorenv.push_back((char *)(res.c_str()));
	res = "PATH_NAME=" + file;
	this->vectorenv.push_back((char *)(res.c_str()));
	res = "SCRIPT_NAME=" + file;
	this->vectorenv.push_back((char *)(res.c_str()));
	res = "SCRIPT_FILENAME=" + file;
	this->vectorenv.push_back((char *)(res.c_str()));
	this->env = ft_regroup_envVector(this->vectorenv);
	int frk = fork();
	if (frk == 0)
	{
		dup2(tmp, 0);
		close(tmp);
		dup2(lucie, 1);
		close(lucie);
		execve("/usr/bin/php-cgi", cmd, this->env);
	}
	else
		wait(NULL);
	this->vectorenv.clear();
	this->vectorenv = this->vectorenvcpy;
	std::string str1 = fileToString("lucieCGI");
	std::string skip = "Content-type: text/html; charset=UTF-8 ";
	str1 = str1.substr(skip.length(), str1.length());
	return str1;
}

std::string	Server::recupHeader(int ret, std::string index)
{
	std::string code;
	
	if (ret == 404)
		code = "Not Found";
	if (ret == 400)
		code = "Bad Request";
	if (ret == 403)
		code = "Forbidden";
	if (ret == 405)
		code = "Method Not Allowed";
	if (ret == 505)
		code = "HTTP Version Not Supported";

	std::string errorPage = "./html/" + intToString(ret) + ".html";
	errorPage = fileToString(errorPage);
	std::string header = "HTTP/1.1 " + intToString(ret) + code;
	header += "\nContent-type: text/html; charset=UTF-8\nContent-Length: ";
	header += intToString(errorPage.length()) + "\n\n" + errorPage + "\n";
	(void)index;
	std::cerr << "////////////////////////////////////////////////////////: " << header << std::endl;
	return header;
}
