/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_img.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huaydin <huaydin@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 21:13:36 by huaydin           #+#    #+#             */
/*   Updated: 2023/10/05 21:10:18 by huaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/* Determines the texture color for a specific position on the screen.
The texture and shading are selected based on the ray's direction
and intersection point. It also accounts for the direction from which
the ray hits a wall to pick the correct texture side. */
int	put_texture(t_data *g, float start, int line, t_img *texture)
{
	int		color;
	float	x_text;
	float	x_wall;
	float	y_text;

	if (g->x_ray > 0 && !g->side)
		texture = g->east;
	else if (g->x_ray < 0 && !g->side)
		texture = g->west;
	else if (g->y_ray < 0 && g->side)
		texture = g->north;
	if (g->side == 0)
		x_wall = g->y + g->wall * g->y_ray;
	else
		x_wall = g->x + g->wall * g->x_ray;
	x_wall = x_wall - (int) x_wall;
	x_text = (int)(x_wall * (float)(texture->width));
	if ((g->side == 0 && g->x_ray < 0) || (g->side == 1 && g->y_ray > 0))
		x_text = texture->width - x_text - 1;
	color = ((int)start << 8) - (g->height << 7) + (line << 7);
	y_text = ((color * texture->height) / line) >> 8;
	color = texture->addr[(int)(y_text * texture->width + x_text)];
	return (color);
}

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
	if (!img || *height > 1400 || *width > 1400)
	{
		if (img)
			mlx_destroy_image(g->mlx, img);
		return (NULL);
	}
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
		new->img = load_image(g, g->no_path, &new->width, &new->height);
	else if (x == 2)
		new->img = load_image(g, g->we_path, &new->width, &new->height);
	else if (x == 3)
		new->img = load_image(g, g->ea_path, &new->width, &new->height);
	else if (x == 4)
		new->img = load_image(g, g->so_path, &new->width, &new->height);
	else if (g->mlx)
		new->img = mlx_new_image(g->mlx, width, height);
	if (!new->img)
	{
		free(new);
		ft_error("Mlx failed", g);
	}
	return (new);
}

/* Creates a new image structure intended for rendering. It initializes
the structure, loads the appropriate texture, and also retrieves
the data addrfer where pixel information will be written. */
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
	if (!new || !new->img)
		ft_error("Mlx init img failed", g);
	new->addr = (int *)mlx_get_data_addr(new->img, &bpp, &x, &endian);
	if (!new->addr)
		ft_error("Mlx failed", g);
	return (new);
}

/* Implements the Digital Differential Analyzer (DDA) algorithm for raycasting,
tracing the path of a ray until it hits a wall or goes out of bounds.
Returns 1 if a wall is hit, 0 otherwise. */
int	calculate_dda(t_data *g)
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
