#ifndef DIALOGKEYBOARD_H
#define DIALOGKEYBOARD_H

#include <QDialog>

namespace Ui {
class DialogKeyboard;
}

class DialogKeyboard : public QDialog
{
    Q_OBJECT

public:
    explicit DialogKeyboard(QWidget *parent = nullptr);
    ~DialogKeyboard();

    void setTypeNum(bool isNum);
    void setTextValue(const QString &text);
    QString textValue();
    static QString getText(const QString &text, bool *ok = nullptr);
    static float getNumber(const QString &text, bool *ok = nullptr);

private:
    Ui::DialogKeyboard *ui;

    void onBtnClicked(QPushButton *btn);
    void onCursorFlash();
    void onUpperCase(bool upper);

};

#endif // DIALOGKEYBOARD_H
