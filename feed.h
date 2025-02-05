#ifndef FEED_H
#define FEED_H

#include "posts.h"

/*
 * Function that handles the calling of every command from task 3
 *
 * Please add any necessary parameters to the functions
 */
void handle_input_feed(char *input, int **mat, Node **posts, int nr_posts);

/*
functia de sortare aplica algoritmul bubble-sort pentr a face vectorul in
oridine crescatoare, functie carea ajuta la afisarea clicii in ordinea
id-urilor
*/
void sortare(int *v, int n);

/*
functia bron de determinare a celei mai mari clici intr-un graf, functia
functioneaza pe baza aflarii celei mai mari clici cu toate nodurile din multime
R, din multimea P poate sa aiba sau nu noduri, iar din X suntem siguri ca nu
avem noduri in clica, astfel cand multimile P si X sunt vide in R avem clica
maximala
*/
void max_clique(int *R, int R_size, int *P, int P_size, int *X, int X_size,
				int **mat, int *maxim, int **cliq);

/*
functia de clica imparte linia primita pentru comanda pentru a determina carui
user trebuie sa ii determinam clica maximala si initializeaza multimile pe care
le transmitem initial ca parametrii
*/
void clica(char *cmd, int **mat);

/*
pentru fiecare postare mai recenta decat ne dorim noi, vom verifica daca
apartine user-ului sau unui prieten de al lui, daca da o afisam
*/
void feed(char *cmd, int **mat, Node **posts, int nr_posts);

/*
se parcurge postarea transmisa ca parametru si se ia fiecare repost pentru
a verifica daca este facut de user-id cerut
*/
void dfs_view_profile(Node *repost, Node *post, int user_id);

/*
se verifica toate postarile si in caz de postarea a fost facuta de user-id pe
care il dorim o afisam si se mai parcurg inca o data postarile pentru a apela
functia anterioara si a determina doar daca user-id dorit a repostat sau nu.
trebuie sa parcurgem de 2 ori deoarece vrem sa afisam intai toate postarile si
apoi toate repostarile
*/
void view_profile(char *cmd, Node **posts, int nr_posts);

/*
pentru postarea pe care o dorim vom afisa doar reposturile care sunt facute de
prietenii user-idului
*/
void dfs_friends_repost(Node *post, int **mat, int user_id);

/*
aceasta functie este facuta pentru a determina exact ce postare vrem sa o
parcurgem
*/
void friends_repost(char *cmd, int **mat, Node **posts, int nr_posts);

#endif  // FEED_H
