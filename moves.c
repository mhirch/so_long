/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirch <mhirch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:21:15 by mhirch            #+#    #+#             */
/*   Updated: 2023/05/11 16:10:16 by mhirch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	up(t_info *data_game, int x, int y)
{
	if (data_game->map[y - 1][x] == 'E' && data_game->diammand == 0)
	{
		write(1, "you win\n", ft_strlen("you win\n"));
		exit(EXIT_SUCCESS);
	}
	if (data_game->map[y - 1][x] == '0' || data_game->map[y - 1][x] == 'C')
	{
		data_game->moves++;
		ft_putnbr_fd(data_game->moves, 1);
		write(1, "\n", 1);
		if (data_game->map[y - 1][x] == 'C')
			data_game->diammand--;
		data_game->map[y - 1][x] = 'P';
		data_game->map[y][x] = '0';
		mlx_put_image_to_window(data_game->mlx, data_game->window,
			data_game->background, x * 64, y * 64);
		mlx_put_image_to_window(data_game->mlx, data_game->window,
			data_game->player, x * 64, (y - 1) * 64);
	}
}

void	left(t_info *data_game, int x, int y)
{
	if (data_game->map[y][x - 1] == 'E' && data_game->diammand == 0)
	{
		write(1, "you win\n", ft_strlen("you win\n"));
		exit(EXIT_SUCCESS);
	}
	if (data_game->map[y][x - 1] == '0' || data_game->map[y][x - 1] == 'C')
	{
		data_game->moves++;
		ft_putnbr_fd(data_game->moves, 1);
		write(1, "\n", 1);
		if (data_game->map[y][x - 1] == 'C')
			data_game->diammand--;
		data_game->map[y][x - 1] = 'P';
		data_game->map[y][x] = '0';
		mlx_put_image_to_window(data_game->mlx, data_game->window,
			data_game->background, x * 64, y * 64);
		mlx_put_image_to_window(data_game->mlx, data_game->window,
			data_game->player, (x - 1) * 64, y * 64);
	}
}

void	down(t_info *data_game, int x, int y)
{
	if (data_game->map[y + 1][x] == 'E' && data_game->diammand == 0)
	{
		write(1, "you win\n", ft_strlen("you win\n"));
		exit(EXIT_SUCCESS);
	}
	if (data_game->map[y + 1][x] == '0' || data_game->map[y + 1][x] == 'C')
	{
		data_game->moves++;
		ft_putnbr_fd(data_game->moves, 1);
		write(1, "\n", 1);
		if (data_game->map[y + 1][x] == 'C')
			data_game->diammand--;
		data_game->map[y + 1][x] = 'P';
		data_game->map[y][x] = '0';
		mlx_put_image_to_window(data_game->mlx, data_game->window,
			data_game->background, x * 64, y * 64);
		mlx_put_image_to_window(data_game->mlx, data_game->window,
			data_game->player, x * 64, (y + 1) * 64);
	}
}

void	right(t_info *data_game, int x, int y)
{
	if (data_game->map[y][x + 1] == 'E' && data_game->diammand == 0)
	{
		write(1, "you win\n", ft_strlen("you win\n"));
		exit(EXIT_SUCCESS);
	}
	if (data_game->map[y][x + 1] == '0' || data_game->map[y][x + 1] == 'C')
	{
		data_game->moves++;
		ft_putnbr_fd(data_game->moves, 1);
		write(1, "\n", 1);
		if (data_game->map[y][x + 1] == 'C')
			data_game->diammand--;
		data_game->map[y][x + 1] = 'P';
		data_game->map[y][x] = '0';
		mlx_put_image_to_window(data_game->mlx, data_game->window,
			data_game->background, x * 64, y * 64);
		mlx_put_image_to_window(data_game->mlx, data_game->window,
			data_game->player, (x + 1) * 64, y * 64);
	}
}

int	move(int key_code, t_info *data_game)
{
	t_position	p;
	int			i;

	i = 0;
	data_game->diammand = count_collec(data_game->map);
	p = get_position(data_game->map, 'P');
	if (key_code == 13 || key_code == 126)
		up(data_game, p.x, p.y);
	else if (key_code == 0 || key_code == 123)
		left(data_game, p.x, p.y);
	else if (key_code == 1 || key_code == 125)
		down(data_game, p.x, p.y);
	else if (key_code == 2 || key_code == 124)
		right(data_game, p.x, p.y);
	else if (key_code == 53)
		exit(0);
	return (0);
}
