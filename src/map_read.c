/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huaydin <huaydin@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 19:55:44 by huaydin           #+#    #+#             */
/*   Updated: 2023/09/30 19:05:55 by huaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/* Pre-check to ensure certain keywords (like direction indicators and colors)
are present in the given string. These keywords indicate the presence of
texture paths and RGB color definitions. */
int	pre_check(char *s)
{
	if (!ft_strnstr(s, "NO ", ft_strlen(s)) || !ft_strnstr(s, "SO ",
			ft_strlen(s)) || !ft_strnstr(s, "WE ", ft_strlen(s))
		|| !ft_strnstr(s, "EA ", ft_strlen(s)) || !ft_strnstr(s, "C ",
			ft_strlen(s)) || !ft_strnstr(s, "F ", ft_strlen(s))
		|| !ft_strchr(s, '1') || !ft_strchr(s, '0'))
		return (0);
	return (1);
}

/* Reads the content of a file with given file descriptor `fd` and returns it 
as a string. The file is read in 100-byte chunks, and the chunks are 
concatenated to form the complete content string. */
char	*read_cub_file(int fd)
{
	char	*map;
	char	*buffer;
	char	*tmp;
	int		bytes;

	map = ft_calloc(1, 1);
	if (!map)
		return (0);
	buffer = ft_calloc(1, 101);
	if (!buffer)
		return (free(map), NULL);
	bytes = 1;
	while (bytes > 0)
	{
		bytes = read(fd, buffer, 100);
		if (bytes == -1)
			return (free(map), free(buffer), NULL);
		buffer[bytes] = '\0';
		tmp = map;
		map = ft_strjoin(map, buffer);
		if (!map)
			return (free(tmp), free(buffer), NULL);
		free(tmp);
	}
	return (free(buffer), map);
}

/* Parses the .cub map file provided in the argument `map_file`. It reads 
the file content, validates the map layout, and extracts associated
configurations. The parsed information is stored in the game state structure
`t_data *g`. If the file cannot be opened, read, or if the map content is
invalid, the function returns -1. Otherwise, it returns 0. */
int	parse_args(t_data *g)
{
	char	*map_content;

	if (g->fd == -1)
	{
		g->error_code = ERR_FILE_NOT_FOUND;
		return (-1);
	}
	map_content = read_cub_file(g->fd);
	if (!map_content)
	{
		g->error_code = ERR_FILE_READ;
		close(g->fd);
		return (-1);
	}
	if (map_split(map_content, g) || check_texture(g))
	{
		close(g->fd);
		free(map_content);
		return (-1);
	}
	close(g->fd);
	free(map_content);
	return (0);
}
