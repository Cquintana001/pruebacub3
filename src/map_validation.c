/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manu <manu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 22:25:15 by manu              #+#    #+#             */
/*   Updated: 2022/11/16 20:20:46 by manu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>

#include "libft.h"
#include "ft_printf.h"
#include "get_next_line_bonus.h"
#include "state.h"
#include "error.h"
#include "map.h"

static int	count_number_tiles(char *row, t_tile tile)
{
	int	col;
	int	n_tiles;

	col = 0;
	n_tiles = 0;
	while (row[col])
	{
		if ((t_tile) row[col] == tile)
			n_tiles++;
		col++;
	}
	return (n_tiles);
}

static int	get_height(t_map *map)
{
	int	height;

	height = 0;
	while (map->grid[height])
		height++;
	return (height);
}

static int	is_valid_row(t_state *state, char *row)
{
	if (!row)
		return (0);
	if ((int) ft_strlen(row) < 3)
		return (0);
	state->map.n_players += count_number_tiles(row, TILE_PLAYER_N);
	state->map.n_players += count_number_tiles(row, TILE_PLAYER_S);
	state->map.n_players += count_number_tiles(row, TILE_PLAYER_E);
	state->map.n_players += count_number_tiles(row, TILE_PLAYER_W);
	return (1);
}

static int	has_textures(t_map *map)
{
	if (!map || !map->texture_no_path || !map->texture_so_path
		|| !map->texture_we_path || !map->texture_ea_path)
		return (0);
	return (1);
}

int	is_valid_map(t_state *state)
{
	int	height;

	if (!has_textures(&state->map))
		return (0);
	height = get_height(&state->map);
	// state->map.width = ft_strlen((state->map.grid)[0]);
	state->map.height = 0;
	while (state->map.grid[state->map.height])
	{
		if (!is_valid_row(state, state->map.grid[state->map.height]))
			return (0);
		state->map.height++;
	}
	// if (state->map.width < 3 || state->map.height < 3)
	// 	return (0);
	if (state->map.n_players != 1)
	{
		return (0);
	}
	return (1);
}
