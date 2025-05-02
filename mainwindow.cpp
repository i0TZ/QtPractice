#include "mainwindow.h"

#include <QPushButton>
#include <QVBoxLayout>
#include "keyboard/dialogkeyboard.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *widget = new QWidget(this);
    widget->setLayout(new QVBoxLayout());

    QPushButton *btnA = new QPushButton("Text", widget);
    connect(btnA, &QPushButton::clicked, this, [=](){
        bool ok;
        QString text = DialogKeyboard::getText(btnA->text(), &ok);
        if (ok) {
            btnA->setText(text);
        }
    });
    QPushButton *btnB = new QPushButton("Number", widget);
    connect(btnB, &QPushButton::clicked, this, [=](){
        bool ok;
        float num = DialogKeyboard::getNumber(QString(), &ok);
        if (ok) {
            btnB->setText(QString::number(num));
        }
    });

    widget->layout()->addWidget(btnA);
    widget->layout()->addWidget(btnB);

    this->setCentralWidget(widget);
}

MainWindow::~MainWindow() {}
