#include "LoginMenu.h"

void LoginMenu::display()
{
    std::cout << "==== Login Menu ====\n";
    std::cout << "1. Login\n";
    std::cout << "2. Sign Up\n";
    std::cout << "Please select an option: ";

    int choice;
    std::cin >> choice;

    if (choice == 1) {
        std::string username, password;
        std::cout << "Enter your username: ";
        std::cin >> username;
        std::cout << "Enter your password: ";
        std::cin >> password;

        if (handleLogin(username, password)) {
            std::cout << "Login successful! Redirecting to main menu...\n";
            // Redirect to Main Menu
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
            std::cout << "Account created successfully! Please log in.\n";
        }
        else if (password != passwordVerify)
        {
            showErrorMessage("The passwords don't match! Please try again.");
        }
        else showErrorMessage("Sign Up failed. Please try again.");
    }
}

bool LoginMenu::handleLogin(const std::string& username, const std::string& password) {
    // Trimite un POST request către server
    auto response = cpr::Post(
        cpr::Url{ "http://localhost:18080/login" },
        cpr::Payload{
            {"username", username},
            {"password", password}
        }
    );

    // Verifică răspunsul serverului
    if (response.status_code == 200) {
        return true;  // Login reușit
    }
    else if (response.status_code == 400) {
        showErrorMessage("Invalid username or password!");
    }
    else {
        showErrorMessage("Server error. Please try again later.");
    }

    return false;  // Login eșuat
}

bool LoginMenu::handleSignUp(const std::string& username, const std::string& password) {
    // Crează un obiect JSON manual, folosind Crow
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