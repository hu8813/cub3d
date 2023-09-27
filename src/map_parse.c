/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelasam <eelasam@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 21:06:16 by huaydin           #+#    #+#             */
/*   Updated: 2023/09/27 20:17:25 by eelasam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/* Extracts the texture file path for a given direction (e.g., North, South).
The function verifies that the file is accessible and returns the texture's
path. It updates the index `pos` to the end of the current section. */
static char	*get_texture(char *s, t_data *g, int *pos)
{
	int		i;
	int		k;
	char	*tmp;

	i = 0;
	k = ft_strchr_idx(ft_strdup(&s[i]), '\n');
	while (s[i] && i < k && s[i] != '\n' && (s[i] == ' ' || s[i] == '\t'))
		i++;
	if (k == -1 || k == 0 || s[i] == '\n')
		return (NULL);
	*pos += k;
	k--;
	while (s[k] && s[k] != '\n' && (s[k] == ' ' || s[k] == '\t'))
		k--;
	tmp = ft_substr(s, i, k - i + 1);
	if (access(tmp, F_OK | R_OK) == -1)
	{
		free(tmp);
		return (NULL);
	}
	else
		return (tmp);
	(void)g;
	(void)pos;
}

int	assign_textures(char *s, t_data *g, int *i)
{
	while (s[*i] != 0)
	{
		if (!ft_strncmp(&s[*i], "NO ", 3))
			g->no_path = get_texture(&s[*i + 3], g, i);
		else if (!ft_strncmp(&s[*i], "SO ", 3))
			g->so_path = get_texture(&s[*i + 3], g, i);
		else if (!ft_strncmp(&s[*i], "WE ", 3))
			g->we_path = get_texture(&s[*i + 3], g, i);
		else if (!ft_strncmp(&s[*i], "EA ", 3))
			g->ea_path = get_texture(&s[*i + 3], g, i);
		else if (!ft_strncmp(&s[*i], "F ", 2))
			get_color(&s[*i + 2], g->f_color, i);
		else if (!ft_strncmp(&s[*i], "C ", 2))
			get_color(&s[*i + 2], g->c_color, i);
		(*i)++;
	}
	return (0);
}

int	verify_color_path_data(char *s, t_data *g, int *i)
{
	*i = 0;
	while (s[*i] && ft_strnstr(&s[*i], "NO ", ft_strlen(&s[*i]))
		&& ft_strnstr(&s[*i], g->no_path, ft_strlen(&s[*i])))
		(*i)++;
	while (s[*i] && ft_strnstr(&s[*i], "SO ", ft_strlen(&s[*i]))
		&& ft_strnstr(&s[*i], g->so_path, ft_strlen(&s[*i])))
		(*i)++;
	while (s[*i] && ft_strnstr(&s[*i], "WE ", ft_strlen(&s[*i]))
		&& ft_strnstr(&s[*i], g->we_path, ft_strlen(&s[*i])))
		(*i)++;
	while (s[*i] && ft_strnstr(&s[*i], "EA ", ft_strlen(&s[*i]))
		&& ft_strnstr(&s[*i], g->ea_path, ft_strlen(&s[*i])))
		(*i)++;
	while (s[*i] && ft_strnstr(&s[*i], "F ", ft_strlen(&s[*i])))
		(*i)++;
	while (s[*i] && ft_strnstr(&s[*i], "C ", ft_strlen(&s[*i])))
		(*i)++;
	while (s[*i] && s[*i] != '\n')
		(*i)++;
	return (0);
}

int	prepare_map_data(char *s, t_data *g, int *i)
{
	char	*tmp;

	tmp = ft_substr(s, *i, ft_strlen(&s[*i]));
	if (!tmp)
		return (1);
	if (check_map(tmp, &g->p_direction, 0, 0))
		return (write(2, "Error\nInvalid map\n", 19), 1);
	if (tmp)
		free(tmp);
	g->map = ft_split(&s[*i], '\n');
	if (!g->map)
		return (1);
	return (0);
}

/* Parses the map data string and extracts configuration details such as
texture paths and floor/ceiling colors. The function then sets the
associated fields in the game state structure (`t_data *g`). It returns 0
if the map is valid and populated correctly; otherwise, it returns 1. */
int	map_split(char *s, t_data *g)
{
	int	i;

	i = 0;
	if (!pre_check(s))
		return (1);
	assign_textures(s, g, &i);
	if (verify_color_path_data(s, g, &i))
		return (1);
	return (prepare_map_data(s, g, &i));
}
