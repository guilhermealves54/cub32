/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 22:10:47 by gribeiro          #+#    #+#             */
/*   Updated: 2025/06/20 18:22:40 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_cub	cub;

	if (cubparse(&cub, argc, argv) == -1)
		return (1);
	printf ("\n---\n");
	printf ("Texture N:  %s\n", cub.mapset.no);
	printf ("Texture S:  %s\n", cub.mapset.so);
	printf ("Texture E:  %s\n", cub.mapset.ea);
	printf ("Texture W:  %s\n", cub.mapset.we);
	printf ("\n---\n");
	printf ("RGB Ceiling:  %i\n", cub.mapset.c);
	printf ("RGB Floor:  %i\n", cub.mapset.f);
	printf ("\n---\n");
	printf ("Player start position: %i, %i\n", cub.map.str_pos[0], cub.map.str_pos[1]);
	printf ("Player start angle: %fº\n", cub.map.str_angle);
	printf ("\n---\n");
	int i = 0;
	while (cub.map.map[i])
		printf ("%s\n", cub.map.map[i++]);
	printf ("\n---\n");
	cln_conf(&cub, 0);
	cln_maparr(&cub);
}
