/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirch <mhirch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 14:52:50 by mhirch            #+#    #+#             */
/*   Updated: 2023/05/15 15:26:21 by mhirch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include <mlx.h>
# include <unistd.h>
# include <errno.h>
# include <stdio.h>
# include <stdbool.h>
# include <string.h>
# include <stdlib.h>
# include <limits.h>
# include <fcntl.h>
# include "get_next_line/get_next_line.h"

typedef struct s_position
{
	int		x;
	int		y;
}	t_position;

typedef struct s_info
{
	char	**m;
	char	**map;
	void	*mlx;
	void	*window;
	void	*player;
	void	*collectible;
	void	*exit;
	void	*wall;
	void	*background;
	int		moves;
	int		diammand;
	int		rows;
	int		col;
	int		img_width;
	int		img_height;
}	t_info;

/*libft*/
char		*ft_strdup(const char *s1);
void		*ft_memset(void *s, int c, size_t n);
void		ft_putnbr_fd(int n, int fd);
int			ft_strncmp(const char *str1, const char *str2, size_t l);

t_position	get_position(char **map, char x);
char		**check_map(char *map);
void		player_collectible_exit(char *s, int *p, int *c, int *e);
void		put_img_to_window(t_info *data_game);
void		check_path(char **map, t_info *a);
void		check_long(int len, int n);
void		protect(t_info *d, char x);
void		erreur(void);
void		no_collectible(void);
int			count_lines(char *map);
int			count_collec(char **map);
int			move(int key_code, t_info *data_game);
int			check_exit(char **map);
int			calcul_c(char **map);

#endif
