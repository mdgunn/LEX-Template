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
	}

	NumberDisplay::~NumberDisplay()
	{
		displayfont->Release();
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
		context->SetColor(GetColor().x, GetColor().y, GetColor().z, GetAlpha());
		context->DrawRect(posX, posY, width, height);

		if (m_btnmsg != S_NULL)
		{
			context->SetColor(GetTextColor().x, GetTextColor().y, GetTextColor().z, GetAlpha());
			float x = posX + GetWidth() / 2;
			float y = posY + GetHeight() / 2;

			context->SetFont(displayfont);
			x = x - displayfont->GetTextWidth(m_btnmsg) / 2;
			y = y - displayfont->GetHeight() / 2;
			context->DrawText(m_btnmsg, x, y);
		}

		context->SetColor(1, 1, 1);
		DrawBorder();
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

		context->SetColor(1, 1, 1, 1);

	}
}