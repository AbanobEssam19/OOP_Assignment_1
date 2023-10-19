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
void invert ();
void merged ();
void flipImage ();
void rotation ();
void darkenLighten ();
void edgeDetector ();
void shrink ();
void mirrorFilter ();
void blur ();
void cropImage ();
void Enlarge(int c);
void shuffle();
void skewUp ();


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
              "7- Detect Image Edges \n"
              "8- Enlarge Image\n"
              "9- Shrink Image\n"
              "a- Mirror 1/2 Image\n"
              "b- Shuffle Image\n"
              "c- Blur Image\n"
              "d- Crop Image\n"
              "e- Skew Image Right  \n"
              "f- Skew Image Up  "
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
            case '7':
                edgeDetector();
                break;
            case'8':
                Enlarge();
                break;
            case '9':
                shrink();
                break;
            case 'a':
                mirrorFilter();
                break;
            case 'b':
                shuffle();
                break;
            case 'c':
                blur();
                break;
            case 'd':
                cropImage();
                break;
            case 'f':
                skewUp();
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

void copyingTheImage() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            temp[i][j] = image[i][j];
        }
    }
}

void detectingLeftToRight() {
    for (int i = 0; i < SIZE-1; i++) {
        bool black;
        if (image[i][0] == 255)
            black = false;
        else
            black = true;
        for (int j = 1; j < SIZE-1; j++) {
            if (image[i][j] == 0) {
                if (black) {
                    image[i][j] = 255;
                }
                else
                    black = true;
            }
            else {
                if (black) {
                    black = false;
                    image[i][j-1] = 0;
                }
            }
        }
    }
}

void detectingUpToDown() {
    for (int i = 0; i < SIZE-1; i++) {
        bool black;
        if (temp[0][i] == 255)
            black = false;
        else
            black = true;
        for (int j = 1; j < SIZE-1; j++) {
            if (temp[j][i] == 0) {
                if (black) {
                    temp[j][i] = 255;
                }
                else
                    black = true;
            }
            else {
                if (black) {
                    black = false;
                    temp[j][i-1] = 0;
                }
            }
        }
    }
}

void edgeDetector() {
    blackAndWhiteFilter();
    copyingTheImage();
    detectingLeftToRight();
    detectingUpToDown();
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (temp[i][j] == 0)
                image[i][j] = 0;
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

void mirrorLeft() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE/2; ++j) {
            image[i][SIZE-j-1] = image[i][j];
        }
    }
}

void mirrorRight() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE/2; ++j) {
            image[i][j] = image[i][SIZE-j-1];
        }
    }
}

void mirrorUp() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE/2; ++j) {
            image[SIZE-j-1][i] = image[j][i];
        }
    }
}

void mirrorDown() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE/2; ++j) {
            image[j][i] = image[SIZE-j-1][i];
        }
    }
}

void mirrorFilter() {
    cout<<"Mirror (l)eft, (r)ight, (u)pper, (d)own side?\n";
    char c; cin>>c;
    switch (c) {
        case 'l':
            mirrorLeft();
            break;
        case 'r':
            mirrorRight();
            break;
        case 'u':
            mirrorUp();
            break;
        case 'd':
            mirrorDown();
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

void cropImage() {
    cout<<"Please enter x y l w: ";
    int x,y,l,w; cin>>x>>y>>l>>w;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            temp[i][j] = 255;
        }
    }
    for (int i = x; i < x+l; ++i) {
        for (int j = y; j < y+w; ++j) {
            temp[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] = temp[i][j];
        }
    }
}

