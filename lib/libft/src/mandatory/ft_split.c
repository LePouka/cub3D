/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:05:21 by rtissera          #+#    #+#             */
/*   Updated: 2023/05/26 16:10:41 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	*freeerror(char **s, int i)
{
	while (i >= 0)
	{
		free(s[i]);
		i--;
	}
	free(s);
	return (NULL);
}

int	nbstr(const char *s, char c)
{
	long int	i;
	long int	j;

	i = 0;
	j = 0;
	if (s[i] == 0)
		return (0);
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == c || s[i] == '\0')
		{
			j++;
			while (s[i] == c)
				i++;
		}
		else
			i++;
	}
	if (s[i - 1] != c)
		j++;
	return (j);
}

int	getnextstr(const char *s, char c, int i)
{
	long int	j;

	j = 0;
	while (s[i] && (s[i] != c))
	{
		i++;
		j++;
	}
	return (j);
}

char	**ft_split(char const *s, char c)
{
	long int	i;
	long int	j;
	long int	nextstr;
	char		**s2;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	s2 = malloc(sizeof(char *) * ((nbstr(s, c) + 1)));
	if (!s2)
		return (NULL);
	while (j < (nbstr(s, c)))
	{
		while (s[i] == c)
			i++;
		nextstr = getnextstr(s, c, i);
		s2[j] = ft_substr(s, i, nextstr);
		if (!s2[j])
			return (freeerror(s2, j));
		i += nextstr;
		j++;
	}
	s2[j] = NULL;
	return (s2);
}
