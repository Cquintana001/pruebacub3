/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manu <manu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 20:21:45 by manu              #+#    #+#             */
/*   Updated: 2022/05/09 00:10:02 by manu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "utils.h"

int	ft_putchar(int c)
{
	return (write(1, &c, 1));
}

int	ft_putstring(char *str)
{
	int	len;

	if (!str)
	{
		write(1, "(null)", 6);
		return (6);
	}
	len = 0;
	while (str[len])
		len += ft_putchar(str[len]);
	return (len);
}

int	ft_putnumbr_base(unsigned long numbr, int base, bool in_uppercase)
{
	int	len;

	len = 0;
	if (numbr >= base)
	{
		len += ft_putnumbr_base(numbr / base, base, in_uppercase);
		len += ft_putnumbr_base(numbr % base, base, in_uppercase);
	}
	else
	{
		if (numbr >= 10 && base == 16)
		{
			if (in_uppercase == true)
				len += ft_putchar(numbr - 10 + 'A');
			else
				len += ft_putchar(numbr - 10 + 'a');
		}
		else
			len += ft_putchar(numbr + '0');
	}
	return (len);
}

int	ft_put_signed_number(long numbr)
{
	int	len;

	len = 0;
	if (numbr < 0)
	{
		len += ft_putchar('-');
		numbr *= -1;
	}
	len += ft_putnumbr_base(numbr, 10, false);
	return (len);
}

int	ft_put_pointer(unsigned long ptr)
{
	int	len;

	len = 0;
	len += ft_putstring("0x");
	len += ft_putnumbr_base(ptr, 16, false);
	return (len);
}
