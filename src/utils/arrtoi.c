/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrtoi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 03:31:24 by rtissera          #+#    #+#             */
/*   Updated: 2024/05/03 15:59:09 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_atouille(const char *nptr)
{
	int	res;

	res = 0;
	sig = 1;
	if (*nptr == 45)
	{
		return (-1);
	}
	while (((*nptr >= 48) && (*nptr <= 57)) || *nptr == 32)
	{
		if (*nptr == 32)
		{
			res = (res * 10) + 1;
		}
		else
		{
			res = (res * 10) + *nptr - 48;
		}
		nptr++;
	}
	return (res);
}

int	**ft_arrtouille(char **arr, int lignes, int collones)
{
	int	i;
	int	j;
	int	**ret;

	while (arr[++lignes])
	{
		if (ft_strlen(arr[lignes]) > collones)
			collones = ft_strlen(arr[lignes]);
	}
	ret = (int **)malloc(sizeof(int *) * lignes);
	if (!ret)
		return (ft_error(strerror(errno)));
	i = -1;
	while (++i < lignes)
	{
		ret[i] = (int *)malloc(sizeof(int) * collones);
		if (!ret[i])
			return (ft_error(strerror(errno)));
		j = -1;
		while (++j < collones)
			ret[i][j] = arr[i][j] - '0';
	}
	free_array(arr);
	return (ret);
}
