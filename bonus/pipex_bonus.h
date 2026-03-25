/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelmittelbach <manuelmittelbach@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 17:03:22 by mmittelb          #+#    #+#             */
/*   Updated: 2026/03/25 15:06:44 by manuelmitte      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <sys/types.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>

typedef struct s_struct
{
	pid_t	*child_pids;
	int		amount_of_pipes;
	int		amount_of_forks;
	char	**environment;
	int		argc;
	int		path_index;
}	t_struct;

/* pipex bonus */
void	ft_here_doc(t_struct pipex, char **argv);
void	multiple_pipes(t_struct pipex, char **argv);
void	resolve_and_execute_bonus(t_struct pipex, char *command, int **pipes);

/* pipe creation / process handling */
void	create_pipe_bonus(t_struct pipex, int ***pipes, int fd_pipe[2],
			int amount_of_pipes);
void	create_multiple_pipes(t_struct pipex, int ***pipes);
int		ft_fork_bonus(t_struct pipex, int **pipes);

/* command execution */
void	exec_last_command_here_doc(t_struct pipex, int **pipes,
			int fd_pipe[2], char **argv);
void	exec_last_command_multiple_pipes(t_struct pipex, int **pipes,
			int fd_pipe[2], char **argv);
void	exec_middle_command(t_struct pipex, int **pipes, int pipe_i,
			char **argv);

/* error handling */
void	output_check_bonus(t_struct pipex, int fd_output, int **pipes,
			char *filename);
void	input_check_bonus(t_struct pipex, int fd_input, int **pipes,
			char *filename);

/* cleanup */
void	cleanup_pipes_free_child_pids_wait_for_childs(t_struct pipex,
			int **pipes, pid_t *child_pids, int pid_i);
void	free_pipes_free_child_pids(t_struct pipex, int **pipes,
			pid_t *child_pids);
void	free_splitted_command_and_path(int path_index, char **paths,
			char **splitted_command);
void	free_multiple_pipes(int **pipes, int amount_of_pipes);
void	free_rest_of_path(char **paths, int i);
void	close_all_pipes(t_struct pipex, int **pipes);

/* get_next_line */
char	*get_next_line(int fd);

/* libft utils */
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *s);
char	**ft_split(char const *s, char c);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
char	*ft_strjoin(char const *s1, char const *s2);

#endif