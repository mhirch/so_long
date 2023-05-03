/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirch <mhirch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:54:23 by mhirch            #+#    #+#             */
/*   Updated: 2022/12/02 15:34:55 by mhirch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_correct_line(char *str)
{
	size_t	i;
	char	*correct_str;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	correct_str = (char *)malloc(sizeof(char) * (i + 1));
	if (!correct_str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		correct_str[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		correct_str[i] = str[i];
		i++;
	}
	return (correct_str[i] = '\0', correct_str);
}

char	*new_str(char *str)
{
	size_t	i;
	size_t	j;
	char	*new_str;

	i = 0;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] && str[i] == '\n')
		i++;
	new_str = (char *)malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (!new_str)
		return (NULL);
	j = 0;
	while (str[i])
		new_str[j++] = str[i++];
	new_str[j] = '\0';
	free(str);
	return (new_str);
}

char	*read_str(int fd, char *str)
{
	char	*buf;
	int		read_bt;

	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	read_bt = 1;
	while (!ft_strchr(str, '\n') && read_bt != 0)
	{
		read_bt = read(fd, buf, BUFFER_SIZE);
		if (read_bt == -1)
		{
			free(buf);
			free (str);
			str = NULL;
			return (NULL);
		}
		buf[read_bt] = '\0';
		str = ft_strjoin(str, buf);
	}
	free(buf);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*str[OPEN_MAX];

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX || fd > OPEN_MAX)
		return (NULL);
	str[fd] = read_str(fd, str[fd]);
	if (!str[fd])
		return (NULL);
	line = get_correct_line(str[fd]);
	str[fd] = new_str(str[fd]);
	return (line);
}
