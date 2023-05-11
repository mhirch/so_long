/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirch <mhirch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:14:46 by mhirch            #+#    #+#             */
/*   Updated: 2023/05/11 16:30:56 by mhirch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	put_wall_and_collect_and_exit(t_info *data_game)
{
	int	i;
	int	j;

	i = 0;
	while (i < data_game->rows)
	{
		j = 0;
		while (j < data_game->col)
		{
			if (data_game->map[i][j] == '1')
				mlx_put_image_to_window(data_game->mlx, data_game->window,
					data_game->wall, j * 64, i * 64);
			else if (data_game->map[i][j] == 'C')
				mlx_put_image_to_window(data_game->mlx, data_game->window,
					data_game->collectible, j * 64, i * 64);
			else if (data_game->map[i][j] == 'E')
				mlx_put_image_to_window(data_game->mlx, data_game->window,
					data_game->exit, j * 64, i * 64);
			j++;
		}
		i++;
	}
}

void	protect(t_info *d, char x)
{
	if (x == 'i' && !d->mlx)
	{
		write(2, "error\nmlx_init\n", 15);
		exit(1);
	}
	else if (x == 'w' && !d->mlx)
	{
		write(2, "error\nmlx_new_window\n", 22);
		exit(1);
	}
	else if (x == 'x' && (!d->background
			|| !d->collectible || !d->wall || !d->exit || !d->player))
	{
		write(2, "error\nmlx_xpm_file_to_image\n", 28);
		exit(1);
	}
}

void	set_image(t_info *data_game)
{
	data_game->player = mlx_xpm_file_to_image(data_game->mlx,
			"textures/player.xpm", &data_game->img_width,
			&data_game->img_height);
	data_game->wall = mlx_xpm_file_to_image(data_game->mlx,
			"textures/wall.xpm", &data_game->img_width,
			&data_game->img_height);
	data_game->collectible = mlx_xpm_file_to_image(data_game->mlx,
			"textures/collectible.xpm", &data_game->img_width,
			&data_game->img_height);
	data_game->background = mlx_xpm_file_to_image(data_game->mlx,
			"textures/background.xpm", &data_game->img_width,
			&data_game->img_height);
	data_game->exit = mlx_xpm_file_to_image(data_game->mlx,
			"textures/exit.xpm", &data_game->img_width,
			&data_game->img_height);
	protect(data_game, 'x');
}

void	put_img_to_window(t_info *data_game)
{
	t_position	player;

	set_image(data_game);
	player = get_position(data_game->map, 'P');
	mlx_put_image_to_window(data_game->mlx, data_game->window,
		data_game->player, player.x * 64, player.y * 64);
	put_wall_and_collect_and_exit(data_game);
}
