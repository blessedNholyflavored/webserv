/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkhamlac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:07:18 by lkhamlac          #+#    #+#             */
/*   Updated: 2023/01/11 14:07:25 by lkhamlac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/location.hpp"
#include "includes/inc.hpp"

Location::Location() 
{
	
}

Location::~Location()
{

}


std::vector<std::string> ft_split2(std::string str, std::string deli)
{
	std::vector<std::string> res;

		int start = 0;
		int end = str.find(deli);
		int     i = 0;
		while (end != -1)
		{
				res.push_back(str.substr(start, end - start));
				start = end + deli.size();
				end = str.find(deli, start);
				i++;
		}
		res.push_back(str.substr(start, end - start));
		return (res);
}

int	checkEndOfLocation(std::string str){
	for (int i = 0; str[i]; i++){
		if (str[i] == '}')
			return 0;
	}
	return (1);
}

void Location::parseMethod(std::string str){
	int i = 0;
	this->_methods.reserve(10);
	while ( str[i] == ' ' || str[i] == '\t'){
		i++;
	}
	while (str[i] != ' ' && str[i] != '\t' && str[i] != '\0'){
		i++;
	}
	while ( str[i] == ' ' || str[i] == '\t'){
		i++;
	}
	std::string tmp;
	for (std::vector<std::string>::iterator it = _methods.begin();; i++){
		if (str[i] == ' ' || str[i] == '\t' || str[i] == '\0')
		{
			*it = tmp;
			if (*it == "GET"){
				_GET = true;
			}
			else if (*it == "DELETE")
				_DELETE = true;
			else if (*it == "POST")
				_POST = true;
			else {
				std::cout << "error location parsing" << std::endl;
				exit (1);
			}
			it++;
			tmp.clear();
			while(str[i] == ' ' || str[i] == '\t')
				i++;
			if (str[i])
				i--;
		}
		else
			tmp += str[i];
		if (!str[i])
			break ;
	}
}

void Location::parseRoot(std::string str){
	int i = 0;
	while ( str[i] == ' ' || str[i] == '\t')
		i++;
	while ( str[i] != ' ' && str[i] != '\t')
		i++;
	while ( str[i] == ' ' || str[i] == '\t')
		i++;
	std::string tmp;
	for (; str[i]; i++){
		tmp += str[i];
	}
	this->_root = tmp;
}

void Location::parseIndex(std::string str){
	int i = 0;
	while ( str[i] == ' ' || str[i] == '\t')
		i++;
	while ( str[i] != ' ' && str[i] != '\t')
		i++;
	while ( str[i] == ' ' || str[i] == '\t')
		i++;
	std::string tmp;
	for(;str[i]; i++){
		tmp += str[i];
	}
	this->_index = tmp;
}

void Location::parseReturn(std::string str){
	int i = 0;
	while ( str[i] == ' ' || str[i] == '\t')
		i++;
	while ( str[i] != ' ' && str[i] != '\t')
		i++;
	while ( str[i] == ' ' || str[i] == '\t')
		i++;
	std::string tmp;
	for (; str[i]; i++){
		tmp += str[i];
	}
	this->_return = tmp;
}

void Location::parseAutoindex(std::string str){
	int i = 0;
	while ( str[i] == ' ' || str[i] == '\t')
		i++;
	while ( str[i] != ' ' && str[i] != '\t')
		i++;
	while ( str[i] == ' ' || str[i] == '\t')
		i++;
	if (str.find("on")){
		_autoindex = true;
	}
	
}

bool isspace_string(const std::string& s)
{
	for (std::string::const_iterator it = s.begin(); it != s.end(); it++)
	{
		if (!std::isspace(*it))
			return false;
	}
	return true;
}

int Location::parser_la_location(int j)
{
	_methods.push_back("");
	_methods.push_back("");
	_methods.push_back("");
	std::string str;
	this->_defaut = false;
	for (int i = 10; res[j][i] != ' '; i++){
		str += res[j][i];
	}
	this->_location = str;
	j++;
	_autoindex = false;
	_GET = false;
	_DELETE = false;
	_POST = false;
	while (checkEndOfLocation(res[j])){
		if(res[j].find("root") != std::string::npos)
			parseRoot(res[j]);
		else if (res[j].find("allow") != std::string::npos)
			parseMethod(res[j]);
		else if (res[j].find("autoindex") != std::string::npos)
			parseAutoindex(res[j]);
		else if(res[j].find("index") != std::string::npos)
			parseIndex(res[j]);
		else if(res[j].find("return") != std::string::npos)
			parseReturn(res[j]);
		else if (isspace_string(res[j]))
		{
			j++;
			continue;
		}
		else
		{
			std::cout << "error parsing location" << std::endl;
			exit (1);
		}
		j++;
	}
	std::cout << _root + _location << std::endl;
	if (_root + _location == "//"){
		this->_defaut = true;
	}
	return j;
}

std::string Location::getLocation() { return (this->_location); }

std::string Location::getRoot() { return (this->_root); }

std::string Location::getIndex() { return (this->_index); }

bool		Location::getDefaut() { return (this->_defaut); }

bool		Location::getGet() { return (this->_GET); }

bool		Location::getDel() { return (this->_DELETE); }

bool		Location::getPost() { return (this->_POST); }

bool		Location::getAuto() { return (this->_autoindex); }
