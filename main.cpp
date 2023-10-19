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
void enlarge();
void shrink ();
void mirrorFilter ();
void shuffle();
void blur ();
void cropImage ();
void skewRight ();
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
              "f- Skew Image Up \n"
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
                enlarge();
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
            case 'e':
                skewRight();
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

void loadMerge(){
    char merged_image[100];

    cout << "Enter the image to merge with: ";
    cin >> merged_image;

    strcat (merged_image, ".bmp");
    readGSBMP(merged_image, temp);
}

void merged(){
    loadMerge(); // loading the merge image
    for (int i = 0; i < SIZE; ++i) { // merging both image into the original image
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] = (image[i][j] + temp[i][j]) / 2;
        }
    }
}

void flipHorizontally() {
    for (int i = 0; i < SIZE/2; i++) { // Swapping the pixels horizontally
        for (int j = 0; j < SIZE; j++) {
            swap(image[i][j] , image[SIZE-i-1][j]);
        }
    }
}

void flipVertically() {
    for (int i = 0; i < SIZE; i++) { // Swapping the pixels vertically
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
    int c = rotate_angle / 90; // Calculating the number of rotations required
    while (c--) {
        for (int i = 0; i < SIZE; i++) { // Getting a copy from the current image
            for (int j = 0; j < SIZE; j++) {
                temp[i][j] = image[i][j];
            }
        }
        for (int i = 0; i < SIZE; i++) { // Rotating the image by 90 degree
            for (int j = 0; j < SIZE; j++) {
                image[i][j] = temp[SIZE - j - 1][i];
            }
        }
    }
}

void darkenFilter() {
    for (int i = 0; i < SIZE; ++i) { // Making the image darker by 50%
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] -= image[i][j] / 2;
        }
    }
}

void lightenFilter() {
    for (int i = 0; i < SIZE; ++i) { // Merging the image with a white image
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
    blackAndWhiteFilter(); // Applying the black and white filter to the image
    copyingTheImage(); // Taking a copy form the image
    detectingLeftToRight(); // Detecting the edges from left to right
    detectingUpToDown(); // Detecting the edges from up to down
    for (int i = 0; i < SIZE; i++) { // Mixing both images into the original
        for (int j = 0; j < SIZE; j++) {
            if (temp[i][j] == 0)
                image[i][j] = 0;
        }
    }
}

void enlarge() {
    int c; cout << "Which quarter to enlarge 1, 2, 3 or 4? ";
    cin >> c;
    if (c == 1) { // Enlarging the selected quarter into the temporary image
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; j++) {
                temp[i][j] = image[(i / 2)][j / 2];
            }
        }
    }
    else if (c == 2) {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; j++) {
                temp[i][j] = image[(i / 2)][(j / 2) + 128];
            }
        }
    }
    else if (c == 3) {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; j++) {
                temp[i][j] = image[(i / 2) + 128][(j / 2) ];
            }
        }
    }
    else {
        for (int i = 0; i < SIZE; ++i){
            for (int j = 0; j < SIZE; j++) {
                temp[i][j] = image[(i / 2)+128][(j / 2) + 128];
            }
        }
    }
    for (int i = 0; i < SIZE; ++i){ // Copping the temporary image into the original image
        for(int j=0;j<SIZE;j++){
            image[i][j] = temp[i][j];
        }
    }
}


