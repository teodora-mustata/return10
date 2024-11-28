#pragma once
class UserSession {
public:
    static UserSession& getInstance() {
        static UserSession instance;
        return instance;
    }

    void setUserId(int id) {
        currentUserId = id;
    }

    int getUserId() const {
        return currentUserId;
    }

private:
    UserSession() : currentUserId(-1) {}
    int currentUserId;
};