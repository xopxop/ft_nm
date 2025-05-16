/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 07:46:30 by dthan             #+#    #+#             */
/*   Updated: 2025/05/15 10:49:18 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

typedef struct s_list
{
	void		*content;
	size_t		content_size;
	struct s_list	*next;
}	t_list;

typedef struct s_data
{
	void	*address;
	char	*type;
	char	*name;
}	t_data;

void    print_data(t_list *list)
{
    t_list *current;
    t_data *data;

    current = list;
    while (current)
    {
	data = (t_data *)current->content;
	printf("%p %s %s\n", data->address, data->type, data->name);
	current = current->next;
    }
}
