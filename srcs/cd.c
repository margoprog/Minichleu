/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 02:56:31 by maheraul          #+#    #+#             */
/*   Updated: 2023/06/28 22:25:19 by maheraul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

#define BUFFER_SIZE 300

int	ft_pwd(char **arg, char **env)
{
	char cwd[BUFFER_SIZE];
	if (getcwd( cwd, BUFFER_SIZE ) != NULL)
		printf("%s", cwd);
	else
	{
		perror("bash");
		return(1);
	}
	return(0);
}

int	ft_cd(char **arg, char **env)
{
	//if(arg[])
	//printf("\n%s\n", arg[2]);
	if(arg[2] && arg[3])
	{
		printf("bash: cd: too many arguments");
		return(1);
	}
	else if(arg[2] && chdir(arg[2]) < 0)
	{
		printf("bash: cd: %s: No such file or directory", arg[2]);
		return(1);
	}
	return(0);
}

int main(int ac, char **av, char **env)
{
	printf("AVANT ");
	ft_pwd(av, env);
	printf("\n");
	ft_cd(av, env);
	printf("\n");
	printf("APRES ");
	ft_pwd(av, env);
	printf("\n");
}