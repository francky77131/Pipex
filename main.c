/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frgojard <frgojard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:07:00 by frgojard          #+#    #+#             */
/*   Updated: 2022/11/08 12:03:07 by frgojard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <sys/types.h>
#include <sys/wait.h>

int	main(int argc, char **argv)
{
	(void)argv;
	(void)argc;
	int id;
	int n;
	n = 1;
	id = fork();
	wait(NULL);
	if (id != 0)
	{
		n = 6;
		while(n <= 10)
		{
			printf("main %d ", n);
			n++;
		}	
	}
	if (id == 0)
	{
		n = 1;
		while(n <= 5)
		{
			printf("child %d ", n);
			n++;
		}	
	}
	if (id != 0)
		printf("\n");
	return (0);
}