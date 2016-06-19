#ifndef FORM_H
#define FORM_H

#include <QWidget>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = 0);
    ~Form();
    int key;

private slots:
    void on_restart_clicked();

    void on_exit_clicked();

private:
    Ui::Form *ui;
};

#endif // FORM_H
