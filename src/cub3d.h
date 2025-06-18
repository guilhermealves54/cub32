#ifndef CUB3D_H
# define CUB3D_H

#include"libft.h"
#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

//	STRUCTS

//	Map Struct
typedef struct	s_map
{

	int		f;
	int		c;
	char	**map;
	//FDs NAO SAO NECESSARIOS - MAPA COMO ARRAY DE INT - PASSAR COORDENADA DE PLAYER + ANGULO
}	t_map;

typedef struct	s_mapconf
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		f;
	int		c;
	char	*tmp_map;
	char	**map;
}	t_mapconf;

//	Main Struct
typedef struct	s_cub
{
	t_map		map;
	t_mapconf	mapconf;
}	t_cub;

#endif
