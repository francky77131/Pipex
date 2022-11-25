/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frgojard <frgojard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:07:00 by frgojard          #+#    #+#             */
/*   Updated: 2022/11/25 14:10:58 by frgojard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <sys/types.h>
#include <sys/wait.h>

int	main(int argc, char **argv, char *env[])
{
	(void)argv;
	(void)argc;
	int fd[2];
	int pid1;
	int pid2;
	int file1;
	int file2;
	int err;
	int infile;
	int outfile;
	char cmdcat[] = {"/usr/bin/cat"};
	char cmdgrep[] = {"/usr/bin/rev"};
	if (pipe(fd) == -1)
		return (2);
	pid1 = fork();
	if (pid1 == -1)
		return (2);
	file1 = open("infile.txt", O_RDONLY);
	file2 = open("outfile.txt", O_WRONLY);
	if (pid1 == 0)
	{
		close(fd[0]);
		close(file2);
		dup2(fd[1], STDOUT_FILENO);
		dup2(file1, STDIN_FILENO);
		close(file1);
		close(fd[1]);
		execve(cmdcat, argv, env);
	}
	pid2 = fork();
	if (pid2 == -1)
		return (2);
	if (pid2 == 0)
	{
		close(fd[1]);
		close(file1);
		dup2(fd[0], STDIN_FILENO);
		dup2(file2, STDOUT_FILENO);
		close(file2);
		close(fd[0]);
		execve(cmdgrep, argv, env);
	}
	close(fd[0]);
	close(fd[1]);
	close(file1);
	close(file2);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}