void shrink(){
    for (int i = 0; i < SIZE; ++i) { // Creating a white image for the background
        for (int j = 0; j < SIZE; ++j) {
            temp[i][j] = 255;
        }
    }
    int ratio;
    cout << "Choose the percentage of shrink :\n"
            "1- (1/2)\n"
            "2- (1/4)\n"
            "3- (1/3)\n";
    cin >> ratio;
    if (ratio == 1) // Shrinking the image by the selected ratio
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                temp[i/2][j/2] = image[i][j];
            }
        }
    else if (ratio == 2)
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
    for (int i = 0; i < SIZE; ++i) { // Coping the shrank image back to the original image
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

void shuffle() {
    for (int k = 1; k <= 4; k++) { // Lopping through the 4 quarters
        int c , a , b , x , y;  // (a , x) the start and the end for rows , (b , y) are the same but for the columns
        int z = 0 , w = 0; // z : the starting point for the rows of the required quarter , and w is the same but for columns
        cin >> c;
        if (k == 1) {
            a = 0 , b = 0 , x = 128 , y = 128;
            if (c == 2)
                w = 128;
            else if (c == 3)
                z = 128;
            else if (c == 4)
                z = 128 , w = 128;
        }
        else if (k == 2) {
            a = 0 , b = 128 , x = 128 , y = SIZE;
            if (c == 1)
                w = -128;
            else if (c == 3)
                z = 128 , w = -128;
            else if (c == 4)
                z = 128;
        }
        else if (k == 3) {
            a = 128 , b = 0, x = SIZE , y = 128;
            if (c == 1)
                z = -128;
            else if (c == 2)
                z = -128 , w = 128;
            else if (c == 4)
                w = 128;
        }
        else if (k == 4) {
            a = 128 , b = 128 , x = SIZE , y = SIZE;
            if (c == 1)
                z = -128 , w = -128;
            else if (c == 2)
                z = -128;
            else if (c == 3)
                w = -128;
        }
        for (int i = a; i < x; ++i) {
            for (int j =b; j < y; ++j) {
                temp[i][j] = image[i+z][j+w];
            }
        }
    }
    for (int i = 0; i < SIZE; ++i) { // Copping the final image to the original file
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] = temp[i][j];
        }
    }
}

void blur(){
    for (int i = 0; i < SIZE; ++i) { // Adding the surrounding pixels to every pixel to create the blur effect
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] = (image[i][j] + image[i+1][j] + image[i+2][j] + image[i+3][j] + image[i+4][j] +
                           image[i][j+1] + image[i][j+2] + image[i][j+3] + image[i][j+4]) / 9;
        }
    }
}

void cropImage() {
    cout<<"Please enter x y l w: ";
    int x,y,l,w; cin>>x>>y>>l>>w;
    for (int i = 0; i < SIZE; ++i) { // Creating a white image for the background
        for (int j = 0; j < SIZE; ++j) {
            temp[i][j] = 255;
        }
    }
    for (int i = x; i < x+l; ++i) { // Cropping the image with the entered positions and width and height
        for (int j = y; j < y+w; ++j) {
            temp[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < SIZE; ++i) { // Coping the cropped image back to the original image
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] = temp[i][j];
        }
    }
}

void skewRight(){
    double angle;
    cout << "Enter the angle of skewness:";
    cin >> angle;
    double shift = 256 * tan((angle*22)/(180*7)); // Calculating the shift that needs to be applied to the image
    double copy_shift = shift;
    double minus = shift / 256;
    unsigned char temp[SIZE+(int)shift][SIZE]; // Creating a second image to store the skewed image
    for (int i = 0; i < SIZE + copy_shift; ++i) {  // Initializing the second image to white
        for (int j = 0; j < SIZE; ++j) {
            temp[i][j] = 255;
        }
    }
    for (int i = 0; i < SIZE; ++i) { // Coping the original image to the second image shifted by the required amount
        for (int j = 0; j < SIZE; ++j) {
            temp[j+(int)shift][i] = image[j][i];
        }
        shift -= minus;
    }
    double shrink = (SIZE+copy_shift) / SIZE;
    for (int i = 0; i < SIZE + (int)copy_shift; ++i) { // Coping the skewed image back to the original image and shrinking it
        for (int j = 0; j < SIZE; ++j) {
            image[(int)(i/shrink)][j] = temp[i][j];
        }
    }
}

void skewUp(){
    double angle;
    cout << "Enter the angle of skewness:";
    cin >> angle;
    double shift = 256 * tan((angle*22)/(180*7)); // Calculating the shift that needs to be applied to the image
    double copy_shift = shift;
    double minus = shift / 256;
    unsigned char temp[SIZE][SIZE+(int)shift]; // Creating a second image to store the skewed image
    for (int i = 0; i < SIZE; ++i) { // Initializing the second image to white
        for (int j = 0; j < SIZE+copy_shift; ++j) {
            temp[i][j] = 255;
        }
    }
    for (int i = 0; i < SIZE; ++i) { // Coping the original image to the second image shifted by the required amount
        for (int j = 0; j < SIZE; ++j) {
            temp[i][j+(int)shift] = image[i][j];
        }
        shift -= minus;
    }
    double shrink = (SIZE+copy_shift) / SIZE;
    for (int i = 0; i < SIZE; ++i) { // Coping the skewed image back to the original image and shrinking it
        for (int j = 0; j < SIZE + (int)copy_shift; ++j) {
            image[i][(int)(j/shrink)] = temp[i][j];
        }
    }
}
