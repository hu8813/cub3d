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

int	check_map(t_data *g, char *pos, int i, int count)
{
	char	**tmp;

	if (!g->tmp_map)
		return (-1);
	i = process_map_chars(g->tmp_map, i, pos, count);
	if (i == -1 && g->tmp_map)
		return (-1);
	if (g->tmp_map && g->tmp_map[i])
		return (-1);
	tmp = ft_split(g->tmp_map, '\n');
	if (!tmp && g->tmp_map)
		return (-1);
	return (check_valid_route(tmp, g->tmp_map));
}

// Hilfsfunktion
// 1. Initialisierung und Vorverarbeitung
char	*initialize_and_preprocess(char *s, int *i, int *k)
{
	int		ind;
	char	*tmp;

	ind = ft_strchr_idx(&s[*i], '\n');
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
			ft_memset(tmp, 0, ft_strlen(tmp));
			if (ind == 2 && s[*i] == '\n' && rgb[ind] != -1)
				return (0);
			else if (rgb[ind] == -1 || (ind == 2 && s[*i] != '\n'))
				return (1);
			ind++;
			j = 0;
		}
		else if (s[*i] != ' ' && s[*i] != '\t')
			tmp[j++] = s[*i];
		(*i)++;
	}
	return (0);
}

/* Validates the map by ensuring it only has one player position
'N', 'S', 'W', or 'E'). It also trims any leading or trailing empty lines,
spaces, or tabs.
Then it splits the map by newlines and passes it to `check_valid_route`
for further validation.  */
int	get_color(char *s, int rgb[3], int *k)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = initialize_and_preprocess(s, &i, k);
	if (!tmp)
		return (1);
	if (extract_colors_from_string(s, rgb, tmp, &i))
	{
		free(tmp);
		return (1);
	}
	free(tmp);
	return (0);
}
