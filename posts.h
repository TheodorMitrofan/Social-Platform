#ifndef POSTS_H
#define POSTS_H

/*
int id - idul unic al postarii/repostului
char *titlu - titlul postarii, va fi NULL daca este repostare
int user_id - Id ul userului care a facut postarea / repostarea
int events_number - cate reposturi are o postare / repostare
int number_of_likes - cate likeuri are o postare / repostare
int *persons_like - un vector in care tinem minte de cate ori o 
persoana a dat 'like' la o postare be baza idului ei.
struct Node **events - vector de pointeri la structuri de acelasi
tip Node care reprezinta reposturile la o postare / repostare
*/
typedef struct Node {
    int id;
    char *titlu;
    int user_id;
    int events_number;
    int number_of_likes;
    int *persons_like;
    struct Node **events;
} Node;

/**
 * Function that handles the calling of every command from task 2
 *
 * Please add any necessary parameters to the functions
*/
void handle_input_posts(char *input, Node **posts, int *nr_posts, int *id_curent);

/*
pentru functia de create_post trimitem ca parametrii linia de comanda pe care o
impartim in 3, functia de create_post propriu-zisa, numele si titlul, dupa ce 
am obtinut numele obtinem idul userului. Alocam memorie pentru postare o punem 
in vectorul de postari si completam cu informatiile date. Id_curent se
incrementeaza la final
*/
void create_post(char *cmd, Node **posts, int *nr_posts, int *id_curent);

/*
se primeste postarea din care provine repostul si idul acestuia. Se cauta
prin postare pana se gaseste repostul si se returneaza
*/
Node* find_repost(Node* post, int repost_id);

/*
pentru functia de create_repost trimitem ca parametrii linia de comanda pe care
o impartim in 4, functia de create_repost propriu-zisa , numele, idul postului
si idul repostului. Daca nu exista un repost_id atunci se aloca un repost la
postul cu post_id. Daca postarea nu avea niciun repost se aloca vectorul de 
reposturi. Daca exista un repost_id atunci se cauta repostul si se aplica
acelasi rationament pentru vectorul sau de reposturi si se completeaza cu 
informatiile necesare
*/
void create_repost(char *cmd, Node **posts, int nr_posts, int *id_curent);

void dfs_print(Node *post, int contor);

void get_reposts(char *cmd, Node **posts, int nr_posts);

void like_post_or_repost(char *cmd, Node **posts, int nr_posts);

void get_likes(char *cmd, Node **posts, int nr_posts);

void dfs_ratio_max_likes(Node *post, int *max, int *indice);

void get_ratio(char *cmd, Node **posts, int nr_posts);

/*
se primeste o postare / repost pentru a le sterge si de asemenea
sa se stearga toate reposturile lor
*/
void delete_post(Node *posts);

Node* find_parinte(Node *parinte, int repost_id, int *indice);

/*
Pe baza parametrilor primiti se sterge postarea intreaga cu toate reposturile
sau repostul cerut cu reposturile ei. Daca se sterge toata postarea se
foloseste functia de delete_post pentru a elibera memoria si toate postarile
din vectorul de postari de la dreapta celui sters se muta cu indice in stanga
Daca se sterge un repost se gaseste parintele lui, se sterge repostul si il
initializam cu NULL.
*/
void delete(char *cmd, Node **posts, int *nr_posts);

void dfs_parinti(Node *node, int ant , int **parents);

void common_repost(char *cmd, Node **posts, int nr_posts);
#endif // POSTS_H
