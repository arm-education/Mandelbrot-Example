#include "Mandelbrot.h"
#include <iostream>

using namespace std;

int main(){

    Mandelbrot::Mandelbrot myplot(1920, 1080);
    myplot.draw("/home/ubuntu/mandelbrot/images", Mandelbrot::Mandelbrot::GREEN);

    return 0;
}