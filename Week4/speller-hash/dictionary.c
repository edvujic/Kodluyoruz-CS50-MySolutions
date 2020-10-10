//gerekli olan kutuphaneleri ekle.
//add necessary libraries.
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
//uretilmis olan kutuphaneyi ekle.
//add the new library.
#include "dictionary.h"

//dugumlerin prototipini olustur.
//make the nodes prototype.
typedef struct dugum
{
    char word[LENGTH+1];
    struct dugum* next;

}
dugum;



//dugumlerden olusan hash tablosunu olustur
//make the hashtable from nodes
dugum* hash_tablosu[26];


int hash_function(const char* word)
{
    return word[0] - 'a';

}
int dugum_sayisi = 0;

//denetleme yapmak icin.
//to make a check.
bool check(const char* word)

{


    char temp_word[LENGTH+1] = {'\0'};

    strcpy(temp_word, word);

    for(int i = 0; word[i] != '\0'; i++)

        temp_word[i] = tolower(word[i]);

    int temp_array = hash_function(temp_word);
    dugum* temp_dugum = hash_tablosu[temp_array];
    while(temp_dugum != NULL)
    {
        //eger strcpm 0 ise o zaman true dondur.
        //if strcmp 0 then it's true.
        if(strcmp(temp_word, temp_dugum->word) == 0)

            return true;



        //degilse devam dugumleri gezmeye devam.
        //if not continue going to other nodes.
        temp_dugum = temp_dugum->next;

    }


    //0 degilse demek ki bir sozlukte yok false dondur
    //if not 0 then it's not in the dictionary, return false.

    return false;

}


//sozlugu ac.
//open the dictionary.
bool load(const char* dictionary)

{


    FILE* fp = fopen(dictionary, "r");

    //sozluk var mi?
    //is it in the dictionary?
    if(dictionary == NULL)

        return false;

    char* string = malloc(sizeof(char)*(LENGTH+1));
    //sozluk dosyasini sonuna kadar gez.
    //go till the end of the dictionary.
    while (fscanf(fp, "%s", string) != EOF)

    {
        dugum* new_dugum = malloc(sizeof(dugum));

        strcpy(new_dugum->word, string);

        int hash_number = hash_function(string);

        new_dugum->next = hash_tablosu[hash_number];

        hash_tablosu[hash_number] = new_dugum;

        dugum_sayisi++;

    }
    //memoriyi bosalt.
    //free the memory.
    free(string);
    //dosyayi kapat.
    //close the files.
    fclose(fp);
    return true;

}


//dugum sayisini dondurmek icin kullanilir sadece
//used to get the number of words
unsigned int size(void)
{
    if(dugum_sayisi != 0)

        return dugum_sayisi;
        
    //eger yuklenmediyse sozluk o zaman hicbir kelimesi yok demek ondan dolayi 0 dondur.
    //if not loaded then dictionary empty, so return 0.
    return 0;

}
//memoriyi bosaltmak icin kullanilir.
//used to free memory.
bool unload(void)
{

    for(int i=0; i<27; i++)

    {

        dugum* temp_dugum_1 = hash_tablosu[i];
        while(temp_dugum_1 != NULL)

        {
            dugum* temp_dugum_2 = temp_dugum_1->next;

            free(temp_dugum_1);
            temp_dugum_1 = temp_dugum_2;

        }

    }

    return true;

}
