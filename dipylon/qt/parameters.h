#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <QList>
#include <QString>

struct {

  /*
    editors_size_in_main_splitter = sourceeditor / commentaryeditor size.
  */
  const QList<int> editors_size_in_main_splitter = {{500,100}};

  const QString commentary_editor_stylesheet = "color: white;"
                                               "background-color: #DE8ABC;"
                                               "selection-color: yellow;"
                                               "selection-background-color: blue;";

  const QString source_editor_stylesheet = "color: white;"
                                           "background-color: #9ABCDE;"
                                           "selection-color: yellow;"
                                           "selection-background-color: blue;";
} ui_parameters;

#endif
