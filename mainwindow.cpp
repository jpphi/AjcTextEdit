#include <QDebug>
#include <QString>
#include <QFileDialog>
#include <QTextStream>
#include <QFile>
#include <QFileInfo>
#include <QMessageBox>

//#include<QTableWidget>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    lc=  ui->label->text();

    newFile();

    connect(ui->actionOuvrir, SIGNAL(triggered(bool)), this, SLOT(openFile()));
    connect(ui->actionSauvegarde, SIGNAL(triggered(bool)), this, SLOT(saveFile()));
    connect(ui->actionNouveau, SIGNAL(triggered(bool)), this, SLOT(newFile()));
    connect(tabwidget, SIGNAL(tabCloseRequested(int)), this, SLOT(closeFile(int )));
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
        QFileInfo descinfo(fichier);

        if(!desc.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QMessageBox::warning(this,"Attention!","L'ouverture du fichier à échoué, erreur: " + desc.errorString());
        }
        else
        {
            //repcourrant= descinfo.filePath();


            // Lecture du fichier
            QTextStream in(&desc);
            QString  texte= in.readAll();

            // Création du conteneur
            plaintextedit= new QPlainTextEdit();
            plaintextedit->setPlainText(texte);

            // Création de l'onglet contenant le container texte
            tabwidget->setCurrentIndex(tabwidget->addTab(plaintextedit,descinfo.fileName()));

            tabwidget->setTabToolTip(tabwidget->currentIndex(), descinfo.absoluteFilePath());


            tabwidget->setMovable(true);
            tabwidget->setTabsClosable(true);

            connect(plaintextedit, SIGNAL(textChanged()), this, SLOT(ContentChanged( )));

        }
    }


    //qDebug() << repcourrant << " " + QCoreApplication::applicationDirPath();

}

void MainWindow::closeFile(int indexfenetre)
{
    //qDebug()<< "Fenetre: " << indexfenetre;
    tabwidget->removeTab(indexfenetre);
}

void MainWindow::saveFile()
{
    // Suppression de '*' si elle existe
    QString titre= tabwidget->tabText(tabwidget->currentIndex());
    if(titre[0]== "*" )
    {
        tabwidget->setTabText(tabwidget->currentIndex(), titre.remove(0,1));
    }


    qDebug()<<"Sauvegarde: " << tabwidget->tabToolTip(tabwidget->currentIndex());

    //qDebug() << plaintextedit->toPlainText();


    //QFileDialog::getSaveFileName(this)
}

void MainWindow::ContentChanged()
{
    QString titre= tabwidget->tabText(tabwidget->currentIndex());

    //qDebug()<< "Changement de contenuee du fichier : " + titre;

    if(titre[0]!= "*" )
    {
        tabwidget->setTabText(tabwidget->currentIndex(), "*"+titre);
    }

}

void MainWindow::newFile()
{
    //qDebug() << "Signal Nouveau";
    //repcourrant= QCoreApplication::applicationFilePath();

    //qDebug() << repcourrant << " " + QCoreApplication::applicationDirPath();

    plaintextedit= new QPlainTextEdit();

    if(tabwidget== nullptr)
    {
        tabwidget= ui->tabWidget;
        tabwidget->removeTab(0); /// Permet de supprimer la tab provenant de l'ui
        //qDebug()<<"ICI..." << tabwidget->currentIndex();
    }

    tabwidget->setCurrentIndex(tabwidget->addTab(plaintextedit,"Nouveau"));

    tabwidget->setTabToolTip(tabwidget->currentIndex(),QCoreApplication::applicationFilePath()+"/Nouveau");

    tabwidget->setMovable(true);
    tabwidget->setTabsClosable(true);

    connect(plaintextedit, SIGNAL(textChanged()), this, SLOT(ContentChanged( )));
}
