/*
 *
 * This file is part of the Notepadqq text editor.
 *
 * Copyright(c) 2010 Notepadqq team.
 * http://notepadqq.sourceforge.net/
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Qsci/qsciscintilla.h>
#include "qtabwidgetscontainer.h"
#include <QSettings>
#include <QLabel>
#include <QSplitter>
#include <QtNetwork/QLocalServer>
#include <QActionGroup>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QTabWidgetsContainer *container;

    /**
     * Describes the result of a save process. For example, if the user cancels the save dialog, \p saveFileResult_Canceled is returned.
     */
    enum saveFileResult {
         saveFileResult_Saved       /** The file was saved  */
        ,saveFileResult_Canceled    /** The save process was canceled */
    };

    /**
     * Describes the result of a tab closing process.
     */
    enum tabCloseResult {
         tabCloseResult_Saved        /** The tab was closed and the file was saved */
        ,tabCloseResult_NotSaved     /** The tab was closed and the file wasn't saved */
        ,tabCloseResult_AlreadySaved /** The tab was closed and the file was already saved */
        ,tabCloseResult_Canceled     /** The close process was canceled */
    };

    /**
     * Reasons for asking to save changes
     */
    enum askToSaveChangesReason {
         askToSaveChangesReason_tabClosing  /** The tab is closing */
        ,askToSaveChangesReason_generic     /** Generic reason */
    };

    int askIfWantToSave(QsciScintillaqq *sci, int reason);
    int save(QsciScintillaqq *sci);
    int writeDocument(QsciScintillaqq *sci, QString filename, bool updateFileName);
    QString getSaveDialogDefaultFileName(QsciScintillaqq *sci);
    int saveAs(QsciScintillaqq *sci);
    void openDocuments(QStringList fileNames, QTabWidgetqq *tabWidget);
    int kindlyTabClose(QsciScintillaqq *sci);

private:
    Ui::MainWindow *ui;
    QSettings * settings;
    QMenu * tabContextMenu;
    QList<QAction *> tabContextMenuActions;
    QLabel * statusBar_fileFormat;
    QLabel * statusBar_lengthInfo;
    QLabel * statusBar_selectionInfo;
    QLabel * statusBar_EOLstyle;
    QLabel * statusBar_textFormat;
    QLabel * statusBar_overtypeNotify;
    QLocalServer * instanceServer;
    //void closeEvent(QCloseEvent *event);
    // QActionGroup *encodeGroup;
    void closeEvent(QCloseEvent *event);

private slots:
    void on_action_New_triggered();
    void on_text_changed();
    int on_tab_close_requested(int index);
    void on_actionSave_as_triggered();
    void on_actionSave_triggered();
    void on_action_Open_triggered();
    void on_action_Undo_triggered();
    void on_action_Redo_triggered();
    void on_actionCu_t_triggered();
    void on_action_Copy_triggered();
    void on_action_Paste_triggered();
    void on_actionSelect_All_triggered();
    void on_action_Delete_triggered();
    void on_actionClose_triggered();
    void on_actionC_lose_All_triggered();
    void on_actionZoom_In_triggered();
    void on_actionZoom_Out_triggered();
    void on_actionRestore_Default_Zoom_triggered();
    void on_actionAbout_Notepadqq_triggered();
    void on_actionAbout_Qt_triggered();
    void on_actionLaunch_in_Firefox_triggered();
    void on_actionGet_php_help_triggered();
    void on_actionLaunch_in_Chromium_triggered();
    void on_actionGoogle_Search_triggered();
    void on_actionWikipedia_Search_triggered();
    void on_tabWidget_customContextMenuRequested(QPoint pos);
};

#endif // MAINWINDOW_H;
