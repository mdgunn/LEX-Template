/********************************************************************
*		Copyright (c) 2014-2015, reepblue. All rights reserved.		*
*                                                                   *
*		This product contains software technology licensed from     *
*				 Leadwerks Software. All Rights Reserved.           *
********************************************************************/

#if !defined( BASEPANEL_H )
#define BASEPANEL_H
#pragma once

#include "../main.h"
#include "contextbuttons.h"

namespace LEX
{
	class BasePanel
	{
	public:
		BasePanel(short pWidth = 800, short pHeight = 600, short pWorldPosX = 0, short pWorldPosY = 0, bool pCenter = true, short pBorderWidth = 1);
		virtual ~BasePanel();

		/*
		virtual void HandleMouseEvent(void);
		virtual int GetMouseEvent()
		{
			return mouseEvent;
		}

		int mouseEvent;
		int prevMouseEvent;
		*/

		virtual void LoadScheme();

		virtual void SetPosition(short x, short y)
		{
			posX = x - GetWidth() / 2;
			posX = y - GetHeight() / 2;

			worldPosX = x;
			worldPosY = y;
		}

		virtual short GetX()
		{
			return posX;
		}

		virtual short GetY()
		{
			return posY;
		}

		virtual void SetSize(short w, short h)
		{
			width = w;
			height = h;
		}

		virtual short GetWidth()
		{
			return width;
		}

		virtual short GetHeight()
		{
			return height;
		}

		virtual void SetSize(Vec2 size)
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

		// Takes rrr,ggg,bbb then divides by 255 to turn it into a vector.
		virtual void SetLabelColor(float r, float g, float b)
		{
			r = r / 255;
			g = g / 255;
			b = b / 255;

			m_vec3LabelColor.x = r;
			m_vec3LabelColor.y = g;
			m_vec3LabelColor.z = b;
		};

		Vec3 GetLabelColor()
		{
			return m_vec3LabelColor;
		}

		// Takes rrr,ggg,bbb then divides by 255 to turn it into a vector.
		virtual void SetMessageColor(float r, float g, float b)
		{
			r = r / 255;
			g = g / 255;
			b = b / 255;

			m_vec3MessageColor.x = r;
			m_vec3MessageColor.y = g;
			m_vec3MessageColor.z = b;
		};

		Vec3 GetMessageColor()
		{
			return m_vec3MessageColor;
		}

		virtual void SetLabelFont(std::string pFont = FONT_ARIAL, int pSize = 16)
		{
			if (pFont == S_NULL || pSize == NULL)
			{
				return;
			}

			labelfont = Leadwerks::Font::Load(pFont, pSize);
		}
		/*
		virtual void SetLabelFont(Leadwerks::Font* pFont)
		{
			labelfont = pFont;
		}
		*/
		virtual void SetMessageFont(std::string pFont = FONT_ARIAL, int pSize = 10)
		{
			if (pFont == S_NULL || pSize == NULL)
			{
				return;
			}

			messagefont = Leadwerks::Font::Load(pFont, pSize);
		}
		/*
		virtual void SetMessageFont(Leadwerks::Font* pFont)
		{
			messagefont = pFont;
		}
		*/
		Leadwerks::Font* GetLabelFont()
		{
			return labelfont;
		}


		Leadwerks::Font* GetMessageFont()
		{
			return messagefont;
		}

		virtual void Draw();
		virtual bool Drawing()
		{
			return m_bDrawing;
		}

		virtual void DrawBorder();

		virtual void Open(bool pFadeIn = true);
		virtual void Close(bool pFadeout = true);

		virtual void SetLabel(std::string pTitle);
		virtual void SetMessage(std::string pMsg);

		/*
		ImageButton* CloseButton;
		*/

	protected:
		/*
		void CreateCloseButton()
		{
			Leadwerks::Texture* closeicon = Leadwerks::Texture::Load("materials/vgui/icons/close.tex");
			CloseButton = new ImageButton(closeicon, posX + GetWidth() - 20, posY + 4);
		}
		*/

		bool m_bDrawing = false;
		bool m_bFadedIn = false;
		bool m_bFade = false;
		short worldPosX;
		short worldPosY;
		short posX;
		short posY;
		short width;
		short height;
		short borderLineWidth;

		Vec3 m_vec3Color;
		Vec3 m_vec3LabelColor;
		Vec3 m_vec3MessageColor;
		Vec3 m_vec3BorderColor;
		float m_flAlpha;

		//Leadwerks::Font* oldfont;
		Leadwerks::Font* labelfont;
		Leadwerks::Font* messagefont;
		std::string m_stringlabel;
		std::string m_stringmsg;

	};

	class BaseContextBox : public BasePanel
	{
	public:
		BaseContextBox(short pWidth = 800, short pHeight = 600, short pWorldPosX = 0, short pWorldPosY = 0, bool pCenter = true, short pBorderWidth = 1);
		virtual ~BaseContextBox();
		virtual void Draw();
		virtual void FixButtonPos();
		RectButton* cancelbutton;
		RectButton* activatebutton;
		ImageButton* CloseButton;
		//private:

		bool m_bfixedpos = false;

		virtual void CreateButtons()
		{
			m_bfixedpos = false;
			cancelbutton = new RectButton(0, 0, 83, 22);
			cancelbutton->SetButtonLabel(CONTEXT_TEXT_CANCEL);

			activatebutton = new RectButton(0, 0, 83, 22);
			activatebutton->SetButtonLabel(CONTEXT_TEXT_OK);
		}

		void CreateCloseButton()
		{
			Leadwerks::Texture* closeicon = Leadwerks::Texture::Load(FILE_CLOSEICON);
			CloseButton = new ImageButton(closeicon, posX + GetWidth() - 20, posY + 4);
		}

	};
}

#endif //BASEPANEL_H