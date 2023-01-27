#include "../includes/cub.h"

t_vec	vec_add(t_vec one, t_vec two)
{
	t_vec	tmp;
	tmp.x = one.x + two.x;
	tmp.y = one.y + two.y;
	return (tmp);
}

t_vec	vec_sub(t_vec one, t_vec two)
{
	t_vec	tmp;
	tmp.x = one.x - two.x;
	tmp.y = one.y - two.y;
	return (tmp);
}

t_vec	dir_rotation(t_vec dir, double angl)
{
	t_vec	tmp;

	tmp.x = dir.x;
	tmp.y = dir.y;
	dir.x = (tmp.x * cos(angl * M_PI/180)) - (tmp.y * sin(angl * M_PI/180));
	dir.y = (tmp.x * sin(angl * M_PI/180)) + (tmp.y * cos(angl * M_PI/180));
	return (dir);
}