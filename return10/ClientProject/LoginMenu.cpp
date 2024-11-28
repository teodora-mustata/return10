#include "LoginMenu.h"

void LoginMenu::display()
{
    
    while (true) {
        int choice;
        std::cout << "==== Login Menu ====\n";
        std::cout << "1. Login\n";
        std::cout << "2. Sign Up\n";
        std::cout << "Please select an option: ";
        std::cin >> choice;

        if (choice == 1) {
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
        else if (choice == 2) {
            std::string username, password, passwordVerify;
            std::cout << "Choose a username: ";
            std::cin >> username;
            std::cout << "Choose a password: ";
            std::cin >> password;
            std::cout << "Reenter your password: ";
            std::cin >> passwordVerify;

            if (password == passwordVerify && handleSignUp(username, password)) {
                std::cout << "Account created successfully! Proceeding to log in...\n";
                handleLogin(username, password);
                break;
            }
            else if (password != passwordVerify) {
                showErrorMessage("The passwords don't match! Please try again.\n");
            }
            else {
                showErrorMessage("Sign Up failed. Please try again.\n");
            }
        }
        else {
            std::cout << "Not a valid option! Please try again.\n";
        }
    }
}

bool LoginMenu::handleLogin(const std::string& username, const std::string& password) {
    // Creează un obiect JSON cu datele utilizatorului
    crow::json::wvalue jsonData;
    jsonData["username"] = username;
    jsonData["password"] = password;

    // Trimite un POST request către server
    auto response = cpr::Post(
        cpr::Url{ "http://localhost:18080/login" },
        cpr::Header{ {"Content-Type", "application/json"} },
        cpr::Body{ jsonData.dump() }
    );

    // Verifică răspunsul serverului
    if (response.status_code == 200) {
        auto responseJson = crow::json::load(response.text);

        // Verificăm existența cheii "message"
        if (responseJson.has("message")) {
            std::string welcomeMessage = responseJson["message"].s();
            std::cout << welcomeMessage << std::endl;
            std::cout << "A intrat aici";
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

    // Trimite un POST request către server
    auto response = cpr::Post(
        cpr::Url{ "http://localhost:18080/signup" },
        cpr::Header{ {"Content-Type", "application/json"} },  // Setează tipul de conținut ca JSON
        cpr::Body{ jsonData.dump() }  // Corpul cererii ca JSON (folosind `dump()` pentru a obține un string JSON)
    );

    // Verifică răspunsul serverului
    if (response.status_code == 201) {
        return true;  // Înregistrare reușită
    }
    else if (response.status_code == 409) {
        showErrorMessage("Username already exists. Please choose another.");
    }
    else {
        showErrorMessage("Server error. Please try again later.");
    }

    return false;  // Înregistrare eșuată
}

void LoginMenu::showErrorMessage(const std::string& message) {
    std::cout << "Error: " << message << "\n";
}