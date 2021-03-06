// FCI – Programming 1 – 2022 - Assignment 3
// Program Name: photoShop.cpp
// Last Modification Date: 6/4/2022
// Author1 and ID and Group: Rana Essam Ibrahim 20210133 S1
// Author2 and ID and Group: Nourhan Abdullah  20210437 S1
// Author3 and ID and Group: Hazem Medhat  20210116
// Teaching Assistant: Eng: Nesma & Eng: Youssra
// Purpose:first 6 filters

#include <iostream>
#include <cstring>
#include "bmplib.cpp"
#include <vector>
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
void detectImageEdges();
void mirrorImage();
void enlarge ();
void shuffle ();
//------------------------------------------------------------

int main() {
    cout << "Ahlan ya user ya habibi " << char(1) << endl;
    char filter;
    while (true) {
        cout << "Please enter file name of the image to process : " << endl << "->";
        loadImage();
        while (true) {
            cout << "Please select a filter to apply or 0 to exit:\n";
            cout << "1-Black & white Filter\n2-Invert Filter\n3-Merge Filter\n4-Flip Image\n5-Darken and Lighten Image";
            cout << "\n6- Rotate Image\n7- Detect Image Edges\n8- Enlarge Image\n9- Shrink Image\na- Mirror 1/2 Image";
            cout << "\nb- Shuffle Image\nc- Blur Image\ns- Save the image to a file\n0- Exit\n-->";
            cin.ignore();
            cin >> filter;  //to get the filter number

            if (filter == '0') {
                break;
            } else if (filter == '1') {
                blackAndWhite(); //this filter make the image only black and white
            } else if (filter == '2') {
                Invert(); //this filter inverts the colors
            }
            else if (filter=='3'){
                merge(); //this filter merges 2 filters together
            }
            else if (filter == '4') {
                char option;
                cout << "Flip (h)orizontally or (v)ertically ?\n-->";
                cin >> option;   //to detect the flip direction
                flipImage(option);
            }
            else if (filter == '5'){
                darkenAndLighten();
            }
            else if (filter == '6') {
                int option; //to detect the flip degree
                cout << "Rotate 90 or 180 or 270 ?\n-->";
                cin >> option;
                Rotate(option);
            }
            else if (filter == '7'){
                detectImageEdges();
            }
            else if (filter== '8'){
                enlarge();
            }
            else if (filter == '9') {
                shrink();
            }
            else if (filter == 'a'){
                mirrorImage();
            }
            else if (filter == 'b'){
                shuffle();
            }
            
            else if (filter == 'C') {
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
            if (image[i][j] > 127) //to detect the level of the color and if it's close to black we will make it black else white
                image[i][j] = 255;
            else
                image[i][j] = 0;
        }
    }
}
//___________________________________________________________

void flipImage(char option){
    if (option == 'v'){
        for (int i = 0 ; i < SIZE/2 ; i++){  //to loop only on the half of the height
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
        for (int j=0 ; j < SIZE ; j+=2){ //to calculate the average of the pixels around each pixel
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
//-------------------------------------------------------------------
void merge(){
    cout << "enter the file's name: ";
    unsigned char image2 [SIZE][SIZE];
    unsigned char temp [SIZE][SIZE];
    char imageFileName[100];
    cin >> imageFileName;  //to take the second image name from the user which will be merged with the current image
    strcat (imageFileName, ".bmp");
    readGSBMP(imageFileName, image2);
    for (int i = 0; i <= SIZE; i++){
        for(int j = 0; j <= SIZE; j++){
            temp[i][j] = (image[i][j] + image2[i][j])/2; //to take the average of both images and put it in one pixel so the pixel become mix of the both
            image[i][j] = temp[i][j];

        }
    }
}

void darkenAndLighten(){
    char x ;
    cout << "(d)arken or (l)ighten ? "; //to detect the choice which the user wants
    cin >> x;
    if (x== 'd')
    {
        for (int i = 0 ; i < SIZE; i++){
            for(int j = 0 ; j < SIZE ; j++){
                image[i][j] /= 2; //to darken the image we must make each pixel close to black "0" or merge the photo with black image (0,0,0)
            }
        }
    }
    else
    {
        for (int i = 0 ; i < SIZE; i++){
            for(int j = 0 ; j < SIZE ; j++){
                image[i][j] = (image[i][j] + 255)/2 ; //to lighten the image we must make each pixel close to white "255" or merge the photo with white image (255,255,255)
            }
        }
    }

    }



//_____________________________________________________________________________
void detectImageEdges(){
    //to detect the difference between only 2 colors
    blackAndWhite();
    for (int i = 0 ; i <255; i++){
        for (int j = 0 ; j < 255; j++){
            if (image[i][j] != image[i][j+1] || image[i][j] != image[i+1][j]){
                image[i][j] =0;  //if there is a difference between two colors then there is an edge between them
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
    cout << "Mirror (l)eft, (r)ight, (u)pper, (d)own side?\n -->"; //to detect which side the user want to mirror at
    cin >> side;
    if (side == 'l'){
        for (int i = 0; i <255; i++){
            for (int j = 127; j < 255 ; j++){ //to start change the second side of the image and make it equal to the first side
                image[i][j] = image[i][255-j-1]; //to deal with the all pixels as a palindrome
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

//-------------------------------------------
// divide image to corrspond quarter and fill the image given
void divideImage(int quarter, unsigned char newImage[][SIZE / 2]) {
    int startRow, endRow, startCol, endCol;

    // define every quarter by start and end of row and col
    startRow = quarter == 1 || quarter == 2 ? 0 : SIZE / 2;
    endRow = quarter == 1 || quarter == 2 ? SIZE / 2 : SIZE;
    startCol = quarter == 1 || quarter == 3 ? 0 : SIZE / 2;
    endCol = quarter == 1 || quarter == 3 ? SIZE / 2 : SIZE;


    // fill given image
    for (int i = startRow, row = 0; i < endRow; i++) {
        for (int j = startCol, col = 0; j < endCol; j++) {
            newImage[row][col] = image[i][j];
            col++;
        }
        row++;
    }
}
//------------------------------------------------------------------------------
void shuffle() {

        // order of suffle
        int seq[4];

        // get seqaunce from user
        cout << "New sequence of quarters ? ";
        for (int i = 0; i < 4; i++) {
            cin >> seq[i];
            if (seq[i] > 4 || seq[i] < 1) {
                cout << "reject\n";
                return;
            }
        }

        // all quarters of image
        vector<unsigned char[SIZE / 2][SIZE / 2]>quarterImages(4);

        // get quarters of image
        for (int i = 0; i < quarterImages.size(); i++) {
            divideImage(seq[i], quarterImages[i]);
        }

        int row, col;
        for (int i = 0; i < 4; i++) { 

            // avoid overflow
            row = i == 0 || i == 1 ? 0 : SIZE / 2;

            //fiil image with quarter in order
            for (int j = 0; j < SIZE / 2; j++) {

                // avoid overflow
                col = i == 0 || i == 2 ? 0 : SIZE / 2;

                for (int k = 0; k < SIZE / 2; k++) {
                    image[row][col] = quarterImages[i][j][k];
                    col++;
                }
                row++;
            }
        }
    }

//-------------------------------------------------------------------------
void enlarge(){
     unsigned char temp[SIZE/2][SIZE/2];
     int  startRow, startCol, endRow, endCol;
     int quarter=0;
     while(quarter>4 || quarter<1) {
         cout << "Which quarter to enlarge 1, 2, 3 or 4?" << endl;
         cin >> quarter;
     }
     startRow = quarter ==1 || quarter==2 ? 0 : SIZE/2;
     endRow   = quarter ==1 || quarter==2 ? SIZE/2 : SIZE;
     startCol = quarter ==1 || quarter==3 ? 0 : SIZE/2;
     endCol   = quarter ==1 || quarter==3 ? SIZE/2 : SIZE;
     for(int i=startRow,row=0;i<endRow;i++){
         for (int j=startCol, col=0;j<endCol;j++){
             temp[row][col]=image[i][j];
             col++;
         }
         row++;
     }
     for(int i=0, row=0; i<SIZE/2 ; i++){
         for (int j=0, col=0; j<SIZE/2 ; j++){
             image[row][col]=temp[i][j];
             image[row+1][col]=temp[i][j];
             image[row][col+1]=temp[i][j];
             image[row+1][col+1]=temp[i][j];
             col+=2;
         }
         row+=2;
     }
 }
