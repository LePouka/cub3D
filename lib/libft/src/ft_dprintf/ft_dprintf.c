/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 17:03:07 by rtissera          #+#    #+#             */
/*   Updated: 2024/03/19 21:26:17 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	condition(int c, int j, va_list arg, int fd)
{
	if (c == 'c')
		j += ft_putchar_fd(va_arg(arg, unsigned int), fd);
	else if (c == 'u')
		j += ft_putu_fd(va_arg(arg, int), fd);
	else if (c == 's')
		j += ft_putstr_fd(va_arg(arg, char *), fd);
	else if ((c == 'd') || (c == 'i'))
		j += ft_putnbr_fd(va_arg(arg, int), fd);
	else if (c == 'x')
		j += ft_putnbr_base_fd(va_arg(arg, unsigned int), 'x', fd);
	else if (c == 'X')
		j += ft_putnbr_base_fd(va_arg(arg, unsigned int), 'X', fd);
	else if (c == 'p')
		j += ft_putvoid_fd(va_arg(arg, unsigned long int), fd);
	else
		j += ft_putchar_fd(c, fd);
	return (j);
}

int	ft_dprintf(int fd, char const *str, ...)
{
	int		i;
	int		j;
	int		k;
	va_list	arg;

	i = 0;
	j = 0;
	k = 0;
	va_start(arg, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			if (str[i + 1] == '%')
				j += ft_putchar_fd('%', fd);
			else
				j = condition(str[i + 1], j, arg, fd);
			k += 2;
			i += 2;
		}
		else
			i += ft_putchar_fd(str[i], fd);
	}
	va_end(arg);
	return (j + i - k);
}
