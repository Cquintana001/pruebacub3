/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caquinta <caquinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 22:24:50 by manu              #+#    #+#             */
/*   Updated: 2022/11/29 10:30:12 by caquinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include "error.h"
// #include "hero.h"
#include "state.h"
#include <stdio.h>

int	key_hook(int keycode, t_state *state);

int	on_key_pressed(int key_code, t_state *state)
{
	 
	if (key_code == EVENT_KEY_ESC)
		exit_without_error(state);
  key_hook(key_code, state);
	return (0);
}
