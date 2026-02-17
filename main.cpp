#include "Mandelbrot.h"
#include <iostream>

using namespace std;

int main(){

    Mandelbrot::Mandelbrot myplot(1920, 1080);
    myplot.draw("/home/ec2-user/Mandelbrot-final/Mandelbrot-Example/images/green.bmp", Mandelbrot::Mandelbrot::GREEN);

    return 0;
}