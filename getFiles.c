#include "shell.h"

/**
  * get_files_loc - Get direction of the executable file
  * @track: path input
  * @file_title: an executable file name
  *
  * Return: 1 is executable file is located
  */

char *get_files_loc(char *track, char *file_title)
{
	char *track_cp, *token;
	struct stat file_track;
	char *track_buff = NULL;

	track_cp = strdup(track);
	token = strtok(track_cp, ":");

	while (token)
	{
		if (track_buff)
		{
			free(track_buff);
			track_buff = NULL;
		}
		track_buff = malloc(strlen(token) + strlen(file_title) + 2);
		if (!track_buff)
		{
			perror("Error: malloc fails");
			exit(EXIT_FAILURE);
		}
		strcpy(track_buff, token);
		strcat(track_buff, "/");
		strcat(track_buff, file_title);
		strcat(track_buff, "\0");

		if (stat(track_buff, &file_track) == 0 && access(track_buff, X_OK) == 0)
		{
			free(track_cp);
			return (track_buff);
		}
		token = strtok(NULL, ":");
	}
	free(track_cp);
	if (track_buff)
		free(track_buff);
	return (NULL);
}

/**
  * startswith_forwardslash - if file starts with "/"
  * @str: file name to be check for
  *
  * Return: 1 if yes, 0 if no
  */

int startswith_forwardslash(const char *str)
{
	if (str != NULL || str[0] == '/')
		return (1);

	return (0);
}



/**
  * get_files_path - functions to get the file path
  * @file_title: Argument name
  *
  * Return: 1 if successful
  */

char *get_files_path(char *file_title)
{
	char *track = getenv("PATH");
	char *full_track;


	if (startswith_forwardslash(file_title) &&
			access(file_title, X_OK) == 0)
		return (strdup(file_title));

	if (!track)
	{
		perror("track found not");
		return (NULL);
	}

	full_track = get_files_loc(track, file_title);

	if (full_track == NULL)
	{
		write(2, full_track, strlen(file_title));
		write(2, ": cmd found not\n", 19);
		return (NULL);
	}

	return (full_track);
}
