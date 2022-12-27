/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 14:28:47 by jtaravel          #+#    #+#             */
/*   Updated: 2022/12/26 18:07:07 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_HPP

#define FUNCTIONS_HPP

#include "server.hpp"
class Server;

typedef struct s_list
{
	char *name;
	char *content;
	char *line;
	struct s_list *next;
} t_list;

void    StartServer(Server server);
t_list    *init_lst(char **env, t_list *list);
void	ft_lstadd_back(t_list **alst, t_list *newm);
t_list	*ft_lstnew(char	*name, char *content, char *line);
char    **ft_regroup_env(t_list *lst);
char    **ft_split(char const *s, char c);

#endif
