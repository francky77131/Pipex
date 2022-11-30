/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frgojard <frgojard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:07:00 by frgojard          #+#    #+#             */
/*   Updated: 2022/11/30 13:03:24 by frgojard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <sys/types.h>
#include <sys/wait.h>

char	*ft_path_env(char **env, char *path)
{
	int	i;
	int	j;
	int y;
	int find;
	
	i = 0;
	j = 0;
	y = 0;
	find = 0;
	while(find != 4)
	{
		if (env[i][j] == path[y])
		{
			j++;
			y++;
			find++;	
		}
		else
		{
			i++;
			j = 0;
			y = 0;
			find = 0;
		}
	}
	return (env[i]);
}

void ft_search_replace()

int	main(int argc, char **argv, char *env[])
{
	(void)argv;
	(void)argc;
	// int fd[2];
	// int pid1;
	// int pid2;
	// int file1;
	// int file2;
	// char cmdcat[] = {"/usr/bin/ls"};
	// char cmdgrep[] = {"/usr/bin/rev"};
	char *path;
	char **splitpath;

	path = ft_path_env(env, "PATH");
	path = ft_substr(path, 5, ft_strlen(path));
	path = ft_strjoin(path, "/");











	
	splitpath = ft_split(path, ':');
	ft_search_replace(splitpath, ':');
	int i = -1;
	while (splitpath[++i])
		printf("%s\n", splitpath[i]);

	









	
	// if (pipe(fd) == -1)
	// 	return (2);
	// pid1 = fork();
	// if (pid1 == -1)
	// 	return (2);
	// file1 = open("infile.txt", O_RDONLY);
	// file2 = open("outfile.txt", O_WRONLY);
	// if (file1 < 0 || file2 < 0)
	// 	return (2);
	// if (pid1 == 0)
	// {
	// 	close(fd[0]);
	// 	close(file2);
	// 	if (dup2(fd[1], STDOUT_FILENO) < 0)
	// 		return (2);
	// 	if (dup2(file1, STDIN_FILENO) < 0)
	// 		return (2);
	// 	close(file1);
	// 	close(fd[1]);
	// 	execve(cmdcat, argv, env);
	// }
	// pid2 = fork();
	// if (pid2 == -1)
	// 	return (2);
	// if (pid2 == 0)
	// {
	// 	close(fd[1]);
	// 	close(file1);
	// 	if (dup2(fd[0], STDIN_FILENO) < 0)
	// 		return (2);
	// 	if (dup2(file2, STDOUT_FILENO) < 0)
	// 		return (2);
	// 	close(file2);
	// 	close(fd[0]);
	// 	execve(cmdgrep, argv, env);
	// }
	// close(fd[0]);
	// close(fd[1]);
	// close(file1);
	// close(file2);
	// waitpid(pid1, NULL, 0);
	// waitpid(pid2, NULL, 0);
	return (0);
}