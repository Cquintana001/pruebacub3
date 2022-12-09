/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caquinta <caquinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 10:14:14 by caquinta          #+#    #+#             */
/*   Updated: 2022/12/09 09:29:19 by caquinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "state.h"
#include <math.h>

int	move_up(t_data *img, int *worldMap[])
{
	if (worldMap[(int)(img->posX + (img->dirX
				* img->moveSpeed))][(int)img->posY] == 0)
		img->posX += img->dirX * img->moveSpeed;
	if (worldMap[(int)img->posX][(int)(img->posY + img->dirY
		* img->moveSpeed)] == 0)
		img->posY += img->dirY * img->moveSpeed;
	return (0);
}

int	move_down(t_data *img, int *worldMap[])
{
	if (worldMap[(int)(img->posX - img->dirX
			* img->moveSpeed)][(int)img->posY] == 0)
		img->posX -= img->dirX * img->moveSpeed;
	if (worldMap[(int)img->posX][(int)(img->posY - img->dirY
		* img->moveSpeed)] == 0)
		img->posY -= img->dirY * img->moveSpeed;
	return (0);
}

int	rotate_right(t_data *img)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = img->dirX;
	img->dirX = img->dirX * cos(-img->rotSpeed) - img->dirY
		* sin(-img->rotSpeed);
	img->dirY = old_dirx * sin(-img->rotSpeed) + img->dirY * cos(-img->rotSpeed);
	old_planex = img->planeX;
	img->planeX = img->planeX * cos(-img->rotSpeed) - img->planeY
		* sin(-img->rotSpeed);
	img->planeY = old_planex * sin(-img->rotSpeed) + img->planeY
		* cos(-img->rotSpeed);
	return (0);
}

int	rotate_left(t_data *img)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = img->dirX;
	img->dirX = img->dirX * cos(img->rotSpeed) - img->dirY * sin(img->rotSpeed);
	img->dirY = old_dirx * sin(img->rotSpeed) + img->dirY * cos(img->rotSpeed);
	old_planex = img->planeX;
	img->planeX = img->planeX * cos(img->rotSpeed) - img->planeY
		* sin(img->rotSpeed);
	img->planeY = old_planex * sin(img->rotSpeed) + img->planeY
		* cos(img->rotSpeed);
	return (0);
}
