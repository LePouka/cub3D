/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:10:41 by rshay             #+#    #+#             */
/*   Updated: 2024/04/08 14:31:14 by rshay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int clavier(int keycode, t_rays *rays) {

    double rotate = -0.02;

    if (keycode == HAUT) {
        
        if(rays->worldMap[(int)(rays->posX + rays->dirX * 1.2)][(int)(rays->posY)] == false)
            rays->posX += rays->dirX * 1.2;
        if(rays->worldMap[(int)(rays->posX)][(int)(rays->posY + rays->dirY * 1.2)] == false)
            rays->posY += rays->dirY * 1.2;
        
        casting(rays);
    }

    if (keycode == BAS) {
        if(rays->worldMap[(int)(rays->posX - rays->dirX * 0.8)][(int)(rays->posY)] == false)
            rays->posX -= rays->dirX * 0.8;
        if(rays->worldMap[(int)(rays->posX)][(int)(rays->posY - rays->dirY * 0.8)] == false)
            rays->posY -= rays->dirY * 0.8;
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

      casting(rays);
    }

    return (0);
    
}