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
    // Trimit datele către server pentru validare
    // to do 
    if (username == "user123" && password == "password123")  //placeholder
    {
        return true;  // Login reușit
    }
    return false;  // Login eșuat
}

bool LoginMenu::handleSignUp(const std::string& username, const std::string& password) {
    // Trimite datele pentru crearea unui cont pe server
    // to do
    return true; // Returnează true sau false în funcție de răspunsul serverului
}

void LoginMenu::showErrorMessage(const std::string& message) {
    std::cout << "Error: " << message << "\n";
}