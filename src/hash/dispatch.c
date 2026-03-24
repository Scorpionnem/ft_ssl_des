/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 21:04:16 by mbatty            #+#    #+#             */
/*   Updated: 2026/03/01 15:12:59 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256.h"
#include "md5.h"
#include "ctx.h"
#include "ft_printf.h"
#include "libft.h"
#include "input.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

typedef char *(*t_hash_func)(uint8_t *, uint32_t);

char	*md5(uint8_t *msg, uint32_t len);
char	*sha256(uint8_t *msg, uint32_t len);

int	process_av(t_ctx *ctx, char **av, t_hash_func fn)
{
	while (*av)
	{
		t_input	in;

		if (input_get(&in, INPUT_FILE, *av, 0) == -1)
		{
			av++;
			continue ;
		}

		char	*h = fn(in.bytes, in.size);

		if (!ctx->reverse._bool && !ctx->quiet._bool)
			ft_printf("%s (%s) = %s\n", ctx->fn_str, *av, h);
		if (ctx->reverse._bool && !ctx->quiet._bool)
			ft_printf("%s %s\n", h, *av);

		free(h);
		input_free(&in);
		av++;
	}
	return (0);
}

int	process_string(t_ctx *ctx, char *str, t_hash_func fn)
{
	char	*h = fn((uint8_t*)str, ft_strlen(str));

	if (!ctx->reverse._bool && !ctx->quiet._bool)
		ft_printf("%s (\"%s\") = %s\n", ctx->fn_str, str, h);

	if (ctx->reverse._bool && !ctx->quiet._bool)
		ft_printf("%s \"%s\"\n", h, str);

	free(h);
	return (0);
}

void	print_no_nl(char *str, uint32_t len)
{
	uint32_t	 i = 0;
	while (i < len)
	{
		if (str[i] != '\n')
			write(1, &str[i], 1);
		i++;
	}
}

int	process_stdin(t_ctx *ctx, t_hash_func fn)
{
	t_input	in;

	if (input_get(&in, INPUT_STDIN, NULL, 0) == -1)
		return (-1);

	char	*h = fn(in.bytes, in.size);

	if (!ctx->reverse._bool && !ctx->quiet._bool)
	{
		if (ctx->echo._bool)
		{
			print_no_nl((char*)in.bytes, in.size);
			printf(" %s\n", h);
			fflush(stdout);
		}
		else
			ft_printf("%s (stdin) = %s\n", ctx->fn_str, h);
	}

	if (ctx->reverse._bool && !ctx->quiet._bool)
	{
		if (ctx->echo._bool)
		{
			ft_printf("%s ", h);
			print_no_nl((char*)in.bytes, in.size);
			ft_printf("\n");
		}
		else
			ft_printf("%s stdin\n", h);
	}

	free(h);
	input_free(&in);
	return (0);
}

int	md5_dispatch(void *ctx_ptr)
{
	t_ctx	*ctx = ctx_ptr;

	if (ctx->string._str)
		process_string(ctx, ctx->string._str, md5);
	if (**(ctx->av))
		process_av(ctx, *ctx->av, md5);
	else if (!ctx->string._str || ctx->echo._bool)
		process_stdin(ctx, md5);
	return (0);
}

int	sha256_dispatch(void *ctx_ptr)
{
	t_ctx	*ctx = ctx_ptr;

	if (ctx->string._str)
		process_string(ctx, ctx->string._str, sha256);
	if (**(ctx->av))
		process_av(ctx, *ctx->av, sha256);
	else if (!ctx->string._str || ctx->echo._bool)
		process_stdin(ctx, sha256);
	return (0);
}
