#pragma once

#include "EntityTextBox.h"
#include "MouseManager.h"
#include "Settings.h"
#include "BsBDD.h"
#include "SaveData.h"

class LoginMenu
{
public :
	enum class MenuState {WaitClick, LoginBDD, OnMenu};

	struct loginByFileInfo {
		std::string id;
		std::string mdp;
		bool hasFile;
	};

private:
	EntityTextBox* usernameTextBox;
	EntityTextBox* passwordTextBox;
	EntityRectangle* loginButton;
	EntityRectangle* background;
	EntityText* textInfo;
	EntityText* startText;


	sf::Texture buttonTextures[2];
	sf::Texture bgtexture;
	BsBDD* bdd;
	SaveData objData;
	LoginMenuSettings loginMenuSettings;
	SaveData svData;
	bool isLogged = false;
	bool isOnButton = false;
	bool isBusy;
	bool& hasClicked;

	std::vector<std::string> dataVector;
	void Login(std::string id, std::string mdp);
	void LoginInvite();

	float opacite = 255.0f;
	bool increasing = true;
	const float blinkSpeed = .5;
	void updateBlink();
public:

	LoginMenu(sf::Font& font, BsBDD& objBDD, bool& hasClicked, loginByFileInfo& log);

	bool checkForSaveFile(loginByFileInfo& log);
	MenuState update(sf::Event& event, MouseManager &mouseManager);
	void draw(sf::RenderWindow& window, LoginMenu::MenuState state);
};

