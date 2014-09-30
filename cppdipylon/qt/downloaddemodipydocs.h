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

#include <QDir>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QProgressDialog>
#include <QString>
#include <QStringList>

#include <map>

#include "./fixedparameters.h"
#include "debugmsg/debugmsg.h"
#include "qt/ui.h"

class UI;

/*______________________________________________________________________________

  DownloadDemoDipydocs class
________________________________________________________________________________*/
class DownloadDemoDipydocs : public QObject {
    Q_OBJECT

 public:
                     explicit DownloadDemoDipydocs(const UI&);
                             ~DownloadDemoDipydocs(void);
       bool                   cancel_tasks = false;
       bool                   still_waiting = false;
       QUrl                   summary_url;

 private:
       const UI&              ui;

       QString                current_datafile_to_be_downloaded__disk;
       QUrl                   current_datafile_to_be_downloaded__url;
       QStringList            downloaded_titles;
       QFile*                 current_file = nullptr;
       QNetworkReply*         current_reply = nullptr;
       std::map<QString, int> filenames_and_sizes;
       int                    number_of_bytes_to_be_downloaded = 0;

       void                   create_path_to_the_file(const QString& filename);
       QString                get_data_filename_fullpath(const QString& filename) const;
       QUrl                   get_data_url(const QString& filename) const;
       void                   set_summary_url(void);

 signals:

 public slots:  // NOLINT(whitespace/indent)
       void                   cancel(void);
       void                   download_data_finished(QNetworkReply* reply);
       void                   download_summary_finished(QNetworkReply* reply);
       void                   readyRead(void);
};

#endif  // CPPDIPYLON_QT_DOWNLOADDEMODIPYDOCS_H_
