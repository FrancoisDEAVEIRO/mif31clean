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


#include <cassert>
#include <ctime>

#include <Grapic_func.h>
#include <Grapic.h>

namespace grapic
{

	SDL_Renderer* renderer()
	{
		return Grapic::singleton().renderer();
	}

    void winInit(const char* name, int w, int h)
    {
        Grapic::singleton().init(name,w,h);
    }

    void winClear()
    {
        Grapic::singleton().clear();
    }

    void winClearEvent()
    {
        Grapic::singleton().clearEvent();
    }

    bool winHasFinished()
    {
        return Grapic::singleton().hasFinished();
    }

    bool winDisplay()
    {
        return Grapic::singleton().display();
    }

    void winQuit()
    {
        Grapic::singleton().quit();
    }

	void color(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a)
	{
		Grapic::singleton().color( _r, _g, _b, _a );
	}


	void backgroundColor(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a)
	{
		Grapic::singleton().backgroundColor( _r, _g, _b, _a);
	}

    void pressSpace()
    {
        winClearEvent();
        winDisplay();
        print(10,10,"Press space");
        winDisplay();
        printf("Press space\n");

        while(!winHasFinished() && !isKeyPressed(SDL_SCANCODE_SPACE))
        {
            Grapic::singleton().manageEvent();
            delay(50);
        }
    }

  	bool winManageEvent()
	{
	    return Grapic::singleton().manageEvent();
	}


	void rectangle(int xmin, int ymin, int xmax, int ymax)
	{
		Grapic& g = Grapic::singleton();
		SDL_Rect r;
		r.x = xmin;
		r.y = g.inverseY(ymax);
		r.w = xmax - xmin + 1;
		r.h = ymax - ymin + 1;
		SDL_RenderDrawRect(renderer(), &r);
	}

	void rectangleFill(int xmin, int ymin, int xmax, int ymax)
	{
		Grapic& g = Grapic::singleton();
		SDL_Rect r;
		r.x = xmin;
		r.y = g.inverseY(ymax);
		r.w = xmax - xmin + 1;
		r.h = ymax - ymin + 1;
		SDL_RenderFillRect(renderer(), &r);
	}


	//void circle(int xcenter, int ycenter, int radius)
	//{
	//}


	void line(int xmin, int ymin, int xmax, int ymax)
	{
		Grapic& g = Grapic::singleton();
		SDL_RenderDrawLine(renderer(), xmin, g.inverseY(ymin), xmax, g.inverseY(ymax));
	}

	void point(int x, int y)
	{
		Grapic& g = Grapic::singleton();
		SDL_RenderDrawPoint(renderer(), x, g.inverseY(y));
	}

	void points(int p[][2], int n)
	{
		//Grapic& g = Grapic::singleton();
		SDL_RenderDrawPoints(renderer(), ((const SDL_Point*)(p)), n);
	}

	void grid(int xmin, int ymin, int xmax, int ymax, int nx, int ny)
	{
		int i;
		//Grapic& g = Grapic::singleton();
		++nx;
		++ny;
		float stepx = static_cast<float>(xmax - xmin) / (nx - 1);
		float stepy = static_cast<float>(ymax - ymin) / (ny - 1);
		for (i = 0; i < nx; ++i)
			line(xmin + stepx*i, ymin, xmin + stepx*i, ymax);
		for (i = 0; i < ny; ++i)
			line(xmin, ymin + stepy*i, xmax, ymin + stepy*i);
	}

	int irand(int rmin, int rmax)
	{
		return rmin + rand() % (rmax - rmin + 1);
	}

	float frand(float rmin, float rmax)
	{
		float r = static_cast<float>(rand()) / RAND_MAX;
		return rmin + r * (rmax - rmin);
	}

	float elapsedTime()
	{
		return float(clock()) / CLOCKS_PER_SEC;
	}



	int isKeyPressed(int key)
	{
		Grapic& g = Grapic::singleton();
		//SDL_PumpEvents();
		//int siz;
		//const Uint8 *state = SDL_GetKeyboardState(&siz);
		//if (state[key]>0) SDL_Delay(10);
		return (g.keyHasBeenPressed(key)); // || (state[key]>0) );
	}

	void setKeyRepeatMode(bool repeat)
	{
        Grapic& g = Grapic::singleton();
        g.setKeyRepeatMode(repeat);
	}


	bool isMousePressed(int button)
	{
		//SDL_PumpEvents();
		return SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(button);
	}

	void mousePos(int& x, int& y)
	{
		SDL_PumpEvents();
		SDL_GetMouseState(&x, &y);
		Grapic& g = Grapic::singleton();
		y = g.inverseY(y);
	}



	void fontSize(int s)
	{
		Grapic::singleton().setFont(s);
	}

	void print(int x, int y, int nb)
	{
	    char txt[32];
	    sprintf(txt,"%d", nb);
	    print(x,y,txt);
	}

	void print(int x, int y, float nb)
	{
	    char txt[32];
	    sprintf(txt,"%f", nb);
	    print(x,y,txt);
	}

	void print(int x, int y, const char* txt)
	{
		Grapic& g = Grapic::singleton();
		//SDL_Color White = {255, 0, 255};
		//Color c = g.getColor();
		//SDL_Color color = c;
        SDL_Surface* textSurface = TTF_RenderText_Solid( g.font(), txt, g.getColor() );
        SDL_Texture* text = SDL_CreateTextureFromSurface( g.renderer(), textSurface);
        int text_width = textSurface->w;
        int text_height = textSurface->h;
        SDL_FreeSurface(textSurface);
        SDL_Rect renderQuad = { x, g.inverseY(y+text_height), text_width, text_height };
        SDL_RenderCopy( g.renderer(), text, NULL, &renderQuad);
        SDL_DestroyTexture(text);
	}



