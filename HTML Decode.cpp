#include <string>
#include <iostream>
#include <map>

const std::map<std::string, std::string> REPLACEMENTS = {
            {"&quot;", "\""},
            {"&apos;", "'"},
            {"&lt;", "<"},
            {"&amp;", "&"},
            {"&gt;", ">"},
};

const int MIN_LENGTH = 4;
const int MAX_LENGTH = 6;
const char AMPERSAND = '&';
const std::string EMPTY_STRING = "";

std::string GetReplacement(std::string str) 
{   
    return REPLACEMENTS.find(str) != REPLACEMENTS.end() ? REPLACEMENTS.at(str) : str;
}
void AddAndReset(std::string addingString, std::string changingString, std::string& changedString, std::string& addedString)
{
    addedString += addingString;
    changedString = changingString;
}
void TryReplace(std::string& tempString, std::string& resultString)
{
    if (tempString.length() >= MIN_LENGTH && tempString.length() <= MAX_LENGTH)
    {
        std::string replacedString = GetReplacement(tempString);
        if (tempString != replacedString)
        {
            AddAndReset(replacedString, EMPTY_STRING, tempString, resultString);
        } 
        else if (tempString.length() == MAX_LENGTH)
        {
            AddAndReset(tempString, EMPTY_STRING, tempString, resultString);
        }
    }
}
int HandleNonAmpersand(std::string &tempString, std::string &resultString)
{
    if (tempString.length() >= 1)
    {
        TryReplace(tempString, resultString);
    }
    else
    {
        AddAndReset(tempString, EMPTY_STRING, tempString, resultString);
    }
    return 0;
}
std::string HtmlDecode(const std::string &html)
{
    std::string tempString;
    std::string resultString;

    for (char ch : html)
    {
        if (ch == AMPERSAND)
        {
            
            resultString += tempString;
            tempString = ch;         
        } 
        else
        {
            tempString += ch;
            HandleNonAmpersand(tempString, resultString);
        }
    }
    return resultString + tempString;
}
int main()
{
    std::string html = "";
    if (!std::getline(std::cin, html))
    {
        std::cout << "ERROR\n";
        return 1;
    }
    std::string htmlDecoded = HtmlDecode(html);
    std::cout << htmlDecoded << "\n";
    return 0;
}