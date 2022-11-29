/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caquinta <caquinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 22:25:32 by manu              #+#    #+#             */
/*   Updated: 2022/11/29 11:19:19 by caquinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>

#include "state.h"
#include "libft.h"
#include "ft_printf.h"

int	init_state(t_state *state, char *map_file_name)
{
	map_file_name = "hola";
	ft_memset(state, 0, sizeof(t_state));
	state->mlx = mlx_init();
	state->window = mlx_new_window(state->mlx, screenWidth, screenHeight,
			"cub3D");
	return (1);
}

 
int	free_state(t_state *state)
{
	if (state->mlx && state->window)
	{
		mlx_destroy_window(state->mlx, state->window);
		mlx_destroy(state->mlx);
		state->mlx = NULL;
	}

	ft_memset(state, 0, sizeof(t_state));
	return (1);
}
