#ifndef CUB3D_H
# define CUB3D_H

#include"libft.h"
#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

//	STRUCTS

//	Map Struct
typedef struct	s_mapconf
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		f;
	int		c;
	char	*tmp_map;
}	t_mapconf;

//	Main Struct
typedef struct	s_cub
{
	char		*argv;
	t_mapconf	mapconf;
}	t_cub;

#endif
