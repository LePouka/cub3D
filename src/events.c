/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:10:41 by rshay             #+#    #+#             */
/*   Updated: 2024/04/08 13:52:46 by rshay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int clavier(int keycode, t_rays *rays) {

    

    if (keycode == HAUT) {
        
        if(rays->worldMap[(int)(rays->posX + rays->dirX)][(int)(rays->posY)] == false)
            rays->posX += rays->dirX;
        if(rays->worldMap[(int)(rays->posX)][(int)(rays->posY + rays->dirY)] == false)
            rays->posY += rays->dirY;
        
        casting(rays);
    }

    

    return (0);
    
}