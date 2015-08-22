/********************************************************************
*		Copyright (c) 2014-2015, reepblue. All rights reserved.		*
*                                                                   *
*		This product contains software technology licensed from     *
*				 Leadwerks Software. All Rights Reserved.           *
********************************************************************/

#if !defined( CONTEXTBUTTONS_H )
#define CONTEXTBUTTONS_H
#pragma once

#include "../main.h"
#include <iostream>   // std::cout
#include <string>     // std::string, std::stoi

enum
{
	kEventMouseNone,
	kEventMouseOver,
	kEventMouseEnter,
	kEventMouseExit,
	kEventMouseLeftDown,
	kEventMouseLeftUp,
	kEventMouseRightDown,
	kEventMouseRightUp,
	kEventTouchOneDown,
	kEventTouchOneUp,
	kEventMouseLeftHit,
	kEventMouseRightHit
};

namespace LEX
{
	class BaseButton
	{
	public:
		BaseButton();
		virtual ~BaseButton();
		void Init();

		virtual int GetMouseEvent()
		{
			return mouseEvent;
		}

		int mouseEvent;
		int prevMouseEvent;

		virtual void Update(void);
		virtual void Render(void) {};
		virtual void HandleMouseEvent(void);
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

		virtual bool IsVisible()
		{
			return m_bVisible;
		};

		virtual void Lock(bool l = false)
		{
			m_blocked = l;
		};

		// Unlike lock, SetNoAction does not gray out the color of the button.
		virtual void SetNoAction(bool l = false)
		{
			m_bNoAction = l;
		};

		virtual bool IsLocked()
		{
			return m_blocked;
		};

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

		Vec3 GetColor()
		{
			return m_vec3Color;
		}

		Vec3 GetRolloverColor()
		{
			return m_vec3RolloverColor;
		}

		Vec3 GetPressedColor()
		{
			return m_vec3PressedColor;
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

			/*
			m_flColorR = r / 255;
			m_flColorG = g / 255;
			m_flColorB = b / 255;
			*/
		};

		virtual void SetAlpha(float a)
		{
			m_flAlpha = a / 255;
		}

		virtual float GetAlpha()
		{
			return m_flAlpha;
		}

		// Takes rrr,ggg,bbb then divides by 255 to turn it into a vector.
		virtual void SetRolloverColor(float r, float g, float b)
		{
			r = r / 255;
			g = g / 255;
			b = b / 255;

			m_vec3RolloverColor.x = r;
			m_vec3RolloverColor.y = g;
			m_vec3RolloverColor.z = b;

			/*
			m_flRolloverColorR = r / 255;
			m_flRolloverColorG = g / 255;
			m_flRolloverColorB = b / 255;
			*/
		};

		// Takes rrr,ggg,bbb then divides by 255 to turn it into a vector.
		virtual void SetPressedColor(float r, float g, float b)
		{
			r = r / 255;
			g = g / 255;
			b = b / 255;

			m_vec3PressedColor.x = r;
			m_vec3PressedColor.y = g;
			m_vec3PressedColor.z = b;

			/*
			m_flPressedColorR = r / 255;
			m_flPressedColorG = g / 255;
			m_flPressedColorB = b / 255;
			*/
		};

		void SetRollOverSound(Sound* pSound)
		{
			s_Rollover = pSound;
		}

		void SetPressSound(Sound* pSound)
		{
			s_Press = pSound;
		}

		void SetRollOverSoundFile(std::string pSound)
		{
			if (FileSystem::GetFileType(pSound) == 1)
			{
				s_Rollover = Sound::Load(pSound);
			}
		}

		void SetPressSoundFile(std::string pSound)
		{
			if (FileSystem::GetFileType(pSound) == 1)
			{
				s_Press = Sound::Load(pSound);
			}
		}

	protected:
		Sound* s_Rollover;
		Sound* s_Press;

		short worldPosX;
		short worldPosY;
		short posX;
		short posY;
		short width;
		short height;
		float m_flAlpha;

		bool m_bVisible = true;
		bool m_blocked = false;
		bool m_bNoAction = false;

		//	bool m_bMousePressDown;
		bool m_bMouseRollover;

		Vec3 m_vec3Color;
		Vec3 m_vec3RolloverColor;
		Vec3 m_vec3PressedColor;

		/*
		float m_flColorR;
		float m_flColorG;
		float m_flColorB;

		float m_flRolloverColorR;
		float m_flRolloverColorG;
		float m_flRolloverColorB;

		float m_flPressedColorR;
		float m_flPressedColorG;
		float m_flPressedColorB;
		*/
	};

	class TextButton : public BaseButton
	{
	public:
		TextButton();
		virtual ~TextButton();

		virtual void HandleMouseEvent(void);
		virtual void Render(void);
		virtual bool UpdateButton()
		{
			Update();
			return true;
		}

