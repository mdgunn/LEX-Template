/********************************************************************
*		Copyright (c) 2014-2015, reepblue. All rights reserved.		*
*                                                                   *
*		This product contains software technology licensed from     *
*				 Leadwerks Software. All Rights Reserved.           *
********************************************************************/

#include "chooser.h"

namespace LEX
{
	Chooser::Chooser(short pWorldPosX, short pWorldPosY, short pWidth, short pHeight)
	{
		width = pWidth;
		height = pHeight;

		worldPosX = pWorldPosX;
		worldPosY = pWorldPosY;

		posX = worldPosX;
		posY = worldPosY;

		borderLineWidth = 1;
		Leadwerks::Context* context = Leadwerks::Context::GetCurrent();
		chooserfont = context->GetFont();
		SetLabel("");
		SetIncreaseRate(1);

		Leadwerks::Texture* backicon = Leadwerks::Texture::Load(FILE_ARROWLEFT);
		backbutton = new ImageButton(backicon, 0, 0);

		Leadwerks::Texture* forwardicon = Leadwerks::Texture::Load(FILE_ARROWRIGHT);
		nextbutton = new ImageButton(forwardicon, 0, 0);

		SetMinOptionValue(0);
		SetMaxOptionValue(2);
		SetChooseOption(GetMinOptionValue());

		SetColor(37, 37, 37);
		SetBorderColor(64, 64, 64);
		SetTextColor(241, 241, 241);
		SetAlpha(255);

		LoadScheme();
	}

	Chooser::~Chooser()
	{
		SAFE_DELETE(backbutton);
		SAFE_DELETE(nextbutton);

		SAFE_RELEASE(chooserfont)
	}

	void Chooser::Update()
	{
		if (m_bVisible)
		{
			Render();
			Logic();
		}
	}

	void Chooser::LoadScheme()
	{
		if (FileSystem::GetFileType(FILE_RESOURCE_MENUSCHEME) == 0)
			return;

		pugi::xml_document xmlPanelRes;
		Leadwerks::Context* context = Leadwerks::Context::GetCurrent();

		//<chooser>
		xmlPanelRes.load_file(FILE_RESOURCE_MENUSCHEME);
		xml_node rootmenunode = xmlPanelRes.child(NODE_BASEPANEL_ROOT_CHOOSER);

		// -<text>
		xml_node textnode = rootmenunode.child(NODE_BASEPANEL_TEXT);
		std::string textlabelfontval = textnode.attribute("font").value();
		std::string textlabelfontsizeval = textnode.attribute("size").value();
		int textlabelsizeint = atoi(textlabelfontsizeval.c_str());
		SetFont(textlabelfontval, textlabelsizeint);

		// -<colors>
		xml_node colorsnode = rootmenunode.child(NODE_BASEPANEL_COLORS);

		// --<text>
		xml_node txtcolornode = colorsnode.child(NODE_BASEPANEL_TEXT);
		const char* txtcolor_R_vals = txtcolornode.attribute("r").value();
		const char* txtcolor_G_vals = txtcolornode.attribute("g").value();
		const char* txtcolor_B_vals = txtcolornode.attribute("b").value();
		SetTextColor(atof(txtcolor_R_vals),
			atof(txtcolor_G_vals),
			atof(txtcolor_B_vals));

		// --<color>
		xml_node basecolornode = colorsnode.child(NODE_BASEPANEL_BTN_COLOR);
		const char* basecolor_R_vals = basecolornode.attribute("r").value();
		const char* basecolor_G_vals = basecolornode.attribute("g").value();
		const char* basecolor_B_vals = basecolornode.attribute("b").value();
		SetColor(atof(basecolor_R_vals),
			atof(basecolor_G_vals),
			atof(basecolor_B_vals));

		// --<border>
		xml_node bordercolornode = colorsnode.child(NODE_BASEPANEL_BTN_BORDER);
		const char* bordercolor_R_vals = bordercolornode.attribute("r").value();
		const char* bordercolor_G_vals = bordercolornode.attribute("g").value();
		const char* bordercolor_B_vals = bordercolornode.attribute("b").value();
		SetBorderColor(atof(bordercolor_R_vals),
			atof(bordercolor_G_vals),
			atof(bordercolor_B_vals));

		// --<arrows>
		xml_node arrowscolornode = colorsnode.child("arrows");
		const char* arrowscolor_R_vals = arrowscolornode.attribute("r").value();
		const char* arrowscolor_G_vals = arrowscolornode.attribute("g").value();
		const char* arrowscolor_B_vals = arrowscolornode.attribute("b").value();
		SetArrowColor(atof(arrowscolor_R_vals),
			atof(arrowscolor_G_vals),
			atof(arrowscolor_B_vals));
	}

	void Chooser::Logic()
	{
		if (backbutton->GetMouseEvent() == kEventMouseLeftUp)
		{
			//DEVMSG("PRESS-");
			if (m_intoption != GetMinOptionValue())
			{
				m_intoption = m_intoption - m_intincreaserate;
			}
			else
			{
				m_intoption = GetMaxOptionValue();
			}

		}

		if (nextbutton->GetMouseEvent() == kEventMouseLeftUp)
		{
			//DEVMSG("PRESS+");
			if (m_intoption != GetMaxOptionValue())
			{
				m_intoption = m_intoption + m_intincreaserate;
			}
			else
			{
				m_intoption = GetMinOptionValue();
			}
		}
	}

