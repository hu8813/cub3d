/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelasam <eelasam@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 09:23:22 by huaydin           #+#    #+#             */
/*   Updated: 2023/10/03 14:48:39 by eelasam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/* Checks if the input character is a whitespace character (space, tab, newline,
vertical tab, form feed, carriage return) and returns 1 if true, 0 otherwise.*/
int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

/* if 1st parameter is not 0, prints an error message
if 2nd parameter is not 0, frees the struct */
void	ft_error(char *errorcode, t_data *g)
{
	if (g->error_code == ERR_INVALID_COLOR)
		ft_putendl_fd("Error\nInvalid Floor or Ceil color in map file", 2);
	else if (g->error_code == ERR_INVALID_TEXTURE)
		ft_putendl_fd("Error\nInvalid texture file in map file", 2);
	else if (g->error_code == ERR_MULTIPLE_TEXTURE)
		ft_putendl_fd("Error\nInvalid texture or multiple values", 2);
	else if (g->error_code == ERR_INVALID_MAP)
		ft_putendl_fd("Error\nInvalid map", 2);
	else if (g->error_code == ERR_FILE_READ)
		ft_putendl_fd("Error\nInvalid texture file, not found", 2);
	else if (g->error_code == ERR_FILE_NOT_FOUND)
		ft_putendl_fd("Error\nInvalid texture file, not readable", 2);
	if (errorcode)
	{
		if (!g->error_code)
			ft_putendl_fd("Error", 2);
		ft_putendl_fd(errorcode, 2);
	}
	if (g)
		ft_exit(g);
	exit(1);
}

/* if 1st parameter is not 0, frees the string array
if other 3 parameters are not 0, frees those strings */
void	ft_free_all(char **s, char *s1, char *s2, char *s3)
{
	int	i;
	int	j;

	if (s)
	{
		i = 0;
		j = 0;
		while (s && s[i])
			i++;
		while (j < i && s && s[j])
		{
			if (s[j])
				free(s[j]);
			j++;
		}
		if (s[j])
			free(s[j]);
		free(s);
	}
	if (s1 && *s1)
		free(s1);
	if (s2 && *s2)
		free(s2);
	if (s3 && *s3)
		free(s3);
}

/* Frees allocated memory for four image pointers. 
Ensures each pointer is not NULL before attempting to free it.*/
void	ft_free_ptr(t_img *s1, t_img *s2, t_img *s3, t_img *s4)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	if (s3)
		free(s3);
	if (s4)
		free(s4);
}

/* exits and frees whole malloced variables
Cleans up by destroying any allocated memory and MLX related resources 
before exiting the program.*/
int	ft_exit(t_data *g)
{
	if (g)
	{
		if (g->mlx)
		{
			if (g->north && g->north->img)
				mlx_destroy_image(g->mlx, g->north->img);
			if (g->east && g->east->img)
				mlx_destroy_image(g->mlx, g->east->img);
			if (g->west && g->west->img)
				mlx_destroy_image(g->mlx, g->west->img);
			if (g->south && g->south->img)
				mlx_destroy_image(g->mlx, g->south->img);
			if (g->win)
				mlx_destroy_window(g->mlx, g->win);
			mlx_destroy_display(g->mlx);
			free(g->mlx);
			ft_free_ptr(g->north, g->east, g->west, g->south);
		}
		ft_free_all(NULL, NULL, g->no_path, NULL);
		ft_free_all(g->map, g->ea_path, g->we_path, g->so_path);
		if (g->fd != -1)
			close(g->fd);
	}
	exit(0);
}
