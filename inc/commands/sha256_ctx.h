/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_ctx.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 12:34:07 by mbatty            #+#    #+#             */
/*   Updated: 2026/03/25 10:22:02 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "opt.h"

typedef struct	s_sha256_ctx
{
	char	***av;

	t_opt_ctx			opt_ctx;

	t_opt				help;

	t_opt				echo;
	t_opt				quiet;
	t_opt				reverse;
	t_opt				string;
}	t_sha256_ctx;

int		sha256_ctx_init(t_sha256_ctx *ctx, char ***av);
void	sha256_ctx_delete(t_sha256_ctx *ctx);
