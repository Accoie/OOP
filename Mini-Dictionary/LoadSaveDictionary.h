#pragma once

#include <map>
#include <string>
#include <optional>

using DictionaryMap = std::map<std::string, std::string>;

//std::optional добавить
std::optional<DictionaryMap> LoadDictionary(const std::string& filename);

int SaveDictionary(const std::string& filename, const DictionaryMap& dictionary);
