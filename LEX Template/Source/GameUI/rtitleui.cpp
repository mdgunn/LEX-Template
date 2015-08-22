/********************************************************************
*		Copyright (c) 2014-2015, reepblue. All rights reserved.		*
*                                                                   *
*		This product contains software technology licensed from     *
*				 Leadwerks Software. All Rights Reserved.           *
********************************************************************/

#include "rtitleui.h"

namespace LEX
{
	TitleUI::TitleUI(std::string pFont, int pSize, std::string pTitle)
	{
		Leadwerks::Context* context = Leadwerks::Context::GetCurrent();
		titlefont = Leadwerks::Font::Load(pFont, pSize);
		SetColor(255, 255, 255, 255);
		SetTitle(pTitle);
		SetPosition(0, 0);

	}

	TitleUI::~TitleUI()
	{
		SAFE_RELEASE(titlefont);
	}

	void TitleUI::Draw()
	{
		Leadwerks::Context* context = Leadwerks::Context::GetCurrent();
		context->SetColor(GetColor().x, GetColor().y, GetColor().z, GetColor().w);

		if (m_bUseImage && titleimage != NULL)
		{
			context->DrawImage(titleimage, GetX(), GetY(), titleimage->GetWidth(), titleimage->GetHeight());
		}
		else
		{
			context->SetFont(GetFont());
			context->DrawText(GetTitle(), GetX(), GetY());
		}



		context->SetColor(1, 1, 1, 1);
	}

	/*
	RTitleUI::RTitleUI()
	{
		SetTitle("Game");
		SetColor(255, 255, 255, 255);
	}

	RTitleUI::~RTitleUI()
	{
		SAFE_RELEASE(titlefont);
		SAFE_RELEASE(titleimage);
	}

	void RTitleUI::Draw()
	{
		Leadwerks::Context* context = Leadwerks::Context::GetCurrent();
		context->SetColor(GetColor().x, GetColor().y, GetColor().z, GetColor().w);
		if (!m_bUseImage)
		{
			DrawText(GetX(), GetY());
		}
		else
		{
			DrawImage(GetX(), GetY());
		}

		context->SetColor(1, 1, 1, 1);

	}

	void RTitleUI::DrawText(short x, short y)
	{
		if (titlefont == NULL)
			return;

		Leadwerks::Context* context = Leadwerks::Context::GetCurrent();

		//x = context->GetWidth() - context->GetWidth() + GetX();
		//y = context->GetHeight() - context->GetHeight() + GetY();

		context->SetFont(titlefont);
		context->DrawText(title, x, y);

	}

	void RTitleUI::DrawImage(short x, short y)
	{
		if (titleimage == NULL)
			return;

		Leadwerks::Context* context = Leadwerks::Context::GetCurrent();

		//x = context->GetWidth() - context->GetWidth() + GetX();
		//y = context->GetHeight() - context->GetHeight() + GetY();

		context->DrawImage(titleimage, x, y, titleimage->GetWidth(), titleimage->GetHeight());
	}
	*/
}
