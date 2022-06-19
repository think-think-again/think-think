#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QStackedLayout>
#include <QWidget>



class MyWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MyWindow(QWidget *parent = nullptr);
    QStackedLayout *layout;

signals:

public slots:
    void startDialog();
    void startBattle();

};

#endif // MYWINDOW_H
