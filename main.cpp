<<<<<<< Updated upstream
/*
 * FCAI – OOP Programming – 2023 - Assignment 1
 * Author1 and ID and Group: Abanoub Essam - 20220002
 * Author2 and ID and Group: Martin Amgad - 20220263
 * Author3 and ID and Group: Marcelino Maximos - 20220264
 */
=======
/* FCAI - OOP programing - 2023 - Assignment 1
 * Author1 and ID: Abanoub Essam - 20220002
 * Author2 and ID: Martin Amgad - 20220263
 * Author3 and ID: Marcelino Maximos - 20220264
*/

//--------------------------------------------------------------\\
>>>>>>> Stashed changes

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;

<<<<<<< Updated upstream
// The used images
=======
// The used Images
>>>>>>> Stashed changes
unsigned char image[SIZE][SIZE];
unsigned char merge[SIZE][SIZE];
unsigned char temp[SIZE][SIZE];

<<<<<<< Updated upstream
//The functions prototype
=======
// The Filters functions prototype
>>>>>>> Stashed changes
void loadImage ();
void saveImage ();
void BlackAndWhiteFilter ();
void merged();
void darken_lighten();
void FlipImage ();
<<<<<<< Updated upstream
=======
<<<<<<< Updated upstream
void rotation(int n);
void invert();
>>>>>>> Stashed changes

int main()
{
    //The program interface
    cout << "Welcome to The Filters Program :) \n";
=======
void invert();
void rotation(int n);

int main()
{
    // The program interface
    cout << "Welcome to The Filters Program :)\n";
>>>>>>> Stashed changes
    loadImage();
    while (true) {
        cout<<"Please select a filter to apply or 0 to exit: "<<'\n';
        cout<<"1- Black & White Filter\n"
              "2- Invert Filter\n"
              "3- Merge Filter\n"
              "4- Flip Image\n"
              "5- Rotate Image\n"
              "6- Darken and Lighten Image\n"
              "7- Detect Image Edges \n"
              "8- Enlarge Image\n"
              "9- Shrink Image\n"
              "a- Mirror 1/2 Image\n"
              "b- Shuffle Image\n"
              "c- Blur Image\n"
              "d- Crop Image\n"
              "e- Skew Image Right\n"
              "f- Skew Image Up\n"
              "s- Save the image to a file\n"
              "0- Exit\n";
        char c; cin>>c;
        switch (c) {
            case '1':
                BlackAndWhiteFilter();
                break;
            case '2':
                invert();
            case '3':
                merged();
                break;
            case '4':
                FlipImage();
                break;
            case '5':
                int rotate_angle;
                cout << "Choose the angle of rotation 90 or 180 or 270:";
                cin >> rotate_angle;
                rotation(rotate_angle);
            case '6':
                darken_lighten();
                break;
            case 's':
                saveImage();
                break;
            case '0':
                return 0;
        }
    }
}
<<<<<<< Updated upstream
//The functions
=======

// The used functions
>>>>>>> Stashed changes
void loadImage () {
    char imageFileName[100];

    cout << "Enter the source image file name: ";
    cin >> imageFileName;

    strcat (imageFileName, ".bmp");
    readGSBMP(imageFileName, image);
}

void saveImage () {
    char imageFileName[100];

    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    strcat (imageFileName, ".bmp");
    writeGSBMP(imageFileName, image);
}

void BlackAndWhiteFilter () {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            if (image[i][j] > 127)
                image[i][j] = 255;
            else
                image[i][j] = 0;

        }
    }
}

void load_merge(){
    char merged_image[100];

    cout << "Enter the image to merge with: ";
    cin >> merged_image;

    strcat (merged_image, ".bmp");
    readGSBMP(merged_image, merge);
}

void merged(){
    load_merge();
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] = (image[i][j] + merge[i][j]) / 2;
        }
    }
}

void flipHorizontally() {
    for (int i = 0; i < SIZE/2; i++) {
        for (int j = 0; j < SIZE; j++) {
            swap(image[i][j] , image[SIZE-i-1][j]);
        }
    }
}

void flipVertically() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE/2; j++) {
            swap(image[i][j] , image[i][SIZE-j-1]);
        }
    }
}

void FlipImage(){
    cout<<"Flip (h)orizontally or (v)ertically ? ";
    char c; cin >> c;
    if (c == 'h')
        flipHorizontally();
    else
        flipVertically();
}

void darkenFilter() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] -= image[i][j] / 2;
        }
    }
}

void lightenFilter() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] /= 2;
            image[i][j] += 127;
        }
    }
}

void darken_lighten(){
    cout << "Choose your option: \n" << "1] Darken\n2] Lighten \n";
    int option; cin >> option;
    switch (option) {
        case 1:
            darkenFilter();
            break;
        case 2:
            lightenFilter();
            break;
    }
}
<<<<<<< Updated upstream

=======
void rotation(int n) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            temp[i][j] = image[i][j];
        }
    }
    int c = n / 90;
    while (c--) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                temp[i][j] = image[i][j];
            }
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j] = temp[SIZE - j - 1][i];
            }
        }
    }
}

<<<<<<< Updated upstream
void rotation(int n){
   for(int i=0;i<SIZE;i++){
      for(int j=0;j<SIZE;j++){
         temp[i][j]=image[i][j];
      }
   }
   int c=n/90;
   while(c--){
      for(int i=0;i<SIZE;i++){
      for(int j=0;j<SIZE;j++){
         temp[i][j]=image[i][j];
      }
   }
      for(int i=0;i<SIZE;i++){
      for(int j=0;j<SIZE;j++){
         image[i][j]=temp[SIZE - j - 1][i];
      }
   }
   }
}

void invert(){
   for(int i=0;i<SIZE;i++){
      for(int j=0;j<SIZE;j++){
      image[i][j]=255-image[i][j];
   }
}
}
=======
void invert(){
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = 255 - image[i][j];
        }
    }
}
>>>>>>> Stashed changes
>>>>>>> Stashed changes
