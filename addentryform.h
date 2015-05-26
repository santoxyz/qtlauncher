#ifndef ADDENTRYFORM_H
#define ADDENTRYFORM_H

#include <QWidget>
#include <QDialog>
#include <entry.h>
#include "ui_AddEntryForm.h"
class AddEntryForm : public QDialog
{
    Q_OBJECT
public:
    entry e;
    explicit AddEntryForm(QDialog *parent = 0);
    virtual ~AddEntryForm();
signals:

public slots:

private slots:
    void on_btnChooseCmd_clicked();
    void on_btnChooseIcon_clicked();
    void on_btnBoxOkCancel_accepted();

private:
    Ui::Dialog ui;

};

#endif // ADDENTRYFORM_H
