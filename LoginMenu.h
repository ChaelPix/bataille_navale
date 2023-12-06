#pragma once

#include "EntityTextBox.h"
#include "MouseManager.h"
#include "Settings.h"

class LoginMenu
{
private:

	EntityTextBox* usernameTextBox;
	EntityTextBox* passwordTextBox;
	EntityRectangle* loginButton;

	sf::Texture buttonTextures[2];

	LoginMenuSettings loginMenuSettings;
	bool isOnButton = false;
	bool isBusy = false;

	void Login();
public:

	LoginMenu(sf::Font& font); //à ajuster selon la bdd

	void update(sf::Event& event, MouseManager &mouseManager);
	void draw(sf::RenderWindow& window);
	
};

