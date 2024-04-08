/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 15:58:09 by lebronen          #+#    #+#             */
/*   Updated: 2024/04/08 14:22:30 by rshay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"
#include <sys/types.h>

#define screenWidth 1920
#define screenHeight 1080
#define mapWidth 24
#define mapHeight 24

#define abs(x) x >= 0 ? x : -x


void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->l + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

void casting(t_rays *rays) {

    for (int x = 0; x < screenWidth; x++) {
        //calculate ray position and direction
        double cameraX = 2 * x / (double)screenWidth - 1; //x-coordinate in camera space
        double rayDirX = rays->dirX + rays->planeX * cameraX;
        double rayDirY = rays->dirY + rays->planeY * cameraX;
              //which box of the map we're in
      int mapX = rays->posX;
      int mapY = rays->posY;

      //length of ray from current position to next x or y-side
      double sideDistX;
      double sideDistY;

       //length of ray from one x or y-side to next x or y-side
      double deltaDistX = (rayDirX == 0) ? 1e30 : abs(1 / rayDirX);
      double deltaDistY = (rayDirY == 0) ? 1e30 : abs(1 / rayDirY);
      double perpWallDist;

      //what direction to step in x or y-direction (either +1 or -1)
      int stepX;
      int stepY;

      int hit = 0; //was there a wall hit?
      int side; //was a NS or a EW wall hit? 

      //calculate step and initial sideDist
      if (rayDirX < 0)
      {
        stepX = -1;
        sideDistX = (rays->posX - mapX) * deltaDistX;
      }
      else
      {
        stepX = 1;
        sideDistX = (mapX + 1.0 - rays->posX) * deltaDistX;
      }
      if (rayDirY < 0)
      {
        stepY = -1;
        sideDistY = (rays->posY - mapY) * deltaDistY;
      }
      else
      {
        stepY = 1;
        sideDistY = (mapY + 1.0 - rays->posY) * deltaDistY;
      }
      //perform DDA
      while (hit == 0)
      {
        //jump to next map square, either in x-direction, or in y-direction
        if (sideDistX < sideDistY)
        {
          sideDistX += deltaDistX;
          mapX += stepX;
          side = 0;
        }
        else
        {
          sideDistY += deltaDistY;
          mapY += stepY;
          side = 1;
        }
        //Check if ray has hit a wall
        if (rays->worldMap[mapX][mapY] > 0) hit = 1;
      }
      //Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
      if(side == 0) perpWallDist = (sideDistX - deltaDistX);
      else          perpWallDist = (sideDistY - deltaDistY);
      int lineHeight = (int)(screenHeight / perpWallDist);

      //calculate lowest and highest pixel to fill in current stripe
      int drawStart = -lineHeight / 2 + screenHeight / 2;
      if(drawStart < 0)drawStart = 0;
      int drawEnd = lineHeight / 2 + screenHeight / 2;
      if(drawEnd >= screenHeight)drawEnd = screenHeight - 1;
      for (int y = drawStart; y < drawEnd; y++) {
        int color;
        switch(rays->worldMap[mapX][mapY]) {
          case 1: color = 0xd42626; break; //red
          case 2: color = 0x38dB4e; break; //green
          case 3: color = 0x1927a5; break; //blue
          case 4: color = 0xce19e2; break; //purple
          default: color = 0xF5ed0a; break; //yellow
          
        }
        if (side == 1)
          my_mlx_pixel_put(rays->vars->img, x, y, color / 2);
        else
          my_mlx_pixel_put(rays->vars->img, x, y, color);
      }
    }
    //rays->oldTime = rays->time;
    //rays->time = time(NULL);
    //double frameTime = (rays->time - rays->oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
    
    //speed modifiers
    //double rotSpeed = frameTime * 3.0; //the constant value is in radians/second
    
    mlx_put_image_to_window(rays->vars->mlx, rays->vars->win, rays->vars->img->img, 0, 0);


}

void init(t_rays *rays) {
   rays->vars->img->img = mlx_new_image(rays->vars->mlx, screenWidth, screenHeight);
    rays->vars->img->addr = mlx_get_data_addr(rays->vars->img->img, &(rays->vars->img)->bpp, &(rays->vars->img)->l,
								&(rays->vars->img)->endian);
}

int main() {
    void	*mlx;
	t_data	img;
  t_rays rays;
    void *mlx_win;

     int worldMap[mapWidth][mapHeight]=
  {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
  	};


  double posX = 22, posY = 12;  //x and y start position
  double dirX = -1, dirY = 0; //initial direction vector
  double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane
  rays.posX = posX;
  rays.posY = posY;
  rays.dirX = dirX;
  rays.dirY = dirY;
  rays.planeX = planeX;
  rays.planeY = planeY;
  rays.time = 0;
  rays.oldTime = 0;

   int **heapmap = malloc(24 * sizeof(int *));

    for (int i = 0; i < 24; i++) {
      heapmap[i] = malloc(24 * sizeof(int));
      for (int j = 0; j < 24; j++) {
        heapmap[i][j] = worldMap[i][j];
      }
    }
  rays.worldMap = heapmap;
  
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, screenWidth, screenHeight, "Cub3d");
  t_vars vars;
  vars.img = &img;
  vars.mlx = mlx;
  vars.win = mlx_win;
  rays.vars = &vars;

  init(&rays);
	casting(&rays);
  mlx_hook(rays.vars->win, 2, 1L << 0, clavier, &rays);

	mlx_loop(mlx);

}