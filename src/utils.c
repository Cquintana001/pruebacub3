/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caquinta <caquinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 08:33:21 by caquinta          #+#    #+#             */
/*   Updated: 2022/12/05 09:25:17 by caquinta         ###   ########.fr       */
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