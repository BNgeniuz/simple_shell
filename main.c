#include "shell.h"

/**
 * main - input entry points
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 (main file)
 */
int main(int argc, char **argv)
{
	info_t info[] = { INFO_INIT };
	int fdx = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fdx)
			: "r" (fdx));

	if (argc == 2)
	{
		fdx = open(argv[1], O_RDONLY);
		if (fdx == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(argv[0]);
				_eputs(": 0: Can't open ");
				_eputs(argv[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fdx;
	}
	populate_env_list(info);
	read_history(info);
	hsh(info, argv);
	return (EXIT_SUCCESS);
}
