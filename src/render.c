/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huaydin <huaydin@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 11:28:30 by eelasam           #+#    #+#             */
/*   Updated: 2023/09/27 21:13:22 by huaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/* Determines the texture color for a specific position on the screen.
The texture and shading are selected based on the ray's direction
and intersection point. It also accounts for the direction from which
the ray hits a wall to pick the correct texture side. */
static int	put_texture(t_data *g, float start, int line, t_img *texture)
{
	int		color;
	double	x_text;
	double	x_wall;
	double	y_text;

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
	x_wall -= floor((x_wall));
	x_text = (int)(x_wall * (double)(texture->width));
	if (g->side == 0 && g->x_ray > 0)
		x_text = texture->width - x_text - 1;
	else if (g->side == 1 && g->y_ray < 0)
		x_text = texture->width - x_text - 1;
	color = start * 256 - g->height * 128 + line * 128;
	y_text = ((color * texture->height) / line) / 256;
	color = texture->buf[(int)(y_text * texture->width + x_text)];
	return (color);
}

/*Draws the walls and other world elements onto the screen based on
the results of ray casting. This determines the vertical slice of
the texture that should be displayed for each column
of pixels on the screen. */
static void	draw(t_data *g, int x)
{
	int	line;
	int	start;
	int	end;

	if (g->wall < 0)
		return ;
	line = (int)(g->height / g->wall);
	if (line > 200000)
		line = 200000;
	start = -line / 2 + g->height / 2;
	if (start < 0)
		start = 0;
	end = line / 2 + g->height / 2;
	if (end >= g->height)
		end = g->height - 1;
	while (start < end)
	{
		g->pic->buf[(g->pic->width * start) + x]
			= put_texture(g, start, line, g->south);
		start++;
	}
}

/*Uses ray casting algorithms to calculate where rays intersect with map
elements. This helps in determining how far walls are from the player,
which is essential for correct wall rendering and texture mapping. */
static void	calculate_ray_values(t_data *g)
{
	g->x_step = 1;
	g->y_step = 1;
	g->x_delta = fabs(1 / g->x_ray);
	g->y_delta = fabs(1 / g->y_ray);
	g->x_side = (g->x_map + 1.0 - g->x) * g->x_delta;
	g->y_side = (g->y_map + 1.0 - g->y) * g->y_delta;
	if (g->x_ray < 0)
	{
		g->x_step = -1;
		g->x_side = (g->x - g->x_map) * g->x_delta;
	}
	if (g->y_ray < 0)
	{
		g->y_step = -1;
		g->y_side = (g->y - g->y_map) * g->y_delta;
	}
	if (dda(g))
	{
		if (!g->side)
			g->wall = (g->x_map - g->x + (1 - g->x_step) / 2) / g->x_ray;
		else
			g->wall = (g->y_map - g->y + (1 - g->y_step) / 2) / g->y_ray;
	}
}

static void	raycast_columns(t_data *g)
{
	int	y;

	y = -1;
	while (++y < g->width)
	{
		g->x_map = (int)g->x;
		g->y_map = (int)g->y;
		g->x_camera = 2 * y / (double)g->width - 1;
		g->x_ray = g->x_dir - g->x_plane * g->x_camera;
		g->y_ray = g->y_dir - g->y_plane * g->x_camera;
		calculate_ray_values(g);
		draw(g, y);
	}
}

/* The core rendering function that's invoked for every frame. It computes
ray casting for each screen column, draws the results, and then displays
the frame on the screen using MLX. Also handles some input events. */
int	render(void *param)
{
	t_data	*g;
	char result[1000]; 

	g = (t_data *)param;
	sprintf(result, "x:%f y:%f x_dir:%f y_dir:%f x_plane:%f y_plane:%f x_map:%d y_map:%d x_step:%d y_step:%d x_ray:%f y_ray:%f x_delta:%f y_delta:%f x_side:%f y_side:%f wall:%f height:%d",
    g->x, g->y, g->x_dir, g->y_dir, g->x_plane, g->y_plane, g->x_map, g->y_map, g->x_step, g->y_step,
    g->x_ray, g->y_ray, g->x_delta, g->y_delta, g->x_side, g->y_side, g->wall, g->height);
	mlx_string_put(g->mlx, g->win, 10, 10 , 0, result);
	g->pic = ft_create_img(g, g->width, g->width, 0);
	if (!g->pic)
		ft_error("Mlx init img failed", g);
	set_colors(g);
	raycast_columns(g);
	if (g->pic->g)
	{
		mlx_put_image_to_window(g->mlx, g->win, g->pic->g, 0, 0);
		mlx_destroy_image(g->mlx, g->pic->g);
	}
	free(g->pic);
	if (g->key && g->key == XK_Escape)
		ft_exit(g);
	else if (g->key && g->key != XK_Escape)
		key(g->key, g, g->x_dir);
	return (0);
}
