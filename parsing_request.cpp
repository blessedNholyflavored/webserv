/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_request.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkhamlac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:33:23 by lkhamlac          #+#    #+#             */
/*   Updated: 2023/01/11 15:33:24 by lkhamlac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
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
#include <cmath>
#include "includes/server.hpp"
#include "includes/functions.h"

int	alnum(std::string str)
{
	for (int i = 0; str[i]; i++)
	{
		if (!isascii(str[i]))
			return (0);
	}
	return  (1);
}

int	Request::parsRequest(std::string str, std::vector<Location> &location, Server server)
{
	std::string method;

	if (str.compare(0, 24, "------WebKitFormBoundary") == 0 || checkBuffBoundary(str) == 0 || !alnum(str))
		return (200);
	size_t i = 0;
	for (; str[i] != ' '; i++){
		method.push_back(str[i]);
	}
	_method = method;
	i++;
	
	std::string path;
	for (; str[i] != ' '; i++){
		path.push_back(str[i]);
	}
	_path = "." + path;

	i++;

	std::string version;
	for (; str[i] != '\r'; i++){
		version.push_back(str[i]);
	}

	int	flag = 0;
	int c = 0;
	int p = 0;
	Location tmp;
	std::vector<Location>::iterator it = location.begin();
        for (; it != location.end(); it++)
	{
		if (path == (*it).getLocation())
		{
			tmp = *it;
			flag = 1;
			break ;
		}
		else if (method == "DELETE" && (*it).getDel() == 0)
			c++;
		else if (method == "POST" && (*it).getPost() == 0)
			p++;
	}
	std::string conca = server.root + path;
	if (_path == "./")
		return 200;
	int fd1 = open(conca.c_str(), O_RDONLY);
	int fd2 = open(_path.c_str(), O_RDONLY);
	if ((!flag && fd1 == -1 && fd2 == -1)
		&& path.compare(0, 17, "/html/reponse.php") && path.compare(0, 21, "/html/upload_img.php")
		&& path.compare(0, 12, "/reponse.php")
		&& path.compare(0, 16, "/html/py/post.py")
		&& path.compare(0, 16, "/html/upload.php"))
	{
		close(fd1);
		close(fd2);
		this->_retCode = 404;
		return 404;
	}
	if (flag && method == "GET")
	{
		if (tmp.getGet() == 0)
		{
			this->_retCode = 405;
			return 405;
		}
	}
	if (flag && method == "DELETE")
	{
		if (tmp.getDel() == 0)
		{
			this->_retCode = 405;
			return 405;
		}
	}
	if (c == (int)location.size())
		return 405;
	//if (p == (int)location.size())
	//	return 405;
	if (flag && method == "POST")
	{
		if (tmp.getPost() == 0)
		{
			this->_retCode = 405;
			return 405;
		}
	}
	close(fd1);
	close(fd2);
	return (200);
}

std::string getLastSlash(std::string str){
	size_t len = str.length();
	while (str[len] != '/')
		len--;
	return (&str[len]);
	
}

void	Request::findGoodLocation(std::string str, std::vector<Location> &location){

	int		pos = 0;
	int 	bestPos = -1;
	int		countRetSlash = 9999;
	int		countTmp = -1;
	bool	isFind = false;

	for(std::vector<Location>::iterator it2 = location.begin(); it2 != location.end(); it2++){
		std::string tmpLoc = it2->getRoot() + it2->getLocation();
		if (tmpLoc == "//")
			tmpLoc = "/";
		countTmp = -1;
		int len = str.length() - 1;
		isFind = false;
		std::cout << "str  == "<< str << std::endl;
		while (str != "/"){
			if (countTmp >= 0)
				countTmp++;
			if (str == tmpLoc){
				isFind = true;
				break ;
			}
			else
				isFind  = false;
			while (str[len] != '/'){
				str.erase(str.length() - 1, 1);
				len--;
			}
			if (len > 0){
				str.erase(str.length() - 1, 1);
				len--;
			}
			if (countTmp == -1)
				countTmp = 0;
		}
		if (countTmp < countRetSlash && isFind){
			bestPos = pos;
			countRetSlash = countTmp;
		}
		pos++;
	}
	if (bestPos == -1){
		_it = location.begin();
		while ((!_it->getDefaut()) && (_it != location.end())) {
			_it++;
		}
		if (_it == location.end())
			_it --;
		return ;
	}
	else {
		_it = location.begin();
		for (int i = 0; i < bestPos; i++){
			_it++;
		}
		return ;
	}
}

int	Request::checkLocation(std::string str, int method, std::vector<Location> &location){
	findGoodLocation(str, location);
	if (method == 1){
		if (!(_it->getGet()))
			return (0);
	}
	else if (method == 2){
		if (_it->getDel() == false)
			return (0);
	}
	else{
		if (_it->getPost() == false)
			return (0);
	}
	return (1);
}

std::string Request::getMethod() const{ return (_method); }

std::string Request::getPath() const{ return (_path); }

int	Request::getRetCode() const{ return (_retCode); }
