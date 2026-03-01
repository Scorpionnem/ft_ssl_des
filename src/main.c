/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 12:34:33 by mbatty            #+#    #+#             */
/*   Updated: 2026/03/01 18:36:02 by mbatty           ###   ########.fr       */
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

int	main(int UNUSED(ac), char **av)
{
	t_ctx	ctx;

	if (ctx_init(&ctx, &av) == -1)
		return (1);

	ctx.av = &av;

	int	res = ctx.fn(&ctx);

	ctx_delete(&ctx);
	return (res);
}
