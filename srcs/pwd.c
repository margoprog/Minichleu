/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 02:02:35 by maheraul          #+#    #+#             */
/*   Updated: 2023/06/28 22:47:42 by maheraul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#define BUFFER_SIZE 300

int	ft_pwd(char **arg, char **env)
{
	char cwd[BUFFER_SIZE];
	if ( getcwd( cwd, BUFFER_SIZE ) != NULL)
		printf("%s", cwd);
	else
	{
		perror("bash");
		return(1);
	}
	return(0);
}

int main(int ac, char **av, char **env)
{
	ft_pwd(av, env);
}