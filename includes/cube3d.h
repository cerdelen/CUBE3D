#ifndef CUBE3D

#define CUBE3D

# include "libft.h"
# include "get_next_line.h"
# include "mlx.h"

// used for booleans

# include <stdbool.h>

// used for fd management

# include <fcntl.h>				

// used to do math

# include <math.h>

// used for perror

# include <stdio.h>

// used for rotation and movement calculation

# define PI 3.1415926535
# define m_speed 15
# define r_speed (PI / 90)
# define rotationfix (PI / 241)
# define P2 PI / 2
# define P3 3 * PI / 2
# define FOV 90
# define RAD PI / 180
# define T_SIZE 64
# define WINDOW_H 768
# define WINDOW_W 1024
# define RED 0x00FF0000
# define GRE 0x0033CC00
# define BRN 0x006E4F4F
# define BLU 0X000033FF
# define BLK 0



// used for mlx hooks

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_c3d_data
{
	char		**map;
	int			rows;
	int			columns;
	double		p_x;
	double		p_y;
	double		p_dx;
	double		p_dy;
	double		p_a;
	void		*mlx;
	void		*mlx_win;
	void		*mlx_win2;
	int			ceiling_colour;
	int			floor_colour;
	t_data		f_p_view;
	t_data		floor;
	t_data		ceiling;
	// t_data		td_p_img;
	// t_data		td_bg_img;
	// t_data		td_ft_img;
	// t_data		td_w_img;

}	t_c3d_data;

void	cube3d_game(t_c3d_data *data);
int	render_top_down_map(t_c3d_data *data);
t_data		my_new_image(void *mlx, int width, int heigth);



//testing funcitons

int 	draw_line(void *mlx, void *win, int beginX, int beginY, int endX, int endY, int color);
int		draw_line_img(t_data *data, int beginX, int beginY, int endX, int endY, int color);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	draw_rays(t_c3d_data *data);

#endif