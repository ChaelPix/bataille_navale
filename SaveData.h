#pragma once
#include<iostream>
#include<vector>
#include <fstream>
#include <string>
#include <filesystem>
class SaveData{
private:

public:
	void saveDataToFile(const std::vector<std::string>& dataVector, bool flag);
	std::vector<std::string> loadDataFromFile();

};

