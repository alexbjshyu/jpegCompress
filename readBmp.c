#include <stdio.h>
#include <stdlib.h>

typedef struct _BmpHeader{
   unsigned int size;               /* Header size in bytes      */
   int width;
   int height;                /* Width and height of image */
   unsigned short int planes;       /* Number of colour planes   */
   unsigned short int bits;         /* Bits per pixel            */
   unsigned int compression;        /* Compression type          */
   unsigned int imagesize;          /* Image size in bytes       */
   int xresolution,yresolution;     /* Pixels per meter          */
   unsigned int ncolours;           /* Number of colours         */
   unsigned int importantcolours;   /* Important colours         */
}  BmpHeader;//stucture for bmp file header

typedef struct {
	int blue;
	int green;
	int red;
} RGB;//structure for RGB values

int main(void){
int i,j;

int **buffer;//free space same size as the original bmp file used for storing RGB values.
// super-simplified BMP read algorithm to pull out RGB data
 // read image for coloring scheme
 int image[1024][3]; // first number here is 1024 pixels in my image, 3 is for RGB values
 FILE *streamIn, *testPrint;
 streamIn = fopen("lena_gray.bmp", "rb");
 testPrint = fopen("testPrint.txt","wb");
 if (streamIn == (FILE *)0){
   printf("File opening error ocurred. Exiting program.\n");
   exit(0);
 }

 int byte;
 int count = 0;
//reading in the header of original bmp file
BmpHeader bmpHeader;
unsigned char* ptr;
ptr = (unsigned char *) &bmpHeader;
fread(ptr,sizeof(unsigned char),sizeof(BmpHeader), streamIn);

printf("%d\n",bmpHeader.size);
printf("%d %d\n",bmpHeader.height,bmpHeader.width);

 for(i=0;i<54;i++) byte = getc(streamIn);  // strip out BMP header
 

//initializing space for buffer using width and height taken from header
 buffer = (int **) calloc(sizeof(int*), bmpHeader.height);
 for(j=0;j<bmpHeader.height;j++)
 {
 	buffer[j] = (int *)calloc(sizeof(int), bmpHeader.width);
 }

 for(i=0;i<1024;i++){    // foreach pixel
    image[i][2] = getc(streamIn);  // use BMP 24bit with no alpha channel
    image[i][1] = getc(streamIn);  // BMP uses BGR but we want RGB, grab byte-by-byte
    image[i][0] = getc(streamIn);  // reverse-order array indexing fixes RGB issue...
    printf("pixel %d : [%d,%d,%d]\n",i+1,image[i][0],image[i][1],image[i][2]);
 }

 fclose(streamIn);
}