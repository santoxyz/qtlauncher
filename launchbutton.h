#ifndef LAUNCHBUTTON_H
#define LAUNCHBUTTON_H
#include <QPushButton>
#include <QProcess>
#include <QDebug>
#include <QStyleOptionViewItem>
#include <QStyledItemDelegate>
#include <QStylePainter>
#include <QKeyEvent>
#include <QMenu>

class launchButton : public QPushButton
{
    Q_OBJECT
private:
    QString cmdName;

public:
    explicit launchButton(QWidget *parent = 0);
    launchButton(QIcon ico):
    QPushButton(ico,NULL)
    {
//        setStyleSheet("border-style: outset; border-width: 0px;");

        QPalette* palette3 = new QPalette();
        palette3->setColor(QPalette::Button,Qt::transparent);


        setPalette(*palette3);

    }

    void launch(){
        QProcess p;
        p.startDetached(cmdName);
    }
    void setCmdName(QString cmd){cmdName = cmd;}
    QString getCmdName(){ return cmdName;}

    void focusInEvent ( QFocusEvent * e )
    {
       // QPushButton::focusInEvent(e);
  //      qDebug()<<(QPushButton*)this<<__func__;
        setPalette( QPalette( Qt::darkGray ) );
        setAutoFillBackground(true);
        setAutoDefault(true);
        update();

    }
    void focusOutEvent ( QFocusEvent * e )
    {
        //QPushButton::focusOutEvent(e);
//        qDebug()<<(QPushButton*)this<<__func__;
        setPalette( QPalette( Qt::black) );
        setAutoFillBackground(true);
        update();
    }


    void mousePressEvent(QMouseEvent* e)
    {
        QPushButton::mousePressEvent(e);
        switch(e->button())
        {
    //    case Qt::Key_Down:
    //    {
    //        QKeyEvent k( QEvent::KeyPress,Qt::Key_Tab,Qt::NoModifier);
    //        keyPressEvent(&k);
    //        qDebug()<<"down pressed";
    //        break;
    //    }
            case Qt::RightButton:
            {
                qDebug()<<"mouse dx on "<<this;
                QMenu *m = new QMenu;

                QAction* a = new QAction("Edit",this);
                connect(a,SIGNAL(triggered()),this,SLOT(menuActionEdit()));
                m->addAction(a);
                a = new QAction("Remove",this);
                connect(a,SIGNAL(triggered()),this,SLOT(menuActionRemove()));
                m->addAction(a);
                m->popup(this->pos()+e->pos());
                break;
            }
        }
    }

    void mouseReleaseEvent(QMouseEvent* e)
    {
        qDebug()<<__func__<<e;
        QPushButton::mouseReleaseEvent(e);
        switch(e->type())
        {
            case QEvent::MouseButtonRelease:
            {

                setPalette( QPalette( Qt::black) );
                setAutoFillBackground(true);
                update();

            break;
            }
        }
    }

protected:
    void paintEvent(QPaintEvent *e)
    {

        QStyleOptionButton option;
        option.initFrom(this);
        option.icon = icon();
        option.text = text();
        option.iconSize = iconSize();
        option.features = QStyleOptionButton::Flat;
        if (option.state & QStyle::State_HasFocus)
            option.state = option.state ^ QStyle::State_HasFocus;
        QStylePainter painter(this);
        style()->drawControl(QStyle::CE_PushButton,&option,&painter,this);
    }

signals:
    void remove(QWidget*);
    void edit(QWidget*);

public slots:
    void menuActionEdit()
    {
        qDebug()<<__func__;
        emit edit(this);

    }
    void menuActionRemove()
    {
        qDebug()<<__func__;
        emit remove(this);
    }

};
#endif // LAUNCHBUTTON_H







