/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:05:35 by dthan             #+#    #+#             */
/*   Updated: 2025/03/19 15:32:15 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>

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

off_t	get_file_size(int fd)
{
	struct stat file_stat;

	if (fstat(fd, &file_stat) == -1) {
		perror("fstat");
		return (-1);
	}
	return (file_stat.st_size);
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

void	display_symbol_table(char *file)
{
	int fd = get_file_descriptor(file);
	if (fd == -1) return ;
	printf("fd: %d\n", fd);
	off_t file_size = get_file_size(fd);
	if (file_size == -1) return ;
	printf("file_size: %lld\n", file_size);
	void *map = get_memory_map(fd, file_size);
	if (map == NULL) return ;
	printf("Symbol table\n");
	print_symbol();
	close(fd);
}

int	main(int ac, char **av)
{
	display_symbol_table("a.out");	
	return (0);
}
