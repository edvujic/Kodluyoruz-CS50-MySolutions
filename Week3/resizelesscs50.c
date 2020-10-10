#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"
//to do manipulation on bitmap, we include bmp.h.
//bitmap resimlerde manipule etmek icin bmp.h kullaniriz.


int main(int argc, char* argv[])
{
//Be sure of proper usage.
//Kullanicinin dogru kullandigindan emin olun.
    if (argc != 4)
    {
        printf("Usage: ./copy infile outfile\n");
        return 1;
    }

    // be sure of proper scale_size usage.
    // dogru boyutlandirma tamsayi kullanimdan emin olun.
    int scale_size = atoi(argv[1]);
    
    if (scale_size < 1 || scale_size > 100)
    {
        printf("Scale must be between 1 and 100\n");
        return 1;
    }
    
    char* infile = argv[2];
    char* outfile = argv[3];

    //open infile.
    //infile'i ac.
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open outfile.
    // outfile'i ac.
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
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
    }
    
    // create outfile's BITMAPFILEHEADER and BITMAPINFOHEADER
    // outfile'nin BITMAPFILEHEADER'i ve BITMAPINFOHEADER'i olustur.
    BITMAPFILEHEADER out_bf = bf;
    BITMAPINFOHEADER out_bi = bi;
    
    // rescale the new dimension for the outfile
    // yeni boyutlari outfile icin hazirla
    out_bi.biWidth *= scale_size;
    out_bi.biHeight *= scale_size;

    // determine padding.
    // paddingleri ayarla.
    int in_padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int out_padding = (4 - (out_bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // determine the outfile biSizeImage and bfSize
    // outfile'nin biSizeImage ve bfSize (boyutunu) ayarla.
    out_bi.biSizeImage = abs(out_bi.biHeight) * (out_bi.biWidth * sizeof(RGBTRIPLE) + out_padding);
    out_bf.bfSize = (out_bi.biSizeImage + 54);
    
    //write down header info in the new outfile.
    //yeni outfile'a header bilgileri yazdir.
    fwrite(&out_bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    fwrite(&out_bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over bitmap matrix.
    // bitmap matirisi gezdir.
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        for (int j = 0; j < scale_size; j++)
        {
            // set pointer to beginning of line
            // baslangictaki isaretciyi ayarla.
            fseek(inptr, 54 + (bi.biWidth * 3 + in_padding) * i, SEEK_SET);
            
            //go over the pixels.
            //pixel'leri gezdir.
            for (int k = 0; k < bi.biWidth; k++)
            {
            
                //bmp.h allows us to use this type of structures to find the RGB values of the matrix values.
                //RGB degerleri cekmek icin bmp.h'te bulunan RGBTRIPLE veri tipini kullaniyoruz.
            
                  //read the bitmap as RGBTRIPLE.
                 //bitmap'i RGBTRIPLE olarak oku.
                RGBTRIPLE triple;
        
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                
                for (int l = 0; l < scale_size; l++)
                {
                    // write RGB triple to outfile.
                    // RGB'leri outfile'a yaz.
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            
            // add padding to outfile.
            // padding'i ekle.
            for (int y = 0; y < out_padding; y++)
            {
                fputc(0x00, outptr);
            }
        }
    }
    fclose(inptr);
    fclose(outptr);

    return 0;
}
