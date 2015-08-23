/********************************************************************
*		Copyright (c) 2014-2015, reepblue. All rights reserved.		*
*                                                                   *
*		This product contains software technology licensed from     *
*				 Leadwerks Software. All Rights Reserved.           *
********************************************************************/

#include "contextbuttons.h"

namespace LEX
{
	BaseButton::BaseButton()
	{
		width = 0;

		height = 0;

		worldPosX = 0;

		worldPosY = 0;

		posX = 0;

		posY = 0;

		m_bMouseRollover = false;
		m_bVisible = true;

		SetColor(255, 255, 255);
		SetAlpha(255);
		SetRolloverColor(192, 192, 192);
		SetPressedColor(96, 96, 96);

		s_Rollover = NULL;
		s_Press = NULL;

		Init();
	}

	BaseButton::~BaseButton()
	{
		SAFE_RELEASE(s_Rollover)
		SAFE_RELEASE(s_Press)
	}

	void BaseButton::Update()
	{
		if (m_bVisible)
		{
			HandleMouseEvent();
			Render();
		}
		else
		{
			Init();
		}
	}

	void BaseButton::Init()
	{
		if (!mouseEvent == kEventMouseNone || !prevMouseEvent == kEventMouseNone)
		{
			mouseEvent = kEventMouseNone;
			prevMouseEvent = kEventMouseNone;
		}
	}

	void BaseButton::HandleMouseEvent()
	{
		Leadwerks::Context *context = Context::GetCurrent();
		Leadwerks::Window *window = context->GetWindow();

		if (!m_bVisible)
			return;

		// If the window is not active, don't handle any events.
		if (window->Active() == false)
			return;

		if (m_bNoAction)
			return;

		if (m_blocked)
			return;

		if (context->GetColor().w < 1.0) return;

		Vec3 mousePos = window->GetMousePosition();

		if (mousePos.x > worldPosX && mousePos.x < worldPosX + width && mousePos.y > worldPosY && mousePos.y < worldPosY + height)
			mouseEvent = kEventMouseOver;
		else
			mouseEvent = kEventMouseNone;

		if (mouseEvent == kEventMouseOver)
		{
			if (prevMouseEvent == kEventMouseNone)
			{
				if (!m_bMouseRollover)
				{
					m_bMouseRollover = true;
					if (s_Rollover != NULL)
					{
						s_Rollover->Play();
					}
					mouseEvent = kEventMouseEnter;
				}
			}
			else if (!(window->MouseDown(MOUSE_LEFT)) && prevMouseEvent == kEventMouseLeftDown)
			{
				if (s_Press != NULL)
				{
					s_Press->Play();
				}
				mouseEvent = kEventMouseLeftUp;
			}
			else if (window->MouseHit(MOUSE_LEFT) && prevMouseEvent == kEventMouseOver)
			{
				mouseEvent = kEventMouseLeftHit;
			}
			else if (window->MouseDown(MOUSE_LEFT))
			{
				mouseEvent = kEventMouseLeftDown;
			}
			else if (!window->MouseDown(MOUSE_RIGHT) && prevMouseEvent == kEventMouseRightDown)
			{
				mouseEvent = kEventMouseRightUp;
			}
			else if (window->MouseHit(MOUSE_RIGHT) && prevMouseEvent == kEventMouseOver)
			{
				mouseEvent = kEventMouseRightHit;
			}
			else if (window->MouseDown(MOUSE_RIGHT))
			{
				mouseEvent = kEventMouseRightDown;
			}
		}
		else if (prevMouseEvent == kEventMouseOver || prevMouseEvent == kEventMouseLeftDown || prevMouseEvent == kEventMouseRightDown || prevMouseEvent == kEventMouseLeftHit || prevMouseEvent == kEventMouseRightHit)
		{
			mouseEvent = kEventMouseExit;
			m_bMouseRollover = false;
		}

		prevMouseEvent = mouseEvent;

	}

	TextButton::TextButton()
	{
		SetExistingFont();

		message = STRING_ERROR;
		width = font->GetTextWidth(message);

		height = font->GetHeight();

		worldPosX = 0;

		worldPosY = 0;

		posX = worldPosX;

		posY = worldPosY;

		Init();
	}

	TextButton::~TextButton()
	{
		font->Release();
	}

