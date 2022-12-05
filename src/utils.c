/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caquinta <caquinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 08:33:21 by caquinta          #+#    #+#             */
/*   Updated: 2022/12/05 12:31:04 by caquinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h> 
#include "state.h"

long    get_time(void)
{
    struct timeval  now;
    long            milliseconds;
    gettimeofday(&now, NULL);
    milliseconds = (now.tv_sec * 1000) + (now.tv_usec / 1000);
    return (milliseconds);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	* (unsigned int*)dst = color;
}

int assign_values(t_state *state)
{
    t_data *img;

    img = &state->img;
        
    state->cameraX = 2 * state->x / (double)screenWidth - 1; //x-coordinate in camera space
    state->rayDirX = img->dirX + img->planeX * state->cameraX;
    state->rayDirY = img->dirY + img->planeY * state->cameraX;
    state->mapX = (int)img->posX;
    state->mapY = (int)img->posY;
    if(state->rayDirX == 0)
        state->deltaDistX = 1e30;
    else
        state->deltaDistX = fabs(1 / state->rayDirX);
    if(state->rayDirY == 0)
        state->deltaDistY = 1e30;
    else
        state->deltaDistY = fabs(1 / state->rayDirX);  
    state->hit = 0; //was there a wall hit?
  
  return(0);
}

int assign_values2(t_state *state)
{
    t_data *img;

    img = &state->img;   
      if (state->rayDirX < 0)
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
      }
    return(0);
}

int perform_DDA(t_state *state)
{
      while (state->hit == 0)
      {
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
        if (worldMap[mapX][mapY] > 0) 
          state->hit = 1;
      }    
}

int calculate_dist(t_state *state)
{
  if(state->side == 0)
    state->perpWallDist = (state->sideDistX - state->deltaDistX);
  else        
    state->perpWallDist = (state->sideDistY - state->deltaDistY);
  state->lineHeight = (int)(screenHeight/ state->perpWallDist);
  state->drawStart = -state->lineHeight / 2 + screenHeight / 2;
  if(state->drawStart < 0)
    state->drawStart = 0;
  state->drawEnd = state->lineHeight / 2 + screenHeight / 2;
  if(state->drawEnd >= screenHeight)
    state->drawEnd = screenHeight - 1; 
}