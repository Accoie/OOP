#include "stdafx.h"

std::string ReplaceString(const std::string& subject, const std::string& searchString, const std::string& replacementString)
{
   
    if (searchString.empty())
    {
        return subject;
    }

    std::string result;
    size_t pos = 0;
    size_t searchLen = searchString.length();

    while (pos < subject.length())
    {
        size_t foundPos = subject.find(searchString, pos);

        if (foundPos == std::string::npos)
        {
            result.append(subject, pos, subject.length() - pos);
            break;
        }

        result.append(subject, pos, foundPos - pos);
        result.append(replacementString);

        pos = foundPos + searchLen;
    }

    return result;
}

void CopyStreamWithReplacement(std::istream& input, std::ostream& output, const std::string& searchString, const std::string& replacementString)
{
    std::string line;
    bool hasInput = false;

    while (std::getline(input, line) && !line.empty())
    {
        hasInput = true;
        output << ReplaceString(line, searchString, replacementString) << "\n";
    }

    if (!hasInput)
    {
        
        if ((!searchString.empty() || !replacementString.empty()) && line.empty())
        {
            std::cerr << "ERROR\n";
        }
        
        std::cout << "\n";
    }
}

bool CopyFileWithReplacement(const std::string& inputFileName, const std::string& outputFileName, const std::string& searchString, const std::string& replacementString)
{
    std::ifstream inputFile(inputFileName);
    if (!inputFile)
    {
        std::cerr << "ERROR\n";
        return false;
    }

    std::ofstream outputFile(outputFileName);
    if (!outputFile)
    {
        std::cerr << "ERROR\n";
        return false;
    }

    CopyStreamWithReplacement(inputFile, outputFile, searchString, replacementString);
    return true;
}

int main(int argc, char* argv[])
{
    if (argc == 5)
    {
        std::string inputFile = argv[1];//кортеж
        std::string outputFile = argv[2];
        std::string searchString = argv[3];
        std::string replacementString = argv[4];

        if (!CopyFileWithReplacement(inputFile, outputFile, searchString, replacementString))
        {
            return 1;
        }
        return 0; // вынести 
    } 
    else if (argc == 2 && std::string(argv[1]) == "-h")
    {
        std::cout << "Usage: replace.exe <inputFile> <outputFile> <searchString> <replacementString>\n";
        return 0;
    }
    else if (argc == 1)
    {
        std::string searchString, replacementString;
        if (!std::getline(std::cin, searchString) || !std::getline(std::cin, replacementString))
        {
            std::cout << "ERROR\n";
            return 0; 
        }

        CopyStreamWithReplacement(std::cin, std::cout, searchString, replacementString);
        return 0;
    } 
    else
    {
        std::cout << "Invalid argument count\n"
            << "Usage: replace.exe <inputFile> <outputFile> <searchString> <replacementString>\n";
        return 1;
    }
}
// добавить bat с неполными аргументами