/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:32:28 by rtissera          #+#    #+#             */
/*   Updated: 2023/05/26 16:11:25 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	c2;
	unsigned char	*str;

	c2 = (unsigned char)c;
	str = (unsigned char *)s;
	while (n)
	{
		if (*str == c2)
			return (str);
		str++;
		n--;
	}
	return (NULL);
}
