#include "image.h"





Image::Image()
{

}
void Image::saveImage(string (&myarray2D)[99][2], int n){
    cout << endl;
    cout << endl;
    for (int l =0; l <= n; l++){
    }
    cout << endl;
    cout << endl;
    cout << endl;

    int height = 200;
    int width = 200;
    string countyName;
    unsigned char image[height][width][bytesPerPixel];
    char* imageFileName = "IowaCountyImage.bmp";
    int i, j;
    for(i=0; i<height; i++){
        for(j=0; j<width; j++){
            image[i][j][2] = (unsigned char)((double)255); ///red
            image[i][j][1] = (unsigned char)((double)255); ///green
            image[i][j][0] = (unsigned char)(((double)255)); ///blue
        }
    }
    cout << endl << endl;

    int a = 0;
    int x1 = 0;
    int y1 = 0;
    int x2 = 0;
    int y2 = 0;
    for (a = 0; a <= n; a++){
        if (a == n){
            x1 = stoi(myarray2D[0][0]);
            y1 = stoi(myarray2D[0][1]);
            x2 = stoi(myarray2D[a][0]);
            y2 = stoi(myarray2D[a][1]);
        }
        else {
            x1 = stoi(myarray2D[a][0]);
            y1 = stoi(myarray2D[a][1]);
            x2 = stoi(myarray2D[a + 1][0]);
            y2 = stoi(myarray2D[a + 1][1]);
        }
        if (abs(x2-x1) >= abs(y2-y1) ){
            for(j=1; j<=abs(x2 - x1); j++){
                if (x1 < x2){
                    image[(int)(y1 + j*((1.0*(y2 - y1))/(1.0*(x2 - x1))))][j + x1][2] = (unsigned char)((double)0); ///red
                    image[(int)(y1 + j*((1.0*(y2 - y1))/(1.0*(x2 - x1))))][j + x1][1] = (unsigned char)((double)0); ///green
                    image[(int)(y1 + j*((1.0*(y2 - y1))/(1.0*(x2 - x1))))][j + x1][0] = (unsigned char)(((double)0)); ///blue
                }
                else{
                    int temp = x1;
                    x1 = x2;
                    x2 = temp;
                    temp = y1;
                    y1 = y2;
                    y2 = temp;
                    image[(int)(y1 + j*((1.0*(y2 - y1))/(1.0*(x2 - x1))))][j + x1][2] = (unsigned char)((double)0); ///red
                    image[(int)(y1 + j*((1.0*(y2 - y1))/(1.0*(x2 - x1))))][j + x1][1] = (unsigned char)((double)0); ///green
                    image[(int)(y1 + j*((1.0*(y2 - y1))/(1.0*(x2 - x1))))][j + x1][0] = (unsigned char)(((double)0)); ///blue
                }
            }
        }
        else{
            for(i=1; i<=abs(y2 - y1); i++){
                if (y1 < y2){
                    image[i + y1][(int)(x1 + i*((1.0*(x2 - x1))/(1.0*(y2 - y1))))][2] = (unsigned char)((double)0); ///red
                    image[i + y1][(int)(x1 + i*((1.0*(x2 - x1))/(1.0*(y2 - y1))))][1] = (unsigned char)((double)0); ///green
                    image[i + y1][(int)(x1 + i*((1.0*(x2 - x1))/(1.0*(y2 - y1))))][0] = (unsigned char)(((double)0)); ///blue
                }
                else{
                    int temp = x1;
                    x1 = x2;
                    x2 = temp;
                    temp = y1;
                    y1 = y2;
                    y2 = temp;
                    image[i + y1][(int)(x1 + i*((1.0*(x2 - x1))/(1.0*(y2 - y1))))][2] = (unsigned char)((double)0); ///red
                    image[i + y1][(int)(x1 + i*((1.0*(x2 - x1))/(1.0*(y2 - y1))))][1] = (unsigned char)((double)0); ///green
                    image[i + y1][(int)(x1 + i*((1.0*(x2 - x1))/(1.0*(y2 - y1))))][0] = (unsigned char)(((double)0)); ///blue

                }
             }
        }
    }
    generateBitmapImage((unsigned char *)image, height, width, imageFileName);
}



void Image::generateBitmapImage(unsigned char *image, int height, int width, char* imageFileName){

    unsigned char padding[3] = {0, 0, 0};
    int paddingSize = (4 - (width*bytesPerPixel) % 4) % 4;

    unsigned char* fileHeader = createBitmapFileHeader(height, width, paddingSize);
    unsigned char* infoHeader = createBitmapInfoHeader(height, width);

    FILE* imageFile = fopen(imageFileName, "wb");

    fwrite(fileHeader, 1, fileHeaderSize, imageFile);
    fwrite(infoHeader, 1, infoHeaderSize, imageFile);

    int i;
    for(i=0; i<height; i++){
        fwrite(image+(i*width*bytesPerPixel), bytesPerPixel, width, imageFile);
        fwrite(padding, 1, paddingSize, imageFile);
    }

    fclose(imageFile);
}

unsigned char* Image::createBitmapFileHeader(int height, int width, int paddingSize){
    int fileSize = fileHeaderSize + infoHeaderSize + (bytesPerPixel*width+paddingSize) * height;

    static unsigned char fileHeader[] = {
        0,0, /// signature
        0,0,0,0, /// image file size in bytes
        0,0,0,0, /// reserved
        0,0,0,0, /// start of pixel array
    };

    fileHeader[ 0] = (unsigned char)('B');
    fileHeader[ 1] = (unsigned char)('M');
    fileHeader[ 2] = (unsigned char)(fileSize    );
    fileHeader[ 3] = (unsigned char)(fileSize>> 8);
    fileHeader[ 4] = (unsigned char)(fileSize>>16);
    fileHeader[ 5] = (unsigned char)(fileSize>>24);
    fileHeader[10] = (unsigned char)(fileHeaderSize + infoHeaderSize);

    return fileHeader;
}

unsigned char* Image::createBitmapInfoHeader(int height, int width){
    static unsigned char infoHeader[] = {
        0,0,0,0, /// header size
        0,0,0,0, /// image width
        0,0,0,0, /// image height
        0,0, /// number of color planes
        0,0, /// bits per pixel
        0,0,0,0, /// compression
        0,0,0,0, /// image size
        0,0,0,0, /// horizontal resolution
        0,0,0,0, /// vertical resolution
        0,0,0,0, /// colors in color table
        0,0,0,0, /// important color count
    };

    infoHeader[ 0] = (unsigned char)(infoHeaderSize);
    infoHeader[ 4] = (unsigned char)(width    );
    infoHeader[ 5] = (unsigned char)(width>> 8);
    infoHeader[ 6] = (unsigned char)(width>>16);
    infoHeader[ 7] = (unsigned char)(width>>24);
    infoHeader[ 8] = (unsigned char)(height    );
    infoHeader[ 9] = (unsigned char)(height>> 8);
    infoHeader[10] = (unsigned char)(height>>16);
    infoHeader[11] = (unsigned char)(height>>24);
    infoHeader[12] = (unsigned char)(1);
    infoHeader[14] = (unsigned char)(bytesPerPixel*8);

    return infoHeader;
}
