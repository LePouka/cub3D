/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:29:46 by rshay             #+#    #+#             */
/*   Updated: 2024/06/04 16:29:46 by rshay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int	close_win(void *mlx)
{
	mlx_loop_end(mlx);
	return (0);
}

void	move_x(int fact, t_rays *rays)
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
	if (!rays->world_map[p_y][(int)new_x])
	{
		if (!rays->world_map[p_y - 1][(int)new_x])
			rays->pos_x = new_x;
		if ((rays->pos_y - (double)(p_y) <= 0.8 \
			&& rays->pos_y - (double)p_y >= 0.2))
			rays->pos_x = new_x;
	}
	else
		axe_y(rays, fact);
	col_y(rays, fact);
}

void	move_y(int fact, t_rays *rays)
{
	double	move;
	int		new_x;
	int		new_y;

	move = 0.1 * fact;
	new_x = (int)(rays->pos_x + rays->dir_y * move);
	new_y = (int)(rays->pos_y - rays->dir_x * move);
	if (!rays->world_map[(int)rays->pos_y][(int)(new_x)])
			rays->pos_x += rays->dir_y * move;
	if (!rays->world_map[new_y][(int)(rays->pos_x)])
	{
		if (!rays->world_map[new_y - 1][(int)(rays->pos_x)])
		rays->pos_y -= rays->dir_x * move;
	}
	mlx_destroy_image(rays->vars->mlx, rays->vars->img->img);
	init(rays);
}

void	rotate(int fact, t_rays *rays)
{
	double	rotate;
	double	olddir_x;
	double	oldplane_x;

	rotate = fact * -0.1;
	olddir_x = rays->dir_x;
	rays->dir_x = rays->dir_x * cos(rotate) - rays->dir_y * sin(rotate);
	rays->dir_y = olddir_x * sin(rotate) + rays->dir_y * cos(rotate);
	oldplane_x = rays->plane_x;
	rays->plane_x = rays->plane_x * cos(rotate) - rays->plane_y * sin(rotate);
	rays->plane_y = oldplane_x * sin(rotate) + rays->plane_y * cos(rotate);
	mlx_destroy_image(rays->vars->mlx, rays->vars->img->img);
	init(rays);
}

int	clavier(int keycode, t_rays *rays)
{
	if (keycode == W)
		move_x(-1, rays);
	if (keycode == S)
		move_x(1, rays);
	if (keycode == A)
		move_y(-1, rays);
	if (keycode == D)
		move_y(1, rays);
	if (keycode == DROITE)
		rotate(1, rays);
	if (keycode == GAUCHE)
		rotate(-1, rays);
	if (keycode == ESCAPE)
		mlx_loop_end(rays->vars->mlx);
	return (0);
}
