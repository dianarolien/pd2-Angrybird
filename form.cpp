#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    key = 0;
}

Form::~Form()
{
    delete ui;
}

void Form::on_restart_clicked()
{
    this->hide();
    key = 1;
}

void Form::on_exit_clicked()
{
    key = 2;
    this->hide();
}
