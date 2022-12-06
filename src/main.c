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
      /* state->cameraX = 2 * state->x / (double)screenWidth - 1;  
      state->rayDirX = img->dirX + img->planeX * state->cameraX;
      state->rayDirY = img->dirY + img->planeY * state->cameraX;

 
      state->mapX = (int)img->posX;
      state->mapY = (int)img->posY;
 
    if(state->rayDirX == 0)
      {  state->deltaDistX = 1e30;
      }
    else
      {
        state->deltaDistX = fabs(1 / state->rayDirX);
      }
    if(state->rayDirY == 0)
    {
        state->deltaDistY = 1e30;
    }
    else
    {
        state->deltaDistY = fabs(1 / state->rayDirY);
    } 
 state->deltaDistX = (state->rayDirX == 0) ? 1e30 : fabs(1 / state->rayDirX);
    state->deltaDistY = (state->rayDirY == 0) ? 1e30 : fabs(1 / state->rayDirY); */
    state->hit = 0; //was there a wall hit?
 
  
      assign_values(state);
       //was a NS or a EW wall hit?
      /* if (state->rayDirX < 0)
      {
        state->stepX = -1;
        state->sideDistX = (img->posX - state->mapX) * state->deltaDistX;
      }
      else
      {
        state->stepX = 1;
        state->sideDistX = (state->mapX + 1.0 - img->posX) * state->deltaDistX;
      }
      if (state->rayDirY < 0)
      {
        state->stepY = -1;
        state->sideDistY = (img->posY - state->mapY) * state->deltaDistY;
      }
      else
      {
        state->stepY = 1;
        state->sideDistY = (state->mapY + 1.0 - img->posY) * state->deltaDistY;
      } */
      assign_values2(state);
      //perform DDA
     /*  while (state->hit == 0)
      {
        //jump to next map square, either in x-direction, or in y-direction
        if (state->sideDistX < state->sideDistY)
        {
          state->sideDistX += state->deltaDistX;
          state->mapX += state->stepX;
          state->side = 0;
        }
        else
        {
          state->sideDistY += state->deltaDistY;
          state->mapY += state->stepY;
          state->side = 1;
        }
        //Check if ray has hit a wall
        if (worldMap[state->mapX][state->mapY] > 0) 
          state->hit = 1;
      }  */
      perform_DDA(state, worldMap);
      //Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
      /* if(state->side == 0)
      { 
        state->perpWallDist = (state->sideDistX - state->deltaDistX);
      }
      else
      {          
        state->perpWallDist = (state->sideDistY - state->deltaDistY);
      }
      //Calculate height of line to draw on screen
      state->lineHeight = (int)(screenHeight/ state->perpWallDist);
      //calculate lowest and highest pixel to fill in current stripe
      state->drawStart = -state->lineHeight / 2 + screenHeight / 2;
      if(state->drawStart < 0)
      {
        state->drawStart = 0;
      }
      state->drawEnd = state->lineHeight / 2 + screenHeight / 2;
      if(state->drawEnd >= screenHeight)
      {
        state->drawEnd = screenHeight - 1;
      } */
      calculate_dist(state);
 
     /*  if (state->side == 0) state->wallX = img->posY + state->perpWallDist * state->rayDirY;
      else           state->wallX = img->posX + state->perpWallDist * state->rayDirX;
      state->wallX -= floor((state->wallX));

      //x coordinate on the texture
      state->texX = (int)(state->wallX * (double)(texWidth));
      if(state->side == 0 && state->rayDirX > 0) state->texX = texWidth - state->texX - 1;
      if(state->side == 1 && state->rayDirY < 0) state->texX = texWidth - state->texX - 1;
      //choose wall color
      // How much to increase the texture coordinate per screen pixel
      state->step = 1.0 * texHeight / state->lineHeight;
      // Starting texture coordinate
     state->texPos = (state->drawStart -screenHeight / 2 + state->lineHeight / 2) * state->step; */
     calculate_wall(state);
      /* for(int y = state->drawStart; y<state->drawEnd; y++)
      {
        // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
      state->texY = (int)state->texPos & (texHeight - 1);
        state->texPos += state->step;
        int color;
        if(state->side == 1) 
        { 
          if(state->rayDirY<=0) 
            color = img->texture[0][texHeight * state->texY + state->texX];
          else
            color = img->texture[2][texHeight * state->texY + state->texX];
        }
        else
        {  if(state->rayDirX<=0) 
          color = img->texture[1][texHeight * state->texY + state->texX];
           else
            color = img->texture[3][texHeight * state->texY + state->texX];
        }
     

        buffer[y][state->x] = color;
      } */
      load_buffer(state, buffer);
	    state->x++;
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
    img->tex[i] = malloc(sizeof(int) * texHeight * texWidth);
	void *t1 = mlx_xpm_file_to_image(state->mlx, "./pics/eagle.xpm", &img->w, &img->h);
    img->tex[0] =  (int*)mlx_get_data_addr(t1, &img->bits_per_pixel, &img->line_length, &img->endian);
	t1 = mlx_xpm_file_to_image(state->mlx, "./pics/mossy.xpm", &img->w, &img->h);
    img->tex[1] = (int*)mlx_get_data_addr(t1, &img->bits_per_pixel, &img->line_length, &img->endian);
	t1 = mlx_xpm_file_to_image(state->mlx, "./pics/face.xpm", &img->w, &img->h);
    img->tex[2] = (int*)mlx_get_data_addr(t1, &img->bits_per_pixel, &img->line_length, &img->endian);
	t1 = mlx_xpm_file_to_image(state->mlx, "./pics/stone.xpm", &img->w, &img->h);
    img->tex[3] = (int*)mlx_get_data_addr(t1, &img->bits_per_pixel, &img->line_length, &img->endian); 
  if (!t1)
    return (printf("Error, one or more files are not xpm\n"), 1); //<---HAY QUE MIRAR ESTA CONDICION
  return (1);
}




 