#include "IsValidIdentifier.h"

bool IsValidIdentifier(const std::string& id)
{
    if (id.empty()) return false;

    char first = id[0];
    if (!(std::isalpha(static_cast<unsigned char>(first)) && first != '_'))
    {
        return false;
    }

    for (char c : id)
    {
        if (!(std::isalnum(static_cast<unsigned char>(c))) && c != '_')
        {
            return false;
        }
    }
    return true;
}