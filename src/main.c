/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 22:10:47 by gribeiro          #+#    #+#             */
/*   Updated: 2025/06/06 02:44:36 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3d.h"

int	main(int argc, char **argv)
{
	t_cub	cub;

	if (argc != 2)
		return (write(2, "Error\nInvalid Arguments\n", 25), 1);
	if (cubinit(&cub, argv))
		return (1);
}

int	cubinit(t_cub *cub, char **argv)
{
	int	i;

	i = 0;
	if (!argv[1])
		return (write(2, "Error\nInvalid Arguments\n", 25), 1);
	if (checkmap(cub, argv))
		return (write(2, "Error\nInvalid Map\n", 18), 1);
	return (0);
}

int	checkmap(t_cub *cub, char **argv)
{
	int	fd;

	if (ft_strncmp (&argv[1][ft_strlen (argv[1]) - 4], ".cub", 4) != 0)
		return (write(2, "Error\nInvalid Map\n", 18), 1);
	fd = open (argv[1], O_RDONLY);
	if (fd < 0)
		return (write(2, "Error\nInvalid Map\n", 18), 1);
	if (readmap(cub, fd))
		return (1);
	if (parse_map(cub) == -1)
		return(1);
	return (0);
}

int	readmap(t_cub *cub, int fd)
{
	char	buff[1000];
	char	*file;
	char	*temp;
	int		r;

	r = 1;
	file = ft_strdup ("");
	if (!file)
		return (write(2, "Error\nMemmory Error\n", 20), 1);
	while (r > 0)
	{
		r = read (fd, buff, 10);
		buff[r] = '\0';
		temp = NULL;
		temp = file;
		file = ft_strjoin (file, buff);
		if (!file)
			return (free (temp), write(2, "Error\nMemmory Error\n", 20), 1);
		free (temp);
	}
	close (fd);
	if (fillmap(cub, file))
		return (1);
	free(file);
	return (0);
}

int	fillmap(t_cub *cub, char *file)
{
	int	params;

	params = 0;
	cub->mapconf.no = get_texture(file, "NO", &params);
	cub->mapconf.so = get_texture(file, "SO", &params);
	cub->mapconf.we = get_texture(file, "WE", &params);
	cub->mapconf.ea = get_texture(file, "EA", &params);
	cub->mapconf.f = get_color(file, "F", &params);
	cub->mapconf.c = get_color(file, "C", &params);
	if (params != 6)
		return (write(2, "Error\nInvalid map\n", 20), 1);
	cub->mapconf.map = get_map(file);
	return (0);
}

char	*get_texture(char *file, char *texture, int *params)
{
	char	*path;
	int		i;
	int		j;

	path = NULL;
	i = 0;
	j = 0;
	while(file[i])
	{
		if (!ft_strncmp(&file[i], texture, 2))
		{
			i += 2;
			while (file[i] && (file[i] == '\t' || file[i] == ' '))
				i++;
			j = i;
			while (file[j] && file[j] != '\n')
				j++;
			path = ft_substr(file, i, j);
			return (*params++, path);
		}
		i++;
	}
	return (path);
}

int	get_color(char *file, char *place, int *params)
{
	int	color;
	int	i;
	int	j;

	color = -1;
	i = 0;
	j = 0;
	while(file[i])
	{
		if (!ft_strncmp(&file[i], place, 1))
		{
			i++;
			while (file[i] && (file[i] == '\t' || file[i] == ' '))
				i++;
			j = i;
			extract_color(file, i);
			return (*params++, color);
		}
		i++;
	}
	return (color);
}

int	extract_color(char *file, int i)
{
	int		r;
	int		g;
	int		b;

	r = 0;
	g = 0;
	b = 0;
	while (file[i] && (file[i] >= '0' && file[i] <= '9'))
		r = r * 10 + (file[i++] - '0');
	while (file[i] && (file[i] == ',' || file[i] == '\t' || file[i] == ' '))
		i++;
	while (file[i] && (file[i] >= '0' && file[i] <= '9'))
		g = g * 10 + (file[i++] - '0');
	while (file[i] && (file[i] == ',' || file[i] == '\t' || file[i] == ' '))
		i++;
	while (file[i] && (file[i] >= '0' && file[i] <= '9'))
		b = b * 10 + (file[i++] - '0');
	if (r > 255 || g > 255 | b > 255)
		return (-1);
	return ((r << 16) | (g << 8) | b);
}

char	*get_map(char *file)
{
	int		i;
	int		j;
	char	*tmp_map;

	i = ft_strlen(file);
	while (i >= 0 && (!file[i] || file[i] == '\n'))
		i--;
	j = i;
	while (i > 0 && (file[i] != '\n' && file[i - 1] != '\n'))
		i--;
	tmp_map = malloc((j - i + 1) * sizeof(char));
	if (!tmp_map)
		return (NULL);
	while (i <= j)
	{
		tmp_map[i] = file[i];
		i++;
	}
	tmp_map[i] = '\0';
	return(tmp_map);
}

int	parse_map(t_cub *cub)
{
	return (0);
	return (-1);
}