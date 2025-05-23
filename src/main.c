/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:05:35 by dthan             #+#    #+#             */
/*   Updated: 2025/05/16 11:55:49 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include "helper.h"
#include <stdio.h>
#include <elf.h>

int	cleanup_file_resources_and_return(int value, int file_descriptor_to_close, void *file_mmap_to_free, size_t file_size)
{
	if (file_descriptor_to_close != -1)
		close(file_descriptor_to_close);
	if (file_mmap_to_free && file_size)
		munmap(file_mmap_to_free, file_size);
	return (value);
}

void    print_symbol_entry_list(t_list *list)
{
    t_list *current;
    t_symbol_entry *entry;

    current = list;
    while (current)
    {
	entry = (t_symbol_entry *)current->content;
	printf("%p %s %s\n", entry->address, entry->type, entry->name);
	current = current->next;
    }
}

void print_symbol_table(void *file_map)
{
        t_list *list;

        list = get_symbol_entry_list(file_map);
        if (list == NULL) return;
        print_symbol_entry_list(list);
        // Free the list after use
}

int	execute(char *file)
{
	int file_descriptor;
	struct stat file_stat;
	void *file_mmap;

	file_descriptor = open(file, O_RDONLY);
	if (file_descriptor == -1 || !valid_file(file_descriptor))
		return cleanup_file_resources_and_return(-1, -1, NULL, 0);
	if (fstat(file_descriptor, &file_stat) == -1)
		return cleanup_file_resources_and_return(-1, file_descriptor, NULL, 0);
	file_mmap = mmap(NULL, file_stat.st_size, PROT_READ, MAP_PRIVATE, file_descriptor, 0);
	if (file_mmap == NULL)
		return cleanup_file_resources_and_return(-1, file_descriptor, NULL, 0);
	print_symbol_table(file_mmap);
	return cleanup_file_resources_and_return(0, file_descriptor, file_mmap, file_stat.st_size);
}

int	main(int ac, char **av)
{
	return execute("a.out");
}
