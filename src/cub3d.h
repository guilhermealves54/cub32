/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 19:31:06 by gribeiro          #+#    #+#             */
/*   Updated: 2025/06/19 19:32:58 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

//	STRUCTS

//	Map Struct
typedef struct s_map
{
	int		str_pos[2];
	double	str_angle;
	int		col;
	int		lns;
	char	**map;
}	t_map;

typedef struct s_mapset
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		f;
	int		c;
	char	*tmp_map;
}	t_mapset;

//	Main Struct
typedef struct s_cub
{
	t_map		map;
	t_mapset	mapset;
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
int		chk_remain(t_cub *cub);
void	mapsize(t_cub *cub);

//	Memory Cleanup
void	cln_maparr(t_cub *cub);
void	cln_conf(t_cub *cub, int opt);

#endif
