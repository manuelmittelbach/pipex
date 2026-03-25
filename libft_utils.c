/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmittelb <mmittelb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 13:41:31 by mmittelb          #+#    #+#             */
/*   Updated: 2025/09/08 13:29:33 by mmittelb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	char	*start_sub;

	if (start >= ft_strlen(s))
	{
		sub = (char *)malloc(sizeof(char) * 1);
		if (!sub)
			return (NULL);
		*sub = '\0';
		return (sub);
	}
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	sub = (char *)malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	start_sub = sub;
	while (len--)
	{
		*sub = s[start];
		sub++;
		start++;
	}
	*sub = '\0';
	return (start_sub);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)

{
	size_t				i;
	const unsigned char	*s1u;
	const unsigned char	*s2u;

	s1u = (const unsigned char *)s1;
	s2u = (const unsigned char *)s2;
	i = 0;
	while ((s1u[i] != '\0' || s2u[i] != '\0') && i < n)
	{
		if (s1u[i] == s2u[i])
			i++;
		else if (s1u[i] != s2u[i])
			return (s1u[i] - s2u[i]);
	}
	return (0);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	src_len;

	src_len = ft_strlen((char *)src);
	i = 0;
	if (size > 0)
	{
		while (src[i] && i < size - 1)
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (src_len);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;

	ptr = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (ptr == NULL)
		return (NULL);
	ft_strlcpy(ptr, s1, (ft_strlen(s1)) + 1);
	ft_strlcat(ptr, s2, (ft_strlen(s1) + ft_strlen(s2)) + 1);
	return (ptr);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	j = ft_strlen(dst);
	i = 0;
	if (size <= j)
		return (size + ft_strlen(src));
	while (i < (size - j - 1) && src[i])
	{
		dst[j + i] = src[i];
		i++;
	}
	dst[j + i] = '\0';
	return (j + ft_strlen(src));
}
