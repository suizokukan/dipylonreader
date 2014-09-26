/*******************************************************************************

    DipylonReader Copyright (C) 2008 Xavier Faure
    Contact: faure dot epistulam dot mihi dot scripsisti at orange dot fr

    This file is part of DipylonReader.
    DipylonReader is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    DipylonReader is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with DipylonReader.  If not, see <http://www.gnu.org/licenses/>.

    ____________________________________________________________________________

    ❏DipylonReader❏ : qt/downloaddemodipydocs.h

    o DownloadDemoDipydocs class

      The DownloadDemoDipydocs class allows to remove the old demonstration
    Dipydocs and to download them.

*******************************************************************************/

#ifndef CPPDIPYLON_QT_DOWNLOADDEMODIPYDOCS_H_
#define CPPDIPYLON_QT_DOWNLOADDEMODIPYDOCS_H_

#include "fixedparameters.h"
#include "debugmsg/debugmsg.h"
#include "qt/ui.h"

#include <QProgressDialog>
#include <QDir>
#include <QString>
#include <QStringList>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

/*______________________________________________________________________________

  DownloadDemoDipydocs class
________________________________________________________________________________*/
class DownloadDemoDipydocs : public QObject {

    Q_OBJECT

public:
       DownloadDemoDipydocs(const UI&);
       bool cancel_tasks = false;
       bool still_waiting = false;
       QUrl summary_url;

private:
               std::map<QString, int> filenames_and_sizes;
       int     number_of_bytes_to_be_downloaded = 0;
       QUrl    current_datafile_to_be_downloaded__url;
       QString current_datafile_to_be_downloaded__disk;
       QStringList downloaded_titles;

  void set_summary_url(void);
  QUrl get_data_url(const QString& filename) const;
  QString get_data_filename_fullpath(const QString& filename) const;

 signals:
public slots:
  void cancel(void);
  void download_summary__replyFinished(QNetworkReply*);
  void download_data__replyFinished(QNetworkReply*);
};

#endif  // CPPDIPYLON_QT_DOWNLOADDEMODIPYDOCS_H_
