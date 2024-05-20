/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrtouille.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 03:31:24 by rtissera          #+#    #+#             */
/*   Updated: 2024/05/20 17:56:54 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_atouille(const char *nptr)
{
	int	res;

	res = 0;
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

int	**ft_arrtouille(t_world *world, char **arr, int lignes, int collones, \
	int start)
{
	int	i;
	int	j;
	int	**ret;

	while (arr[++lignes])
	{
		if (ft_strlen(arr[lignes]) > (size_t)collones)
			collones = ft_strlen(arr[lignes]);
	}
	ret = (int **)malloc(sizeof(int *) * lignes);
	if (!ret)
		ft_error(world, strerror(errno));
	i = start - 1;
	while (++i < lignes)
	{
		ret[i] = (int *)malloc(sizeof(int) * collones);
		if (!ret[i])
			ft_error(world, strerror(errno));
		j = -1;
		while (++j < collones)
			ret[i][j] = arr[i][j] - '0';
	}
	return (ret);
}
