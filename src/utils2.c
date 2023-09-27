/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huaydin <huaydin@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 18:25:48 by huaydin           #+#    #+#             */
/*   Updated: 2023/09/27 09:02:00 by huaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/* checks the R G or B color value if it's between 0-255 
Validates the input color value (R, G, or B) to ensure it's within the 
valid range (0-255) and is a numerical value. Returns the number if valid,
otherwise -1 to indicate an overflow or invalid input.*/
int	check_overflow(char *str, int num)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = NULL;
	while (str && str[++i])
	{
		if (!ft_isdigit(str[i]) && !ft_isspace(str[i]))
			return (-1);
	}
	tmp = ft_itoa(num);
	if (!tmp)
		return (-1);
	if (ft_strncmp(str, tmp, ft_strlen(str)) != 0)
	{
		ft_free_all(NULL, NULL, NULL, tmp);
		return (-1);
	}
	free(tmp);
	if (num < 0 || num > 255)
		return (-1);
	return (num);
}

/* finds first occurence of a char in a string, returns index of the found
character or -1 if not found*/
int	ft_strchr_idx(char *s, int c)
{
	unsigned char	c_unsigned;
	int				i;

	i = 0;
	if (!s || !s[0])
		return (-1);
	c_unsigned = (unsigned char)c;
	while (s && s[i])
	{
		if (s[i] == c_unsigned)
			return (free(s), i);
		i++;
	}
	if (c == 0)
		return (free(s), i);
	return (-1);
}
