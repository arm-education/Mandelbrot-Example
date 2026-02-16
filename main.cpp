#include "Mandelbrot.h"
#include <iostream>

using namespace std;

int main(){

    Mandelbrot::Mandelbrot myplot(1920, 1080);
    myplot.draw("./images/green-512.bmp", Mandelbrot::Mandelbrot::GREEN);

    return 0;
}