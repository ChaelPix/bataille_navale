#include "LoginMenu.h"


LoginMenu::LoginMenu(sf::Font &font, BsBDD& objBDD, bool& hasClicked, loginByFileInfo& app) : hasClicked(hasClicked)
{
	usernameTextBox = new EntityTextBox(loginMenuSettings.usernameTextBoxPos, nullptr, font, "Username", 9);
	passwordTextBox = new EntityTextBox(loginMenuSettings.passwordTextBosPos, nullptr, font, "Password", 15);
	
	for (int i = 0; i < 2; i++)
		buttonTextures[i].loadFromFile(loginMenuSettings.buttonImagePaths[i]);
	
	loginButton = new EntityRectangle(loginMenuSettings.buttonSize, loginMenuSettings.buttonPos, buttonTextures[0]);
	textInfo = new EntityText(font, loginMenuSettings.textPosition, loginMenuSettings.characterSize, "Login Menu");

	bgtexture.loadFromFile(loginMenuSettings.backgroundMenuPath);
	background = new EntityRectangle(loginMenuSettings.backgroundMenuSize, loginMenuSettings.backgroundMenuPos, bgtexture);

	bdd = &objBDD;
	isBusy = false;

	if (!hasClicked)
	{
		startText = new EntityText(font, loginMenuSettings.startTextPos, loginMenuSettings.startTextCharacterSize, "Left Click to begin your voyage");
	}
	else
		isLogged = true;

	checkForSaveFile(app);
}


bool LoginMenu::checkForSaveFile(loginByFileInfo& app)
{
	if (!app.hasFile)
		return false;

	Login(app.id, app.mdp);

	return true;
}

LoginMenu::MenuState LoginMenu::update(sf::Event& event, MouseManager& mouseManager)
{
	if (!hasClicked)
	{
		updateBlink();
		startText->SetColor(sf::Color(255, 255, 255, opacite));
		if (mouseManager.isMouseClicked())
		{
			hasClicked = true;
			return LoginMenu::MenuState::LoginBDD;
		}

		return LoginMenu::MenuState::WaitClick;
	}


	if (isLogged)
	{
		return LoginMenu::MenuState::OnMenu;
	}

	if (isBusy)
		return LoginMenu::MenuState::LoginBDD;

	bool isOnUsername = false;
	bool isOnPassword = false;

	sf::Vector2f mousePos = mouseManager.getClickPosition();

	if (usernameTextBox->isOnTextBox(mousePos))
	{
		isOnUsername = true;
		usernameTextBox->update(event);
	}
	else if (passwordTextBox->isOnTextBox(mousePos))
	{
		isOnPassword = true;
		passwordTextBox->update(event);
	}
	else if (loginButton->getShape().getGlobalBounds().contains(mousePos))
	{
		isOnButton = true;
		loginButton->setTexture(&buttonTextures[1]);

		if (mouseManager.isMouseClicked())
		{
			if (usernameTextBox->getText().empty() && passwordTextBox->getText().empty()) {
				isBusy = true;
				LoginInvite();
			}
			else
			{
				isBusy = true;
				Login(usernameTextBox->getText(), passwordTextBox->getText());
			}	
		}
	}
	else if (isOnButton)
	{
		isOnButton = false;
		loginButton->setTexture(&buttonTextures[0]);
	}

	usernameTextBox->setSelected(isOnUsername);
	passwordTextBox->setSelected(isOnPassword);

	return LoginMenu::MenuState::LoginBDD;
}

void LoginMenu::draw(sf::RenderWindow& window, LoginMenu::MenuState state)
{
	if (!hasClicked)
	{
		startText->draw(window);
	}
	else if(state == LoginMenu::MenuState::LoginBDD)
	{
		background->draw(window);
		usernameTextBox->draw(window);
		passwordTextBox->draw(window);
		loginButton->draw(window);
		textInfo->draw(window);
	}

}

void LoginMenu::LoginInvite() {
	
	std::cout << "Welcome invite.... ";
	if (bdd != nullptr)
		bdd->setIsConnected(false);

	bdd->setIdPlayers("Guest");

	isLogged = true;	
}

void LoginMenu::Login(std::string id, std::string mdp){

	std::cout << "Login.... ";
	textInfo->SetText("Login...");

	bool isConnected = bdd->connectToDB("10.187.52.4", "batailleNavale", "batailleNavale");

	if (!isConnected)
	{
		LoginInvite();
		return;
	}

	if (bdd->isUserDoesNotExist(id))
	{
		bdd->registerUser(id, mdp);	
	} 
	else if (bdd->isUserExistsButWrongPassword(id, mdp))
	{
		textInfo->SetText("Wrong Password.");
		isBusy = false;
		return;
	}
	else
	{
		if (!bdd->login(id, mdp))
		{
			textInfo->SetText("Error, please retry.");
			isBusy = false;
			return;
		}
	}
	bdd->setMdp(mdp);
	bdd->setIsConnected(true);
	bdd->getAllData(dataVector);
	svData.saveDataToFile(dataVector, "data.txt", false);
	isLogged = true;

}

void LoginMenu::updateBlink() {
	if (increasing) {
		opacite += blinkSpeed;
		if (opacite >= 255.0f) {
			opacite = 255.0f;
			increasing = false;
		}
	}
	else {
		opacite -= blinkSpeed;
		if (opacite <= 0.0f) {
			opacite = 0.0f;
			increasing = true;
		}
	}
}