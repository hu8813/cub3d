/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   positions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelasam <eelasam@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 11:30:27 by eelasam           #+#    #+#             */
/*   Updated: 2023/10/06 16:36:42 by eelasam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/* Sets the initial direction and view plane for the player based on
the player's position character in the game state `t_data *g`. */
void	set_pos(t_data *g)
{
	g->x_dir = 0;
	g->y_dir = -1;
	if (g->p_direction == 'W')
	{
		g->x_dir = -1;
		g->y_dir = 0;
	}
	else if (g->p_direction == 'E')
	{
		g->x_dir = 1;
		g->y_dir = 0;
	}
	else if (g->p_direction == 'S')
	{
		g->x_dir = 0;
		g->y_dir = 1;
	}
}

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

/* Modifies the player's position in the game state `t_data *g` based on the
proposed movements in the x and y directions (`newX` and `newy`). */
static void	go(t_data *g, float newy, float newX)
{
	if ((int)newy >= 0 && g->map[(int)(newy)])
	{
		if (g->y > 1.5)
			g->y = newy;
		else
			g->y = newy + 0.01;
		if ((int)newX >= 0 && g->map[(int)newy][(int)(newX)]
			&& g->map[(int)newy][(int)(newX)] != ' '
			&& g->map[(int)newy][(int)(newX)] != '1')
			g->x = newX;
	}
}

/* Handles player movement and rotation based on the key pressed. Updates
the player's position and direction in the game state `t_data *g`. */
void	handle_key(int key, t_data *g, float temp)
{
	if ((g->move == XK_w || key == XK_w) && g->y)
		go(g, g->y + g->y_dir * SPEED, g->x + g->x_dir * SPEED);
	else if (g->move && (key == XK_s))
		go(g, g->y - g->y_dir * SPEED / 2, g->x - g->x_dir * SPEED / 2);
	else if (key == XK_a)
		go(g, g->y - g->x_dir * SPEED / 2, g->x + g->y_dir * SPEED / 2);
	else if (key == XK_d)
		go(g, g->y + g->x_dir * SPEED / 2, g->x - g->y_dir * SPEED / 2);
	if (g->rotate[2] == XK_Right && (key == XK_Right))
	{
		g->x_dir = g->x_dir * cos(LR_ANGLE) - g->y_dir * sin(LR_ANGLE);
		g->y_dir = temp * sin(LR_ANGLE) + g->y_dir * cos(LR_ANGLE);
	}
	else if (g->rotate[0] == XK_Left && (key == XK_Left))
	{
		g->x_dir = g->x_dir * cos(-LR_ANGLE) - g->y_dir * sin(-LR_ANGLE);
		g->y_dir = temp * sin(-LR_ANGLE) + g->y_dir * cos(-LR_ANGLE);
	}
}
