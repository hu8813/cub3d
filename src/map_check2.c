/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelasam <eelasam@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:42:58 by eelasam         #+#    #+#             */
/*   Updated: 2023/09/27 12:45:37 by eelasam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/* static int	check_valid_route(char **map, char *str)
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
} */

/* Helper function to handle character position check and whitespace skipping*/
int	process_map_chars(char *m, int i, char *p_direction, int count)
{
	while (m && m[i] && (m[i] == '\n' || m[i] == ' ' || m[i] == '\t'))
		i++;
	while (m && i >= 0 && m[i])
	{
		if (m && m[i + 1] && m[i] == '\n' && (m[i + 1] == '\n' || m[i
					+ 1] == '\t'))
			break ;
		if ((m && m[i] != '0' && m[i] != '1' && m[i] != ' ' && m[i] != '\n'))
		{
			*p_direction = m[i];
			count++;
		}
		i++;
	}
	if (count != 1 || (*p_direction != 'N' && *p_direction != 'S'
			&& *p_direction != 'W' && *p_direction != 'E'))
		return (-1);
	while (m && m[i] && (m[i] == '\n' || m[i] == ' ' || m[i] == '\t'))
		i++;
	return (i);
}

int	check_map(char *map, char *pos, int i, int count)
{
	char	**tmp;

	i = process_map_chars(map, i, pos, count);
	return (0);
	if (i == -1)
		return (free(map), -1);
	if (map && map[i])
		return (free(map), -1);
	tmp = ft_split(map, '\n');
	if (!tmp)
		return (free(map), -1);
	return (check_valid_route(tmp, map));
}

/* Validates the map by ensuring it only has one player position
'N', 'S', 'W', or 'E'). It also trims any leading or trailing empty lines,
spaces, or tabs.
Then it splits the map by newlines and passes it to `check_valid_route`
for further validation.  */

/* int	check_map(char *map, char *p_direction, int i, int count)
{
	char	**tmp;
	int		validation_result;
	int		i;
	int		j;
	int		ind;
	char	*tmp;

	validation_result = validate_map(map, pos);
	if (validation_result != 0)
		return (validation_result);
	tmp = ft_split(map, '\n');
	if (!tmp)
		return (-1);
	return (check_valid_route(tmp, map));
} */
/* Extracts RGB color values from a given string, starting from the first
occurrence of a color definition (e.g., 'F' or 'C'). It returns these RGB
values in an array. */
/* void	get_color(char *s, int rgb[3], int *k)
{
	i = 0;
	j = 0;
	ind = ft_strchr_idx(ft_strdup(&s[i]), '\n');
	if (ind == -1 || ind == 0 || s[i] == '\n')
		return ;
	*k += ind;
	tmp = malloc(ind + 1);
	if (tmp == NULL)
		return ;
	ind = 0;
	while (s[i])
	{
		if (s[i] == ',' || s[i] == '\n')
		{
			tmp[j] = '\0';
			rgb[ind] = check_overflow(tmp, atoi(tmp));
			ft_memset(tmp, 0, 10);
			j = 0;
			ind++;
			if (ind == 3)
			{
				free(tmp);
				return ;
			}
		}
		else if (s[i] != ' ' && s[i] != '\t')
		{
			tmp[j] = s[i];
			j++;
		}
		i++;
	}
	free(tmp);
} */
// Helper function to handle color extraction and validation
/* int	extract_color_values(char *s, int rgb[3], char *tmp, int i, int *j,
		int *ind)
{
	while (s[i])
	{
		if (s[i] == ',' || s[i] == '\n')
		{
			tmp[*j] = '\0';
			rgb[*ind] = check_overflow(tmp, ft_atoi(tmp));
			ft_memset(tmp, 0, 10);
			*j = 0;
			(*ind)++;
			if (*ind == 3)
				return (1);
		}
		else if (s[i] != ' ' && s[i] != '\t')
		{
			tmp[*j] = s[i];
			(*j)++;
		}
		i++;
	}
	return (0);
}

void	get_color(char *s, int rgb[3], int *k)
{
	int		i;
	int		j;
	int		ind;
	char	*tmp;
	int		ind;
	char	*tmp;

	i = 0;
	j = 0;
	ind = ft_strchr_idx(ft_strdup(&s[i]), '\n');
	if (ind == -1 || ind == 0 || s[i] == '\n')
		return ;
	*k += ind;
	tmp = malloc(ind + 1);
	if (tmp == NULL)
		return ;
	ind = 0;
	if (extract_color_values(s, rgb, tmp, i, &j, &ind))
	{
		free(tmp);
		return ;
	}
	free(tmp);
} */
// Hilfsfunktion
// 1. Initialisierung und Vorverarbeitung
char	*initialize_and_preprocess(char *s, int *i, int *k)
{
	int		ind;
	char	*tmp;

	ind = ft_strchr_idx(ft_strdup(&s[*i]), '\n');
	if (ind == -1 || ind == 0 || s[*i] == '\n')
		return (NULL);
	*k += ind;
	tmp = malloc(ind + 1);
	if (tmp == NULL)
		return (NULL);
	return (tmp);
}

// 2. Extraktion von Farbwerten aus dem String
int	extract_colors_from_string(char *s, int rgb[3], char *tmp, int *i)
{
	int	j;
	int	ind;

	j = 0;
	ind = 0;
	while (s[*i])
	{
		if (s[*i] == ',' || s[*i] == '\n')
		{
			tmp[j] = '\0';
			rgb[ind] = check_overflow(tmp, atoi(tmp));
			ft_memset(tmp, 0, 10);
			j = 0;
			ind++;
			if (ind == 3)
				return (1);
		}
		else if (s[*i] != ' ' && s[*i] != '\t')
		{
			tmp[j] = s[*i];
			j++;
		}
		(*i)++;
	}
	return (0);
}

void	get_color(char *s, int rgb[3], int *k)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = initialize_and_preprocess(s, &i, k);
	if (!tmp)
		return ;
	if (extract_colors_from_string(s, rgb, tmp, &i))
	{
		free(tmp);
		return ;
	}
	free(tmp);
}