/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*   By: jsmith <marvin.fr>                           +:+ +:+         +:+     */
/*   By: pojea-lo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 07:46:30 by pojea-lo          #+#    #+#             */
/*   Updated: 2022/09/30 07:46:53 by pojea-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	ft_ch(int i, int j, t_in *dt, int n)
{
	if (dt->map[i][j])
	{
		if (n == 0)
		{
			if (dt->map[i][j] != '1' && dt->map[i][j] != ' ')
				return (-1);
		}
		if (n == 1)
		{
			if (dt->map[i][j] != '1' && dt->map[i][j] != '0')
				return (-1);
		}
	}
	return (0);
}

char	**ft_add_columns(t_in *dt)
{
	char	**aux;
	int		i;
	int		j;

	aux = (char **) malloc (sizeof(char *) * (dt->maxy + 1));
	if (!aux)
		return (NULL);
	i = 0;
	while (dt->map[i])
	{
		aux[i] = (char *) malloc (sizeof(char) * (dt->maxx + 1));
		j = -1;
		while (dt->map[i][++j])
			aux[i][j] = dt->map[i][j];
		while (j < dt->maxx)
			aux[i][j++] = ' ';
		aux[i][j] = 00;
		free (dt->map[i++]);
	}
	aux[i] = NULL;
	free (dt->map);
	return (aux);
}
