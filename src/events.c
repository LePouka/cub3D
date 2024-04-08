/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebronen <lebronen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:10:41 by rshay             #+#    #+#             */
/*   Updated: 2024/04/08 18:41:02 by lebronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int close_win(void *mlx) {
    mlx_loop_end(mlx);
    return (0);
}

int clavier(int keycode, t_rays *rays) {


    double rotate = -0.03;
    double move = -0.2;

    if (keycode == BAS) {
        if(rays->worldMap[(int)(rays->posX + rays->dirX * move)][(int)(rays->posY)] == false)
            rays->posX += rays->dirX * move;
        if(rays->worldMap[(int)(rays->posX)][(int)(rays->posY + rays->dirY * move)] == false)
            rays->posY += rays->dirY * move;
        init(rays);
        mlx_put_image_to_window(rays->vars->mlx, rays->vars->win, rays->vars->img->img, 0, 0);
        casting(rays);
    }

    if (keycode == HAUT) {
        if(rays->worldMap[(int)(rays->posX - rays->dirX * move)][(int)(rays->posY)] == false)
            rays->posX -= rays->dirX * move;
        if(rays->worldMap[(int)(rays->posX)][(int)(rays->posY - rays->dirY * move)] == false)
            rays->posY -= rays->dirY * move;
        init(rays);
        mlx_put_image_to_window(rays->vars->mlx, rays->vars->win, rays->vars->img->img, 0, 0);
        casting(rays);
    }

    if (keycode == DROITE) {
        //both camera direction and camera plane must be rotated
      double oldDirX = rays->dirX;
      rays->dirX = rays->dirX * cos(rotate) - rays->dirY * sin(rotate);
      rays->dirY = oldDirX * sin(rotate) + rays->dirY * cos(rotate);
      double oldPlaneX = rays->planeX;
      rays->planeX = rays->planeX * cos(rotate) - rays->planeY * sin(rotate);
      rays->planeY = oldPlaneX * sin(rotate) + rays->planeY * cos(rotate);

    init(rays);
    mlx_put_image_to_window(rays->vars->mlx, rays->vars->win, rays->vars->img->img, 0, 0);
    casting(rays);
    }

    if (keycode == GAUCHE) {
        //both camera direction and camera plane must be rotated
      double oldDirX = rays->dirX;
      rays->dirX = rays->dirX * cos(-rotate) - rays->dirY * sin(-rotate);
      rays->dirY = oldDirX * sin(-rotate) + rays->dirY * cos(-rotate);
      double oldPlaneX = rays->planeX;
      rays->planeX = rays->planeX * cos(-rotate) - rays->planeY * sin(-rotate);
      rays->planeY = oldPlaneX * sin(-rotate) + rays->planeY * cos(-rotate);

    init(rays);
    mlx_put_image_to_window(rays->vars->mlx, rays->vars->win, rays->vars->img->img, 0, 0);
    casting(rays);
    }

    if (keycode == ESCAPE) {
    mlx_loop_end(rays->vars->mlx);
  }

    return (0);
    
}