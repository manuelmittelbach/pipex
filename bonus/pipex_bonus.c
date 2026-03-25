/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelmittelbach <manuelmittelbach@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 12:45:46 by mmittelb          #+#    #+#             */
/*   Updated: 2026/03/25 13:04:52 by manuelmitte      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_struct	pipex;

	if (argc <= 4)
	{
		write(2, "invalid amount of arguments\n", 28);
		exit (1);
	}
	pipex.path_index = 0;
	pipex.environment = envp;
	pipex.amount_of_pipes = argc - 4;
	pipex.amount_of_forks = argc - 3;
	pipex.child_pids = malloc(sizeof(pid_t) * pipex.amount_of_forks);
	if (!pipex.child_pids)
		exit(1);
	pipex.argc = argc;
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
		ft_here_doc(pipex, argv);
	else
		multiple_pipes(pipex, argv);
	return (0);
}
