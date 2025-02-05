/**
 * The entrypoint of the homework. Every initialization must be done here
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "users.h"
#include "friends.h"
#include "posts.h"
#include "feed.h"

#define MAX_POSTS 200
/**
 * Initializez every task based on which task we are running
*/
void init_tasks(void)
{
	#ifdef TASK_1

	#endif

	#ifdef TASK_2

	#endif

	#ifdef TASK_3

	#endif
}

void delete_post1(Node *posts) {
	if(posts == NULL)
		return;
	for (int i = 0; i < posts->events_number; i++) {
		delete_post1(posts->events[i]);
	}
	if(posts->titlu)
		free(posts->titlu);
	if(posts->persons_like)
		free(posts->persons_like);
	if (posts->events != NULL) {
        for (int i = 0; i < posts->events_number; i++) {
			if(posts->events[i])
            	free(posts->events[i]);
        }
        free(posts->events);
    }
}
/**
 * Entrypoint of the program, compiled with different defines for each task
*/
int main(void)
{
	int **mat = malloc(sizeof(int *) * MAX_PEOPLE);
	for (int i = 0 ; i < MAX_PEOPLE ; i++)
	{
		mat[i] = calloc(MAX_PEOPLE, sizeof(int));
	}

	Node **posts = (Node**)malloc(MAX_POSTS * sizeof(Node*));
	int nr_posts = 0, id_curent = 1;

	init_users();
	init_tasks();

	char *input = (char *)malloc(MAX_COMMAND_LEN);
	while (1) {
		char *command = fgets(input, MAX_COMMAND_LEN, stdin);

		// If fgets returns null, we reached EOF
		if (!command)
			break;

		#ifdef TASK_1
		handle_input_friends(input, mat);
		#endif

		#ifdef TASK_2
		handle_input_posts(input, posts, &nr_posts, &id_curent);
		(void)mat;
		#endif

		#ifdef TASK_3
		handle_input_feed(input, mat, posts, nr_posts);
		#endif
	}

	free_users();
	free(input);

	while(nr_posts != 0) {
		delete_post1(posts[nr_posts - 1]);
		free(posts[nr_posts - 1]);
		nr_posts--;
	}
	free(posts);

	for (int i = 0 ; i < MAX_PEOPLE ; i++)
	{
		free(mat[i]);
	}
	free(mat);

	(void)id_curent;
	return 0;
}