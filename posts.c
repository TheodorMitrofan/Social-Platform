#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "users.h"
#include "posts.h"

#define MAX_POSTS 200
#define MAX_TITLU 280
#define MAX_PEOPLE 550

Node* find_repost(Node* post, int repost_id) {
	if(post->id == repost_id)
		return post;
	for (int i = 0; i < post->events_number; i++) {
			if(post->events[i]) {
				Node* repost = find_repost(post->events[i], repost_id);
        		if (repost != NULL) {
            		return repost;
       			}
			}   
    }
	(void) post;
	(void) repost_id;
	return NULL;
}

void create_post(char *cmd, Node **posts, int *nr_posts, int *id_curent) {
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
	int user_id = get_user_id(s1);
	posts[(*nr_posts)] = (Node*)malloc(sizeof(Node));
	posts[(*nr_posts)]->id = *id_curent;
	posts[(*nr_posts)]->events_number = 0;
	posts[(*nr_posts)]->events = NULL;
	posts[(*nr_posts)]->user_id = user_id;
	posts[(*nr_posts)]->number_of_likes = 0;
	posts[(*nr_posts)]->persons_like = (int*)calloc(MAX_PEOPLE, sizeof(int));

	posts[*nr_posts]->titlu = strdup(s2);
	(*nr_posts)++;
	(*id_curent)++;
	printf("Created %s for %s\n", s2, s1);
}

void create_repost(char *cmd, Node **posts, int nr_posts, int *id_curent) {
	char *s1, *s2, *s3 = NULL;
	char *token = strtok(cmd, "\n ");
	int count = 0;
	while (token) {
        count++;
        if (count == 2) {
            s1 = token;
        }
        if (count == 3) {
            s2 = token;
        }
		if (count == 4) {
			s3 = token;
		}
        token = strtok(NULL, "\n ");
    }
	Node *aux;
	int user_id = get_user_id(s1);
	int id = atoi(s2);
	int i = 0;
	for (i = 0; i < nr_posts; i++) {
		aux = posts[i];
		if(aux->id == id)
			break;
	}
	if (s3 == NULL) 
	{   // repost la post
			if(aux->events_number == 0)
				aux->events = (Node**)malloc(MAX_POSTS * sizeof(Node*));
			aux->events[aux->events_number] = (Node*)malloc(sizeof(Node));
			aux->events[aux->events_number]->id = *id_curent;
			aux->events[aux->events_number]->user_id = user_id;
			aux->events[aux->events_number]->titlu = NULL;
			aux->events[aux->events_number]->events = NULL;
			aux->events[aux->events_number]->events_number = 0;
			aux->events[aux->events_number]->number_of_likes = 0;
			aux->events[aux->events_number]->persons_like = (int*)calloc(MAX_PEOPLE, sizeof(int));
			aux->events_number++;
	} else {  // repost la repost
		int repost_id = atoi(s3);
		aux = find_repost(posts[i], repost_id);
		if(aux->events_number == 0)
				aux->events = (Node**)malloc(MAX_POSTS * sizeof(Node*));
			aux->events[aux->events_number] = (Node*)malloc(sizeof(Node));
			aux->events[aux->events_number]->id = *id_curent;
			aux->events[aux->events_number]->user_id = user_id;
			aux->events[aux->events_number]->titlu = NULL;
			aux->events[aux->events_number]->events = NULL;
			aux->events[aux->events_number]->events_number = 0;
			aux->events[aux->events_number]->number_of_likes = 0;
			aux->events[aux->events_number]->persons_like = (int*)calloc(MAX_PEOPLE, sizeof(int));
			aux->events_number++;
	}
			
	printf("Created repost #%d for %s\n", *id_curent, s1);
	(*id_curent)++;
}

void dfs_print(Node *post, int contor) {
	
	if(contor == 1) {
		printf("%s - Post by %s\n", post->titlu, get_user_name(post->user_id));
	}

	if(contor == 0) {
		if(post)
			printf("Repost #%d by %s\n", post->id, get_user_name(post->user_id));
	}
	for (int i = 0; i < post->events_number; i++) {
		if(post->events[i])
			dfs_print(post->events[i], 0);
	}
}

void get_reposts(char *cmd, Node **posts, int nr_posts) {
	char *s1, *s2 = NULL;
	char *token = strtok(cmd, "\n ");
	int count = 0;
	while (token) {
        count++;
        if (count == 2) {
            s1 = token;
        }
        if (count == 3) {
            s2 = token;
        }
        token = strtok(NULL, "\n ");
    }
	Node *aux;
	int id = atoi(s1);
	int i = 0;
	for (i = 0; i < nr_posts; i++) {
		aux = posts[i];
		if(aux->id == id)
			break;
	}
	if(s2 == NULL) {  //print la toata postarea
		dfs_print(aux, 1);
	} else {
		int repost_id = atoi(s2);
		aux = find_repost(posts[i], repost_id);
		dfs_print(aux, 0);
	}
}

