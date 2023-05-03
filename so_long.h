/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirch <mhirch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 14:52:50 by mhirch            #+#    #+#             */
/*   Updated: 2023/05/03 16:16:16 by mhirch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <stdio.h>
#include <stdbool.h>
#include <string.h>
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
	int		rows;
	int		col;
}	t_info;


char	**get_map_line(int fd, int i);
char	**ft_split(char const *s, char c);


#endif