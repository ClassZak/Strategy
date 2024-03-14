#pragma once

#include "GameFunctions.h"
#include "Global.h"

int MainMenu(sf::RenderWindow& window)
{
	sf::Vector2f buttonDimensions(200, 40);
	std::vector<Button>MainButtons = CreateMainButtons
	(
		Global::font, buttonDimensions,
		(std::vector<sf::String>&)Global::Localizator::GetLocalization().find(L"buttonLabels")->second
	);

	sf::Event event;
	sf::Vector2f mouse_pos;
	while (window.isOpen() and Global::playing and Global::room == Global::MENU)
	{
		mouse_pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));


		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				return 0;
			}


			if (Global::focus)
				for (int i = 0; i < Global::MAIN_BUTTONS; ++i)
					MainButtons[i].PollEvent(event, window, mouse_pos);


			if (event.type == sf::Event::LostFocus)
				Global::focus = false;
			else
				if (event.type == sf::Event::MouseButtonPressed)
				{
					if (Global::focus)
						break;

					Global::focus = true;
					for (int i = 0; i < Global::MAIN_BUTTONS; ++i)
						MainButtons[i].PollEvent(event, window, mouse_pos);
					continue;
				}
		}
		CheckMainButtons(MainButtons);




		window.clear(MENU_BACKGROUND_COLOR);
		for (unsigned short i = 0; i < Global::MAIN_BUTTONS; ++i)
			MainButtons[i].Draw(window);
		window.display();
		
	}
	return 0;
}



int GameField(sf::RenderWindow& window, std::list<GameObject*>* objects)
{
	//Start settings
	Global::room = Global::GAME_FIELD;
	sf::Texture backgroundTexture;
	backgroundTexture.loadFromFile(std::string("resources/Backgrounds/FieldBackground.png"));



	unsigned long LINE;
	LINE = UINT32((Global::WINDOW_HEIGHT * std::pow(1.f / Global::zoom, 10)) / backgroundTexture.getSize().y) + 3;
	if (LINE & 1)++LINE;
	const std::size_t VERT_BACKGROUND_COUNT = LINE;
	LINE = UINT32((Global::WINDOW_WIDTH * std::pow(1.f / Global::zoom, 10)) / backgroundTexture.getSize().x) + 3;
	if (LINE & 1)++LINE;
	const std::size_t HOR_BACKGROUND_COUNT = LINE;

	sf::Texture* pBackgroundTexture = nullptr;
	sf::Sprite background(backgroundTexture);
	if ((backgroundTexture.getSize().x < (VERT_BACKGROUND_COUNT - 3) * backgroundTexture.getSize().x)
		and (backgroundTexture.getSize().y < (HOR_BACKGROUND_COUNT - 3) * backgroundTexture.getSize().y))
		pBackgroundTexture =
		GetFullBackground(backgroundTexture, background, (UINT)HOR_BACKGROUND_COUNT, (UINT)VERT_BACKGROUND_COUNT);
	else
	{
		pBackgroundTexture = new sf::Texture;
		pBackgroundTexture = &backgroundTexture;
	}
	background.setOrigin((float)(background.getTextureRect().width / 2), (float)(background.getTextureRect().height / 2));

	//GUI objects and interface
	const sf::Vector2f buttonSizes(32, 32);

	

	std::list<GUIObject*> GUIObjects;

	OverlayPanel p;
	p.AddRectangle
	(
		sf::Vector2f(0, Global::WINDOW_HEIGHT - Global::DOWN_EDGE_LENGTH - 1),
		sf::Vector2f(Global::WINDOW_WIDTH, 1),
		BACKGROUND_LINE_COLOR
	);
	p.AddRectangle
	(
		sf::Vector2f(0, 0),
		sf::Vector2f(Global::LEFT_EDGE_LENGTH, Global::WINDOW_HEIGHT - Global::DOWN_EDGE_LENGTH),
		BACKGROUND_COLOR
	);
	p.AddRectangle
	(
		sf::Vector2f(0, Global::WINDOW_HEIGHT - Global::DOWN_EDGE_LENGTH),
		sf::Vector2f(Global::WINDOW_WIDTH, Global::DOWN_EDGE_LENGTH),
		BACKGROUND_COLOR
	);
	p.AddRectangle
	(
		sf::Vector2f(Global::LEFT_EDGE_LENGTH, 0),
		sf::Vector2f(1, Global::WINDOW_HEIGHT - Global::DOWN_EDGE_LENGTH),
		BACKGROUND_LINE_COLOR, p.rectangles - 1
	);
	GUIObjects.push_back(&p);


	ButtonWithImage menuButton = CreateButtonWithImage
	(
		(sf::Texture&)Global::TexturesContext::GetTextures().find(L"ButtonWithImage")->second.at(1),
		sf::Vector2f(Global::LEFT_EDGE_LENGTH / 4, 24),//Position
		sf::Vector2f(Global::LEFT_EDGE_LENGTH / 4, 24)//Image pos
	);
	GUIObjects.push_back(&menuButton);
	ButtonWithImage settingsButton = CreateButtonWithImage
	(
		(sf::Texture&)Global::TexturesContext::GetTextures().find(L"ButtonWithImage")->second.at(2),
		sf::Vector2f(Global::LEFT_EDGE_LENGTH / 4 * 3, 24),//Position
		sf::Vector2f(Global::LEFT_EDGE_LENGTH / 4 * 3, 24)//Image pos
	);
	GUIObjects.push_back(&settingsButton);



	Selector selector;
	//Set rendering


	if (!Global::gameStarted)
		Global::gameStarted = true;
	if (!Global::gameStarted)
	{
		Global::view.reset(sf::FloatRect(0, 0, Global::WINDOW_WIDTH, Global::WINDOW_HEIGHT));
		Global::view.setCenter((float)Global::WINDOW_WIDTH / 2, (float)Global::WINDOW_HEIGHT / 2);
	}
	window.setView(Global::view);

	//Set mouse vector
	sf::Vector2f globalMousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	while (window.isOpen() and Global::playing and Global::room == Global::GAME_FIELD)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				Global::room = Global::MENU;
			if (event.type == sf::Event::Closed)
			{
				window.close();
				break;
			}


			if (Global::focus)
			{
				if (event.type != sf::Event::MouseMoved)
					ObjectPollEvent(window, event, objects);


				Global::ReleasedMouseButtons::checkMouse();////////////

				window.setView(Global::standartView);
				sf::Vector2f GUIMousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
				ObjectPollEvent(window, event, &GUIObjects);

				window.setView(Global::view);


				selector.pollEvent(event, window, globalMousePos, GUIMousePos, *objects);
			}

			if (event.type == sf::Event::LostFocus)
				Global::focus = false;
			else
				if (event.type == sf::Event::MouseButtonPressed)
				{
					if (Global::focus)
						break;

					Global::focus = true;
					if (event.type != sf::Event::MouseMoved)
						ObjectPollEvent(window, event, objects);

					window.setView(Global::standartView);
					ObjectPollEvent(window, event, &GUIObjects);
					window.setView(Global::view);
					continue;
				}

			if (Global::focus)
				ChangeViewScale(event, Global::view, window, globalMousePos);
		}
		CheckInGameButtons(&GUIObjects);




		window.clear();
		globalMousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

		background.setPosition
		(
			(double)(long long)(Global::view.getCenter().x / backgroundTexture.getSize().x) *
			backgroundTexture.getSize().x,
			(double)(long long)(Global::view.getCenter().y / backgroundTexture.getSize().y) *
			backgroundTexture.getSize().y
		);

		window.draw(background);


		Global::ReleasedKeys::CheckKeys();
		if (Global::focus)
			MoveView(Global::view, window, event, GUIObjects);

		ObjectUpdate(window, *objects);
		Drawing(window, *objects);
		selector.draw(window);


		window.setView(Global::standartView);
		sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
		if (Global::focus)
		{
			DrawPoint(window, mousePos);
			ShowMousePosition(window, mousePos, globalMousePos, Global::font);
		}
		

		Drawing(window, GUIObjects);
		window.setView(Global::view);
		window.display();
	}
	window.setView(Global::standartView);
	delete pBackgroundTexture;
	return 0;
}



