#ifndef PRINT_WINDOW_H
#define PRINT_WINDOW_H

#include <QMainWindow>

namespace Ui {
class Print_window;
}

class Print_window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Print_window(QWidget *parent = 0);
    ~Print_window();

private slots:
    void on_printButton_clicked();

    void on_addFormBtn_clicked();

protected:
    void print_form(int number);
private:
    Ui::Print_window *ui;
};

#endif // PRINT_WINDOW_H
