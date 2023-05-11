/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirch <mhirch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:44:09 by mhirch            #+#    #+#             */
/*   Updated: 2023/05/11 15:34:41 by mhirch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

void	ft_putchar_fd(char c, int fd)
{
	write (fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		write (fd, "-2147483648", 11);
	}
	if (n == 2147483647)
	{
		write (fd, "2147483647", 10);
	}
	else if (n < 0 && n >= -2147483647)
	{
		ft_putchar_fd('-', fd);
		n *= -1;
		ft_putnbr_fd(n, fd);
	}
	else if (n > 9 && n < 2147483647)
	{
		ft_putnbr_fd((n / 10), fd);
		ft_putnbr_fd((n % 10), fd);
	}
	else if (n >= 0 && n <= 9)
	{
		ft_putchar_fd(n + 48, fd);
	}
}
