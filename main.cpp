/*
 * FCAI – OOP Programming – 2023 - Assignment 1
 * Author1 and ID and Group: Abanob Essam - 20220002
 * Author2 and ID and Group: Martin Amgad - 20220263
 * Author3 and ID and Group: Marcelino Maximos - 20220264
 */

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;

// The used Images
unsigned char image[SIZE][SIZE];
unsigned char merge[SIZE][SIZE];
unsigned char temp[SIZE][SIZE];

// The Filters functions prototype
void loadImage ();
void saveImage ();
void blackAndWhiteFilter ();
void merged();
void darkenLighten();
void flipImage ();
void rotation();
void invert();
void blur();
void shrink();
void skew_up();


int main()
{
    // The program interface
    cout << "Welcome to The Filters Program :)\n";
    loadImage();
    while (true) {
        cout<<"Please select a filter to apply or 0 to exit: "<<'\n';
        cout<<"1- Black & White Filter\n"
              "2- Invert Filter\n"
              "3- Merge Filter\n"
              "4- Flip Image\n"
              "5- Rotate Image\n"
              "6- Darken and Lighten Image\n"
              "s- Save the image to a file\n"
              "0- Exit\n";
        char c; cin>>c;
        switch (c) {
            case '1':
                blackAndWhiteFilter();
                break;
            case '2':
                invert();
                break;
            case '3':
                merged();
                break;
            case '4':
                flipImage();
                break;
            case '5':
                rotation();
                break;
            case '6':
                darkenLighten();
                break;
            case '9':
                shrink();
                break;
            case 'c':
                blur();
                break;
            case 'f':
                skew_up();
                break;
            case 's':
                saveImage();
                break;
            case '0':
                return 0;
        }
    }
}

// The used functions
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

void blackAndWhiteFilter () {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            if (image[i][j] > 127)
                image[i][j] = 255;
            else
                image[i][j] = 0;

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

void flipImage(){
    cout<<"Flip (h)orizontally or (v)ertically ? ";
    char c; cin >> c;
    if (c == 'h')
        flipHorizontally();
    else
        flipVertically();
}

void rotation() {
    int rotate_angle;
    cout << "Choose the angle of rotation 90 or 180 or 270:";
    cin >> rotate_angle;
    int c = rotate_angle / 90;
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

void darkenLighten(){
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

void blur(){
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] = (image[i][j] + image[i+1][j] + image[i+2][j] + image[i+3][j] + image[i+4][j] +
                           image[i][j+1] + image[i][j+2] + image[i][j+3] + image[i][j+4]) / 9;
        }
    }
}

void shrink(){
    float ratio;
    unsigned char temp[SIZE][SIZE];
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            temp[i][j] = 255;
        }
    }
    cout << "Enter the percentage of shrink 0.5 or 0.25 or 0.333333:";
    cin >> ratio;
    if(ratio == 0.5)
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                temp[i/2][j/2] = image[i][j];
            }
        }
    else if(ratio == 0.25)
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                temp[i/4][j/4] = image[i][j];
            }
        }
    else
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                temp[i/3][j/3] = image[i][j];
            }
        }
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] = temp[i][j];
        }
    }
}

void skew_up(){
    double angle;
    cout << "Enter the angle of skewness:";
    cin >> angle;
    double shift = 256 * tan((angle*22)/(180*7));
    double copy_shift = shift;
    double minus = shift / 256;
    unsigned char temp[SIZE][SIZE+(int)shift];
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            temp[i][j] = 255;
        }
    }
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            temp[i][j+(int)shift] = image[i][j];
        }
        shift -= minus;
    }
    double shrink = (SIZE+copy_shift) / SIZE;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            temp[i/(int)shrink][j/(int)shrink] = image[i][j];
        }
    }
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] = temp[i][j];
        }
    }
}

