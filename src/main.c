#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <memory.h>
#include <math.h>
#include "mlx.h"
#include <sys/time.h> 
#include "state.h"


#define mapWidth 24
#define mapHeight 24

// Movidos a state.h
// #define screenWidth 1920
// #define screenHeight 1080
/* long	get_time(void)
{
	struct timeval	tp;
	long			milliseconds;

	gettimeofday(&tp, NULL);
	milliseconds = tp.tv_sec;
	milliseconds += tp.tv_usec;
  printf("get_time: %ld\n", milliseconds);
	return (milliseconds);
} */
long    get_time(void)
{
    struct timeval  now;
    long            milliseconds;
    gettimeofday(&now, NULL);
    milliseconds = (now.tv_sec * 1000) + (now.tv_usec / 1000);
    return (milliseconds);
}
int global;

 

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

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}
// typedef struct	s_data {
// 	void	*img;
// 	char	*addr;
// 	int		bits_per_pixel;
// 	int		line_length;
// 	int		endian;
//   int posX;
//   int posY;
//   int dirY;
//   int dirX;
//   double moveSpeed;
//   double rotSpeed;
//   double planeX;
//   double planeY;
//   void *mlx1;
//   void *mlx1_win;
//   double Oldtime;
//   double Time;
// }				t_data;
 void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
} 
 void	*g_img;

int get_map_tile(int mapX, int mapY)
{

  if (mapX >= mapWidth)
    printf("get_map_tile x fuera de rango (%d)", mapX);
  return worldMap[mapX][mapY];
}

int draw_map(t_state *state)
{

  t_data *img;

  img = &state->img;
  mlx_destroy_image(state->mlx, img->img);
  img->img = mlx_new_image(state->mlx, screenWidth,  screenHeight );
  img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length,
								&img->endian);
  int x = 0;
  while(x<screenWidth)
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
      int side; //was a NS or a EW wall hit?
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
      //choose wall color
     int color;
      // switch(worldMap[mapX][mapY])
      switch(get_map_tile(mapX, mapY))
      {
        case 1:  color = create_trgb(240,255,0,0);  break; //red
        case 2:  color = 0x00008000;  break; //green
        case 3:  color = 0x000000FF;  break; //blue
        case 4:  color = 0x00FFFFFF;  break; //white
        default: color = 0x00FFFF00;  break; //yellow
      } 
      if (side == 1) {color = color / 2;}       
        while(drawStart<drawEnd)
          {
           
            my_mlx_pixel_put(img,  x, drawStart, color );
            drawStart++;
          }      
	    x++;
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
  
  printf("Key code pressed: (%d), (posX = %f), (posY = %f), (dirX = %f), (dirY = %f), (planeX = %f), (planeY = %f)\n", keycode, img->posX, img->posY, img->dirX, img->dirY, img->planeX, img->planeY);

if (keycode == 13)
    {
      if(worldMap[(int)(img->posX + (img->dirX * img->moveSpeed))][(int)img->posY] == 0) {img->posX += img->dirX * img->moveSpeed;}
      if(worldMap[(int)img->posX][(int)(img->posY + img->dirY * img->moveSpeed)] == 0) {img->posY += img->dirY * img->moveSpeed;}
    }
    //move backwards if no wall behind you
    if (keycode == 1)
    {
      
      if(worldMap[(int)(img->posX - img->dirX * img->moveSpeed)][(int)img->posY] == 0)
      { 
       
        img->posX -= img->dirX * img->moveSpeed;
      }
      if(worldMap[(int)img->posX][(int)(img->posY - img->dirY * img->moveSpeed)] == 0)
      {
      
       img->posY -= img->dirY * img->moveSpeed;
      }
    }
    //rotate to the right
    if (keycode == 2)
    {
      //both camera direction and camera plane must be rotated
      double oldDirX = img->dirX;
      img->dirX = img->dirX * cos(-img->rotSpeed) - img->dirY * sin(-img->rotSpeed);
      img->dirY = oldDirX * sin(-img->rotSpeed) + img->dirY * cos(-img->rotSpeed);
      double oldPlaneX = img->planeX;
      img->planeX = img->planeX * cos(-img->rotSpeed) - img->planeY * sin(-img->rotSpeed);
      img->planeY = oldPlaneX * sin(-img->rotSpeed) + img->planeY * cos(-img->rotSpeed);
    }
    //rotate to the left
    if (keycode == 0)
    {
      //both camera direction and camera plane must be rotated
      double oldDirX = img->dirX;
      img->dirX = img->dirX * cos(img->rotSpeed) - img->dirY * sin(img->rotSpeed);
      img->dirY = oldDirX * sin(img->rotSpeed) + img->dirY * cos(img->rotSpeed);
      double oldPlaneX = img->planeX;
      img->planeX = img->planeX * cos(img->rotSpeed) - img->planeY * sin(img->rotSpeed);
      img->planeY = oldPlaneX * sin(img->rotSpeed) + img->planeY * cos(img->rotSpeed);
    }
    
    // draw_map(state);
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
  img->planeX = 0, img->planeY = 0.66; //the 2d raycaster version of camera plane
  img->Time = 0; //time of current frame
  img->Oldtime = 0; //time of previous frame

 
	 
  return (1);
}




 