void like_post_or_repost(char *cmd, Node **posts, int nr_posts) {
	char *s1, *s2, *s3 = NULL;
	char *token = strtok(cmd, "\n ");
	int count = 0;
	while (token) {
        count++;
        if (count == 2) {
            s1 = token;
        }
        if (count == 3) {
            s2 = token;
        }
		if (count == 4) {
			s3 = token;
		}
        token = strtok(NULL, "\n ");
    }
	Node *aux;
	int user_id = get_user_id(s1);
	int post_id = atoi(s2);
	int i = 0;
	for (i = 0; i < nr_posts; i++) {
		aux = posts[i];
		if(aux->id == post_id)
			break;
	}
	if(s3 == NULL) {
		if(aux->persons_like[user_id] % 2 == 0) {
			aux->number_of_likes++;
			printf("User %s liked post %s\n", s1, posts[i]->titlu);
		}
		else{
			aux->number_of_likes--;
			printf("User %s unliked post %s\n", s1, posts[i]->titlu);
			} 	
		} else {
		int repost_id = atoi(s3);
		aux = find_repost(posts[i], repost_id);
		if(aux->persons_like[user_id] % 2 == 0) {
			printf("User %s liked repost %s\n", s1, posts[i]->titlu);
			aux->number_of_likes++;
		} else {
			printf("User %s unliked repost %s\n", s1, posts[i]->titlu);
			aux->number_of_likes--;
		}
	}
	aux->persons_like[user_id]++;
}

void get_likes(char *cmd, Node **posts, int nr_posts) {
	char *s1, *s2 = NULL;
	char *token = strtok(cmd, "\n ");
	int count = 0;
	while (token) {
        count++;
        if (count == 2) {
            s1 = token;
        }
        if (count == 3) {
            s2 = token;
        }
        token = strtok(NULL, "\n ");
    }
	Node *aux;
	int post_id = atoi(s1);
	int i = 0;
	for (i = 0; i < nr_posts; i++) {
		aux = posts[i];
		if(aux->id == post_id)
			break;
	}
	if(s2 == NULL) {
		printf("Post %s has %d likes\n", aux->titlu, aux->number_of_likes);
	} else {
		int repost_id = atoi(s2);
		aux = find_repost(posts[i], repost_id);
		printf("Repost #%d has %d likes\n", aux->id, aux->number_of_likes);
	}
}

void dfs_ratio_max_likes(Node *post, int *max, int *indice) {
	if(post->number_of_likes > *max)
	{
		*max = post->number_of_likes;
		if(*indice < post->id)
			*indice = post->id;
	}
	for (int i = 0; i < post->events_number; i++) {
		if(post->events[i])
			dfs_ratio_max_likes(post->events[i], max, indice);
	}
		
}

void get_ratio(char *cmd, Node **posts, int nr_posts) {
	char *s1;
	char *token = strtok(cmd, "\n ");
	int count = 0;
	while (token) {
        count++;
        if (count == 2) {
            s1 = token;
        }
        token = strtok(NULL, "\n ");
    }
	Node *aux;
	int post_id = atoi(s1);
	int i = 0;
	for (i = 0; i < nr_posts; i++) {
		aux = posts[i];
		if(aux->id == post_id)
			break;
	}
	int max = 0, indice = 0;
	dfs_ratio_max_likes(aux, &max, &indice);
	if(max == aux->number_of_likes) {
		printf("The original post is the highest rated\n");
	} else {
		printf("Post %d got ratio'd by repost %d\n", aux->id, indice);
	}
}

void delete_post(Node *posts) {
	if(posts == NULL)
		return;
	for (int i = 0; i < posts->events_number; i++) {
		delete_post(posts->events[i]);
	}
	if(posts->titlu)
		free(posts->titlu);
	free(posts->persons_like);
	if (posts->events != NULL) {
        for (int i = 0; i < posts->events_number; i++) {
            free(posts->events[i]);
        }
        free(posts->events);
    }
}

Node* find_parinte(Node *parinte, int repost_id, int *indice) {
	for (int i = 0; i < parinte->events_number; i++) {
		if(parinte->events[i])
			if (parinte->events[i]->id == repost_id) {
				return parinte;
				*indice = i;
			}
		if(parinte->events[i]) {
			Node *result = find_parinte(parinte->events[i], repost_id, indice);
        	if (result != NULL) {
           		return result;
			}
		}
	}
	return NULL;
}

