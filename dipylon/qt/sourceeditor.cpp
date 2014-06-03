#include "qt/sourceeditor.h"

SourceEditor::SourceEditor(DipyDoc* dipydoc) : current_dipydoc(dipydoc) {
  this->setReadOnly(true);

  this->setStyleSheet("color: white;"
                      "background-color: #9ABCDE;"
                      "selection-color: yellow;"
                      "selection-background-color: blue;");
}
