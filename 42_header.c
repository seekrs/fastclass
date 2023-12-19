#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

#ifndef USER
# define USER "marvin"
# endif
#ifndef MAIL
# define MAIL "student.42.fr"
# endif

int	set_42_header(char *path, bool open_fd)
{
	time_t ltime = time(NULL);
	int fd;
	int amount;
	struct tm tstruct = *localtime(&ltime);
	char buf[24];

	fd = open(path, O_CREAT | O_WRONLY, 0644);
	if (fd == -1)
		return (-1);
	dprintf(fd, "/* ************************************************************************** */\n");
	dprintf(fd, "/*                                                                            */\n");
	dprintf(fd, "/*                                                        :::      ::::::::   */\n");
	dprintf(fd, "/*   ");
	amount = 50 - dprintf(fd, "%.*s", 43, path);
	while (amount--)
		dprintf(fd, " ");
	dprintf(fd, " :+:      :+:    :+:   */\n/*                                                    +:+ +:+         +:+     */\n");
	amount = 52 - dprintf(fd, "/*   By: %.*s <%.*s@%s>", 8, USER, 8, USER, MAIL);
	while (amount--)
		dprintf(fd, " ");
	dprintf(fd, "+#+  +:+       +#+        */\n");
	dprintf(fd, "/*                                                +#+#+#+#+#+   +#+           */\n");
	amount = dprintf(fd, "/*   Created: ");
	strftime(buf, 24, "%Y/%m/%d %T by ", &tstruct);
	amount += dprintf(fd, "%s%.*s", buf, 8, USER);
	amount = 55 - amount;
	while (amount--)
		dprintf(fd, " ");
	dprintf(fd, "#+#    #+#             */\n");
	amount = dprintf(fd, "/*   Updated: ");
	strftime(buf, 24, "%Y/%m/%d %T by ", &tstruct);
	amount += dprintf(fd, "%s%.*s", buf, 8, USER);
	amount = 54 - amount;
	while (amount--)
		dprintf(fd, " ");
	dprintf(fd, "###   ########.fr       */\n");
	dprintf(fd, "/*                                                                            */\n");
	dprintf(fd, "/* ************************************************************************** */\n\n");
	if (!open_fd)
		return (close(fd));
	return (fd);
}