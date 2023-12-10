#include "LoginMenu.h"


LoginMenu::LoginMenu(sf::Font &font, BsBDD& objBDD, bool& hasClicked) : hasClicked(hasClicked)
{
	usernameTextBox = new EntityTextBox(loginMenuSettings.usernameTextBoxPos, nullptr, font, "Username");
	passwordTextBox = new EntityTextBox(loginMenuSettings.passwordTextBosPos, nullptr, font, "Password");
	
	for (int i = 0; i < 2; i++)
		buttonTextures[i].loadFromFile(loginMenuSettings.buttonImagePaths[i]);
	
	loginButton = new EntityRectangle(loginMenuSettings.buttonSize, loginMenuSettings.buttonPos, buttonTextures[0]);
	textInfo = new EntityText(font, loginMenuSettings.textPosition, loginMenuSettings.characterSize, "Wrong Password.");

	bdd = &objBDD;
	isBusy = false;

	startText = new EntityText(font, loginMenuSettings.startTextPos, loginMenuSettings.startTextCharacterSize, "Left Click to begin your voyage");
	checkForSaveFile();
}

bool LoginMenu::checkForSaveFile()
{
	dataVector.clear();
	dataVector = svData.loadDataFromFile("data.txt");

	if (dataVector.at(0) == "")
		return false;

	bdd->setIdPlayers(dataVector.at(0));
	bdd->setMdp(dataVector.at(1));

	return true;
}

void LoginMenu::update(sf::Event& event, MouseManager& mouseManager)
{
	if (!hasClicked)
	{
		updateBlink();
		startText->SetColor(sf::Color(255, 255, 255, opacite));
		if (mouseManager.isMouseClicked())
			hasClicked = true;
		return;
	}


	if (isBusy || isLogged)
		return;

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
				Login();
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
}

void LoginMenu::draw(sf::RenderWindow& window)
{
	if(!hasClicked)
		startText->draw(window);
	else
	{
		usernameTextBox->draw(window);
		passwordTextBox->draw(window);
		loginButton->draw(window);
		textInfo->draw(window);
	}

}

void LoginMenu::LoginInvite() {

	std::cout << "Welcome invite.... ";
	bdd->setIsConnected(false);

	isLogged = true;	
}

void LoginMenu::Login(){

	std::cout << "Login.... ";
	bool isConnected = bdd->connectToDB("10.187.52.4", "batailleNavale", "batailleNavale");

	if (!isConnected)
	{
		LoginInvite();
		return;
	}

	std::string id = usernameTextBox->getText();
	std::string mdp = passwordTextBox->getText();

	textInfo->SetText("Login...");

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

	bdd->getAllData(dataVector);
	svData.saveDataToFile(dataVector, "data.txt");
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