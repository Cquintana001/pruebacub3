/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manu <manu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 13:51:26 by manu              #+#    #+#             */
/*   Updated: 2022/11/11 13:51:27 by manu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_malloc.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array && array[i])
	{
		if (array[i])
			free(array[i]);
		i++;
	}
	if (array)
		free(array);
}

int	count_str_in_array(char **array)
{
	int	count;

	count = 0;
	while (array && array[count])
		count++;
	return (count);
}

char	**add_str_to_array(char **array, char *str)
{
	char	**new;
	int		count;
	int		i;

	count = count_str_in_array(array);
	new = ft_malloc((count + 2) * sizeof(char *));
	i = 0;
	while (i < count && array && array[i])
	{
		new[i] = ft_strdup(array[i]);
		i++;
	}
	new[i] = ft_strdup(str);
	new[i + 1] = NULL;
	free_array(array);
	return (new);
}

char	**del_str_from_array(char **array, char *str)
{
	char	**new;
	int		count;
	int		array_index;
	int		new_index;

	count = count_str_in_array(array);
	new = (char **) ft_malloc((count + 1) * sizeof(char *));
	array_index = 0;
	new_index = 0;
	while (array_index < count && array && array[array_index])
	{
		if (ft_strncmp(str, array[array_index], ft_strlen(str)) != 0)
		{
			new[new_index] = ft_strdup(array[array_index]);
			new_index++;
		}
		array_index++;
	}
	new[new_index] = NULL;
	free_array(array);
	return (new);
}

char	**duplicate_array(char **array)
{
	char	**new;
	int		count;
	int		i;

	count = count_str_in_array(array);
	new = (char **) ft_malloc((count + 1) * sizeof(char *));
	i = 0;
	while (i < count && array && array[i])
	{
		new[i] = ft_strdup(array[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}
