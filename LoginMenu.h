#pragma once

#include "EntityTextBox.h"
#include "MouseManager.h"
#include "Settings.h"
#include "BsBDD.h"
#include "SaveData.h"

class LoginMenu
{
private:
	EntityTextBox* usernameTextBox;
	EntityTextBox* passwordTextBox;
	EntityRectangle* loginButton;
	sf::Texture buttonTextures[2];
	BsBDD* bdd;
	SaveData objData;
	LoginMenuSettings loginMenuSettings;
	SaveData svData;
	bool isLogged = false;
	bool isOnButton = false;
	bool isBusy;
	std::vector<std::string> DataVector;
	void Login();
	void LoginInvite();

public:

	LoginMenu(sf::Font& font, BsBDD& objBDD); //à ajuster selon la bdd

	void update(sf::Event& event, MouseManager &mouseManager);
	void draw(sf::RenderWindow& window);	
};