int SettingsMenu(sf::RenderWindow& window)
{
	std::list<Object*> GUIObjects;/////////////ïåðåäåëàòü íà ñïèñîê óêàçàòåëåé
	std::list<Button*> buttonsList;

	ButtonWithImage menuButton = CreateButtonWithImage
	(
		(sf::Texture&)Global::TexturesContext::GetTextures().find(L"ButtonWithImage")->second.at(1),
		sf::Vector2f(22, 24),
		sf::Vector2f(22, 24)
	);
	GUIObjects.push_back((&menuButton));
	buttonsList.push_back((&menuButton));
	ButtonWithImage settingsButton = CreateButtonWithImage
	(
		(sf::Texture&)Global::TexturesContext::GetTextures().find(L"ButtonWithImage")->second.at(0),
		sf::Vector2f(64, 24),
		sf::Vector2f(64, 24)
	);
	GUIObjects.push_back((&settingsButton));
	buttonsList.push_back((&settingsButton));


	TextBox TextBox
	(
		32 + 256, 128,
		[&]() -> int 
		{
			sf::Text t;
			t.setFont(Global::monoFont);
			t.setCharacterSize(14u);
			return (INT)(t.getCharacterSize() / 2.f + t.getLetterSpacing());
		}() * 10, 70
	);
	TextBox.setTextParametres(Global::monoFont, 14u);
	GUIObjects.push_back((&TextBox));


	while (window.isOpen() and Global::playing and Global::room == Global::SETTINGS)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			Global::ReleasedMouseButtons::checkMouse();

			if (event.type == sf::Event::Closed)
			{
				window.close();
				break;
			}


			if (Global::focus)
				ObjectPollEvent(window, event, &GUIObjects);


			if (event.type == sf::Event::LostFocus)
			{
				Global::focus = false;
				ObjectPollEvent(window, event, &GUIObjects);
			}
			else
				if (event.type == sf::Event::MouseButtonPressed)
				{
					if (Global::focus)
						break;

					Global::focus = true;
					ObjectPollEvent(window, event, &GUIObjects);
					continue;
				}
			if (event.type == sf::Event::KeyPressed)
				Global::ReleasedKeys::CheckKeys();
		}

		//CheckSettingsButtons(GUIObjects);
		CheckSettingsButtons(buttonsList);




		window.clear(BACKGROUND_COLOR);
		Drawing(window, GUIObjects);
		window.display();
	}
	buttonsList.clear();
	GUIObjects.clear();
	return 0;
}

