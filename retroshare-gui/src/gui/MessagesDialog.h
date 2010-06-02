/****************************************************************
 *  RetroShare is distributed under the following license:
 *
 *  Copyright (C) 2006, crypton
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation; either version 2
 *  of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, 
 *  Boston, MA  02110-1301, USA.
 ****************************************************************/

#ifndef _MESSAGESDIALOG_H
#define _MESSAGESDIALOG_H

#include <list>
#include <QFileDialog>
#include <QModelIndex>
#include <QSortFilterProxyModel>

#include <QVariant>

#include "rsiface/rsmsgs.h"
#include "mainpage.h"
#include "ui_MessagesDialog.h"

#include "settings/NewTag.h"

class RSettings;

// Thunder: need a static msgId
//#define STATIC_MSGID

class MessagesDialog : public MainPage 
{
  Q_OBJECT

public:
  /** Default Constructor */
  MessagesDialog(QWidget *parent = 0);
  /** Default Destructor */
  ~MessagesDialog();

#ifdef STATIC_MSGID
  static void initStandardTagItems(std::map<int, TagItem> &Items);
  void getTagItems(std::map<int, TagItem> &Items);
  void setTagItems(std::map<int, TagItem> &Items);
#endif

// replaced by shortcut
//  virtual void keyPressEvent(QKeyEvent *) ;
 void updateMessageSummaryList();

public slots:
  void insertMessages();

  
private slots:

  /** Create the context popup menu and it's submenus */
  void messageslistWidgetCostumPopupMenu( QPoint point ); 
  void msgfilelistWidgetCostumPopupMenu(QPoint);  

  void changeBox( int newrow );
#ifdef STATIC_MSGID
  void changeTag( int newrow );
#endif
  void updateCurrentMessage();
  void currentChanged(const QModelIndex&);
  void clicked(const QModelIndex&);
  void doubleClicked(const QModelIndex &);

  void newmessage();

  void replytomessage();
  void replyallmessage();
  void forwardmessage();

  void print();
  void printpreview();
  
  bool fileSave();
  bool fileSaveAs();
  
  void removemessage();
  void undeletemessage();

#ifdef STATIC_MSGID
  void markAsRead();
  void markAsUnread();
#endif

  void anchorClicked (const QUrl &);
  
  void getcurrentrecommended();
//  void getallrecommended();

  /* handle splitter */
  void togglefileview();
  
  void buttonstextbesideicon();
  void buttonsicononly();
  void buttonstextundericon();
  
  void loadToolButtonsettings();
  
  void filterRegExpChanged();
  void filterColumnChanged();
  
  void clearFilter();
#ifdef STATIC_MSGID
  void tagTriggered(QAction *pAction);
  void tagAboutToShow();
#endif

private:
  class QStandardItemModel *MessagesModel;
  QSortFilterProxyModel *proxyModel;

  void insertMsgTxtAndFiles(QModelIndex index = QModelIndex(), bool bSetToRead = true);

  bool getCurrentMsg(std::string &cid, std::string &mid);
  void setMsgAsReadUnread(const QList<int> &Rows, bool bRead);

  void setCurrentFileName(const QString &fileName);

  int getSelectedMsgCount (QList<int> *pRows, QList<int> *pRowsRead, QList<int> *pRowsUnread);
  bool isMessageRead(int nRow);

  /* internal handle splitter */
  void togglefileview_internal();

  void processSettings(bool bLoad);

  void setToolbarButtonStyle(Qt::ToolButtonStyle style);
#ifdef STATIC_MSGID
  void fillTags();
#endif
  bool m_bProcessSettings;
  bool m_bInChange;

  enum { LIST_NOTHING,
         LIST_BOX,
#ifdef STATIC_MSGID
         LIST_TAG
#endif
     } m_eListMode;

  std::string mCurrCertId;
  std::string mCurrMsgId;

  QString fileName;
  QFont mFont;
  RSettings *m_pConfig;

  // timer and index for showing message
  QTimer *timer;
  QModelIndex timerIndex;

  /** Qt Designer generated object */
  Ui::MessagesDialog ui;
};

#endif

