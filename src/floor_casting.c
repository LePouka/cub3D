/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_casting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:38:39 by rshay             #+#    #+#             */
/*   Updated: 2024/04/29 16:10:41 by rshay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	casting_loop(t_rays *rays, t_casting cast, int y)
{
	int			x;

	x = 0;
	while (++x < SCREENWIDTH)
	{
		cast.floorX += cast.floorStepX;
		cast.floorY += cast.floorStepY;
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
		cast.rayDirX0 = rays->dir_x - rays->plane_x;
		cast.rayDirY0 = rays->dir_y - rays->plane_y;
		cast.rayDirX1 = rays->dir_x + rays->plane_x;
		cast.rayDirY1 = rays->dir_y + rays->plane_y;
		cast.p = y - SCREENHEIGHT / 2;
		cast.posZ = 0.5 * SCREENHEIGHT;
		cast.rowDistance = cast.posZ / cast.p;
		cast.diff_x = (cast.rayDirX1 - cast.rayDirX0);
		cast.diff_y = (cast.rayDirY1 - cast.rayDirY0);
		cast.floorStepX = cast.rowDistance * cast.diff_x / SCREENWIDTH;
		cast.floorStepY = cast.rowDistance * cast.diff_y / SCREENWIDTH;
		cast.floorX = rays->pos_x + cast.rowDistance * cast.rayDirX0;
		cast.floorY = rays->pos_y + cast.rowDistance * cast.rayDirY0;
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
		rays->color = rays->texture[calcs.tex_num][c_tex];
		if (calcs.side == 1)
			rays->color = (rays->color >> 1) & 8355711;
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
