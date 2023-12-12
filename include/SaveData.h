#pragma once
#include<iostream>
#include<vector>
#include <fstream>
#include <string>
class SaveData{
private:

public:
	void saveDataToFile(const std::vector<std::string>& dataVector, const std::string& filename, bool flag);
	std::vector<std::string> loadDataFromFile(const std::string& filename);

};

