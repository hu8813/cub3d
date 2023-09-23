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

static int pre_check(char *buffer)
{
	if (!ft_strnstr(buffer, "NO ", ft_strlen(buffer)) || !ft_strnstr(buffer, "SO ", ft_strlen(buffer))
		|| !ft_strnstr(buffer, "WE ", ft_strlen(buffer)) || !ft_strnstr(buffer, "EA ", ft_strlen(buffer))	
		|| !ft_strnstr(buffer, "C ", ft_strlen(buffer)) || !ft_strnstr(buffer, "F ", ft_strlen(buffer)))
		return (0);
	return (1);
}

static void get_color(char *buffer, int rgb[3], int *k)
{
    int i = 0;
    int j = 0;
    int component = 0;
	int pos = ft_strchr_idx(&buffer[i], '\n');

	k += pos;
	if (pos == -1 || pos == 0 || buffer[i] == '\n')
		return ;	
    char *tmp = malloc(pos + 1);
    if (tmp == NULL) {
       ft_error("Error\nMalloc failed", NULL);
    }

    while (buffer[i]) {
        if (buffer[i] == ',' || buffer[i] == '\n') {
            tmp[j] = '\0';
            rgb[component] = atoi(tmp);
			memset(tmp, 0, 10);
            j = 0;
            component++;

            if (component == 3) {
                free(tmp);
                return ;
            }
        } else if (buffer[i] != ' ' && buffer[i] != '\t') {
            tmp[j] = buffer[i];
            j++;
        }

        i++;
    }
    free(tmp);
	(void)pos;
	(void)k;
}

static char	*get_texture(char *buffer, t_main *main, int *pos)
{
	int		i;
	int		k;
	char	*tmp;

	i = 0;
	k = ft_strchr_idx(&buffer[i], '\n');
	while (buffer[i] && i < k && buffer[i] != '\n'  && (buffer[i] == ' ' || buffer[i] == '\t'))
		i++;
	pos+= k;
	if (k == -1 || k == 0 || buffer[i] == '\n')
		return (NULL);
	k--;
	while (buffer[k] && buffer[k] != '\n' && (buffer[k] == ' ' || buffer[k] == '\t'))
		k--;
	tmp = ft_substr(buffer, i, k - i + 1);
	if (access(tmp, F_OK | R_OK) == -1)
		{
			free(tmp);
			return (NULL);
		}
	else
		return (tmp);
	(void)main;
	(void)pos;
}

static void	map_split(char *buffer, t_main *main)
{
	int	height;
	int	width;
	int	i;
	int err;

	main->exitcount = 0;
	main->playercount = 0;
	main->coincount = 0;
	height = 0;
	i = 0;
	err = 0;
	if (!pre_check(buffer))
		ft_error("Error\nMissing texture or color", main);
	
	while (buffer[i] != 0)
		{
			if (!ft_strncmp(&buffer[i], "\0NO ", 4) || !ft_strncmp(&buffer[i], "\nNO ", 4))
				main->north = get_texture(&buffer[i + 4], main, &i);
			else if (!ft_strncmp(&buffer[i], "\0SO ", 4) || !ft_strncmp(&buffer[i], "\nSO ", 4))
				main->south = get_texture(&buffer[i + 4], main, &i);
			else if (!ft_strncmp(&buffer[i], "\0WE ", 4) || !ft_strncmp(&buffer[i], "\nWE ", 4))
				main->west = get_texture(&buffer[i + 4], main, &i);
			else if (!ft_strncmp(&buffer[i], "\0EA ", 4) || !ft_strncmp(&buffer[i], "\nEA ", 4))
				main->east = get_texture(&buffer[i + 4], main, &i);
			else if (!ft_strncmp(&buffer[i], "\0F ", 3) || !ft_strncmp(&buffer[i], "\nF ", 3))
				get_color(&buffer[i + 3], main->floor, &i);
			else if (!ft_strncmp(&buffer[i], "\0C ", 3) || !ft_strncmp(&buffer[i], "\nC ", 3))
				get_color(&buffer[i + 3], main->ceil, &i);
			
			i++;
			height++;
		}
	if (main->floor[0] == -1 || main->ceil[0] == -1 || main->floor[1] == -1 || main->ceil[1] == -1 || main->floor[2] == -1 || main->ceil[2] == -1 || !main->north || !main->south || !main->west || !main->east)
		ft_error("Error\nMissing texture or color", main);
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
	(void)err;
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

char	**map_init(int fd, t_main *main)
{
	char *buffer;
	int i;
	int bytes;

	buffer = ft_calloc(10000, sizeof(char));
	if (!buffer)
		ft_error("Error\nMalloc failed", main);
	i = 0;
	bytes = 1;
	while (bytes)
	{
		bytes = read(fd, &buffer[i++], 1);
		if (bytes == -1)
			ft_error("Error\nRead failed\n", main);
	}
	if (!buffer[0])
		ft_error("Error\nEmpty map\n", main);
	map_split(buffer, main);
	free(buffer);
	close(fd);
	return (main->map->map);
}