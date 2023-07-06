/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 23:24:23 by maheraul          #+#    #+#             */
/*   Updated: 2023/07/06 03:31:42 by maheraul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	truc(int r)
{
	fprintf(stderr, "%d\n", r);
}

// int	ft_pwd(char **arg, char **env)

typedef int	(*t_builtin)(char **arg, char **env);

int	ft_is_builtin(t_cmd *cmd, char **env)
{
	int i;
	static const char *str[4] = {"pwd", "cd", "echo", NULL};
	static const t_builtin func[3] = {ft_pwd, ft_cd, ft_echo};

	i = 0;
	if (!cmd)
		return (0);

	while(str[i])
	{
		if (!ft_strncmp(cmd->cmd, str[i], ft_strlen(cmd->cmd)))
		{
			printf("mon %s\n", str[i]);
			func[i](cmd->arg, env);
			printf("mon %s\n", str[i]);
			return (1);
		}
		i++;
	}
	return (0);
}