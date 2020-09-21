#ifndef FORM_INFO_H
#define FORM_INFO_H

#include <iostream>
#include <QString>
#include "stdbool.h"

using namespace std;

class Staff{
private:
    QString mName;
    QString mPosition;

public:
    Staff();
    Staff(QString name, QString position);
    Staff(const Staff &person);

    QString getName();
    QString getPosition();
    bool setName(QString name);
    bool setPosition(QString position);
};

class Room{
private:
    QString mName;
    unsigned short mCode;

public:
    Room();
    Room(QString name, unsigned short code);
    Room(const Room& ex_room);

    QString getName();
    unsigned short getCode();
    bool setName(QString name);
    bool setCode(unsigned short code);
};

class Assets{
private:
    QString mName;
    unsigned char mQuantity;
    bool mStatus;

public:
    Assets();
    Assets(QString name, unsigned char number, bool status);
    Assets(const Assets& ex_assets);

    QString getName();
    unsigned char getQuantity();
    bool getStatus();
    bool setName(QString name);
    bool setQuantity(unsigned char number);
    bool setStatus(bool status);

};

class Form{
private:
    unsigned short mFormCode;
    unsigned char mCheckingDay;
    Staff mCheckingStaff;
    Room mRoom;
    Assets* mAssetsList;
    unsigned char mListNumber;

public:
    Form();
    Form(unsigned short formCode, unsigned short checkingDay, Staff staff, Room room, Assets* assetsList, int listNumber);
    Form(Form& exForm);

    unsigned short getFormCode();
    unsigned char getCheckingDay();
    unsigned char getListNumber();
    Staff getStaff();
    Room getRoom();
    Assets getAssetsList(int number);
    bool setFormCode(unsigned short code);
    bool setCheckingDay(unsigned char day);
    bool setStaff(Staff person);
    bool setRoom(Room room);
    bool addAssetsList(Assets newAssets);

};

#endif // FORM_INFO_H
