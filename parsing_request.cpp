/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_request.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mmhaya <Mmhaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:30:29 by mmhaya            #+#    #+#             */
/*   Updated: 2022/12/18 14:49:20 by Mmhaya           ###   ########.fr       */
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
#include "parsing_request.hpp"

void	Request::parsRequest(std::string str, std::vector<Location> location){
	std::string method;
	size_t i = 0;
	for (; str[i] != ' '; i++){
		method.push_back(str[i]);
	}
	i++;
	
	std::string path;
	for (; str[i] != ' '; i++){
		path.push_back(str[i]);
	}
	i++;

	std::string version;
	for (; str[i] != '\n'; i++){
		version.push_back(str[i]);
	}

	if (version != "HTTP/1.0"){
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
		file.open(path, std::ifstream::in);
		if (!checkLocation(1)){
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
		file.open(path, std::ifstream::in);
		if (!checkLocation(2)){
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

int	Request::checkLocation(std::string str, int method, std::vector<Location> location){
	for(std::vector<Location>::iterator it; it != location.end(); it++){
		it->_
	}
}