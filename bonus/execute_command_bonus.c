/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelmittelbach <manuelmittelbach@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 18:55:57 by manuelmitte       #+#    #+#             */
/*   Updated: 2026/03/25 14:58:20 by manuelmitte      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	exec_command_bonus(t_struct pipex, int **pipes, char **paths, char *path_try, char **splitted_command, int i)
{
	if (access(path_try, X_OK) == 0)
	{
		free_rest_of_path(paths, i);
		free_pipes_free_child_pids(pipex, pipes, pipex.child_pids);
		execve(path_try, splitted_command, pipex.environment);
		return (1);
	}
	return (0);
}

static void	attempt_exec_in_paths_bonus(t_struct pipex, int **pipes, char **splitted_command, char **paths)
{
	char	*path_try;
	char	*backslash_command;
	int		i;

	i = 0;
	while (paths[i])
	{
		backslash_command = ft_strjoin("/", splitted_command[0]);
		if (backslash_command == NULL)
		{
			free_splitted_command_and_path(i, paths, splitted_command);
			free_pipes_free_child_pids(pipex, pipes, pipex.child_pids);
			exit (1);
		}
		path_try = ft_strjoin(paths[i], backslash_command);
		if (path_try == NULL)
		{
			free(backslash_command);
			free_splitted_command_and_path(i, paths, splitted_command);
			free_pipes_free_child_pids(pipex, pipes, pipex.child_pids);
			exit (1);
		}
		free(backslash_command);
		free(paths[i]);
		if (exec_command_bonus(pipex, pipes, paths, path_try, splitted_command, i) == 1)
		{
			free_splitted_command_and_path(0, NULL, splitted_command);
			free(path_try);
			perror("execve");
			exit (1);
		}
		i++;
		free(path_try);
	}
}

static char	**split_path_bonus(t_struct pipex, int **pipes, char **splitted_command)
{
	char	**paths;

	paths = ft_split(pipex.environment[pipex.path_index] + 5, ':');
	if (paths == NULL)
	{
		free_splitted_command_and_path(0, NULL, splitted_command);
		free_pipes_free_child_pids(pipex, pipes, pipex.child_pids);
		exit (1);
	}
	return (paths);
}

static char	**parse_command_bonus(t_struct pipex, int **pipes, char *command)
{
	char	**splitted_command;

	splitted_command = ft_split(command, ' ');
	if (splitted_command == NULL)
	{
		free_pipes_free_child_pids(pipex, pipes, pipex.child_pids);
		exit (1);
	}
	if (splitted_command[0] == NULL)
	{
		free(splitted_command);
		free_pipes_free_child_pids(pipex, pipes, pipex.child_pids);
		write(2, command, ft_strlen(command));
		write(2, ": command not found\n", 20);
		exit(127);
	}
	return (splitted_command);
}

void	resolve_and_execute_bonus(t_struct pipex, char *command, int **pipes)
{
	char	**splitted_command;
	char	**paths;

	splitted_command = parse_command_bonus(pipex, pipes, command);
	while (pipex.environment[pipex.path_index]
		&& ft_strncmp(pipex.environment[pipex.path_index], "PATH=", 5) != 0)
		pipex.path_index++;
	if (!pipex.environment[pipex.path_index])
	{
		free_splitted_command_and_path(0, NULL, splitted_command);
		free_pipes_free_child_pids(pipex, pipes, pipex.child_pids);
		write(2, command, ft_strlen(command));
		write(2, ": command not found\n", 20);
		exit(127);
	}
	paths = split_path_bonus(pipex, pipes, splitted_command);
	attempt_exec_in_paths_bonus(pipex, pipes, splitted_command, paths);
	free(paths);
	free_splitted_command_and_path(0, NULL, splitted_command);
	free_pipes_free_child_pids(pipex, pipes, pipex.child_pids);
	write(2, command, ft_strlen(command));
	write(2, ": command not found\n", 20);
	exit(127);
}

void	exec_last_command_here_doc(t_struct pipex, int **pipes, int fd_pipe[2], char **argv)
{
	int		fd_output;

	fd_output = open(argv[pipex.argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	output_check_bonus(pipex, fd_output, pipes, argv[pipex.argc - 1]);
	dup2(fd_pipe[0], 0);
	dup2(fd_output, 1);
	close(fd_output);
	close_all_pipes(pipex, pipes);
	resolve_and_execute_bonus(pipex, argv[pipex.argc - 2], pipes);
}

void	exec_last_command_multiple_pipes(t_struct pipex, int **pipes, int fd_pipe[2], char **argv)
{
	int		fd_output;

	fd_output = open(argv[pipex.argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	output_check_bonus(pipex, fd_output, pipes, argv[pipex.argc - 1]);
	dup2(fd_pipe[0], 0);
	dup2(fd_output, 1);
	close(fd_output);
	close_all_pipes(pipex, pipes);
	resolve_and_execute_bonus(pipex, argv[pipex.argc - 2], pipes);
}

void	exec_middle_command(t_struct pipex, int **pipes, int pipe_i, char **argv)
{
	int		fd_in;
	int		fd_out;

	fd_in = (pipes)[pipe_i - 1][0];
	fd_out = (pipes)[pipe_i][1];
	dup2(fd_in, 0);
	dup2(fd_out, 1);
	close_all_pipes(pipex, pipes);
	resolve_and_execute_bonus(pipex, argv[pipe_i + 2], pipes);
}
