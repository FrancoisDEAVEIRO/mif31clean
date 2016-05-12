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

#ifndef GRAPIC_H
#define GRAPIC_H

#include <cassert>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>

#include <Grapic_func.h>

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>



//! \todo Circle

//! \todo Finish coding the game "dame"




namespace grapic
{


	/**
	* @brief The Grapic class
	*/
	class Grapic
	{
	public:
		Grapic();

        void init(const char* name, int w, int h);
        void clear();
        void clearEvent();
        bool display();
        bool hasFinished()  { return m_quit; }
        void quit();

		inline void color(unsigned char r, unsigned char g, unsigned b, unsigned char a);
		inline SDL_Color& getColor();
		inline void backgroundColor(unsigned char r, unsigned char g, unsigned b, unsigned char a);
		inline int inverseY(int y);
		inline void setFont(int s, const char* ttf=NULL);
		SDL_Window* window() { return m_window;  }
		SDL_Renderer * renderer() { return m_renderer;  }
		TTF_Font* font() { return m_font; }
        int keyHasBeenPressed(unsigned int sc);
        void setKeyRepeatMode(bool kr);

		static Grapic& singleton() { return currentGrapic; }
        bool manageEvent();

	protected:
		int m_width;
		int m_height;
		SDL_Window* m_window;
		SDL_Renderer *m_renderer;
		TTF_Font *m_font;
		std::string m_fontFile;
		int m_fontSize;
		bool m_quit;
		bool m_anim;
		SDL_Color m_currentColor;
		SDL_Color m_backgroundColor;
		std::vector<int> m_key;
		bool m_keyRepeatMode;

		void manageKeyPressed(SDL_KeyboardEvent& ke);
        void initKeyArray();
        void copyFrontToBackBuffer();
		void help() const;

		static Grapic currentGrapic;
	};






	inline void Grapic::init(const char* name, int w, int h)
	{
		// Initialisation de la SDL
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			std::cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << std::endl;
			SDL_Quit();
			assert(0);
			exit(1);
		}

        if (TTF_Init() != 0)
        {
			std::cout << "Erreur lors de l'initialisation de la SDL_ttf : " << SDL_GetError() << std::endl;
            SDL_Quit();
            assert(0);
            exit(1);
        }

        int imgFlags = IMG_INIT_PNG;
        if( !( IMG_Init( imgFlags ) & imgFlags ) )
        {
            printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
            SDL_Quit();
            assert(0);
            exit(1);
        }

        //system("cd");
        setFont( 20, "data/ttf/Raleway-Regular.ttf");

		// Creation de la fenetre
		m_window = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		if (m_window == NULL)
		{
			std::cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << std::endl;
			SDL_Quit();
			assert(0);
			exit(1);
		}

		SDL_SetWindowTitle(m_window, name);

		m_renderer = SDL_CreateRenderer( m_window, -1, SDL_RENDERER_ACCELERATED);

		m_width = w;
		m_height = h;
		m_quit = false;
		m_anim = false;

