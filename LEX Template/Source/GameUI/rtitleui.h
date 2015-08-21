/********************************************************************
*		Copyright (c) 2014-2015, reepblue. All rights reserved.		*
*                                                                   *
*		This product contains software technology licensed from     *
*				 Leadwerks Software. All Rights Reserved.           *
********************************************************************/

#if !defined( RTITLEUI_H )
#define RTITLEUI_H
#pragma once

#include "../main.h"
namespace LEX
{
	class TitleUI
	{
	public:
		TitleUI(std::string pFont, int pSize, std::string pTitle);
		virtual ~TitleUI();

		void Draw();

		void SetFont(Leadwerks::Font* pFont)
		{
			titlefont = pFont;
		}

		void SetFontFile(std::string titlefontval, int titlesizeval)
		{
			titlefont = Leadwerks::Font::Load(titlefontval, titlesizeval);
		}

		Leadwerks::Font* GetFont()
		{
			return titlefont;
		}

		void SetTitle(string pTitle)
		{
			title = pTitle;
		}

		string GetTitle()
		{
			return title;
		}

		void SetPosition(short pX, short pY)
		{
			posX = pX;
			posY = pY;
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
			return titlefont->GetTextWidth(title);
		}

		short GetHeight()
		{
			return titlefont->GetHeight();
		}

		// Takes rrr,ggg,bbb then divides by 255 to turn it into a vector.
		virtual void SetColor(float r, float g, float b, float a = 255)
		{
			r = r / 255;
			g = g / 255;
			b = b / 255;
			a = a / 255;

			m_vec4Color.x = r;
			m_vec4Color.y = g;
			m_vec4Color.z = b;
			m_vec4Color.w = a;
		};

		Vec4 GetColor()
		{
			return m_vec4Color;
		}

		void UseImage(bool b)
		{
			m_bUseImage = b;
		}

		void SetImage(string titleimageval)
		{
			if (FileSystem::GetFileType(titleimageval) == 1)
			{
				titleimage = Leadwerks::Texture::Load(titleimageval);
				//SAFE_DELETE(titlefont);
			}
		}

	private:
		Leadwerks::Font* titlefont;
		std::string title = STRING_ERROR;

		short posX;
		short posY;

		Vec4 m_vec4Color;

		bool m_bUseImage;
		Leadwerks::Texture* titleimage = NULL;
	};

	/*
	class RTitleUI
	{
	public:
		RTitleUI();
		virtual ~RTitleUI();



		void Draw();
		void DrawText(short x, short y);
		void DrawImage(short x, short y);

		void SetPosition(short pX, short pY)
		{
			posX = pX;
			posY = pY;
		}

		short GetX()
		{
			return posX;
		}

		short GetY()
		{
			return posY;
		}

		int GetWidth()
		{
			if (m_bUseImage)
			{
				return titleimage->GetWidth();
			}

			return titlefont->GetTextWidth(title);
		}

		int GetHeight()
		{
			if (m_bUseImage)
			{
				return titleimage->GetHeight();
			}

			return titlefont->GetHeight();

		}

		virtual void SetContextFont(Leadwerks::Font* pFont)
		{
			titlefont = pFont;
		}

		void SetFont(std::string titlefontval, int titlesizeval)
		{
			titlefont = Leadwerks::Font::Load(titlefontval, titlesizeval);
			m_bUseImage = false;
		}

		void SetTitle(string pTitle)
		{
			title = pTitle;
		}

		string GetTitle()
		{
			return title;
		}

		Leadwerks::Font* GetFont()
		{
			return titlefont;
		}

		void SetImage(string titleimageval)
		{
			//SAFE_DELETE(titlefont);
			titleimage = Leadwerks::Texture::Load(titleimageval);
			m_bUseImage = true;
		}

		Leadwerks::Texture* GetImage()
		{
			SAFE_RETURN(titleimage);
		}

		// Takes rrr,ggg,bbb then divides by 255 to turn it into a vector.
		virtual void SetColor(float r, float g, float b, float a=255)
		{
			r = r / 255;
			g = g / 255;
			b = b / 255;
			a = a / 255;

			m_vec4Color.x = r;
			m_vec4Color.y = g;
			m_vec4Color.z = b;
			m_vec4Color.w = a;
		};

		Vec4 GetColor()
		{
			return m_vec4Color;
		}

	private:
		Leadwerks::Font* titlefont;
		std::string title = STRING_ERROR;

		Leadwerks::Texture* titleimage = NULL;
		bool m_bUseImage = false;

		Vec4 m_vec4Color;

		short posX;
		short posY;

	};
	*/
}
#endif //RTITLEUI