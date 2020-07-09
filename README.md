# Easy pixel canvas for X Window System

Need a canvas for simply setting pixel values, for example when prototyping LED matrix draw functions? Naturally it's easy to use `<canvas>` tag with JavaScript, but what if you want to do stuff in C?

## There's only two functions, "run" and "draw"
Just include easy.h, initialize your canvas and set pixels:
~~~
#include "./easy.h"

void draw() {
	// x,y,r,g,b
	set(0,0,255,0,0);
	set(1,1,100,200,250);
}

int main(int argc, char *argv[]) {
	// x, y, width, height, pixel size, draw func, delay, clear between updates
	run(100, 100, 2, 2, 10, draw, 5000, 0);
	return 0;
}
~~~

## Fast workflow
Clone the repo, type `make` and start editing [template.c](/template.c) file - the code will be compiled and a window displaying the canvas is shown. As you modify and save the file the canvas will automatically relaunch and update so you don't have to leave your code editor.

## Examples: "tunnel" and "interference"
Two examples are provided. To build and run them (press any key or click the canvas to close the examples), just:
~~~
make examples
./tunnel
./interference
~~~

![Tunnel example](/docs/tunnel.png)
![Interference example](/docs/interference.png)

