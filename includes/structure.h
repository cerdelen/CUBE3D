#ifndef STRUCTURE_H
#define STRUCTURE_H

typedef struct	s_vec
{
	double	x;
	double	y;
}	t_vec;

typedef struct	s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct	s_wall_stats
{
	t_img	*img;
	int		width;
	int		height;
}	t_wall_stats;

typedef struct	s_player
{
	t_vec		pos;
	t_vec		dir;
}	t_player;

typedef struct s_data
{
	void			*mlx;
	void			*mlx_win;
	t_img			img;
	t_wall_stats	walls[4];
	// t_wall_stats	east_walls;
	// t_wall_stats	west_walls;
	// t_wall_stats	north_walls;
	// t_wall_stats	south_walls;
	int				floor_col;
	int				ceiling_col;
	char			**map;
	int				map_x;
	int				map_y;
	t_player		player;
	int				found_wall;
	t_vec			intersection_horz; // temp for debugging
	t_vec			intersection_vert; // temp for debugging
	t_vec			intersection; // temp for debugging
}	t_data;

//	utility
char		*get_next_line(int fd);




void		init(t_data *data);
void		parsing(int argc, char **argv, t_data *data);
void		cleanup(t_data *data);











#endif