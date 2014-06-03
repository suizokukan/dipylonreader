#ifndef SOURCEEDITOR_H
#define SOURCEEDITOR_H

#include "qt/parameters.h"
#include "dipydoc/dipydoc.h"

#include <QTextEdit>

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
