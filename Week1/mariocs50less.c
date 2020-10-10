/*
EDMOND VUJICI CS50x 2020
*/

#include <stdio.h>
#include <cs50.h>

void draw_a_piramide(int height);
//function prototype.
//fonksiyonun prototipi.

int main (void)
{
  bool number_check = false;
  //to check the number first assume that number is not valid.
  //girilen numarayi kontrol etmek icin ilk once numaranin yanlis oldugu varsayilir.
 
  int height;
  //number is gonna be entered as height of the pyramide.
  //girilen numara piramitin yuksekligi olarak belirlenir
  
  do{
     height = get_int("Height: "); 
     //using cs50.h library to use get_int function.
     //cs50.h kutuphanesi kullanarak kullanicidan sayi istemek uzere get_int fonskiyonu kullanilir.
     
     if (height <= 8 && height>=1) 
     //if number smaller than 1 or bigger than 8 number is invalid.
     //numara eger 1'den daha kucuk ya da 8'den daha buyuk ise gecersizdir.
     {
     
       number_check = true;
       //in contrary the number is right therefore we seet number_check boolean to true.
       //aksi halde numara gecerlidir ve ikili degere sahip olan number_check "true" degerine esitliyoruz.
       
     }
  }while(number_check == false);
  //use do-while because this loop is gonna be executed AT LEAST ONCE. If the number is wrong go to the beginning of loop.
  //do-while kullanilmanin nedeni de bu dongunun en az bir kere calistirilmasidir. Eger numara yanlis ise dongunun basina don.
  
  
  draw_a_piramide(height);
}
void draw_a_piramide(int height)
{
  int i, j;
  //gonna be used in loops.
  //dongulerde kullanilmak uzere tanimlandi.
  
  int definer = height-1;
  //definer is used to find where instead of # a space is gonna be printed. Because there won't be a row where there'll be all spaces, we go with "height-1"
  //definer (belirleyici) # yerine boslugun yazdirilacagi yeri belirlenmek icin kullanilacak. Sadece bosluklardan olusacak bir satirin olmayacagindan "height-1" degerine esitliyoruz.
  
  for(i= 0; i<height; i++)
  {
    for(j=0; j<height; j++)
    {
      if(j<definer)
        printf(" ");
        //if the definer is bigger than j print space.
        //eger definer j'den buyukse bosluk yazdir.
        
      else
      //if not print #.
      //aksi takdirde # yazdir.
        printf("#");
    }
    printf("\n");
    //to go to the next row we use "\n".
    //diger satira gecmek uzere "\n" kullanilir.
    
    definer--;
    //while j is going from 0 to height, definer is being decremented. This allows printing spaces and hashes in a piramide-like shape (leaning to right).
    //height sinir olmak uzere j 0'dan height'e büyüdükçe definer azaltılır. Böylece saga egimli bir piramit sekli ekrana yazdirilir.
  }
}
