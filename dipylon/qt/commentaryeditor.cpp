#include "qt/commentaryeditor.h"
#include "qt/parameters.h"

CommentaryEditor::CommentaryEditor(void) {
  this->setReadOnly(true);

  this->setStyleSheet(ui_parameters.commentary_editor_stylesheet);
}
