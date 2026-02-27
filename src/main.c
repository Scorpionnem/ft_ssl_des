/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 12:34:33 by mbatty            #+#    #+#             */
/*   Updated: 2026/02/27 21:39:13 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
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

static int	process(t_ctx *ctx, char *input, uint32_t len)
{
	ctx->fn(input, len);
	return (0);
}

static int	process_av(t_ctx *ctx, char **av)
{
	while (*av)
	{
		int	fd = open(*av, O_RDONLY);
		if (fd == -1)
		{
			ft_dprintf(2, "ft_ssl: %s: %s\n", *av, strerror(errno));
			av++;
			continue ;
		}

		struct stat	stats;
		fstat(fd, &stats);

		char	*input = mmap(NULL, stats.st_size, PROT_READ, MAP_SHARED, fd, 0);
		if (input == (void*)-1)
			return (ft_dprintf(2, "ft_ssl: mmap: %s\n", strerror(errno)), -1);

		if (!ctx->reverse._bool && !ctx->quiet._bool)
			ft_printf("%s (%s) = ", ctx->fn_str, *av);

		process(ctx, input, stats.st_size);

		if (ctx->reverse._bool && !ctx->quiet._bool)
			ft_printf(" %s", *av);
		ft_printf("\n");

		munmap(input, stats.st_size);
		close(fd);
		av++;
	}
	return (0);
}

static int	process_string(t_ctx *ctx, char *str)
{
	if (!ctx->reverse._bool && !ctx->quiet._bool)
		ft_printf("%s (\"%s\") = ", ctx->fn_str, str);

	process(ctx, str, ft_strlen(str));

	if (ctx->reverse._bool && !ctx->quiet._bool)
		ft_printf(" \"%s\"", str);
	ft_printf("\n");

	return (0);
}

static void	print_no_nl(char *str, uint32_t len)
{
	uint32_t	 i = 0;
	while (i < len)
	{
		if (str[i] != '\n')
			write(1, &str[i], 1);
		i++;
	}
}

static int	process_stdin(t_ctx *ctx)
{
	char	*buf = ft_calloc(1, 1);
	int		total_read = 0;

	while (1)
	{
		int bytes = read(0, buf + total_read, 1);
		if (bytes <= 0)
			break ;
		total_read += bytes;
		buf = realloc(buf, total_read + 1);
		buf[total_read] = 0;
	}
	if (!ctx->reverse._bool && !ctx->quiet._bool)
	{
		if (ctx->echo._bool)
		{
			print_no_nl(buf, total_read);
			printf(" ");
			fflush(stdout);
		}
		else
			ft_printf("%s (stdin) = ", ctx->fn_str);
	}

	process(ctx, buf, total_read);

	if (ctx->reverse._bool && !ctx->quiet._bool)
	{
		if (ctx->echo._bool)
		{
			ft_printf(" ");
			print_no_nl(buf, total_read);
		}
		else
			ft_printf(" stdin");
	}
	ft_printf("\n");

	free(buf);
	return (0);
}

#define BASE64 "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"

void	base64(char *str)
{
	int	seq = 0;

	uint8_t	prev = 0;
	uint8_t	cur = *str;
	uint8_t	b = 0;
	size_t	i = 0;
	(void)str;
	while (i <= ft_strlen(str))
	{
		prev = cur;
		cur = str[i];

		if (seq == 0)
			b = (cur >> 2) & 0b00111111;
		if (seq == 1)
			b = ((prev & 0b00000011) << 4) | ((cur & 0b11110000) >> 4);
		if (seq == 2)
			b = ((prev & 0b00001111) << 2) | ((cur & 0b11000000) >> 6);
		if (seq == 3)
			b = prev & 0b00111111;

		printf("%c", BASE64[b]);

		i++;
		seq++;
		if (seq >= 4)
			seq = 0;
	}
	printf("\n");
}

int	main(int UNUSED(ac), char **av)
{
	// base64(av[1]);
	// return (0);
	t_ctx	ctx;

	if (ctx_init(&ctx, &av) == -1)
		return (1);

	if (ctx.string._str)
		process_string(&ctx, ctx.string._str);
	if (*av)
		process_av(&ctx, av);
	else if (!ctx.string._str || ctx.echo._bool)
		process_stdin(&ctx);

	ctx_delete(&ctx);
	return (0);
}
