/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 15:12:51 by jtaravel          #+#    #+#             */
/*   Updated: 2022/12/28 17:39:25 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstdlib>
#include "functions.h"


typedef struct s_cgi
{
    

} t_cgi;

t_list    *init_lst(char **env, t_list *list);
void	ft_lstadd_back(t_list **alst, t_list *newm);
t_list	*ft_lstnew(char	*name, char *content, char *line);

//////////////////////////////////////////////


void	del(void *data)
{
	free(data);
}

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	if (lst->content)
		(*del)(lst->content);
	if (lst->name)
		(*del)(lst->name);
	if (lst->line)
		(*del)(lst->line);
	free(lst);
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*list;
	t_list	*tmp;

	if (!lst || !del)
		return ;
	list = *lst;
	while (list)
	{
		tmp = list->next;
		ft_lstdelone(list, del);
		list = tmp;
	}
	*lst = NULL;
}

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
	}
	return (tmp);
}

void	ft_lstadd_back(t_list **alst, t_list *newm)
{
	t_list	*tmp;

	tmp = *alst;
	if ((*alst))
	{
		tmp = ft_lstlast(*alst);
		tmp->next = newm;
	}
	else
	{
		*alst = newm;
	}
}


void	ft_lstadd_back(t_list **alst, t_list *newm);
t_list	*ft_lstnew(char	*name, char *content, char *line)
{
	t_list	*tmp;

	tmp = (t_list *)malloc(sizeof(struct s_list));
	if (!tmp)
		return (0);
	tmp->name = name;
	tmp->line = line;
	tmp->content = content;
	tmp->next = NULL;
	return (tmp);
}

int	ft_lstsize(t_list *lst)
{
	int	i;

	if (!lst)
		return (0);
	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

char	*ft_strdup(char *s);

char    **ft_regroup_env(t_list *lst)
{
    t_list    *tmp;
    char    **recup;
    int        len;
    int        i;

    tmp = lst;
    len = ft_lstsize(tmp);
    recup = (char **)malloc(sizeof(char *) * (len + 1));
    i = 0;
    while (tmp->next)
    {
        recup[i] = ft_strdup(tmp->line);
	printf("regroup = %s\n", recup[i]);
        i++;
        tmp = tmp->next;
    }
    recup[i] = ft_strdup(tmp->line);
    recup[i + 1] = 0;
    return (recup);
}

int	ft_strlen(char *str)
{
	int i = -1;
	while (str[++i])
		;
	return (i);
}

char	*ft_strdup(char *s)
{
	char	*cpy;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	cpy = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!cpy)
		return (0);
	while (s[i])
	{
		cpy[i] = s[i];
		i++;
	}
	cpy[i] = 0;
	return (cpy);
}

t_list    *init_lst(char **env, t_list *list)
{
    int        i;
    char    *name;
    char    *content;
    char    *line;

    name = NULL;
    content = NULL;
    i = -1;
    while (env[++i])
    {
        name = (char *)malloc(sizeof(char) * (ft_strlen(env[i]) + 1));
        content = ft_strdup(env[i] + ft_strlen(name));
        line = ft_strdup(env[i]);
        ft_lstadd_back(&list, ft_lstnew(name, content, line));
    }
    return (list);
}
