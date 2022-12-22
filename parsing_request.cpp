/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_request.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmhaya <mmhaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:30:29 by mmhaya            #+#    #+#             */
/*   Updated: 2022/12/22 18:36:32 by mmhaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmhaya <mmhaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 18:52:49 by mmhaya            #+#    #+#             */
/*   Updated: 2022/11/23 19:40:16 by mmhaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "server.hpp"

void	Request::parsRequest(std::string str, std::vector<Location> location){
		std::cout << "1-------------------------" << std::endl << str  << std::endl << "2----------------------" << std::endl;
	std::string method;
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
	_path = path;
	i++;

	std::string version;
	for (; str[i] != '\n'; i++){
		version.push_back(str[i]);
	}
 
	if (version != "HTTP/1.1"){
		// pour linstant je mets ca comme ca //
		std::cerr << "bad version" << std::endl;
		_retCode = 400;
		return ;
	}

	if (method != "GET" || method != "POST" || method != "DELETE")
	{
		std::cerr << "method didnt exist" << std::endl;
		_retCode = 400;
		return ;
	}
	
	path = "." + path;
	if (method == "GET"){
		std::ifstream file;
		file.open(path.c_str(), std::ifstream::in);
		if (!checkLocation(path, 1, location)){
			_retCode = 777;
			std::cout << "pas les droits" << std::endl;
			return ;
		}
		if (!file.is_open()){
			std::cerr << "Erreur 404, page not found" << std::endl;
			_retCode = 404;
			return ;
		}
		file.close();
	}
	else if (method == "DELETE"){
		std::ifstream file;
		file.open(path.c_str(), std::ifstream::in);
		if (!checkLocation(path, 2, location)){
			_retCode = 777;
			std::cout << "pas les droits" << std::endl;
			return ;
		}
		if (!file.is_open()){
			//revoir code de retour
			std::cerr << "cannot delete cause file not existing" << std::endl;
			_retCode = 404;
			return ;
		}
		file.close();
	}
	_retCode = 200;
	return ;
}
std::string getLastSlash(std::string str){
	size_t len = str.length();
	while (str[len] != '/')
		len--;
	return (&str[len]);
	
}

std::vector<Location>::iterator Request::findGoodLocation(std::string str, std::vector<Location> location){

	int		pos = 0;
	int 	bestPos = -1;
	int		countRetSlash = 9999;
	int		countTmp = -1;
	bool	isFind = false;

	str = "/scale" + str;
	if (str[str.length() - 1] == '/')
		str.erase(str.length(), 1);
	for(std::vector<Location>::iterator it = location.begin(); it != location.end(); it++){
		std::string tmpLoc = it->getRoot() + it->getLocation();
		if (tmpLoc[tmpLoc.length() - 1] == '/')
			str.erase(str.length(), 1);
		countTmp = -1;
		int len = str.length() - 1;
		while(str != "/scale"){
			if (countTmp >= 0)
				countTmp++;
			if (str == tmpLoc){
				isFind = true;
				break ;
			}
			else
				isFind  = false;
			while (str[len] != '/'){
				str.erase(str.length(), 1);
				len--;
			}
			str.erase(str.length(), 1);
			len--;
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
		std::vector<Location>::iterator it = location.begin();
		for (; it->getScale() == false; it++) {}
		return (it);
	}
	else {
		std::vector<Location>::iterator it = location.begin();
		for (int i = 0; i < bestPos; i++){
			it++;
		}
		return (it);
	}
}

int	Request::checkLocation(std::string str, int method, std::vector<Location> location){
	std::vector<Location>::iterator it = findGoodLocation(str, location);
	if (method == 1){
		if (it->getGet() == false)
			return (0);
	}
	else if (method == 2){
		if (it->getDel() == false)
			return (0);
	}
	else{
		if (it->getPost() == false)
			return (0);
	}
	return (1);
}

std::string Request::getMethod() const{ return (_method); }

std::string Request::getPath() const{ return (_path); }

int	Request::getRetCode() const{ return (_retCode); }