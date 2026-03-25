/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelmittelbach <manuelmittelbach@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 17:00:07 by mmittelb          #+#    #+#             */
/*   Updated: 2026/03/25 14:49:57 by manuelmitte      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	ft_get_all_lines(t_struct pipex, int fd_pipe[2], \
	char **argv, int **pipes)
{
	char	*limiter_plus_newline;
	char	*line;

	limiter_plus_newline = ft_strjoin(argv[2], "\n");
	if (!limiter_plus_newline)
		return (close_all_pipes(pipex, pipes), free_pipes_free_child_pids(pipex, pipes, pipex.child_pids), 1);
	line = get_next_line(0);
	if (!line)
		return (close_all_pipes(pipex, pipes), free_pipes_free_child_pids(pipex, pipes, pipex.child_pids), free(limiter_plus_newline), 1);
	while (line && ft_strncmp(line, limiter_plus_newline, ft_strlen(limiter_plus_newline)) != 0)
	{
		write(fd_pipe[1], line, ft_strlen(line));
		free(line);
		line = get_next_line(0);
		if (!line)
			return (close_all_pipes(pipex, pipes), free_pipes_free_child_pids(pipex, pipes, pipex.child_pids), free(limiter_plus_newline), 1);
	}
	free(line);
	free(limiter_plus_newline);
	close_all_pipes(pipex, pipes);
	free_pipes_free_child_pids(pipex, pipes, pipex.child_pids);
	return (0);
}

void	ft_here_doc(t_struct pipex, char **argv)
{
	int		**pipes;
	int		pid_i;
	int		pipe_i;

	pid_i = 0;
	create_multiple_pipes(pipex, &pipes);
	pipex.child_pids[pid_i] = ft_fork_bonus(pipex, pipes);
	if (pipex.child_pids[pid_i] == 0)
	{
		if (ft_get_all_lines(pipex, pipes[0], argv, pipes) == 1)
			exit (1);
		exit (0);
	}
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
		exec_last_command_here_doc(pipex, pipes, pipes[pipex.amount_of_pipes - 1], argv);
	pid_i++;
	cleanup_pipes_free_child_pids_wait_for_childs(pipex, pipes, pipex.child_pids, pid_i);
}
