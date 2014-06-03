#ifndef SOURCEEDITOR_H
#define SOURCEEDITOR_H

#include <QTextEdit>
#include "dipydoc/dipydoc.h"

class SourceEditor : public QTextEdit
{
    Q_OBJECT

public:
    SourceEditor(DipyDoc*);

private:
    // DipyDoc object linked to the editor :
    DipyDoc* current_dipydoc;
};

#endif
