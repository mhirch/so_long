/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhirch <mhirch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:59:11 by mhirch            #+#    #+#             */
/*   Updated: 2023/05/01 17:01:00 by mhirch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static	int	count_str(const char *str, char c)
{
	int	i;
	int	z;

	i = 0;
	z = 0;
	if (str == NULL)
		return (0);
	if (str[i] != c)
		z++;
	while (str[i])
	{
		if (str[i] == c && str[i + 1] != c && str[i + 1] != '\0')
			z++;
		i++;
	}
	i = 0;
	return (z);
}

static	void	f_free(char **tab, int j)
{
	while (j >= 0)
	{
		free(tab[j]);
		j--;
	}
	free(tab);
}
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substring;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	substring = malloc(sizeof(char) * len + 1);
	if (!substring)
		return (NULL);
	if (start >= (unsigned int)ft_strlen((char *)s))
	{
		*substring = '\0' ;
		return (substring);
	}
	while (i < len && s[start])
	{
		substring[i] = s[start];
		i++;
		start++;
	}
	substring[i] = '\0';
	return (substring);
}

static	void	skip(char const *s, int *i, int *index, char c)
{
	while (s[*i] && s[*i] == c)
		(*i)++;
	*index = *i;
	while (s[*i] && s[*i] != c)
		(*i)++;
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**tab;
	int		index;

	i = 0;
	j = 0;
	tab = malloc(sizeof(char *) * (count_str(s, c) + 1));
	if (!tab || !s)
		return (NULL);
	while (i <= (int)ft_strlen(s))
	{
		skip(s, &i, &index, c);
		if (index < i)
		{
			tab[j] = ft_substr(&s[index], 0, i - index);
			if (!tab[j])
				f_free(tab, j);
			j++;
		}
		i++;
	}
	tab[j] = NULL;
	return (tab);
}