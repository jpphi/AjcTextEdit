#include <QDebug>
#include <QString>
#include <QFileDialog>
#include <QTextStream>
#include <QFile>
#include <QFileInfo>
#include <QMessageBox>
#include <QList>

//#include<QTableWidget>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //lstdict= new QList<Dict *>;

    ui->setupUi(this);

    lc=  ui->label->text();

    newFile();

    connect(ui->actionOuvrir, SIGNAL(triggered(bool)), this, SLOT(openFile()));
    connect(ui->actionSauvegarde, SIGNAL(triggered(bool)), this, SLOT(saveFile()));
    connect(ui->actionNouveau, SIGNAL(triggered(bool)), this, SLOT(newFile()));
    connect(tabwidget, SIGNAL(tabCloseRequested(int)), this, SLOT(closeFile(int )));

    //qDebug() << "Retour MainWindows";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newFile()
{
    //qDebug() << "Signal Nouveau";
    //repcourrant= QCoreApplication::applicationFilePath();

    //qDebug() << repcourrant << " " + QCoreApplication::applicationDirPath();
    //QFrame *tabf= new QFrame(ui->centralwidget);
    //QVBoxLayout *calque= new QVBoxLayout(tabf);

    if(tabwidget== nullptr)
    {
        //tabwidget= new QTabWidget();

        tabwidget= ui->tabWidget;
        tabwidget->removeTab(0); // Permet de supprimer la tab provenant de l'ui
        //qDebug()<<"ICI..." << tabwidget->currentIndex();
        //calque= new QVBoxLayout(tabwidget);
    }


    //calque->addWidget(plaintextedit);

    QPlainTextEdit *plaintextedit= new QPlainTextEdit(tabwidget);
    plaintextedit->setObjectName("Edition");

    int index= tabwidget->addTab(plaintextedit,"Nouveau");
    tabwidget->setCurrentIndex(index);

    //plaintextedit->setParent(tabwidget);

    tabwidget->setTabToolTip(tabwidget->currentIndex(),"");

    tabwidget->setMovable(true);
    tabwidget->setTabsClosable(true);

    //calque->show();
    ajoutFich(index, "Nouveau", "");

    connect(plaintextedit, SIGNAL(textChanged()), this, SLOT(ContentChanged( )));
}

