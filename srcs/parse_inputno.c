/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input_ori.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 22:44:42 by maheraul          #+#    #+#             */
/*   Updated: 2023/06/29 01:31:26 by maheraul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//int	find_sep(void)

int	len_total(char *input, int len)
{
	int	i;
	int	j;
	int	n;
	int	d;

	i = 0;
	j = 0;
	n = 0;
	d = 1;
	while (input[i])
	{
		if (input[i] == '|' || input[i] == '<' || input[i] == '>')
		{
			if ((input[i] != '|' && input[i + 1] && input[i] == '>' && input[i
					+ 1] == '>') ||
				(input[i] != '|' && input[i + 1] && input[i] == '<' && input[i
						+ 1] == '<'))
				d = 2;
			if (i > 0)
				j++;
			n = 1;
		}
		while (d > 0)
		{
			d--;
			j++;
			i++;
		}
		if (n == 1 && i != len)
			j++;
		n = 0;
		d = 1;
	}
	return (j);
}

void	*parse_input(char *input)
{
	int		i;
	int		j;
	int		n;
	int		d;
	int		len;
	int		lentotal;
	char	*new;

	i = 0;
	j = 0;
	n = 0;
	d = 1;
	len = ft_strlen(input);
	lentotal = len_total(input, len);
	new = malloc(sizeof(char) * lentotal + 1);
	while (input[i])
	{
		if (input[i] == '|' || input[i] == '<' || input[i] == '>')
		{
			if ((input[i] != '|' && input[i + 1] && input[i] == '>' && input[i
					+ 1] == '>') ||
				(input[i] != '|' && input[i + 1] && input[i] == '<' && input[i
						+ 1] == '<'))
				d = 2;
			if (i > 0)
				new[j++] = ' ';
			n = 1;
		}
		while (d > 0)
		{
			d--;
			new[j++] = input[i++];
		}
		if (n == 1 && i != len)
			new[j++] = ' ';
		n = 0;
		d = 1;
	}
	new[j] = '\0';
	return (new);
}

//<SADsad>DSadSD|SD>>SDA?SDSADS?DASD
//< SADsad > DSadSD | SD >> SDA?SDSADS << ?DASD

// des la fin