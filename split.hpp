#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include<iostream>
#include<sstream>
#include <vector>
std::vector<std::string> split(const std::string& originalString, const std::string& delimiter) {
    std::vector<std::string> tokens;
    size_t startPos = 0;
    size_t foundPos = originalString.find(delimiter);

    while (foundPos != std::string::npos) {
        tokens.push_back(originalString.substr(startPos, foundPos - startPos));
        startPos = foundPos + delimiter.length();
        foundPos = originalString.find(delimiter, startPos);
    }

    // Add the last token (or the whole string if delimiter not found)
    tokens.push_back(originalString.substr(startPos));

    return tokens;
}