/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caquinta <caquinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 10:14:14 by caquinta          #+#    #+#             */
/*   Updated: 2022/12/05 11:22:12 by caquinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "state.h"
#include <math.h>

int move_up(t_data *img, int *worldMap[])
{
      if(worldMap[(int)(img->posX + (img->dirX * img->moveSpeed))][(int)img->posY] == 0) 
        img->posX += img->dirX * img->moveSpeed;
      if(worldMap[(int)img->posX][(int)(img->posY + img->dirY * img->moveSpeed)] == 0) 
        img->posY += img->dirY * img->moveSpeed;
    return (0);   
}

int move_down(t_data *img, int *worldMap[])
{
    if(worldMap[(int)(img->posX - img->dirX * img->moveSpeed)][(int)img->posY] == 0)     
        img->posX -= img->dirX * img->moveSpeed;
    if(worldMap[(int)img->posX][(int)(img->posY - img->dirY * img->moveSpeed)] == 0)
        img->posY -= img->dirY * img->moveSpeed;
    return (0);
}

int rotate_right(t_data *img)
{
    double oldDirX = img->dirX;
    img->dirX = img->dirX * cos(-img->rotSpeed) - img->dirY * sin(-img->rotSpeed);
    img->dirY = oldDirX * sin(-img->rotSpeed) + img->dirY * cos(-img->rotSpeed);
    double oldPlaneX = img->planeX;
    img->planeX = img->planeX * cos(-img->rotSpeed) - img->planeY * sin(-img->rotSpeed);
    img->planeY = oldPlaneX * sin(-img->rotSpeed) + img->planeY * cos(-img->rotSpeed);
    return (0);
}
int rotate_left(t_data *img)
{
    double oldDirX = img->dirX;
    img->dirX = img->dirX * cos(img->rotSpeed) - img->dirY * sin(img->rotSpeed);
    img->dirY = oldDirX * sin(img->rotSpeed) + img->dirY * cos(img->rotSpeed);
    double oldPlaneX = img->planeX;
    img->planeX = img->planeX * cos(img->rotSpeed) - img->planeY * sin(img->rotSpeed);
    img->planeY = oldPlaneX * sin(img->rotSpeed) + img->planeY * cos(img->rotSpeed);
    return (0);
}