void skewUp(){
    double angle;
    cout << "Enter the angle of skewness:";
    cin >> angle;
    double shift = 256 * tan((angle*22)/(180*7));
    double copy_shift = shift;
    double minus = shift / 256;
    unsigned char temp[SIZE][SIZE+(int)shift];
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE+copy_shift; ++j) {
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
        for (int j = 0; j < SIZE + (int)copy_shift; ++j) {
            image[i][(int)(j/shrink)] = temp[i][j];
        }
    }
}
void shuffle(){
    int order=1;
    for(int k=0;k<4;k++){
        int c;cin>>c;
        if(order==1){
            if(c==1){
                for(int i=0;i<128;i++){
                    for(int j=0;j<128;j++){
                        temp[i][j]=image[i][j];
                    }
                }
            }
            else if(c==2){
                for(int i=0;i<128;i++){
                    for(int j=0;j<128;j++){
                        temp[i][j]=image[i][j+128];
                    }
                }
            }
            else if(c==3){
                for(int i=0;i<128;i++){
                    for(int j=0;j<128;j++){
                        temp[i][j]=image[i+128][j];
                    }
                }
            }
            else if(c==4){
                for(int i=0;i<128;i++){
                    for(int j=0;j<128;j++){
                        temp[i][j]=image[i+128][j+128];
                    }
                }
            }
            order=2;
        }
        else if(order==2){
            if(c==1){
                for(int i=0;i<128;i++){
                    for(int j=128;j<255;j++){
                        temp[i][j]=image[i][j-128];
                    }
                }
            }
            else if(c==2){
                for(int i=0;i<128;i++){
                    for(int j=128;j<255;j++){
                        temp[i][j]=image[i][j];
                    }
                }
            }
            else if(c==3){
                for(int i=0;i<128;i++){
                    for(int j=128;j<255;j++){
                        temp[i][j]=image[i+128][j-128];
                    }
                }
            }
            else if(c==4){
                for(int i=0;i<128;i++){
                    for(int j=128;j<255;j++){
                        temp[i][j]=image[i+128][j];
                    }
                }
            }
            order=3;
        }
        else if(order==3){
            if(c==1){
                for(int i=128;i<255;i++){
                    for(int j=0;j<128;j++){
                        temp[i][j]=image[i-128][j];
                    }
                }
            }
            else if(c==2){
                for(int i=128;i<255;i++){
                    for(int j=0;j<128;j++){
                        temp[i][j]=image[i-128][j+128];
                    }
                }
            }
            else if(c==3){
                for(int i=128;i<255;i++){
                    for(int j=0;j<128;j++){
                        temp[i][j]=image[i][j];
                    }
                }
            }
            else if(c==4){
                for(int i=128;i<255;i++){
                    for(int j=0;j<128;j++){
                        temp[i][j]=image[i][j+128];
                    }
                }
            }
            order=4;
        }
        else if(order==4){
            if(c==1){
                for(int i=128;i<255;i++){
                    for(int j=128;j<255;j++){
                        temp[i][j]=image[i-128][j-128];
                    }
                }
            }
            else if(c==2){
                for(int i=128;i<255;i++){
                    for(int j=128;j<255;j++){
                        temp[i][j]=image[i-128][j];
                    }
                }
            }
            else if(c==3){
                for(int i=128;i<255;i++){
                    for(int j=128;j<255;j++){
                        temp[i][j]=image[i][j-128];
                    }
                }
            }
            else if(c==4){
                for(int i=128;i<255;i++){
                    for(int j=128;j<255;j++){
                        temp[i][j]=image[i][j];
                    }
                }
            }
        }
    }
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            image[i][j]=temp[i][j];
        }
    }
}
void Enlarge(int c) {
    if (c == 1) {
        fr(SIZE) {
            for (int j = 0; j < SIZE; j++) {
                temp[i][j] = image[(i / 2)][j / 2];
            }
        }
    } else if (c == 2) {
        fr(SIZE) {
            for (int j = 0; j < SIZE; j++) {
                temp[i][j] = image[(i / 2)][(j / 2) + 128];
            }
        }
    } else if (c == 3) {
        fr(SIZE) {
            for (int j = 0; j < SIZE; j++) {
                temp[i][j] = image[(i / 2) + 128][(j / 2) ];
            }
        }
    } else {
        fr(SIZE) {
            for (int j = 0; j < SIZE; j++) {
                temp[i][j] = image[(i / 2)+128][(j / 2) + 128];
            }
        }
    }
    fr(SIZE){
        for(int j=0;j<SIZE;j++){
            image[i][j]=temp[i][j];
        }
    }
}