void MainWindow::openFile()
{
    QString fichier= QFileDialog::getOpenFileName(this, "Ouverture d'un fichier", QDir::currentPath(),
                            "All files (*.*) ;; Source C/C++ (*.c *.h *.cpp *.hpp);; PNG files (*.png)");

    if( !fichier.isNull() )
    {
        QFile desc(fichier);
        QFileInfo descinfo(fichier);

        //QPlainTextEdit *plaintextedit= new QPlainTextEdit();


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
            QPlainTextEdit *plaintextedit= new QPlainTextEdit(tabwidget);
            plaintextedit->setObjectName("Edition");

            //plaintextedit->setDocumentTitle("toto");

            plaintextedit->setPlainText(texte);

            //calque->addWidget(plaintextedit);
            //qDebug() << "Doc titre " << plaintextedit->documentTitle();


            // Création de l'onglet contenant le container texte
            int index= tabwidget->addTab(plaintextedit,descinfo.fileName());

            tabwidget->setCurrentIndex(index);

            //qDebug()<< "LA" << tabwidget->indexOf(tabwidget->children());

            tabwidget->setTabToolTip(index, descinfo.absoluteFilePath());

            tabwidget->setMovable(true);
            tabwidget->setTabsClosable(true);

            ajoutFich(index, descinfo.fileName(), texte);

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
    //QPlainTextEdit *qpte = new QPlainTextEdit(tabwidget);
    // Suppression de '*' si elle existe
    QString titre= tabwidget->tabText(tabwidget->currentIndex());
    if(titre[0]== "*" )
    {
        tabwidget->setTabText(tabwidget->currentIndex(), titre.remove(0,1));
    }

    QList<QPlainTextEdit *> lqpte= tabwidget->findChildren<QPlainTextEdit *>("Edition"); // "Edition"


    // BUG POUR EVITER LE PROBLEME DE DISFONCTIONNEMENT D INDEXOF.
    QString contenu= lqpte[tabwidget->count()-1]->toPlainText();

    qDebug()<<"tooltip : " << tabwidget->tabToolTip(tabwidget->currentIndex());

    //qDebug() << "Hors du for: tabw : " <<  tabwidget->currentIndex();
    //qDebug() << "Hors du for: lpqt[tabw...] : " <<  lqpte[tabwidget->currentIndex()]->toPlainText();
    //qDebug() << "Hors du for: lpqt[tabw...] : " <<  contenu;


    // Sauvegarde
    QString fichier= QFileDialog::getSaveFileName(this, tr("Sauvegarde du fichier"), tabwidget->tabToolTip(tabwidget->currentIndex()),
                                    tr( "All files (*.*) ;; Source C/C++ (*.c *.h *.cpp *.hpp);; PNG files (*.png)"));

    QFile desc(fichier);
    //QFileInfo descinfo(fichier);

    //qDebug()<< descinfo.absoluteFilePath();

    if(!desc.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(this,"Attention!","L'ouverture du fichier à échoué, erreur: " + desc.errorString());
    }
    else
    {
        // Lecture du fichier
        QTextStream out(&desc);

        out << contenu;

        desc.close();

    }
}

void MainWindow::ContentChanged()
{
    QString titre= tabwidget->tabText(tabwidget->currentIndex());

    //qDebug()<< "Changement de contenu du fichier : " + titre;

    if(titre[0]!= "*" )
    {
        tabwidget->setTabText(tabwidget->currentIndex(), "*"+titre);
    }



    /* A IMPLEMENTER DANS EVENNEMENT MOVEEVENT ????
    // BUG POUR EVITER LE PROBLEME DE DISFONCTIONNEMENT D INDEXOF.
    QList<QPlainTextEdit *> lqpte= tabwidget->findChildren<QPlainTextEdit *>("Edition"); // "Edition"
    QPoint qpt= lqpte[tabwidget->count()-1]->pos();

    lc= "Position : " + QString::number(qpt.x());

    ui->label->setText(lc);
    */
}


void MainWindow::ajoutFich(int n, QString nf, QString cont)
{
    Onglet o;

    o.num= n;
    o.nfich= nf;
    o.content= cont;
    lstonglet->append(o);
    qDebug() << "Onglet" << o.num << o.nfich << o.content;
}


/*
QString MainWindow::texteAssocieTab()
{
    //QList<QWidget *>liste= tabwidget->findChildren<QWidget *>();
    QList<QPlainTextEdit *>liste= tabwidget->findChildren<QPlainTextEdit *>();
    //int el = tabwidget->indexOf((QWidget *)tabwidget->findChild);
    QString ret("ttoto");

    //for(QPlainTextEdit *el : liste)
    for(int i= 0; i< liste.count(); i++)
    {
        //qDebug()<< tabwidget->indexOf(el->parentWidget());
        qDebug()<< tabwidget->indexOf((QTabWidget *)liste[i]->parent()) << liste[i]->toolTip();
        //qDebug()<< liste[i]->parentWidget()->;
        //qDebug()<< tabwidget->indexOf(liste[i]->parent());
        //qDebug()<< el;
    }
    return ret;

}

*/

/*
void MainWindow::saveFile()
{
    //QPlainTextEdit *qpte = new QPlainTextEdit(tabwidget);
    // Suppression de '*' si elle existe
    QString titre= tabwidget->tabText(tabwidget->currentIndex());
    if(titre[0]== "*" )
    {
        tabwidget->setTabText(tabwidget->currentIndex(), titre.remove(0,1));
    }


    //qDebug()<<"Sauvegarde: " << tabwidget->tabToolTip(tabwidget->currentIndex());

    //qDebug()<<texteAssocieTab();

    ////////////////////// TTEST



    QList<QPlainTextEdit *> lqpte= tabwidget->findChildren<QPlainTextEdit *>("Edition"); // "Edition"
    int ind= tabwidget->currentIndex();
    qDebug() << "ind " << ind;
    //auto cw= tabwidget->currentWidget()->toolTip();

    qDebug() << "courant widget : " << ind;

    qDebug() << "Dans le for " << endl;
    for(int i= 0; i < lqpte.count(); i++)
    {
        //QPlainTextEdit *el= lqpte[i];
        qDebug()<< "test4" << tabwidget->indexOf((QTabWidget *)lqpte[i]->parent());//tabwidget->indexOf(el->parentWidget());
        //qDebug()<< ((QTabWidget *)el->parentWidget())->currentIndex();//tabwidget->indexOf(el->parentWidget());
        //qDebug()<< tabwidget->isAncestorOf(el); // true
        //qDebug() << (el->parentWidget())->isWidgetType();
        //qDebug() << (el->parentWidget())->inherits("QTabWidget");
        //qDebug() << "Titre doc :" << el->documentTitle();

        qDebug()<<"tooltip : " << tabwidget->tabToolTip(i) << " de l  indice i= "<< i;

        qDebug() << "plaitext : " << lqpte[i]->toPlainText();
        qDebug() << "tabwidget->currentIndex(): " << tabwidget->currentIndex();
        qDebug() << "test: " <<lqpte[tabwidget->currentIndex()]->toPlainText();//tabwidget->indexOf(el->parentWidget());
        qDebug()<< "test2" << tabwidget->indexOf((QTabWidget *)lqpte[i]->parent());//tabwidget->indexOf(el->parentWidget());
        qDebug()<< "test3" << lqpte[tabwidget->currentIndex()]->toPlainText();//tabwidget->indexOf(el->parentWidget());
        qDebug()<< "test3" << lqpte[1]->toPlainText();//tabwidget->indexOf(el->parentWidget());


        if( el->parentWidget()->inherits("QTabWidget") )
        {
            //qDebug() << "ICI" << tabwidget->indexOf(el->parentWidget());
            QTabWidget *qtw= (QTabWidget *)el->parentWidget();
            qDebug() << "ICI" << qtw->indexOf(el->parentWidget());
            qDebug() << "ICI" << qtw->indexOf(el->parentWidget());
        }


        //qDebug() <<
        //qDebug() << tabwidget->currentIndex();
    }

    //QList<QTabWidget *> tab= tabwidget;

    qDebug() << "Hors du for: tabw : " <<  tabwidget->currentIndex() <<endl;
    qDebug() << "Hors du for: lpqt[tabw...] : " <<  lqpte[tabwidget->currentIndex()]->toPlainText()<< endl;


    //QFileDialog::getSaveFileName(this)
}

*/


/*
void MainWindow::createTab(QString f)
{
    tabwidget->addTab(new QWidget, f);
    tabwidget->setMovable(true);
    tabwidget->setTabsClosable(true);
}
*/
