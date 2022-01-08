#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    // Constructor for main window
    ui->setupUi(this);
    //this->setCentralWidget(ui->textEdit);
    QDate date_file = QDate::currentDate();
    current_file = date_file.toString("dd/MM/yyyy") + ".txt";
    setWindowTitle(current_file);
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