	unsigned char image_get(const Image& im, int x, int y, int c)
	{
		SDL_Surface* surface = im.surface;
		/* Extracting color components from a 32-bit color value */
		SDL_PixelFormat *fmt;
		Uint32 pixel;
		Uint8 red, green, blue, alpha;

		fmt = surface->format;
		SDL_LockSurface(surface);
		pixel = ((Uint32*)surface->pixels) [((surface->h - 1 - y) * surface->w) + x];
		SDL_UnlockSurface(surface);

		SDL_GetRGBA( pixel, fmt, &red, &green, &blue, &alpha);

        switch(c)
        {
            case 0: return red;
            case 1: return green;
            case 2: return blue;
            case 3: return alpha;
            default: return red;
        }
		//return SDL_Color( {red, green, blue, alpha} );
	}

	void image_set( Image& im, int x, int y, unsigned char r, unsigned char g, unsigned b, unsigned char a)
	{
		SDL_Surface* surface = im.surface;
		if ((x<0) || (y<0) || (x>=surface->w) || (y>=surface->h)) return;
		//Convert the pixels to 32 bit
		Uint32 *pixels = (Uint32 *)surface->pixels;
		//Set the pixel
		SDL_PixelFormat *fmt;
		fmt = surface->format;
		SDL_LockSurface(surface);
		pixels[( (surface->h-1-y) * surface->w) + x] = SDL_MapRGBA(fmt, r,g,b,a);
		SDL_UnlockSurface(surface);
		im.has_changed = true;
	}



	Image image(const char* filename, bool transparency,  unsigned char r, unsigned char g, unsigned b, unsigned char a)
	{
		Grapic& gp = Grapic::singleton();
		Image res;

		//res.surface = SDL_LoadBMP(filename);
		res.surface = IMG_Load(filename);
		if (res.surface == NULL)
        {
            std::string nfn = std::string("../") + filename;
			std::cout<<"error: Can not load "<< filename<<". Trying "<<nfn<<std::endl;;
            res.surface = IMG_Load(nfn.c_str());
            if (res.surface == NULL)
            {
                nfn = std::string("../") + nfn;
                res.surface = IMG_Load(nfn.c_str());
            }
        }
		if (res.surface == NULL)
		{
			std::cout<<"error: Can not load "<< filename<<std::endl;
			return res;
		}

		if (transparency)
        {
            SDL_Color c;
            c.r=r;
            c.g=g;
            c.b=b;
            c.a=a;
            Uint32 cc = *((Uint32*)(&c));
            SDL_SetColorKey(res.surface, SDL_TRUE, cc);
        }

		//res.texture = SDL_CreateTexture(g.renderer(), SDL_PIXELFORMAT_ARGB8888, 	SDL_TEXTUREACCESS_STREAMING,	res.surface->w, res.surface->h);
		res.texture = SDL_CreateTextureFromSurface( gp.renderer(), res.surface);

		if (res.texture == NULL)
		{
			printf("error: problem to create the texture of %s\n", filename);
			return res;
		}

		//int ok = SDL_UpdateTexture(res.texture, NULL, res.surface->pixels, res.surface->pitch);
		//assert(ok==0);

		printf("Image loaded: %s\t", filename);
		image_printInfo(res);

		return res;
	}



	Image image(int w, int h)
	{
		Grapic& g = Grapic::singleton();
		Image res;
		res.surface = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);
		if (res.surface == NULL)
		{
			printf("error: Can not create this surface: %dx%d\n", w, h);
			return res;
		}

		res.texture = SDL_CreateTexture( g.renderer(), SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, res.surface->w, res.surface->h);
		if (res.texture == NULL)
		{
			printf("error: problem to create the texture\n");
			return res;
		}

		res.has_changed = false;

		return res;
	}


	void image_draw(Image& im, int x, int y, int w, int h)
	{
		int ok;
		Grapic& g = Grapic::singleton();
		SDL_Rect r;
		r.x = x;
		r.y = y;
		r.w = (w<0)?im.surface->w:w;
		r.h = (h<0)?im.surface->h:h;
		r.y = g.inverseY( r.y+r.h);
		//int res = SDL_BlitSurface(im, NULL, SDL_GetWindowSurface(g.window()), &r);
		//assert(res == 0);

		if (im.has_changed)
		{
			ok = SDL_UpdateTexture(im.texture, NULL, im.surface->pixels, im.surface->pitch);
			assert(ok == 0);
			im.has_changed = false;
		}

		ok = SDL_RenderCopy(g.renderer(), im.texture, NULL, &r);
		//ok = SDL_RenderCopyEx(g.renderer(), im.texture, NULL, &r, 0, NULL, SDL_FLIP_NONE);
		assert(ok == 0);
		//SDL_RenderPresent(g.renderer());
		//int SDL_RenderCopyEx(SDL_Renderer*          renderer,
		//	SDL_Texture*           texture,
		//	const SDL_Rect*        srcrect,
		//	const SDL_Rect*        dstrect,
		//	const double           angle,
		//	const SDL_Point*       center,
		//	const SDL_RendererFlip flip)
	}


	void image_printInfo(const Image& im)
	{
		if (!image_isInit(im))
		{
			printf("image not initialized\n");
			return;
		}
		printf("image: %dx%d format=%d pitch=%d\n", im.surface->w, im.surface->h, im.surface->format->format, im.surface->pitch);
	}



} // namespace
