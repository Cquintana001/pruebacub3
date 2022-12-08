/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caquinta <caquinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 22:24:50 by manu              #+#    #+#             */
/*   Updated: 2022/12/08 12:15:58 by caquinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include "error.h"
// #include "hero.h"
#include "state.h"
#include <stdio.h>

int	key_hook(int keycode, t_state *state);

int press_key(int keycode, t_state *state)
{
	if (keycode == EVENT_KEY_ESC)
		exit_without_error(state);
	if(keycode==13)
		state->up = 1; 
	if(keycode==0)
		state->left = 1;
	if(keycode==1)
		state->down = 1; 
	if(keycode==2)
		state->right = 1;
	return(0);
}
 int key_release(int keycode, t_state *state)
{
	if(keycode==13)
		state->up = 0; 
	if(keycode==0)
		state->left = 0;
	if(keycode==1)
		state->down = 0; 
	if(keycode==2)
		state->right = 0;  
	return(0);
}  
int	on_key_pressed(int key_code, t_state *state)
{
	 
	if (key_code == EVENT_KEY_ESC)
		exit_without_error(state);
  key_hook(key_code, state);
	return (0);
}

 
