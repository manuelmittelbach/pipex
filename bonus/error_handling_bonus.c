/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelmittelbach <manuelmittelbach@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 11:14:39 by mmittelb          #+#    #+#             */
/*   Updated: 2026/03/25 14:31:59 by manuelmitte      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	input_check_bonus(t_struct pipex, int fd_input, int **pipes, char *filename)
{
	if (fd_input == -1)
	{
		perror(filename);
		close_all_pipes(pipex, pipes);
		free_pipes_free_child_pids(pipex, pipes, pipex.child_pids);
		exit (1);
	}
}

void	output_check_bonus(t_struct pipex, int fd_output, int **pipes, char *filename)
{
	if (fd_output == -1)
	{
		perror(filename);
		close_all_pipes(pipex, pipes);
		free_pipes_free_child_pids(pipex, pipes, pipex.child_pids);
		exit (1);
	}
}

void	create_pipe_bonus(t_struct pipex, int ***pipes, int fd_pipe[2], int amount_of_pipes_created)
{
	int	k;
	int	j;

	if (pipe(fd_pipe) == -1)
	{
		k = 0;
		while (k < amount_of_pipes_created)
		{
			j = 0;
			while (j != 2)
			{
				close((*pipes)[k][j]);
				j++;
			}
			k++;
		}
		free_multiple_pipes(*pipes, amount_of_pipes_created);
		free(pipex.child_pids);
		perror("pipe error");
		exit (1);
	}
}

void	create_multiple_pipes(t_struct pipex, int ***pipes)
{
	int	i;

	*pipes = malloc(sizeof(int *) * (pipex.amount_of_pipes));
	if (!(*pipes))
	{
		free(pipex.child_pids);
		exit(1);
	}
	i = 0;
	while (i < pipex.amount_of_pipes)
	{
		(*pipes)[i] = malloc(sizeof(int) * 2);
		if (!(*pipes)[i])
		{
			while (--i >= 0)
			{
				close((*pipes)[i][0]);
				close((*pipes)[i][1]);
				free((*pipes)[i]);
			}
			free(*pipes);
			*pipes = NULL;
			free(pipex.child_pids);
			exit(1);
		}
		create_pipe_bonus(pipex, pipes, (*pipes)[i], i);
		i++;
	}
}

int	ft_fork_bonus(t_struct pipex, int **pipes)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork_error");
		close_all_pipes(pipex, pipes);
		free_multiple_pipes(pipes, pipex.amount_of_pipes);
		free(pipex.child_pids);
		exit (1);
	}
	return (pid);
}
