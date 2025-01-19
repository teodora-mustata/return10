#include "LoginMenu.h"
import validation;
import verification;
void LoginMenu::display()
{
    while (true) {
        std::string choice;
        std::cout << "==== Login Menu ====\n";
        std::cout << "1. Login\n";
        std::cout << "2. Sign Up\n";
        std::cout << "Please select an option: ";
        std::getline(std::cin, choice);

        if (choice == "1") {
            std::string username, password;
            std::cout << "Enter your username: ";
            std::cin >> username;
            std::cout << "Enter your password: ";
            std::cin >> password;

            if (handleLogin(username, password)) {
                std::cout << "Login successful! Redirecting to main menu...\n";
                break;
            }
            else {
                showErrorMessage("The username and password don't match. Please try again.");
            }
        }
        else if (choice == "2") {
            std::string username, password, passwordVerify;
            std::cout << "Choose a username: ";
            std::cin >> username;
            std::cout << "Choose a password! Make sure it has at least one: uppercase letter, number, special caracter, and that it has over 8 characters: ";
            std::cin >> password;
            std::cout << "Reenter your password: ";
            std::cin >> passwordVerify;

            Verifier verifier;
            if (!verifier.AreEmpty(username,password,passwordVerify))
            {
                if (Validator::ValidatePassword(password) == true)
                {
                    if (password == passwordVerify && handleSignUp(username, password)) {
                        std::cout << "Account created successfully! Proceeding to log in...\n";
                        handleLogin(username, password);
                        break;
                    }
                    else if (password != passwordVerify) {
                        showErrorMessage("The passwords don't match! Please try again.\n");
                    }
                    else
                    {
                        showErrorMessage("Sign Up failed. Please try again.\n");
                    }
                }
                else {
                    showErrorMessage("Password is not strong enough! Please try again.\n");
                }
            }
        }
        else {
            std::cout << "Not a valid option! Please try again.\n";
        }
    }
}

bool LoginMenu::passwordValidation(const std::string& password)
{
    std::regex passwordRegex(R"(^(?=.*[A-Z])(?=.*[0-9])(?=.*[!@#$%^&*]).{8,}$)");
    return std::regex_match(password, passwordRegex);
}

bool LoginMenu::handleLogin(const std::string& username, const std::string& password) {
    crow::json::wvalue jsonData;
    jsonData["username"] = username;
    jsonData["password"] = password;

    auto response = cpr::Post(
        cpr::Url{ "http://localhost:18080/login" },
        cpr::Header{ {"Content-Type", "application/json"} },
        cpr::Body{ jsonData.dump() }
    );

    if (response.status_code == 200) {
        auto responseJson = crow::json::load(response.text);

        if (responseJson.has("message")) {
            std::string welcomeMessage = responseJson["message"].s();
            std::cout << welcomeMessage << std::endl;
        }

        if (responseJson.has("userId")) {
            int userId = responseJson["userId"].i();
            UserSession::getInstance().setUserId(userId);
        }

        if (responseJson.has("points") && responseJson.has("score")) {
            int points = responseJson["points"].i();
            int score = responseJson["score"].i();
            std::cout << "Points: " << points << ", Score: " << score << std::endl;
        }

        if (responseJson.has("gunDetails")) {
            auto gunDetailsJson = responseJson["gunDetails"];
            if (gunDetailsJson.has("fireRate") && gunDetailsJson.has("bulletSpeed")) {
                float fireRate = static_cast<float>(gunDetailsJson["fireRate"].d());
                float bulletSpeed = static_cast<float>(gunDetailsJson["bulletSpeed"].d());
                std::cout << "Gun - Fire Rate: " << fireRate << ", Bullet Speed: " << bulletSpeed << std::endl;
            }
        }
        return true;  
    }
    else if (response.status_code == 401) {
        showErrorMessage("Invalid username or password!");
    }
    else {
        showErrorMessage("Server error. Please try again later.");
    }

    return false; 
}

bool LoginMenu::handleSignUp(const std::string& username, const std::string& password) {
    crow::json::wvalue jsonData;
    jsonData["username"] = username;
    jsonData["password"] = password;

    auto response = cpr::Post(
        cpr::Url{ "http://localhost:18080/signup" },
        cpr::Header{ {"Content-Type", "application/json"} },
        cpr::Body{ jsonData.dump() }
    );

    if (response.status_code == 201) {
        return true;
    }
    else if (response.status_code == 409) {
        showErrorMessage("Username already exists. Please choose another.");
    }
    else {
        showErrorMessage("Server error. Please try again later.");
    }

    return false;
}

void LoginMenu::showErrorMessage(const std::string& message) {
    std::cout << "Error: " << message << "\n";
}