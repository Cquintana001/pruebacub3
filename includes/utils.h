/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caquinta <caquinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 09:16:38 by caquinta          #+#    #+#             */
/*   Updated: 2022/12/09 09:40:02 by caquinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "state.h"

long    get_time(void);
int	create_trgb(int t, int r, int g, int b);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int assign_values(t_state *state);
int assign_values2(t_state *state);
int perform_dda(t_state *state, int worldMap[mapWidth][mapHeight]);
int calculate_dist(t_state *state);
int calculate_wall(t_state *state);
int load_buffer(t_state *state, int buffer[screenHeight][screenWidth]);
int draw(t_state *state, int buffer[screenHeight][screenWidth]);
int load_pixels(t_state *state, int buffer[screenHeight][screenWidth]);
int load_color_f_c(t_state *state);
 
#endif