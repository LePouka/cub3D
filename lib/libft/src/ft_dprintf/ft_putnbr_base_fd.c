/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 14:12:08 by rtissera          #+#    #+#             */
/*   Updated: 2024/03/19 21:26:24 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putvoid_fd(unsigned long int n, int fd)
{
	int	i;

	i = 0;
	if (!n)
		return (ft_putstr_fd("(nil)", fd));
	i += ft_putstr_fd("0x", fd);
	i += ft_putnbr_base_fd(n, 'x', fd);
	return (i);
}

int	ft_putnbr_base_fd(unsigned long int n, int base, int fd)
{
	int	i;

	i = 0;
	if (n >= 16)
	{
		i += ft_putnbr_base_fd((n / 16), base, fd);
		i += ft_putnbr_base_fd((n % 16), base, fd);
	}
	else if (n < 10)
		i += ft_putnbr_fd(n, fd);
	else
		i += ft_putchar_fd(n - 10 + 'a' + base - 'x', fd);
	return (i);
}
