#include "LoginMenu.h"


LoginMenu::LoginMenu(sf::Font &font, BsBDD& objBDD)
{
	usernameTextBox = new EntityTextBox(loginMenuSettings.usernameTextBoxPos, nullptr, font, "Username");
	passwordTextBox = new EntityTextBox(loginMenuSettings.passwordTextBosPos, nullptr, font, "Password");
	
	for (int i = 0; i < 2; i++)
		buttonTextures[i].loadFromFile(loginMenuSettings.buttonImagePaths[i]);
	
	loginButton = new EntityRectangle(loginMenuSettings.buttonSize, loginMenuSettings.buttonPos, buttonTextures[0]);

	bdd = &objBDD;
}

void LoginMenu::update(sf::Event& event, MouseManager& mouseManager)
{
	if (isBusy)
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
			if (usernameTextBox->getText().empty() || passwordTextBox->getText().empty()) {
				isBusy = true;
				std::cout << "empty ";
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
	usernameTextBox->draw(window);
	passwordTextBox->draw(window);
	loginButton->draw(window);
}

void LoginMenu::LoginInvite() {
	std::cout << "Welcome invite.... ";
	std::cout << bdd->getIdPlayers() << " ---------->" << bdd->getScore();
}

void LoginMenu::Login(){
	std::cout << "Login.... ";
	bdd->connectToDB("10.187.52.4", "batailleNavale", "batailleNavale");
	std::string id = usernameTextBox->getText();
	std::string mdp = passwordTextBox->getText();
	std::cout << id + mdp;
	std::cout << std::endl << bdd->login(id, mdp) << std::endl;
	std::cout << bdd->getIdPlayers() << " ---------->" << bdd->getScore();
	bdd->getAllData(DataVector);
}


