/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:53:31 by ruida-si          #+#    #+#             */
/*   Updated: 2025/06/26 16:49:35 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	key_press(int keycode, t_cub *cub);
static int	key_release(int keycode, t_cub *cub);
static int	close_event(void *param);

void	init_display(t_cub *cub)
{
	cub->img = NULL;
	cub->mlx = mlx_init();	
	cub->win = mlx_new_window(cub->mlx, WIDTH, HEIGHT, "cub3D");
	load_textures(cub);
	ft_memset(&cub->keys, 0, sizeof(t_keys));
	mlx_hook(cub->win, 2, 1L<<0, key_press, cub);
	mlx_hook(cub->win, 3, 1L<<1, key_release, cub);
	mlx_hook(cub->win, 17, 0, close_event, cub);
	mlx_loop_hook(cub->mlx, game_loop, cub);
	mlx_loop(cub->mlx);
}

static int	key_press(int keycode, t_cub *cub)
{
	if (keycode == XK_w)
		cub->keys.w = 1;
	else if (keycode == XK_a)
		cub->keys.a = 1;
	else if (keycode == XK_s)
		cub->keys.s = 1;
	else if (keycode == XK_d)
		cub->keys.d = 1;
	else if (keycode == XK_Left)
		cub->keys.left = 1;
	else if (keycode == XK_Right)
		cub->keys.right = 1;
	else if (keycode == XK_Escape)
	{
		mem_clean(cub);
		exit(1);
	}
	return (0);
}

static int	key_release(int keycode, t_cub *cub)
{
	if (keycode == XK_w)
		cub->keys.w = 0;
	else if (keycode == XK_a)
		cub->keys.a = 0;
	else if (keycode == XK_s)
		cub->keys.s = 0;
	else if (keycode == XK_d)
		cub->keys.d = 0;
	else if (keycode == XK_Left)
		cub->keys.left = 0;
	else if (keycode == XK_Right)
		cub->keys.right = 0;
	return (0);
}

static int	close_event(void *param)
{
	t_cub	*cub;
	
	cub = (t_cub *)param;
	mem_clean(cub);
	exit(1);
}
