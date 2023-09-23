#include "../inc/cub3D.h"

int	ft_destroy(t_main *main)
{
	if (main)
        free(main);
	exit(0);
	return (0);
}