#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QTabWidget>
#include<QPlainTextEdit>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //void createTab(QString);

private slots:
    void openFile();
    void closeFile(int);
    void saveFile(void);
    void ContentChanged(void);
    void newFile(void);

private:
    Ui::MainWindow *ui;
    QTabWidget *tabwidget= nullptr;
    QPlainTextEdit *plaintextedit= nullptr;

};
#endif // MAINWINDOW_H
