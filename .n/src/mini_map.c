/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huaydin <huaydin@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 22:46:49 by eelasam           #+#    #+#             */
/*   Updated: 2023/09/23 10:24:14 by huaydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_mini_map(t_game *game, t_img_data *mini_map)
{
	mini_map->img_width = game->len_x * game->cell_size;
	mini_map->img_height = game->len_y * game->cell_size;
	mini_map->img = mlx_new_image(game->mlx, mini_map->img_width, \
		mini_map->img_height);
	mini_map->addr = mlx_get_data_addr(mini_map->img, &mini_map->bpp, \
		&mini_map->line_length, &mini_map->endian);
	ft_ray_caster(game);
}
