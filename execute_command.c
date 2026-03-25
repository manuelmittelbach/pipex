/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelmittelbach <manuelmittelbach@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 18:55:57 by manuelmitte       #+#    #+#             */
/*   Updated: 2026/03/25 14:59:56 by manuelmitte      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	exec_command(t_struct pipex, char **paths, char *path_try, char **splitted_command, int i)
{
	if (access(path_try, X_OK) == 0)
	{
		free_rest_of_path(paths, i);
		execve(path_try, splitted_command, pipex.environment);
		return (1);
	}
	return (0);
}

static void	attempt_exec_in_paths(t_struct pipex, char **splitted_command, char **paths)
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
			exit (1);
		}
		path_try = ft_strjoin(paths[i], backslash_command);
		if (path_try == NULL)
		{
			free(backslash_command);
			free_splitted_command_and_path(i, paths, splitted_command);
			exit (1);
		}
		free(backslash_command);
		free(paths[i]);
		if (exec_command(pipex, paths, path_try, splitted_command, i) == 1)
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

static char	**split_path(t_struct pipex, char **splitted_command)
{
	char	**paths;

	paths = ft_split(pipex.environment[pipex.path_index] + 5, ':');
	if (paths == NULL)
	{
		free_splitted_command_and_path(0, NULL, splitted_command);
		exit (1);
	}
	return (paths);
}

static char	**parse_command(char *command)
{
	char	**splitted_command;

	splitted_command = ft_split(command, ' ');
	if (splitted_command == NULL)
		exit (1);
	if (splitted_command[0] == NULL)
	{
		free(splitted_command);
		write(2, command, ft_strlen(command));
		write(2, ": command not found\n", 20);
		exit (127);
	}
	return (splitted_command);
}

void	resolve_and_execute(t_struct pipex, char *command)
{
	char	**splitted_command;
	char	**paths;

	while (pipex.environment[pipex.path_index]
		&& ft_strncmp(pipex.environment[pipex.path_index], "PATH=", 5) != 0)
		pipex.path_index++;
	if (!pipex.environment[pipex.path_index])
	{
		write(2, command, ft_strlen(command));
		write(2, ": command not found\n", 20);
		exit(127);
	}
	splitted_command = parse_command(command);
	paths = split_path(pipex, splitted_command);
	attempt_exec_in_paths(pipex, splitted_command, paths);
	free(paths);
	free_splitted_command_and_path(0, NULL, splitted_command);
	write(2, command, ft_strlen(command));
	write(2, ": command not found\n", 20);
	exit(127);
}
