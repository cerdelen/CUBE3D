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



# define PI 3.1415926535
# define m_speed 15
# define r_speed 0.1

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
	t_data		td_p_img;
	t_data		td_bg_img;
	t_data		td_ft_img;
	t_data		td_w_img;

}	t_c3d_data;






#endif