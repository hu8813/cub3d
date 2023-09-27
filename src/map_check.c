/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelasam <eelasam@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 18:17:13 by eelasam           #+#    #+#             */
/*   Updated: 2023/09/27 20:06:16 by eelasam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/* This function conducts a flood-fill operation on the map to ensure its
walls are closed and no spaces leak out of the map boundaries. If the fill
hits the edge of the map or an open space, the map is marked as invalid. */
void	flood_fill(char **mapcopy, size_t i, size_t j, int *exit)
{
	if (i < 0 || j < 0 || !mapcopy[i] || (j >= ft_strlen(mapcopy[i]))
		|| (mapcopy[i][j] && mapcopy[i][j] == ' '))
	{
		*exit = 1;
		return ;
	}
	else if (mapcopy[i][j] != '0')
		return ;
	mapcopy[i][j] = 'O';
	flood_fill(mapcopy, i - 1, j, exit);
	flood_fill(mapcopy, i + 1, j, exit);
	flood_fill(mapcopy, i, j - 1, exit);
	flood_fill(mapcopy, i, j + 1, exit);
}

/* Checks if a map has a valid route by converting player positions and
other characters (not walls or spaces) to '0' and then invoking a
flood-fill from these positions. If the flood-fill hits an open space,
it means there's a gap in the walls and the map is invalid. */
int	check_valid_route(char **map, char *str)
{
	size_t	i;
	size_t	j;
	int		err;

	i = -1;
	err = 0;
	while (map && map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != ' '
				&& map[i][j] != '\t')
			{
				map[i][j] = '0';
				flood_fill(map, i, j, &err);
				if (err == 1)
					return (ft_free_all(map, str, NULL, NULL), -1);
			}
		}
	}
	ft_free_all(map, str, NULL, NULL);
	return (0);
}

// Checks if a single texture file exists and can be read.
static int	check_single_texture(char *path)
{
	int		fd;
	char	c;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		ft_putendl_fd("Error\nCannot open file ", 2);
		ft_putendl_fd(path, 2);
		return (-1);
	}
	else if (read(fd, &c, 1) == -1)
	{
		ft_putendl_fd("Error\nCannot read file ", 2);
		ft_putendl_fd(path, 2);
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

/* Validates each texture path (north, south, west, and east) by checking
if the corresponding files exist and can be read. */
int	check_texture(t_data *data)
{
	if (check_single_texture(data->no_path) == -1)
		return (-1);
	if (check_single_texture(data->so_path) == -1)
		return (-1);
	if (check_single_texture(data->we_path) == -1)
		return (-1);
	if (check_single_texture(data->ea_path) == -1)
		return (-1);
	return (0);
}