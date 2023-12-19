#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <errno.h>

#define HEADER 0u
#define PRINT_CONSTRUCTOR 1u
#define STATIC_CLASS 2u
#define has_flag(flags, flag) (flags >> flag & 1)

int	set_42_header(char *path, bool open_fd);

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

void	create_class(char *filename, char *name, unsigned int flags)
{
	char *upper = ft_toupper(name);
	int fd;

	if (has_flag(flags, HEADER))
		fd = set_42_header(filename, true);
	else
		fd = open(filename, O_CREAT | O_WRONLY, 0644);
	dprintf(fd, "#ifndef __%s__\n", upper); 
	dprintf(fd, "# define __%s__\n", upper);
	dprintf(fd, "\nclass %s\n", name);
	dprintf(fd, "{\n\tpublic:\n");
	if (!has_flag(flags, STATIC_CLASS))
		dprintf(fd, "\t\t%s(void);\n\t\t~%s(void);\n\t\t%s(%s &copy);\n\t\t%s& operator=(const %s& x);\n", name, name, name, name, name, name);
	else
		dprintf(fd, "\t\t~%s(void);\n", name);
	dprintf(fd, "\tprivate:\n");
	if (has_flag(flags, STATIC_CLASS))
		dprintf(fd, "\t\t%s(void);\n\t\t%s(%s &copy);\n\t\t%s& operator=(const %s& x);\n", name, name, name, name, name);
	dprintf(fd, "\n};\n\n#endif");
	free(upper);
	close(fd);
}

void	create_cpp(char *filename, char *name, unsigned int flags)
{
	int fd;

	if (has_flag(flags, HEADER))
		fd = set_42_header(filename, true);
	else
		fd = open(filename, O_CREAT | O_WRONLY, 0644);
	dprintf(fd, "#include \"%s.hpp\"\n", (name));
	if (has_flag(flags, PRINT_CONSTRUCTOR))
		dprintf(fd, "#include <iostream>\n");
	dprintf(fd, "\n%s::%s(void)\n{\n", name, name);
	if (has_flag(flags, PRINT_CONSTRUCTOR))
		dprintf(fd, "\tstd::cout << \"%s Constructor called\" << std::endl;", name);
	dprintf(fd, "\n}\n\n%s::~%s(void)\n{\n", name, name);
	if (has_flag(flags, PRINT_CONSTRUCTOR))
		dprintf(fd, "\tstd::cout << \"%s Destructor called\" << std::endl;", name);
	dprintf(fd, "\n}\n\n%s::%s(%s &copy)\n{\n", name, name, name);
	if (has_flag(flags, PRINT_CONSTRUCTOR))
		dprintf(fd, "\tstd::cout << \"%s Copy constructor called\" << std::endl;\n", name);
	dprintf(fd, "\t*this = copy;\n}\n\n%s& %s::operator=(const %s& x)\n{\n", name, name, name);
	if (has_flag(flags, PRINT_CONSTRUCTOR))
		dprintf(fd, "\tstd::cout << \"Copy assignment operator called\" << std::endl;\n");
	dprintf(fd, "\treturn (*this);\n}\n");
	close(fd);
}

void print_help(void)
{
	printf("USAGE : \e[1mclass\e[m [-fps] [FILE] ...\n");
	printf("FLAGS USAGE :\n");
	printf("\t\e[1m-h\e[m : prints this help\n");
	printf("\t\e[1m-f\e[m : create the class with the 42 header with the USER and MAIL defines\n");
	printf("\t\e[1m-p\e[m : create the class with std::cout output for constructors and destructors\n");
	printf("\t\e[1m-s\e[m : create the class as a static class, making all constructors privates\n");
}

int main(int argc, char **argv)
{
	char *name;
	unsigned int flags = 0;

	if (argc == 1)
	{
		print_help();
		return (0);
	}
	argv++;
	while (strlen(*argv) >= 2 && **argv == '-')
	{
		if (strchr(*argv, 'h') && strlen(*argv) == 2)
		{
			print_help();
			return 0;
		}
		if (strchr(*argv, 's'))
			flags |= (1 << STATIC_CLASS);
		if (strchr(*argv, 'p'))
			flags |= (1 << PRINT_CONSTRUCTOR);
		if (strchr(*argv, 'f'))
			flags |= (1 << HEADER);
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
			create_class(name, *argv, flags);
			printf("created %s successfully\n", name);
		}
		name[strlen(*argv) + 1] = 'c';
		if (access(name, F_OK) == 0)
			dprintf(2, "WARNING : %s already exists, aborting\n", name);
		else
		{
			create_cpp(name, *argv, flags);
			printf("created %s successfully\n", name);
		}
		free(name);
		argv++;
	}
	return (0);
}