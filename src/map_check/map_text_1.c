/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_text_1.c                                       :+:      :+:    :+:   */
/*   By: jsmith <marvi@42.fr>                         +:+ +:+         +:+     */
/*   By: pojea-lo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 07:43:29 by pojea-lo          #+#    #+#             */
/*   Updated: 2022/09/30 07:44:54 by pojea-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

char	*ft_regen_tex(char *old)
{
	char	*new;
	int		i;

	if (!old)
		return (NULL);
	i = 0;
	while (old[i] && (old[i] == 'N' || old[i] == 'S' || old[i] == 'E'
			|| old[i] == 'W' || old[i] == 'O' || old[i] == 'A' || old[i]
			== ' ' || old[i] == '.' || old[i] == '/'))
		i++;
	new = (char *)malloc(sizeof(char) * (ft_strlen(old) - i + 1));
	if (!new)
		return (NULL);
	new = ft_regen_tex_aux(old, new, i);
	if (!new)
		return (free (old), NULL);
	free(old);
	return (new);
}

char	*ft_regen_tex_aux(char *old, char *new, int i)
{
	int	j;

	j = 0;
	while (old[i])
	{
		if (old[i] != ' ')
			new[j] = old[i];
		else
		{
			while (old[i] && old[i] == ' ')
				i++;
			if (old[i] != 00)
				return (free (new), NULL);
		}
		if (old[i])
		{
			i++;
			j++;
		}
	}
	if (j == 0)
		return (free (new), NULL);
	new[j] = 00;
	return (new);
}

int	ft_ch_extension(char *new)
{
	int	i;

	i = ft_strlen(new);
	while (new[i] != '.' && i >= 0)
		i--;
	if (new[++i] == 'x')
	{
		if (new[++i] != 00 && new[i] == 'p')
		{
			if (new[++i] != 00 && new[i] == 'm')
			{
				if (new[++i] == 00)
					return (0);
			}
		}
	}
	return (-1);
}

t_mlx	ft_charge_tex(t_hook *hk, int i)
{
	t_mlx	img;

	img.img = mlx_xpm_file_to_image(hk->gr->mlx, hk->dt->tex[i], &img.w,
			&img.h);
	img.line_length = 0;
	img.bits_per_pixel = 0;
	img.endian = 0;
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	return (img);
}
