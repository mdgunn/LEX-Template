/********************************************************************
*		Copyright (c) 2014-2015, reepblue. All rights reserved.		*
*                                                                   *
*		This product contains software technology licensed from     *
*				 Leadwerks Software. All Rights Reserved.           *
********************************************************************/

#include "numberdisplay.h"

namespace LEX
{
	NumberDisplay::NumberDisplay(short pWorldPosX, short pWorldPosY, short pWidth, short pHeight)
	{
		width = pWidth;
		height = pHeight;

		worldPosX = pWorldPosX;
		worldPosY = pWorldPosY;

		posX = worldPosX;
		posY = worldPosY;

		m_bVisible = true;
		borderLineWidth = 1;
		Leadwerks::Context* context = Leadwerks::Context::GetCurrent();
		displayfont = context->GetFont();
		Display("000");

		SetColor(37, 37, 37);
		SetBorderColor(64, 64, 64);
		SetTextColor(241, 241, 241);
		SetAlpha(255);

		LoadScheme();
	}

	NumberDisplay::~NumberDisplay()
	{
		displayfont->Release();
	}

	void NumberDisplay::LoadScheme()
	{
		if (FileSystem::GetFileType(FILE_RESOURCE_MENUSCHEME) == 0)
			return;

		pugi::xml_document xmlPanelRes;
		Leadwerks::Context* context = Leadwerks::Context::GetCurrent();

		//<slider>
		xmlPanelRes.load_file(FILE_RESOURCE_MENUSCHEME);
		xml_node rootmenunode = xmlPanelRes.child("numberdisplay");

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

	}

	void NumberDisplay::Update()
	{
		if (m_bVisible)
		{
			Render();
		}
	}

	void NumberDisplay::Render()
	{
		Context *context = Context::GetCurrent();
		Vec4 oldr = context->GetColor();
		context->SetColor(GetColor().x, GetColor().y, GetColor().z);
		context->DrawRect(posX, posY, width, height);

		if (m_btnmsg != S_NULL)
		{
			context->SetColor(GetTextColor().x, GetTextColor().y, GetTextColor().z);
			float x = posX + GetWidth() / 2;
			float y = posY + GetHeight() / 2;

			context->SetFont(displayfont);
			x = x - displayfont->GetTextWidth(m_btnmsg) / 2;
			y = y - displayfont->GetHeight() / 2;
			context->DrawText(m_btnmsg, x, y);
		}

		DrawBorder();

		context->SetColor(oldr);
	}

	void NumberDisplay::DrawBorder()
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
}
