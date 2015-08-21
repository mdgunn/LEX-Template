/********************************************************************
*		Copyright (c) 2014-2015, reepblue. All rights reserved.		*
*                                                                   *
*		This product contains software technology licensed from     *
*				 Leadwerks Software. All Rights Reserved.           *
********************************************************************/

#if !defined( SLIDER_H )
#define SLIDER_H
#pragma once

#include "../main.h"
#include "contextbuttons.h"

namespace LEX
{
	class SliderBox : public RectButton
	{
	public:
		SliderBox(short pWorldPosX = 0, short pWorldPosY = 0, short pWidth = 16, short pHeight = 32);
		virtual ~SliderBox();

		virtual void HandleMouseEvent(void) { RectButton::HandleMouseEvent(); };
		virtual void Render(void);
		virtual void DrawBorder() { RectButton::DrawBorder(); };

		virtual void SetSliderPosition(short x)
		{
			posX = x;
			worldPosX = x;
		}

		short GetSliderPosition()
		{
			return posX;
		}

		virtual void SetMinDistance(short min)
		{
			m_shortSliderMin = min;
		}

		virtual void SetMaxDistance(short max)
		{
			m_shortSliderMax = max;
		}

		short GetX()
		{
			return posX;
		}

		short GetY()
		{
			return posY;
		}

		short GetWidth()
		{
			return width;
		}

		short GetHeight()
		{
			return height;
		}


	private:
		short m_shortSliderMin;
		short m_shortSliderMax;
		int m_intvalue;

	};


	class Slider
	{
	public:
		Slider(short pWorldPosX = 0, short pWorldPosY = 0);
		virtual ~Slider();
		virtual void Update();

		virtual void SetPosition(short x, short y)
		{
			posX = x;
			posY = y;

			worldPosX = x;
			worldPosY = y;
		}

		int GetValue()
		{
			return m_intvalue;
		}

		short GetX()
		{
			return posX;
		}

		short GetY()
		{
			return posY;
		}

		short GetWidth()
		{
			return width;
		}

		short GetHeight()
		{
			return slider->GetHeight();
		}

		// Takes rrr,ggg,bbb then divides by 255 to turn it into a vector.
		virtual void SetTextColor(float r, float g, float b)
		{
			r = r / 255;
			g = g / 255;
			b = b / 255;

			m_vec3TextColor.x = r;
			m_vec3TextColor.y = g;
			m_vec3TextColor.z = b;
		};

		Vec3 GetTextColor()
		{
			return m_vec3TextColor;
		}

		// Takes rrr,ggg,bbb then divides by 255 to turn it into a vector.
		virtual void SetTrackColor(float r, float g, float b)
		{
			r = r / 255;
			g = g / 255;
			b = b / 255;

			m_vec3TrackColor.x = r;
			m_vec3TrackColor.y = g;
			m_vec3TrackColor.z = b;
		};

		Vec3 GetTrackColor()
		{
			return m_vec3TrackColor;
		}

		// Takes rrr,ggg,bbb then it passes through the slider function which divides by 255 to turn it into a vector.
		virtual void SetSliderColor(float r, float g, float b)
		{
			slider->SetColor(r, g, b);
		};

		// Takes rrr,ggg,bbb then it passes through the slider function which divides by 255 to turn it into a vector.
		virtual void SetSliderBorderColor(float r, float g, float b)
		{
			slider->SetBorderColor(r, g, b);
		};

		void SetLabel(string pLabel)
		{
			m_title = pLabel;
		}

		void SetSliderPosition(short x)
		{
			slider->SetSliderPosition(posX + x);
		}

		/*
		void SetMinValue(int pVal)
		{
			m_intminvalue = pVal;
			slider->SetMinDistance(posX + m_intminvalue);
		}
		*/

		void SetMaxValue(int pVal)
		{
			m_intmaxvalue = pVal;
			width = posX + m_intmaxvalue + slider->GetWidth();
			slider->SetMaxDistance(width - posX);
		}

	private:
		SliderBox* slider;
		short worldPosX;
		short worldPosY;
		short posX;
		short posY;

		short width;

		int m_intminvalue = 0;
		int m_intmaxvalue = 100;
		int m_intvalue;

		Vec3 m_vec3TextColor;
		Vec3 m_vec3TrackColor;

		Leadwerks::Font* titlefont;
		std::string m_title;
	};
}

#endif //SLIDER_H