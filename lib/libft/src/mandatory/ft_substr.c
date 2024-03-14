/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:37:37 by rtissera          #+#    #+#             */
/*   Updated: 2023/09/19 14:18:06 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*starttoofar(void)
{
	char	*str;

	str = malloc(sizeof(char));
	if (!str)
		return (NULL);
	str[0] = 0;
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	alllen;
	char	*str;

	i = 0;
	alllen = 0;
	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (starttoofar());
	while (s[alllen + start])
		alllen++;
	if (alllen > len)
		alllen = len;
	str = malloc(sizeof(char) * alllen + 1);
	if (!str)
		return (NULL);
	while ((i < len) && s[start + i])
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = 0;
	return (str);
}
