/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmittelb <mmittelb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025//11 11:14:39 by mmittelb          #+#    #+#             */
/*   Updated: 2025/09/12 15:39:22 by mmittelb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	close_all_pipes(t_struct pipex, int **pipes)
{
	int	j;
	int	k;

	k = 0;
	while (k < pipex.amount_of_pipes)
	{
		j = 0;
		while (j != 2)
		{
			close(pipes[k][j]);
			j++;
		}
		k++;
	}
}

void	free_multiple_pipes(int **pipes, int amount_of_pipes)
{
	int	i;

	i = 0;
	while (i < amount_of_pipes)
	{
		free((pipes)[i]);
		i++;
	}
	free(pipes);
}

void	free_pipes_free_child_pids(t_struct pipex, int **pipes, pid_t *child_pids)
{
	free_multiple_pipes(pipes, pipex.amount_of_pipes);
	free(child_pids);
}

static void	wait_for_children(pid_t *child_pids, int amount)
{
	int	i;

	i = 0;
	while (i < amount)
	{
		waitpid(child_pids[i], NULL, 0);
		i++;
	}
}

void	cleanup_pipes_free_child_pids_wait_for_childs(t_struct pipex, int **pipes, pid_t *child_pids, int pid_i)
{
	close_all_pipes(pipex, pipes);
	wait_for_children(child_pids, pid_i);
	free_pipes_free_child_pids(pipex, pipes, child_pids);
}
