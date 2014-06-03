#include "qt/commentaryeditor.h"

CommentaryEditor::CommentaryEditor(void) {
  this->setReadOnly(true);

  this->setStyleSheet("color: white;"
                      "background-color: #DE8ABC;"
                      "selection-color: yellow;"
                      "selection-background-color: blue;");
}
