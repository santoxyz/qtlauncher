#include "mainwindow.h"
#include <QButtonGroup>
#include <QPushButton>
#include <QIcon>
#include <QGridLayout>
#include <QDebug>
#include <launchbutton.h>
#include <entry.h>
#include <QFile>
#include <QDir>
#include <QApplication>
#include <QDesktopWidget>
#include <QTime>
#include "ui_AddEntryForm.h"
#include "addentryform.h"

#define SUSPEND_CMD "gksudo pm-suspend"
#define SHUTDOWN_CMD "gksudo \"shutdown -h now\" "

#define NEWITEM "/usr/share/icons/hicolor/48x48/apps/libreoffice-main.png"
#define WIFI "/usr/share/icons/hicolor/24x24/apps/wicd-gtk.png"
#define SUSPEND "/usr/share/icons/gnome/24x24/actions/xfce-system-lock.png" //exit
#define ADDNEW "/usr/share/icons/gnome/48x48/actions/add.png"
#define SHUTDOWN "/usr/share/icons/gnome/24x24/actions/xfce-system-exit.png"

using namespace Ui;

void MainWindow::launch(QAbstractButton *btn)
{
    qDebug() << __func__ << "btn" << btn;
    QApplication* app = (QApplication*)this->parent();

    if(((launchButton*)btn)->getCmdName()=="qtLauncherAddNewEntry")
    {
        qDebug()<<"qtLauncherAddNewEntry";
        AddEntryForm* aef =new AddEntryForm;

        ///AddEntryForm è un QDialog;
        // continuo sotto solo alla pressione di OK o Cancel nel form

        if(aef->e.cmd.isEmpty())
        {
            delete aef;
            return;
        }

        if(aef->e.ico.isEmpty())
            aef->e.ico=NEWITEM;
        lEntries.append(aef->e);

        SaveListEntries(lEntries);
        delete aef;

        QProcess::startDetached(app->arguments()[0]);

    }
    else
    {
        ((launchButton*)btn)->launch();
    }

    qDebug()<<"exiting qtLauncher";
    app->exit(0);

}

QList<entry> MainWindow::fakeListEntries()
{
    entry e;
    e.cmd = "/usr/bin/chromium-browser";
    e.descr = "Chromium";
    e.ico = "/usr/share/icons/hicolor/48x48/apps/chromium.png";
    lEntries.append(e);
    e.cmd = "geany";
    e.descr = "Geany";
    e.ico = "/usr/share/icons/hicolor/48x48/apps/geany.png";
    lEntries.append(e);
    e.cmd = "qtcreator";
    e.descr = "QtCreator";
    e.ico = "/usr/share/icons/hicolor/48x48/apps/qtcreator.png";
    lEntries.append(e);
    return lEntries;
}

void MainWindow::SaveListEntries(QList<entry> lEntries)
{
    QDir dir;
    dir.mkpath("/home/s/.config/qtlauncher/");
    QFile file("/home/s/.config/qtlauncher/entries.list");
    if (file.open(QFile::WriteOnly | QFile::Truncate))
    {
        QTextStream stream(&file);
        for (int i=0;i<lEntries.count();i++)
        {
            stream << "Entry="<<i;
            stream << "\ndescr=" << lEntries.at(i).descr;
            stream << "\ncmd=" << lEntries.at(i).cmd;
            stream << "\nico=" << lEntries.at(i).ico;
            stream << "\ntooltip=" << lEntries.at(i).tooltip;
            stream << "\n";
        }
    }
    else qDebug()<< __func__<<": unable to create file";
}

QList<entry>  MainWindow::LoadListEntries()
{
    QDir dir;
    dir.mkpath("/home/s/.config/qtlauncher/");
    QFile file("/home/s/.config/qtlauncher/entries.list");
    if (file.open(QFile::ReadOnly))
    {
        QTextStream stream(&file);
        QString s;
        entry e;
        while(!(s=stream.readLine()).isNull()){
            QStringList sl = s.split("=");
            if(sl[0].compare("descr")==0) {e.descr=sl[1];}
            else if(sl[0].compare("cmd")==0){e.cmd=sl[1];}
            else if(sl[0].compare("ico")==0){e.ico=sl[1];}
            else if(sl[0].compare("tooltip")==0){e.tooltip=sl[1];}
            else if(sl[0].compare("Entry")==0){
                if(sl[1].compare("0")!=0)
                    lEntries.append(e);/*newEntry*/
            };

        }
        lEntries.append(e); /*add Last Entry*/
    }
    else qDebug()<< __func__<<": unable to create file";
    return lEntries; //TODO: rivedere
}

void MainWindow::speedlaunch()
{
    qDebug()<<__func__;
    QProcess::startDetached(quicklaunch->text());
    exit(0);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent/*,Qt::FramelessWindowHint*/)
