/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirch <mhirch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 13:49:44 by mhirch            #+#    #+#             */
/*   Updated: 2023/05/09 16:38:49 by mhirch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "so_long.h"
#include <errno.h>

char	*ft_strdup(const char *s1)
{
	char	*str;
	size_t	i;

	str = malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = 0;
	return (str);
}

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
		if (write(1, "Error\nmap error", 15) == -1)
		{
			perror("write");
			exit(1);
		}
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
		if (write(1, "Error\nmap error", 15) == -1)
		{
			perror("write");
			exit(1);
		}
		exit(1);
	}
	while (s1[i] && s2[i])
	{
		if (s1[i] == '\n' || s2[i] == '\n')
			break ;
		if (s1[i] != '1' || s2[i] != '1')
		{
			if (write(1, "Error\nmap error", 15) == -1)
			{
				perror("write");
				exit(1);
			}
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
			if (write(1, "Error\nmap error", 15) == -1)
			{
				perror("write");
				exit(1);
			}
			exit(1);
		}
		i++;
	}
	len1 = ft_strlen(s[i]);
	if (len0 != len1 + 1)
	{
		if (write(1, "Error\nmap error", 15) == -1)
		{
			perror("write");
			exit(1);
		}
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
			if (write(1, "Error\nmap error", 15) == -1)
			{
				perror("write");
				exit(1);
			}
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
			if (write(1, "Error\nmap error", 15) == -1)
			{
				perror("write");
				exit(1);
			}
			exit(1);
		}
		i++;
	}
	if ((*p) > 1 || (*e) > 1)
	{
		if (write(1, "Error\nmore than one player and or exit", 38) == -1)
		{
			perror("write");
			exit(1);
		}
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
			if (write(1, "Error\nmap error", 15) == -1)
			{
				perror("write");
				exit(1);
			}
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
		if (write(1, "Error\ncould not open file", 25) == -1)
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
	// while(map_lines[i])
	// 	printf("%s", map_lines[i++]);
	return (map_lines);
}

void	*ft_memset(void *s, int c, size_t n)
{
	char	*ch;
	size_t	i;

	ch = s;
	i = 0;
	while (i < n - 2)
		ch[i++] = (unsigned int)c;
	ch[i++] = '\n';
	ch[i] = '\0';
	return (ch);
}

void duplicate_map(char **map, t_info *a)
{
	int i;
	int j;
	
	a->rows = 0;
	a->col = 0;
	while (map[a->rows])
		a->rows++;
	a->m = malloc(sizeof(char *) * a->rows + 1);
	while (map[0][a->col])
		a->col++;
	i = 0;
	while(i < a->rows)
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
	a->m[a->rows]  = NULL;
	a->col--;
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
void	copy_map_m(char **map, t_info a)
{
	int i;
	int j;

	a.rows = 0;
	a.col = 0;
	i = 0;

	while (map[a.rows])
		a.rows++;
	a.m = malloc(sizeof(char *) * a.rows);
	while (map[0][a.col])
		a.col++;
	printf("\n--%d\n", a.col);
	while ( i < a.rows)
	{
		j = 0;
		a.m[i] = ft_strdup(map[i]);
		
		printf("%s", a.m[i]);
		i++;
	}
	
	// a.rows = 0;
	// a.col = 0;
	// while (map[a.rows])
	// 	a.rows++;
	// a.m = malloc(sizeof(char *) * a.rows);
	// while (map[0][a.col])
	// 	a.col++;
	// a.rows = 0;
	// while (map[a.rows])
	// {
	// 	map[a.rows] = malloc(sizeof(char) * a.col);
	// 	a.col = 0;
	// 	while (map[a.rows][a.col])
	// 	{
	// 			a.m[a.rows][a.col] = map[a.rows][a.col];
	// 		a.col++;
	// 	}
	// 	a.rows++;
	// }
}
int check_roadblock(int x, int y, char **m)
{
	if (m[y][x] == 'C' || m[y][x] == '0' || m[y][x] == 'E')
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
int	calcul_p_c(char **map, int *e, int *c)
{
	int i;
	int j;

	(*c)= 0;
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
void	check_path(char **map, t_info *a)
{
	t_position p;
	int e;
	int c;
	
	duplicate_map(map, a);
	p = get_position(map, 'P');
	set_p_m(a->m, p.x, p.y);
	if (calcul_p_c(a->m, &e, &c))
	{
		if (write(1, "Error\ninvalid map", 17) == -1)
		{
			perror("write");
			exit(1);
		}
		exit(1);
	}
}
void	set_image(t_info *data_game)
{
	data_game->player = mlx_xpm_file_to_image(data_game->mlx, "textures/player.xpm", &data_game->img_width, &data_game->img_height);
	// data_game->collectible = mlx_xpm_file_to_image(data_game->mlx, "textures/collectible.xpm", &data_game->img_width, &data_game->img_height);
	// data_game->wall = mlx_xpm_file_to_image(data_game->mlx, "textures/wall.xpm", &data_game->img_width, &data_game->img_height);
	// data_game->exit = mlx_xpm_file_to_image(data_game->mlx, "textures/exit.xpm", &data_game->img_width, &data_game->img_height);
	// data_game->background = mlx_xpm_file_to_image(data_game->mlx, "textures/background.xpm", &data_game->img_width, &data_game->img_height);
	
}
void	put_img_to_window(t_info *data_game)
{
	t_position player;

	set_image(data_game);
	player = get_position(data_game->map, 'P');
	printf("%d\n", player.x);
	printf("%d\n", player.y);
	mlx_put_image_to_window(data_game->mlx, data_game->window, data_game->player, player.x, player.y);
}

int main(int ac, char **av)
{
	t_info	data_game;
	if (ac == 2)
	{
		data_game.map = check_map(av[1]);
		check_path(data_game.map, &data_game);
		data_game.mlx = mlx_init();
		data_game.window = mlx_new_window(data_game.mlx, data_game.col * 64, data_game.rows * 64, "so_long");
		put_img_to_window(&data_game);
		mlx_loop(data_game.mlx);
	}
}
