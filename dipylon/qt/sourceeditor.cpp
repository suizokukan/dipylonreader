#include "qt/sourceeditor.h"

SourceEditor::SourceEditor(DipyDoc* dipydoc) : current_dipydoc(dipydoc) {
  this->setReadOnly(true);

  this->setStyleSheet(ui_parameters.source_editor_stylesheet);
}
