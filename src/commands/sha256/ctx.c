/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 18:05:57 by mbatty            #+#    #+#             */
/*   Updated: 2026/03/25 10:22:21 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256_ctx.h"
#include "ft_printf.h"
#include <stdlib.h>

int	sha256_ctx_init_opts(t_sha256_ctx *ctx, char ***av);

#define sha256_HELP_STRING "\
\n\
Usage:\n  ./ft_ssl sha256 [options]\n\
\n\
Options:\n\
  -q\t\tquiet mode\n\
  -s <string>\tprint the sum of <string>\n\
  -h\t\tshow help message and exit\n\
  -r\t\treverse the format of the output\n\
  -p\t\techo STDIN to STDOUT and append the checksum to STDOUT\n\
\n\
"

int	sha256_ctx_init(t_sha256_ctx *ctx, char ***av)
{
	if (sha256_ctx_init_opts(ctx, av) == -1)
		return (-1);
	if (ctx->help._bool)
	{
		opt_ctx_delete(&ctx->opt_ctx);
		ft_dprintf(2, sha256_HELP_STRING);
		return (-1);
	}

	return (0);
}

void	sha256_ctx_delete(t_sha256_ctx *ctx)
{
	opt_ctx_delete(&ctx->opt_ctx);
}

int	sha256_ctx_init_opts(t_sha256_ctx *ctx, char ***av)
{
	opt_ctx_init(&ctx->opt_ctx);

	opt_ctx_add_opt(&ctx->opt_ctx, "-h", &ctx->help, OPT_BOOL);
	opt_ctx_add_opt(&ctx->opt_ctx, "--help", &ctx->help, OPT_BOOL);

	opt_ctx_add_opt(&ctx->opt_ctx, "-p", &ctx->echo, OPT_BOOL);
	opt_ctx_add_opt(&ctx->opt_ctx, "-q", &ctx->quiet, OPT_BOOL);
	opt_ctx_add_opt(&ctx->opt_ctx, "-r", &ctx->reverse, OPT_BOOL);

	opt_ctx_add_opt(&ctx->opt_ctx, "-s", &ctx->string, OPT_STR);

	if (opt_ctx_parse(&ctx->opt_ctx, av) == -1)
	{
		opt_ctx_delete(&ctx->opt_ctx);
		return (-1);
	}
	return (0);
}