void delete(char *cmd, Node **posts, int *nr_posts) {
	char *s1, *s2 = NULL;
	char *token = strtok(cmd, "\n ");
	int count = 0;
	while (token) {
        count++;
        if (count == 2) {
            s1 = token;
        }
        if (count == 3) {
            s2 = token;
        }
        token = strtok(NULL, "\n ");
    }
	Node *aux;
	int post_id = atoi(s1);
	int i = 0;
	for (i = 0; i < *nr_posts; i++) {
		aux = posts[i];
		if(aux->id == post_id)
			break;
	}
	(void)s2;
	if(s2 == NULL) {
		printf("Deleted %s\n", aux->titlu);
		delete_post(posts[i]);
		for (int j = i; j < *nr_posts - 1; j++)
			posts[j] = posts[j + 1];
		posts[*nr_posts - 1] = NULL;
		(*nr_posts)--;
	} else {
		int repost_id = atoi(s2);
		aux = find_repost(posts[i], repost_id);
		printf("Deleted repost #%d of post %s\n", repost_id, posts[i]->titlu);
		int indice = 0;
		Node *parinte = find_parinte(posts[i], repost_id, &indice);
		delete_post(aux);
		free(parinte->events[indice]);
		parinte->events[indice] = NULL;
	}
}

void dfs_parinti(Node *node, int ant , int **parents) {
    (*parents)[node->id] = ant;
	for (int i = 0; i < node->events_number; i++) {
		if(node->events[i])
			dfs_parinti(node->events[i], node->id, parents);
	}
}

void common_repost(char *cmd, Node **posts, int nr_posts) {
	char *s1, *s2, *s3 = NULL;
	char *token = strtok(cmd, "\n ");
	int count = 0;
	while (token) {
        count++;
        if (count == 2) {
            s1 = token;
        }
        if (count == 3) {
            s2 = token;
        }
		if (count == 4) {
			s3 = token;
		}
        token = strtok(NULL, "\n ");
    }
	int post_id = atoi(s1);
	int i = 0;
	Node *aux;
	for (i = 0; i < nr_posts; i++) {
		aux = posts[i];
		if(aux->id == post_id)
			break;
	}
	int repost_id1 = atoi(s2); 
	int repost_id2 = atoi(s3);
	int *parinti = (int*)calloc(MAX_PEOPLE, sizeof(int));
	dfs_parinti(posts[i], 0, &parinti);
	int aux1 = parinti[repost_id1];
	int aux2 = parinti[repost_id2];
	int *parinti1 = (int*)calloc(MAX_PEOPLE, sizeof(int));
	int *parinti2 = (int*)calloc(MAX_PEOPLE, sizeof(int));

	i = 0;
	while (aux1 != 0) {
		parinti1[i++] = aux1;
		aux1 = parinti[aux1];
    }
	parinti1[i++] = 0;

	int j = 0;
	while (aux2 != 0) {
		parinti2[j++] = aux2;
		aux2 = parinti[aux2];
    }
	parinti2[j++] = 0;

	i--;
	j--;
	while(i >=0  &&  j >= 0  &&  parinti1[i] == parinti2[j]) {
		i--;
		j--;
	}
	
	if(i == -1  &&  j == -1)
	{
		printf("The first common repost of %d and %d is %d\n", repost_id1, repost_id2, parinti2[0]);
	}
	else if(i == -1)
	{
		if(parinti2[j] == repost_id1)
			printf("The first common repost of %d and %d is %d\n", repost_id1, repost_id2, parinti2[j]);
		else
			printf("The first common repost of %d and %d is %d\n", repost_id1, repost_id2, parinti2[j+1]);
	}
	else if(j == -1)
		if(parinti1[i] == repost_id2)
			printf("The first common repost of %d and %d is %d\n", repost_id1, repost_id2, parinti1[i]);
		else
			printf("The first common repost of %d and %d is %d\n", repost_id1, repost_id2, parinti1[i+1]);

	else
		printf("The first common repost of %d and %d is %d\n", repost_id1, repost_id2, parinti1[i+1]);
	
	free(parinti);
	free(parinti1);
	free(parinti2);
}

void handle_input_posts(char *input, Node **posts, int *nr_posts, int *id_curent)
{
	char *commands = strdup(input);
	char *cmd = strtok(commands, "\n ");
	if (!cmd)
		return;

	if (!strcmp(cmd, "create"))
		create_post(input, posts, nr_posts, id_curent);

	else if (!strcmp(cmd, "repost"))
		create_repost(input, posts, *nr_posts, id_curent);
		
	else if (!strcmp(cmd, "common-repost"))
		common_repost(input, posts, *nr_posts);

	else if (!strcmp(cmd, "like"))
		like_post_or_repost(input, posts, *nr_posts);

	else if (!strcmp(cmd, "ratio"))
		get_ratio(input, posts, *nr_posts);

	else if (!strcmp(cmd, "delete"))
		delete(input, posts, nr_posts);

	else if (!strcmp(cmd, "get-likes"))
		get_likes(input, posts, *nr_posts);

	else if (!strcmp(cmd, "get-reposts"))
		get_reposts(input, posts, *nr_posts);
			
	else if (!strcmp(cmd, "get-likes"))
		(void)cmd;
		// TODO: Add function

	free(commands);
}

