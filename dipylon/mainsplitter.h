#ifndef MAINSPLITTER_H
#define MAINSPLITTER_H

#include <QSplitter>
#include <QObject>

class MainSplitter : public QSplitter
{
    Q_OBJECT

public:
    MainSplitter(QWidget *parent = 0);
};

#endif
