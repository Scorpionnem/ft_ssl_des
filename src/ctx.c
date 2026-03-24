/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 18:05:50 by mbatty            #+#    #+#             */
/*   Updated: 2026/03/24 17:54:19 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "libft.h"
#include "ft_printf.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int		ctx_init_opts(t_ctx *ctx, char ***av);
void	print_help();

static t_command_func	get_command_func(char *id)
{
	#define COMMANDS_COUNT 4
	const struct {char *id; t_command_func fn;} commands_to_funcs[COMMANDS_COUNT] =
	{
		{.id = "md5", .fn = md5_dispatch},
		{.id = "sha256", .fn = sha256_dispatch},
		{.id = "base64", .fn = base64_dispatch},
		{.id = "des-ecb", .fn = des_ecb_dispatch},
	};

	for (int i = 0; i < COMMANDS_COUNT; i++)
		if (!ft_strcmp(commands_to_funcs[i].id, id))
			return (commands_to_funcs[i].fn);
	return (NULL);
}

int	ctx_init(t_ctx *ctx, char ***av)
{
	if (ctx_init_opts(ctx, av) == -1)
		return (-1);
	if (ctx->help._bool)
	{
		opt_ctx_delete(&ctx->opt_ctx);
		// print_help();
		return (-1);
	}

	if (*av[0] == NULL)
	{
		opt_ctx_delete(&ctx->opt_ctx);
		ft_dprintf(2, "ft_ssl: command required (see -h)\n");
		return (-1);
	}
	ctx->fn = get_command_func(*av[0]);
	if (ctx->fn == NULL)
	{
		opt_ctx_delete(&ctx->opt_ctx);
		ft_dprintf(2, "ft_ssl: Unknown command (%s)\n", *av[0]);
		return (-1);
	}
	ctx->fn_str = ft_strdup(*av[0]);

	(*av)++;

	return (0);
}

void	ctx_delete(t_ctx *ctx)
{
	free(ctx->fn_str);
	opt_ctx_delete(&ctx->opt_ctx);
}

int	ctx_init_opts(t_ctx *ctx, char ***av)
{
	opt_ctx_init(&ctx->opt_ctx);

	opt_ctx_add_opt(&ctx->opt_ctx, "-h", &ctx->help, OPT_BOOL);
	opt_ctx_add_opt(&ctx->opt_ctx, "--help", &ctx->help, OPT_BOOL);

	// HMMMM YUMMY -p FLAG
	if ((*av)[1] && (!ft_strcmp((*av)[1], "des") || !ft_strcmp((*av)[1], "des-ecb") || !ft_strcmp((*av)[1], "des-cbc")))
		opt_ctx_add_opt(&ctx->opt_ctx, "-p", &ctx->echo, OPT_STR);
	else
		opt_ctx_add_opt(&ctx->opt_ctx, "-p", &ctx->echo, OPT_BOOL);

	opt_ctx_add_opt(&ctx->opt_ctx, "-q", &ctx->quiet, OPT_BOOL);
	opt_ctx_add_opt(&ctx->opt_ctx, "-r", &ctx->reverse, OPT_BOOL);
	opt_ctx_add_opt(&ctx->opt_ctx, "-e", &ctx->encode, OPT_BOOL);
	ctx->encode._bool = true;
	opt_ctx_add_opt(&ctx->opt_ctx, "-d", &ctx->decode, OPT_BOOL);
	opt_ctx_add_opt(&ctx->opt_ctx, "-a", &ctx->base64_io, OPT_BOOL);

	opt_ctx_add_opt(&ctx->opt_ctx, "-s", &ctx->string, OPT_STR);
	opt_ctx_add_opt(&ctx->opt_ctx, "-i", &ctx->input, OPT_STR);
	opt_ctx_add_opt(&ctx->opt_ctx, "-o", &ctx->output, OPT_STR);

	opt_ctx_add_opt(&ctx->opt_ctx, "-k", &ctx->key, OPT_STR);
	opt_ctx_add_opt(&ctx->opt_ctx, "-v", &ctx->init_vector, OPT_STR);

	// Options collision, need to do ts (yes I couldve done the options after checking the command (might do that actually?))
	ctx->password = &ctx->echo;
	ctx->salt = &ctx->string;

	if (opt_ctx_parse(&ctx->opt_ctx, av) == -1)
	{
		opt_ctx_delete(&ctx->opt_ctx);
		return (-1);
	}
	return (0);
}
