#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "../json.hpp"

using json = nlohmann::json;
using namespace std;


class Auth {
public:
    static bool registerUser(const string& username, const string& password);
    static bool loginUser(const string& username, const string& password);
};


