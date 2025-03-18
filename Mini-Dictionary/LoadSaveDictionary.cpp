#include "LoadSaveDictionary.h"
#include "ToLowerCase.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <Windows.h>

using DictionaryMap = std::map<std::string, std::string>;

std::optional<DictionaryMap> LoadDictionary(const std::string& filename)
{
    std::map<std::string, std::string> dictionary;
    std::ifstream file(filename);
    bool success = false;
    if (file)
    {
        success = true;
        std::string line;
        while (std::getline(file, line))
        {
            std::stringstream ss(line);
            std::string key, value;
            std::getline(ss, key, '>');
            std::getline(ss, value);
            key = ToLowerCase(key);
            dictionary[key] = value;
        }
        file.close();
        return dictionary;
    } else
    {
        std::cout << "Словарь " << filename << " не найден\n";
        return std::nullopt;
    }
    
}

int SaveDictionary(const std::string& filename, const DictionaryMap& dictionary)
{
    
    size_t pos = filename.find(".txt");

    if (pos != std::string::npos)
    {
        std::ofstream file(filename);
        for (const auto& pair : dictionary)
        {
            file << pair.first << ">" << pair.second << "\n";
        }
        file.close();
        return 0;
    }
    else
    {
        std::cout << "Неправильное название файла: " << filename << "\n";
        return 1;
    }
}