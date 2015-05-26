/********************************************************************************
** Form generated from reading UI file 'AddEntryForm.ui'
**
** Created: Wed Mar 28 21:46:57 2012
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDENTRYFORM_H
#define UI_ADDENTRYFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QDialogButtonBox *btnBoxOkCancel;
    QLineEdit *editChooseCommand;
    QLabel *label;
    QPushButton *btnChooseCmd;
    QPushButton *btnChooseIcon;
    QLabel *label_2;
    QLineEdit *editChooseIcon;
    QLabel *label_3;
    QLineEdit *editChooseDecription;
    QLabel *label_4;
    QLineEdit *editChooseTooltip;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(398, 325);
        btnBoxOkCancel = new QDialogButtonBox(Dialog);
        btnBoxOkCancel->setObjectName(QString::fromUtf8("btnBoxOkCancel"));
        btnBoxOkCancel->setGeometry(QRect(40, 270, 341, 32));
        btnBoxOkCancel->setOrientation(Qt::Horizontal);
        btnBoxOkCancel->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        editChooseCommand = new QLineEdit(Dialog);
        editChooseCommand->setObjectName(QString::fromUtf8("editChooseCommand"));
        editChooseCommand->setGeometry(QRect(20, 50, 331, 21));
        label = new QLabel(Dialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 30, 111, 16));
        btnChooseCmd = new QPushButton(Dialog);
        btnChooseCmd->setObjectName(QString::fromUtf8("btnChooseCmd"));
        btnChooseCmd->setGeometry(QRect(360, 50, 21, 21));
        btnChooseIcon = new QPushButton(Dialog);
        btnChooseIcon->setObjectName(QString::fromUtf8("btnChooseIcon"));
        btnChooseIcon->setGeometry(QRect(360, 110, 21, 21));
        label_2 = new QLabel(Dialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 90, 111, 16));
        editChooseIcon = new QLineEdit(Dialog);
        editChooseIcon->setObjectName(QString::fromUtf8("editChooseIcon"));
        editChooseIcon->setGeometry(QRect(20, 110, 331, 21));
        label_3 = new QLabel(Dialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 150, 111, 16));
        editChooseDecription = new QLineEdit(Dialog);
        editChooseDecription->setObjectName(QString::fromUtf8("editChooseDecription"));
        editChooseDecription->setGeometry(QRect(20, 170, 331, 21));
        label_4 = new QLabel(Dialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(20, 210, 111, 16));
        editChooseTooltip = new QLineEdit(Dialog);
        editChooseTooltip->setObjectName(QString::fromUtf8("editChooseTooltip"));
        editChooseTooltip->setGeometry(QRect(20, 230, 331, 21));

        retranslateUi(Dialog);
        QObject::connect(btnBoxOkCancel, SIGNAL(accepted()), Dialog, SLOT(accept()));
        QObject::connect(btnBoxOkCancel, SIGNAL(rejected()), Dialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0, QApplication::UnicodeUTF8));
        editChooseCommand->setPlaceholderText(QString());
        label->setText(QApplication::translate("Dialog", "Command", 0, QApplication::UnicodeUTF8));
        btnChooseCmd->setText(QApplication::translate("Dialog", "...", 0, QApplication::UnicodeUTF8));
        btnChooseIcon->setText(QApplication::translate("Dialog", "...", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Dialog", "Icon", 0, QApplication::UnicodeUTF8));
        editChooseIcon->setPlaceholderText(QString());
        label_3->setText(QApplication::translate("Dialog", "Description", 0, QApplication::UnicodeUTF8));
        editChooseDecription->setPlaceholderText(QString());
        label_4->setText(QApplication::translate("Dialog", "Tooltip", 0, QApplication::UnicodeUTF8));
        editChooseTooltip->setPlaceholderText(QString());
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDENTRYFORM_H
