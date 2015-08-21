/********************************************************************
*		Copyright (c) 2014-2015, reepblue. All rights reserved.		*
*                                                                   *
*		This product contains software technology licensed from     *
*				 Leadwerks Software. All Rights Reserved.           *
********************************************************************/

#if !defined( NUMBERDISPLAY_H )
#define NUMBERDISPLAY_H
#pragma once

#include "../main.h"
#include "contextbuttons.h"

namespace LEX
{
	class NumberDisplay
	{
	public:
		NumberDisplay(short pWorldPosX = 0, short pWorldPosY = 0, short pWidth = 0, short pHeight = 22);
		virtual ~NumberDisplay();
		virtual void Update();
		virtual void Render(void);
		virtual void DrawBorder();

		virtual void SetPosition(short x, short y)
		{
			posX = x;
			posY = y;

			worldPosX = x;
			worldPosY = y;
		}

		short GetX()
		{
			return posX;
		}

		short GetY()
		{
			return posY;
		}

		void SetSize(short w, short h)
		{
			width = w;
			height = h;
		}

		short GetWidth()
		{
			return width;
		}

		short GetHeight()
		{
			return height;
		}

		void SetSize(Vec2 size)
		{
			width = size.x;
			height = size.y;
		}

		// Takes rrr,ggg,bbb then divides by 255 to turn it into a vector.
		virtual void SetColor(float r, float g, float b)
		{
			r = r / 255;
			g = g / 255;
			b = b / 255;

			m_vec3Color.x = r;
			m_vec3Color.y = g;
			m_vec3Color.z = b;

		};

		Vec3 GetColor()
		{
			return m_vec3Color;
		}

		virtual void SetAlpha(float a)
		{
			m_flAlpha = a / 255;
		}

		virtual float GetAlpha()
		{
			return m_flAlpha;
		}

		// Takes rrr,ggg,bbb then divides by 255 to turn it into a vector.
		virtual void SetBorderColor(float r, float g, float b)
		{
			r = r / 255;
			g = g / 255;
			b = b / 255;

			m_vec3BorderColor.x = r;
			m_vec3BorderColor.y = g;
			m_vec3BorderColor.z = b;
		};

		Vec3 GetBorderColor()
		{
			return m_vec3BorderColor;
		}

		short GetBorderLineWidth(void)
		{
			return borderLineWidth;
		}

		void SetBorderLineWidth(short width)
		{
			borderLineWidth = width;
		}

		virtual void SetVisible(bool b)
		{
			m_bVisible = b;
		};

		virtual void Show()
		{
			m_bVisible = true;
		}

		virtual void Hide()
		{
			m_bVisible = false;
		}

		virtual void SetFont(std::string pFont = FONT_ARIAL, int pSize = 10)
		{
			if (pFont == S_NULL || pSize == NULL)
			{
				return;
			}

			displayfont = Leadwerks::Font::Load(pFont, pSize);
		}

		void Display(std::string ptxt)
		{
			if (ptxt != S_NULL)
			{
				// Make sure the text can fit in the button.
				if (displayfont->GetTextWidth(ptxt) > width)
				{
					width = displayfont->GetTextWidth(ptxt) + 16;
				}

				if (displayfont->GetHeight() > height)
				{
					height = displayfont->GetHeight() + 16;
				}
			}

			if (ptxt != m_btnmsg)
			{
				m_btnmsg = ptxt;
			}

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

	private:
		short worldPosX;
		short worldPosY;
		short posX;
		short posY;
		short width;
		short height;
		short borderLineWidth;
		bool m_bVisible = true;

		Vec3 m_vec3Color;
		Vec3 m_vec3TextColor;
		float m_flAlpha;
		Vec3 m_vec3BorderColor;

		Leadwerks::Font* displayfont;
		std::string m_btnmsg;
	};
}

#endif // NUMBERDISPLAY_H