/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 15:28:35 by lguillau          #+#    #+#             */
/*   Updated: 2022/12/26 18:12:21 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

static int	check_charset(char c, char current)
{
	if (current == c)
	{
		return (1);
	}
	return (0);
}

static int	words_count(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (check_charset(c, s[i]))
		i++;
	while (s[i])
	{
		if (check_charset(c, s[i]))
			count++;
		while (check_charset(c, s[i]))
			i++;
		i++;
	}
	if (!check_charset(c, s[i]))
		count++;
	return (count);
}

static int	wordlen(char const *s, char c)
{
	int	i;
	int	s_size;

	s_size = 0;
	i = 0;
	while (check_charset(c, s[i]) && s[i])
		i++;
	while (!check_charset(c, s[i]) && s[i])
	{
		s_size++;
		i++;
	}
	return (s_size);
}

static char	*dupword(char const *s, char c, int n)
{
	char	*dup;
	int		i;
	int		j;

	i = 0;
	j = 0;
	dup = (char *)malloc(sizeof(char) * (n + 1));
	if (!dup)
		return (NULL);
	while (check_charset(c, s[i]))
		i++;
	while (!check_charset(c, s[i]) && s[i])
	{
		dup[j] = s[i];
		j++;
		i++;
	}
	dup[j] = 0;
	return (dup);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s)
		return (0);
	str = (char **)malloc(sizeof(char *) * (words_count(s, c) + 1));
	if (!str)
		return (NULL);
	while (s[i])
	{
		if (check_charset(c, s[i]))
			i++;
		else
		{
			str[j] = dupword(s + i, c, wordlen(s + i, c));
			j++;
			i += wordlen(s + i, c);
		}
	}
	str[j] = NULL;
	return (str);
}