        initKeyArray();
		help();
	}

	inline void Grapic::initKeyArray()
	{
        int ksize;
        SDL_GetKeyboardState(&ksize);
        m_key.resize(ksize);
        unsigned int i;
        for(i=0;i<m_key.size();++i) m_key[i]=0;
	}

	inline void Grapic::clear()
    {
        // Clear the entire screen to our selected color.
        SDL_SetRenderDrawColor(m_renderer, m_backgroundColor.r, m_backgroundColor.g, m_backgroundColor.b, m_backgroundColor.a);
        SDL_RenderClear(m_renderer);
        SDL_SetRenderDrawColor(m_renderer, m_currentColor.r, m_currentColor.g, m_currentColor.b, m_currentColor.a);
    }

   	inline void Grapic::clearEvent()
    {
		SDL_Event events;
        SDL_PumpEvents();
        while (SDL_PollEvent(&events))
        {
        }
        initKeyArray();
    }


	inline bool Grapic::manageEvent()
    {
		SDL_Event events;
        SDL_PumpEvents();
        while (SDL_PollEvent(&events))
        {
            switch (events.type)
            {
                case SDL_QUIT:
                    m_quit = true;
                    break;
                case SDL_KEYDOWN:
                    if ((events.key.repeat == 1) && (m_keyRepeatMode))
                        m_key[events.key.keysym.scancode]++;
                    else if (events.key.repeat == 0)
                        m_key[events.key.keysym.scancode]++;
                    manageKeyPressed(events.key);
                    break;
                default:
                    break;
            }
        }
        return m_quit;
    }


	inline bool Grapic::display()
    {
        manageEvent();
        SDL_RenderPresent(m_renderer);
        copyFrontToBackBuffer();
        return m_quit;
    }


	inline void Grapic::quit()
	{
        TTF_CloseFont(m_font);
        SDL_DestroyWindow(m_window);
		SDL_Quit();
	}


    inline int Grapic::keyHasBeenPressed(unsigned int sc)
    {
        if (sc>=m_key.size()) return 0;
        bool r = m_key[sc];
		const Uint8 *state = SDL_GetKeyboardState(NULL);
		if (m_keyRepeatMode)
            m_key[sc] = state[sc];
        else
            m_key[sc] = 0;
        //std::cout<<m_key[sc]<<" "<<r<<std::endl;
        return r;
    }


    inline void Grapic::setKeyRepeatMode(bool kr)
    {
       m_keyRepeatMode = kr;
       //if (kr) SDL_EnableKeyRepeat(0, 0);
       //else SDL_EnableKeyRepeat( SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
    }


	inline void Grapic::manageKeyPressed(SDL_KeyboardEvent& ke)
	{
		unsigned char keyuc = (unsigned char)(ke.keysym.sym);
		//int key = ke.keysym.sym;
		const Uint8 *state = SDL_GetKeyboardState(NULL);
		if (state[SDL_SCANCODE_LSHIFT] || state[SDL_SCANCODE_RSHIFT]) keyuc += 'A' - 'a';
		switch (keyuc)
		{
		case 'q':
		case 27:
			m_quit = true;
			break;

		case 'f':
			SDL_SetWindowFullscreen(m_window, 0);
			printf("Windows mode\n");
			break;
		case 'F':
			SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN_DESKTOP);
			printf("Fullscreen mode\n");
			break;

		case 'h':
		case 'H':
			help();
			break;

		default:
			break;
		}
	}


	inline void Grapic::color(unsigned char r, unsigned char g, unsigned b, unsigned char a)
	{
		m_currentColor.r = r;
		m_currentColor.g = g;
		m_currentColor.b = b;
		m_currentColor.a = a;
		SDL_SetRenderDrawColor(m_renderer, m_currentColor.r, m_currentColor.g, m_currentColor.b, m_currentColor.a);
	}


	inline SDL_Color& Grapic::getColor()
	{
	    return m_currentColor;
	}


	inline void Grapic::backgroundColor(unsigned char r, unsigned char g, unsigned b, unsigned char a)
	{
		m_backgroundColor.r = r;
		m_backgroundColor.g = g;
		m_backgroundColor.b = b;
		m_backgroundColor.a = a;
	}


	inline int Grapic::inverseY(int y)
	{
		SDL_GetRendererOutputSize(m_renderer, &m_width, &m_height);
		return m_height - y - 1;
	}


	inline void Grapic::setFont(int s, const char* ttf)
	{
        if ((m_fontSize==s) && (ttf && m_fontFile==std::string(ttf))) return;
	    if (m_font) TTF_CloseFont(m_font);
	    m_fontSize = s;
	    if (ttf) m_fontFile = ttf;
        m_font = TTF_OpenFont( m_fontFile.c_str(), m_fontSize);
        if (!m_font) m_font = TTF_OpenFont( ("../"+m_fontFile).c_str(), m_fontSize);
        if (!m_font) m_font = TTF_OpenFont( ("../../"+m_fontFile).c_str(), m_fontSize);
        if (!m_font)
        {
			std::cout << "Erreur lors de l'initialisation de la police : " << SDL_GetError() << std::endl;
            SDL_Quit();
            assert(0);
            exit(1);
        }
	}



} // namespace

#endif
