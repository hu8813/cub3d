#include "../inc/cub3D.h"

static void	map_split2(t_main *main, int height, int width, char *buffer)
{
	int	y;
	int	x;

	y = 0;
	while (y < height)
	{
		x = 0;
		main->map->map[y] = ft_calloc((width + 1), sizeof(char));
		while (x < width)
		{
			if (buffer[(y * (width + 1) + x)] == 'E')
				main->exitcount++;
			else if (buffer[y * (width + 1) + x] == 'P')
			{
				main->playercount++;
				main->p_x = x;
				main->p_y = y;
			}
			else if (buffer[(y * (width + 1) + x)] == 'C')
				main->coincount++;
			main->map->map[y][x] = buffer[(y * (width + 1) + x)];
			x++;
		}
		main->map->map[y++][x] = '\0';
	}
}

static void	map_split(char *buffer, t_main *main)
{
	int	height;
	int	width;
	int	i;


	main->exitcount = 0;
	main->playercount = 0;
	main->coincount = 0;
	height = 0;
	i = 0;
	while (buffer[i] != 0)
		if (buffer[i++] == '\n')
			height++;
	if (buffer[i - 1] != '\n')
		height++;
	i = 0;
	while (buffer[i] != '\n' && buffer[i] && buffer[i] != EOF)
		i++;
	width = i;
	main->map->map = ft_calloc((height + 1), sizeof(char *));
	map_split2(main, height, width, buffer);
	main->map->x = width;
	main->map->y = height;
}

char	*get_next_line(int fd)
{
	char	*string;
	char	*copy;
	char	*new;
	int		i;

	string = (char *)calloc(1, 10000);
	copy = string;
	i = 0;
	while (i < 10000 && read(fd, copy, 1) > 0 && *copy++ != '\n')
		i++;
	if (copy > string)
	{
		*copy = 0;
		new = (char *)malloc(sizeof * new * (ft_strlen(string) + 1));
		i = -1;
		while (string[++i])
			new[i] = string[i];
		new[i] = 0;
		free(string);
		return (new);
	}
	else
		return (free(string), NULL);
}

char	**map_init(char *path, t_main *main)
{
	char *buffer;
	int i;
	int bytes;
	int fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		ft_error("Error\nMap file not found", main);
	buffer = get_next_line(fd);
	while (!buffer)
		buffer = get_next_line(fd);
	i = 0;
	bytes = 1;
	buffer[0] = '\0';
	while (bytes)
	{
		bytes = read(fd, &buffer[i++], 1);
		if (bytes == -1)
			ft_error("Error\nRead failed\n", main);
	}
	buffer[i] = '\0';
	map_split(buffer, main);
	//free(buffer);
	close(fd);
	return (main->map->map);
}