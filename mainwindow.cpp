#include <QDebug>
#include <QString>
#include <QFileDialog>
#include <QTextStream>
#include <QFile>
#include <QMessageBox>

//#include<QTableWidget>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Création d'un Menu

    // Réccupération du pointeur sur TabWiidgget
    tabwidget= ui->tabWidget;

    //tabwidget->addTab(new QWidget, "tab0");
    //tabwidget->setMovable(true);
    //tabwidget->setTabsClosable(true);

    connect(ui->actionOuvrir, SIGNAL(triggered(bool)), this, SLOT(openFile()));
    connect(ui->actionSauvegarde, SIGNAL(triggered(bool)), this, SLOT(saveFile()));
    connect(tabwidget, SIGNAL(tabCloseRequested(int)), this, SLOT(closeFile(int )));

    //connect(tabwidget, SIGNAL(tabCloseRequested(int)), this, SLOT(closeFile(int )));
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
void MainWindow::createTab(QString f)
{
    tabwidget->addTab(new QWidget, f);
    tabwidget->setMovable(true);
    tabwidget->setTabsClosable(true);
}
*/
void MainWindow::openFile()
{
    QString fichier= QFileDialog::getOpenFileName(this, "Ouverture d'un fichier", QDir::currentPath(),
                            "All files (*.*) ;; Source C/C++ (*.c *.h *.cpp *.hpp);; PNG files (*.png)");

    if( !fichier.isNull() )
    {
        QFile desc(fichier);

        if(!desc.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QMessageBox::warning(this,"Attention!","L'ouverture du fichier à échoué, erreur: " + desc.errorString());
        }
        else
        {

            // Lecture du fichier
            QTextStream in(&desc);
            QString  texte= in.readAll();

            // Création du conteneur
            plaintextedit= new QPlainTextEdit();
            plaintextedit->setPlainText(texte);

            // Création de l'onglet contenant le container texte
            tabwidget->addTab(plaintextedit, fichier);

            tabwidget->setMovable(true);
            tabwidget->setTabsClosable(true);
        }

        //plaintextedit->
    }

}

void MainWindow::closeFile(int indexfenetre)
{
    //qDebug()<< "Fenetre: " << indexfenetre;
    tabwidget->removeTab(indexfenetre);
}

void MainWindow::saveFile()
{
    qDebug()<<"Sauvegarde: " << tabwidget->currentIndex();

    plaintextedit= ui->plainTextEdit;

    qDebug() << plaintextedit->toPlainText();


    //QFileDialog::getSaveFileName(this)
}

void MainWindow::textChanged()
{
    QString titre= tabwidget->tabText(tabwidget->currentIndex());
    qDebug() << "textChanged " <<  titre;
}

