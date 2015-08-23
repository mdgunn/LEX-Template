/********************************************************************
*		Copyright (c) 2014-2015, reepblue. All rights reserved.		*
*                                                                   *
*		This product contains software technology licensed from     *
*				 Leadwerks Software. All Rights Reserved.           *
********************************************************************/
#include "basepanel.h"

#define FADE_SPEED 4.5

namespace LEX
{
	BasePanel::BasePanel(short pWidth, short pHeight, short pWorldPosX, short pWorldPosY, bool pCenter, short pBorderWidth)
	{
		width = pWidth;
		height = pHeight;

		if (pCenter)
		{
			worldPosX = pWorldPosX - GetWidth() / 2;
			worldPosY = pWorldPosY - GetHeight() / 2;
		}
		else
		{
			worldPosX = pWorldPosX;
			worldPosY = pWorldPosY;
		}

		posX = worldPosX;
		posY = worldPosY;

		borderLineWidth = pBorderWidth;

		m_stringlabel = "";
		m_stringmsg = "";

		Leadwerks::Context* context = Leadwerks::Context::GetCurrent();
		labelfont = context->GetFont();
		messagefont = context->GetFont();

		SetColor(45, 45, 45);
		SetAlpha(0);
		SetBorderColor(64, 64, 64);
		borderLineWidth = 4;
		SetLabelColor(153, 153, 153);
		SetMessageColor(241, 241, 241);

		// 8-19-15: Come back to me!
		LoadScheme();
	}

	BasePanel::~BasePanel()
	{
		labelfont->Release();
		messagefont->Release();
	}

	void BasePanel::LoadScheme()
	{
		if (FileSystem::GetFileType(FILE_RESOURCE_MENUSCHEME) == 0)
			return;
		pugi::xml_document xmlPanelRes;
		Leadwerks::Context* context = Leadwerks::Context::GetCurrent();

		//<basepanel>
		xmlPanelRes.load_file(FILE_RESOURCE_MENUSCHEME);
		xml_node rootmenunode = xmlPanelRes.child(NODE_BASEPANEL_ROOT); // basepanel
		const char* color_R_vals = rootmenunode.attribute("r").value();
		const char* color_G_vals = rootmenunode.attribute("g").value();
		const char* color_B_vals = rootmenunode.attribute("b").value();

		SetColor(atof(color_R_vals),
			atof(color_G_vals),
			atof(color_B_vals));

		// -<border>
		xml_node bordernode = rootmenunode.child(NODE_BASEPANEL_BORDER);
		const char* border_color_R_vals = bordernode.attribute("r").value();
		const char* border_color_G_vals = bordernode.attribute("g").value();
		const char* border_color_B_vals = bordernode.attribute("b").value();

		SetBorderColor(atof(border_color_R_vals),
			atof(border_color_G_vals),
			atof(border_color_B_vals));
		
		// -<text>
		xml_node textnode = rootmenunode.child(NODE_BASEPANEL_TEXT);

		// --<label>
		xml_node text_labelnnode = textnode.child(NODE_BASEPANEL_LABEL);
		std::string textlabelfontval = text_labelnnode.attribute("font").value();
		std::string textlabelsizeval = text_labelnnode.attribute("size").value();
		int textlabelsizeint = atoi(textlabelsizeval.c_str());
		SetLabelFont(textlabelfontval, textlabelsizeint);

		// --<message>
		xml_node text_msgnnode = textnode.child(NODE_BASEPANEL_MESSAGE);
		std::string textmessagefontval = text_msgnnode.attribute("font").value();
		std::string textmessagesizeval = text_msgnnode.attribute("size").value();
		int textmessagesizeint = atoi(textmessagesizeval.c_str());

		if (textlabelfontval == textmessagefontval)
		{
			if (textlabelsizeval == textmessagesizeval)
			{
				messagefont = labelfont;
			}
			else
			{
				SetMessageFont(textmessagefontval, textmessagesizeint);
			}
		}
		else
		{
			SetMessageFont(textmessagefontval, textmessagesizeint);
		}
		
	
		// --<color>
		xml_node text_colornnode = textnode.child(NODE_BASEPANEL_COLORS);

		// ----<label>
		xml_node color_labelnnode = text_colornnode.child(NODE_BASEPANEL_LABEL);
		const char* text_color_label_R_vals = color_labelnnode.attribute("r").value();
		const char* text_color_label_G_vals = color_labelnnode.attribute("g").value();
		const char* text_color_label_B_vals = color_labelnnode.attribute("b").value();

		SetLabelColor(atof(text_color_label_R_vals),
			atof(text_color_label_G_vals),
			atof(text_color_label_B_vals));

		// ----<message>
		xml_node color_messagennode = text_colornnode.child(NODE_BASEPANEL_MESSAGE);
		const char* text_color_message_R_vals = color_messagennode.attribute("r").value();
		const char* text_color_message_G_vals = color_messagennode.attribute("g").value();
		const char* text_color_message_B_vals = color_messagennode.attribute("b").value();

		SetMessageColor(atof(text_color_message_R_vals),
			atof(text_color_message_G_vals),
			atof(text_color_message_B_vals));
	}

