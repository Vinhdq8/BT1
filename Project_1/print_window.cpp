#include "print_window.h"
#include "ui_print_window.h"
#include "printdialog.h"
#include <QDebug>
#include "form_info.h"
#include <QMessageBox>

extern Form* FormList;
extern int numberList;

Print_window::Print_window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Print_window)
{
    ui->setupUi(this);
    ui->assetWidget->setEditTriggers(0); //0 = no editting
    ui->assetWidget->setColumnWidth(0,ui->assetWidget->width()/3);
    ui->assetWidget->setColumnWidth(1,ui->assetWidget->width()/3);
    ui->assetWidget->setColumnWidth(2,ui->assetWidget->width()/3-3);
}

Print_window::~Print_window()
{
    delete ui;
}

void Print_window::on_printButton_clicked()
{
    bool checkNumber = true;
    int number;
    for (int i=0; i< ui->formNumber->text().length(); i++)
        if ((ui->formNumber->text().at(i) <48) || (ui->formNumber->text().at(i) > 57)){
            QMessageBox::warning(this,"Warning","Bạn chỉ được nhập vào số, vui lòng nhập lại!");
            ui->formNumber->setText("\0");
            checkNumber = false;
            break;
        }
    if (checkNumber == true){
        if (numberList == 0){
            QMessageBox::warning(this,"Warning","Chưa có phiếu kiểm kê nào!");
            ui->formNumber->setText("\0");
        }
        else{
            number = ui->formNumber->text().toInt();
            if (number == 0){
                QMessageBox::warning(this,"Warning","Bạn cần nhập số thứ tự lớn hơn 0, vui lòng nhập lại!");
                ui->formNumber->setText("\0");
            }
            else if ((number > numberList)){
                QMessageBox::warning(this,"Warning",QString("Chỉ có %1 phiếu, không tồn tại phiếu thứ %2, vui lòng nhập lại!").arg(numberList).arg(number));
                ui->formNumber->setText("\0");
            }
            else
                this->print_form(number);
        }
    }
}

void Print_window::print_form(int number){
        ui->Form->setTitle("Phiếu số " + QString::number(number));

        ui->formcode->setText(QString("Mã phiếu: ")+QString::number(FormList[number-1].getFormCode()));
        ui->checkingday->setText(QString("Ngày kiểm kê: ")+QString::number(FormList[number-1].getCheckingDay()));
        ui->staffname->setText(QString("Nhân viên kiểm kê: ")+(FormList[number-1].getStaff().getName()));
        ui->position->setText(QString("Chức vụ: ")+FormList[number-1].getStaff().getPosition());
        ui->Roomname->setText(QString("Kiểm kê tại phòng: ")+FormList[number-1].getRoom().getName());
        ui->roomcode->setText(QString("Mã phòng: ")+QString::number(FormList[number-1].getRoom().getCode()));

        ui->assetWidget->setRowCount(FormList[number-1].getListNumber());
        ui->assetWidget->verticalHeader()->hide();
        ui->assetWidget->setMaximumHeight(ui->assetWidget->verticalHeader()->sectionSize(0)*FormList[number-1].getListNumber()+25);

        for (int i=0; i<FormList[number-1].getListNumber(); i++){
            ui->assetWidget->setItem(i,0,new QTableWidgetItem(FormList[number-1].getAssetsList(i+1).getName()));
            ui->assetWidget->setItem(i,1,new QTableWidgetItem(QString::number(FormList[number-1].getAssetsList(i+1).getQuantity())));
            if (FormList[number-1].getAssetsList(i+1).getStatus() == 1)
                ui->assetWidget->setItem(i,2,new QTableWidgetItem(QString("Tốt")));
            else
                ui->assetWidget->setItem(i,2,new QTableWidgetItem(QString("Hỏng")));
            ui->assetWidget->item(i,1)->setTextAlignment(Qt::AlignCenter);
            ui->assetWidget->item(i,2)->setTextAlignment(Qt::AlignCenter);
        }
}

void Print_window::on_addFormBtn_clicked()
{
    PrintDialog getDialog(this);
    getDialog.setModal(true);
    getDialog.exec();
}
