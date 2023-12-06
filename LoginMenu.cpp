#include "LoginMenu.h"


LoginMenu::LoginMenu(sf::Font &font)
{
	usernameTextBox = new EntityTextBox(loginMenuSettings.usernameTextBoxPos, nullptr, font, "Username");
	passwordTextBox = new EntityTextBox(loginMenuSettings.passwordTextBosPos, nullptr, font, "Password");

	for (int i = 0; i < 2; i++)
		buttonTextures[i].loadFromFile(loginMenuSettings.buttonImagePaths[i]);
	
	loginButton = new EntityRectangle(loginMenuSettings.buttonSize, loginMenuSettings.buttonPos, buttonTextures[0]);
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
			isBusy = true;
			Login();
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



void LoginMenu::Login()
{
	std::cout << "Login.... ";


}


