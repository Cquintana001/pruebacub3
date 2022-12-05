#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <memory.h>
#include <math.h>
#include "mlx.h"
#include <sys/time.h> 
#include "state.h"
#include "utils.h"
#include "moves.h"

#define mapWidth 24
#define mapHeight 24
#define texWidth 64
#define texHeight 64

int global;

int load_textures(t_state *state);
 

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1},
  {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1},
  {1,0,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1},
  {1,0,1,0,0,0,0,1,0,1,0,1,0,1,0,1,1,0,0,0,1,1,1,1},
  {1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1},
  {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1},
  {1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,1,0,0,0,1,1,1,1},
  {1,0,0,0,0,0,0,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,0,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,0,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,1,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,0,0,1,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,1,1,0,1,1},
  {1,0,1,0,1,0,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,1},
  {1,0,0,1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,1,1,0,1,1},
  {1,0,1,0,1,0,0,0,0,1,1,0,1,1,0,0,1,0,0,1,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,1,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

 

int draw_map(t_state *state)
{

  t_data *img;
  int buffer[screenHeight][screenWidth];
  img = &state->img;
  mlx_destroy_image(state->mlx, img->img);
  img->img = mlx_new_image(state->mlx, screenWidth,  screenHeight );
  img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length,
								&img->endian);
  state->x = 0;
  while(state->x<screenWidth)
	{
      //calculate ray position and direction
      double cameraX = 2 * x / (double)screenWidth - 1; //x-coordinate in camera space
      double rayDirX = img->dirX + img->planeX * cameraX;
      double rayDirY = img->dirY + img->planeY * cameraX;

      //which box of the map we're in
      int mapX = (int)img->posX;
      int mapY = (int)img->posY;

      //length of ray from current position to next x or y-side
      double sideDistX;
      double sideDistY;

       //length of ray from one x or y-side to next x or y-side
      double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
      double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
      double perpWallDist;

   
      //what direction to step in x or y-direction (either +1 or -1)
      int stepX;
      int stepY;
      int hit = 0; //was there a wall hit?
      int side;
       //was a NS or a EW wall hit?
      if (rayDirX < 0)
      {
        stepX = -1;
        sideDistX = (img->posX - mapX) * deltaDistX;
      }
      else
      {
        stepX = 1;
        sideDistX = (mapX + 1.0 - img->posX) * deltaDistX;
      }
      if (rayDirY < 0)
      {
        stepY = -1;
        sideDistY = (img->posY - mapY) * deltaDistY;
      }
      else
      {
        stepY = 1;
        sideDistY = (mapY + 1.0 - img->posY) * deltaDistY;
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
        if (worldMap[mapX][mapY] > 0) 
          hit = 1;
      } 
      //Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
      if(side == 0)
      { 
        perpWallDist = (sideDistX - deltaDistX);
      }
      else
      {          
        perpWallDist = (sideDistY - deltaDistY);
      }
      //Calculate height of line to draw on screen
      int lineHeight = (int)(screenHeight/ perpWallDist);
      //calculate lowest and highest pixel to fill in current stripe
      int drawStart = -lineHeight / 2 + screenHeight / 2;
      if(drawStart < 0)
      {
        drawStart = 0;
      }
      int drawEnd = lineHeight / 2 + screenHeight / 2;
      if(drawEnd >= screenHeight)
      {
        drawEnd = screenHeight - 1;
      }
      
      //int texNum = worldMap[mapX][mapY] - 1; //1 subtracted from it so that texture 0 can be used!

      //calculate value of wallX
      double wallX; //where exactly the wall was hit
      if (side == 0) wallX = img->posY + perpWallDist * rayDirY;
      else           wallX = img->posX + perpWallDist * rayDirX;
      wallX -= floor((wallX));

      //x coordinate on the texture
      int texX = (int)(wallX * (double)(texWidth));
      if(side == 0 && rayDirX > 0) texX = texWidth - texX - 1;
      if(side == 1 && rayDirY < 0) texX = texWidth - texX - 1;
      //choose wall color
      // How much to increase the texture coordinate per screen pixel
      double step = 1.0 * texHeight / lineHeight;
      // Starting texture coordinate
      double texPos = (drawStart -screenHeight / 2 + lineHeight / 2) * step;
      for(int y = drawStart; y<drawEnd; y++)
      {
        // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
        int texY = (int)texPos & (texHeight - 1);
        texPos += step;
        int color;
        if(side == 1) 
        { 
          if(rayDirY<=0) 
            color = img->texture[0][texHeight * texY + texX];
          else
            color = img->texture[2][texHeight * texY + texX];
        }
        else
        {  if(rayDirX<=0) 
          color = img->texture[1][texHeight * texY + texX];
           else
            color = img->texture[3][texHeight * texY + texX];
        }
     

        buffer[y][x] = color;
      }
    
	    x++;
  }
      int e = 0;
        while(e<screenWidth)
          {
            int y = 0;
            while(y<screenHeight)
            {
              my_mlx_pixel_put(img,  e, y,buffer[y][e]);
              y++;
            }
            e++;
          }
          e = 0;
         while(e<screenWidth)
          {
            int y = 0;
            while(y<screenHeight)
            {
             buffer[y][e] = 0;
              y++;
            }
            e++;
          } 
  img->Oldtime = img->Time;
  img->Time = get_time();
  double frameTime = (img->Time - img->Oldtime)/1000; //frameTime is the time this frame has taken, in seconds
 
  mlx_put_image_to_window(state->mlx, state->window, img->img, 0, 0);
  img->moveSpeed = frameTime * 5.0; //the constant value is in squares/second
  img->rotSpeed = frameTime * 3.0; //the constant value is in radians/second
 
  return(0);
}

 int	key_hook(int keycode, t_state *state)
{
  t_data *img;

  img = &state->img;
    if (keycode == 13)
    {
      //move_up(img, worldMap);
      if(worldMap[(int)(img->posX + (img->dirX * img->moveSpeed))][(int)img->posY] == 0) 
        img->posX += img->dirX * img->moveSpeed;
      if(worldMap[(int)img->posX][(int)(img->posY + img->dirY * img->moveSpeed)] == 0) 
        img->posY += img->dirY * img->moveSpeed;
    }
    if (keycode == 1)
    {   
      //move_down(img, worldMap); 
      if(worldMap[(int)(img->posX - img->dirX * img->moveSpeed)][(int)img->posY] == 0)     
        img->posX -= img->dirX * img->moveSpeed;
      if(worldMap[(int)img->posX][(int)(img->posY - img->dirY * img->moveSpeed)] == 0)
        img->posY -= img->dirY * img->moveSpeed;
    }
    if (keycode == 2)
    {
      rotate_right(img);
      /* double oldDirX = img->dirX;
      img->dirX = img->dirX * cos(-img->rotSpeed) - img->dirY * sin(-img->rotSpeed);
      img->dirY = oldDirX * sin(-img->rotSpeed) + img->dirY * cos(-img->rotSpeed);
      double oldPlaneX = img->planeX;
      img->planeX = img->planeX * cos(-img->rotSpeed) - img->planeY * sin(-img->rotSpeed);
      img->planeY = oldPlaneX * sin(-img->rotSpeed) + img->planeY * cos(-img->rotSpeed); */
    }
    if (keycode == 0)
    {
      rotate_left(img);
      double oldDirX = img->dirX;
      img->dirX = img->dirX * cos(img->rotSpeed) - img->dirY * sin(img->rotSpeed);
      img->dirY = oldDirX * sin(img->rotSpeed) + img->dirY * cos(img->rotSpeed);
      double oldPlaneX = img->planeX;
      img->planeX = img->planeX * cos(img->rotSpeed) - img->planeY * sin(img->rotSpeed);
      img->planeY = oldPlaneX * sin(img->rotSpeed) + img->planeY * cos(img->rotSpeed);
    }
	return (0);
}

 

 

