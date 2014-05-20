#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QPlainTextEdit>
#include <QObject>

class CodeEditor : public QTextEdit
{
    Q_OBJECT

public:
    CodeEditor(QWidget *parent = 0);
};

#endif
