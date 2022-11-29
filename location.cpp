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
		std::cout << "wwdwdwdwd " << std::endl;
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

void Location::parser_la_location(int j)
{
	_methods.push_back("");
	_methods.push_back("");
	_methods.push_back("");
	std::string str;
	for (int i = 10; res[j][i] != ' '; i++){
		str += res[j][i];
	}
	this->_location = str;
	j++;
	_autoindex = false;
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
		else
		{
			std::cout << "error parsing location" << std::endl;
			exit (1);
		}
		j++;
	}
	std::cout << "\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\" << std::endl;
	std::cout << "location : " << _location << std::endl; 
	std::cout << "root : " << this->_root << std::endl; 
	std::cout << "index : " << _index << std::endl; 
	for (std::vector<std::string>::iterator it = _methods.begin(); it != _methods.end(); it++){
		//std::cout << "qwjdqggggggggggggggggggggggggggggggggggwd" << std::endl;
		std::cout << *it << std::endl;
	} 
	std::cout << "\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\" << std::endl;

}