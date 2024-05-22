/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_casting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:38:39 by rshay             #+#    #+#             */
/*   Updated: 2024/05/06 17:37:20 by rshay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	casting_loop(t_rays *rays, t_casting cast, int y)
{
	int			x;

	x = 0;
	while (++x < SCREENWIDTH)
	{
		cast.floor_x += cast.floor_step_x;
		cast.floor_y += cast.floor_step_y;
		rays->color = 0x0500FF00;
		rays->color = (rays->color >> 1) & 8355711;
		rays->buffer[y][x] = rays->color;
		rays->color = 0x00e11e00;
		rays->color = (rays->color >> 1) & 8355711;
		rays->buffer[SCREENHEIGHT - y - 1][x] = rays->color;
	}
}

void	floor_casting(t_rays *rays)
{
	int			y;
	t_casting	cast;

	y = 0;
	while (y < SCREENHEIGHT)
	{
		cast.ray_dir_x0 = rays->dir_x - rays->plane_x;
		cast.ray_dir_y0 = rays->dir_y - rays->plane_y;
		cast.ray_dir_x1 = rays->dir_x + rays->plane_x;
		cast.ray_dir_y1 = rays->dir_y + rays->plane_y;
		cast.p = y - SCREENHEIGHT / 2;
		cast.pos_z = 0.5 * SCREENHEIGHT;
		cast.row_distance = cast.pos_z / cast.p;
		cast.diff_x = (cast.ray_dir_x1 - cast.ray_dir_x0);
		cast.diff_y = (cast.ray_dir_y1 - cast.ray_dir_y0);
		cast.floor_step_x = cast.row_distance * cast.diff_x / SCREENWIDTH;
		cast.floor_step_y = cast.row_distance * cast.diff_y / SCREENWIDTH;
		cast.floor_x = rays->pos_x + cast.row_distance * cast.ray_dir_x0;
		cast.floor_y = rays->pos_y + cast.row_distance * cast.ray_dir_y0;
		casting_loop(rays, cast, y);
		y++;
	}
}

void	drawing(t_rays *rays, t_calcs calcs, int x)
{
	int	y;
	int	tex_y;
	int	c_tex;

	y = calcs.draw_start;
	while (y < calcs.draw_end)
	{
		tex_y = (int)calcs.tex_pos & (TEXTHEIGHT - 1);
		calcs.tex_pos += calcs.step;
		c_tex = TEXTHEIGHT * tex_y + calcs.tex_x;
		rays->color = rays->texture[calcs.orientation][c_tex];
		if (calcs.side == 1)
			rays->color = (rays->color) & 8355711;
		rays->buffer[y][x] = rays->color;
		y++;
	}
	y = 0;
	while (y < SCREENHEIGHT)
	{
		my_mlx_pixel_put(rays->vars->img, x, y, rays->buffer[y][x]);
		y++;
	}
}

int	casting(t_rays *rays)
{
	t_calcs		calcs;
	int			x;
	void		*mlx;
	void		*win;
	void		*img;

	mlx = rays->vars->mlx;
	win = rays->vars->win;
	img = rays->vars->img->img;
	floor_casting(rays);
	x = 0;
	while (x < SCREENWIDTH)
	{
		init_calculating(&calcs, rays, x);
		init_side_dist(&calcs, rays);
		calculate_dda(&calcs, rays);
		drawing_calculations(&calcs, rays);
		drawing(rays, calcs, x);
		x++;
	}
	speed_calculation(rays);
	mlx_put_image_to_window(mlx, win, img, 0, 0);
	return (0);
}
