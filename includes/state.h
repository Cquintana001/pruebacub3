/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caquinta <caquinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 22:24:05 by manu              #+#    #+#             */
/*   Updated: 2022/11/19 12:06:06 by caquinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATE_H
# define STATE_H

# define MAX_IMAGE_PER_ANIMATION	10
# define TIME_PER_ANIMATION_FRAME	5

# define screenWidth 1920
# define screenHeight 1080

typedef struct s_image
{
	void		*img;
	int			width;
	int			height;
	int			x;
	int			y;
}	t_image;

typedef struct s_animation
{
	t_image	image[MAX_IMAGE_PER_ANIMATION];
	int		n_images;
	int		n_image;
	int		time;
	int		x;
	int		y;
}	t_animation;

typedef struct s_map
{
	char		**grid;
	int			width;
	int			height;
	int			n_players;
	char		*texture_no_path;
	char		*texture_so_path;
	char		*texture_we_path;
	char		*texture_ea_path;
	// TODO: f & c to RGB colors
	char		*f;
	char		*c;
}	t_map;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	double	posX;
	double	posY;
	double	dirY;
	double	dirX;
	double	moveSpeed;
	double	rotSpeed;
	double	planeX;
	double	planeY;
	// void	*mlx1;
	// void	*mlx1_win;
	double	Oldtime;
	double	Time;
}	t_data;

typedef struct s_state
{
	t_map		map;
	void		*mlx;
	void		*window;
	t_animation	hero;
	t_animation	monster;
	int			monster_last_axis_move;
	t_image		floor;
	t_image		exit;
	t_image		wall;
	t_image		collectible;
	int			n_hero_moves;
	int			n_collectibles;
	int			time;
	t_data		img;
}	t_state;

int	init_state(t_state *state, char *map_file_name);
int	free_state(t_state *state);

#endif
