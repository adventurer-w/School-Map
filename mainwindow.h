#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QVector>
#include "wangziyi.h"
#include <QMap>
#include <QRadioButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    int c=4;
    int distance[25];
    int distance1[25][25];
    QString display;
    QString colors[25][25];
    QRadioButton *mpb[25];
    MainWindow(QWidget *parent = nullptr);
    void place_onclick(QRadioButton *btn);
    void init();
    void floyd_print(int dis[25][25],int i,int j);
    ~MainWindow();

protected:
   void paintEvent(QPaintEvent *);

private slots:
   void on_btn_dijkstra_clicked();
   void on_btn_floyd_clicked();
   void on_btn_clean_clicked();
    void on_btn_cailiao_clicked();
    void on_btn_dongcao_clicked();
    void on_btn_beichan_clicked();
    void on_btn_sijiao_clicked();
    void on_btn_wujiao_clicked();
    void on_btn_beicao_clicked();
    void on_btn_diyuan_clicked();
    void on_btn_gongyuan_clicked();
    void on_btn_huayuan_clicked();
    void on_btn_xinbei_clicked();
    void on_btn_xinnan_clicked();
    void on_btn_houqin_clicked();
    void on_btn_wuziding_clicked();
    void on_btn_wenxin_clicked();
    void on_btn_haiyang_clicked();
    void on_btn_haike_clicked();
    void on_btn_tiyuguan_clicked();
    void on_btn_liujiao_clicked();
    void on_btn_tushuguan_clicked();
    void on_btn_xinzilou_clicked();
    void on_btn_shuyuan_clicked();
    void on_btn_zhengfa_clicked();

private:
    Ui::MainWindow *ui;
    wangziyi *shortes;
};
#endif // MAINWINDOW_H
