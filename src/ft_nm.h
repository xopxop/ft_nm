/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:34:15 by dthan             #+#    #+#             */
/*   Updated: 2025/05/14 15:36:14 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H
#include <stddef.h>

typedef struct s_nm_options
{
	int display_all_symbols;
	int display_only_external_symbols;
	int display_only_undefined_symbols;
	int reverse_sortted_order;
	int no_sort;
}	t_nm_options;

typedef struct s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}	t_list;

#endif