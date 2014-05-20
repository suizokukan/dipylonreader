#include <QtWidgets>

#include "sourceeditor.h"

void myfunc(void)
{
  qDebug() << "oh...";
}

SourceEditor::SourceEditor(QWidget *parent) : QTextEdit(parent)
{
}

void SourceEditor::mouseReleaseEvent(QMouseEvent* mouse_event)
{
    // mouse_event isn't used :
    Q_UNUSED(mouse_event);

    QTextCursor cursor = this->textCursor();

    if ( cursor.hasSelection() )
    {
        // some text has been selected :
        qDebug() << "position=" << cursor.position() << "texte sélectionné=" << cursor.selectedText();
    }
}
