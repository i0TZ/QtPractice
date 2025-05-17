#include "dialogkeyboard.h"
#include "ui_dialogkeyboard.h"

#include <QTimer>

DialogKeyboard::DialogKeyboard(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogKeyboard)
{
    ui->setupUi(this);
    this->setWindowTitle("Keyboard");
    QTimer *cursorTimer = new QTimer(this);
    connect(cursorTimer, &QTimer::timeout, this, &DialogKeyboard::onCursorFlash);
    cursorTimer->start(500);

    QFont font;
    font.setPixelSize(20);
    for (QPushButton *btn : this->findChildren<QPushButton *>()) {
        btn->setFont(font);
        connect(btn, &QPushButton::clicked, this, &DialogKeyboard::onBtnClicked);
    }
    setTypeNum(false);
}

DialogKeyboard::~DialogKeyboard()
{
    delete ui;
}

void DialogKeyboard::setTypeNum(bool isNum)
{
    ui->btnNum_lock->setChecked(isNum);
    ui->keyboardNum->setVisible(isNum);
    ui->stackedWidget->setVisible(!isNum);
    this->resize(isNum ? QSize(400, 375) : QSize(1050, 375));
}

void DialogKeyboard::setTextValue(const QString &text)
{
    ui->label->setText(text);
}

QString DialogKeyboard::textValue()
{
    return ui->label->text();
}

QString DialogKeyboard::getText(const QString &text, bool *ok)
{
    DialogKeyboard keyboard;
    keyboard.setTypeNum(false);
    keyboard.setTextValue(text);
    const int ret = keyboard.exec();
    if (ok) {
        *ok = !!ret;
    }
    if (ret) {
        return keyboard.textValue();
    }
    return QString();
}

float DialogKeyboard::getNumber(const QString &text, bool *ok)
{
    DialogKeyboard keyboard;
    keyboard.setTypeNum(true);
    keyboard.setTextValue(text);
    const int ret = keyboard.exec();
    if (ok) {
        *ok = !!ret;
    }
    if (ret) {
        return keyboard.textValue().toFloat();
    }
    return 0;
}

void DialogKeyboard::onBtnClicked()
{
    QPushButton *btn = static_cast<QPushButton *>(sender());
    QString str = ui->label->text();
    QString tip = btn->toolTip();
    if (tip.isEmpty()) {
        ui->label->setText(str + btn->text());
    } else if (tip == "Backspace") {
        str.removeLast();
        ui->label->setText(str);
    } else if (tip == "Shift") {
        onUpperCase(ui->btn_shift_left->isVisible());
    } else if (tip == "Caps") {
        onUpperCase(ui->btn_caps->isVisible());
    } else if (tip == "Enter") {
        accept();
    } else if (tip == "Space") {
        ui->label->setText(str + " ");
    } else if (tip == "Clear") {
        ui->label->setText(QString());
    } else if (tip == "Num") {
        setTypeNum(ui->stackedWidget->isVisible());
    } else if (tip == "Esc") {
        this->reject();
    }
}

void DialogKeyboard::onCursorFlash()
{
    static bool black = false;
    QPalette palette = ui->label_Cursor->palette();
    palette.setColor(QPalette::WindowText, black ? Qt::darkGray : Qt::white);
    ui->label_Cursor->setPalette(palette);
    black = !black;
}

void DialogKeyboard::onUpperCase(bool upper)
{
    if (upper) {
        ui->stackedWidget->setCurrentWidget(ui->keyboardUpper);
        ui->btn_ShiftLeft->setChecked(true);
        ui->btn_ShiftRight->setChecked(true);
        ui->btn_Caps->setChecked(true);
    } else {
        ui->stackedWidget->setCurrentWidget(ui->keyboardLower);
        ui->btn_ShiftLeft->setChecked(false);
        ui->btn_ShiftRight->setChecked(false);
        ui->btn_Caps->setChecked(false);
    }
}
