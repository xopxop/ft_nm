/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:05:35 by dthan             #+#    #+#             */
/*   Updated: 2025/04/04 09:55:51 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <mach-o/loader.h>

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
	// what if file_stat.st_size == 0
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


// enum {
// 	absolute_value = "A",
// 	uninitialized_data_section = "B",
// 	common = "C",
// 	initialised_data_section = "D",
// 	an_initialised_data_section_for_small_objects = "G",
// 	debugging = "N",
// 	a_read_only_data_section = "R",
// 	an_uninitialized_data_section_for_small_objects = "S",
// 	text_code_section = "T",
// 	undefined = "U",
// 	a_weak_object = "V",
// 	"W" ,

// } e_global_symbol_type;

// enum {
// 	uninitialized_data_section = "b",
// 	initialised_data_section = "d",
// 	an_initialised_data_section_for_small_objects = "g",
// 	// "i"
// 	a_stack_unwind_section = "p",
// 	a_read_only_data_section = "r",
// 	an_uninitialized_data_section_for_small_objects = "s",
// 	text_code_section = "t",
// 	unique_global_symbol = "u",
// 	a_weak_object = "v",
// 	"w",
// 	"-",
// 	"?",

// } e_local_symbol_type;

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

}

char get_symbol_letter(sym)
{
	if (N_S)
}

void handle_macho_file(void *file_memory)
{
	// header
	struct mach_header_64 *header = (struct mach_header_64 *)file_memory;
	// load commands
	struct load_command *lc = (struct load_command *)(file_memory + sizeof(struct mach_header_64));
	
	for (int i = 0; i < header->ncmds; i++) {
		if (lc->cmd == LC_SYMTAB) {
			
		}
	}
	// symbol table
}


void handel_file(void *file_memory)
{
	uint32_t magic = *(uint32_t *)(file_memory);

	if (magic == MH_MAGIC_64)
		handle_macho_file();
	else
		printf(stderr, "Not a 64-bit Mach-O file\n");
}

void	display_symbol_table(char *file)
{
	struct stat *st;
	int fd = get_file_descriptor(file);
	if (fd == -1) return ;
	st = get_file_stat(fd);
	if (st == NULL) return ;
	void *file_memory = get_memory_map(fd, st->st_size);
	if (file_memory == NULL) return ;
	handle_file(file_memory);
	munmap(file_memory, st->st_size);
	close(fd);
}


#define N_UNDF 0x0
#define N_ABS 0x2
#define N_SECT 0xe
#define N_PBUD 0xc
#define N_INDR 0xa
#define N_STAB 0xe0
#define N_PEXT 0x10
#define N_TYPE 0x0e
#define N_EXT 0x1

char	get_symbol_letter(sym)
{
	
}


int	main(int ac, char **av)
{
	display_symbol_table("a.out");	
	return (0);
}
