/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebronen <lebronen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 15:58:09 by lebronen          #+#    #+#             */
/*   Updated: 2024/04/08 18:11:16 by lebronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"
#include <sys/types.h>

#define screenWidth 1920
#define screenHeight 1080
#define texWidth 64
#define texHeight 64
#define mapWidth 24
#define mapHeight 24
#define ESCAPE 65307

#define abs(x) x >= 0 ? x : -x


void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->l + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

void casting(t_rays *rays) {

  int texture[8][texWidth * texHeight];

  for(int x = 0; x < texWidth; x++) {
    for(int y = 0; y < texHeight; y++)
    {
      int xorcolor = (x * 256 / texWidth) ^ (y * 256 / texHeight);
      //int xcolor = x * 256 / texWidth;
      int ycolor = y * 256 / texHeight;
      int xycolor = y * 128 / texHeight + x * 128 / texWidth;
      texture[0][texWidth * y + x] = 65536 * 254 * (x != y && x != texWidth - y); //flat red texture with black cross
      texture[1][texWidth * y + x] = xycolor + 256 * xycolor + 65536 * xycolor; //sloped greyscale
      texture[2][texWidth * y + x] = 256 * xycolor + 65536 * xycolor; //sloped yellow gradient
      texture[3][texWidth * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor; //xor greyscale
      texture[4][texWidth * y + x] = 256 * xorcolor; //xor green
      texture[5][texWidth * y + x] = 65536 * 192 * (x % 16 && y % 16); //red bricks
      texture[6][texWidth * y + x] = 65536 * ycolor; //red gradient
      texture[7][texWidth * y + x] = 128 + 256 * 128 + 65536 * 128; //flat grey texture
    }
  }

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

      //texturing calculations
      int texNum = rays->worldMap[mapX][mapY] - 1; //1 subtracted from it so that texture 0 can be used!

      //calculate value of wallX
      double wallX; //where exactly the wall was hit
      if (side == 0) wallX = rays->posY + perpWallDist * rayDirY;
      else           wallX = rays->posX + perpWallDist * rayDirX;
      wallX -= floor((wallX));

      //x coordinate on the texture
      int texX = (int)(wallX * (double)(texWidth));
      if(side == 0 && rayDirX > 0) texX = texWidth - texX - 1;
      if(side == 1 && rayDirY < 0) texX = texWidth - texX - 1;
       // How much to increase the texture coordinate per screen pixel
      double step = 1.0 * texHeight / lineHeight;
      // Starting texture coordinate
      double texPos = (drawStart - screenHeight / 2 + lineHeight / 2) * step;
      for(int y = drawStart; y<drawEnd; y++)
      {
        // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
        int texY = (int)texPos & (texHeight - 1);
        texPos += step;
        u_int32_t color = texture[texNum][texHeight * texY + texX];
        //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
        if(side == 1) color = (color >> 1) & 8355711;
        //buffer[y][x] = color;
        my_mlx_pixel_put(rays->vars->img, x, y, color);
      }
    }
    rays->oldTime = rays->time;
    rays->time = time(NULL);
    double frameTime = (rays->time - rays->oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
    
    //speed modifiers
    double moveSpeed = frameTime * 5.0; //the constant value is in squares/second
    double rotSpeed = frameTime * 3.0; //the constant value is in radians/second
    rays->moveSpeed = moveSpeed;
    rays->rotSpeed = rotSpeed;
    
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
  rays.moveSpeed = 0;
  rays.time = time(NULL);
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
  mlx_hook(mlx_win, 17, 1L<< 0, close_win, mlx);
  
	mlx_loop(mlx);

}