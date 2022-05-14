#ifndef CUBE3D

#define CUBE3D

#include "libft.h"
#include "get_next_line.h"
#include "mlx.h"
#include <stdbool.h>





# define PI 3.1415926535
# define m_speed 15
# define r_speed 0.1


typedef struct s_c3d_data
{
	char		**map;
	double		p_x;
	double		p_y;
	double		p_dx;
	double		p_dy;

}	t_c3d_data;






#endif