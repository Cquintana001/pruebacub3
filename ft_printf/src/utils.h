/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manu <manu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 18:45:30 by manu              #+#    #+#             */
/*   Updated: 2022/05/09 00:08:55 by manu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdbool.h>

int	ft_putchar(int c);
int	ft_putstring(char *str);
int	ft_put_signed_number(long numbr);
int	ft_putnumbr_base(unsigned long numbr, int base, bool in_uppercase);
int	ft_put_pointer(unsigned long ptr);

#endif