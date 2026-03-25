/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelmittelbach <manuelmittelbach@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 17:47:41 by mmittelb          #+#    #+#             */
/*   Updated: 2026/03/24 18:58:30 by manuelmitte      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_splitted_command_and_path(int path_index, char **paths, char **splitted_command)
{
	int	i;

	while (paths != NULL && paths[path_index] != NULL)
	{
		free (paths[path_index]);
		path_index++;
	}
	if (paths != NULL)
		free(paths);
	i = 0;
	while (splitted_command[i])
	{
		free(splitted_command[i]);
		i++;
	}
	free(splitted_command);
}

void	free_rest_of_path(char **paths, int i)
{
	while (paths[++i])
		free(paths[i]);
	free(paths);
}
