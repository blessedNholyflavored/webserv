/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execFile.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 11:03:05 by jtaravel          #+#    #+#             */
/*   Updated: 2023/01/06 18:30:34 by jtaravel         ###   ########.fr       */
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
	char	**cmd = new char*[3];
	cmd[0] = new char[16];
	cmd[0] = (char *)"/usr/bin/php-cgi";
	cmd[1] = new char[file.length()];
	cmd[1] = (char *)file.c_str();
	cmd[2] = new char[1];
	cmd[2] = 0;
	this->vectorenv.push_back((char *)("REQUEST_METHOD=GET"));
	this->vectorenv.push_back((char *)("REQUEST_METHOD=POST"));
	std::string res = "PATH_INFO=" + file;
	this->vectorenv.push_back((char *)(res.c_str()));
	res.clear();
	res = "PATH_TRANSLATED=" + file;
	this->vectorenv.push_back((char *)(res.c_str()));
	res.clear();
	res = "PATH_NAME=" + file;
	this->vectorenv.push_back((char *)(res.c_str()));
	res.clear();
	res = "SCRIPT_NAME=" + file;
	this->vectorenv.push_back((char *)(res.c_str()));
	res.clear();
	res = "SCRIPT_FILENAME=" + file;
	this->vectorenv.push_back((char *)(res.c_str()));
	this->env = ft_regroup_envVector(this->vectorenv);
	std::string index;
	int frk = fork();
	if (frk == 0)
	{
		dup2(tmp, 0);
		close(tmp);
		dup2(lucie, 1);
		close(lucie);
		execve(cmd[0], cmd, this->env);
	}
	else
		wait(NULL);
	this->vectorenv.clear();
	this->vectorenv = this->vectorenvcpy;
	if (this->env)
		freeTab(this->env);
	this->env = NULL;
	std::string str1 = fileToString("lucieCGI");
	std::string skip = "Content-type: text/html; charset=UTF-8 ";
	str1 = str1.substr(skip.length(), str1.length());
	delete [] cmd;
	return str1;
}

std::string	Server::execFile_py(std::string file)
{
	std::cout << "RENTRERRRRR" << std::endl;
	std::cerr << "FILEEEEEEEEEEEE" << file << std::endl; 
	int tmp;
	std::string recup = file;
	tmp = open(recup.c_str(), O_RDONLY, 0644);
	int lucie = open("lucieCGI", O_CREAT | O_WRONLY | O_RDONLY | O_TRUNC, 0644);
	char	**cmd = new char*[3];
	cmd[0] = new char[16];
	cmd[0] = (char *)"/usr/bin/python";
	cmd[1] = new char[file.length()];
	cmd[1] = (char *)file.c_str();
	cmd[2] = new char[1];
	cmd[2] = 0;
	this->vectorenv.push_back((char *)("REQUEST_METHOD=GET"));
	this->vectorenv.push_back((char *)("REQUEST_METHOD=POST"));
	std::string res = "PATH_INFO=" + file;
	this->vectorenv.push_back((char *)(res.c_str()));
	res.clear();
	res = "PATH_TRANSLATED=" + file;
	this->vectorenv.push_back((char *)(res.c_str()));
	res.clear();
	res = "PATH_NAME=" + file;
	this->vectorenv.push_back((char *)(res.c_str()));
	res.clear();
	res = "SCRIPT_NAME=" + file;
	this->vectorenv.push_back((char *)(res.c_str()));
	res.clear();
	res = "SCRIPT_FILENAME=" + file;
	this->vectorenv.push_back((char *)(res.c_str()));
	this->env = ft_regroup_envVector(this->vectorenv);
	std::string index;
	int frk = fork();
	if (frk == 0)
	{
		dup2(tmp, 0);
		close(tmp);
		dup2(lucie, 1);
		close(lucie);
		execve(cmd[0], cmd, this->env);
	}
	else
		wait(NULL);
	this->vectorenv.clear();
	this->vectorenv = this->vectorenvcpy;
	if (this->env)
	freeTab(this->env);
		this->env = NULL;
	std::string str1 = fileToString("lucieCGI");
	std::string skip = "Content-type: text/html; charset=UTF-8 ";
	str1 = str1.substr(skip.length(), str1.length());
	std::cerr <<" SJOJOIHODW" << str1 << std::endl;
	delete [] cmd;
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
	return header;
}
