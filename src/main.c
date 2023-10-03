/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelasam <eelasam@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 15:12:05 by eelasam           #+#    #+#             */
/*   Updated: 2023/10/03 17:28:10 by eelasam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/* Callback function for when a key is pressed. Updates the game's 
state based on which key was pressed (e.g., movement or rotation).*/
static int	key_pressed(int key, t_data *g)
{
	if (key == XK_w || key == XK_a || key == XK_s || key == XK_d)
	{
		g->move = key;
	}
	else if (key == XK_Left)
		g->rotate[0] = '1';
	else if (key == XK_Right)
		g->rotate[2] = '1';
	g->key = key;
	if (key == XK_Escape)
		ft_exit(g);
	return (0);
}

/* Callback function for when a key is released. Resets the game's 
state based on which key was released.*/
static int	key_released(int key, t_data *g)
{
	if (key == XK_w || key == XK_a || key == XK_s || key == XK_d)
	{
		g->move = 0;
		if (g->key == XK_w || g->key == XK_a || g->key == XK_s
			|| g->key == XK_d)
			g->key = 0;
		if (g->rotate[0])
			g->key = g->rotate[0];
		if (g->rotate[2])
			g->key = g->rotate[2];
	}
	else if (g->move)
		g->key = g->move;
	if (key == XK_Left)
		g->rotate[0] = '0';
	if (key == XK_Right)
		g->rotate[2] = '0';
	return (0);
}

/* Initializes the game's graphics and settings. Sets up the game window,
loads textures, and connects callback functions for key presses/releases.*/
static int	init_game(t_data *g)
{
	g->mlx = mlx_init();
	if (!g->mlx)
		return (0);
	mlx_get_screen_size(g->mlx, &g->width, &g->height);
	if (g->width == 0 || g->height == 0)
		return (0);
	get_position(g->map, g);
	g->win = mlx_new_window(g->mlx, g->width, g->height, "cub3D");
	if (!g->win)
		return (0);
	g->north = ft_create_img(g, 0, 0, 1);
	g->east = ft_create_img(g, 0, 0, 2);
	g->west = ft_create_img(g, 0, 0, 3);
	g->south = ft_create_img(g, 0, 0, 4);
	if (!g->north || !g->east || !g->south || !g->west)
		return (0);
	mlx_hook(g->win, 2, 1L, &key_pressed, g);
	mlx_hook(g->win, 3, 2L, &key_released, g);
	mlx_hook(g->win, 17, 0, ft_exit, g);
	mlx_loop_hook(g->mlx, &render, g);
	mlx_loop(g->mlx);
	return (1);
}

static void	init_struct(t_data *g)
{
	g->error_code = 0;
	g->mlx = 0;
	g->north = 0;
	g->south = 0;
	g->east = 0;
	g->west = 0;
	g->win = 0;
	g->no_path = 0;
	g->so_path = 0;
	g->we_path = 0;
	g->ea_path = 0;
	g->f_color[0] = -1;
	g->f_color[1] = -1;
	g->f_color[2] = -1;
	g->c_color[0] = -1;
	g->c_color[1] = -1;
	g->c_color[2] = -1;
	g->map = 0;
	g->tmp_map = 0;
	g->p_direction = 0;
	g->key = 0;
	g->move = 0;
	g->rotate[0] = '0';
	g->rotate[1] = '0';
	g->rotate[2] = '0';
}

int	main(int argc, char **argv)
{
	t_data	g;

	if (argc != 2 || ft_strlen(argv[1]) < 4
		|| (!ft_strncmp(argv[1] + ft_strlen(argv[1]) - 5, ".cub", 4)))
	{
		ft_putendl_fd("Error\nUsage: ./cub3D maps/map1.cub", 2);
		exit(1);
	}
	ft_memset(&g, 0, sizeof(t_data));
	g.fd = open(argv[1], O_RDONLY);
	if (g.fd == -1)
	{
		ft_putendl_fd("Error\nUsage: ./cub3D maps/map1.cub", 2);
		exit(1);
	}
	init_struct(&g);
	if (parse_args(&g) != 0)
		ft_error("Parsing failed, map error", &g);
	if (init_game(&g) == 0)
		ft_error("Initialisation failed", &g);
	return (0);
}
