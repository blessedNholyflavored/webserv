#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "server.hpp"

void	Request::parsRequest(std::string str, std::vector<Location> location){
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
	_path = "." + path;
	i++;

	std::string version;
	for (; str[i] != '\r'; i++){
		version.push_back(str[i]);
	}
	if (version != "HTTP/1.1"){
		std::cerr << "bad version" << std::endl;
		_retCode = 400;
		return ;
	}

	if (method != "GET" && method != "POST" && method != "DELETE")
	{
		std::cerr << "method didnt exist" << std::endl;
		_retCode = 401;
		return ;
	}
	
	if (method == "GET"){
		std::ifstream file;
		if (!checkLocation(path, 1, location)){
			_retCode = 777;
			std::cout << "pas les droits" << std::endl;
			return ;
		}
		file.open(_path.c_str(), std::ifstream::in);
		if (!file.is_open()){
			_retCode = 404;
			return ;
		}
		file.close();
	}
	else if(method == "DELETE"){
		std::ifstream file;
		file.open(path.c_str(), std::ifstream::in);
		if (!checkLocation(path, 2, location)){
			_retCode = 777;
			std::cout << "pas les droits" << std::endl;
			return ;
		}
		if (!file.is_open()){
			std::cerr << "cannot delete cause file not existing" << std::endl;
			_retCode = 404;
			return ;
		}
		file.close();
	}
	else {
		if (!checkLocation(path, 3, location)){
			_retCode = 404;
			return ;
		}
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

void	Request::findGoodLocation(std::string str, std::vector<Location> location){

	int		pos = 0;
	int 	bestPos = -1;
	int		countRetSlash = 9999;
	int		countTmp = -1;
	bool	isFind = false;

	str = "/scale" + str;
	if (str[str.length() - 1] == '/')
		str.erase(str.length(), 1);
	for(std::vector<Location>::iterator it2 = location.begin(); it2 != location.end(); it2++){
		std::string tmpLoc = it2->getRoot() + it2->getLocation();
		if (tmpLoc[tmpLoc.length() - 1] == '/')
			str.erase(str.length() - 1, 1);
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
				str.erase(str.length() - 1, 1);
				len--;
			}
			str.erase(str.length() - 1, 1);
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
		_it = location.begin();
		for (; _it->getScale() == false; _it++) {
		}
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

int	Request::checkLocation(std::string str, int method, std::vector<Location> location){
	findGoodLocation(str, location);
	if (method == 1){
		if (_it->getGet() == false)
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