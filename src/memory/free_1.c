#include "../../include/cub3d.h"

//funcion para liberar bidimensionales
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
