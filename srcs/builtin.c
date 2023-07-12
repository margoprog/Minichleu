/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 23:24:23 by maheraul          #+#    #+#             */
/*   Updated: 2023/07/13 00:12:20 by maheraul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_is_builtin(t_cmd *cmd, char **env)
{
	int i;
	static const char *str[4] = {"pwd", "cd", "echo", NULL};
	static const t_builtin func[3] = {ft_pwd, ft_cd, ft_echo};

	i = 0;
	if (!cmd)
		return (0);

	while (str[i])
	{
		if (!ft_strncmp(cmd->cmd, str[i], ft_strlen(cmd->cmd)))
		{
			printf("cmd = %s | builtin %s\n", cmd->cmd, str[i]);
			func[i](cmd->arg, env);
			printf("mon %s\n", str[i]);
			return (1);
		}
		i++;
	}
	return (0);
}