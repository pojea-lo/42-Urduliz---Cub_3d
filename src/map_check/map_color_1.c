/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_color_1.c                                      :+:      :+:    :+:   */
/*   By: jsmith <marvin@42.fr>                        +:+ +:+         +:+     */
/*   By: pojea-lo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 07:33:03 by pojea-lo          #+#    #+#             */
/*   Updated: 2022/09/30 07:37:50 by pojea-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	ft_dup_atoi(t_in *dt, char *line, int n)
{
	char	**num;
	int		i;
	int		j;

	num = (char **)malloc(sizeof(char *) * 5);
	if (!num || !line)
		return (-1);
	j = -1;
	i = 0;
	while (++j < 4 && line[i])
	{
		i = ft_restore_i(line, j);
		if (i == -1)
			break ;
		num[j] = ft_line (line, num, i, j);
		if (!num[j])
			return (-1);
	}
	num[j] = NULL;
	if (j != 3)
		return (ft_free_bidim(num), -1);
	if (ft_atoi_bid(dt, num, n) == -1)
		return (-1);
	return (0);
}

int	ft_restore_i(char *line, int j)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	i++;
	while (line[i] && line[i] == ' ')
		i++;
	if (!(line[i] > 47) && !(line[i] < 58))
		return (-1);
	line = ft_trim(line, i);
	if (!line)
		return (-1);
	while (--j >= 0)
	{
		while (line[i] && line[i] != ',')
			i++;
		if (!line[i])
			return (-1);
		i++;
	}
	return (i);
}

char	*ft_trim(char *line, int i)
{
	int	j;

	j = 0;
	while (line[i])
	{
		if (line[i] == ' ')
		{
			j = ft_trim_aux(line, i);
			if (j == -1)
				return (NULL);
			j = i - 1;
			while (line[++j])
				line[j] = line[j + 1];
		}
		if (line[i] && line[i] != ' ')
			i++;
	}
	return (line);
}

int	ft_trim_aux(char *line, int i)
{
	int	j;

	j = i;
	if (line[i - 1] > 47 && line[i - 1] < 58)
	{
		while (line[j] == ' ')
			j++;
		if (line[j] > 47 && line[j] < 58)
			return (-1);
	}
	else if (line[i - 1] == ',')
	{
		while (line[j] == ' ')
			j++;
		if (line[j] == ',')
			return (-1);
	}
	return (j);
}

char	*ft_line(char *line, char **num, int i, int j)
{
	int	k;

	if (!line)
		return (NULL);
	num[j] = (char *)malloc(sizeof(char) * 100);
	if (!num[j])
		return (NULL);
	k = -1;
	while (line[i] && (line[i] > 47 && line[i] < 58))
	{
		num[j][++k] = line[i];
		i++;
	}
	if (k == -1)
		return (NULL);
	num[j][++k] = 00;
	return (num[j]);
}
