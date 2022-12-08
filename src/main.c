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
 int	key_hook( t_state *state);
 

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
  key_hook(state);
  while(state->x<screenWidth)
	{ 
    assign_values(state);      
    assign_values2(state);      
    perform_DDA(state, worldMap);     
    calculate_dist(state);     
    calculate_wall(state);
    load_color_f_c(state);
    load_buffer(state, buffer);      
	  state->x++;
  }
  load_pixels(state, buffer);
  img->Oldtime = img->Time;
  img->Time = get_time();
  double frameTime = (img->Time - img->Oldtime)/1000; //frameTime is the time this frame has taken, in seconds
  mlx_put_image_to_window(state->mlx, state->window, img->img, 0, 0);
  img->moveSpeed = frameTime * 2.0; //the constant value is in squares/second
  img->rotSpeed = frameTime * 2.0; //the constant value is in radians/second
  return(0);
}

 int	key_hook(t_state *state)
{
  t_data *img;

  img = &state->img;
   
    if (state->up==1)
    {
      if(worldMap[(int)(img->posX + (img->dirX * img->moveSpeed))][(int)img->posY] == 0) 
        img->posX += img->dirX * img->moveSpeed;
      if(worldMap[(int)img->posX][(int)(img->posY + img->dirY * img->moveSpeed)] == 0) 
        img->posY += img->dirY * img->moveSpeed;
    }
    if (state->down == 1)
    {  
      if(worldMap[(int)(img->posX - img->dirX * img->moveSpeed)][(int)img->posY] == 0)     
        img->posX -= img->dirX * img->moveSpeed;
      if(worldMap[(int)img->posX][(int)(img->posY - img->dirY * img->moveSpeed)] == 0)
        img->posY -= img->dirY * img->moveSpeed;
    }
    if (state->right == 1)
      rotate_right(img);
    if (state->left==1)
      rotate_left(img);
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
  state->up = 0;
  state->down = 0;
  state->right = 0;
  state->left = 0;
  
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




 