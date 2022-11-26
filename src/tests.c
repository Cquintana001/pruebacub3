/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manu <manu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 22:25:38 by manu              #+#    #+#             */
/*   Updated: 2022/11/10 22:25:40 by manu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>

#include "check_extension.h"

int	main(int argc, char *argv[])
{
	assert(check_extension("map.cub", "cub") == 1);
	assert(check_extension("map.ber", "cub") == 0);
	(void)argc;
	(void)argv;
	return (0);
}
