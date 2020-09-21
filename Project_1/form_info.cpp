#include <iostream>
#include <form_info.h>

using namespace std;

//Class Staff
Staff::Staff(){
    mName = "\0";
    mPosition = "\0";
}
Staff::Staff(QString name, QString position){
    mName = name;
    mPosition = position;
}
Staff::Staff(const Staff &person){
    mName = person.mName;
    mPosition = person.mPosition;
}
QString Staff::getName(){
    return mName;
}
QString Staff::getPosition(){
    return mPosition;
}
bool Staff::setName(QString name){
    if(name.compare("\0") != 0){
        mName = name;
        return 1;
    }
    else
        return 0;
}
bool Staff::setPosition(QString position){
    if(position.compare("\0") != 0){
        mPosition = position;
        return 1;
    }
    else
        return 0;
}

//Class Room
Room::Room(){
    mName = "\0";
    mCode = 0;
}
Room::Room(QString name, unsigned short code){
    mName = name;
    mCode = code;
}
Room::Room(const Room &ex_room){
    mName = ex_room.mName;
    mCode = ex_room.mCode;
}
QString Room::getName(){
    return mName;
}
unsigned short Room::getCode(){
    return mCode;
}
bool Room::setName(QString name){
    if(name.compare("\0") != 0){
        mName = name;
        return 1;
    }
    else
        return 0;
}
bool Room::setCode(unsigned short code){
    if(code != 0){
        mCode = code;
        return 1;
    }
    else
        return 0;
}

//Class Assets
Assets::Assets(){
    mName = "\0";
    mQuantity = 0;
    mStatus = 1;
}
Assets::Assets(QString name, unsigned char number, bool status){
    mName = name;
    mQuantity = number;
    mStatus = status;
}
Assets::Assets(const Assets &ex_assets){
    mName = ex_assets.mName;
    mQuantity = ex_assets.mQuantity;
    mStatus = ex_assets.mStatus;
}
QString Assets::getName(){
    return mName;
}
unsigned char Assets::getQuantity(){
    return mQuantity;
}
bool Assets::getStatus(){
    return mStatus;
}
bool Assets::setName(QString name){
    if(name.compare("\0") != 0){
        mName = name;
        return 1;
    }
    else
        return 0;
}
bool Assets::setQuantity(unsigned char number){
    if(number != 0){
        mQuantity = number;
        return 1;
    }
    else
        return 0;
}
bool Assets::setStatus(bool status){
    mStatus = status;
    return status;
}

//Class Form
Form::Form(){
    mFormCode = 0;
    mCheckingDay = 0;
    mCheckingStaff = Staff();
    mRoom = Room();
    mListNumber = 0;
    mAssetsList = new Assets[mListNumber+1];
    mAssetsList[0] = Assets();
}
Form::Form(unsigned short formCode, unsigned short checkingDay, Staff staff, Room room, Assets* assetsList, int listNumber){
    mFormCode = formCode;
    mCheckingDay = checkingDay;
    mCheckingStaff = staff;
    mRoom = room;
    mListNumber = listNumber;
    mAssetsList= new Assets[mListNumber];
    for (int i=0; i<listNumber; i++)
        mAssetsList[i] = *(assetsList+i*sizeof(Assets));
}
Form::Form(Form &exForm){
    mFormCode = exForm.mFormCode;
    mCheckingDay = exForm.mCheckingDay;
    mCheckingStaff = exForm.mCheckingStaff;
    mRoom = exForm.mRoom;
    mListNumber = exForm.mListNumber;
    mAssetsList = new Assets[mListNumber];
    for (int i=0; i <mListNumber; i++){
        mAssetsList[i].setName(exForm.getAssetsList(i+1).getName());
        mAssetsList[i].setQuantity(exForm.getAssetsList(i+1).getQuantity());
        mAssetsList[i].setStatus(exForm.getAssetsList(i+1).getStatus());
    }
}
unsigned short Form::getFormCode(){
    return mFormCode;
}
unsigned char Form::getCheckingDay(){
    return mCheckingDay;
}
unsigned char Form::getListNumber(){
    return mListNumber;
}
Staff Form::getStaff(){
    return mCheckingStaff;
}
Room Form::getRoom(){
    return mRoom;
}
Assets Form::getAssetsList(int number){
    if ((number > mListNumber) || (mListNumber == 0))
        return Assets();
    Assets assets;
    assets = Assets(mAssetsList[number-1]);
    return assets;
}
bool Form::setFormCode(unsigned short code){
    if(code != 0){
        mFormCode = code;
        return 1;
    }
    else
        return 0;
}
bool Form::setCheckingDay(unsigned char day){
    if(day != 0){
        mCheckingDay = day;
        return 1;
    }
    else
        return 0;
}
bool Form::setStaff(Staff person){
    if ((person.getName().compare("\0") != 0) && (person.getPosition().compare("\0") != 0)){
        this->mCheckingStaff.setName(person.getName());
        this->mCheckingStaff.setPosition(person.getPosition());
        return 1;
    }
    else
        return 0;
}
bool Form::setRoom(Room room){
    if ((room.getName().compare("\0") != 0) && (room.getCode() != 0)){
        this->mRoom.setName(room.getName());
        this->mRoom.setCode(room.getCode());
        return 1;
    }
    else
        return 0;
}
bool Form::addAssetsList(Assets newAsset){
    if ((newAsset.getName().compare("\0") == 0) || (newAsset.getQuantity() == 0))
        return 0;

    for (int i = 0; i<mListNumber; i++)
        if((mAssetsList[i].getName()).compare(newAsset.getName()) == 0){
            if (mAssetsList[i].getStatus() == newAsset.getStatus()){
                mAssetsList[i].setQuantity(mAssetsList[i].getQuantity()+newAsset.getQuantity());
                return 1;
            }
        }
    mListNumber++;
    if (mListNumber == 1){
        mAssetsList = new Assets[mListNumber];
        mAssetsList[0] = Assets(newAsset);
    }
    else{
        Assets* tempList = new Assets[mListNumber];
        for (int i=0; i<(mListNumber-1); i++)
            tempList[i] = Assets(mAssetsList[i]);
        tempList[mListNumber-1] = Assets(newAsset);

        delete[] mAssetsList;
        mAssetsList = new Assets[mListNumber];

        for (int i=0; i<mListNumber; i++){
            mAssetsList[i].setName(tempList[i].getName());
            mAssetsList[i].setQuantity(tempList[i].getQuantity());
            mAssetsList[i].setStatus(tempList[i].getStatus());
        }
        delete[] tempList;
    }
    return 1;
}
