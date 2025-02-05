#ifndef FRIENDS_H
#define FRIENDS_H

#define MAX_COMMAND_LEN 500
#define MAX_PEOPLE 550

/**
 * Function that handles the calling of every command from task 1
 *
 * Please add any necessary parameters to the functions
*/
void handle_input_friends(char *input, int **mat);

/*
pentru functia de add trimitem ca parametrii linia de comanda pe care o
impartim in 3, functia de add propriu-zisa si cele 2 nume, dupa ce am
obtinut numele , cu functia get_id gasim nr de ordine din baza de date
si adaugam muchiile astfel incat graful sa fie bidirectional
*/
void adding_friend(char *cmd, int **mat);

/*
pentru functia de revome trimitem ca parametrii linia de comanda pe care o
impartim in 3, functia de remove propriu-zisa si cele 2 nume, dupa ce am
obtinut numele , cu functia get_id gasim nr de ordine din baza de date
si stergem muchiile astfel incat graful sa ramana fie bidirectional
*/
void remove_friend(char *cmd, int **mat);

/*
aplicam algoritmul bfs dupa ce gasim id-urile pe care trebuie sa aplicam
algoritmul
*/
void find_distance(char *cmd, int **mat);

/*
cu un for-for vom verifica daca distanta dintre cele 2 persoane este de 2
*/
void suggested(char *cmd, int **mat);

/*
cu simplu for prin toata baza de date verificam dac exista o legatura intre
el si persoanele pe care le dorim noi
*/
void common(char *cmd, int **mat);

/*
pentru user-ul nostru vedem cati prieteni are in matricea de adiacenta prin
numararea aparitiei lui 1
*/
int friends(int nr1, int **mat);

/*
aceasta functie returneaza numarul de priteni al utilizatorului dorit,
diferenta fata de functia precedenta e ca aceasta functie prelucreaza linia
primita ca comanda
*/
void how_many(char *cmd, int **mat);

/*
pentru fiecare priten al unui user vom identifica care este cel cu cel mai
multi prieteni
*/
void popular(char *cmd, int **mat);

#endif // FRIENDS_H