	void TextButton::Render()
	{
		Context *context = Context::GetCurrent();
		Vec4 oldr = context->GetColor();
		Leadwerks::Font* oldfont = context->GetFont();

		context->SetFont(font);
		if (!m_blocked)
		{
			if (mouseEvent == kEventMouseOver)
			{
				context->SetColor(GetRolloverColor().x, GetRolloverColor().y, GetRolloverColor().z);
				//context->SetColor(m_flRolloverColorR, m_flRolloverColorG, m_flRolloverColorB);
			}
			else if (mouseEvent == kEventMouseLeftDown)
			{
				context->SetColor(GetPressedColor().x, GetPressedColor().y, GetPressedColor().z);
				//context->SetColor(m_flPressedColorR, m_flPressedColorG, m_flPressedColorB);
			}
			else
			{
				context->SetColor(GetColor().x, GetColor().y, GetColor().z);
			}
		}
		else
		{
			context->SetColor(GetRolloverColor().x, GetRolloverColor().y, GetRolloverColor().z);
			// context->SetColor(m_flRolloverColorR, m_flRolloverColorG, m_flRolloverColorB, 0.25);
		}

		context->DrawText(message, posX, posY);

		context->SetFont(oldfont);
		context->SetColor(oldr);
	}

	void TextButton::HandleMouseEvent()
	{
		BaseButton::HandleMouseEvent();

		switch (mouseEvent)
		{
		case kEventMouseOver:
		{
			//System::Print("kEventMouseOver");
			break;
		}
		case kEventMouseExit:
		{
			//System::Print("kEventMouseExit");
			break;
		}
		case kEventMouseLeftDown:
		{
			//System::Print("kEventMouseLeftDown");
			break;
		}
		case kEventMouseLeftUp:
		{
			//System::Print("kEventMouseLeftUp");
			break;
		}
		case kEventMouseRightDown:
		{
			//System::Print("kEventMouseLeftDown");
			break;
		}
		case kEventMouseRightUp:
		{
			//System::Print("kEventMouseLeftUp");
			break;
		}
		}
	}

	ImageButton::ImageButton(Texture* pImage, short pWorldPosX, short pWorldPosY)
	{
		image = pImage;

		width = pImage->GetWidth();

		height = pImage->GetHeight();

		worldPosX = pWorldPosX;

		worldPosY = pWorldPosY;

		posX = worldPosX;

		posY = worldPosY;

		Init();
	}

	ImageButton::~ImageButton()
	{
		image->Release();
	}

	void ImageButton::Render()
	{
		Context *context = Context::GetCurrent();
		Vec4 oldr = context->GetColor();

		if (mouseEvent == kEventMouseOver)
		{
			context->SetColor(GetRolloverColor().x, GetRolloverColor().y, GetRolloverColor().z);
			//context->SetColor(m_flRolloverColorR, m_flRolloverColorG, m_flRolloverColorB);
		}
		else if (mouseEvent == kEventMouseLeftDown)
		{
			context->SetColor(GetPressedColor().x, GetPressedColor().y, GetPressedColor().z);
			//context->SetColor(m_flPressedColorR, m_flPressedColorG, m_flPressedColorB);
		}
		else
		{
			context->SetColor(GetColor().x, GetColor().y, GetColor().z);
			//context->SetColor(m_flColorR, m_flColorG, m_flColorB);
		}

		context->DrawImage(image, posX, posY, width, height);
		context->SetColor(oldr);
	}

	void ImageButton::HandleMouseEvent()
	{
		BaseButton::HandleMouseEvent();

		switch (mouseEvent)
		{
		case kEventMouseOver:
		{
			//System::Print("kEventMouseOver");
			break;
		}
		case kEventMouseExit:
		{
			//System::Print("kEventMouseExit");
			break;
		}
		case kEventMouseLeftDown:
		{
			//System::Print("kEventMouseLeftDown");
			break;
		}
		case kEventMouseLeftUp:
		{
			//System::Print("kEventMouseLeftUp");
			break;
		}
		case kEventMouseRightDown:
		{
			//System::Print("kEventMouseLeftDown");
			break;
		}
		case kEventMouseRightUp:
		{
			//System::Print("kEventMouseLeftUp");
			break;
		}
		}
	}

	RectButton::RectButton(short pWorldPosX, short pWorldPosY, short pWidth, short pHeight)
	{
		width = pWidth;
		height = pHeight;

		worldPosX = pWorldPosX;
		worldPosY = pWorldPosY;

		posX = worldPosX;
		posY = worldPosY;

		borderLineWidth = 1;
		Leadwerks::Context* context = Leadwerks::Context::GetCurrent();
		buttonfont = context->GetFont();

		SetColor(45, 45, 45);
		SetTextColor(241, 241, 241);
		SetAlpha(255);
		SetRolloverColor(64, 64, 70);
		SetPressedColor(37, 37, 37);
		SetBorderColor(64, 64, 64);
		SetRolloverBorderColor(0, 112, 204);
		Init();

		LoadScheme();
	}

	RectButton::~RectButton()
	{
	}

