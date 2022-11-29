/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caquinta <caquinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 22:24:59 by manu              #+#    #+#             */
/*   Updated: 2022/11/29 10:35:23 by caquinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

// #include "image.h"
#include "state.h"
#include "error.h"
#include "ft_printf.h"
#include "mlx.h"
#include "libft.h"
// #include "collision.h"
// #include "monster.h"

int draw_map(t_state *state);

void	update_frame(t_state *state)
{
 
		draw_map(state);
 
}


int	on_render_frame(t_state *state)
{
	update_frame(state);
	// draw_map(state);



	return (1);
}
