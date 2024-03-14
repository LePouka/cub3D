/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:56:01 by rtissera          #+#    #+#             */
/*   Updated: 2022/11/14 23:45:52 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *nptr)
{
	int	res;
	int	sig;

	res = 0;
	sig = 1;
	while (((*nptr >= 9) && (*nptr <= 13)) || (*nptr == 32))
		nptr++;
	if (*nptr == 45)
	{
		sig *= -1;
		nptr++;
	}
	else if (*nptr == 43)
		nptr++;
	while ((*nptr >= 48) && (*nptr <= 57))
	{
		res = (res * 10) + *nptr - 48;
		nptr++;
	}
	return (res * sig);
}
