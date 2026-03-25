/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 12:34:33 by mbatty            #+#    #+#             */
/*   Updated: 2026/03/25 21:07:23 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

#define MAIN_HELP_STRING "\
\nUsage:\n  ./ft_ssl <command> [options]\n\n\
Standard commands:\n\
\n\
Message Digest commands:\n\
  md5\n\
  sha256\n\
\n\
Cipher commands:\n\
  base64\n\
  des\n\
  des-ecb\n\
  des-cbc\n\
\n\
"

int	md5_main(char **av);
int	sha256_main(char **av);
int	base64_main(char **av);
int	des_ecb_main(char **av);

typedef int (*t_command_func)(char **av);
static t_command_func	get_command_func(char *id)
{
	#define COMMANDS_COUNT 4
	const struct {char *id; t_command_func fn;} cmds_map[COMMANDS_COUNT] =
	{
		{.id = "md5", .fn = md5_main},
		{.id = "sha256", .fn = sha256_main},
		{.id = "base64", .fn = base64_main},
		{.id = "des-ecb", .fn = des_ecb_main},
	};

	for (int i = 0; i < COMMANDS_COUNT; i++)
		if (!ft_strcmp(cmds_map[i].id, id))
			return (cmds_map[i].fn);
	return (NULL);
}

int	main(int ac, char **av)
{
	if (ac < 2)
		return (ft_dprintf(2, MAIN_HELP_STRING), 1);

	t_command_func	fn = get_command_func(av[1]);
	if (!fn)
		return (ft_dprintf(2, "ft_ssl: Unknown command: %s\n" MAIN_HELP_STRING, av[1]), 1);

	return (fn(av + 1));
}
