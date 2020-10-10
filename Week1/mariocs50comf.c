/*
EDMOND VUJICI CS50x 2020
*/


#include <stdio.h>
#include <cs50.h>

void print(char c, int n);
//function prototype.
//fonskiyon prototipi.

int main (void)
{
  int n;
  //pyramid's height.
  //piramidin yuksekligi.
  do 
  {
    n = get_int("Height: ");
    
  }while(n<1 || n>8);
  //do-while because loop will be executed at least once.
  //dongu en az bir kere calistiracagi icin do-while kullanilir.

  for (int i = 0; i < n ; i++)
  {
    print(' ', n - 1 - i);
    //first, print spaces n-1-i times.
    //ilk olarak bosluklari n-1-i kez yazdir.
    
    print('#', i + 1);
    //next print # i+1 times.
    //sonra i+1 kez kadar # yazdir.
    
    print(' ', 2);
    //print two space values to demosntrate the mario pyramid.
    //mario'nun piramidi sekli gosterebilmek icin iki bosluk yazdir.
    
    print('#', i + 1);
    //then continue with priting the other half of the task.
    //piramidin diger kismi yazdirmak icin.
    
    printf("\n");
    //to move to next row.
    //diger satira gecmek icin.

  }
  
}
void print(char c, int n)
{
  for(int i = 0; i < n; i++)
  {
    printf("%c", c);
  }
}
