/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 17:54:44 by motroian          #+#    #+#             */
/*   Updated: 2023/08/29 22:17:22 by maheraul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_ok(char *str, t_data *env, int *clef)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	if (str[0] && ft_isdigit(str[0]))
		return (*clef += 1, NULL);
	if (str[0] && alphanum(str[0]) && str[0] != '?')
		return (ft_strdup("$"));
	if (str[0] == '?')
		return (*clef += 1, ft_itoa(env->status));
	while (str && str[i] && !alphanum(str[i]))
		i++;
	*clef += i;
	while (env->env_copy[y])
	{
		if (!ft_strncmp(str, env->env_copy[y], i) && env->env_copy[y][i] == '=')
			return (ft_strdup(&env->env_copy[y][i + 1]));
		y++;
	}
	return (NULL);
}

int	is_heredoc(char *str, char *new, int *i, int *n)
{
	int	x;

	x = *i;
	if (str[x] && str[x + 1] && str[x] == '<' && str[x + 1] == '<')
	{
		new[(*n)++] = str[(*i)++];
		new[(*n)++] = str[(*i)++];
		while (str[(*i)] && str[(*i)] == ' ')
			new[(*n)++] = str[(*i)++];
		while (str[(*i)] && str[(*i)] != ' ')
			new[(*n)++] = str[(*i)++];
		return (1);
	}
	return (0);
}

int	copy_squote(char *str, char *new, int *i, int *n)
{
	if (str[(*i)] == 39)
	{
		new[(*n)++] = str[(*i)++];
		while (str[(*i)] && str[(*i)] != 39)
			new[(*n)++] = str[(*i)++];
		new[(*n)++] = str[(*i)++];
		return (1);
	}
	return (0);
}

char	*ft_expandd(char *str, t_data *env)
{
	int		i;
	char	*new;
	char	*value;
	int		n;

	new = ft_calloc(count_expand(str, env) + 1, 1);
	if (!new)
		return (NULL);
	i = 0;
	n = 0;
	while (str && str[i])
	{
		if (copy_squote(str, new, &i, &n) || is_heredoc(str, new, &i, &n))
			;
		else if (str[i] == '$' && str[i + 1])
		{
			i++;
			value = expand_ok(&str[i], env, &i);
			if (value)
			{
				ft_strcat(&new[n], mgamiloueee(value), &n);
				free(value);
			}
		}
		else
			new[n++] = str[i++];
	}
	free(str);
	return (new);
}
