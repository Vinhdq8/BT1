#include "printdialog.h"
#include "ui_printdialog.h"
#include <QString>
#include "form_info.h"
#include <QMessageBox>
#include <QDebug>

extern Form* FormList;
extern int numberList;
Form newForm;
Assets exAssets;

PrintDialog::PrintDialog(QWidget *parent):
    QDialog(parent),
    ui(new Ui::PrintDialog)
{
    ui->setupUi(this);
    ui->assetWidget->setColumnWidth(0,ui->assetWidget->width()/3);
    ui->assetWidget->setColumnWidth(1,ui->assetWidget->width()/3);
    ui->assetWidget->setColumnWidth(2,ui->assetWidget->width()/3-3);
    ui->assetWidget->verticalHeader()->hide();
    newForm = Form();

    connect(ui->checkBtn,SIGNAL(clicked()),this,SLOT(close()));
}

PrintDialog::~PrintDialog()
{
    delete ui;
}

bool PrintDialog::checkInt(QString text){
    bool checkNumber = true;
    for (int i=0; i< text.length(); i++)
        if ((text.at(i) <48) || (text.at(i) > 57)){
            QMessageBox::warning(this,"Warning","Bạn chỉ được nhập vào số, vui lòng nhập lại!");
            checkNumber = false;
            break;
        }
    return checkNumber;
}

void PrintDialog::on_formCodeEdit_editingFinished()
{
   if (ui->formCodeEdit->text().compare("\0") == 0)
       QMessageBox::warning(this,"Warning","Bạn chưa nhập mã phiếu!");
   else if (checkInt(ui->formCodeEdit->text()))
       newForm.setFormCode(ui->formCodeEdit->text().toInt());
   else
       ui->formCodeEdit->setText("\0");
}

void PrintDialog::on_dayEdit_editingFinished()
{
    if (ui->dayEdit->text().compare("\0") == 0)
        QMessageBox::warning(this,"Warning","Bạn chưa nhập ngày!");
    else
    if (checkInt(ui->dayEdit->text()))
        if ((ui->dayEdit->text().toInt() == 0 ) || (ui->formCodeEdit->text().toInt()>31))
            QMessageBox::warning(this,"Warning","Bạn nhập sai ngày, vui lòng nhập lại!");
        else
            newForm.setCheckingDay(ui->dayEdit->text().toInt());
    else
        ui->dayEdit->setText("\0");
}

void PrintDialog::on_StaffNameCode_editingFinished()
{
    if (ui->StaffNameCode->text().compare("\0") == 0)
        QMessageBox::warning(this,"Warning","Bạn chưa nhập tên nhân viên!");
    else
        newForm.setStaff(Staff(ui->StaffNameCode->text(),ui->positionEdit->text()));
}

void PrintDialog::on_positionEdit_editingFinished()
{
    if (ui->positionEdit->text().compare("\0") == 0)
        QMessageBox::warning(this,"Warning","Bạn chưa nhập chức vụ của nhân viên!");
    else
        newForm.setStaff(Staff(ui->StaffNameCode->text(),ui->positionEdit->text()));
}

void PrintDialog::on_RoomNameEdit_editingFinished()
{
    if (ui->RoomNameEdit->text().compare("\0") == 0)
        QMessageBox::warning(this,"Warning","Bạn chưa nhập tên phòng!");
    else if (ui->roomCodeEdit->text().compare("\0") == 0)
        newForm.setRoom(Room(ui->RoomNameEdit->text(),0));
    else
        newForm.setRoom(Room(ui->RoomNameEdit->text(),ui->roomCodeEdit->text().toInt()));
}

void PrintDialog::on_roomCodeEdit_editingFinished()
{
    if (ui->roomCodeEdit->text().compare("\0") == 0)
        QMessageBox::warning(this,"Warning","Bạn chưa nhập mã phòng!");
    else if (checkInt(ui->roomCodeEdit->text()))
        newForm.setRoom(Room(ui->RoomNameEdit->text(),ui->roomCodeEdit->text().toInt()));
    else
        ui->roomCodeEdit->setText("\0");
}

