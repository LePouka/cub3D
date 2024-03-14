/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:57:40 by rtissera          #+#    #+#             */
/*   Updated: 2023/05/26 16:10:37 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	c2;

	i = 0;
	c2 = (char)c;
	while ((s[i] && (c2 != s[i])))
		i++;
	if (s[i] == c2)
		return ((char *)s + i);
	return (NULL);
}
