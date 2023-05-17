/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirch <mhirch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:47:50 by mhirch            #+#    #+#             */
/*   Updated: 2023/05/15 18:37:52 by mhirch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	erreur(void)
{
	if (write(1, "Error\nmap error\n", 16) == -1)
	{
		perror("write");
		exit(1);
	}
	exit(1);
}

void	check_long(int len, int n)
{
	if (n > 21)
	{
		if (write(1, "Error\nmap so_long\n", 18) == -1)
		{
			perror("write");
			exit(1);
		}
		exit(1);
	}
	if (n == len)
	{
		if (write(1, "Error\nmap not rectangular\n", 26) == -1)
		{
			perror("write");
			exit(1);
		}
		exit(1);
	}
}

int	count_lines(char *map)
{
	int		lines;
	char	*c;
	int		fd;
	int		i;

	lines = 0;
	c = malloc(sizeof(char) * 2);
	fd = open(map, O_RDONLY);
	if (fd == -1)
		erreur();
	i = read(fd, c, 1);
	while (i > 0)
	{
		i = read(fd, c, 1);
		if (!ft_strncmp(c, "\n", 1))
			lines++;
	}
	if (!ft_strncmp(c, "\n", 1))
		lines--;
	lines++;
	free(c);
	return (lines);
}

void	no_collectible(void)
{
	if (write(1, "Error\nthere is no collectible on the map\n", 41) == -1)
	{
		perror("write");
		exit(1);
	}
	exit(1);
}

void	player_collectible_exit(char *s, int *p, int *c, int *e)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '\n')
	{
		if (s[i] == 'P')
			(*p)++;
		else if (s[i] == 'C')
			(*c)++;
		else if (s[i] == 'E')
			(*e)++;
		else if (s[i] != '1' && s[i] != '0')
			erreur();
		i++;
	}
}
