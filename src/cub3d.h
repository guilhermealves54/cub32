/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 19:31:06 by gribeiro          #+#    #+#             */
/*   Updated: 2025/06/26 17:19:27 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "./../minilibx-linux/mlx.h"
# include <math.h>
# include <X11/keysym.h>

//	CONST

// DIMENSIONS
# define WIDTH 1920
# define HEIGHT 1000

// TEXTURES
# define TEX_N 0
# define TEX_S 1
# define TEX_E 2
# define TEX_W 3

// WALLS HIT SIDE
# define X 4
# define Y 5

// VARIABLES
# define FOV 60.0
# define SPEED 0.03
# define ROT 1

//	STRUCTS

//	Map Struct
typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	angle;
}	t_player;
typedef struct s_map
{
	int		col;
	int		lns;
	char	**map;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		f;
	int		c;
	char	*tmp_map;
}	t_map;

typedef struct s_tex
{
	int		*pix;
	void	*img;
	int		width;
	int		height;
	int		bpp;
	int		size_line;
	int		endian;
}	t_tex;

typedef struct s_keys
{
	int w;
	int a;
	int s;
	int d;
	int left;
	int right;
}	t_keys;

typedef struct s_ray
{
	int		x;
	int		side;
	double	raydir_x;
	double	raydir_y;
	double	dist_x;
	double	dist_y;
	double	f_dist_x;
	double	f_dist_y;
	double	step_x;
	double	step_y;
	double	angle;
	double	wall_dist;	
	double	wall_x;
}	t_ray;

//	Main Struct
typedef struct s_cub
{
	void		*mlx;
	void		*win;
	void		*img;
	int			*img_data;
	int			bpp;
	int			size_line;
	int			endian;
	t_keys		keys;
	t_tex		tex[4];
	t_map		map;
	t_player	player;
}	t_cub;

//	FUNCS

//	Parse
int		cubparse(t_cub *cub, int argc, char **argv);
int		fill_final_map(t_cub *cub, int col, int lns);
int		parse_map(t_cub *cub);

//	Parse Utils
char	*get_texture(char *file, char *texture, int *params, int i_bk);
int		get_color(char *file, char *place, int *params);
int		extract_color(char *file, int i, int *j);
void	clean_text(char *file, int i, int j);
int		chk_remain(char *file);
void	mapsize(t_cub *cub);
int		check_xpm_file(t_cub *cub);
int		search_row(t_cub *cub, int i);
int		search_col(t_cub *cub, int j);

//	Graphics
void	init_display(t_cub *cub);
int		game_loop(t_cub * cub);
void	ft_draw_image(t_ray *ray, t_cub *cub, t_player *player);
void	raycast(t_cub *cub);

//	Graphics Utils
void	load_textures(t_cub *cub);
double	deg_to_rad(double degree);

//	Memory Cleanup
void	cln_maparr(t_cub *cub);
void	cln_conf(t_cub *cub, int opt);
void	mem_clean(t_cub *cub);
void	cln_basic(t_cub *cub);

#endif
