// FCI – Programming 1 – 2022 - Assignment 3
// Program Name: photoShop.cpp
// Last Modification Date: 6/4/2022
// Author1 and ID and Group: Rana Essam Ibrahim 20210133 S1
// Author2 and ID and Group: Nourhan Abdullah  20210437 S1
// Author3 and ID and Group: Hazem Medhat  20210116
// Teaching Assistant: Eng: Nesma & Eng: Youssra
// Purpose:first 6 filters

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"
using namespace std;
unsigned char image[SIZE][SIZE];

void loadImage ();
void saveImage ();
void blackAndWhite ();
void flipImage(char option);
void blur();
void shrink();
void Invert ();
void Rotate(int option);
void merge();
void darkenAndLighten();
//------------------------------------------------------------

int main() {
    cout << "Ahlan ya user ya habibi " << char(1) << endl;
    char filter;
    while (true) {
        cout << "Please enter file name of the image to process : " << endl << "->";
        loadImage();
        while (true) {
            cout << "Please select a filter to apply or 0 to exit:\n";
            cout << "1-Black & white Filter\n2-Invert Filter\n3-Flip Image";
            cout << "\n4- Rotate Image\n5- Shrink Image";
            cout << "\n6- Blur Image\ns- Save the image to a file\n0- Exit\n-->";
            cin.ignore();
            cin >> filter;  //to get the filter number

            if (filter == '0') {
                break;
            } else if (filter == '1') {
                blackAndWhite(); //this filter make the image only black and white
            } else if (filter == '2') {
                Invert(); //this filter inverts the colors
            } else if (filter == '4') {
                char option;
                cout << "Flip (h)orizontally or (v)ertically ?\n-->";
                cin >> option;   //to detect the flip direction
                flipImage(option);
            } else if (filter == '5') {
                int option; //to detect the flip degree
                cout << "Rotate 90 or 180 or 270 ?\n-->";
                cin >> option;
                Rotate(option);
            } else if (filter == '9') {
                shrink();
            } else if (filter == 'C') {
                blur();
            } else if (filter == 's') {
                saveImage();
                break;
            }
        }
        int x;
        cout << "Do you want to upload new image (1) or exit (0)?";
        cin >> x;
        if (x==0){
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

void blackAndWhite() {
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
        for (int i = 0 ; i < SIZE/2 ; i++){  //to loop only on the half of the hight
            for (int j = 0 ; j < SIZE ; j++){
                int temp = image[i][j];
                image[i][j] = image[SIZE-i-1][j];
                image[SIZE-i-1][j] = temp;
            }
        }
    }
    else if (option == 'h'){
        for (int i = 0 ; i < SIZE ; i++){
            for (int j = 0 ; j < SIZE/2 ; j++){ //to loop only on the half on the width
                int temp = image[i][j];
                image[i][j] = image[i][SIZE-j-1];
                image[i][SIZE-j-1] = temp;
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
//----------------------------------------------------------------------------------
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
//---------------------------------------------------------------------------------
void Invert (){
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = 255 - image[i][j];      //turn every pixel to the negative
        }
    }
}
//-----------------------------------------------------------------------
void Rotate (int option){
    int n = 0;
    if (option == 270) {
        for (int i = 0; i < SIZE; i++) {    //loop on rows
            int start = 0;
            int end = SIZE - 1;             // start from the last index in the row 
            while (start < end) {
                swap(image[i][start], image[i][end]);     //swap last index in the row with the first index (every row )
                start++;
                end--;
            }
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (i < j) {
                    swap(image[i][j], image[j][i]);       //transpose
                }
            }
        }
    }
        if (option == 180) {
            while (n < 2) {
                for (int i = 0; i < SIZE; i++) {       //loop on rows
                    int start = 0;
                    int end = SIZE - 1;                // start from the last index in the row
                    while (start < end) {
                        swap(image[i][start], image[i][end]);        //swap last index in the row with the first index (every row )
                        start++;
                        end--;
                    }
                }
                for (int i = 0; i < SIZE; i++) {
                    for (int j = 0; j < SIZE; j++) {
                        if (i < j) {
                            swap(image[i][j], image[j][i]);      //transpose
                        }
                    }
                }
                n++;
            }
        }
        if (option == 90){
            while (n < 3) {
                for (int i = 0; i < SIZE; i++) {       //loop on rows
                    int start = 0;
                    int end = SIZE - 1;                // start from the last index in the row
                    while (start < end) {
                        swap(image[i][start], image[i][end]);      //swap last index in the row with the first index (every row )
                        start++;
                        end--;
                    }
                }
                for (int i = 0; i < SIZE; i++) {
                    for (int j = 0; j < SIZE; j++) {
                        if (i < j) {
                            swap(image[i][j], image[j][i]);        //transpose
                        }
                    }
                }
                n++;
            }
        }
}

void merge(){
    cout << "enter the file's name: ";
    strcat (imageFileName);
    writeGSBMP(imageFileName, image2);
    for (int i = 0; i <= SIZE; i++){
        for(int j = 0; j <= SIZE; j++){
            temp[i][j] = (image1[i][j] + image2[i][j])/2;
            image[i][j] = temp[i][j];

        }
    }
}

void darkenAndLighten(){
    char option;
    cout << "Do you want to (d)arken or (l)ighten?";
    cin >> option;
    if(option == 'd'){
        strcat (C:\Users\asus\Downloads\photo_shop-main\img\A_black_image);
        writeGSBMP(A_black_image, image2);
        for (int i = 0; i <= SIZE; i++){
            for(int j = 0; j <= SIZE; j++){
                temp[i][j] = (image1[i][j] + image2[i][j])/2;
                image[i][j] = temp[i][j];

    }
    else if(option == 'l'){
                strcat (C:\Users\asus\Downloads\photo_shop-main\img\Solid_white.svg);
                writeGSBMP(Solid_white.svg, image2);
                for (int i = 0; i <= SIZE; i++){
                    for(int j = 0; j <= SIZE; j++){
                        temp[i][j] = (image1[i][j] + image2[i][j])/2;
                        image[i][j] = temp[i][j];

    }
    else{
        cout << "invalid entry";
    }
}