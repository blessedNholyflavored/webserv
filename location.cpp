#include "location.hpp"
#include "inc.hpp"

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
			if (*it == "GET")
				_GET = true;
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
	//
	// SI TARRIVE A CREER UN VECTOR DE 3 STRING DANS TON HPP CA VA FONCTIONNER 
	// JUSTE CPLUSPLUS.COM NE FONCTIONNE PAS LA MAIS SINON TON LOCATION DEVRAIT ETRE BON
	//

}
void Location::parseRoot(std::string str){
	int i = 0;
	while ( str[i] == ' ' || str[i] == '\t')
		i++;
	while ( str[i] != ' ' && str[i] != '\t')
		i++;
	while ( str[i] == ' ' || str[i] == '\t')
		i++;
	std::cout << &str[i] << std::endl;
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

void Location::parser_la_location(int j)
{
	_methods.push_back("");
	_methods.push_back("");
	_methods.push_back("");
	std::string str;
	this->_scale = false;
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
	if (_root + _location == "/scale/")
		_scale = true;
	// std::cout << "\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\" << std::endl;
	// std::cout << "location : " << _location << std::endl; 
	// std::cout << "root : " << this->_root << std::endl; 
	// std::cout << "index : " << _index << std::endl; 
	// for (std::vector<std::string>::iterator it = _methods.begin(); it != _methods.end(); it++){
	// 	std::cout << *it << std::endl;
	// } 
	// std::cout << "\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\" << std::endl;

}

std::string Location::getLocation() { return (this->_location); }

std::string Location::getRoot() { return (this->_root); }

bool		Location::getScale() { return (this->_scale); }

bool		Location::getGet() { return (this->_GET); }

bool		Location::getDel() { return (this->_DELETE); }

bool		Location::getPost() { return (this->_POST); }
