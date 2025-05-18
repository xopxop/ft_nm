/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:09:58 by dthan             #+#    #+#             */
/*   Updated: 2025/05/16 11:56:09 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <elf.h>
#include <stddef.h>

typedef struct s_list
{
	void		*content;
	size_t		content_size;
	struct s_list	*next;
}	t_list;

typedef struct s_symbol_entry
{
	void	*address;
	char	*type;
	char	*name;
}	t_symbol_entry;

t_list  *parse_section_header_symtab(void *file_map, Elf64_Off offset)
{
	Elf64_Sym *symtab = (Elf64_Sym *)(file_map + offset);
	int sym_count = sizeof(symtab) / sizeof(Elf64_Sym);
	t_list *list = NULL;

	for (int i = 0; i < sym_count; i++)
	{
		t_symbol_entry *entry = malloc(sizeof(t_symbol_entry));
		entry->address = (void *)(symtab[i].st_value);
		entry->type = "symbol"; // Placeholder for actual type
		entry->name = "symbol_name"; // Placeholder for actual name
		list_add(&list, entry);
	}
}

t_list *get_symbol_entry_list(void *file_map)
{
	Elf64_Ehdr *eh = (Elf64_Ehdr *)file_map;
	Elf64_Shdr *sh = (Elf64_Shdr *)(file_map + eh->e_shoff);
	int i = 0;

	while (i < eh->e_shnum)
	{
		if (sh[i].sh_type == SHT_SYMTAB)
			return parse_section_header_symtab(file_map, sh[i].sh_offset);
		i++;
	}
	return (NULL);
}
