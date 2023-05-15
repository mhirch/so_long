/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirch <mhirch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:07:29 by mhirch            #+#    #+#             */
/*   Updated: 2023/05/15 15:30:43 by mhirch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	duplicate_map(char **map, t_info *a)
{
	int	i;
	int	j;

	a->rows = 0;
	a->col = 0;
	while (map[a->rows])
		a->rows++;
	a->m = malloc(sizeof(char *) * a->rows + 1);
	while (map[0][a->col])
		a->col++;
	i = 0;
	while (i < a->rows)
	{
		a->m[i] = malloc(sizeof(char) * a->col);
		j = 0;
		while (j <= a->col)
		{
			a->m[i][j] = map[i][j];
			j++;
		}
		i++;
	}
	a->m[a->rows] = NULL;
	a->col--;
}

t_position	get_position(char **map, char x)
{
	t_position	position;
	bool		p;

	p = 0;
	position.y = 0;
	while (map[position.y])
	{
		position.x = 0;
		while (map[position.y][position.x])
		{
			if (map[position.y][position.x] == x)
			{
				p = 1;
				break ;
			}
			position.x++;
		}
		if (p == 1)
			break ;
		position.y++;
	}
	return (position);
}

int	check_roadblock(int x, int y, char **m)
{
	if (m[y][x] == 'C' || m[y][x] == '0')
		return (1);
	return (0);
}

void	set_p_m(char **map, int x, int y)
{
	if (check_roadblock(x + 1, y, map))
	{
		map[y][x + 1] = 'P';
		set_p_m(map, x + 1, y);
	}
	if (check_roadblock(x - 1, y, map))
	{
		map[y][x - 1] = 'P';
		set_p_m(map, x - 1, y);
	}
	if (check_roadblock(x, y + 1, map))
	{
		map[y + 1][x] = 'P';
		set_p_m(map, x, y + 1);
	}
	if (check_roadblock(x, y - 1, map))
	{
		map[y - 1][x] = 'P';
		set_p_m(map, x, y - 1);
	}
}

void	check_path(char **map, t_info *a)
{
	t_position	p;

	duplicate_map(map, a);
	p = get_position(map, 'P');
	set_p_m(a->m, p.x, p.y);
	if (calcul_c(a->m) || check_exit(a->m))
	{
		if (write(1, "Error\ninvalid map\n", 18) == -1)
		{
			perror("write");
			exit(1);
		}
		exit(1);
	}
}
