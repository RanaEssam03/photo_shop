#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"
using namespace std;
unsigned char image[SIZE][SIZE];

void loadImage ();
void saveImage ();
void bAndW ();
void flipImage();

int main() {
    cout << "Ahlan ya user ya habibi " << char(1) << endl;
    while (true){
        char filter;
       cout <<"Please enter file name of the image to process : " << endl << "->";
        loadImage();
       cout << "Please select a filter to apply or 0 to exit:\n";
       cout << "1-Black & white Filter\n2-Invert Filter\n3-Merge Filter\n4-Flip Image\n5-Darken and Lighten Image";
       cout << "\n6- Rotate Image\n7- Detect Image Edges\n8- Enlarge Image\n9- Shrink Image\na- Mirror 1/2 Image";
       cout << "\nb- Shuffle Image\nc- Blur Image\ns- Save the image to a file\n0- Exit\n-->";
      cin.ignore();
       cin >> filter;

        if (filter =='0'){
           break;
       }
        else if (filter == '1'){
            bAndW();
        }
        else if (filter == '4'){
            flipImage();
        }

        saveImage();

    }
    return 0;
}
//_________________________________________________

void loadImage () {
    char imageFileName[100];

    // Get gray scale image file name

    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    readGSBMP(imageFileName, image);
}

//_________________________________________
void saveImage () {
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    writeGSBMP(imageFileName, image);
}
//_____________________________________________

void bAndW() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {

            if (image[i][j] > 127)
                image[i][j] = 255;
            else
                image[i][j] = 0;
        }
    }
}

void flipImage(){
    char option ;
    cout <<"Flip (h)orizontally or (v)ertically ?\n-->";
    cin >> option;

    if (option == 'v'){
        for (int i = 0 ; i < SIZE/2 ; i++){
            for (int j = 0 ; j < SIZE ; j++){
                int temp = image[i][j];
                image[i][j] = image[SIZE-i-1][j];
                image[SIZE-i-1][j] = temp;
            }
        }
    }
    else if (option == 'h'){
        for (int i = 0 ; i < SIZE ; i++){
            for (int j = 0 ; j < SIZE/2 ; j++){
                int temp = image[i][j];
                image[i][j] = image[i][SIZE-j-1];
                image[i][SIZE-j-1] = temp;
            }
        }
    }
}
