/********************************************************************
*		Copyright (c) 2014-2015, reepblue. All rights reserved.		*
*                                                                   *
*		This product contains software technology licensed from     *
*				 Leadwerks Software. All Rights Reserved.           *
********************************************************************/

#if !defined( CHOOSER_H )
#define CHOOSER_H
#pragma once

#include "../main.h"
#include "contextbuttons.h"
namespace LEX
{
	class Chooser
	{
	public:
		Chooser(short pWorldPosX = 0, short pWorldPosY = 0, short pWidth = 83, short pHeight = 22);
		virtual ~Chooser();
		virtual void LoadScheme();
		virtual void Update();
		virtual void Render(void);
		virtual void DrawBorder();
		virtual void Logic();


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

		// Takes rrr,ggg,bbb then divides by 255 to turn it into a vector.
		virtual void SetArrowColor(float r, float g, float b)
		{
			r = r / 255;
			g = g / 255;
			b = b / 255;

			m_vec3ArrowColor.x = r;
			m_vec3ArrowColor.y = g;
			m_vec3ArrowColor.z = b;
		};

		Vec3 GetArrowColor()
		{
			return m_vec3ArrowColor;
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

			chooserfont = Leadwerks::Font::Load(pFont, pSize);
		}

		virtual void SetFontFile(Leadwerks::Font* pFont)
		{
			chooserfont = pFont;
		}

		void SetLabel(std::string ptxt)
		{
			if (ptxt != S_NULL)
			{
				// Make sure the text can fit in the button.
				if (chooserfont->GetTextWidth(ptxt) > width)
				{
					width = chooserfont->GetTextWidth(ptxt) + 16;
				}

				if (chooserfont->GetHeight() > height)
				{
					height = chooserfont->GetHeight() + 16;
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

		void SetChooseOption(int pin)
		{
			m_intoption = pin;
		}

		int GetChooseOption()
		{
			return m_intoption;
		}

		void SetMinOptionValue(int pin)
		{
			m_intminoption = pin;
		}

		void SetMaxOptionValue(int pin)
		{
			m_intmaxoption = pin;
		}

		int GetMinOptionValue()
		{
			return m_intminoption;
		}

		int GetMaxOptionValue()
		{
			return m_intmaxoption;
		}

		void SetIncreaseRate(int pin)
		{
			m_intincreaserate = pin;
		}

		int GetIncreaseRate()
		{
			return m_intincreaserate;
		}

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
		Vec3 m_vec3ArrowColor;

		Leadwerks::Font* chooserfont;
		std::string m_btnmsg;

		ImageButton* backbutton;
		ImageButton* nextbutton;

		int m_intoption;
		int m_intminoption;
		int m_intmaxoption;
		int m_intincreaserate = 1;
	};

	class Chooser3 : public Chooser
	{
	public:
		Chooser3(short pWorldPosX = 0, short pWorldPosY = 0, short pWidth = 83, short pHeight = 22);
		virtual ~Chooser3();
		virtual void Update() { Chooser::Update(); };
		virtual void Render(void) { Chooser::Render(); };
		virtual void DrawBorder() { Chooser::DrawBorder(); };
		virtual void Logic();
	};

	class ChooserMSAA : public Chooser
	{
	public:
		ChooserMSAA(short pWorldPosX = 0, short pWorldPosY = 0, short pWidth = 83, short pHeight = 22);
		virtual ~ChooserMSAA();
		virtual void Update() { Chooser::Update(); };
		virtual void Render(void) { Chooser::Render(); };
		virtual void DrawBorder() { Chooser::DrawBorder(); };
		virtual void Logic();

		void SetMSAAOptionValue(int pint)
		{
			m_intfinaloption = pint;
		}

		int GetMSAAOptionValue()
		{
			return m_intfinaloption;
		}

		int GetRelativeOptionValue()
		{
			if (m_intfinaloption == 1)
			{
				m_intoption = 1;
			}

			if (m_intfinaloption == 2)
			{
				m_intoption = 2;
			}

			if (m_intfinaloption == 4)
			{
				m_intoption = 3;
			}

			if (m_intfinaloption == 8)
			{
				m_intoption = 4;
			}

			if (m_intfinaloption == 16)
			{
				m_intoption = 5;
			}

			return m_intoption;
		}

	private:
		int m_intfinaloption;
	};
}
#endif //CHOOSER_H