	void RectButton::LoadScheme()
	{
		if (FileSystem::GetFileType(FILE_RESOURCE_MENUSCHEME) == 0)
			return;

		pugi::xml_document xmlPanelRes;
		Leadwerks::Context* context = Leadwerks::Context::GetCurrent();

		//<buttons>
		xmlPanelRes.load_file(FILE_RESOURCE_MENUSCHEME);
		xml_node rootmenunode = xmlPanelRes.child(NODE_BASEPANEL_ROOT_BTN); // basepanel

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

		// --<pressed>
		xml_node pressedcolornode = colorsnode.child(NODE_BASEPANEL_BTN_PRESSED);
		const char* pressedcolor_R_vals = pressedcolornode.attribute("r").value();
		const char* pressedcolor_G_vals = pressedcolornode.attribute("g").value();
		const char* pressedcolor_B_vals = pressedcolornode.attribute("b").value();
		SetPressedColor(atof(pressedcolor_R_vals),
			atof(pressedcolor_G_vals),
			atof(pressedcolor_B_vals));

		// --<rollover>
		xml_node rollovercolornode = colorsnode.child(NODE_BASEPANEL_BTN_ROLLOVER);
		const char* rollovercolor_R_vals = rollovercolornode.attribute("r").value();
		const char* rollovercolor_G_vals = rollovercolornode.attribute("g").value();
		const char* rollovercolor_B_vals = rollovercolornode.attribute("b").value();
		SetRolloverColor(atof(rollovercolor_R_vals),
			atof(rollovercolor_G_vals),
			atof(rollovercolor_B_vals));

		// --<border>
		xml_node bordercolornode = colorsnode.child(NODE_BASEPANEL_BTN_BORDER);
		const char* bordercolor_R_vals = bordercolornode.attribute("r").value();
		const char* bordercolor_G_vals = bordercolornode.attribute("g").value();
		const char*bordercolor_B_vals = bordercolornode.attribute("b").value();
		SetBorderColor(atof(bordercolor_R_vals),
			atof(bordercolor_G_vals),
			atof(bordercolor_B_vals));

		// --<highlight>
		xml_node highlightcolornode = colorsnode.child(NODE_BASEPANEL_BTN_HIGHLIGHT);
		const char* highlightcolor_R_vals = highlightcolornode.attribute("r").value();
		const char* highlightcolor_G_vals = highlightcolornode.attribute("g").value();
		const char* highlightcolor_B_vals = highlightcolornode.attribute("b").value();
		SetRolloverBorderColor(atof(highlightcolor_R_vals),
			atof(highlightcolor_G_vals),
			atof(highlightcolor_B_vals));
	}

