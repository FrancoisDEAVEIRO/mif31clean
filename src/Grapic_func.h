/****************************************************************************
Copyright (C) 2010-2020 Alexandre Meyer

This file is part of Grapic.

Grapic is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Grapic is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Grapic.  If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************/

/**
\file Grapic_func.h
\author Alexandre Meyer
*/


#ifndef GRAPIC_FUNC_H
#define GRAPIC_FUNC_H

/// \cond
#include <cassert>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <thread>
#include <chrono>

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

/// \endcond


namespace grapic
{

    /** \brief Initialize the window
    */
    void winInit(const char* name, int w, int h);

    /** \brief Clear the window with the default background color
    */
    void winClear();

    /** \brief return true if the application should be closed (because of 'ESC' or 'q' key pressed for instance)
    */
    bool winHasFinished();

    /** \brief Clear the event queue of the window
    */
    void winClearEvent();

    /** \brief Display the window. All drawing is hidden until this function is not called.
    */
    bool winDisplay();

    /** \brief Quit and close all things
    */
    void winQuit();



    /** \brief Change the default color
    */
	void color(unsigned char _r = 255, unsigned char _g = 255, unsigned char _b = 255, unsigned char _a = 255);

    /** \brief Change the default background color (the color used to clear the screen)
    */
	void backgroundColor(unsigned char _r = 255, unsigned char _g = 255, unsigned char _b = 255, unsigned char _a = 255);

    /** \brief Draw a rectangle from (xmin,ymin) to (xmax,ymax)
    */
	void rectangle(int xmin, int ymin, int xmax, int ymax);

    /** \brief Draw a filled rectangle from (xmin,ymin) to (xmax,ymax)
    */
	void rectangleFill(int xmin, int ymin, int xmax, int ymax);

    /** \brief Draw a line from (x1,y1) to (x2,y2)
    */
	void line(int x1, int y1, int x2, int y2);


    /** \brief Draw a point at (x,y)
    */
	void point(int x, int y);

    /** \brief Draw an array of n points
    */
	void points(int p[][2], int n);


    /** \brief Draw a grid from (xmin,ymin) to (xmax,ymax) with nx columns and ny rows
    */
	void grid(int xmin, int ymin, int xmax, int ymax, int nx, int ny);

    /** \brief return a random number (integer) between rmin to rmax included
    */
	int irand(int rmin=0, int rmax=100);

    /** \brief return a random number (float) between rmin to rmax included
    */
	float frand(float rmin = 0.f, float rmax = 1.f);


    /** \brief return the time elapsed since the beginning of the process
    */
	float elapsedTime();


    /** \brief return the number of time the key 'key' has been pressed since the last call to this function.
        ~~~~~~~~~~~~~~~{.c}
    	if (isKeyPressed(SDL_SCANCODE_LEFT)) { ... }     // test if the left arrow is pressed
    	for(i=0;i<isKeyPressed(SDL_SCANCODE_RIGHT;++i) { // move the character N times to the right...
        ~~~~~~~~~~~~~~~
    */
	int isKeyPressed(int key);
	void setKeyRepeatMode(bool repeat);


    /** \brief Stop the program during d milliseconds
        ~~~~~~~~~~~~~~~{.c}
    	if (isKeyPressed(SDL_SCANCODE_LEFT)) { delay(10); ... }    // if the left arrow is pressed then delay the program to avoid to fast movement
        ~~~~~~~~~~~~~~~
    */
    inline void delay(int d)
    {
        //std::this_thread::sleep_for(std::chrono::milliseconds(d));
        SDL_Delay(d);
    }



    /** \brief return true if the mouse button 'button' is pressed
        ~~~~~~~~~~~~~~~{.c}
        if (isMousePressed(SDL_BUTTON_LEFT)) { ... }    // test if the left button of the mouse is pressed
        ~~~~~~~~~~~~~~~
    */
	bool isMousePressed(int button);


    /** \brief After this function (x,y) store the mouse position
        ~~~~~~~~~~~~~~~{.c}
        int x,y;
        mousePos(x,y);                                                                          // test if the left button of the mouse is pressed
        if ((isMousePressed(SDL_BUTTON_LEFT)) && (x>10) && (y>10) && (x<50) && (y<50)) { ... }  // if the user clicks if the square (10,10)(50,50)
        ~~~~~~~~~~~~~~~
    */
	void mousePos(int& x, int& y);


    /** \brief Manage standard event like key 'ESC', quit, etc.
    */
	bool winManageEvent();


    /** \brief Change the default size of the font
    */
	void fontSize(int s);


    /** \brief Print the text txt , up left corner is (x,y)
        ~~~~~~~~~~~~~~~{.c}
        fontSize(24);                               // Change the default font to the size 24
        print( 10, 20, "Bonjour");                  // Print the text "Bonjour" with the left corner (10,20)
        ~~~~~~~~~~~~~~~
    */
	void print(int x, int y, const char* txt);

    /** \brief Print the integer nb, up left corner is (x,y)
        ~~~~~~~~~~~~~~~{.c}
        print( 10, 20, 128);                      // Print the number "128" with the left corner (10,20)
        ~~~~~~~~~~~~~~~
    */
	void print(int x, int y, int nb);

    /** \brief Print the float nb, up left corner is (x,y)
        ~~~~~~~~~~~~~~~{.c}
        print( 10, 20, 3.1415);                      // Print the number "3.1415" with the left corner (10,20)
        ~~~~~~~~~~~~~~~
    */
	void print(int x, int y, float nb);


    /** \brief Stop the program until key 'space'is pressed
    */
    void pressSpace();




    /// \cond
	struct Image
	{
		Image() : surface(NULL), texture(NULL), has_changed(false) {}
		SDL_Surface* surface;
		SDL_Texture* texture;
		bool has_changed;
	};
    /// \endcond


