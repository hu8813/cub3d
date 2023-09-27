/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_img.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelasam <eelasam@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 21:13:36 by huaydin           #+#    #+#             */
/*   Updated: 2023/09/27 13:26:12 by eelasam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/* Uses the MLX library to load an image from a file. This function 
is essential for loading different textures used in the game world. 
It will return a pointer to the loaded image or fail if there are issues. */
static void	*load_image(t_data *g, char *path, int *width, int *height)
{
	void	*img;

	img = 0;
	if (!g || !g->mlx || !path || !width || !height)
		return (0);
	if (g && g->mlx && path && width && height)
		img = mlx_xpm_file_to_image(g->mlx, path, width, height);
	if (!img)
		ft_error("Mlx failed", g);
	return (img);
}

/* Allocates and initializes a new image structure, assigning the correct 
texture based on the provided value 'x' which determines the type of texture 
(north, west, east, south, etc.).
It uses the `load_image` function to assist.*/
static t_img	*init_new_img(t_data *g, int width, int height, int x)
{
	t_img	*new;

	if (!g)
		return (0);
	new = ft_calloc(1, sizeof(t_img));
	if (!new)
		ft_error("Malloc failed", g);
	new->width = width;
	new->height = height;
	if (x == 1)
		new->g = load_image(g, g->no_path, &new->width, &new->height);
	else if (x == 2)
		new->g = load_image(g, g->we_path, &new->width, &new->height);
	else if (x == 3)
		new->g = load_image(g, g->ea_path, &new->width, &new->height);
	else if (x == 4)
		new->g = load_image(g, g->so_path, &new->width, &new->height);
	else if (g->mlx)
		new->g = mlx_new_image(g->mlx, width, height);
	if (!new->g)
		ft_error("Mlx failed", g);
	return (new);
}

/* Creates a new image structure intended for rendering. It initializes 
the structure, loads the appropriate texture, and also retrieves 
the data buffer where pixel information will be written. */
t_img	*ft_create_img(t_data *g, int width, int height, int x)
{
	t_img	*new;
	int		bpp;
	int		endian;

	bpp = 32;
	endian = 1;
	if (!g)
		return (0);
	new = init_new_img(g, width, height, x);
	if (!new || !new->g)
		ft_error("Mlx init img failed", g);
	new->buf = (int *)mlx_get_data_addr(new->g, &bpp, &x, &endian);
	if (!new->buf)
		ft_error("Mlx failed", g);
	return (new);
}

/* Implements the Digital Differential Analyzer (DDA) algorithm for raycasting,
tracing the path of a ray until it hits a wall or goes out of bounds.
Returns 1 if a wall is hit, 0 otherwise. */
int	dda(t_data *g)
{
	while (1)
	{
		if (g->x_side < g->y_side)
		{
			g->x_side += g->x_delta;
			g->x_map += g->x_step;
			g->side = 0;
		}
		else
		{
			g->y_side += g->y_delta;
			g->y_map += g->y_step;
			g->side = 1;
		}
		if (g->y_map < 0)
			g->y_map = 0;
		if (g->x_map < 0)
			g->x_map = 0;
		if (!g->map[g->y_map] || !g->map[g->y_map][g->x_map]
			|| g->map[g->y_map][g->x_map] == ' ')
			return (g->wall = -1, 0);
		if (g->map[g->y_map][g->x_map] == '1')
			return (1);
	}
	return (0);
}