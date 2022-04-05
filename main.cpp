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
void flipImage(char option);
void detectImageEdges();
void mirrorImage();
void blur();
void shrink();


int main() {
    cout << "Ahlan ya user ya habibi " << char(1) << endl;
    char filter;
    cout <<"Please enter file name of the image to process : " << endl << "->";
    loadImage();
    while (true){
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
            char option ;
            cout <<"Flip (h)orizontally or (v)ertically ?\n-->";
            cin >> option;
            flipImage(option);
        }
        else if (filter == '7'){
           detectImageEdges();
        }
        else if (filter == 'a'){
            mirrorImage();
        }
        else if (filter == 'c'){
            blur();
        }
        else if (filter == 's'){
            saveImage();
            break;
        }
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
//___________________________________________________________

void flipImage(char option){


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
//____________________________________________________________

void detectImageEdges(){
    bAndW();
    for (int i = 0 ; i <255; i++){
        for (int j = 0 ; j < 255; j++){
            if (image[i][j] != image[i][j+1] || image[i][j] != image[i+1][j]){
                image[i][j] =0;
            }
            else if (image[i][j] == image[i][j+1] || image[i][j] == image[i+1][j]){
                image[i][j] = 255;
            }

        }
    }
}
//______________________________________________________
void mirrorImage(){
    char side;
    cout << "Mirror (l)eft, (r)ight, (u)pper, (d)own side?\n -->";
    cin >> side;
    if (side == 'l'){
        for (int i = 0; i <255; i++){
            for (int j = 127; j < 255 ; j++){
                image[i][j] = image[i][255-j-1];
            }
        }
    }
    else if (side == 'r'){
        for (int i = 0; i <255; i++){
            for (int j = 0; j < 127 ; j++){
                image[i][j] = image[i][255-j-1];
            }
        }
    }

    if (side == 'u'){
        for (int i = 127; i <255; i++){
            for (int j = 0; j < 255 ; j++){
                image[i][j] = image[255-1-i][j];
            }
        }
    }
    if (side == 'd'){
        for (int i = 0; i <127; i++){
            for (int j = 0; j < 255 ; j++){
                image[i][j] = image[255-1-i][j];
            }
        }
    }
}

//________________________________________________________________________________
void blur () {
    int value;
    for (int i=0 ; i < SIZE ; i+=2){
        for (int j=0 ; j < SIZE ; j+=2){
            value =((image[i][j]+image[i+1][j]+image[i][j+1]+image[i+1][j+1]+image[i][j+2]+image[i+2][j]+image[i+2][i+2]+image[i+1][j+2]+image[i+2][j+1])/9);
            image[i][j]=value;
            image[i+1][j]=value;
            image[i][j+1]=value;
            image[i+1][j+1]=value;
            image[i][j+2]=value;
            image[i+2][j]=value;
            image[i+2][i+2]=value;
            image[i+1][j+2]=value;
            image[i+2][j+1]=value;

        }}
}

void shrink () {
    cout << "please enter the value you want to shrink with from the list[1/2,1/3,1/4]\n";
    string shrink_value;
    cin >> shrink_value;
    if (shrink_value == "1/2") {
        int x = 0;
        for (int i = 0; i < SIZE; i += 2) {
            int y = 0;
            for (int j = 0; j < SIZE; j += 2) {
                image[x][y] = ((image[i][j] + image[i + 1][j] + image[i][j + 1] + image[i + 1][j + 1]) / 4);
                y++;
            }
            x++;
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (i >= (SIZE / 2) || j >= (SIZE / 2)) {
                    image[i][j] = SIZE - 1;
                }
            }
        }
    }
    else if (shrink_value == "1/3"){
        int x = 0;
        for (int i = 0; i < SIZE; i += 3) {
            int y = 0;
            for (int j = 0; j < SIZE; j += 3) {
                image[x][y] = ((image[i][j]+image[i+1][j]+image[i][j+1]+image[i+1][j+1]+image[i][j+2]+image[i+2][j]+image[i+2][i+2]+image[i+1][j+2]+image[i+2][j+1])/9);
                y++;
            }
            x++;
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (i >= (SIZE / 3) || j >= (SIZE / 3)) {
                    image[i][j] = SIZE - 1;
                }
            }
        }
    }else if (shrink_value == "1/4"){
        int x = 0;
        for (int i = 0; i < SIZE; i += 4) {
            int y = 0;
            for (int j = 0; j < SIZE; j += 4) {
                image[x][y] = ((image[i][j]+image[i+1][j]+image[i][j+1]+image[i+1][j+1]+image[i][j+2]+image[i+2][j]+image[i+2][i+2]+image[i+1][j+2]+image[i+2][j+1]+image[i+3][j]+image[i][j+3]+image[i+1][j+3]+image[i+3][j+1]+image[i+3][j+2]+image[i+2][j+3])/16);
                y++;
            }
            x++;
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (i >= (SIZE / 4) || j >= (SIZE / 4)) {
                    image[i][j] = SIZE - 1;
                }
            }
        }
    }}
