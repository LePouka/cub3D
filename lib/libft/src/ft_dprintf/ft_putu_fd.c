/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putu_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphael <raphael@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:04:49 by rtissera          #+#    #+#             */
/*   Updated: 2023/06/29 16:00:44 by raphael          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int	ft_putu_fd(unsigned int n, int fd)
{
	int				i;
	char			c;
	long long int	nb;

	i = 0;
	c = 0;
	nb = n;
	if (nb < 10)
	{
		c = nb + 48;
		i += ft_putchar_fd(c, fd);
	}
	if (nb >= 10)
	{
		i += ft_putu_fd(nb / 10, fd);
		i += ft_putu_fd(nb % 10, fd);
	}
	return (i);
}
