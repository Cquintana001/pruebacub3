/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manu <manu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 22:23:30 by manu              #+#    #+#             */
/*   Updated: 2022/11/15 19:09:31 by manu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H

# include "state.h"

enum {
	EVENT_KEY_ESC = 53,
	EVENT_KEY_W = 13,
	EVENT_KEY_A = 0,
	EVENT_KEY_S = 1,
	EVENT_KEY_D = 2,
	EVENT_KEY_LEFT = 123,
	EVENT_KEY_RIGHT = 124,
	EVENT_ON_DESTROY = 17,
};

int	on_key_pressed(int key, t_state *state);

#endif
