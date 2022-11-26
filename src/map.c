/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manu <manu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 22:25:24 by manu              #+#    #+#             */
/*   Updated: 2022/11/16 20:15:53 by manu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#include "array.h"
#include "array_display.h"
#include "error.h"
#include "ft_printf.h"
#include "get_next_line_bonus.h"
#include "map.h"
#include "libft.h"
#include "state.h"

static char	*load_map_file(t_state *state, int fd)
{
	char	*str_map;
	char	*line;
	char	*aux;

	line = get_next_line(fd);
	if (!line)
	{
		ft_printf("Error\nMap file is empty\n");
		exit_with_error(state);
	}
	str_map = NULL;
	while (line)
	{
		if (str_map)
		{
			aux = str_map;
			str_map = ft_strjoin(str_map, line);
			free(aux);
			free(line);
		}
		else
			str_map = line;
		line = get_next_line(fd);
	}
	return (str_map);
}

static char	*get_last_part_in_line(char *line)
{
	char	**parts;
	char	*last_part;
	int		len;

	parts = ft_split(line, ' ');
	len = count_str_in_array(parts);
	if (!len)
		last_part = ft_strdup("");
	else
		last_part = ft_strdup(parts[len - 1]);
	free_array(parts);
	return (last_part);
}

static char	*get_map_value(char **lines, char *key)
{
	int		count;
	char	*line;
	char	*value;

	value = NULL;
	if (!lines || !count_str_in_array(lines))
		return (value);
	count = 0;
	while (!value && lines && lines[count])
	{
		line = ft_strtrim(lines[count], " ");
		if (line)
		{
			if (!ft_strncmp(line, key, ft_strlen(key)))
				value = get_last_part_in_line(line);
			free(line);
		}
		count++;
	}
	return (value);
}

static int	is_valid_map_char(char c)
{
	if (c == TILE_FLOOR
		|| c == TILE_WALL
		|| c == TILE_EMPTY
		|| c == TILE_PLAYER_N
		|| c == TILE_PLAYER_S
		|| c == TILE_PLAYER_E
		|| c == TILE_PLAYER_W)
		return (1);
	return (0);
}

static int	is_first_grid_line(char *line)
{
	int		is_first;
	char	*aux;

	if (!ft_strlen(line))
	{
		free(line);
		return (0);
	}
	is_first = 1;
	aux = line;
	while (aux && *aux)
	{
		if (!is_valid_map_char(*aux))
		{
			is_first = 0;
			break ;
		}
		aux++;
	}
	return (is_first);
}

static char	**get_map_grid(char **lines)
{
	int		i;
	char	**grid;

	grid = NULL;
	i = 0;
	while (lines && !is_first_grid_line(lines[i]))
		i++;
	while (lines && lines[i])
	{
		grid = add_str_to_array(grid, lines[i]);
		i++;
	}
	return (grid);
}

static void	map_display(t_map *map)
{
	ft_printf("NO: %s\n", map->texture_no_path);
	ft_printf("SO: %s\n", map->texture_so_path);
	ft_printf("WE: %s\n", map->texture_we_path);
	ft_printf("EA: %s\n", map->texture_ea_path);
	ft_printf("F: %s\n", map->f);
	ft_printf("C: %s\n", map->c);
	ft_printf("The map grid:\n\n");
	array_display(map->grid);
}

static void	load_map_sections(t_state *state, char *str_map)
{
	char	**lines;

	lines = ft_split(str_map, '\n');
	state->map.texture_no_path = get_map_value(lines, "NO ");
	state->map.texture_so_path = get_map_value(lines, "SO ");
	state->map.texture_we_path = get_map_value(lines, "WE ");
	state->map.texture_ea_path = get_map_value(lines, "EA ");
	state->map.f = get_map_value(lines, "F ");
	state->map.c = get_map_value(lines, "C ");
	state->map.grid = get_map_grid(lines);
	map_display(&state->map);
	free_array(lines);
}

void	load_map(t_state *state, char *file_name)
{
	char	*str_map;
	int		fd;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		ft_printf("Error\nMap file does not exist: (%s)\n", file_name);
		exit_with_error(state);
	}
	str_map = load_map_file(state, fd);
	close(fd);
	if (!str_map)
	{
		ft_printf("Error\nMap file is invalid: (%s)\n", file_name);
		exit_with_error(state);
	}
	load_map_sections(state, str_map);
	free(str_map);
}

void	free_map(t_state *state)
{
	if (state->map.texture_no_path)
		free(state->map.texture_no_path);
	if (state->map.texture_so_path)
		free(state->map.texture_so_path);
	if (state->map.texture_we_path)
		free(state->map.texture_we_path);
	if (state->map.texture_ea_path)
		free(state->map.texture_ea_path);
	if (state->map.f)
		free(state->map.f);
	if (state->map.c)
		free(state->map.c);
	if (!state->map.grid)
		return ;
	free_array(state->map.grid);
}

void	set_tile(t_state *state, t_tile tile, int x, int y)
{
	state->map.grid[y][x] = tile;
}
