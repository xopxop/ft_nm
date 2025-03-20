/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:05:35 by dthan             #+#    #+#             */
/*   Updated: 2025/03/20 23:29:09 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <elf.h>

int	get_file_descriptor(char *file)
{
	int fd;
	int flags;

	flags = O_RDONLY;
	fd = open(file, flags);
	if (fd == -1) {
		perror("open");
		return (-1);
	}
	return (fd);
}

struct stat *get_file_stat(int fd)
{
	struct stat *file_stat;

	if (fstat(fd, file_stat) == -1) {
		perror("fstat");
		return (NULL);
	}
	return (file_stat);
}

void	*get_memory_map(int fd, off_t file_size)
{
	void *map;

	map = mmap(NULL, file_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (map == MAP_FAILED) {
		perror("mmap");
		return (NULL);
	}
	return (map);
}

void	print_symbol(void)
{
	printf("print_symbol\n");
}


enum {
	absolute_value = "A",
	uninitialized_data_section = "B",
	common = "C",
	initialised_data_section = "D",
	an_initialised_data_section_for_small_objects = "G",
	debugging = "N",
	a_read_only_data_section = "R",
	an_uninitialized_data_section_for_small_objects = "S",
	text_code_section = "T",
	undefined = "U",
	a_weak_object = "V",
	"W" ,

} e_global_symbol_type;

enum {
	uninitialized_data_section = "b",
	initialised_data_section = "d",
	an_initialised_data_section_for_small_objects = "g",
	// "i"
	a_stack_unwind_section = "p",
	a_read_only_data_section = "r",
	an_uninitialized_data_section_for_small_objects = "s",
	text_code_section = "t",
	unique_global_symbol = "u",
	a_weak_object = "v",
	"w",
	"-",
	"?",

} e_local_symbol_type;

char get_symbol_type(Elf64_Sym *sym, Elf64_Shdr *shdr)
{
	if (ELF64_ST_BIND(sym->st_info) == STB_GNU_UNIQUE) return 'u';
	if (ELF64_ST_BIND(sym->st_info) == STB_WEAK) {
	    if (ELF64_ST_TYPE(sym->st_info) == STT_OBJECT)
		return (sym->st_shndx == SHN_UNDEF) ? 'v' : 'V';
	    return (sym->st_shndx == SHN_UNDEF) ? 'w' : 'W';
	}
	if (sym->st_shndx == SHN_UNDEF) return 'U';
	if (sym->st_shndx == SHN_ABS) return 'A';
	if (sym->st_shndx == SHN_COMMON) return 'C';
	if (shdr[sym->st_shndx].sh_type == SHT_NOBITS) return 'B';
	if (shdr[sym->st_shndx].sh_type == SHT_PROGBITS) {
		if (shdr[sym->st_shndx].sh_flags & SHF_EXECINSTR) return 'T';
		if (shdr[sym->st_shndx].sh_flags & SHF_WRITE) return 'D';
		return 'R';
	}
	return '?';
}

void safe_write(const char *str)
{
	write(STDOUT_FILENO, str, strlen(str));
}

void parse_elf_symbols(void *map, struct stat *st)
{
	Elf64_Ehdr *ehdr = (Elf64_Ehdr *)map;
	Elf64_Shdr *shdr = (Elf64_Shdr *)(map + ehdr->e_shoff);
	Elf64_Shdr *strtab_shdr = &shdr[ehdr->e_shstrndx];
	char *shstrtab = (char *)(map + strtab_shdr->sh_offset);

	for (int i = 0; i < ehdr->e_shnum; i++)
	{
		if (shdr[i].sh_type == SHT_SYMTAB)
		{
			Elf64_Sym *symtab = (Elf64_Sym *)(map + shdr[i].sh_offset);
			int symcount = shdr[i].sh_size / shdr[i].sh_entsize;
			char *strtab = (char *)(map + shdr[shdr[i].sh_link].sh_offset);

			for (int j = 0; j < symcount; j++)
			{
				if (symtab[j].st_name == 0) continue;

				char buffer[128];
				snprintf(buffer, sizeof(buffer), "%016lx %c %s\n",
					symtab[j].st_value,
					get_symbol_type(&symtab[j], shdr),
					&strtab[symtab[j].st_name]);
				safe_write(buffer);
			}
			return;
		}
	}
}

void	display_symbol_table(char *file)
{
	struct stat *st;
	int fd = get_file_descriptor(file);
	if (fd == -1) return ;
	st = get_file_stat(fd);
	if (st == NULL) return ;
	void *map = get_memory_map(fd, st->st_size);
	if (map == NULL) return ;
	parse_elf_symbols(map, st);
	close(fd);
}

int	main(int ac, char **av)
{
	display_symbol_table("a.out");	
	return (0);
}
