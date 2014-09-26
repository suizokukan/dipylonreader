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

    ❏DipylonReader❏ : qt/downloaddemodipydocs.cpp

    see downloaddemodipydocs.h for the documentation

*******************************************************************************/

#include "qt/downloaddemodipydocs.h"

/*______________________________________________________________________________

  DownloadDemoDipydocs::DownloadDemoDipydocs

  Class constructor.

     (0) progress dialog
     (1) erase old files
     (2) download summary file
     (3) download & install data files
     (4) success message
________________________________________________________________________________*/
DownloadDemoDipydocs::DownloadDemoDipydocs(const UI& ui) {
  DebugMsg() << "DownloadDemoDipydocs::DownloadDemoDipydoc() : entry point";

  // setting this->summary_url :
  this->set_summary_url();

  if( ui.network_manager->networkAccessible() != QNetworkAccessManager::NetworkAccessibility::Accessible ) {
    // no network !
    DebugMsg() << "DownloadDemoDipydocs::DownloadDemoDipydoc() : No network available !";
    QMessageBox msgBox;
    msgBox.setText(QObject::tr("No network available ! You can't download if the network is down."));
    msgBox.exec();
    return;
  }

  /* ...........................................................................
     (0) progress dialog
   ...........................................................................*/
  QProgressDialog progress(QObject::tr("Download demo Dipydocs"),
                           QObject::tr("Abort installation"),
                           0, 1000);
  connect(&progress, SIGNAL(canceled()),
          this, SLOT(cancel()));
  progress.setWindowModality(Qt::WindowModal);

  /* ...........................................................................
     (1) erase old files
   ...........................................................................*/
  progress.setLabelText(QObject::tr("removing old files..."));
  progress.setValue(1);

  QDir path = QDir( ui.path_to_dipydocs,
                    fixedparameters::DEMODIPYDOCS__REGEX_FOR_DIRECTORIES_NAME,
                    QDir::Name,
                    QDir::Dirs );
  bool ok = true;

  for( QString &directory : path.entryList() ) {
    if( (directory != ".") && (directory != "..") ) {
      QString directory_with_full_path = path.absolutePath() + "/" + directory;
      DebugMsg() << "(MainWindow::download_dipydocs_demo) erasing recursively" << directory_with_full_path;

      QDir path_to_be_erased(directory_with_full_path);
      ok &= path_to_be_erased.removeRecursively();

      if(ok == false) {
        // error : the function can't erase old demo dipydocs.
        QMessageBox msgBox;
        msgBox.setText(QObject::tr("The program can't erase the old demonstration Dipydoc's. See details below."));
        msgBox.setDetailedText(QString("Can't access the following directory : %1").arg(directory_with_full_path));
        msgBox.exec();
        break;
      }
    }
  }

  if(ok == false) {
    return;
  }

  /* ...........................................................................
     (2) download summary file,
     initialize this->filenames_and_sizes and this->number_of_bytes_to_be_downloaded
  ............................................................................*/
  progress.setLabelText(QObject::tr("contacting the download site..."));
  progress.setValue(2);

  QObject::connect(ui.network_manager, &QNetworkAccessManager::finished,
                   this,               &DownloadDemoDipydocs::download_summary_finished);

  ui.network_manager->get(QNetworkRequest(this->summary_url));

  this->still_waiting = true;
  while( (this->still_waiting==true) && (this->cancel_tasks==false) ) {
    QApplication::processEvents();
  }

  QObject::disconnect(ui.network_manager, &QNetworkAccessManager::finished,
                      this,               &DownloadDemoDipydocs::download_summary_finished);

  if( this->cancel_tasks == true ) {
    return;
  }

  /* ...........................................................................
     (3) download & install data files
  ............................................................................*/
  // update the progress bar : new maximum value.
  progress.setMaximum(this->number_of_bytes_to_be_downloaded);

  QObject::connect(ui.network_manager, &QNetworkAccessManager::finished,
                   this,               &DownloadDemoDipydocs::download_data_finished);

  for(auto &filename_and_size : this->filenames_and_sizes) {

    // we fill this->current_datafile_to_be_downloaded__* so that the
    // DownloadDemoDipydocs::download_data_finished slot will know
    // which file to write.
    this->current_datafile_to_be_downloaded__disk = this->get_data_filename_fullpath(filename_and_size.first);
    this->current_datafile_to_be_downloaded__url = this->get_data_url(filename_and_size.first);

    ui.network_manager->get(QNetworkRequest(this->current_datafile_to_be_downloaded__url));

    this->still_waiting = true;
    while( (this->still_waiting==true) && (this->cancel_tasks==false) ) {
      QApplication::processEvents();
    }

    if(this->cancel_tasks == true) {
      break;
    } else {
      // update the progress bar :
      progress.setValue( progress.value() + filename_and_size.second );
      // let's add this new title to this->downloaded_titles :
      QString dirname = QFileInfo(filename_and_size.first).dir().path();
      if(this->downloaded_titles.contains(dirname) == false) {
        this->downloaded_titles.append(dirname);
      }
    }
  }

  QObject::disconnect(ui.network_manager, &QNetworkAccessManager::finished,
                      this,               &DownloadDemoDipydocs::download_data_finished);


  /* ...........................................................................
     (4) success message
  ............................................................................*/
  QMessageBox msgBox;
  msgBox.setText(QString(tr("Demonstration Dipydocs have been successfully downloaded.")));
  msgBox.setDetailedText(this->downloaded_titles.join("\n"));
  msgBox.exec();

  DebugMsg() << "DownloadDemoDipydocs::DownloadDemoDipydoc() : exit point";
}

