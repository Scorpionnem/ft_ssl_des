/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 17:58:29 by mbatty            #+#    #+#             */
/*   Updated: 2026/03/25 10:25:39 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256_ctx.h"
#include "libft.h"
#include "ft_printf.h"
#include "input.h"
#include <stdint.h>

char	*sha256(uint8_t *msg, uint64_t len);

static void	print_no_nl(char *str, uint32_t len)
{
	uint32_t	 i = 0;
	while (i < len)
	{
		if (str[i] != '\n')
			ft_printf("%c", str[i]);
		i++;
	}
}

static int	process_stdin(t_sha256_ctx *ctx)
{
	t_input	in;

	if (input_get(&in, INPUT_STDIN, NULL, 0) == -1)
		return (-1);

	char	*h = sha256(in.bytes, in.size);

	if (!ctx->reverse._bool && !ctx->quiet._bool)
	{
		if (ctx->echo._bool)
		{
			print_no_nl((char*)in.bytes, in.size);
			ft_printf(" %s\n", h);
		}
		else
			ft_printf("SHA256 (stdin) = %s\n", h);
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

static int	process_files(t_sha256_ctx *ctx, char **av)
{
	while (*av)
	{
		t_input	in;

		if (input_get(&in, INPUT_FILE, *av, 0) == -1)
		{
			av++;
			continue ;
		}

		char	*h = sha256(in.bytes, in.size);

		if (!ctx->reverse._bool && !ctx->quiet._bool)
			ft_printf("SHA256 (%s) = %s\n", *av, h);
		if (ctx->reverse._bool && !ctx->quiet._bool)
			ft_printf("%s %s\n", h, *av);

		free(h);
		input_free(&in);
		av++;
	}
	return (0);
}

static int	process_string(t_sha256_ctx *ctx, char *str)
{
	char	*hash_str = sha256((uint8_t*)str, ft_strlen(str));
	if (!hash_str)
		return (-1);

	if (!ctx->reverse._bool && !ctx->quiet._bool)
		ft_printf("SHA256 (\"%s\") = %s\n", str, hash_str);
	if (ctx->reverse._bool && !ctx->quiet._bool)
		ft_printf("%s \"%s\"\n", hash_str, str);

	free(hash_str);
	return (0);
}

int	sha256_main(char **av)
{
	t_sha256_ctx	ctx;

	if (sha256_ctx_init(&ctx, &av) == -1)
		return (1);

	if (ctx.string._str)
		process_string(&ctx, ctx.string._str);
	if (*av)
		process_files(&ctx, av);
	else if (!ctx.string._str || ctx.echo._bool)
		process_stdin(&ctx);

	sha256_ctx_delete(&ctx);
	return (0);
}
