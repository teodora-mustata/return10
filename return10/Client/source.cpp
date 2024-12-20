//#include <iostream>
//#include <cpr/cpr.h>
//#include <crow.h>
//#include "LoginMenu.h"
//#include "MainMenu.h"
//
//int main()
//{
//    std::cout << "Client" << std::endl;
//    try {
//        std::cout << "Welcome to Battle City!\n";
//
//        LoginMenu loginMenu;
//        loginMenu.display();
//        if (UserSession::getInstance().getUserId() != -1)
//        {
//            MainMenu mainMenu;
//            mainMenu.display();
//        }
//        else {
//            std::cout << "You need to log in to proceed!\n";
//        }
//
//    }
//    catch (const std::exception& e) {
//        std::cerr << "An unexpected error occurred: " << e.what() << '\n';
//    }
//    catch (...) {
//        std::cerr << "An unknown error occurred." << '\n';
//    }
//
//    return 0;
//
//}