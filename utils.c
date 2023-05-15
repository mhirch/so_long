/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirch <mhirch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:13:06 by mhirch            #+#    #+#             */
/*   Updated: 2023/05/15 15:44:43 by mhirch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	calcul_c(char **map)
{
	int	i;
	int	j;
	int	c;

	c = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == 'C')
				c++;
			j++;
		}
		i++;
	}
	if (c > 0)
		return (1);
	return (0);
}

int	count_collec(char **map)
{
	int	i;
	int	j;
	int	c;

	c = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == 'C')
				c++;
			j++;
		}
		i++;
	}
	return (c);
}

int	check_exit(char **map)
{
	t_position	e;

	e = get_position(map, 'E');
	if (map[e.y][e.x - 1] == 'P')
		return (0);
	if (map[e.y][e.x + 1] == 'P')
		return (0);
	if (map[e.y - 1][e.x] == 'P')
		return (0);
	if (map[e.y + 1][e.x] == 'P')
		return (0);
	return (1);
}
