/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 22:10:47 by gribeiro          #+#    #+#             */
/*   Updated: 2025/06/11 17:47:48 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3d.h"

int	cubinit(t_cub *cub, char **argv);
int	checkmap(t_cub *cub, char **argv);
int	readmap(t_cub *cub, int fd);
int	fillmap(t_cub *cub, char *file);
char	*get_texture(char *file, char *texture, int *params);
int	get_color(char *file, char *place, int *params);
int	extract_color(char *file, int i, int *j);
char	*get_map(char *file);
int	parse_map(t_cub *cub);

int	main(int argc, char **argv)
{
	t_cub	cub;

	if (argc != 2)
		return (write(2, "Error\nInvalid Arguments\n", 25), 1);
	if (cubinit(&cub, argv) == -1)
		return (1);
	printf("N Text: %s\n", cub.mapconf.no);
	printf("S Text: %s\n", cub.mapconf.so);
	printf("E Text: %s\n", cub.mapconf.ea);
	printf("O Text: %s\n", cub.mapconf.we);
	printf("Ceiling color: %i\n", cub.mapconf.c);
	printf("floor color: %i\n", cub.mapconf.f);
	printf("map:\n%s\n", cub.mapconf.tmp_map);
}

int	cubinit(t_cub *cub, char **argv)
{
	int	i;

	i = 0;
	if (!argv[1])
		return (write(2, "Error\nInvalid Arguments\n", 25), -1);
	if (checkmap(cub, argv) == -1)
		return (-1);
	return (0);
}

int	checkmap(t_cub *cub, char **argv)
{
	int	fd;

	if (ft_strncmp (&argv[1][ft_strlen (argv[1]) - 4], ".cub", 4) != 0)
		return (write(2, "Error\nInvalid Map\n", 18), -1);
	fd = open (argv[1], O_RDONLY);
	if (fd < 0)
		return (write(2, "Error\nInvalid Map\n", 18), -1);
	if (readmap(cub, fd) == -1)
		return (-1);
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
		return (write(2, "Error\nMemmory Error\n", 20), -1);
	while (r > 0)
	{
		r = read (fd, buff, 999);
		buff[r] = '\0';
		temp = NULL;
		temp = file;
		file = ft_strjoin (file, buff);
		if (!file)
			return (free (temp), write(2, "Error\nMemmory Error\n", 20), -1);
		free (temp);
	}
	close (fd);
	if (fillmap(cub, file) == -1)
		return (free(file), -1);
	free(file);
	return (0);
}

int	fillmap(t_cub *cub, char *file)
{
	int	params;

	params = 0;
	printf ("%s\n\n", file);
	cub->mapconf.no = get_texture(file, "NO", &params);
	cub->mapconf.so = get_texture(file, "SO", &params);
	cub->mapconf.we = get_texture(file, "WE", &params);
	cub->mapconf.ea = get_texture(file, "EA", &params);
	cub->mapconf.f = get_color(file, "F", &params);
	if (cub->mapconf.f == -1)
		return (write(2, "Error\nInvalid map\n", 18), -1);
	cub->mapconf.c = get_color(file, "C", &params);
	if (cub->mapconf.c == -1)
		return (write(2, "Error\nInvalid map\n", 18), -1);
	if (params != 6)
		return (write(2, "Error\nInvalid map\n", 18), -1);
	cub->mapconf.tmp_map = get_map(file);
	printf ("%s\n\n", file);
	return (0);
}

void	clean_text(char *file, int i, int j)
{
	while (i < j)
		file[i++] = '#';
}

char	*get_texture(char *file, char *texture, int *params)
{
	char	*path;
	int		i;
	int		i_bk;
	int		j;

	path = NULL;
	i = 0;
	i_bk = 0;
	j = 0;
	while(file[i])
	{
		if (!ft_strncmp(&file[i], texture, 2))
		{
			i_bk = i;
			i += 2;
			while (file[i] && (file[i] == '\t' || file[i] == ' '))
				i++;
			j = i;
			while (file[j] && file[j] != '\n')
				j++;
			path = ft_substr(file, i, j - i);
			return (clean_text(file, i_bk, j), (*params)++, path);
		}
		i++;
	}
	return (path);
}

int	get_color(char *file, char *place, int *params)
{
	int	color;
	int	i;
	int	i_bk;
	int	j;

	color = -1;
	i = 0;
	i_bk = 0;
	j = 0;
	while(file[i])
	{
		if (!ft_strncmp(&file[i], place, 1))
		{
			i_bk = i;
			i += 2;
			while (file[i] && (file[i] == '\t' || file[i] == ' '))
				i++;
			color = extract_color(file, i, &j);
			return (clean_text(file, i_bk, j), (*params)++, color);
		}
		i++;
	}
	return (color);
}

int	extract_color(char *file, int i, int *j)
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
	*j = i;
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
	j = i;
	while (i > 0 && (!file[i] || file[i] == '\n'))
		i--;
	while (i > 0)
	{
		if (file[i] == '\n' && file[i - 1] == '\n')
		{
			i += 1;
			break;
		}
		i--;
	}
	if (i <= 0)
		return (NULL);
	tmp_map = ft_strdup(&file[i]);
	if (!tmp_map)
		return (NULL);
	return(clean_text(file, i, j), tmp_map);
}

int	parse_map(t_cub *cub)
{
	(void)cub;
	return (0);
	return (-1);
}