	void RectButton::DrawBorder()
	{
		Leadwerks::Context* context = Leadwerks::Context::GetCurrent();
		//context->SetColor(GetBorderColor().x, GetBorderColor().y, GetBorderColor().z, GetAlpha());

		if (mouseEvent == kEventMouseOver)
		{
			context->SetColor(GetRolloverBorderColor().x, GetRolloverBorderColor().y, GetRolloverBorderColor().z);
		}
		else if (mouseEvent == kEventMouseLeftDown)
		{
			context->SetColor(GetBorderColor().x, GetBorderColor().y, GetBorderColor().z);
		}
		else
		{
			context->SetColor(GetBorderColor().x, GetBorderColor().y, GetBorderColor().z);
		}

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

	void RectButton::Render()
	{
		Context *context = Context::GetCurrent();
		Vec4 oldr = context->GetColor();
		Leadwerks::Font* oldfont = context->GetFont();

		if (mouseEvent == kEventMouseOver)
		{
			context->SetColor(GetRolloverColor().x, GetRolloverColor().y, GetRolloverColor().z);
			//context->SetColor(m_flRolloverColorR, m_flRolloverColorG, m_flRolloverColorB);
		}
		else if (mouseEvent == kEventMouseLeftDown)
		{
			context->SetColor(GetPressedColor().x, GetPressedColor().y, GetPressedColor().z);
			//context->SetColor(m_flPressedColorR, m_flPressedColorG, m_flPressedColorB);
		}
		else
		{
			context->SetColor(GetColor().x, GetColor().y, GetColor().z);
			//context->SetColor(m_flColorR, m_flColorG, m_flColorB);
		}

		context->DrawRect(posX, posY, width, height);

		if (m_btnmsg != S_NULL)
		{
			context->SetColor(GetTextColor().x, GetTextColor().y, GetTextColor().z);
			float x = posX + GetWidth() / 2;
			float y = posY + GetHeight() / 2;

			context->SetFont(buttonfont);
			x = x - buttonfont->GetTextWidth(m_btnmsg) / 2;
			y = y - buttonfont->GetHeight() / 2;
			context->DrawText(m_btnmsg, x, y);
		}

		DrawBorder();
		context->SetFont(oldfont);
		context->SetColor(oldr);
	}

	void RectButton::HandleMouseEvent()
	{
		BaseButton::HandleMouseEvent();

		switch (mouseEvent)
		{
		case kEventMouseOver:
		{
			//System::Print("kEventMouseOver");
			break;
		}
		case kEventMouseExit:
		{
			//System::Print("kEventMouseExit");
			break;
		}
		case kEventMouseLeftDown:
		{
			//System::Print("kEventMouseLeftDown");
			break;
		}
		case kEventMouseLeftUp:
		{
			//System::Print("kEventMouseLeftUp");
			break;
		}
		case kEventMouseRightDown:
		{
			//System::Print("kEventMouseLeftDown");
			break;
		}
		case kEventMouseRightUp:
		{
			//System::Print("kEventMouseLeftUp");
			break;
		}
		}
	}

	BaseCheckBox::BaseCheckBox(short pWorldPosX, short pWorldPosY /*, short pWidth, short pHeight!*/)
	{
		Leadwerks::Context* context = Leadwerks::Context::GetCurrent();
		image = Leadwerks::Texture::Load(FILE_CLOSEICON);

		width = image->GetWidth();
		height = image->GetHeight();

		worldPosX = pWorldPosX;
		worldPosY = pWorldPosY;

		posX = worldPosX;
		posY = worldPosY;

		borderLineWidth = 1;

		SetColor(37, 37, 37);
		//SetColor(45, 45, 45);
		SetAlpha(255);
		SetBorderColor(64, 64, 64);

		Init();
		LoadScheme();
	}

	BaseCheckBox::~BaseCheckBox()
	{
		//image->Release();
	}

	void BaseCheckBox::LoadScheme()
	{
		if (FileSystem::GetFileType(FILE_RESOURCE_MENUSCHEME) == 0)
			return;

		pugi::xml_document xmlPanelRes;
		Leadwerks::Context* context = Leadwerks::Context::GetCurrent();

		//<buttons>
		xmlPanelRes.load_file(FILE_RESOURCE_MENUSCHEME);
		xml_node rootmenunode = xmlPanelRes.child("checkbox"); 


		// -<colors>
		xml_node colorsnode = rootmenunode.child(NODE_BASEPANEL_COLORS);

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
		const char*bordercolor_B_vals = bordercolornode.attribute("b").value();
		SetBorderColor(atof(bordercolor_R_vals),
			atof(bordercolor_G_vals),
			atof(bordercolor_B_vals));

		// --<check>
		xml_node txtcolornode = colorsnode.child("check");
		const char* txtcolor_R_vals = txtcolornode.attribute("r").value();
		const char* txtcolor_G_vals = txtcolornode.attribute("g").value();
		const char* txtcolor_B_vals = txtcolornode.attribute("b").value();
		SetCheckColor(atof(txtcolor_R_vals),
			atof(txtcolor_G_vals),
			atof(txtcolor_B_vals));
	}

	void BaseCheckBox::DrawBorder()
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

		context->SetColor(1, 1, 1, 1);

	}

	void BaseCheckBox::Render()
	{
		Context *context = Context::GetCurrent();
		Vec4 oldr = context->GetColor();

		context->SetColor(GetColor().x, GetColor().y, GetColor().z);
		context->DrawRect(posX, posY, width, height);

		DrawBorder();

		if (mouseEvent == kEventMouseLeftUp)
		{
			//context->SetColor(GetPressedColor().x, GetPressedColor().y, GetPressedColor().z, GetAlpha());
			if (!IsTicked())
			{
				//DEVMSG("TICKED!");
				SetTick(true);
			}
			else
			{
				//DEVMSG("UNTICKED!");
				SetTick(false);
			}
		}

		if (IsTicked())
		{
			context->SetColor(GetCheckColor().x, GetCheckColor().y, GetCheckColor().z);
			context->DrawImage(image, posX, posY, image->GetWidth(), image->GetHeight());
		}

		context->SetColor(oldr);
	}

	void BaseCheckBox::HandleMouseEvent()
	{
		BaseButton::HandleMouseEvent();

		switch (mouseEvent)
		{
		case kEventMouseOver:
		{
			//System::Print("kEventMouseOver");
			break;
		}
		case kEventMouseExit:
		{
			//System::Print("kEventMouseExit");
			break;
		}
		case kEventMouseLeftDown:
		{
			//System::Print("kEventMouseLeftDown");
			break;
		}
		case kEventMouseLeftUp:
		{
			//System::Print("kEventMouseLeftUp");
			break;
		}
		case kEventMouseRightDown:
		{
			//System::Print("kEventMouseLeftDown");
			break;
		}
		case kEventMouseRightUp:
		{
			//System::Print("kEventMouseLeftUp");
			break;
		}
		}
	}
}