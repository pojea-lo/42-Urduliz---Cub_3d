/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_1.c                                           :+:      :+:    :+:   */
/*   By: jsmith <marvin@42.fr>                        +:+ +:+         +:+     */
/*   By: pojea-lo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 07:48:49 by pojea-lo          #+#    #+#             */
/*   Updated: 2022/10/04 11:17:11 by pojea-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	ft_free_breakmap(t_in *dt, int j, char *line)
{
	int	i;

	free (line);
	i = -1;
	dt->info[++j] = NULL;
	while (dt->info[++i])
		free (dt->info[i]);
	free (dt->info);
}

void	ft_free_bidim(char **str)
{
	int	j;

	j = -1;
	while (str[++j])
	{
		if (str[j])
			free(str[j]);
	}
	free (str);
}
