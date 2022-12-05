/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caquinta <caquinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 22:24:05 by manu              #+#    #+#             */
/*   Updated: 2022/12/05 12:28:57 by caquinta         ###   ########.fr       */
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
	double	Oldtime;
	double	Time;
	int w;
	int h;
	int *texture[8];
}	t_data;

typedef struct s_state
{
	void		*mlx;
	void		*window;
	int			x;
	int			cameraX;
	double		rayDirX;
	double		rayDirY;
	int			mapX;
	int			mapY;
	double		sideDistX;
	double		sideDistY;
	double		deltaDistX;
	double		deltaDistY;
	double		perpWallDist;
	int			stepX;
	int			stepY;
	int			hit;
	int			side;
	int			time;
	int			lineHeight;
	int			drawStart;
	int			drawEnd;
	t_data		img;
}	t_state;

int	init_state(t_state *state, char *map_file_name);
int	free_state(t_state *state);

#endif
