/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelmittelbach <manuelmittelbach@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 12:45:46 by mmittelb          #+#    #+#             */
/*   Updated: 2026/03/24 18:57:27 by manuelmitte      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	exec_pipe(t_struct pipex, int *fd_pipe, char **argv, int pid)
{
	int		fd_input;
	int		fd_output;

	if (pid == 0)
	{
		close (fd_pipe[0]);
		fd_input = open(argv[1], O_RDONLY);
		input_check(fd_input, argv[1], fd_pipe);
		dup2(fd_input, 0);
		close(fd_input);
		dup2(fd_pipe[1], 1);
		close(fd_pipe[1]);
		resolve_and_execute(pipex, argv[2]);
	}
	else
	{
		close (fd_pipe[1]);
		fd_output = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		output_check(fd_output, argv[4], fd_pipe);
		dup2(fd_pipe[0], 0);
		close(fd_pipe[0]);
		dup2(fd_output, 1);
		close(fd_output);
		resolve_and_execute(pipex, argv[3]);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int			fd_pipe[2];
	pid_t		pid;
	t_struct	pipex;

	pipex.environment = envp;
	pipex.path_index = 0;
	if (argc != 5)
	{
		write(2, "invalid amount of arguments\n", 28);
		exit (1);
	}
	create_pipe(fd_pipe);
	pid = ft_fork(fd_pipe);
	exec_pipe(pipex, fd_pipe, argv, pid);
	return (0);
}
