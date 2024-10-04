#include "stringProcessing.h"
#include <string>
#include <cctype>

using namespace std;

string stripNonAlphaNum(string input) {
    // use loop to find the index of the first alphanumeric char
    size_t startIndex = 0;
    // while start is less than the input length is not alphanumeric
    while (startIndex < input.length() and not isalnum(input[startIndex])) {
        ++startIndex;
    }

    // use loop to find the index of the last alphanumeric char
    size_t endIndex = (input.length() - 1);
    while (endIndex > startIndex and not isalnum(input[endIndex])) {
        --endIndex;
    }

    // return the substring containing only alphanumeric characters
    return input.substr(startIndex, (endIndex - startIndex + 1));
}