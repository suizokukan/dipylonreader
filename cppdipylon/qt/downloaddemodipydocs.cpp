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

  Class' constructor.
________________________________________________________________________________*/
DownloadDemoDipydocs::DownloadDemoDipydocs(const UI& ui) {
  DebugMsg() << "DownloadDemoDipydocs::DownloadDemoDipydoc() : entry point";

  // setting this->summary_url :
  this->set_summary_url();

  if( ui.network_manager->networkAccessible() != QNetworkAccessManager::NetworkAccessibility::Accessible ) {
    // $$$ pas de réseau $$$
    DebugMsg() << "############ pas de réseau !!!!!";
    return;
  }

  QProgressDialog progress(QObject::tr("Download demo Dipydocs"),
                           QObject::tr("Abort Copy"),
                           0, 1000);
  connect(&progress, SIGNAL(canceled()),
          this, SLOT(cancel()));
  progress.setWindowModality(Qt::WindowModal);

  /* ...........................................................................
     erase old files :
   ...........................................................................*/
  progress.setLabelText(QObject::tr("removing old files..."));
  progress.setValue(1);

  QDir path = QDir( ui.path_to_dipydocs,
                    fixedparameters::DEMODIPYDOCS__REGEX_FOR_DIRECTORIES_NAME,
                    QDir::Name,
                    QDir::Dirs );

  for( QString &directory : path.entryList() ) {
    if( (directory != ".") && (directory != "..") ) {
      QString directory_with_full_path = path.absolutePath() + "/" + directory;
      DebugMsg() << "(MainWindow::download_dipydocs_demo) erasing recursively" << directory_with_full_path;
      // ok &= path.removeRecursively(directory_with_full_path);
      //if(ok == false) {
      //  // $$$ pas d'accès : problème de droit ???
      // }
    }
  }

  /* ...........................................................................
     download summary file :
   ...........................................................................*/
  progress.setLabelText(QObject::tr("contacting the download site..."));
  progress.setValue(2);

  QObject::connect(ui.network_manager, &QNetworkAccessManager::finished,
                   this,               &DownloadDemoDipydocs::download_summary__replyFinished);

  ui.network_manager->get(QNetworkRequest(this->summary_url));

  this->still_waiting = true;
  while( (this->still_waiting==true) && (this->cancel_tasks==false) ) {
    QApplication::processEvents();
  }

  DebugMsg() << "DownloadDemoDipydocs::DownloadDemoDipydoc() : exit point";
}

/*______________________________________________________________________________

  DownloadDemoDipydocs::download_summary__replyFinished

  Function called when downloading the summary file is over.
______________________________________________________________________________*/
void DownloadDemoDipydocs::download_summary__replyFinished(QNetworkReply* reply) {
  DebugMsg() << "DownloadDemoDipydocs::download_summary__replyFinished() : entry point";

  if(reply->error()) {
    DebugMsg() << "DownloadDemoDipydocs::download_summary__replyFinished() : ERROR :" << reply->errorString();

    QMessageBox msgBox;
    msgBox.setText(QString(tr("The source site could not be reached : is the network ok ? Check out details below.")));
    msgBox.setDetailedText( QString("Trying to reach %1.\n\nSystem error=\n%2").arg(this->summary_url.toString(),
                                                                                    reply->errorString()));
    msgBox.exec();
  }
  else {
    DebugMsg() << reply->header(QNetworkRequest::ContentTypeHeader).toString();
    DebugMsg() << reply->header(QNetworkRequest::LastModifiedHeader).toDateTime().toString();
    DebugMsg() << reply->header(QNetworkRequest::ContentLengthHeader).toULongLong();
    DebugMsg() << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    DebugMsg() << reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();
    DebugMsg() << QString(reply->readAll());
  }
  this->still_waiting = false;
  reply->deleteLater();

  DebugMsg() << "DownloadDemoDipydocs::download_summary__replyFinished() : exit point";
}

/*______________________________________________________________________________

  DownloadDemoDipydocs::cancel()

  Function called when the user stops the process.
______________________________________________________________________________*/
void DownloadDemoDipydocs::cancel(void) {
  this->cancel_tasks = true;
}

/*______________________________________________________________________________

  DownloadDemoDipydocs::set_summary_url()

  Set this->summary_url
______________________________________________________________________________*/
void DownloadDemoDipydocs::set_summary_url(void) {
  QString str(QString(fixedparameters::DEMODIPYDOCS__SOURCE_SITE) + \
              "/" + \
              QString(fixedparameters::application_version) + \
             "/" + \
              QString(fixedparameters::DEMODIPYDOCS__SUMMARY_FILENAME));
  this->summary_url.setUrl( str );

  DebugMsg() << "(DownloadDemoDipydocs::set_summary_url) this->summary_url=" << this->summary_url.toString();
}
