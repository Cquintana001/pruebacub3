/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caquinta <caquinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 10:27:01 by caquinta          #+#    #+#             */
/*   Updated: 2022/12/05 10:32:57 by caquinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOVES_H
# define MOVES_H

# include "state.h"

int move_up(t_data *img, int *worldMap[]);
int move_down(t_data *img, int *worldMap[]);
int rotate_right(t_data *img);
int rotate_left(t_data *img);

#endif