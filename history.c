#include "shell.h"

/**
 * get_history_file - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containg history file
 */

char *get_history_file(info_t *info)
{
	char *buf, *di;

	di = get_env(info, "HOME=");
	if (!di)
		return (NULL);
	buf = malloc(sizeof(char) * (str_len(di) + str_len(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	str_cpy(buf, di);
	str_cat(buf, "/");
	str_cat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_history - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_history(info_t *info)
{
	ssize_t fda;
	char *filenam = get_history_file(info);
	list_t *node = NULL;

	if (!filenam)
		return (-1);

	fda = open(filenam, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filenam);
	if (fda == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		put_sfd(node->str, fda);
		put_fd('\n', fda);
	}
	put_fd(BUF_FLUSH, fda);
	close(fda);
	return (1);
}

/**
 * read_history - reads history from file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_history(info_t *info)
{
	int a, las = 0, linecount = 0;
	ssize_t fda, rd_len, f_size = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	fda = open(filename, O_RDONLY);
	free(filename);
	if (fda == -1)
		return (0);
	if (!fstat(fda, &st))
		f_size = st.st_size;
	if (f_size < 2)
		return (0);
	buf = malloc(sizeof(char) * (f_size + 1));
	if (!buf)
		return (0);
	rd_len = read(fda, buf, f_size);
	buf[f_size] = 0;
	if (rd_len <= 0)
		return (free(buf), 0);
	close(fda);
	for (a = 0; a < f_size; a++)
		if (buf[a] == '\n')
		{
			buf[a] = 0;
			build_history_list(info, buf + las, linecount++);
			las = a + 1;
		}
	if (las != a)
		build_history_list(info, buf + las, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *nod = NULL;

	if (info->history)
		nod = info->history;
	add_node_end(&nod, buf, linecount);

	if (!info->history)
		info->history = nod;
	return (0);
}

/**
 * renumber_history - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int a = 0;

	while (node)
	{
		node->num = a++;
		node = node->next;
	}
	return (info->histcount = a);
}

