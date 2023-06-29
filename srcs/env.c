/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 03:12:53 by maheraul          #+#    #+#             */
/*   Updated: 2023/06/28 22:47:49 by maheraul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int	ft_env(int ac, char **arg, char **env)
{
	int i;
	i = 0;
	while(env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	return(0);
}

int main(int ac, char **av, char **env)
{
	ft_env(ac ,av, env);
}