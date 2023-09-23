#ifndef cub3D
# define cub3D

# include <fcntl.h> 	/* open */
# include <stdio.h> 	/* perror */
# include <errno.h> 	/* errno */
# include <stdlib.h> 	/* exit */
# include <unistd.h> 	/* write, access */
# include <string.h> 	/* strerror */

# ifdef __APPLE__
#  include "../minilibx-mac/mlx.h"
#  define W_UP 13
#  define S_DOWN 1
#  define A_LEFT 0
#  define D_RIGHT 2
#  define ESC 53
# endif
# ifdef __linux__
//#  include "../minilibx-linux/mlx.h"
#  define W_UP 119
#  define S_DOWN 115
#  define A_LEFT 97
#  define D_RIGHT 100
#  define ESC 65307
# endif

# define PIXEL 64

typedef struct s_img
{
	void			*wall;
	void			*way;
	void			*coin;
	void			*exitd;
	void			*enemy;
	void			*pr;
	void			*pl;
	void			*ple;
	void			*pu;
	void			*pd;
}					t_img;

typedef struct s_map
{
	char			**map;
	int				x;
	int				y;
}					t_map;

typedef struct s_main
{
	void			*mlx;
	void			*win;
	int				p_x;
	int				p_y;
	int				coincount;
	int				movecount;
	int				playercount;
	int				exitcount;
	int				tmp;
	int				exitflag;
	char			*north;
	char			*west;
	char			*east;
	char			*south;
	t_map			*map;
	t_img			*img;
}					t_main;

//t_main		*main_init(t_main *main, char *path);
char		**map_init(int fd, t_main *main);
void		ft_map_check(t_main *main);
void		draw_map(t_main *main);
void		xpm_to_img(t_main *main);
int			key_event(int key, t_main *main);
int			render(t_main *main);
void		write_move_count(t_main *main);
void		ft_error(char *errorcode, t_main *main);
void		*ft_calloc(size_t count, size_t size);
size_t		ft_strlen(const char *s);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_itoa(int n);
int			ft_destroy(t_main *main);
void        check_files(char *path);
void        ft_map_check(t_main *main);
void    	ft_check_valid_map_path(t_main *main);
void    	ft_error(char *errorcode, t_main *main);
int     	ft_destroy(t_main *main);
char		*ft_strnstr(const char *big, const char *little, size_t len);
int			ft_strchr_idx(const char *s, int c);
char		*ft_substr(char const *s, unsigned int start, size_t len);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);

#endif