int	carlos_main(t_state *state)
{
  t_data *img;

  img = &state->img;  
	img->img = mlx_new_image(state->mlx, screenWidth,  screenHeight );
  img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length,
								&img->endian);
  img->posX = 22, img->posY = 12;  //x and y start position
  img->dirX = -1, img->dirY = 0; //initial direction vector
  img->planeX = 0, img->planeY = 0.66; //the 2d raycaster version of camera planea
  img->Time = 0; //time of current frame
  img->Oldtime = 0; //time of previous frame
  load_textures(state);
  return (1);
}

int load_textures(t_state *state)
{
  t_data *img;
  int i;

  img = &state->img;
  img->w = 64;
  img->h = 64;
  i = -1;
  while(++i<3)
    img->texture[i] = malloc(sizeof(int) * texHeight * texWidth);
	void *t1 = mlx_xpm_file_to_image(state->mlx, "./pics/eagle.xpm", &img->w, &img->h);
    img->texture[0] =  (int*)mlx_get_data_addr(t1, &img->bits_per_pixel, &img->line_length, &img->endian);
	t1 = mlx_xpm_file_to_image(state->mlx, "./pics/mossy.xpm", &img->w, &img->h);
    img->texture[1] = (int*)mlx_get_data_addr(t1, &img->bits_per_pixel, &img->line_length, &img->endian);
	t1 = mlx_xpm_file_to_image(state->mlx, "./pics/face.xpm", &img->w, &img->h);
    img->texture[2] = (int*)mlx_get_data_addr(t1, &img->bits_per_pixel, &img->line_length, &img->endian);
	t1 = mlx_xpm_file_to_image(state->mlx, "./pics/stone.xpm", &img->w, &img->h);
    img->texture[3] = (int*)mlx_get_data_addr(t1, &img->bits_per_pixel, &img->line_length, &img->endian); 
  if (!t1)
    return (printf("Error, one or more files are not xpm\n"), 1); //<---HAY QUE MIRAR ESTA CONDICION
  return (1);
}




 