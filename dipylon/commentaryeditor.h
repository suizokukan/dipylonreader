#ifndef COMMENTARYEDITOR_H
#define COMMENTARYEDITOR_H

#include <QPlainTextEdit>
#include <QObject>

class CommentaryEditor : public QTextEdit
{
    Q_OBJECT

public:
    CommentaryEditor(QWidget *parent = 0);
};

#endif
