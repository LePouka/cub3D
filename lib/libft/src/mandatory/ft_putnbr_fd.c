/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphael <raphael@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:12:49 by rtissera          #+#    #+#             */
/*   Updated: 2023/06/29 16:19:28 by raphael          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int	ft_putnbr_fd(int n, int fd)
{
	int	i;

	if (n == INT_MIN)
		return (ft_putstr_fd("-2147483648", fd));
	i = 0;
	if (n < 0)
	{
		i += ft_putchar_fd('-', fd);
		n *= -1;
	}
	if (n <= 9)
		i += ft_putchar_fd(n + 48, fd);
	if (n > 9)
	{
		i += ft_putnbr_fd((n / 10), fd);
		i += ft_putnbr_fd((n % 10), fd);
	}
	return (i);
}
