/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 18:05:57 by mbatty            #+#    #+#             */
/*   Updated: 2026/03/25 20:57:58 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5_ctx.h"
#include "ft_printf.h"
#include <stdlib.h>

int	md5_ctx_init_opts(t_md5_ctx *ctx, char ***av);

#define MD5_HELP_STRING "\
\n\
Usage:\n  ./ft_ssl md5 [options]\n\
\n\
Options:\n\
  -h --help\t\tshow help message and exit\n\
  -q --quiet\t\tquiet mode\n\
  -s --string <string>\tprint the sum of <string>\n\
  -r --reverse\t\treverse the format of the output\n\
  -p\t\t\techo STDIN to STDOUT and append the checksum to STDOUT\n\
\n\
"

int	md5_ctx_init(t_md5_ctx *ctx, char ***av)
{
	if (md5_ctx_init_opts(ctx, av) == -1)
		return (-1);
	if (ctx->help._bool)
	{
		opt_ctx_delete(&ctx->opt_ctx);
		ft_dprintf(2, MD5_HELP_STRING);
		return (-1);
	}

	return (0);
}

void	md5_ctx_delete(t_md5_ctx *ctx)
{
	opt_ctx_delete(&ctx->opt_ctx);
}

int	md5_ctx_init_opts(t_md5_ctx *ctx, char ***av)
{
	opt_ctx_init(&ctx->opt_ctx);

	opt_ctx_add_opt(&ctx->opt_ctx, "-h", &ctx->help, OPT_BOOL);
	opt_ctx_add_opt(&ctx->opt_ctx, "--help", &ctx->help, OPT_BOOL);

	opt_ctx_add_opt(&ctx->opt_ctx, "-p", &ctx->echo, OPT_BOOL);

	opt_ctx_add_opt(&ctx->opt_ctx, "-q", &ctx->quiet, OPT_BOOL);
	opt_ctx_add_opt(&ctx->opt_ctx, "--quiet", &ctx->quiet, OPT_BOOL);

	opt_ctx_add_opt(&ctx->opt_ctx, "-r", &ctx->reverse, OPT_BOOL);
	opt_ctx_add_opt(&ctx->opt_ctx, "--reverse", &ctx->reverse, OPT_BOOL);

	opt_ctx_add_opt(&ctx->opt_ctx, "-s", &ctx->string, OPT_STR);
	opt_ctx_add_opt(&ctx->opt_ctx, "--string", &ctx->string, OPT_STR);

	if (opt_ctx_parse(&ctx->opt_ctx, av) == -1)
	{
		opt_ctx_delete(&ctx->opt_ctx);
		return (-1);
	}
	return (0);
}
