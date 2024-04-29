/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_to_int.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 03:31:24 by rtissera          #+#    #+#             */
/*   Updated: 2024/04/29 04:05:27 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	**char_to_int(char **arr, int lignes, int collones)
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
	i = 0;
	while (i < lignes)
	{
		ret[i] = (int *)malloc(sizeof(int) * collones);
		if (!ret[i])
			return (ft_error(strerror(errno)));
		j = 0;
		while (j < collones)
			ret[i][j] = arr[i][j] - '0';
	}
	free_array(arr);
	return (ret);
}
