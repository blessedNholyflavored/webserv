/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_request.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkhamlac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:33:29 by lkhamlac          #+#    #+#             */
/*   Updated: 2023/01/11 15:33:29 by lkhamlac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_REQUEST_HPP
#define PARSING_REQUEST_HPP

class Server;

#include "server.hpp"
#include <string>

class Request {
	public:
		int								parsRequest(std::string str, std::vector<Location> &location, Server server);
		int								checkLocation(std::string str, int method, std::vector<Location> &location);
		void							findGoodLocation(std::string str, std::vector<Location> &location);
		int								getRetCode() const;
		std::string						getMethod() const;
		std::string						getPath() const;

	private:
		std::vector<Location>::iterator _it;
		std::string						_method;
		std::string					_path;
		int								_retCode;
};


#endif
