/*
EDMOND VUJICI CS50x 2020
*/


//Explanations both in Turkish and English

//Insert the libraries that are needed.
//Gerekli olan kütüphaneleri ekle.
#include <stdio.h>
//used to used printf function.
//printf'i kullanmak için stdio.h eklememiz lazım.
#include <cs50.h>
//used to cs50 functions such as get_int, get_float etc.
//cs50'nin çeşitli fonskiyonları kullanmak için kullanılır (get_int, get_float) vs.

int main (void)
{
    //getting the name from the user
    //kullanıcının ismi alma
    string name = get_string("What is your name?\n");

    //printing user's name with a "hello" message.
    //kullanıcının ismiyle birlikte "hello" (merhaba) mesajını yazma.
    printf("hello, %s", name);
}
