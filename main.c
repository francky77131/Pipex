/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frgojard <frgojard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:07:00 by frgojard          #+#    #+#             */
/*   Updated: 2022/12/05 15:33:17 by frgojard         ###   ########.fr       */
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

void ft_search_replace(char	**path, char c)
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




char	*path(char **env, char *cmd)
{
	char *path;
	char **splitpath;
	char	*paths;
	int i;

	i = 0;
	path = ft_path_env(env, "PATH");
	path = ft_substr(path, 5, ft_strlen(path));
	path = ft_strjoin(path, "/");
	splitpath = ft_split(path, ':');
	ft_search_replace(splitpath, ':');
	while (splitpath[i])
	{
		paths = ft_strjoin(splitpath[i], cmd);
		if (!access(paths, F_OK | X_OK))
		{
			//free(path);
			//free_split(splitpath);
			return (paths);
		}
		//free(path);
		i++;
	}
	//free_split(splitpath);
	return (0);
}

void	child_one(char **argv, int *fd, int *file, char **env)
{
	char **cmd;

	cmd = ft_split(argv[2], ' ');
	close(fd[0]);
	close(file[1]);
	if (dup2(fd[1], STDOUT_FILENO) < 0)
		return (perror("dup2 1"));
	if (dup2(file[0], STDIN_FILENO) < 0)
		return (perror("dup2 2"));
	close(fd[1]);
	close(file[0]);
	execve(path(env, cmd[0]), cmd, env);
}

void	child_two(char **argv, int *fd, int *file, char **env)
{
	char **cmd;

	cmd = ft_split(argv[3], ' ');
	close(fd[1]);
	close(file[0]);
	if (dup2(fd[0], STDIN_FILENO) < 0)
		return (perror("dup2 3"));
	if (dup2(file[1], STDOUT_FILENO) < 0)
		return (perror("dup2 4"));
	close(fd[0]);
	close(file[1]);
	execve(path(env, cmd[0]), cmd, env);
}

int	main(int argc, char **argv, char *env[])
{
	int fd[2];
	int file[2];
	int pid;
	int pid2;
	
	if (argc != 5)
		return (1);
	if (pipe(fd) < 0)
		return (perror("pipe"), 1);
	file[0] = open(argv[1], O_RDONLY);
	if (file[0] < 0)
		return (perror("file1"), 1);
	file[1] = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 00644);
	if (file[1] < 0)
		return (perror("file2"), 1);
	pid = fork();
	if (pid == 0)
		child_one(argv, fd, file, env);
	pid2 = fork();
	if (pid2 == 0)
		child_two(argv, fd, file, env);
	close(fd[0]);
	close(fd[1]);
	close(file[0]);
	close(file[1]);
	waitpid(pid, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}