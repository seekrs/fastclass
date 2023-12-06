#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <errno.h>

#ifndef USER
# define USER "marvin"
# endif
#ifndef MAIL
# define MAIL "student.42.fr"
# endif

void	set_42_header(char *path)
{
	time_t ltime = time(NULL);
	int fd;
	int amount;
	struct tm tstruct = *localtime(&ltime);
	char buf[24];

	fd = open(path, O_CREAT | O_WRONLY, 0644);
	if (fd == -1)
		return ;
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
	close(fd);
}

char *ft_toupper(char *str)
{
	char *buf;
	unsigned int i;

	buf = calloc(sizeof(char), strlen(str) + 1);
	for (i = 0; i < strlen(str); i++)
		buf[i] = toupper(str[i]);
	buf[i] = 0;
	return (buf);
}

void	create_class(char *name, int fd)
{
	char *upper = ft_toupper(name);
	dprintf(fd, "#ifndef %s_H\n# define %s_H\n\nclass %s\n{\n\tpublic:\n\t\t%s(void);\n\t\t~%s(void);\n\t\t%s(%s &copy);\n\t\t%s& operator=(const %s& x);\n\tprivate:\n\n};\n\n#endif", upper, upper, name, name, name, name, name, name, name);
	free(upper);
}

void	create_cpp(char *name, int fd, bool print)
{
	dprintf(fd, "#include \"%s.hpp\"\n", (name));
	if (print)
		dprintf(fd, "#include <iostream>\n");
	dprintf(fd, "\n%s::%s(void)\n{\n", name, name);
	if (print)
		dprintf(fd, "\tstd::cout << \"%s Constructor called\" << std::endl;", name);
	dprintf(fd, "\n}\n\n%s::~%s(void)\n{\n", name, name);
	if (print)
		dprintf(fd, "\tstd::cout << \"%s Destructor called\" << std::endl;", name);
	dprintf(fd, "\n}\n\n%s::%s(%s &copy)\n{\n", name, name, name);
	if (print)
		dprintf(fd, "\tstd::cout << \"%s Copy constructor called\" << std::endl;\n", name);
	dprintf(fd, "\t*this = copy;\n}\n\n%s& %s::operator=(const %s& x)\n{\n", name, name, name);
	if (print)
		dprintf(fd, "\tstd::cout << \"Copy assignment operator called\" << std::endl;\n");
	dprintf(fd, "\treturn (*this);\n}\n");
}

void print_help(void)
{
	printf("USAGE : \e[1mclass\e[m [-fp] [FILE] ...\n");
	printf("FLAGS USAGE :\n");
	printf("\t\e[1m-h\e[m : prints this help\n");
	printf("\t\e[1m-f\e[m : create the class with the 42 header with the USER and MAIL defines\n");
	printf("\t\e[1m-p\e[m : create the class with std::cout output for constructors and destructors\n");
}

int main(int argc, char **argv)
{
	char *name;
	int fd;
	bool header = false;
	bool print = false;

	if (argc == 1)
	{
		print_help();
		return (0);
	}
	argv++;
	if (strlen(*argv) >= 2 && **argv == '-')
	{
		if (strchr(*argv, 'h') && strlen(*argv) == 2)
		{
			print_help();
			return 0;
		}
		if (strchr(*argv, 'f'))
			header = true;
		if (strchr(*argv, 'p'))
			print = true;
		argv++;
	}
	while (*argv && strlen(*argv) > 0)
	{
	name = calloc(sizeof(char), strlen(*argv) + 5);
	name = strcat(name, *argv);
	name = strcat(name, ".hpp");
	if (access(name, F_OK) == 0)
		dprintf(2, "WARNING : %s already exists, trying to make .cpp\n", name);
	else
	{
		if (header)
		{
			set_42_header(name);
			fd = open(name, O_APPEND | O_WRONLY, 0644);
		}
		else
			fd = open(name, O_CREAT | O_WRONLY, 0644);
		if (fd == -1)
		{
			printf("%s\n", strerror(errno));
			dprintf(STDERR_FILENO, "Error : Couldn't open %s", name);
			free(name);
			return (-1);
		}
		create_class(*argv, fd);
		close(fd);
		printf("created %s successfully\n", name);
	}
	name[strlen(*argv) + 1] = 'c';
	if (access(name, F_OK) == 0)
		dprintf(2, "WARNING : %s already exists, aborting\n", name);
	else
	{
		if (header)
		{
			set_42_header(name);
			fd = open(name, O_APPEND | O_WRONLY, 0644);
		}
		else
			fd = open(name, O_CREAT | O_WRONLY, 0644);
		if (fd == -1)
		{
			printf("%s\n", strerror(errno));
			dprintf(STDERR_FILENO, "Error : Couldn't open %s", name);
			free(name);
			return (-1);
		}
		create_cpp(*argv, fd, print);
		close(fd);
		printf("created %s successfully\n", name);
	}
	free(name);
	argv++;
	}
	return (0);
}