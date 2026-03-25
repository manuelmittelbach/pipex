/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmittelb <mmittelb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 13:45:52 by mmittelb          #+#    #+#             */
/*   Updated: 2025/09/11 16:51:10 by mmittelb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	input_check(int fd_input, char *filename, int *fd_pipe)
{
	if (fd_input == -1)
	{
		perror(filename);
		close(fd_pipe[1]);
		exit (1);
	}
}

void	output_check(int fd_input, char *filename, int *fd_pipe)
{
	if (fd_input == -1)
	{
		perror(filename);
		close(fd_pipe[0]);
		exit (1);
	}
}

void	create_pipe(int fd_pipe[2])
{
	if (pipe(fd_pipe) == -1)
	{
		perror("pipe error");
		exit (1);
	}
}

int	ft_fork(int *fd_pipe)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork_error");
		close(fd_pipe[0]);
		close(fd_pipe[1]);
		exit (1);
	}
	return (pid);
}