void PrintDialog::printAssets(){
    ui->assetWidget->setRowCount(newForm.getListNumber());
    ui->assetWidget->verticalHeader()->hide();

    for (int i=0; i<newForm.getListNumber(); i++){
        ui->assetWidget->setItem(i,0,new QTableWidgetItem(newForm.getAssetsList(i+1).getName()));
        ui->assetWidget->setItem(i,1,new QTableWidgetItem(QString::number(newForm.getAssetsList(i+1).getQuantity())));
        if (newForm.getAssetsList(i+1).getStatus() == 1)
            ui->assetWidget->setItem(i,2,new QTableWidgetItem(QString("Tốt")));
        else
            ui->assetWidget->setItem(i,2,new QTableWidgetItem(QString("Hỏng")));
        ui->assetWidget->item(i,1)->setTextAlignment(Qt::AlignCenter);
        ui->assetWidget->item(i,2)->setTextAlignment(Qt::AlignCenter);
    }
}

void PrintDialog::on_assetNameEdit_editingFinished()
{
    if (ui->assetNameEdit->text().compare("\0") == 0)
        QMessageBox::warning(this,"Warning","Bạn chưa nhập tên tài sản!");
}

void PrintDialog::on_AssetQuantityEdit_editingFinished()
{
    if (ui->AssetQuantityEdit->text().compare("\0") == 0)
        QMessageBox::warning(this,"Warning","Bạn chưa nhập số lượng tài sản!");
    else if (!checkInt(ui->AssetQuantityEdit->text()))
        ui->AssetQuantityEdit->setText("\0");
}

void PrintDialog::on_statusEdit_editingFinished()
{
    if (ui->statusEdit->text().compare("\0") == 0)
        QMessageBox::warning(this,"Warning","Bạn chưa nhập tình trạng tài sản!");
    else if((!ui->statusEdit->text().compare("G")) && (!ui->statusEdit->text().compare("B"))){
        QMessageBox::warning(this,"Warning","Bạn đã nhập sai tình trạng tài sản, vui lòng nhập lại!");
        ui->statusEdit->setText("\0");
    }
}

void PrintDialog::on_assetsBtn_clicked()
{
    if((ui->assetNameEdit->text().compare("\0") == 0)||(ui->AssetQuantityEdit->text().compare("\0") == 0)||(ui->statusEdit->text().compare("\0") == 0))
        QMessageBox::warning(this,"Warning","Bạn chưa nhập đủ thông tin tài sản mới, vui lòng nhập lại!");
    else{
        if ((ui->assetNameEdit->text().compare(exAssets.getName()) == 0)&&(ui->AssetQuantityEdit->text().toInt() == exAssets.getQuantity())&&!(!ui->statusEdit->text().compare("G") ^ exAssets.getStatus())){
                QMessageBox::warning(this,"Warning","Vui lòng nhập thông tin tài sản mới!");
        }
        else{
            if  (!ui->statusEdit->text().compare("G")){
                newForm.addAssetsList(Assets(ui->assetNameEdit->text(),ui->AssetQuantityEdit->text().toInt(),true));
                exAssets = Assets(ui->assetNameEdit->text(),ui->AssetQuantityEdit->text().toInt(),true);
                printAssets();
            }
            else{
                newForm.addAssetsList(Assets(ui->assetNameEdit->text(),ui->AssetQuantityEdit->text().toInt(),false));
                exAssets = Assets(ui->assetNameEdit->text(),ui->AssetQuantityEdit->text().toInt(),false);
                printAssets();
            }
        }
    }
}

void PrintDialog::on_checkBtn_clicked()
{
    if((newForm.getFormCode()==0)||(newForm.getCheckingDay()==0)||(!newForm.getStaff().getName().compare("\0"))||(!newForm.getStaff().getPosition().compare("\0"))||(!newForm.getRoom().getName().compare("\0"))||(newForm.getRoom().getCode()==0)||(newForm.getListNumber()==0))
        QMessageBox::warning(this,"Warning","Bạn chưa nhập đủ thông tin, vui lòng nhập đủ!");
    else {
        numberList++;
        FormList[numberList-1] = Form(newForm);
    }
}
