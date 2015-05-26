#include "addentryform.h"
#include <QDebug>
#include <QFileDialog>
AddEntryForm::AddEntryForm(QDialog *parent) :
    QDialog(parent)
{
    ui.setupUi(this);
    exec();
}

AddEntryForm::~AddEntryForm()
{
//    delete ui;
}

void AddEntryForm::on_btnChooseCmd_clicked()
{
    qDebug()<<__func__;
    e.cmd = QFileDialog::getOpenFileName(this,
         tr("Choose command"), "/usr/bin", tr("Excutables (*)"));
    ui.editChooseCommand->setText(e.cmd);
}

void AddEntryForm::on_btnChooseIcon_clicked()
{
    qDebug()<<__func__;
    e.ico = QFileDialog::getOpenFileName(this,
         tr("Choose icon"), "/usr/share/icons/hicolor/48x48/apps/", tr("Icons (*.png *.jpg *.bmp *.ico *.svg)"));
    ui.editChooseIcon->setText(e.ico);
}

void AddEntryForm::on_btnBoxOkCancel_accepted()
{
    qDebug()<<__func__;
    e.cmd = ui.editChooseCommand->text();
    e.ico = ui.editChooseIcon->text();

    if(ui.editChooseDecription->text().isEmpty())
        e.descr = e.cmd;
    else
        e.descr = ui.editChooseDecription->text();

    if(ui.editChooseTooltip->text().isEmpty())
        e.tooltip= e.cmd;
    else
        e.tooltip= ui.editChooseTooltip->text();

}
