#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "friends.h"
#include "users.h"

#define name_len 32

void adding_friend(char *cmd, int **mat)
{
	char *s1, *s2;
	char *token = strtok(cmd, "\n ");

	int count = 0;
	while(token)
	{
		count++;
		if(count == 2)
		{
			s1 = token;
		}
		else if(count == 3)
		{
			s2 = token;
		}

		token = strtok(NULL, "\n ");
	}

	int nr1 = get_user_id(s1);
	int nr2 = get_user_id(s2);

	mat[nr1][nr2] = mat[nr2][nr1] = 1;

	printf("Added connection %s - %s\n", s1, s2);
}

void remove_friend(char *cmd, int **mat)
{
	char *s1, *s2;
	char *token = strtok(cmd, "\n ");

	int count = 0;
	while(token)
	{
		count++;
		if(count == 2)
		{
			s1 = token;
		}
		else if(count == 3)
		{
			s2 = token;
		}

		token = strtok(NULL, "\n ");
	}

	int nr1 = get_user_id(s1);
	int nr2 = get_user_id(s2);

	mat[nr1][nr2] = mat[nr2][nr1] = 0;

	printf("Removed connection %s - %s\n", s1, s2);
}

void find_distance(char *cmd, int **mat)
{
	char *s1, *s2;
	char *token = strtok(cmd, "\n ");

	int count = 0;
	while(token)
	{
		count++;
		if(count == 2)
		{
			s1 = token;
		}
		else if(count == 3)
		{
			s2 = token;
		}

		token = strtok(NULL, "\n ");
	}

	int nr1 = get_user_id(s1);
	int nr2 = get_user_id(s2);

	int *queue = calloc(MAX_PEOPLE*MAX_PEOPLE, sizeof(int));
	int *dist = calloc(MAX_PEOPLE, sizeof(int));
	int st = 0;
	int dr = 0;
	queue[dr] = nr1;
	dist[nr1] = 1;

	while(st <= dr)
	{
		int nodv = queue[st];
		st++;

		for(int i = 0 ; i < MAX_PEOPLE ; i++)
		{
			if(!dist[i]  &&  mat[nodv][i])
			{
				dist[i] = dist[nodv]+1;
				queue[++dr] = i;
				
				if(i == nr2)
				{
					st = dr+1;
				}
			}
		}
	}

	if(!dist[nr2])
	{
		printf("There is no way to get from %s to %s\n", s1, s2);
	}
	else
	{
		printf("The distance between %s - %s is %d\n", s1, s2, dist[nr2]-1);
	}

	free(dist);
	free(queue);
}

void suggested(char *cmd, int **mat)
{
	char *s1;
	char *token = strtok(cmd, "\n ");

	int count = 0;
	while(token)
	{
		count++;
		if(count == 2)
		{
			s1 = token;
		}

		token = strtok(NULL, "\n ");
	}

	int nr1 = get_user_id(s1);

	int ok = 0;
	for(int i = 0 ; i < MAX_PEOPLE ; i++)
	{
		if(mat[nr1][i])
		{
			for(int j = 0 ; j < MAX_PEOPLE ; j++)
			{
				if(mat[i][j]  &&  j != nr1)
				{
					ok = 1;
				}
			}
		}
	}

	if(ok == 0)
	{
		printf("There are no suggestions for %s\n", s1);
	}
	else
	{
		printf("Suggestions for %s:\n", s1);
		int *visited = calloc(MAX_PEOPLE, sizeof(int));
		for(int i = 0 ; i < MAX_PEOPLE ; i++)
		{
			if(i != nr1)
			{
				for(int j = 0 ; j < MAX_PEOPLE ; j++)
				{
					if(mat[i][j]  &&  mat[j][nr1]  &&  !visited[i]  &&  !mat[nr1][i])
					{
						visited[i] = 1;
						printf("%s\n", get_user_name(i));
					}
				}
			}
		}

		free(visited);
	}
}

void common(char *cmd, int **mat)
{
	char *s1, *s2;
	char *token = strtok(cmd, "\n ");

	int count = 0;
	while(token)
	{
		count++;
		if(count == 2)
		{
			s1 = token;
		}
		else if(count == 3)
		{
			s2 = token;
		}

		token = strtok(NULL, "\n ");
	}

	int nr1 = get_user_id(s1);
	int nr2 = get_user_id(s2);

	int ok = 0;
	for(int i = 0 ; i < MAX_PEOPLE ; i++)
	{
		if(mat[nr1][i] == 1  &&  mat[nr2][i] == 1  &&
		   i != nr2  &&  i != nr1)
		{
			ok = 1;
		}
	}

	if(ok == 0)
		printf("No common friends for %s and %s\n", s1, s2);
	else
	{
		printf("The common friends between %s and %s are:\n", s1, s2);
		for(int i = 0 ; i < MAX_PEOPLE ; i++)
		{
			if(mat[nr1][i] == 1  &&  mat[nr2][i] == 1  &&
			i != nr2  &&  i != nr1)
			{
				printf("%s\n", get_user_name(i));
			}
		}
	}
}

int friends(int nr1, int **mat)
{
	int count = 0;
	for(int i = 0 ; i < MAX_PEOPLE ; i++)
	{
		if(mat[i][nr1])
		{
			count++;
		}
	}

	return count;
}

void how_many(char *cmd, int **mat)
{
	char *s1;
	char *token = strtok(cmd, "\n ");

	int count = 0;
	while(token)
	{
		count++;
		if(count == 2)
		{
			s1 = token;
		}

		token = strtok(NULL, "\n ");
	}

	int nr1 = get_user_id(s1);

	count = friends(nr1, mat);

	printf("%s has %d friends\n", s1, count);
}

void popular(char *cmd, int **mat)
{
	char *s1;
	char *token = strtok(cmd, "\n ");

	int count = 0;
	while(token)
	{
		count++;
		if(count == 2)
		{
			s1 = token;
		}

		token = strtok(NULL, "\n ");
	}

	int nr1 = get_user_id(s1);

	int maxim = friends(nr1, mat);
	int ind = nr1;

	for(int i = 0 ; i < MAX_PEOPLE ; i++)
	{
		if(mat[i][nr1])
		{
			int nr_friend = friends(i, mat);
			if(nr_friend > maxim)
			{
				maxim = nr_friend;
				ind = i;
			}
		}
	}

	if(ind == nr1)
	{
		printf("%s is the most popular\n", s1);
	}
	else
	{
		printf("%s is the most popular friend of %s\n", get_user_name(ind), s1);
	}
}

void handle_input_friends(char *input, int **mat)
{
	char *commands = strdup(input);
	char *cmd = strtok(commands, "\n ");

	if (!cmd)
		return;

	if (!strcmp(cmd, "add"))
		adding_friend(input, mat);

	else if (!strcmp(cmd, "remove"))
		remove_friend(input, mat);

	else if (!strcmp(cmd, "suggestions"))
		suggested(input, mat);

	else if (!strcmp(cmd, "distance"))
		find_distance(input, mat);

	else if (!strcmp(cmd, "common"))
		common(input, mat);

	else if (!strcmp(cmd, "friends"))
		how_many(input, mat);

	else if (!strcmp(cmd, "popular"))
		popular(input, mat);

	free(commands);
}