/*______________________________________________________________________________

  DownloadDemoDipydocs::cancel()

  Function called when the user stops the process.
______________________________________________________________________________*/
void DownloadDemoDipydocs::cancel(void) {
  this->cancel_tasks = true;
}

/*______________________________________________________________________________

  DownloadDemoDipydocs::download_data_finished

  Write on disk the data file named this->current_datafile_to_be_downloaded__disk.

  Function called when downloading the data file is over.
______________________________________________________________________________*/
void DownloadDemoDipydocs::download_data_finished(QNetworkReply* reply) {
  // an error occurs :
  if(reply->error()) {
    QMessageBox msgBox;
    msgBox.setText(QString(tr("The source site could not be reached : is the network ok ? Check out details below.")));
    msgBox.setDetailedText( QString("Trying to reach %1.\n\n"
                                    "System error=\n%2").arg(this->current_datafile_to_be_downloaded__url.toString(),
                                                             reply->errorString()));
    msgBox.exec();

    this->cancel();
  }
  // let's write on disk the new file name this->current_datafile_to_be_downloaded__disk :
  else {
    // if the directory where this->current_datafile_to_be_downloaded__disk
    // should be stored doesn't exist, we create it :
    QDir new_d = QFileInfo(this->current_datafile_to_be_downloaded__disk).dir();

    if( new_d.exists() == false ) {
      DebugMsg() << "DownloadDemoDipydocs::download_data_finished : creating " << new_d.absolutePath();

      if(new_d.mkpath(new_d.absolutePath()) == false) {
        QMessageBox msgBox;
        msgBox.setText(QObject::tr("The program can't write the new demonstration Dipydoc's on disk. See details below."));
        msgBox.setDetailedText(QString("Can't create the following directory : %1").arg(new_d.absolutePath()));
        msgBox.exec();
        this->cancel();
      }
    }

    // writing the file :
    QFile* file = new QFile(this->current_datafile_to_be_downloaded__disk);
    if (!file->open(QIODevice::WriteOnly)) {
        QMessageBox msgBox;
        msgBox.setText(QObject::tr("The program can't write the new demonstration Dipydoc's on disk. See details below."));
        msgBox.setDetailedText(QString("Can't fill the "
                                       "following file : %1").arg(this->current_datafile_to_be_downloaded__disk));
        msgBox.exec();
        this->cancel();
    }
    file->write(reply->readAll());
    delete file;
  }

  this->still_waiting = false;
  reply->deleteLater();
}

