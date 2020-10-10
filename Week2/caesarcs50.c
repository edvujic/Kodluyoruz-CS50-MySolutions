#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
//ctype.h is used for string, numerical etc. operations (i.e. translating a number into a string).
//ctype.h kutuphanesi stringler, sayisal islemler icin kullanilir, ornegin: bir stringin sayiyay donusturulumesi.
#include <stdlib.h>
#include <string.h>

bool check_key_valid(string key);
//function prototype.
//fonksiyon prototipi.

int main (int argc, string argv[])
{
//the reason we don't have void here is because argc gets the # of inputs in the command line, argv gets the arguments in the command line.
//argc komut satirinda kac kelimenin bulunduga dair, argv[] o kelimelere erismek icin kullanilir.


//if the key isn't available then show usage form.
//eger key orada bulunmuyorsa nasil kullanilmasina dair uyari ver.
    if(argc!=2 || !check_key_valid(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
            
        //return 1 is used to finish a program if the input is wrong, or any other action.
        //retunr 1 herhangi bir yanlis girdi ya da islem yapildiginda programi daha erken bitirmek icin kullanilir.
    }
    int key = atoi(argv[1]);
    //atoi is in ctype.h and is used to parse a numerical string to a number.
    //sayisal bir stringi intengere cevirmek icin atoi kullanilir.
    
    string plaintext = get_string("plaintext: ");
    //getting the string to be ciphered from the user.
    //kullanicidan sifrelemek uzere string isteniyor.

    printf("ciphertext: ");
    
   //strlen is used to find the string's length, it's in string.h
   //strlen stringin uzunlugunu bulmak icin kullanilir, string.h kutuphanesinde bulunan bir fonksiyon.
    for(int i=0, len = strlen(plaintext); i < len; i++)
    {
    //in order to achieve circular ciphering, we need to add numerical values of chars.
    //sirkuler (dairesel) sifrelemeye ulasmak icin ilk char'larin sayisal degerlerini ekliyoruz.
    
        char c = plaintext[i];
        //we take the charater of the string and parse it into a char.
        //stringi karakter karakter char'a pars ediyoruz.
        
        //isalpha checks is the char is a letter.
        //isalpha char'in harf olup olmadigina bakar.
        if (isalpha(c))
        {
            char m = 'A';
            //to cipher a uppercase letter we need to add the ASCII value of "A" to the normal letter.
            //buyuk harfleri sifrelemek uzere buyuk A'nin ASCII degerini eklememiz lazim.
            if(islower(c))
                m = 'a';
                //to cipher a lowercase letter we need to add the ASCII value of "a" to the normal letter.
                //kucuk harfleri sifrelemek uzere kucuk a'nin ASCII degerini eklememiz lazim.
                
            
            printf("%c", (c-m+key)%26 + m);
            //the formula that allows us circular ciphering.
            //dairesel sifrlemeyi saglayan formul.
        }
        else
            printf("%c", c);
            //if char not letter, then print normally.
            //eger char harf degilse oldugu gibi yazdirilir.
        
    }
    printf("\n");

}
bool check_key_valid(string key)
{   
//is used to control if given key is numerical.
//verilen anahtarin sayisal bir degere sahip olup olmadigina bakilir.

    for(int i=0, len = strlen(key); i<len; i++)
    {
        if(!isdigit(key[i]))
            return false;
            //if not numerical returns false;
            //sayisal bir degere sahip degilse false dondurur.
    }
        return true;
        //if numerical returns true.
        //sayisalsa true dondurur.
}