//    ,ui(new Ui::MainWindow)
{
//    ui->setupUi(this);
    QDesktopWidget* desk = QApplication::desktop();

    setPalette( QPalette( Qt::black ) );
    setWindowFlags(windowFlags()
                   | Qt::FramelessWindowHint
                   | Qt::WindowStaysOnTopHint);
//    setWindowOpacity(0.9);
    QBoxLayout *mainLayout = new QBoxLayout(QBoxLayout::TopToBottom);
    QBoxLayout *widgetLayout = new QBoxLayout(QBoxLayout::LeftToRight);
    QBoxLayout *btnLayout = new QBoxLayout(QBoxLayout::LeftToRight);

    quicklaunch=new QLineEdit;
    connect(quicklaunch,SIGNAL(returnPressed()),this,SLOT(speedlaunch()));
    widgetLayout->addWidget(quicklaunch);
    QLabel*time=new QLabel;
    time->setText(QTime::currentTime().toString("H:mm"));
    widgetLayout->addWidget(time);

    QSize d(24,24);
    launchButton* s;

    s = new launchButton(QIcon(WIFI));
    s->setBaseSize(d);
    s->setMaximumSize(d);
    connect(s,SIGNAL(clicked()),this,SLOT(wificonnect()));
    widgetLayout->addWidget(s);


    s = new launchButton(QIcon(SUSPEND));
    s->setBaseSize(d);
    s->setMaximumSize(d);
    connect(s,SIGNAL(clicked()),this,SLOT(sleep()));
    widgetLayout->addWidget(s);

    s = new launchButton(QIcon(SHUTDOWN));
    s->setBaseSize(d);
    s->setMaximumSize(d);
    connect(s,SIGNAL(clicked()),this,SLOT(shutdown()));
    widgetLayout->addWidget(s);

    //aggiornamento time
    //creazione layout time??
    mainLayout->addLayout(widgetLayout );


    btnGrp = new QButtonGroup();
    QWidget *w =new QWidget(this);
    lEntries = LoadListEntries();
    if(lEntries.empty())
        lEntries = fakeListEntries();
    for (int i=0;i<=lEntries.count();i++)
    {
        QString num;
        launchButton* btn;
        num = QString::number(i+1);
        if(i<lEntries.count())
        {
            entry e = lEntries.at(i);
            btn = new launchButton(QIcon(e.ico));
            btn->setToolTip(e.descr);
            btn->setCmdName(e.cmd);
            connect(btn,SIGNAL(remove(QWidget*)),this,SLOT(removeItem(QWidget*)));
            connect(btn,SIGNAL(edit(QWidget*)),this,SLOT(editItem(QWidget*)));

            if(i==0)
                this->setFocusProxy(btn);
        }
        else //add new
        {
            btn = new launchButton(QIcon(ADDNEW
                                         /*"/usr/share/icons/Humanity/actions/128/bookmark-new.svg"*/));
            btn->setToolTip("Add New");
            btn->setCmdName("qtLauncherAddNewEntry");
        }
        btn->setShortcut(QKeySequence(num));
        btn->setFixedSize(64,64);
        btn->setIconSize(QSize(48,48));
        btn->setFlat(true);
        btnGrp->addButton(btn);
        btnLayout->addWidget(btn);
        //mainLayout->addWidget(btn, 1, i+1);
        //btn->setText(num);

    }
    mainLayout->addLayout(btnLayout);

    connect(btnGrp,SIGNAL(buttonClicked(QAbstractButton*)),
            this,SLOT(launch(QAbstractButton*)));
    w->setMinimumSize(800 /*desk->width()*/,24+64+16+16);
    w->setMaximumSize(1366 /*desk->width()*/,24+64+16+16);

    w->setLayout(mainLayout);
    this->setCentralWidget(w);
    setMaximumHeight(24+64+16+16);
    setMaximumWidth(1366);
    setGeometry(0,0,1366,maximumHeight());

}
MainWindow::~MainWindow()
{
//    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent* e)
{
    QMainWindow::keyPressEvent(e);
    switch(e->key())
    {
//    case Qt::Key_Down:
//    {
//        QKeyEvent k( QEvent::KeyPress,Qt::Key_Tab,Qt::NoModifier);
//        keyPressEvent(&k);
//        qDebug()<<"down pressed";
//        break;
//    }
    case Qt::Key_Escape:
        exit(0);
    }
}



///SLOTS:
void MainWindow::removeItem(QWidget*btn)
{
    qDebug()<<__func__<<btn;

    QAbstractButton* b = ((QAbstractButton*)btn);
    int idx = btnGrp->buttons().indexOf(b);
    lEntries.removeAt(idx);
    SaveListEntries(lEntries);

    ///Restart app
    QApplication* app = (QApplication*)this->parent();
    QProcess::startDetached(app->arguments()[0]);
    app->exit(0);
}

void MainWindow::editItem(QWidget*btn)
{
    qDebug()<<__func__<<btn;
}

void MainWindow::shutdown()
{
    qDebug()<<__func__;
    QProcess p;
    p.startDetached(SHUTDOWN_CMD);
    exit(0);
}

void MainWindow::sleep()
{
    qDebug()<<__func__;
    QProcess p;
    p.startDetached(SUSPEND_CMD);
    exit(0);
}

void MainWindow::wificonnect()
{
    qDebug()<<__func__;
    QProcess p;
    p.startDetached("");
//    exit(0);
}

