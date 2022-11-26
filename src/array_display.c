/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manu <manu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 19:57:12 by manu              #+#    #+#             */
/*   Updated: 2022/11/14 20:39:51 by manu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	array_display(char **array)
{
	int	count;

	count = 0;
	while (array && array[count])
	{
		ft_printf("%s\n", array[count]);
		count++;
	}
}
