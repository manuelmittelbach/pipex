/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmittelb <mmittelb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 11:24:34 by mmittelb          #+#    #+#             */
/*   Updated: 2025/09/10 13:55:59 by mmittelb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_wordlen(char const *s, int i, char c)
{
	int	count;

	count = 0;
	while (s[i] && s[i] != c)
	{
		i++;
		count = count + 1;
	}
	return (count);
}

static int	ft_stramount(char const *s, char c)
{
	int		count;
	size_t	i;
	size_t	b_index;

	count = 0;
	b_index = ft_strlen(s);
	while (s[b_index] == c)
		b_index--;
	i = 0;
	while (s[i] == c)
		i++;
	while (s[i] && (i < b_index))
	{
		while (s[i] && s[i] != c)
			i++;
		count++;
		while (s[i] && s[i] == c)
			i++;
	}
	return (count);
}

static char	**ft_free(char ***ptr, int j)
{
	while (j >= 0)
	{
		free((*ptr)[j]);
		j--;
	}
	free(*ptr);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**ptr;

	i = 0;
	j = 0;
	ptr = malloc(sizeof(char *) * (ft_stramount(s, c) + 1));
	if (!ptr)
		return (NULL);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] == '\0')
			break ;
		ptr[j] = ft_substr(s, i, ft_wordlen(s, i, c));
		if (!ptr[j])
			return (ft_free(&ptr, j));
		while (s[i] != c && s[i] != '\0')
			i++;
		j++;
	}
	ptr[j] = NULL;
	return (ptr);
}
