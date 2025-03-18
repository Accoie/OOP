#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <Windows.h>
#include <sstream>
#include <cstring>
#include <algorithm>
#include "LoadSaveDictionary.h"
#include "ToLowerCase.h"
#include <optional>

using DictionaryMap = std::map<std::string, std::string>;

const std::string PROGRAM_LEAVE = "...";
// ознакомиться с using
void HandleProgramLeave(bool changesMade, bool loadSuccess, std::string dictionaryFile, const DictionaryMap &dictionary)
{
    if (changesMade)
    {
        std::cout << "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом.\n";
        char choice;
        std::cin >> choice;
        if (choice == 'Y' || choice == 'y')
        {
            if (!loadSuccess)
            {
                std::cout << "Введите название словаря в .txt: ";
                std::cin >> dictionaryFile;
                std::cout << "\n";
            }
            SaveDictionary(dictionaryFile, dictionary) == 0 ? std::cout << "Изменения сохранены. До свидания.\n"
                                                            : std::cout << "Изменения не были сохранены. До свидания.\n";
        }
    }
}
// разделить функции чтобы было без input и протестировать, принцип единой ответственности
bool FindInDictionary(const DictionaryMap &dictionary, std::string input)
{
    std::string lowerInput = ToLowerCase(input);
    
    if (dictionary.find(lowerInput) != dictionary.end())
    {
        std::cout << dictionary.at(lowerInput) << "\n";
    } 
    else if (dictionary.find(input) != dictionary.end())
    {
        std::cout << dictionary.at(input) << "\n";
    }
    else
    {
        return false;
    }
    return true;
}
void ProcessNotFound(DictionaryMap &dictionary, std::string input, bool &changesMade)
{
    std::string lowerInput = ToLowerCase(input);
    std::cout << "Неизвестное слово \"" << input << "\". Введите перевод или пустую строку для отказа.\n";
    std::string translation;
    std::getline(std::cin, translation);
    if (!translation.empty())
    {
        dictionary[lowerInput] = translation;
        changesMade = true;
        std::cout << "Слово \"" << input << "\" сохранено в словаре как \"" << dictionary[lowerInput] << "\".\n";
    } 
    else
    {
        std::cout << "Слово \"" << input << "\" проигнорировано.\n";
    }
}
int main(int argc, char* argv[]) 
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    DictionaryMap dictionary;
    std::string dictionaryFile = "";
    bool loadSuccess = false;
    if (argc >= 2)
    {
        dictionaryFile = argv[1];
        std::optional<DictionaryMap> loadDictionaryResult = LoadDictionary(dictionaryFile);
        dictionary = loadDictionaryResult.value_or(DictionaryMap{});
        loadSuccess = loadDictionaryResult.has_value();
        
    }
    bool changesMade = false;
    // вынести в процедуру
    while (true)
    {
        std::cout << ">";
        std::string input;
        std::getline(std::cin, input);
        std::string lowerInput = ToLowerCase(input);
        if (input == PROGRAM_LEAVE)
        {
            HandleProgramLeave(changesMade, loadSuccess, dictionaryFile, dictionary);
            return 0;
        } 
        else if (!FindInDictionary(dictionary, input))
        {
            ProcessNotFound(dictionary, input, changesMade);
        }
    }
    return 0;
}