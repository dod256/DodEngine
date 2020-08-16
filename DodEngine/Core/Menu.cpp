#include "Menu.h"
#include "precomp.h"

Menu::~Menu()
{
	for (IDrawable* item : m_Items)
	{
		if (item)
		{
			delete item;
		}
	}
}

void Menu::Init()
{
	std::function<void()> func = std::bind(&Menu::StartGame, this);
	std::string s = "Start";
	Text* text = new Text(s, DVec4(0.0f, 0.0f, 1.0f, 1.0f), DEFAULT_WINDOWS_WIDTH / 2 - 50.0f, DEFAULT_WINDOWS_HEIGHT / 2 + 50.0f);
	text->AddOnClick(func);
	m_Items.push_back(text);

	func = std::bind(&Menu::CloseGame, this);
	s = "Exit";
	text = new Text(s, DVec4(0.0f, 0.0f, 1.0f, 1.0f), DEFAULT_WINDOWS_WIDTH / 2 - 50.0f, DEFAULT_WINDOWS_HEIGHT / 2 + 00.0f);
	text->AddOnClick(func);
	m_Items.push_back(text);
}

void Menu::Update()
{
	for (IDrawable* item : m_Items)
	{
		if (item)
		{
			item->Draw();
		}
	}
}
