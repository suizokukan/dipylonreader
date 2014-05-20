#ifndef SOURCEEDITOR_H
#define SOURCEEDITOR_H

#include <QPlainTextEdit>
#include <QObject>

class SourceEditor : public QTextEdit
{
    Q_OBJECT

public:
    SourceEditor(QWidget *parent = 0);

protected:
    void mouseReleaseEvent(QMouseEvent*);
};

#endif
