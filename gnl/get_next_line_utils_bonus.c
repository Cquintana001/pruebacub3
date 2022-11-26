/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manugarc <manugarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 13:27:52 by manugarc          #+#    #+#             */
/*   Updated: 2022/04/30 16:27:23 by manugarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include <errno.h>
#include "get_next_line_bonus.h"

char	*ft_strchr(const char *s, int c)
{
	char	*str;

	str = (char *)s;
	while (*str)
	{
		if ((*str) == (char)c)
			return (str);
		str++;
	}
	if (c == 0)
		return (str);
	return (NULL);
}

size_t	ft_strlen(const char *str)
{
	size_t	number_characters;

	number_characters = 0;
	while (str && *str)
	{
		str++;
		number_characters++;
	}
	return (number_characters);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	copy_index;
	int		src_len_reached;

	if (!size || !src || !dest)
		return (ft_strlen(src));
	copy_index = 0;
	src_len_reached = 0;
	while ((copy_index < size - 1) && src[copy_index] != '\0')
	{
		dest[copy_index] = src[copy_index];
		copy_index++;
	}
	dest[copy_index] = '\0';
	return (ft_strlen(src));
}

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	cont;
	size_t	len_src;
	size_t	len_dest;

	len_src = ft_strlen((char *)src);
	len_dest = ft_strlen((char *)dest);
	if (!dest || !src || size < 1 || size <= len_dest)
		return (len_src + size);
	cont = 0;
	while ((cont + len_dest) < (size - 1) && src[cont])
	{
		dest[len_dest + cont] = src[cont];
		cont++;
	}
	dest[len_dest + cont] = '\0';
	return (len_src + len_dest);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*str;
	size_t	len_s1;
	size_t	len_s2;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	if (len_s1 + len_s2 == 0)
	{
		str = malloc(1);
		*str = '\0';
		return (str);
	}
	str = malloc(len_s1 + len_s2 + 1);
	if (!str)
	{
		errno = ENOMEM;
		return (NULL);
	}
	ft_strlcpy(str, s1, len_s1 + 1);
	ft_strlcat(str, s2, len_s1 + len_s2 + 1);
	return (str);
}
