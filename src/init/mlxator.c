/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxator.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 15:51:29 by rtissera          #+#    #+#             */
/*   Updated: 2024/04/21 18:38:26 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_mlx	*mlxator(void)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)malloc(sizeof(t_mlx *));
	if (!mlx)
	{
		ft_error(strreror(errno));
		return (NULL);
	}
	mlx.mlx = mlx_init();
	mlx.mlx_win = mlx_new_window(mlx.mlx, SCREENWIDTH, SCREENHEIGHT, "Cub3D");
	return (mlx);
}
