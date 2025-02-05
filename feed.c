#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "feed.h"
#include "users.h"
#include "posts.h"

#define MAX_PEOPLE 550

void sortare(int *v, int n)
{
	int ok = 1;
	do
	{
		ok = 0;
		for (int i = 0 ; i < n - 1 ; i++)
		{
			if (v[i] > v[i + 1])
			{
				int t = v[i];
				v[i] = v[i + 1];
				v[i + 1] = t;
				ok = 1;
			}
		}
	} while (ok == 1);

	for (int i = 0 ; i < n ; i++)
	{
		printf("%s\n", get_user_name(v[i]));
	}
}

void max_clique(int *R, int R_size, int *P, int P_size, int *X, int X_size, 
				int **mat, int *maxim, int **cliq)
{
	if(P_size == 0  &&  X_size == 0)
	{
		if(R_size > *maxim)
		{
			for (int i = 0 ; i < R_size ; i++)
			{	
				(*cliq)[i] = R[i];
			}
			*maxim = R_size;
		}
	}
	else
	{
		for (int i = P_size-1 ; i >= 0; i--)
		{
			int nod = P[i];
 
			int *Rv = calloc(MAX_PEOPLE, sizeof(int));
			for (int j = 0 ; j < R_size ; j++)
			{
				Rv[j] = R[j];
			}
			int Rv_size = R_size;
			Rv[Rv_size++] = nod;
 
			int *N = calloc(MAX_PEOPLE, sizeof(int));
			int n = 0;
			for (int j = 0 ; j < MAX_PEOPLE ; j++)
			{
				if(mat[nod][j])
				{
					N[n++] = j;
				}
			}
 
			int *Pv = calloc(MAX_PEOPLE, sizeof(int));
			int Pv_size = 0;
			for (int j = 0 ; j < n ; j++)
			{
				for (int t = 0 ; t < P_size ; t++)
				{
					if(N[j] == P[t])
					{
						Pv[Pv_size++] = N[j];
					}
				}
			}
 
			int *Xv = calloc(MAX_PEOPLE, sizeof(int));
			int Xv_size = 0;
			for (int j = 0 ; j < n ; j++)
			{
				for (int t = 0 ; t < X_size ; t++)
				{
					if(N[j] == X[t])
					{
						Xv[Xv_size++] = N[j];
					}
				}
			}
 
			max_clique(Rv, Rv_size, Pv, Pv_size, Xv, Xv_size, mat, maxim, cliq);
 
			free(N);
			free(Xv);
			free(Pv);
			free(Rv);
 
			P_size--;
			X[X_size++] = nod;
		}
	}
}
 
void clica(char *cmd, int **mat)
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
 
	printf("The closest friend group of %s is:\n", s1);
 
	int *P = calloc(MAX_PEOPLE, sizeof(int));
	int P_size = 0;
 
	for (int i = 0 ; i < MAX_PEOPLE ; i++)
	{
		if (mat[nr1][i])
			P[P_size++] = i;
	}
 
	int *R = calloc(MAX_PEOPLE, sizeof(int));
	int R_size = 0;
	R[R_size++] = nr1;
 
	int *X = calloc(MAX_PEOPLE, sizeof(int));
	int X_size = 0;
 
	int maxim = 0;
	int *cliq = calloc(MAX_PEOPLE, sizeof(int));
	max_clique(R, R_size, P, P_size, X, X_size, mat, &maxim, &cliq);
 
	sortare(cliq, maxim);
 
	free(P);
	free(R);
	free(X);
	free(cliq);
}

void feed(char *cmd, int **mat, Node **posts, int nr_posts)
{
	char *s1;
	int nr_feed;
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
			nr_feed = atoi(token);
		}
 
		token = strtok(NULL, "\n ");
	}
 
	int nr1 = get_user_id(s1);
 
	for (int i = nr_posts - 1 ; i >= 0 ; i--)
	{
		if(posts[i]->id >= nr_posts-nr_feed)
		{
			if(posts[i]->user_id == nr1  ||  mat[nr1][posts[i]->user_id])
			{
				printf("%s: %s\n", get_user_name(posts[i]->user_id), posts[i]->titlu);
			}
		}
	}
 
}

void dfs_view_profile(Node *repost, Node *post, int user_id) {
	if(repost->user_id == user_id) {
			printf("Reposted: %s\n", post->titlu);
		}
	for (int i = 0; i < repost->events_number; i++) {
		dfs_view_profile(repost->events[i], post, user_id);
	}
}

void view_profile(char *cmd, Node **posts, int nr_posts) {
	char *s1 = NULL;
	char *token = strtok(cmd, "\n ");
	int count = 0;
	while (token) {
        count++;
        if (count == 2) {
            s1 = token;
		}
        token = strtok(NULL, "\n ");
    }
	int user_id = get_user_id(s1);
	for (int i = 0; i < nr_posts; i++) {
		if(posts[i]->user_id == user_id) {
			printf("Posted: %s\n", posts[i]->titlu);
		}
	}
	for (int i = 0; i < nr_posts; i++) {
		for (int j = 0; j < posts[i]->events_number; j++) {
			dfs_view_profile(posts[i]->events[j], posts[i], user_id);
		}
	}
		
}

void dfs_friends_repost(Node *post, int **mat, int user_id) {
	int friend_id = post->user_id;
	if(mat[user_id][friend_id]) 
		printf("%s\n", get_user_name(friend_id));
	for (int i = 0; i < post->events_number; i++) {
		dfs_friends_repost(post->events[i], mat, user_id);
	}
}

void friends_repost(char *cmd, int **mat, Node **posts, int nr_posts) {
	char *s1, *s2;
	char *token = strtok(cmd, "\n ");
	token = strtok(NULL, " \n");
    if (token) {
        s1 = token; 
        token = strtok(NULL, "\n");
        if (token) {
            s2 = token;
        }
    }
	int post_id = atoi(s2);
	int user_id = get_user_id(s1);
	Node *aux;
	int i = 0;
	for (i = 0; i < nr_posts; i++) {
		aux = posts[i];
		if(aux->id == post_id)
			break;
	}
	//printf("Friends that reposted:\n");
	dfs_friends_repost(posts[i], mat, user_id);
}

void handle_input_feed(char *input, int **mat, Node **posts, int nr_posts)
{
	char *commands = strdup(input);
	char *cmd = strtok(commands, "\n ");
 
	if (!cmd)
		return;
 
	if (!strcmp(cmd, "feed"))
		feed(input, mat, posts, nr_posts);
		// TODO: Add function
	else if (!strcmp(cmd, "view-profile"))
		view_profile(input, posts, nr_posts);
		// TODO: Add function
	else if (!strcmp(cmd, "friends-repost"))
		friends_repost(input, mat, posts, nr_posts);
		// TODO: Add function
	else if (!strcmp(cmd, "common-group"))
		clica(input, mat);
 
	free(commands);
}
