/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*   By: jsmith <marvin@42.fr>                        +:+ +:+         +:+     */
/*   By: pojea-lo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 06:48:33 by pojea-lo          #+#    #+#             */
/*   Updated: 2022/09/30 07:00:28 by pojea-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int argc, char *argv[])
{
	int		fd;
	t_in	dt;

	if (argc != 2)
	{
		printf("Error\nError in arguments\n");
		return (0);
	}
	if (ft_ch_arg(argv[1]) == -1)
	{
		printf("Error\nBad extension in file\n");
		return (0);
	}
	fd = open(argv[1], O_RDWR);
	if (fd == -1)
	{
		printf("Error\nMap does't exist\n");
		close (fd);
		return (0);
	}
	ft_traspas(fd, argv[1], &dt);
	ft_free(&dt);
	return (0);
}

int	ft_ch_arg(char *argv)
{
	int	i;

	i = 0;
	while (argv[i] && argv[i] != '.')
		i++;
	i++;
	if (argv[i] != 'c')
		return (-1);
	if (argv[i])
		i++;
	if (argv[i] != 'u')
		return (-1);
	if (argv[i])
		i++;
	if (argv[i] != 'b')
		return (-1);
	if (argv[i])
		i++;
	if (argv[i] != 00)
		return (-1);
	return (0);
}

int	ft_traspas(int fd, char *argv, t_in *dt)
{
	t_hook	*hk;

	hk = ft_memset(dt);
	dt->info = ft_get_info(fd, argv, dt);
	if (!dt->info)
		return (printf ("Error\nEmpty map\n"), ft_free_structur (hk), -1);
	if (ft_create_text(hk) == -1)
	{
		printf ("Texture error\n");
		return (ft_free_structur (hk), -1);
	}
	if (ft_create_bid(dt) == -1)
		return (ft_free_structur (hk), -1);
	if (ft_ch_map(dt) == -1)
	{
		printf ("Map error\n");
		return (ft_free_structur (hk), -1);
	}
	if (ft_draw_map (hk) == -1)
	{
		printf ("Draw map error\n");
		return (-1);
	}
	ft_free_structur (hk);
	return (0);
}
