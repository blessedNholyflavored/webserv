/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_request.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mmhaya <Mmhaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 22:36:55 by Mmhaya            #+#    #+#             */
/*   Updated: 2022/12/18 14:49:33 by Mmhaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include <string>

class Request {
	public:
		void	parsRequest(std::string str, std::vector<Location> location);
		int		checkLocation(std::string str, int method, std::vector<Location> location);
	private:
		std::string _method;
		std::string	_path;
		int			_retCode;
};