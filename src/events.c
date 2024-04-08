/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:10:41 by rshay             #+#    #+#             */
/*   Updated: 2024/04/08 14:23:44 by rshay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int clavier(int keycode, t_rays *rays) {

    

    if (keycode == HAUT) {
        
        if(rays->worldMap[(int)(rays->posX + rays->dirX * 1.2)][(int)(rays->posY)] == false)
            rays->posX += rays->dirX * 1.2;
        if(rays->worldMap[(int)(rays->posX)][(int)(rays->posY + rays->dirY * 1.2)] == false)
            rays->posY += rays->dirY * 1.2;
        
        casting(rays);
    }

    if (keycode == BAS) {
        if(rays->worldMap[(int)(rays->posX - rays->dirX * 1.2)][(int)(rays->posY)] == false)
            rays->posX -= rays->dirX * 1.2;
        if(rays->worldMap[(int)(rays->posX)][(int)(rays->posY - rays->dirY * 1.2)] == false)
            rays->posY -= rays->dirY * 1.2;
        casting(rays);
    }

    if (keycode == DROITE) {
        //both camera direction and camera plane must be rotated
      double oldDirX = rays->dirX;
      rays->dirX = rays->dirX * cos(-1) - rays->dirY * sin(-1);
      rays->dirY = oldDirX * sin(-1) + rays->dirY * cos(-1);
      double oldPlaneX = rays->planeX;
      rays->planeX = rays->planeX * cos(-1) - rays->planeY * sin(-1);
      rays->planeY = oldPlaneX * sin(-1) + rays->planeY * cos(-1);

      casting(rays);
    }

    return (0);
    
}