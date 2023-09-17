#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QTabWidget>
#include<QPlainTextEdit>
#include <QVBoxLayout>

#include <map>
#include <QVector>
#include <QString>
#include <QList>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

typedef struct
{
    int num;
    QString nfich;
    QString content;
}Onglet;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void ajoutFich(int, QString, QString);

    //void createTab(QString);

private slots:
    void openFile();
    void closeFile(int);
    void saveFile(void);
    void ContentChanged(void);
    void newFile(void);
    //QString texteAssocieTab();

private:
    Ui::MainWindow *ui;
    QTabWidget *tabwidget= nullptr;
    //QPlainTextEdit *plaintextedit= nullptr;
    QString lc;
    //QVBoxLayout *calque;
    //QString repcourrant;
    //std::map <int,QString> dict;
    QList <Onglet> *lstonglet= new QList<Onglet>;

};


#endif // MAINWINDOW_H
