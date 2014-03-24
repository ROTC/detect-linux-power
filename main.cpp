#include <QApplication>
#include <cstdlib>
#include <QMessageBox>
#include <QDialog>
#include <QDebug>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QThread>
#include <QPushButton>

using std::system;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    const int count = 3600;
    QString line;
    for(int j=0;j!=count;++j)
    {
        QThread::sleep(10);
        system("acpi -V > ~/power.txt");
        QFile file("/home/rotc/power.txt");
        if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
            return -1;
        QTextStream in(&file);
        //ifstream power("~/power.txt");
        for(int i=0;i!=3;++i)
             line = in.readLine();
        QString test = line.split(": ").last();
        if(test=="off-line")
        {
            QMessageBox msgBox;
            msgBox.setText("电源断电了!");
            msgBox.setInformativeText("你想继续监测电源吗？");
            QPushButton *yes = msgBox.addButton(QObject::tr("是/Yes"),QMessageBox::YesRole);
            QPushButton *no = msgBox.addButton(QObject::tr("否/No"),QMessageBox::NoRole);
            msgBox.setWindowFlags(Qt::WindowStaysOnTopHint);
            msgBox.setDefaultButton(yes);
            msgBox.exec();
            if(msgBox.clickedButton() == yes)
                continue;
            else
                return 0;
        }
    }
    return a.exec();
}
