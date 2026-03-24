/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 21:05:19 by mbatty            #+#    #+#             */
/*   Updated: 2026/02/27 21:28:12 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdint.h>

typedef enum	e_input_type
{
	INPUT_STR,
	INPUT_FILE,
	INPUT_STDIN,
}	t_input_type;

typedef struct	s_input
{
	uint8_t			*bytes;
	uint64_t		size;
	t_input_type	type;
	union
	{
		struct
		{
			int		fd;
			void	*addr;
		}	file;
	};
}	t_input;

int	input_get(t_input *in, t_input_type type, char *str_path, uint64_t size);
int	input_free(t_input *in);
