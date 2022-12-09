/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caquinta <caquinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 08:33:21 by caquinta          #+#    #+#             */
/*   Updated: 2022/12/09 09:23:14 by caquinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "state.h"
#include <math.h>
#include <sys/time.h>

long	get_time(void)
{
	struct timeval	now;
	long			milliseconds;

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
	*(unsigned int *)dst = color;
}

int	load_color_f_c(t_state *state)
{
	state->c = create_trgb(0, 234, 221, 202);
	state->f = create_trgb(0, 0, 0, 250);
	return (0);
}

int	assign_values(t_state *state)
{
	t_data	*img;

	img = &state->img;
	state->hit = 0;
	state->cameraX = 2 * state->x / (double)screenWidth - 1;
	state->rayDirX = img->dirX + img->planeX * state->cameraX;
	state->rayDirY = img->dirY + img->planeY * state->cameraX;
	state->mapX = (int)img->posX;
	state->mapY = (int)img->posY;
	if (state->rayDirX == 0)
		state->deltaDistX = 1e30;
	else
		state->deltaDistX = fabs(1 / state->rayDirX);
	if (state->rayDirY == 0)
		state->deltaDistY = 1e30;
	else
		state->deltaDistY = fabs(1 / state->rayDirY);
	state->hit = 0;
	return (0);
}

int	assign_values2(t_state *state)
{
	t_data	*img;

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
	return (0);
}

int	perform_dda(t_state *state, int worldmap[mapWidth][mapHeight])
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
		if (worldmap[state->mapX][state->mapY] > 0)
			state->hit = 1;
	}
	return (0);
}

int	calculate_dist(t_state *state)
{
	if (state->side == 0)
		state->perpWallDist = (state->sideDistX - state->deltaDistX);
	else
		state->perpWallDist = (state->sideDistY - state->deltaDistY);
	state->lineHeight = (int)(screenHeight / state->perpWallDist);
	state->drawStart = -state->lineHeight / 2 + screenHeight / 2;
	if (state->drawStart < 0)
		state->drawStart = 0;
	state->drawEnd = state->lineHeight / 2 + screenHeight / 2;
	if (state->drawEnd >= screenHeight)
		state->drawEnd = screenHeight - 1;
	return (0);
}

int	calculate_wall(t_state *state)
{
	t_data	*img;

	img = &state->img;
	if (state->side == 0)
		state->wallX = img->posY + state->perpWallDist * state->rayDirY;
	else
		state->wallX = img->posX + state->perpWallDist * state->rayDirX;
	state->wallX -= floor((state->wallX));
	state->texX = (int)(state->wallX * (double)(img->w));
	if (state->side == 0 && state->rayDirX > 0)
		state->texX = img->w - state->texX - 1;
	if (state->side == 1 && state->rayDirY < 0)
		state->texX = img->w - state->texX - 1;
	state->step = 1.0 * img->h / state->lineHeight;
	state->texPos = (state->drawStart - screenHeight / 2 + state->lineHeight
			/ 2) * state->step;
	return (0);
}

static int	draw_textures(t_state *state, int buffer[screenHeight][screenWidth])
{
	t_data	*img;

	img = &state->img;
	state->texY = (int)state->texPos & (img->h - 1);
	state->texPos += state->step;
	if (state->side == 1)
	{
		if (state->rayDirY <= 0)
			state->color = img->tex[0][img->h * state->texY + state->texX];
		else
			state->color = img->tex[2][img->h * state->texY + state->texX];
	}
	else
	{
		if (state->rayDirX <= 0)
			state->color = img->tex[1][img->h * state->texY + state->texX];
		else
			state->color = img->tex[3][img->h * state->texY + state->texX];
	}
	buffer[state->y][state->x] = state->color;
	return (0);
}

int	load_buffer(t_state *state, int buffer[screenHeight][screenWidth])
{
	t_data	*img;

	state->y = -1;
	img = &state->img;
	while (++state->y < screenHeight)
	{
		if (state->y <= state->drawStart)
			buffer[state->y][state->x] = state->f;
		else if (state->y >= state->drawEnd)
			buffer[state->y][state->x] = state->c;
		else
			draw_textures(state, buffer);
	}
	return (0);
}

int	load_pixels(t_state *state, int buffer[screenHeight][screenWidth])
{
	int	e;
	int	y;

	e = -1;
	while (++e < screenWidth)
	{
		y = 0;
		while (y < screenHeight)
		{
			my_mlx_pixel_put(&state->img, e, y, buffer[y][e]);
			y++;
		}
	}
	e = -1;
	while (++e < screenWidth)
	{
		y = 0;
		while (y < screenHeight)
		{
			buffer[y][e] = 0;
			y++;
		}
	}
	return (0);
}
