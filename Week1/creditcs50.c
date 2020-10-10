/*
EDMOND VUJICI CS50x 2020
*/

#include <stdio.h>
#include <cs50.h>

bool check_validity(long long credit_number);
int find_length(long long n);
bool checksum(long long ccn);
void print_credit_card_brand(long long ccn);
//functions' prototypes.
//fonksiyon protipleri.

int main(void)
{
    long long credit_number;
    //get credit card number.
    //kredi karti numarasi al.
    do
    {
        credit_number = get_long_long("Number: ");
        //cs50.h library's function get_long_long.
        //cs50.h kutuphanenin get_long_long fonksiyonu.
        
    }while(credit_number < 0);
    //check if number not smaller than 0.
    //numara 0'dan daha kucuk mu diye bakilir.

    if(check_validity(credit_number))
    //check if credit card valid.
    //kredi karti gecersiz olup olmadigina bakilir.
    {
        print_credit_card_brand(credit_number);
    }
    else
    {
        printf("INVALID\n");
    }

}
bool check_validity(long long credit_number)
{
    int len = find_length(credit_number);
    //gets the number of digits in credit card number.
    //kredi kartin rakam sayisi alinir.
    
    return (len == 15 || len == 13 || len == 16) && checksum(credit_number);
    //checks the sum of the credit cart digits (Luhn's Algorithm) and returns true or false.
    //Luhn Algoritma araciligyla kredi kartin gecerli olup olmadigina bakilir ona gore "true" ya da "false" degerine dondurur.
}
int find_length(long long n)
{
    //gets the number of digits in the credit card number by dividing the number by 10.
    //10'a bolerek kredi kartin rakam numarasina ulasilir.
    
    int len;
    for(len = 0; n!=0; n/=10, len++);
    return len;
}

bool checksum(long long ccn)
{
    int sum = 0;
    for(int i=0; ccn!= 0; i++, ccn/=10)
    {
    //checking every second number from last digit in credit card number.
    //sondan her ikinci rakama bakilir.
        if(i%2==0)
            sum+=ccn%10;
        else
        {
        //if number bigger than 10 get the two digits of the number.
        //eger numara 10'dan buyukse onun rakamlari alinip ekleniyor.
            int digit = 2 * (ccn%10);
            sum += digit/10 + digit%10;
        }
    }

    return (sum%10) == 0;
    //return true or false if the modulo of the sum is 0.
    //hesabin 10'la modu 0 ise true-false degeri dondur.
}
void print_credit_card_brand(long long ccn)
{
    if((ccn>=34e13 && ccn<35e13) || (ccn>=37e13 && ccn<38e13))
        printf("AMEX\n");
    else if((ccn>=51e14 && ccn<56e14))
        printf("MASTERCARD\n");
    //check numbers from 4000000000000 to 499999999999 to check card's company.
    // kartin cinsi bulmak icin 4000000000000 ve 499999999999 arasinda bulunup bulunmadigina bakilir.
    else if((ccn >= 4e12 && ccn<5e12) || (ccn >= 4e15 && ccn<5e15) )
        printf("VISA\n");
    else
        printf("INVALID\n");

}
