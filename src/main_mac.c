/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_mac.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caquinta <caquinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 22:25:07 by manu              #+#    #+#             */
/*   Updated: 2022/12/05 09:52:23 by caquinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include "error.h"
#include "events.h"
#include "frame.h"
#include "ft_printf.h"
#include "libft.h"
#include "mlx.h"
#include "state.h"

int	carlos_main(t_state *state);

static void	init_hooks(t_state *state)
{
	mlx_hook (state->window, EVENT_ON_DESTROY, 0, exit_without_error, state);
	mlx_key_hook(state->window, on_key_pressed, state);
	mlx_loop_hook(state->mlx, on_render_frame, state);
}

int	main(int argc, char *argv[])
{
	t_state	state;

	if (argc != 2)
	{
		ft_printf("Error\nIncorrect arguments.Expected './cub3D map.cub'\n");
		return (0);
	}
/*  	if (!check_extension(argv[1], "cub"))
	{
		ft_printf("Error\nIncorrect map file extension\n");
		return (0);
	}  */
	if (!init_state(&state, argv[1]))
		exit_with_error(&state);
	carlos_main(&state);
	init_hooks(&state);
	mlx_loop(state.mlx);
	return (exit_without_error(&state));
}
