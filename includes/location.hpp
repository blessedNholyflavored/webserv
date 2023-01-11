/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkhamlac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:07:31 by lkhamlac          #+#    #+#             */
/*   Updated: 2023/01/11 14:07:32 by lkhamlac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef LOCATION_HPP
# define LOCATION_HPP
# include <iostream>
# include <fstream>
# include <sstream>
# include <string>
# include <cstdlib>
# include <unistd.h>
#include <vector>
#include <iterator>
# define WHITESPACES "; \t"


class Location
{
	private:
		std::string					_location;
		std::string					_root;
		std::string					_index;
		std::string					_return;
		std::vector<std::string>	_methods;
		bool						_autoindex;
		bool						_GET;
		bool						_DELETE;
		bool						_POST;
		bool						_defaut;

	public:
		Location();
		~Location();
		int			parser_la_location(int j);
		void		parseMethod(std::string str);
		void		parseRoot(std::string str);
		void		parseIndex(std::string str);
		void		parseReturn(std::string str);
		void		parseAutoindex(std::string str);
		std::string	getLocation();
		std::string	getRoot();
		std::string	getIndex();
		bool		getDefaut();
		bool		getGet();
		bool		getDel();
		bool		getPost();
		bool		getAuto();
};

#endif
