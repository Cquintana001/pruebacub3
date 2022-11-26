/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manu <manu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 13:51:42 by manu              #+#    #+#             */
/*   Updated: 2022/11/11 13:51:43 by manu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_H
# define ARRAY_H

void	free_array(char **array);
int		count_str_in_array(char **array);
char	**add_str_to_array(char **array, char *str);
char	**duplicate_array(char **array);
char	**del_str_from_array(char **array, char *str);

#endif