	void BasePanel::Draw()
	{
		if (m_bFade)
		{
			if (!m_bDrawing)
			{
				if (m_bFadedIn)
				{
					if (GetAlpha() != 0.0)
					{
						float currentalpha = GetAlpha() - FADE_SPEED * Time::GetSpeed() / 100;
						SetAlpha(currentalpha * 255);

						if (GetAlpha() < 0.0)
						{
							SetAlpha(0);
							m_bFadedIn = false;
							//System::Print(GetAlpha());
							return;
						}
					}
					else
					{
						SetAlpha(255);
					}
				}
			}
			else
			{
				if (!m_bFadedIn)
				{
					if (GetAlpha() <= 1.0)
					{
						float currentalpha = GetAlpha() + FADE_SPEED * Time::GetSpeed() / 100;
						SetAlpha(currentalpha * 255);

						if (GetAlpha() > 1.0)
						{
							SetAlpha(255);
							m_bFadedIn = true;
						}
						//System::Print(GetAlpha());
					}
					else
					{
						SetAlpha(0);
					}
				}
			}
		}
		else
		{
			if (!m_bDrawing)
			{
				m_bFadedIn = false;
				SetAlpha(0);
				return;
			}
			/*
			if (!m_bDrawing)
				return;
				*/
		}
	
		Leadwerks::Context* context = Leadwerks::Context::GetCurrent();
		Vec4 oldr = context->GetColor();
		context->SetColor(GetColor().x, GetColor().y, GetColor().z, GetAlpha());
		context->DrawRect(posX, posY, width, height);

		if (m_stringlabel != S_NULL)
		{
			context->SetFont(labelfont);
			context->SetColor(GetLabelColor().x, GetLabelColor().y, GetLabelColor().z);
			context->DrawText(m_stringlabel, posX + 8, posY + 8);
		}

		if (m_stringmsg != S_NULL)
		{
			context->SetColor(GetMessageColor().x, GetMessageColor().y, GetMessageColor().z);
			float x = posX + GetWidth() / 2;
			float y = posY + GetHeight() / 2;

			context->SetFont(messagefont);
			x = x - labelfont->GetTextWidth(m_stringmsg) / 2;
			y = y - labelfont->GetHeight() / 2;
			context->DrawText(m_stringmsg, x, y);
		}

		DrawBorder();

		context->SetColor(oldr);
	}

