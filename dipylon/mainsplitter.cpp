#include <QtWidgets>

#include "mainsplitter.h"

MainSplitter::MainSplitter(QWidget *parent) : QSplitter(parent)
{
  // vertical splitter :
  this->setOrientation(Qt::Vertical);
}
