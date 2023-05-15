/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirch <mhirch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:13:06 by mhirch            #+#    #+#             */
/*   Updated: 2023/05/13 18:34:22 by mhirch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	calcul_p_c(char **map, int *e, int *c)
{
	int	i;
	int	j;

	(*c) = 0;
	(*e) = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == 'C')
				(*c)++;
			else if (map[i][j] == 'E')
				(*e)++;
			j++;
		}
		i++;
	}
	if (*c > 0 || *e > 0)
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
