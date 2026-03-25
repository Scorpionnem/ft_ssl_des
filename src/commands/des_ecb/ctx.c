/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 18:05:57 by mbatty            #+#    #+#             */
/*   Updated: 2026/03/25 21:21:57 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des_ecb_ctx.h"
#include "ft_printf.h"
#include <stdlib.h>

int	des_ecb_ctx_init_opts(t_des_ecb_ctx *ctx, char ***av);

#define DES_ECB_HELP_STRING "\
\n\
Usage:\n  ./ft_ssl des_ecb [options]\n\
\n\
Options:\n\
  -h --help\t\t\tshow help message and exit\n\
  -a\t\t\t\tdecode/encode the input/output in base64, depending on the encrypt mode\n\
  -d --decrypt\t\t\tdecrypt mode\n\
  -e --encrypt\t\t\tencrypt mode (default)\n\
  -i --input <string>\t\tinput file\n\
  -o --output <string>\t\toutput file\n\
  -k --key <string>\t\tkey in hex\n\
  -p --password <string>\tpassword in ASCII\n\
  -s --salt <string>\t\tsalt in hex\n\
  -v --vector <string>\t\tinitialization vector in hex\n\
\n\
"

int	des_ecb_ctx_init(t_des_ecb_ctx *ctx, char ***av)
{
	if (des_ecb_ctx_init_opts(ctx, av) == -1)
		return (-1);
	if (ctx->help._bool)
	{
		opt_ctx_delete(&ctx->opt_ctx);
		ft_dprintf(2, DES_ECB_HELP_STRING);
		return (-1);
	}

	return (0);
}

void	des_ecb_ctx_delete(t_des_ecb_ctx *ctx)
{
	opt_ctx_delete(&ctx->opt_ctx);
}

int	des_ecb_ctx_init_opts(t_des_ecb_ctx *ctx, char ***av)
{
	opt_ctx_init(&ctx->opt_ctx);

	opt_ctx_add_opt(&ctx->opt_ctx, "-h", &ctx->help, OPT_BOOL);
	opt_ctx_add_opt(&ctx->opt_ctx, "--help", &ctx->help, OPT_BOOL);

	opt_ctx_add_opt(&ctx->opt_ctx, "-a", &ctx->b64_encode, OPT_BOOL);

	opt_ctx_add_opt(&ctx->opt_ctx, "-e", &ctx->encrypt, OPT_BOOL);
	opt_ctx_add_opt(&ctx->opt_ctx, "--encrypt", &ctx->encrypt, OPT_BOOL);

	ctx->encrypt._bool = true;

	opt_ctx_add_opt(&ctx->opt_ctx, "-d", &ctx->decrypt, OPT_BOOL);
	opt_ctx_add_opt(&ctx->opt_ctx, "--decrypt", &ctx->decrypt, OPT_BOOL);

	opt_ctx_add_opt(&ctx->opt_ctx, "-i", &ctx->input, OPT_STR);
	opt_ctx_add_opt(&ctx->opt_ctx, "--input", &ctx->input, OPT_STR);

	opt_ctx_add_opt(&ctx->opt_ctx, "-o", &ctx->output, OPT_STR);
	opt_ctx_add_opt(&ctx->opt_ctx, "--output", &ctx->output, OPT_STR);

	opt_ctx_add_opt(&ctx->opt_ctx, "-k", &ctx->key, OPT_STR);
	opt_ctx_add_opt(&ctx->opt_ctx, "--key", &ctx->key, OPT_STR);

	opt_ctx_add_opt(&ctx->opt_ctx, "-p", &ctx->password, OPT_STR);
	opt_ctx_add_opt(&ctx->opt_ctx, "--password", &ctx->password, OPT_STR);

	opt_ctx_add_opt(&ctx->opt_ctx, "-s", &ctx->salt, OPT_STR);
	opt_ctx_add_opt(&ctx->opt_ctx, "--salt", &ctx->salt, OPT_STR);

	opt_ctx_add_opt(&ctx->opt_ctx, "-v", &ctx->init_vector, OPT_STR);
	opt_ctx_add_opt(&ctx->opt_ctx, "--vector", &ctx->init_vector, OPT_STR);

	if (opt_ctx_parse(&ctx->opt_ctx, av) == -1)
	{
		opt_ctx_delete(&ctx->opt_ctx);
		return (-1);
	}
	return (0);
}
