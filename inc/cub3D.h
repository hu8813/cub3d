/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelasam <eelasam@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 06:57:31 by eelasam           #+#    #+#             */
/*   Updated: 2023/09/27 19:53:06 by eelasam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>

/* write, read, */
# include <unistd.h>

/* File Manipulation Functions: open (O_CREAT, O_WRONLY, O_APPEND) */
# include <fcntl.h>

/* sin, cos for trigonometric calculations */
# include <math.h>

/* malloc, free */
# include <stdlib.h>

/* mlx library */
# include <mlx.h>

/* to get keycodes i.e. (XK_w) for w or XK_left for left arroy key */
# include <X11/keysym.h>

/* ft_isdigit, ft_atoi, ft_itoa, ft_strncmp, ft_split, ft_memset, ft_strlen,
ft_calloc, ft_putendl_fd, ft_substr, ft_strdup, ft_strjoin */
# include "../libft/libft.h"

/* angle (instead degrees) to turn when left or right arrow is pressed */
# define LR_ANGLE 0.04

/* speed of the movement of the player, when w, a, s or d is pressed*/
# define SPEED 0.06

/**/
typedef struct s_pic
{
	int		width;
	int		height;
	void	*mlx;
	void	*win;
	void	*g;
	int		*buf;
}			t_img;

/**/
typedef struct s_data
{
	void	*mlx;
	void	*win;
	char	**map;
	int		fd;
	int		side;
	int		width;
	int		height;
	double	wall;
	double	x;
	int		x_map;
	int		x_step;
	double	x_camera;
	double	x_ray;
	double	x_dir;
	double	x_plane;
	double	x_delta;
	double	x_side;
	double	y;
	int		y_map;
	int		y_step;
	double	y_ray;
	double	y_dir;
	double	y_plane;
	double	y_delta;
	double	y_side;
	char	p_direction;
	int		key;
	int		move;
	char	rotate[3];
	int		f_color[3];
	int		c_color[3];
	t_img	*pic;
	t_img	*north;
	t_img	*east;
	t_img	*west;
	t_img	*south;
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
}			t_data;

int			map_split(char *s, t_data *g);
char		*read_cub_file(int fd);
int			check_map(char *map, char *p_direction, int i, int count);
int			check_texture(t_data *data);
int			parse_args(char *map_file, t_data *data);
void		get_position(char **map, t_data *cub);
int			dda(t_data *cub);
void		key(int key, t_data *cub, double temp);
t_img		*ft_create_img(t_data *cub, int width, int height, int x);
int			render(void *param);
void		set_pos(t_data *cub);
void		set_colors(t_data *cub);
int			ft_exit(t_data *cub);
void		ft_free_all(char **s, char *s1, char *s2, char *s3);
void		ft_error(char *errorcode, t_data *data);
int			ft_strchr_idx(char *s, int c);
int			ft_isspace(int c);
int			check_overflow(char *str, int num);
void		get_color(char *s, int rgb[3], int *k);
int			pre_check(char *s);
void		flood_fill(char **mapcopy, size_t i, size_t j, int *exit);
int			check_valid_route(char **map, char *str);

#endif