    /** \brief Return an image loaded from the file filename
        ~~~~~~~~~~~~~~~{.c}
        struct Data
        {
            Image im;
        };
        void init(Data& d)
        {
            d.im = image("data/grapic.bmp", true, 255, 255, 255, 255);      // load the image "data/grapic.bmp" with transparency for the color (255,255,255,255)
        }
        void draw(Data& d)
        {
            image_draw(d.im, 0, 255);                                       // Draw the image with the left corner (0,255)
        }
        ~~~~~~~~~~~~~~~
    */
	Image image(const char* filename, bool transparency=false, unsigned char r=255, unsigned char g=255, unsigned b=255, unsigned char a=255);

    /** \brief Return an image of width=w and height=h
    */
	Image image(int w, int h);

    /** \brief Draw the image at position (x,y) with width=w and height=h (if w<0 or h<0 the original size of the image is used)
    */
	void image_draw(Image& im, int x, int y, int w=-1, int h=-1);

    /** \brief return the color component c of the pixel (x,y) of the image im.
        c must be 0 for the red component, 1 for the green component, 2 for the blue component or 3 for the alpha/opacity component.
    */
	unsigned char image_get(const Image& im, int x, int y, int c);

    /** \brief Set the pixel (x,y) of the image im with the color c
    */
	void image_set(Image& im, int x, int y, unsigned char r, unsigned char g, unsigned b, unsigned char a);

    /** \brief return the width of the image
    */
	inline int image_width(const Image& im) { return im.surface->w; }

    /** \brief return the height of the image
    */
	inline int image_height(const Image& im) { return im.surface->h; }

    /** \brief return true if the image is initialized
        ~~~~~~~~~~~~~~~{.c}
    	d.im = image("data/grapic.bmp", true, 255, 255, 255, 255);
        if (!image_isInit(d.im))                                            // if the image was not loaded, try an other path
            d.im = image("../data/grapic.bmp", true, 255,255,255,255 );
        ~~~~~~~~~~~~~~~
    */
	inline bool image_isInit(const Image& im) { return im.surface && im.texture;  }

    /** \brief Print the informations of the image im
    */
	void image_printInfo(const Image& im);


} // namespace

#endif







/*! \mainpage GrAPiC

<br>
\image html grapic_samples.jpg
<br>
\section intro Introduction

GrAPiC is a small, easy-to-use framework to add graphical functionalities to your C/C++ code. Its main goal is to provide easy
graphical functions to be used in introduction courses of algorithm and programming in C/C++.
It is based on SDL2 but to use it you need to know only few very simples functions.
The Grapic archive comes with the needed SDL part, you do not have to install SDL. Just unzip and enjoy !
<br>
<br>
<br>

\section download Download
Download and install the last version:\htmlinclude "VERSION.html".
Previous versions may be downloaded from the [download](../download) directory.

<br>
<br>
<br>
\section start How to start ?

\subsection win Run on Windows
  - Install Codeblocks from: [http://www.codeblocks.org/downloads](http://www.codeblocks.org/downloads)\n
    Take the one with MinGW like codeblocks-13.12mingw-setup.exe

  - Download the archive file, see section download.

  - Run with CodeBlocks
     - Open the file grapic_win.cbp with Codeblocks.
     - Select in the toolbar the target you want:
       \image html cb_target.jpg "Selection of the target in Codeblocks" width=400
     - And run the program !

\subsection linux Run on Linux
  - Install SDL2, SDL_Image for SDL2 and SDL_ttf for SDL2 ; for instance with
    \code
    sudo apt-get install libsdl2-dev libsdl2-ttf-dev libsdl2-image-dev
    \endcode

  - Download the archive file, see section download.

  - Run with CodeBlocks
     - Open the file grapic_win.cbp with Codeblocks.
     - Select in the toolbar the target you want:
       \image html cb_target.jpg "Selection of the target in Codeblocks" width=400
     - And run the program !
  - Run in the Terminal:
     - cd grapic
     - make
     - bin/demo


\subsection mac Run on MacOS
  - Download the archive file, see section download.

  - Run in the Terminal:
     - cd grapic
     - make
     - bin/demo

\subsection edit Edit my first program
The kernel source code of grapic is in grapic/src.
The source codes of the demos are in grapic/apps.
You can create your own program by editing the file grapic/apps/myprog/main_myprog.cpp
\image html cb_myprogcpp.jpg width=10



<br>
<br>
<br>
\section tutorial Tutorial
\image html simple.jpg "The simpleDrawing code illustrates the basis of Grapic" width=200px
\include "../../apps/simpleDrawing/main_simpleDrawing.cpp"


<br>
<br>
<br>
\section myfirstprog My First Program
\include "../../apps/myprog/main_myprog.cpp"

<br>
<br>
<br>
\section demo Demo
\image html demo.jpg "The demo code illustrates many functionalities of Grapic" width=200px
\include "../../apps/demo/main_demo.cpp"


<br>
<br>
<br>
\section Examples

Grapic comes with several small examples. It can be used as source of inspiration.

\subsection particles Particles
\image html particles.jpg "Falling and bouncing particles simulated by a physical simulation" width=200px
\include "../../apps/particles/main_particles.cpp"


\subsection tetris Tetris
\image html tetris.jpg "A example of tetris" width=200px
\include "../../apps/tetris/main_tetris.cpp"

\subsection fluid Fluid
\image html fluid.jpg "An easy to understand Particles-In-Cell (PIC) simulation of fluid" width=200px
\include "../../apps/fluid/main_fluid.cpp"

\subsection pacman Pacman
\image html pacman.jpg "Pacman" width=200px
\include "../../apps/pacman/main_pacman.cpp"







*/
