/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manu <manu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 22:24:43 by manu              #+#    #+#             */
/*   Updated: 2022/11/10 22:24:44 by manu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "state.h"
#include "error.h"

static void	exit_with_code(int code, t_state *state)
{
	free_state(state);
	exit(code);
}

int	exit_with_error(t_state *state)
{
	exit_with_code(ERROR_GENERIC, state);
	return (0);
}

int	exit_without_error(t_state *state)
{
	exit_with_code(ERROR_NONE, state);
	return (0);
}
