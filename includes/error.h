/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manu <manu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 22:23:22 by manu              #+#    #+#             */
/*   Updated: 2022/11/10 22:26:33 by manu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "state.h"

# define ERROR_NONE			0
# define ERROR_GENERIC		1

int	exit_with_error(t_state *state);
int	exit_without_error(t_state *state);

#endif
