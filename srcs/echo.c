/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 00:36:11 by maheraul          #+#    #+#             */
/*   Updated: 2023/06/28 21:14:19 by maheraul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "minishell.h"
#include <stdio.h>
#include <unistd.h>

int	ft_check_n(char *str)
{
	int	i;

	i = 0;
	if (str[i] && str[i+1] && str[i] == '-')
	{
		i++;
		while (str[i] && str[i] == 'n')
			i++;
		if (str[i] && str[i] != 'n')
			return (1);
		return (0);
	}
	return (1);
}

void	*ft_echo(char **arg, char **env)
{
	int	i;
	int	n;

	(void)env;
	i = 2;
	n = 0;
	if(arg[i])
	{	while (!ft_check_n(arg[i]))
		{
			i++;
			n++;
		}
		while (arg[i])
		{
			printf("%s", arg[i]);
			if (arg[i + 1])
				printf(" ");
			i++;
		}
	}
	if (n == 0)
		printf("\n");
}

int main(int ac, char **av, char **env)
{
	// chdir("moha");
	// static char *tab[5] = {"-n", "hello", NULL};
	 ft_echo(av, env);
}