		virtual void SetContextFont(Leadwerks::Font* pFont)
		{
			font = pFont;
			width = font->GetTextWidth(message);
			height = font->GetHeight();

		}

		virtual void SetFont(std::string pFont = FONT_ARIAL, int pSize = 10)
		{
			if (pFont == "")
			{
				MSG("TextButton: Failed to load TextButton Font.");
				return;
			}

			if (pSize == NULL)
			{
				MSG("TextButton: Failed to load TextButton Size.");
				return;
			}

			font = Leadwerks::Font::Load(pFont, pSize);
			width = font->GetTextWidth(message);
			height = font->GetHeight();
			//System::Print("TextButton: " + pFont + " " + std::to_string(pSize));
		}

		// Set font to a font that's already been loaded.
		virtual void SetExistingFont()
		{
			Context *context = Context::GetCurrent();
			font = context->GetFont();
			width = font->GetTextWidth(message);
			height = font->GetHeight();
		}

		virtual void SetText(std::string pMessage)
		{
			//if (pMessage == message)
				//return;

			message = pMessage;
			width = font->GetTextWidth(message);
			return;
		}

		Leadwerks::Font* GetFont()
		{
			return font;
		}

		std::string GetButtonText()
		{
			return message;
		}

	private:
		Leadwerks::Font* font;
		int size;
		std::string message;

	};

	class ImageButton : public BaseButton
	{
	public:
		ImageButton(Texture* pImage, short pWorldPosX, short pWorldPosY);
		virtual ~ImageButton();

		virtual void HandleMouseEvent(void);
		virtual void Render(void);

	private:
		Texture* image;

	};

	class RectButton : public BaseButton
	{
	public:
		//RectButton(short pWidth = 83, short pHeight = 22, short pWorldPosX = 0, short pWorldPosY = 0);
		RectButton(short pWorldPosX = 0, short pWorldPosY = 0, short pWidth = 83, short pHeight = 22);
		virtual ~RectButton();

		virtual void HandleMouseEvent(void);
		virtual void Render(void);
		virtual void DrawBorder();

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
		virtual void SetRolloverBorderColor(float r, float g, float b)
		{
			r = r / 255;
			g = g / 255;
			b = b / 255;

			m_vec3RolloverBorderColor.x = r;
			m_vec3RolloverBorderColor.y = g;
			m_vec3RolloverBorderColor.z = b;

		};

		Vec3 GetRolloverBorderColor()
		{
			return m_vec3RolloverBorderColor;
		}

		short GetBorderLineWidth(void)
		{
			return borderLineWidth;
		}

		void SetBorderLineWidth(short width)
		{
			borderLineWidth = width;
		}

		virtual void SetFont(std::string pFont = FONT_ARIAL, int pSize = 10)
		{
			if (pFont == S_NULL || pSize == NULL)
			{
				return;
			}

			buttonfont = Leadwerks::Font::Load(pFont, pSize);
		}

		void SetButtonLabel(std::string ptxt)
		{
			if (ptxt != S_NULL)
			{
				// Make sure the text can fit in the button.
				if (buttonfont->GetTextWidth(ptxt) > width)
				{
					width = buttonfont->GetTextWidth(ptxt) + 16;
				}

				if (buttonfont->GetHeight() > height)
				{
					height = buttonfont->GetHeight() + 16;
				}
			}

			m_btnmsg = ptxt;
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

		//private:
		short borderLineWidth;
		Vec3 m_vec3BorderColor;
		Vec3 m_vec3RolloverBorderColor;
		Vec3 m_vec3TextColor;
		Leadwerks::Font* buttonfont;
		std::string m_btnmsg;

	};

	class BaseCheckBox : public BaseButton
	{
	public:
		BaseCheckBox(short pWorldPosX = 0, short pWorldPosY = 0 /*, short pWidth = 0, short pHeight = 0*/);
		virtual ~BaseCheckBox();

		virtual void HandleMouseEvent(void);
		virtual void Render(void);
		virtual void DrawBorder();

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

		/*
		// Takes rrr,ggg,bbb then divides by 255 to turn it into a vector.
		virtual void SetTickColor(float r, float g, float b)
		{
			r = r / 255;
			g = g / 255;
			b = b / 255;

			m_vec3TickColor.x = r;
			m_vec3TickColor.y = g;
			m_vec3TickColor.z = b;
		};

		Vec3 GetTickColor()
		{
			return m_vec3BorderColor;
		}
		*/
		void SetTick(bool b)
		{
			m_bticked = b;
		}

		bool IsTicked()
		{
			return m_bticked;
		}

	private:
		bool m_bticked = false;
		short borderLineWidth;
		Vec3 m_vec3BorderColor;
		//Vec3 m_vec3TickColor;
		Leadwerks::Texture* image;

	};
}
#endif