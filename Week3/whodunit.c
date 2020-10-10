#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"
//to do manipulation on bitmap, we include bmp.h.
//bitmap resimlerde manipule etmek icin bmp.h kullaniriz.

int main(int argc, char* argv[])
{
    //Be sure of proper usage.
    //Kullanicinin dogru kullandigindan emin olun.
    if (argc != 3)
    {
        printf("Usage: ./copy infile outfile\n");
        return 1;
    }

    //take the file that's gonna be deciphered in infile.
    //infile olarak desifrlemek uzere olan bitmap'i alin.
    char* infile = argv[1];
    
    //take the file that's gonna be deciphered in infile.
    //infile olarak desifrlemek uzere olan bitmap'i alin.
    char* outfile = argv[2];

    //open infile in reading mode.
    //infile'i okuma modunda ac.
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        //if file not present, stop the program
        //dosya mevcut degilse programi durdur.
        printf("Could not open %s.\n", infile);
        return 2;
    }

     //open outfile in write mode.
    //outfile'i yazma modunda ac.
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        //if file couldn't be made, stop the program.
        //eger outfile olusturulmadiysa, programi durdur.
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    //read the bitmaps header.
    //bitmapin header'in oku.
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    
    //read bitmap's info header.
    //bitmap'in info headerini oku.
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    //the headers that are read are used to se if the used file is an actual bitmap.
    //okunan header'ler gercekte dosyanin bir bitmap olup olmadigi icin bakilir.
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
        //if file not supported, stop program.
        //dosya uygun degilse, durdur.
    }

    //write down header info in the new outfile.
    //yeni outfile'a header bilgileri yazdir.
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    //make the padding.
    //padding'i ayarla.
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    //start reading the bitmap matrix.
    //bitmap matirisi okumaya basla.
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            RGBTRIPLE triple;
            //bmp.h allows us to use this type of structures to find the RGB values of the matrix values.
            //RGB degerleri cekmek icin bmp.h'te bulunan RGBTRIPLE veri tipini kullaniyoruz.
            
            //read the bitmap as RGBTRIPLE.
            //bitmap'i RGBTRIPLE olarak oku.

            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            if (triple.rgbtRed == 0xff)
            {
                //if one of the three colors of RGB are higher than 250 (white) make it black to get the message.
                //eger RGB reklerinden birisi 250'den daha fazla bir deger aliyorsa, onu siyah yap.
                triple.rgbtRed = 0x00;
            }

            //write down the new bitmap in the outfile.
            //yeni bitmapi olusturmak icin bilgilerini outfile'a yazdir.
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
        }

        
        fseek(inptr, padding, SEEK_CUR);
        //make the padding
        //padding'i ayarla.
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
    }

     //close the files.
    //dosyalari kapat.
    fclose(inptr);
    fclose(outptr);

    return 0;
}
