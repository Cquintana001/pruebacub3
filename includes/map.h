/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manu <manu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 22:23:55 by manu              #+#    #+#             */
/*   Updated: 2022/11/16 20:18:10 by manu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "state.h"

typedef enum e_tile {
	TILE_FLOOR = '0',
	TILE_WALL = '1',
	TILE_EMPTY = ' ',
	TILE_PLAYER_N = 'N',
	TILE_PLAYER_S = 'S',
	TILE_PLAYER_E = 'E',
	TILE_PLAYER_W = 'W',
}	t_tile;

void	load_map(t_state *state, char *file_name);
void	free_map(t_state *state);
void	set_tile(t_state *state, t_tile tile, int x, int y);

#endif
