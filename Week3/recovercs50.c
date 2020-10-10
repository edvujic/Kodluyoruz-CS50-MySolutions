#include<stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
    //be sure of right usage.
    //dogru kullanimdan emin olun.
    if (argc != 2)
    {
        printf( "Please enter file to open.\n");
        return 1;
    }
    //open file in reading mode from argv.
    //argv'den alinan dosyayi okuma modunda ac.
    FILE *file=fopen(argv[1],"r");
    
    //if file not present.
    //eger dosya mevcut degilse.
    if(file == NULL) 
    {
        printf("not a file\n");
    }

    int jpg_found=0;
    //how many jpg found.
    //kac jpg bulundu.
    
    int filecount=0;
    //how many files found.
    //kac dosya bulundu.
    unsigned char buffer[512];

    FILE *img=NULL;

    char filename[8]; 
    
    //read the file.
    //dosyayi oku.
    while(fread(buffer,512,1,file)==1)

    {
        //does jpg use first 4 bits?
        //jpg ilk dort pixeli kullaniyor mu?
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if( jpg_found==1) 
            //if jpg already opened then close it.
            //eger jpg acildiysa o zaman kapat.
            {
                fclose(img);
            }
            else 
            {
            //if not opened then found a jpg.
            //acik degilse o zaman bir jpg bulundu.
                jpg_found=1;
            }
            //for every opened file increment i.
            //acilan her dosya icin i'yi buyut.
            sprintf(filename,"%03i.jpg",filecount); 
            
            //open the file to write.
            //dosyaya yazmak icin acin.
            img=fopen(filename,"w"); 
            
            filecount++; 
        }
        if(jpg_found==1) 
        {
            fwrite(&buffer,512,1,img);
            //write buffer of found jpg to img.
            //bulunan jpg'nin bufferini img'ye yazin.
        }
    }
    fclose(file); 
    fclose(img);

    return 0;

}
