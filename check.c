/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirch <mhirch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:46:09 by mhirch            #+#    #+#             */
/*   Updated: 2023/05/15 18:38:05 by mhirch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_first_last_line(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1[0] || !s2[0])
		erreur();
	while (s1[i] && s2[i])
	{
		if (s1[i] == '\n' || s2[i] == '\n')
			break ;
		if (s1[i] != '1' || s2[i] != '1')
			erreur();
		i++;
	}
}

void	check_lines_length(char **s, int n)
{
	int	i;
	int	len0;
	int	len1;

	i = 1;
	len0 = ft_strlen(s[0]);
	while (i < n - 1)
	{
		len1 = ft_strlen(s[i]);
		if (len0 != len1)
			erreur();
		i++;
	}
	len1 = ft_strlen(s[i]);
	if (len0 != len1 + 1)
		erreur();
	if (len0 > 41)
	{
		write(1, "Error\nmap so_long\n", 18);
		exit(1);
	}
	check_long(len1, n);
}

void	check_wall(char **s, int n)
{
	int	i;
	int	len;

	i = 1;
	len = ft_strlen(s[n - 1]);
	check_first_last_line(s[0], s[n - 1]);
	while (s[i])
	{
		if (s[i][0] != '1' || s[i][len - 1] != '1')
		{
			if (write(1, "Error\nmap error\n", 16) == -1)
			{
				perror("write");
				exit(1);
			}
			exit(1);
		}
		i++;
	}
}

void	check(char **map_lines, int n)
{
	int		i;
	int		p;
	int		c;
	int		e;

	check_lines_length(map_lines, n);
	check_wall(map_lines, n);
	p = 0;
	c = 0;
	e = 0;
	i = -1;
	while (++i < n)
	{
		if (!ft_strncmp(map_lines[i], "\n", 1)
			|| !ft_strncmp(map_lines[n - 1], "\n", 1))
			erreur();
		player_collectible_exit(map_lines[i], &p, &c, &e);
	}
	check_player_exit(p, e);
	if (c < 1)
		no_collectible();
}

char	**check_map(char *map)
{
	char	**map_lines;
	int		fd;
	int		i;
	int		lines;

	fd = open(map, O_RDONLY);
	if (fd == -1)
	{
		if (write(1, "Error\ncould not open file\n", 26) == -1)
		{
			perror("write");
			exit(1);
		}
		exit(1);
	}
	lines = count_lines(map);
	map_lines = malloc(sizeof(char *) * lines + 1);
	map_lines[0] = get_next_line(fd);
	i = 1;
	while (i < lines)
		map_lines[i++] = get_next_line(fd);
	map_lines[i] = NULL;
	check(map_lines, i);
	i = 0;
	return (map_lines);
}
