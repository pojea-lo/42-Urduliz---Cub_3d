#include "../cub3d.h"

int	ft_atoi(char *str)
{
	int	i;
	int	r;

	r = 0;
	i = 0;
	while (str[i])
		i++;
	if (i > 3)
		return (-1);
	i = -1;
	while (str[++i])
		r = (str[i] - '0') + (r * 10);
	if (r > 255)
		return (-1);
	return (r);
}