	void BasePanel::DrawBorder()
	{
		Leadwerks::Context* context = Leadwerks::Context::GetCurrent();
		context->SetColor(GetBorderColor().x, GetBorderColor().y, GetBorderColor().z, GetAlpha());

		if (borderLineWidth <= 0)
			return;

		if (borderLineWidth > 1)
		{
			context->DrawRect(worldPosX, worldPosY, width, height - (height - borderLineWidth));
			context->DrawRect(worldPosX, (worldPosY + height - borderLineWidth), width, borderLineWidth);
			context->DrawRect(worldPosX, worldPosY + borderLineWidth, borderLineWidth, (height - borderLineWidth * 2));
			context->DrawRect(worldPosX + (width - borderLineWidth), worldPosY + borderLineWidth, borderLineWidth, (height - borderLineWidth * 2));
		}
		else if (borderLineWidth == 1)
		{
			//Draw A line
			context->DrawLine(worldPosX, worldPosY, worldPosX + width, worldPosY);
			context->DrawLine(worldPosX, (worldPosY + height), worldPosX + width, (worldPosY + height));
			context->DrawLine(worldPosX, worldPosY, worldPosX, worldPosY + height);
			context->DrawLine(worldPosX + width, worldPosY, worldPosX + width, worldPosY + height);
		}

		context->SetColor(1, 1, 1);
	}

	void BasePanel::Open(bool pFadeIn)
	{
		if (!m_bDrawing)
		{
			if (!m_bFade)
			{
				SetAlpha(0);
			}

			m_bFade = pFadeIn;

			m_bDrawing = true;
		}
	}

	void BasePanel::Close(bool pFadeOut)
	{
		if (m_bDrawing)
		{
			if (!m_bFade)
			{
				SetAlpha(255);
			}

			m_bFade = pFadeOut;

			m_bDrawing = false;
		}
	}

	void BasePanel::SetLabel(std::string pTitle)
	{
		m_stringlabel = pTitle;
	}

	void BasePanel::SetMessage(std::string pMsg)
	{
		m_stringmsg = pMsg;

		// If the message can't fit in our box, make the box bigger.
		if (messagefont->GetTextWidth(m_stringmsg) > width)
		{
			width = messagefont->GetTextWidth(m_stringmsg) + 16;
		}
	}

	BaseContextBox::BaseContextBox(short pWidth, short pHeight, short pWorldPosX, short pWorldPosY, bool pCenter, short pBorderWidth)
	{
		width = pWidth;
		height = pHeight;

		if (pCenter)
		{
			worldPosX = pWorldPosX - GetWidth() / 2;
			worldPosY = pWorldPosY - GetHeight() / 2;
		}
		else
		{
			worldPosX = pWorldPosX;
			worldPosY = pWorldPosY;
		}

		posX = worldPosX;
		posY = worldPosY;

		borderLineWidth = pBorderWidth;

		CreateCloseButton();
		CreateButtons();
	}

	BaseContextBox::~BaseContextBox()
	{
		delete cancelbutton;
		delete activatebutton;
		delete CloseButton;
	}

	void BaseContextBox::FixButtonPos()
	{
		if (m_bfixedpos) return;

		float x = worldPosX + GetWidth();
		float y = worldPosY + GetHeight();

		x = x - cancelbutton->GetWidth() - 8;
		y = y - cancelbutton->GetHeight() - 8;
		cancelbutton->SetPosition(x, y);

		activatebutton->SetPosition(x - activatebutton->GetWidth() - 4, y);
		m_bfixedpos = true;
	}

	void BaseContextBox::Draw()
	{
		BasePanel::Draw();

		if (!m_bDrawing)
			return;

		FixButtonPos();

		Leadwerks::Context* context = Leadwerks::Context::GetCurrent();

		CloseButton->Update();
		if (CloseButton->GetMouseEvent() == kEventMouseLeftUp)
		{
			Close();
		}

		cancelbutton->Update();
		if (cancelbutton->GetMouseEvent() == kEventMouseLeftUp)
		{
			Close();
		}

		activatebutton->Update();
		
	}
}