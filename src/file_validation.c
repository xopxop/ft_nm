/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:00:00 by dthan             #+#    #+#             */
/*   Updated: 2025/05/14 15:53:51 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <elf.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

static int      elf_check_x86(const int fd, int *is32, int *is64) {
	unsigned char e_ident[EI_NIDENT];

	if (read(fd, e_ident, EI_NIDENT) != EI_NIDENT)
                return 0;
	if (memcmp(e_ident, ELFMAG, SELFMAG) != 0)
	        return 0;
	*is32 = (e_ident[EI_CLASS] == ELFCLASS32);
	*is64 = (e_ident[EI_CLASS] == ELFCLASS64);
	return 1;
}

int	valid_file(const int fd)
{
	int is32;
	int is64;

	if (elf_check_x86(fd, &is32, &is64) == 0)
		return (0);
	if (!is32 && !is64)
                return (0);
	return (1);
}