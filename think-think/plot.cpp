#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget widget;

    QPushButton but12("进入战斗",&widget);
    but12.move(2800,1800);
    but12.setStyleSheet("QPushButton{font:50px;}");
    but12.resize(200,200);
    but12.setFlat(true);
    but12.hide();

    QPushButton but11(">>",&widget);
    but11.move(2800,1800);
    but11.setStyleSheet("QPushButton{font:50px;}");
    but11.resize(200,200);
    but11.setFlat(true);

    QPushButton but10(">>",&widget);
    but10.move(2800,1800);
    but10.setStyleSheet("QPushButton{font:50px;}");
    but10.resize(200,200);
    but10.setFlat(true);

    QPushButton but9(">>",&widget);
    but9.move(2800,1800);
    but9.setStyleSheet("QPushButton{font:50px;}");
    but9.resize(200,200);
    but9.setFlat(true);

    QPushButton but8(">>",&widget);
    but8.move(2800,1800);
    but8.setStyleSheet("QPushButton{font:50px;}");
    but8.resize(200,200);
    but8.setFlat(true);

    QPushButton but7(">>",&widget);
    but7.move(2800,1800);
    but7.setStyleSheet("QPushButton{font:50px;}");
    but7.resize(200,200);
    but7.setFlat(true);

    QPushButton but6(">>",&widget);
    but6.move(2800,1800);
    but6.setStyleSheet("QPushButton{font:50px;}");
    but6.resize(200,200);
    but6.setFlat(true);

    QPushButton but5(">>",&widget);
    but5.move(2800,1800);
    but5.setStyleSheet("QPushButton{font:50px;}");
    but5.resize(200,200);
    but5.setFlat(true);

    QPushButton but4(">>",&widget);
    but4.move(2800,1800);
    but4.setStyleSheet("QPushButton{font:50px;}");
    but4.resize(200,200);
    but4.setFlat(true);

    QPushButton but3(">>",&widget);
    but3.move(2800,1800);
    but3.setStyleSheet("QPushButton{font:50px;}");
    but3.resize(200,200);
    but3.setFlat(true);

    QPushButton but2(">>",&widget);
    but2.move(2800,1800);
    but2.setStyleSheet("QPushButton{font:50px;}");
    but2.resize(200,200);
    but2.setFlat(true);

    QPushButton but1(">>",&widget);
    but1.move(2800,1800);
    but1.setStyleSheet("QPushButton{font:50px;}");
    but1.resize(200,200);
    but1.setFlat(true);

    widget.show();
    QLabel lab0(&widget);
    lab0.setAlignment(Qt::AlignCenter);
    lab0.setGeometry(200,600,2700,500);
    lab0.setStyleSheet("QLabel{font:50px}");
    lab0.setText("北京大学大一的学生zwq，在经过了一个学期的努力之后，成功地为自己接下来的学习以及科研打下了一定的基础。\n如今，他来到了在大学的第二学期，不知道在这一学期他又会遇到什么样的挑战呢？");

    QLabel lab1(&widget);
    lab1.setAlignment(Qt::AlignCenter);
    lab1.setGeometry(200,600,2700,500);
    lab1.setStyleSheet("QLabel{font:50px}");
    lab1.setText("一个平平无奇的周四下午\nAI引论CV小班课上");

    QLabel lab2(&widget);
    lab2.setAlignment(Qt::AlignCenter);
    lab2.setGeometry(200,1500,2700,500);
    lab2.setStyleSheet("QLabel{font:50px}");
    lab2.setText("Ljy：今天我们就来讲一讲这个有关于CV的一些基本知识……");

    QLabel lab3(&widget);
    lab3.setAlignment(Qt::AlignCenter);
    lab3.setGeometry(200,1500,2700,500);
    lab3.setStyleSheet("QLabel{font:50px}");
    lab3.setText("Zwq：什么嘛，这个CV听起来不是很难嘛，不就是把这些东西这样搞一下，那样搞一下就完事儿了嘛。\n还是隔壁的NLP听着有意思，什么时候去他们那儿搞两个demo来玩玩。现在还是来写写昨天布置的程设作业吧。");

    QLabel lab4(&widget);
    lab4.setAlignment(Qt::AlignCenter);
    lab4.setGeometry(200,1500,2700,500);
    lab4.setStyleSheet("QLabel{font:50px}");
    lab4.setText("说着，zwq便打开了POJ");

    QLabel lab5(&widget);
    lab5.setAlignment(Qt::AlignCenter);
    lab5.setGeometry(200,1500,2700,500);
    lab5.setStyleSheet("QLabel{font:50px}");
    lab5.setText("Zwq：“全面的Mystring”，让我看看……欸？这个Mystring不就是string吗？\n它能实现的string不是都能实现？但好像直接继承有点不道德，算了，还是一个一个全部写出来吧。");

    QLabel lab6(&widget);
    lab6.setAlignment(Qt::AlignCenter);
    lab6.setGeometry(200,1500,2700,500);
    lab6.setStyleSheet("QLabel{font:50px}");
    lab6.setText("Ljy：有人想回答一下这个问题吗？……");

    QLabel lab7(&widget);
    lab7.setAlignment(Qt::AlignCenter);
    lab7.setGeometry(200,1500,2700,500);
    lab7.setStyleSheet("QLabel{font:50px}");
    lab7.setText("Ljy：那我要不随便抽一个幸运儿？正好当一次考勤了。");

    QLabel lab8(&widget);
    lab8.setAlignment(Qt::AlignCenter);
    lab8.setGeometry(200,1500,2700,500);
    lab8.setStyleSheet("QLabel{font:50px}");
    lab8.setText("Zwq：这里要重载一个加号，这里要重载一个等于号，这里……");

    QLabel lab9(&widget);
    lab9.setAlignment(Qt::AlignCenter);
    lab9.setGeometry(200,1500,2700,500);
    lab9.setStyleSheet("QLabel{font:50px}");
    lab9.setText("Ljy：呦，这个名字不错。Zwq！Zwq来了吗？");

    QLabel lab10(&widget);
    lab10.setAlignment(Qt::AlignCenter);
    lab10.setGeometry(200,1500,2700,500);
    lab10.setStyleSheet("QLabel{font:50px}");
    lab10.setText("Zwq：啊？我运气这么好？");

    QObject::connect(&but1,&QPushButton::clicked,&lab0,&QLabel::show);
    QObject::connect(&but1,&QPushButton::clicked,&but1,&QPushButton::hide);

    QObject::connect(&but2,&QPushButton::clicked,&lab0,&QLabel::hide);
    QObject::connect(&but2,&QPushButton::clicked,&lab1,&QLabel::show);
    QObject::connect(&but2,&QPushButton::clicked,&but2,&QPushButton::hide);

    QObject::connect(&but3,&QPushButton::clicked,&lab1,&QLabel::hide);
    QObject::connect(&but3,&QPushButton::clicked,&lab2,&QLabel::show);
    QObject::connect(&but3,&QPushButton::clicked,&but3,&QPushButton::hide);

    QObject::connect(&but4,&QPushButton::clicked,&lab2,&QLabel::hide);
    QObject::connect(&but4,&QPushButton::clicked,&lab3,&QLabel::show);
    QObject::connect(&but4,&QPushButton::clicked,&but4,&QPushButton::hide);

    QObject::connect(&but5,&QPushButton::clicked,&lab3,&QLabel::hide);
    QObject::connect(&but5,&QPushButton::clicked,&lab4,&QLabel::show);
    QObject::connect(&but5,&QPushButton::clicked,&but5,&QPushButton::hide);

    QObject::connect(&but6,&QPushButton::clicked,&lab4,&QLabel::hide);
    QObject::connect(&but6,&QPushButton::clicked,&lab5,&QLabel::show);
    QObject::connect(&but6,&QPushButton::clicked,&but6,&QPushButton::hide);

    QObject::connect(&but7,&QPushButton::clicked,&lab5,&QLabel::hide);
    QObject::connect(&but7,&QPushButton::clicked,&lab6,&QLabel::show);
    QObject::connect(&but7,&QPushButton::clicked,&but7,&QPushButton::hide);

    QObject::connect(&but8,&QPushButton::clicked,&lab6,&QLabel::hide);
    QObject::connect(&but8,&QPushButton::clicked,&lab7,&QLabel::show);
    QObject::connect(&but8,&QPushButton::clicked,&but8,&QPushButton::hide);

    QObject::connect(&but9,&QPushButton::clicked,&lab7,&QLabel::hide);
    QObject::connect(&but9,&QPushButton::clicked,&lab8,&QLabel::show);
    QObject::connect(&but9,&QPushButton::clicked,&but9,&QPushButton::hide);

    QObject::connect(&but10,&QPushButton::clicked,&lab8,&QLabel::hide);
    QObject::connect(&but10,&QPushButton::clicked,&lab9,&QLabel::show);
    QObject::connect(&but10,&QPushButton::clicked,&but10,&QPushButton::hide);

    QObject::connect(&but11,&QPushButton::clicked,&lab9,&QLabel::hide);
    QObject::connect(&but11,&QPushButton::clicked,&lab10,&QLabel::show);
    QObject::connect(&but11,&QPushButton::clicked,&but11,&QPushButton::hide);
    QObject::connect(&but11,&QPushButton::clicked,&but12,&QPushButton::show);
    return a.exec();
}
