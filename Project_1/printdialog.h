#ifndef PRINTDIALOG_H
#define PRINTDIALOG_H

#include <QDialog>

namespace Ui {
class PrintDialog;
}

class PrintDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PrintDialog(QWidget *parent = 0);
    ~PrintDialog();

private slots:

    void on_formCodeEdit_editingFinished();

    void on_dayEdit_editingFinished();

    void on_StaffNameCode_editingFinished();

    void on_positionEdit_editingFinished();

    void on_RoomNameEdit_editingFinished();

    void on_roomCodeEdit_editingFinished();

    void on_assetNameEdit_editingFinished();

    void on_AssetQuantityEdit_editingFinished();

    void on_statusEdit_editingFinished();

    void on_assetsBtn_clicked();

    void on_checkBtn_clicked();

protected:
    bool checkInt(QString text);
    void printAssets();
private:
    Ui::PrintDialog *ui;
};

#endif // PRINTDIALOG_H
