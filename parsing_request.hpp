/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_request.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmhaya <mmhaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 22:36:55 by Mmhaya            #+#    #+#             */
/*   Updated: 2022/12/19 17:08:44 by mmhaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include <string>

class Request {
	public:
		void							parsRequest(std::string str, std::vector<Location> location);
		int								checkLocation(std::string str, int method, std::vector<Location> location);
		std::vector<Location>::iterator	findGoodLocation(std::string str, std::vector<Location> location);

	private:
		std::string _method;
		std::string	_path;
		int			_retCode;
};