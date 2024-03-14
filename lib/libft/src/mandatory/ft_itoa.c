/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:39:54 by rtissera          #+#    #+#             */
/*   Updated: 2023/05/26 16:11:28 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*intmin(int n, int i, char *str)
{
	str[i] = '8';
	n /= 10;
	i--;
	str[0] = '-';
	n *= -1;
	while (n > 0)
	{
		str[i] = (n % 10) + 48;
		n /= 10;
		i--;
	}
	return (str);
}

char	*intnull(int i, char *str)
{
	str[i] = '0';
	return (str);
}

size_t	intlen(int n)
{
	size_t	i;

	i = 0;
	if (n == INT_MIN)
		n++;
	if (n == 0)
		i++;
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	size_t	i;
	char	*str;

	i = intlen(n);
	str = malloc(sizeof(char) * i + 1);
	if (!str)
		return (NULL);
	str[i--] = 0;
	if (n == INT_MIN)
		return (intmin(n, i, str));
	if (n == 0)
		return (intnull(i, str));
	if (n < 0)
	{
		str[0] = '-';
		n *= -1;
	}
	while (n > 0)
	{
		str[i] = (n % 10) + 48;
		n /= 10;
		i--;
	}
	return (str);
}
