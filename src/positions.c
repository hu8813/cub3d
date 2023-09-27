/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   positions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelasam <eelasam@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 11:30:27 by eelasam           #+#    #+#             */
/*   Updated: 2023/09/27 13:50:14 by eelasam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/* Determines the starting position of the player on the map using the position
character stored in the game state `t_data *g`. It then initializes the player's
x and y coordinates in the game state. */
void	get_position(char **map, t_data *g)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j] && map[i][j] != g->p_direction)
			j++;
		if (map[i][j] && map[i][j] == g->p_direction)
		{
			g->x = (j + 0.5);
			g->y = (i + 0.5);
		}
		i++;
	}
	set_pos(g);
}

/* Sets the initial direction and view plane for the player based on
the player's position character in the game state `t_data *g`. */
void	set_pos(t_data *g)
{
	g->x_dir = 0;
	g->y_dir = -0.7;
	g->x_plane = 0.7;
	g->y_plane = 0;
	if (g->p_direction == 'W')
	{
		g->x_dir = 0.7;
		g->y_dir = 0;
		g->x_plane = 0;
		g->y_plane = 0.7;
	}
	else if (g->p_direction == 'E')
	{
		g->x_dir = -0.7;
		g->y_dir = 0;
		g->x_plane = 0;
		g->y_plane = -0.7;
	}
	else if (g->p_direction == 'S')
	{
		g->x_dir = 0;
		g->y_dir = 0.7;
		g->x_plane = -0.7;
		g->y_plane = 0;
	}
}

/* Initializes the color buffer for the ceiling and floor based on the colors
defined in the game state `t_data *g`. */
void	set_colors(t_data *g)
{
	int	i;

	i = 0;
	if (!g)
		return ;
	while (i < (g->width * g->height) / 2)
	{
		g->pic->buf[i] = g->c_color[0] << 16;
		g->pic->buf[i] += g->c_color[1] << 8;
		g->pic->buf[i] += g->c_color[2];
		i++;
	}
	while (i < g->width * g->height)
	{
		g->pic->buf[i] = g->f_color[0] << 16;
		g->pic->buf[i] += g->f_color[1] << 8;
		g->pic->buf[i] += g->f_color[2];
		i++;
	}
}

/* Modifies the player's position in the game state `t_data *g` based on the
proposed movements in the x and y directions (`sumX` and `sumy`). */
static void	go(t_data *g, double sumy, double sumX)
{
	if ((int)sumy >= 0 && g->map[(int)sumy])
	{
		g->y = sumy;
		if ((int)sumX >= 0 && g->map[(int)sumy][(int)sumX]
			&& g->map[(int)sumy][(int)sumX] != ' ')
			g->x = sumX;
	}
}

/* Handles player movement and rotation based on the key pressed. Updates
the player's position and direction in the game state `t_data *g`. */
void	key(int key, t_data *g, double temp)
{
	if (g->move == XK_w || key == XK_w)
		go(g, g->y + g->y_dir * SPEED, g->x + g->x_dir * SPEED);
	else if (g->move && (key == XK_s))
		go(g, g->y - g->y_dir * SPEED / 2, g->x - g->x_dir * SPEED / 2);
	else if (key == XK_d)
		go(g, g->y - g->y_plane * SPEED / 2, g->x - g->x_plane * SPEED / 2);
	else if (key == XK_a)
		go(g, g->y + g->y_plane * SPEED / 2, g->x + g->x_plane * SPEED / 2);
	if (g->rotate[0] == '1' && (key == XK_Left))
	{
		g->x_dir = g->x_dir * cos(LR_ANGLE) - g->y_dir * sin(LR_ANGLE);
		g->y_dir = temp * sin(LR_ANGLE) + g->y_dir * cos(LR_ANGLE);
		temp = g->x_plane;
		g->x_plane = g->x_plane * cos(LR_ANGLE) - g->y_plane * sin(LR_ANGLE);
		g->y_plane = temp * sin(LR_ANGLE) + g->y_plane * cos(LR_ANGLE);
	}
	else if (g->rotate[2] == '1' && (key == XK_Right))
	{
		g->x_dir = g->x_dir * cos(-LR_ANGLE) - g->y_dir * sin(-LR_ANGLE);
		g->y_dir = temp * sin(-LR_ANGLE) + g->y_dir * cos(-LR_ANGLE);
		temp = g->x_plane;
		g->x_plane = g->x_plane * cos(-LR_ANGLE) - g->y_plane * sin(-LR_ANGLE);
		g->y_plane = temp * sin(-LR_ANGLE) + g->y_plane * cos(-LR_ANGLE);
	}
}