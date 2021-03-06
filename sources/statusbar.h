#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <QLabel>
#include <QStatusBar>
#include "macros.h"

AS_NAMESPACE_START

class StatusBar : public QStatusBar
{
    Q_OBJECT
private:
    AS_CONNECTIONS_LIST
    QLabel *_message;
private slots:
    void onMessageChanged(const QString &text);
public:
    explicit StatusBar(QWidget *parent);
    ~StatusBar();
};

class StatusBarSeparator : public QFrame
{
public:
    explicit StatusBarSeparator(QWidget *parent = 0);
};

AS_NAMESPACE_END

#endif // STATUSBAR_H
