#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int main(int argc, string argv[])
{
    // Get the key to the cipher.
    // Sifrenin anahtarini al.
    string key = argv[1];
    
    if (argc != 2)
    {
        printf("Usage: ./vigenere keyword\n");
        return 1;
        //Be sure of right usage.
        //Dogru kullanimdan emin olun.
    }
    else
    {
        //Check that it is a letter key
        //Harften olusan anahtarin bulunup bulunmamasindan emin olun.
        for (int i = 0, n = strlen(key); i < n; i++)
        {
            if (isalpha(key[i]))
            {
            //the reason why empty - we just need it to skip.
            //eger harfse o zaman sadece atlamasi lazim, ondan dolayi bos.
            }
            else
            {   printf("Usage: ./vigenere keyword\n");
                return 1;
                //If all not letters, be sure of right usage.
                //Komut satirinda tum karakterler harf degilse, tekrar girdi iste.
            }
        } 
    }
    
    //Get the text to encrypt.
    //Sifrelemek uzere stringi al.
    string plntxt = get_string("plaintext: ");
    
    printf("ciphertext: ");
    if (plntxt != NULL)
    {
        //Encrypt and print.
        //Sifreleme ve yazdirma.
        for (int i = 0, j = 0, n = strlen(plntxt); i < n; i++, j++)
        {
        
            //if j has become bigger than the size of the key, start j from 0 to encode from beginning.
            //j anahtar uzunlugundan daha buyuk olduysa, sifirla ve sifrelenemyi bastan baslat.
            if (j > strlen(key) - 1)
            {
                j = 0;
            }
                int c = 0;
                //Check case of textual character
                //Assign it an alphabet number and encrypt
                if (isupper(plntxt[i]))
                {
                    //if plain text an uppercase letter use formula to cipher.
                    //eger buyuk harfse formulu kullan ve sifrele.
                    c = (((plntxt[i] - 65) + (tolower(key[j]) - 97))%26) + 65;
                    printf("%c", (char)c);
                }
                else if (islower(plntxt[i]))
                {
                    c = (((plntxt[i] - 97) + (tolower(key[j]) - 97))%26) + 97;
                    printf("%c", (char)c);
                }
                else
                {
                //if not letter, then print as it is.
                //eger harf degilse, oldugu gibi yazdir.
                    printf("%c", plntxt[i]);
                    j--;
                }
            }                             
        }
        printf("\n");
    
    return 0;
}
