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
#include <Grapic.h>
#include <cstdio>

namespace grapic
{

#define ESCAPE 27
#define PAGE_UP 73
#define PAGE_DOWN 81
#define UP_ARROW 72
#define DOWN_ARROW 80
#define LEFT_ARROW 75
#define RIGHT_ARROW 77


	//Data Grapic::m_data;
	grapic::Grapic Grapic::currentGrapic;


	Grapic::Grapic() :
			m_width(-1),
            m_height(-1),
            m_window(NULL),
            m_renderer(NULL),
            m_font(NULL),
            m_fontFile(""),
            m_fontSize(-1),
            m_quit(false),
            m_anim(false),
            //m_currentColor({0,0,0,255}),
            //m_backgroundColor({255,255,255,255}),
            m_keyRepeatMode(true)
	{
		//currentGrapic = this;
        m_currentColor.r = 0;
        m_currentColor.g = 0;
        m_currentColor.b = 0;
        m_currentColor.a = 255;
        m_backgroundColor.r = 255;
        m_backgroundColor.g = 255;
        m_backgroundColor.b = 255;
        m_backgroundColor.a = 255;
	}


	void Grapic::help() const
	{
		printf("Help:\n");
		printf("   q,ESC: quit\n");
		printf("   f,F: fullscreen\n");
		printf("   h: help\n");
	}

    void Grapic::copyFrontToBackBuffer()
    {
        //SDL_RenderReadPixels( m_renderer, NULL, 0, buffer, 0);


    }




} // namespace