	void Chooser::Render()
	{
		Context *context = Context::GetCurrent();

		Vec4 oldr = context->GetColor();
		Leadwerks::Font* oldfont = context->GetFont();

		context->SetColor(GetColor().x, GetColor().y, GetColor().z);
		context->DrawRect(posX, posY, width, height);
	
		if (m_btnmsg != S_NULL)
		{
			context->SetColor(GetTextColor().x, GetTextColor().y, GetTextColor().z);
			float x = posX + GetWidth() / 2;
			float y = posY + GetHeight() / 2;

			context->SetFont(chooserfont);
			x = x - chooserfont->GetTextWidth(m_btnmsg) / 2;
			y = y - chooserfont->GetHeight() / 2;
			context->DrawText(m_btnmsg, x, y);
		}

		context->SetColor(GetArrowColor().x, GetArrowColor().y, GetArrowColor().z);

		float by = posY + GetHeight() / 2;
		by = by - backbutton->GetHeight() / 2;
		backbutton->SetPosition(posX, by);
		backbutton->Update();

		float ny = posY + GetHeight() / 2;
		ny = ny - nextbutton->GetHeight() / 2;
		nextbutton->SetPosition(posX + GetWidth() - nextbutton->GetWidth(), ny);
		nextbutton->Update();

		DrawBorder();
		context->SetFont(oldfont);
		context->SetColor(oldr);
	}

	void Chooser::DrawBorder()
	{
		Leadwerks::Context* context = Leadwerks::Context::GetCurrent();
		context->SetColor(GetBorderColor().x, GetBorderColor().y, GetBorderColor().z);

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

	}

	Chooser3::Chooser3(short pWorldPosX, short pWorldPosY, short pWidth, short pHeight)
	{
		width = pWidth;
		height = pHeight;

		worldPosX = pWorldPosX;
		worldPosY = pWorldPosY;

		posX = worldPosX;
		posY = worldPosY;

		borderLineWidth = 1;
		SetLabel("");
		SetIncreaseRate(1);

		Leadwerks::Texture* backicon = Leadwerks::Texture::Load(FILE_ARROWLEFT);
		backbutton = new ImageButton(backicon, 0, 0);

		Leadwerks::Texture* forwardicon = Leadwerks::Texture::Load(FILE_ARROWRIGHT);
		nextbutton = new ImageButton(forwardicon, 0, 0);


		SetMinOptionValue(0);
		SetMaxOptionValue(2);
		SetChooseOption(GetMinOptionValue());

		SetColor(37, 37, 37);
		SetBorderColor(64, 64, 64);
		SetTextColor(241, 241, 241);
		SetAlpha(255);

		LoadScheme();
	}

	Chooser3::~Chooser3()
	{
	}

	void Chooser3::Logic()
	{
		Chooser::Logic();

		if (m_intoption == GetMaxOptionValue())
		{
			SetLabel("High");
		}
		else if (m_intoption == GetMinOptionValue())
		{
			SetLabel("Low");
		}
		else
		{
			SetLabel("Medium");
		}
	}

	ChooserMSAA::ChooserMSAA(short pWorldPosX, short pWorldPosY, short pWidth, short pHeight)
	{
		width = pWidth;
		height = pHeight;

		worldPosX = pWorldPosX;
		worldPosY = pWorldPosY;

		posX = worldPosX;
		posY = worldPosY;

		borderLineWidth = 1;
		Leadwerks::Context* context = Leadwerks::Context::GetCurrent();
		chooserfont = context->GetFont();
		SetIncreaseRate(1);

		Leadwerks::Texture* backicon = Leadwerks::Texture::Load(FILE_ARROWLEFT);
		backbutton = new ImageButton(backicon, 0, 0);

		Leadwerks::Texture* forwardicon = Leadwerks::Texture::Load(FILE_ARROWRIGHT);
		nextbutton = new ImageButton(forwardicon, 0, 0);

		SetMinOptionValue(1);
		SetMaxOptionValue(5);
		//SetChooseOption(GetMSAAOptionValue());

		SetColor(37, 37, 37);
		SetBorderColor(64, 64, 64);
		SetTextColor(241, 241, 241);
		SetAlpha(255);

		LoadScheme();
	}

	ChooserMSAA::~ChooserMSAA()
	{
	}

	void ChooserMSAA::Logic()
	{
		Chooser::Logic();

		if (m_intoption == GetMinOptionValue())
		{
			SetLabel("None");
			SetMSAAOptionValue(1);
		}
		else if (m_intoption == 2)
		{
			SetLabel("2x");
			SetMSAAOptionValue(2);
		}
		else if (m_intoption == 3)
		{
			SetLabel("4x");
			SetMSAAOptionValue(4);
		}
		else if (m_intoption == 4)
		{
			SetLabel("8x");
			SetMSAAOptionValue(8);
		}
		else if (m_intoption == 5)
		{
			SetLabel("16x");
			SetMSAAOptionValue(16);
		}
		else
		{
			m_intoption = GetMinOptionValue();
			System::Print(m_intoption);
		}
	}
}
