#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    // Constructor for main window
    ui->setupUi(this);

    // Define the main widget on this window
    this->setCentralWidget(ui->splitter);

    setWindowTitle(current_file);

    // Setup folder structure
    setup_directories();

    // Split vertical layout
    ui->splitter->setStretchFactor(0,1);
    ui->splitter->setStretchFactor(1,1);
    ui->splitter->setSizes({2000, static_cast<int>(10000 / 1.618)});
}


MainWindow::~MainWindow() {
    // Destructor
    delete ui;
}


void MainWindow::on_actionNew_triggered() {
    current_file.clear(); // Clear old file name
    ui->textEdit->setText(QString()); // New file
}


void MainWindow::on_actionOpen_triggered() {
    // Create an open file dialog
    QString filename = QFileDialog::getOpenFileName(this, "Open");

    // Return if file name is not specified (the user clicked cancel)
    if(filename.isEmpty()){
        return;
    }

    QFile file(filename); // Opens the file
    current_file = filename; // Set the current filename to the new filename

    // Error handling if file cannot be opened
    if(!file.open(QIODevice::ReadOnly | QFile::Text)){
        QMessageBox::warning(this, "Warning", "Cannot open file : " + file.errorString());
        return;
    }

    // Set the title of the window
    // TODO change this to "Editor name - filename.txt"
    setWindowTitle(current_file);

    // Read the file contents
    QTextStream in(&file);
    QString text = in.readAll();

    // Insert the text from the file into the text edit area
    ui->textEdit->setText(text);
    file.close(); // Close the file stream
}


void MainWindow::on_actionSave_As_triggered() {
    QString filename = QFileDialog::getSaveFileName(this, "Save as");

    // Return if file name is not specified (the user clicked cancel)
    if(filename.isEmpty()){
        return;
    }

    QFile file(filename);

    // Error handling if file cannot be opened
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "Warning", "Cannot save file : " + file.errorString());
        return;
    }

    current_file = filename;
    setWindowTitle(current_file);

    // Open a file object
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText(); // Convert text within textEdit to plain

    // Write text to output (file)
    out << text;

    file.close();
}


void MainWindow::on_actionExit_triggered() {
    QApplication::quit();
}


void MainWindow::on_actionCopy_triggered() {
    ui->textEdit->copy();
}


void MainWindow::on_actionPaste_triggered() {
    ui->textEdit->paste();
}


void MainWindow::on_actionCut_triggered() {
    ui->textEdit->cut();
}


void MainWindow::on_actionUndo_triggered() {
    ui->textEdit->undo();
}


void MainWindow::on_actionRedo_triggered() {
    ui->textEdit->redo();
}


void MainWindow::on_treeView_expanded() {
    ui->treeView->resizeColumnToContents(0);
}


void MainWindow::setup_directories(){

    QFileSystemModel *model = new QFileSystemModel(this);
    //model->setRootPath(QDir::currentPath());
    model->setRootPath("/Users/hbates/");

    QTreeView *tree = ui->treeView;
    tree->setModel(model);
    tree->hideColumn(1); // Size
    tree->hideColumn(2); // Type
    tree->hideColumn(3); // Date modified
    tree->resizeColumnToContents(0);

    tree->setRootIndex(model->index("/Users/hbates"));
}


void MainWindow::on_treeView_doubleClicked(const QModelIndex &index) {
    QFileSystemModel *model = new QFileSystemModel(this);
    QString filepath = model->filePath(index);
    if(model->isDir(index)){
        return;
    }
    open_file_from_tree(filepath);
    delete model;
}

void MainWindow::open_file_from_tree(QString filepath) {
    // Return if file name is not specified (the user clicked cancel)
    if(filepath.isEmpty()){
        return;
    }

    QFile file(filepath); // Opens the file
    current_file = filepath; // Set the current filename to the new filename

    // Error handling if file cannot be opened
    if(!file.open(QIODevice::ReadOnly | QFile::Text)){
        QMessageBox::warning(this, "Warning", "Cannot open file : " + file.errorString());
        return;
    }

    // Set the title of the window
    // TODO change this to "Editor name - filename.txt"
    setWindowTitle(current_file);

    // Read the file contents
    QTextStream in(&file);
    QString text = in.readAll();

    // Insert the text from the file into the text edit area
    ui->textEdit->setText(text);
    file.close(); // Close the file stream
}
