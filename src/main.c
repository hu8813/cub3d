#include "../inc/cub3D.h"

void	ft_error(char *errorcode, t_main *main)
{
	errno = 2;
	while (*errorcode)
		write(2, errorcode++, 1);
	write(2, "\n", 1);
	if (main)
		ft_destroy(main);
	exit(1);
}

t_main	*main_init(char *path)
{
	t_main	*main;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		ft_error("Error\nUsage: ./cub3D maps/map.cub\n cannot open map file\n", NULL);
	main = ft_calloc(1, sizeof(t_main));
	if (!main)
		ft_error("Error\nMalloc failed", NULL);
	main->map = ft_calloc(1, sizeof(t_map));
	if (!main->map)
		ft_error("Error\nMalloc failed", main);
	main->img = ft_calloc(1, sizeof(t_img));
	if (!main->img)
		ft_error("Error\nMalloc failed", main);
	main->map->map = map_init(fd, main);
	
	//main->mlx = mlx_init();
	//if (main->mlx == NULL)
	//	ft_error("Error\nMlx initialization failed", main);
	//xpm_to_img(main);
	//main->win = mlx_new_window(main->mlx,
	//		main->map->x * PIXEL, main->map->y * PIXEL, "so_long");
	return (main);
}

int	main(int argc, char **argv)
{
t_main		*main;

	if (argc != 2 || access(argv[1], F_OK | R_OK) == -1
		|| !ft_strncmp(argv[1] + ft_strlen(argv[1]) - 5, ".cub", 4))
	{
		errno = 2;
		ft_error("Error\nUsage: ./cub3D maps/map.cub\n wrong map (.cub) file", NULL);
		exit(1);
	}
	main = main_init(argv[1]);

	ft_map_check(main);
	//check_files(main, argv[1]);
}