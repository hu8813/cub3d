/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_display_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huaydin <huaydin@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 19:08:22 by eelasam           #+#    #+#             */
/*   Updated: 2023/09/23 10:24:14 by huaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

void	ft_error_display(t_game *game)
{
	ft_putstr_fd("Error\nDISPLAY has been unset\n", 2);
	free(game->mlx);
	free(game->no_texture.path);
	free(game->so_texture.path);
	free(game->we_texture.path);
	free(game->ea_texture.path);
	free(game->floor_color);
	free(game->ceiling_color);
	free_tab(game->map);
	exit(1);
}
