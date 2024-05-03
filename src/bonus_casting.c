/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_casting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 19:26:53 by rshay             #+#    #+#             */
/*   Updated: 2024/04/28 19:27:54 by rshay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	floor_casting(t_rays *rays)
{
	for(int y = 0; y < SCREENHEIGHT; y++)
    {
		float rayDirX0 = rays->dir_x - rays->plane_x;
		float rayDirY0 = rays->dir_y - rays->plane_y;
		float rayDirX1 = rays->dir_x + rays->plane_x;
		float rayDirY1 = rays->dir_y + rays->plane_y;
		int p = y - SCREENHEIGHT / 2;
		float posZ = 0.5 * SCREENHEIGHT;
		float rowDistance = posZ / p;
		float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / SCREENWIDTH;
		float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / SCREENWIDTH;
		float floorX = rays->pos_x + rowDistance * rayDirX0;
		float floorY = rays->pos_y + rowDistance * rayDirY0;
		for(int x = 0; x < SCREENWIDTH; ++x)
      {
        int cellX = (int)(floorX);
        int cellY = (int)(floorY);
        int tx = (int)(TEXTWIDTH * (floorX - cellX)) & (TEXTWIDTH - 1);
        int ty = (int)(TEXTHEIGHT * (floorY - cellY)) & (TEXTHEIGHT - 1);
        floorX += floorStepX;
        floorY += floorStepY;
        int floorTexture = 3;
        int ceilingTexture = 6;
        u_int32_t color;
        color = rays->texture[floorTexture][TEXTWIDTH * ty + tx];
        color = (color >> 1) & 8355711;
        rays->buffer[y][x] = color;
        color = rays->texture[ceilingTexture][TEXTWIDTH * ty + tx];
        color = (color >> 1) & 8355711;
        rays->buffer[SCREENHEIGHT - y - 1][x] = color;
      }
	}
}
