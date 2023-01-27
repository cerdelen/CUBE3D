#ifndef DEFINES_H
#define DEFINES_H


//macOS-keys
#define	ESC_KEY		53
#define	W_KEY		13
#define	A_KEY		0
#define	S_KEY		1
#define	D_KEY		2
#define	LEFT_KEY	123
#define	RIGHT_KEY	124
#define	DOWN_KEY	125
#define	UP_KEY		126

//mlx events
#define	ON_KEYDOWN	2
#define	ON_KEYUP	3
#define	ON_DESTROY	17

//window specs
#define WIN_WIDTH_2d		1200
#define WIN_HEIGTH_2d		1200
#define WIN_WIDTH_3d		1280
#define WIN_HEIGTH_3d		720
// #define WIN_WIDTH			WIN_WIDTH_2d
// #define WIN_HEIGTH			WIN_HEIGTH_2d
#define WIN_WIDTH			WIN_WIDTH_3d
#define WIN_HEIGTH			WIN_HEIGTH_3d

// Tiles
#define TILE			100
// #define TILE_2D_WID		WIN_WIDTH
// #define TILE_2D_HEIG		win

// movement specs
#define	MOVE_DIST	15

// move defines
#define	MV_FWRD				W_KEY
#define	MV_BACK				S_KEY
#define	MV_RIGHT			D_KEY
#define	MV_LEFT				A_KEY
#define ROTATION_ANGLE		18

// raycast defines
#define FOV				90
// #define RAY_ANGLE		WIN_WIDTH / 
#define RAY_COUNT		WIN_WIDTH 
#define	VERY_BIG_NUMBER	1000000000

// wall_defines
#define	NORTH_WALL	0
#define	SOUTH_WALL	1
#define	WEST_WALL	2
#define	EAST_WALL	3



#endif