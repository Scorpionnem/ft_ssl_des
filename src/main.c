/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 12:34:33 by mbatty            #+#    #+#             */
/*   Updated: 2026/02/27 21:33:51 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static int	process(t_ctx *ctx, uint8_t *input, uint32_t len)
{
	ctx->fn(input, len);
	return (0);
}

static int	process_av(t_ctx *ctx, char **av)
{
	while (*av)
	{
		t_input	in;

		if (input_get(&in, INPUT_FILE, *av, 0) == -1)
		{
			av++;
			continue ;
		}

		if (!ctx->reverse._bool && !ctx->quiet._bool)
			ft_printf("%s (%s) = ", ctx->fn_str, *av);

		process(ctx, in.bytes, in.size);

		if (ctx->reverse._bool && !ctx->quiet._bool)
			ft_printf(" %s", *av);
		ft_printf("\n");

		input_free(&in);
		av++;
	}
	return (0);
}

static int	process_string(t_ctx *ctx, char *str)
{
	if (!ctx->reverse._bool && !ctx->quiet._bool)
		ft_printf("%s (\"%s\") = ", ctx->fn_str, str);

	process(ctx, (uint8_t*)str, ft_strlen(str));

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
	t_input	in;

	if (input_get(&in, INPUT_STDIN, NULL, 0) == -1)
		return (-1);

	if (!ctx->reverse._bool && !ctx->quiet._bool)
	{
		if (ctx->echo._bool)
		{
			print_no_nl((char*)in.bytes, in.size);
			printf(" ");
			fflush(stdout);
		}
		else
			ft_printf("%s (stdin) = ", ctx->fn_str);
	}

	process(ctx, in.bytes, in.size);

	if (ctx->reverse._bool && !ctx->quiet._bool)
	{
		if (ctx->echo._bool)
		{
			ft_printf(" ");
			print_no_nl((char*)in.bytes, in.size);
		}
		else
			ft_printf(" stdin");
	}
	ft_printf("\n");

	input_free(&in);
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
