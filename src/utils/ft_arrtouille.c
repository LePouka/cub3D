/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrtouille.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 03:31:24 by rtissera          #+#    #+#             */
/*   Updated: 2024/05/24 14:32:33 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_atouille(char c)
{
	if (c == ' ')
	{
		return (1);
	}
	else
	{
		return (c - '0');
	}
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
	ret = (int **)malloc(sizeof(int *) * (lignes + 1));
	if (!ret)
		ft_error(world, strerror(errno));
	i = start - 1;
	while (++i < lignes && arr[i])
	{
		ret[i - start] = (int *)malloc(sizeof(int) * collones);
		if (!ret[i - start])
			ft_error(world, strerror(errno));
		j = -1;
		while (++j < collones && arr[i][j])
			ret[i - start][j] = ft_atouille(arr[i][j]);
	}
	ret[i - start] = NULL;
	return (ret);
}
