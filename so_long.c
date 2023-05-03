/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirch <mhirch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 13:49:44 by mhirch            #+#    #+#             */
/*   Updated: 2023/05/03 16:13:23 by mhirch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "so_long.h"

int	ft_strncmp(const char *str1, const char *str2, size_t l)
{
	unsigned int	i;

	i = 0;
	if (l != 0)
	{
		while (str1[i] && str2[i] && str1[i] == str2[i] && i < l - 1)
			i++;
		return ((unsigned char)str1[i] - (unsigned char)str2[i]);
	}
	return (0);
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
	{
		write(1, "Error\nmap error", 15);
		exit(1);
	}
	i = read(fd, c, 1);
	while(i > 0)
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
void check_first_last_line(char *s1, char *s2)
{
	int i;

	i = 0;
	if (!s1[0] || !s2[0])
	{
		write(1, "Error\nmap error", 15);
		exit(1);
	}
	while (s1[i] && s2[i])
	{
		if (s1[i] == '\n' || s2[i] == '\n')
			break ;
		if (s1[i] != '1' || s2[i] != '1')
		{
			write(1, "Error\nmap error", 15);
			exit(1);
		}
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
		{
			write(1, "Error\nmap error", 15);
			exit(1);
		}
		i++;
	}
	len1 = ft_strlen(s[i]);
	if (len0 != len1 + 1)
	{
		write(1, "Error\nmap error", 15);
		exit(1);
	}
}
void	check_wall(char **s, int n)
{
	int i;
	int len;

	i = 1;
	len = ft_strlen(s[n - 1]);
	check_first_last_line(s[0], s[n - 1]);
	while (s[i])
	{
		if (s[i][0] != '1' || s[i][len - 1] != '1')
		{
			write(1, "Error\nmap error", 15);
			exit(1);
		}
		i++;
	}
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
		{
			write(1, "Error\nmap error", 15);
			exit(1);
		}
		i++;
	}
	if ((*p) > 1 || (*e) > 1)
	{
		write(1, "Error\nmore than one player and or exit", 38);
		exit(1);
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
	i = 0;
	p = 0;
	c = 0;
	e = 0;
	while ( i < n)
	{
		if (!ft_strncmp(map_lines[i], "\n", 1) || !ft_strncmp(map_lines[n - 1], "\n", 1))
		{
			write(1, "Error\nmap error", 15);
			exit(1);
		}
		player_collectible_exit(map_lines[i], &p, &c, &e);
		i++;
	}
}
char	**check_map(char *map)
{
	char **map_lines;
	int	fd;
	int	i;
	int lines;

	fd = open(map, O_RDONLY);
	if (fd == -1)
	{
		write(1, "Error\ncould not open file", 25);
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
	// while(map_lines[i])
	// 	printf("%s", map_lines[i++]);
	return (map_lines);
}
// char **creat_empty_map(char **map)
// {
// 	char **m;
// 	int rows;
// 	int cols;
// 	int i;
// 	int j;

// 	rows = 0;
// 	while (map[rows])	
// 		rows++;
// 	rows--;
// 	cols = ft_strlen(map[rows]);
// 	printf("%d\n", cols);
// 	m = malloc(sizeof(char *) * rows);
// 	i = 0;
// 	j = 0;
// 	while (i < rows)
//         m[i++] = (char *)malloc(cols* sizeof(char));
// 	while (i++ < rows )
//     {
//         while (j++ < cols - 1) 
//             m[i][j] = '0';
//     }
// 	i = 0;
// 	j = 0;
// 	while (i++ < rows)
// 	{
//         while (j++ < cols - 1)
// 		{
//             printf("%c", m[i][j]);
//         }
//         printf("\n");
//     }
// 	return (m);
// }

void	*ft_memset(void *s, int c, size_t n)
{
	char	*ch;
	size_t	i;

	ch = s;
	i = 0;
	while (i < n - 1)
		ch[i++] = (unsigned int)c;
	ch[i] = '\0';
	return (ch);
}
// char **creat_empty_map(char **map)
// {
//     char **m;
//     int rows;
//     int cols;
//     int i;
//     int j;

//     // Calculate the number of rows in the map
//     rows = 0;
//     while (map[rows])
//         rows++;
//     cols = ft_strlen(map[rows-1]);

//     m = malloc(sizeof(char *) * (rows));

//     i = 0;
//     while (i < rows)
//     {
//         m[i] = malloc(cols * sizeof(char));
//         j = 0;
//         while (j < cols)
//         {
//             m[i][j] = '0';
//             j++;
//         }
//         i++;
//     }
//     m[i] = NULL;
//     i = 0;
//     while (i < rows)
//     {
//         j = 0;
//         ft_memset(m[i], '0', cols);
//         printf("\n");
//         i++;
//     }

//     return (m);
// }
char **creat_empty_map(char **map)
{
	char **m;
	
	int col;
	int rows;
	
	rows = 0;
	col = 0;
	while (map[rows])
		rows++;
	m = malloc(sizeof(char *) * rows);
	m[rows--] = NULL;
	while (map[0][col])
		col++;
	while(rows >= 0)
	{
		m[rows] = malloc(sizeof(char) * col);
		ft_memset(m[rows--], 48, col);
	}
    return m;
}
t_position get_position(char **map , char x)
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
			break;
		position.y++;
	}
	return (position);
}
void	copy_map_m(char **map, char **m)
{
	int rows;
	int col;
	
	rows = 0;
	while (map[rows])
	{
		col = 0;
		while (map[rows][col])
		{
			if (map[rows][col] == 'P' || map[rows][col] == 'C' || map[rows][col] == '1' || map[rows][col] == 'E')
				m[rows][col] = map[rows][col];
			col++;
		}
		rows++;
	}
}
void	set_p_m(char **map, char **m)
{
	int rows;
	int col;

	
}
void	check_path(char **map)
{
	char	**m;
	t_position p;
	t_position e;
	
	e = get_position(map, 'E');
	p = get_position(map, 'P');
	printf("%d | %d\n", e.x, e.y);
	printf("%d | %d\n", p.x, p.y);
	m = creat_empty_map(map);
	copy_map_m(map, m);
	set_p_m(map, m);
	if (p.x == e.x && p.y == e.y)
		return ;
	printf("\n");
	printf("%s\n", m[0]);
	printf("%s\n", m[1]);
	printf("%s\n", m[2]);
	printf("%s\n", m[3]);
	printf("%s\n", m[4]);
	printf("%s\n", m[5]);
	printf("%s\n", m[6]);
	
	
	
}

int main(int ac, char **av)
{
	char	**map;

	if (ac == 2)
	{
		map = check_map(av[1]);
		check_path(map);
	}

}
