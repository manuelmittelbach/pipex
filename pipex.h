/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelmittelbach <manuelmittelbach@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 12:26:33 by mmittelb          #+#    #+#             */
/*   Updated: 2026/03/25 15:06:13 by manuelmitte      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/types.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>

typedef struct s_struct
{
	char	**environment;
	int		path_index;
}	t_struct;

/* pipex */
void	resolve_and_execute(t_struct pipex, char *command);
void	create_pipe(int fd_pipe[2]);
int		ft_fork(int *fd_pipe);

/* error handling */
void	input_check(int fd_input, char *filename, int *fd_pipe);
void	output_check(int fd_input, char *filename, int *fd_pipe);

/* cleanup */
void	free_splitted_command_and_path(int path_index, char **full_path,
			char **splitted_command);
void	free_rest_of_path(char **paths, int i);

/* libft utils */
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *s);
char	**ft_split(char const *s, char c);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
char	*ft_strjoin(char const *s1, char const *s2);

#endif
