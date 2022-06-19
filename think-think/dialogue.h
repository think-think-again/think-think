#ifndef DIALOGUE_H
#define DIALOGUE_H

#include <QWidget>

class MyWindow;
class Dialogue : public QWidget
{
    Q_OBJECT
public:
    explicit Dialogue(MyWindow *parent);

signals:

private:
    MyWindow *window;

};

#endif // DIALOGUE_H
