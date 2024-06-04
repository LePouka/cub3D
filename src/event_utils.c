/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:23:39 by rshay             #+#    #+#             */
/*   Updated: 2024/06/04 16:30:05 by rshay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	col_y(t_rays *rays, int fact)
{
	double	move;
	int		p_y;
	int		p_x;
	double	new_x;
	double	new_y;

	move = -0.1 * fact;
	p_x = (int)(rays->pos_x);
	p_y = (int)(rays->pos_y);
	new_x = rays->pos_x + rays->dir_x * move;
	new_y = rays->pos_y + rays->dir_y * move;
	if (!rays->world_map[(int)new_y][p_x])
		rays->pos_y = new_y;
	else
	{
		if (!rays->world_map[p_y][(int)(rays->pos_x + rays->dir_x * \
			(move / 2))])
			rays->pos_x += rays->dir_x * (move / 2);
	}
	mlx_destroy_image(rays->vars->mlx, rays->vars->img->img);
	init(rays);
}

void	axe_y(t_rays *rays, int fact)
{
	double	move;
	int		p_y;
	int		p_x;
	double	new_x;
	double	new_y;

	move = -0.1 * fact;
	p_x = (int)(rays->pos_x);
	p_y = (int)(rays->pos_y);
	new_x = rays->pos_x + rays->dir_x * move;
	new_y = rays->pos_y + rays->dir_y * move;
	if (!rays->world_map[(int)(rays->pos_y + rays->dir_y * (move / 2))][p_x])
	{
		if (rays->world_map[p_y][(int)new_x])
			rays->pos_y += rays->dir_y * (move / 2);
	}
}
