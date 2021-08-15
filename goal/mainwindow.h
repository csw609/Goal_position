#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    explicit MainWindow(std::string q, QWidget *parent = nullptr);
    ~MainWindow();
    //func
    bool eventFilter(QObject *target, QEvent *event);

    //var
    QString add;
    QString group = "ns1";
    int wid;
    int hei;
private slots:
    void on_ns1_clicked();

    void on_ns2_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
