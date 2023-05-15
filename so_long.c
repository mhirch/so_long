/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirch <mhirch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 13:49:44 by mhirch            #+#    #+#             */
/*   Updated: 2023/05/15 15:14:53 by mhirch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	exit_game(t_info *data)
{
	free(data->m);
	free(data->map);
	exit(0);
	return (0);
}

int	main(int ac, char **av)
{
	t_info	data_game;

	if (ac == 2)
	{
		data_game.moves = 0;
		data_game.map = check_map(av[1]);
		check_path(data_game.map, &data_game);
		write(1, "0\n", 2);
		data_game.mlx = mlx_init();
		protect(&data_game, 'i');
		data_game.window = mlx_new_window(data_game.mlx, data_game.col * 64,
				data_game.rows * 64, "so_long");
		protect(&data_game, 'w');
		put_img_to_window(&data_game);
		mlx_hook(data_game.window, 2, 0, &move, &data_game);
		mlx_hook(data_game.window, 17, 0, &exit_game, &data_game);
		mlx_loop(data_game.mlx);
	}
}
