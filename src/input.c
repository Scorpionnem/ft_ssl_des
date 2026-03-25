/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 21:05:11 by mbatty            #+#    #+#             */
/*   Updated: 2026/03/25 10:37:40 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "ft_printf.h"
#include "libft.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

int	get_input_stdin(t_input *in);
int	get_input_file(const char *path, t_input *in);

int	input_get(t_input *in, t_input_type type, char *str_path, uint64_t size)
{
	in->type = type;
	switch (in->type)
	{
		case INPUT_STDIN:
			return (get_input_stdin(in));
		case INPUT_STR:
		{
			in->bytes = (uint8_t*)ft_strdup(str_path);
			in->size = size;
			return (0);
		}
		case INPUT_FILE:
			return (get_input_file(str_path, in));
	}
	return (-1);
}

int	input_free(t_input *in)
{
	switch (in->type)
	{
		case INPUT_STR:
		{
			free(in->bytes);
			break ;
		}
		case INPUT_STDIN:
		{
			free(in->bytes);
			break ;
		}
		case INPUT_FILE:
		{
			munmap(in->file.addr, in->size);
			close(in->file.fd);
			break ;
		}
	}
	return (0);
}

int	get_input_stdin(t_input *in)
{
	uint8_t			*buf = ft_calloc(1, 1);
	uint64_t		size = 0;

	while (1)
	{
		int bytes = read(0, buf + size, 1);
		if (bytes == -1)
		{
			free(buf);
			in->bytes = NULL;
			in->size = 0;
			return (-1);
		}
		if (bytes == 0)
			break ;
		size += bytes;
		buf = realloc(buf, size + 1);
		buf[size] = 0;
	}

	in->bytes = buf;
	in->size = size;
	return (0);
}

int	get_input_file(const char *path, t_input *in)
{
	int	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (ft_dprintf(2, "ft_ssl: %s: %s\n", path, strerror(errno)), -1);

	struct stat	stats;
	fstat(fd, &stats);

	uint8_t	*input = mmap(NULL, stats.st_size, PROT_READ, MAP_SHARED, fd, 0);
	if (input == (void*)-1)
	{
		close(fd);
		return (ft_dprintf(2, "ft_ssl: mmap: %s\n", strerror(errno)), -1);
	}

	in->bytes = input;
	in->size = stats.st_size;
	in->file.fd = fd;
	in->file.addr = input;
	return (0);
}
