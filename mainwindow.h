#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QFile> // Working with files
#include <QFileDialog> // File dialogs
#include <QTextStream> // Reading text from files
#include <QMessageBox> // Open message box (errors)
#include <QPrinter> // Printer functions
#include <QPrintDialog> // Printer dialog
#include <QFileSystemModel> // Directory navigation
#include <QTreeView> // File view
#include <QSplitter> // Drag resizeable split
#include <QSyntaxHighlighter> // Syntax highlighting for text edit

QT_BEGIN_NAMESPACE
    namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr); // Window constructor
        void setup_directories();
        void open_file_from_tree(QString filepath);
        ~MainWindow(); // Destroy window

private slots:
        void on_actionNew_triggered();

        void on_actionOpen_triggered();

        void on_actionSave_As_triggered();

        void on_actionExit_triggered();

        void on_actionCopy_triggered();

        void on_actionPaste_triggered();

        void on_actionCut_triggered();

        void on_actionUndo_triggered();

        void on_actionRedo_triggered();

        void on_treeView_expanded();

        void on_treeView_doubleClicked(const QModelIndex &index);

private:
        Ui::MainWindow *ui;
        QString current_file = "new.txt";
};
#endif // MAINWINDOW_H
