/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipes_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelmittelbach <manuelmittelbach@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 16:54:13 by mmittelb          #+#    #+#             */
/*   Updated: 2026/03/25 14:02:56 by manuelmitte      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	exec_first_command(int **pipes, char **argv, t_struct pipex)
{
	int	fd_input;

	fd_input = open(argv[1], O_RDONLY);
	input_check_bonus(pipex, fd_input, pipes, argv[1]);
	dup2(fd_input, 0);
	close(fd_input);
	dup2((pipes)[0][1], 1);
	close_all_pipes(pipex, pipes);
	resolve_and_execute_bonus(pipex, argv[2], pipes);
}

void	multiple_pipes(t_struct pipex, char **argv)
{
	int		**pipes;
	int		pid_i;
	int		pipe_i;

	pid_i = 0;
	create_multiple_pipes(pipex, &pipes);
	pipex.child_pids[pid_i] = ft_fork_bonus(pipex, pipes);
	if (pipex.child_pids[pid_i] == 0)
		exec_first_command(pipes, argv, pipex);
	pid_i++;
	pipe_i = 1;
	while (pipe_i < pipex.amount_of_pipes)
	{
		pipex.child_pids[pid_i] = ft_fork_bonus(pipex, pipes);
		if (pipex.child_pids[pid_i] == 0)
			exec_middle_command(pipex, pipes, pipe_i, argv);
		pid_i++;
		pipe_i++;
	}
	pipex.child_pids[pid_i] = ft_fork_bonus(pipex, pipes);
	if (pipex.child_pids[pid_i] == 0)
		exec_last_command_multiple_pipes(pipex, pipes, pipes[pipex.amount_of_pipes - 1], argv);
	pid_i++;
	cleanup_pipes_free_child_pids_wait_for_childs(pipex, pipes, pipex.child_pids, pid_i);
}

