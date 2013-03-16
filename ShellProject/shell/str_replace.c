#include <stdlib.h>
#include <stdio.h>
#include <string.h>
// From : http://stackoverflow.com/questions/779875/what-is-the-function-to-replace-string-in-c
// You must free the result if result is non-NULL.
char* str_replace(char* orig, char* rep, char* with) {
    char* result; // the return string
    char* ins;    // the next insert point
    char* tmp;    // varies
    size_t len_rep;  // length of rep
    size_t len_with; // length of with
    size_t len_front; // distance between rep and end of last rep
    int count;    // number of replacements
	
	/* char* strstr(char const* s1, char const* s2);
	retourne un pointeur vers la première occurrence de s2 dans s1 
	(ou NULL si s2 n’est pas incluse dans s1). */	
	
    if (!orig)
        return NULL;
    if (!rep || !(len_rep = strlen(rep)))
        return NULL;
    if (!(ins = strstr(orig, rep)))
        return NULL;
    if (!with)
        with = "";
    len_with = strlen(with);

	/*	{	initialisation;
			while (condition) {
				Instructions
				mise_à_jour;
		} }*/
	// compte le nombre d'occurences de la chaîne à remplacer
    for (count = 0; (tmp = strstr(ins, rep)); ++count) {
        ins = tmp + len_rep;
    }
    
    // allocation de mémoire pour la nouvelle chaîne
    tmp = result = malloc(strlen(orig) + (len_with - len_rep) * count + 1);

    if (!result)
        return NULL;
	
	/* char* strcpy(char* dest, char const* src);
	copie la chaîne src dans la chaîne dest. Retourne dest.
	Attention ! aucune vérification de taille n’est effectuée ! */
	
	/* char* strncpy(char* dest, char const* src, size_t n);
	copie les n premiers caractères de src dans dest. Retourne dest.
	Attention ! n’ajoute pas le '\0' à la fin si src contient plus de n
	caractères !*/	
	
	// from here on,
    //    tmp points to the end of the result string
    //    ins points to the next occurrence of rep in orig
    //    orig points to the remainder of orig after "end of rep"
    while (count--) { // count évaluée, puis incrémentée
    // donc ici tant que count est > 0
        ins = strstr(orig, rep);
        len_front = ins - orig;
        tmp = strncpy(tmp, orig, len_front) + len_front;
        tmp = strcpy(tmp, with) + len_with;
        orig += len_front + len_rep; // move to next "end of rep"
    }
    strcpy(tmp, orig);
    return result;
}
