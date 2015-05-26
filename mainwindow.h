#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QAbstractButton>
#include <QList>
#include <entry.h>
#include <QKeyEvent>
#include <QLineEdit>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QList<entry> fakeListEntries();
    void SaveListEntries(QList<entry> lEntries);
    QList<entry> LoadListEntries();


public slots:
    void launch(QAbstractButton *btn);
    void speedlaunch();
    void removeItem(QWidget*);
    void editItem(QWidget*);
    void shutdown();
    void sleep();
    void wificonnect();

private:
//    Ui::MainWindow *ui;
    QLineEdit *quicklaunch;
    QButtonGroup* btnGrp;
    void keyPressEvent(QKeyEvent* e);
    QList<entry> lEntries;

};

#endif // MAINWINDOW_H








