/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frgojard <frgojard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:07:00 by frgojard          #+#    #+#             */
/*   Updated: 2022/12/07 17:35:36 by frgojard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <sys/types.h>
#include <sys/wait.h>

void	free_split(char **args)
{
	int	size;
	int	i;

	i = 0;
	size = 0;
	while (args[size])
		size++;
	while (i < size)
		free(args[i++]);
	free(args);
}

void	ft_search_replace(char	**path, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (path[i])
	{
		j = 0;
		while (path[i][j])
		{
			if (path[i][j] == c)
				path[i][j] = '/';
			j++;
		}
		i++;
	}
}

void	cmd_not_found(char **cmd, char *msg)
{
	write(2, cmd[0], ft_strlen(cmd[0]));
	write(2, msg, ft_strlen(msg));
	free_split(cmd);
	exit(EXIT_FAILURE);
}

char	*paths(char **env, char **cmd)
{
	char	*path;
	char	**splitpath;
	char	*paths;
	char	*tmp;
	int		i;

	i = 0;
	if (cmd[0] == NULL)
		exit(EXIT_FAILURE);
	if (!access(cmd[0], F_OK | X_OK))
		return (cmd[0]);
	while (env[i])
	{
		path = ft_strnstr(env[i], "PATH", 4);
		if (path != NULL)
			break ;
		i++;
	}
	if (path == NULL)
		cmd_not_found(cmd, ": No such file or directory \n");
	path = ft_substr(path, 5, ft_strlen(path));
	splitpath = ft_split(path, ':');
	tmp = ft_strjoin("/", cmd[0]);
	i = 0;
	while (splitpath[i])
	{
		paths = ft_strjoin(splitpath[i], tmp);
		if (!access(paths, F_OK | X_OK))
		{
			free(path);
			free_split(splitpath);
			free(tmp);
			return (paths);
		}
		free(paths);
		i++;
	}
	free_split(splitpath);
	free(path);
	free(tmp);
	cmd_not_found(cmd, ": command not found\n");
	return (0);
}

void	child_one(char **argv, int *fd, int *file, char **env)
{
	char	**cmd;

	cmd = ft_split(argv[2], ' ');
	if (cmd == NULL)
		exit(EXIT_FAILURE);
	close(fd[0]);
	if (file[1] >= 0)
		close(file[1]);
	if (file[0] >= 0)
	{
		if (dup2(fd[1], STDOUT_FILENO) < 0)
			return (perror("dup2 1"));
		if (dup2(file[0], STDIN_FILENO) < 0)
			return (perror("dup2 2"));
	}
	else
	{
		close(fd[1]);
		free_split(cmd);
		exit(EXIT_FAILURE);
	}
	close(fd[1]);
	close(file[0]);
	execve(paths(env, cmd), cmd, env);
}

void	child_two(char **argv, int *fd, int *file, char **env)
{
	char	**cmd;

	cmd = ft_split(argv[3], ' ');
	if (cmd == NULL)
		exit(EXIT_FAILURE);
	close(fd[1]);
	if (file[0] >= 0)
		close(file[0]);
	if (file[1] >= 0)
	{
		if (dup2(fd[0], STDIN_FILENO) < 0)
			return (perror("dup2 3"));
		if (dup2(file[1], STDOUT_FILENO) < 0)
			return (perror("dup2 4"));
	}
	else
	{
		close(fd[0]);
		free_split(cmd);
		exit(EXIT_FAILURE);
	}
	close(file[1]);
	close(fd[0]);
	execve(paths(env, cmd), cmd, env);
}

int	main(int argc, char **argv, char *env[])
{
	int	fd[2];
	int	file[2];
	int	pid;
	int	pid2;

	if (argc != 5)
		return (1);
	if (pipe(fd) < 0)
		return (perror("pipe"), 1);
	file[0] = open(argv[1], O_RDONLY);
	if (file[0] < 0)
		perror("infile");
	file[1] = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 00644);
	if (file[1] < 0)
		perror("outfile");
	pid = fork();
	if (pid < 0)
		return (perror("fork1"), 1);
	if (pid == 0)
		child_one(argv, fd, file, env);
	pid2 = fork();
	if (pid2 < 0)
		return (perror("fork2"), 1);
	if (pid2 == 0)
		child_two(argv, fd, file, env);
	close(fd[0]);
	close(fd[1]);
	if (file[0] >= 0)
		close(file[0]);
	if (file[1] >= 0)
		close(file[1]);
	waitpid(pid, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