/*______________________________________________________________________________

  DownloadDemoDipydocs::download_summary_finished

  Download the summary file, read it and initialize this->filenames_and_sizes
  and this->number_of_bytes_to_be_downloaded.

  See the documentation for the summary file's format.

  Function called when downloading the summary file is over.
______________________________________________________________________________*/
void DownloadDemoDipydocs::download_summary_finished(QNetworkReply* reply) {
  // an error occurs :
  if(reply->error()) {
    DebugMsg() << "DownloadDemoDipydocs::download_summary_finished() : ERROR :" << reply->errorString();

    QMessageBox msgBox;
    msgBox.setText(QString(tr("The source site could not be reached : is the network ok ? Check out details below.")));
    msgBox.setDetailedText(QString("Trying to reach %1.\n\nSystem error=\n%2").arg(this->summary_url.toString(),
                                                                                   reply->errorString()));
    msgBox.exec();

    this->cancel();
  }
  // let's fill this->filenames_and_sizes and this->number_of_bytes_to_be_downloaded :
  else {
    this->filenames_and_sizes.clear();
    this->number_of_bytes_to_be_downloaded = 0;

    QStringList lines = QString(reply->readAll()).split("\n");
    for(auto &line : lines) {
      if( line.trimmed().size() != 0 ) {
        QStringList filename_and_size = line.split(fixedparameters::DEMODIPYDOCS__SUMMARY_SEP);
        if(filename_and_size.size() != 2) {
          QMessageBox msgBox;
          msgBox.setText(QObject::tr("Wrong . See details below."));
          msgBox.setDetailedText(QString("Ill-formed line in the summary "
                                         "file '%1' : '%2'").arg(this->summary_url.toString(),
                                                                 filename_and_size[0]));
          msgBox.exec();
          this->cancel();
          break;
        } else {
          this->filenames_and_sizes[filename_and_size[0]] = filename_and_size[1].toInt();
          this->number_of_bytes_to_be_downloaded += filename_and_size[1].toInt();
        }
      }
    }
  }

  this->still_waiting = false;
  reply->deleteLater();
}

/*______________________________________________________________________________

  DownloadDemoDipydocs::get_data_url()

  Return the url corresponding to a filename.

  E.g. transform "main.xml" into "94.23.197.37/dipylonreader/freedipydocs/0.4.2/ogg/main.xml"
______________________________________________________________________________*/
QUrl DownloadDemoDipydocs::get_data_url(const QString& filename) const {
 return QUrl( QString(fixedparameters::DEMODIPYDOCS__SOURCE_SITE).arg(QString(fixedparameters::application_version)) + \
              "/" + \
              filename );
}

/*______________________________________________________________________________

  DownloadDemoDipydocs::get_data_filename_fullpath

  Return the fullpath of the file 'filename'.

  E.g. transform "Ovide/main.xml" into "/home/suizokukan/dipydocs/Ovide/main.xml"
______________________________________________________________________________*/
QString DownloadDemoDipydocs::get_data_filename_fullpath(const QString& filename) const {
  return fixedparameters::default__path_to_dipydocs + "/" + filename;
}

/*______________________________________________________________________________

  DownloadDemoDipydocs::set_summary_url()

  Set this->summary_url, the URL of the expected summary file.
______________________________________________________________________________*/
void DownloadDemoDipydocs::set_summary_url(void) {
  QString str(QString(fixedparameters::DEMODIPYDOCS__SOURCE_SITE).arg(QString(fixedparameters::application_version)) + \
             "/" + \
              QString(fixedparameters::DEMODIPYDOCS__SUMMARY_FILENAME));
  this->summary_url.setUrl( str );
}
