/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelasam <eelasam@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 11:28:30 by eelasam           #+#    #+#             */
/*   Updated: 2023/10/03 17:39:26 by eelasam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/*Draws the floor and ceiling color */
static void	draw_ceiling_and_floor_color(t_data *g, int x, int start)
{
	int	t;

	t = 0;
	while (t < start)
	{
		g->pic->addr[(g->pic->width * t) + x] = g->c_color[0] << 16;
		g->pic->addr[(g->pic->width * t) + x] += g->c_color[1] << 8;
		g->pic->addr[(g->pic->width * t) + x] += g->c_color[2];
		t++;
	}
	while (t < g->height)
	{
		g->pic->addr[(g->pic->width * t) + x] = g->f_color[0] << 16;
		g->pic->addr[(g->pic->width * t) + x] += g->f_color[1] << 8;
		g->pic->addr[(g->pic->width * t) + x] += g->f_color[2];
		t++;
	}
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

	if (g->wall < 0.03)
		return ;
	line = (int)(g->height / g->wall);
	start = g->height / 2 - line / 2;
	if (start < 0)
		start = 0;
	end = g->height / 2 + line / 2;
	if (end >= g->height)
		end = g->height - 1;
	draw_ceiling_and_floor_color(g, x, start);
	while (++start < end)
		g->pic->addr[(g->pic->width * start) + x]
			= put_texture(g, start, line, g->south);
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
	if (calculate_dda(g))
	{
		if (!g->side)
			g->wall = (g->x_map - g->x + (1 - g->x_step) / 2) / g->x_ray;
		else
			g->wall = (g->y_map - g->y + (1 - g->y_step) / 2) / g->y_ray;
	}
}

static void	raycast_columns(t_data *g)
{
	int		y;
	float	x_camera;

	y = -1;
	while (++y < g->width)
	{
		g->x_map = (int)g->x;
		g->y_map = (int)g->y;
		x_camera = 2 * y / (float)g->width - 1;
		g->x_ray = g->x_dir - g->y_dir * x_camera;
		g->y_ray = g->y_dir + g->x_dir * x_camera;
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

	g = (t_data *)param;
	print_debug(g);
	g->pic = ft_create_img(g, g->width, g->width, 0);
	if (!g->pic)
		ft_error("Mlx init img failed", g);
	raycast_columns(g);
	if (g->pic->img)
	{
		mlx_put_image_to_window(g->mlx, g->win, g->pic->img, 0, 0);
		mlx_destroy_image(g->mlx, g->pic->img);
	}
	free(g->pic);
	if (g->key)
		handle_key(g->key, g, g->x_dir);
	return (0);
}
