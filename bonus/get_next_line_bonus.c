/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelmittelbach <manuelmittelbach@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 16:56:38 by mmittelb          #+#    #+#             */
/*   Updated: 2026/03/24 19:07:34 by manuelmitte      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static char	*ft_strjoin_char(char *s, char c)
{
	int		len;
	char	*new_str;
	int		i;

	len = 0;
	if (s)
		while (s[len])
			len++;
	new_str = malloc(len + 2);
	if (!new_str)
	{
		free(s);
		return (NULL);
	}
	i = 0;
	while (i < len)
	{
		new_str[i] = s[i];
		i++;
	}
	new_str[i++] = c;
	new_str[i] = '\0';
	free(s);
	return (new_str);
}

char	*get_next_line(int fd)
{
	char	buffer;
	char	*line;
	ssize_t	bytes_read;

	line = NULL;
	if (fd < 0)
		return (NULL);
	bytes_read = read(fd, &buffer, 1);
	while (bytes_read > 0)
	{
		line = ft_strjoin_char(line, buffer);
		if (!line)
			return (NULL);
		if (buffer == '\n')
			break ;
		bytes_read = read(fd, &buffer, 1);
	}
	if (bytes_read == -1)
	{
		free(line);
		return (NULL);
	}
	if (bytes_read == 0 && !line)
		return (NULL);
	return (line);
}
