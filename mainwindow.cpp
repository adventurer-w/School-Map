#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QString>
#include <QPainter>
#include<QTime>

void sleep(unsigned int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->shortes=new wangziyi;
    for(int i=0;i<25;i++)
    {
        for(int j=0;j<25;j++)
        {
            colors[i][j]="lightGray";
        }
    }

    mpb[0]= ui->btn_beicao;
    mpb[1]= ui->btn_tiyuguan;
    mpb[2]=ui->btn_beichan;
    mpb[3]=ui->btn_haike;
    mpb[4]=ui->btn_sijiao;
    mpb[5]=ui->btn_dongcao;
    mpb[6]=ui->btn_wujiao;
    mpb[7]=ui->btn_liujiao;
    mpb[8]=ui->btn_gongyuan;
    mpb[9]=ui->btn_haiyang;
    mpb[10]=ui->btn_wuziding;
    mpb[11]=ui->btn_huayuan;
    mpb[12]=ui->btn_xinbei;
    mpb[13]=ui->btn_cailiao;
    mpb[14]=ui->btn_xinnan;
    mpb[15]=ui->btn_diyuan;
    mpb[16]=ui->btn_xinzilou;
    mpb[17]=ui->btn_tushuguan;
    mpb[18]=ui->btn_zhengfa;
    mpb[19]=ui->btn_houqin;
    mpb[20]=ui->btn_shuyuan;
    mpb[21]=ui->btn_wenxin;

}
void MainWindow::init(){

    for(auto x:this->shortes->List){
        int nw=x.first,nx=x.second.first,dis=x.second.second;
        QPen pen;
        QPainter painter(this);
        pen.setWidth(5);
        pen.setColor(colors[nw][nx]);
        painter.setRenderHint(QPainter::Antialiasing, true); // 反走样
        painter.setPen(pen);
        painter.drawLine(QPointF(mpb[nw]->x()+7,mpb[nw]->y()+7), QPointF(mpb[nx]->x()+7, mpb[nx]->y()+7));// 绘制直线

        pen.setColor("Purple");
        painter.setPen(pen);
        painter.drawText(QPointF((mpb[nw]->x()+mpb[nx]->x())/2,(mpb[nw]->y()+mpb[nx]->y())/2),QString::number(dis));
    }
}
void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter pbk(this);
//    pbk.drawPixmap(30,10,881,701,QPixmap("mymap.jpg"));
    init();
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::floyd_print(int pre[25][25],int i,int j){
    if(i==j) return;
    if(pre[i][j]==0){
        colors[i][j]=colors[j][i]="Blue";
    }else{
        floyd_print(pre,i,pre[i][j]);
        floyd_print(pre,pre[i][j],j);
    }
}
void MainWindow::on_btn_floyd_clicked()
{
    if(this->shortes->starcity == ""||this->shortes->overcity== "") return;
    this->c=1;
    this->ui->btn_floyd->setStyleSheet("background-color: rgb(189, 240, 255);");
    this->ui->btn_dijkstra->setStyleSheet("color: rgb(0, 0, 0);");


    for(int i=0;i<25;i++)
    {
        for(int j=0;j<25;j++)
        {
            colors[i][j]="lightGray";
        }
    }
    update();

    int dis[25][25],pre[25][25];
    memset(pre,0,sizeof (pre));
    for(int i=0;i<=21;i++){
        for(int j=0;j<=21;j++){
            dis[i][j]=this->shortes->G.arcs[i][j].path;
        }
    }

    for(int k=0;k<=21;k++){
        for(int i=0;i<=21;i++){
            for(int j=0;j<=21;j++){
                if(dis[i][j]>dis[i][k]+dis[k][j]){
                    dis[i][j]=dis[i][k]+dis[k][j];
                    pre[i][j]=k;
                }
            }
        }
    }
    floyd_print(pre,this->shortes->st,this->shortes->ed);
    this->ui->label_display->setText("最短距离是："+QString::number(dis[this->shortes->st][this->shortes->ed]));
}

void MainWindow::on_btn_dijkstra_clicked()
{
    if(this->shortes->starcity == ""||this->shortes->overcity== "") return;
    this->c=0;
    this->ui->btn_dijkstra->setStyleSheet("background-color: rgb(189, 240, 255);");
    this->ui->btn_floyd->setStyleSheet("color: rgb(0, 0, 0);");


    for(int i=0;i<25;i++)
    {
        for(int j=0;j<25;j++)
        {
            colors[i][j]="lightGray";
        }
    }
    update();


    int dis[25],n=22,pre[25];
    bool st[25];
    memset(st,false,sizeof (st));
    memset(dis,0x3f,sizeof (dis));
    memset(pre,0x3f,sizeof (pre));
    dis[this->shortes->st]=0;

    for(int i=0;i<n;i++){
        int t=-1;
        for(int j=0;j<n;j++){
            if(!st[j]&&(t==-1||dis[t]>dis[j]))
                t=j;
        }
        st[t]=true;
        if(pre[t]!=0x3f3f3f3f) colors[t][pre[t]]=colors[pre[t]][t]="lightBlue";
        update();
        sleep(200);

        for(auto x:this->shortes->List){
            int nw=x.first,j=x.second.first,tt=x.second.second;
            if(j==t){
               j^=nw;nw^=j;j^=nw;
            }
            if(nw==t){
                if(dis[j]>=dis[t]+tt){
                    dis[j]=dis[t]+tt;
                    pre[j]=t;
                }
            }
        }
        if(t==this->shortes->ed) break;
    }
    int zd =this->shortes->ed,qd=this->shortes->st;
    while(zd!=qd){
        colors[zd][pre[zd]]=colors[pre[zd]][zd]="Blue";
        zd=pre[zd];
    }
    update();
    this->ui->label_display->setText("最短距离是："+QString::number(dis[this->shortes->ed]));
}

void MainWindow::on_btn_clean_clicked()
{
    this->c=-1;
    this->ui->btn_floyd->setStyleSheet("color: rgb(0, 0, 0);");
    this->ui->btn_dijkstra->setStyleSheet("color: rgb(0, 0, 0);");
    for(int i=0;i<25;i++)
    {
        for(int j=0;j<25;j++)
        {
            colors[i][j]="lightGray";
        }
    }
    this->ui->label_start->setText("");
    this->ui->label_over->setText("");
    this->ui->label_display->setText("");
    this->shortes->starcity="";
    this->shortes->overcity="";
    update();
}

void MainWindow::place_onclick(QRadioButton *btn){
    int v;
    for(int i=0;i<=23;i++){
        if(mpb[i]==btn){
            v=i;
            break;
        }
    }
    if(this->shortes->starcity==""){
        for(int i=0;i<25;i++)
        {
            for(int j=0;j<25;j++)
            {
                colors[i][j]="lightGray";
            }
        }
        update();
        this->ui->label_start->setText(btn->text());
        this->shortes->starcity=btn->text();
        this->ui->label_over->setText("");
        this->ui->label_display->setText("");
        this->shortes->st=v;
    }else if(this->shortes->starcity==btn->text()||this->shortes->overcity==btn->text()){
        this->ui->label_start->setText("");
        this->shortes->starcity="";

        this->ui->label_over->setText("");
        this->shortes->overcity="";

        this->ui->label_display->setText("");
    }else{
        for(int i=0;i<25;i++)
        {
            for(int j=0;j<25;j++)
            {
                colors[i][j]="lightGray";
            }
        }
        update();
        this->ui->label_over->setText(btn->text());
        this->shortes->overcity=btn->text();
        this->ui->label_display->setText("");
        this->shortes->ed=v;
    }
    btn->setAutoExclusive(false);
    btn->setChecked(false);
}

void MainWindow::on_btn_cailiao_clicked(){
    place_onclick(ui->btn_cailiao);
}
void MainWindow::on_btn_dongcao_clicked(){
place_onclick(ui->btn_dongcao);
}
void MainWindow::on_btn_beichan_clicked(){
place_onclick(ui->btn_beichan);
}
void MainWindow::on_btn_sijiao_clicked(){
place_onclick(ui->btn_sijiao);
}
void MainWindow::on_btn_wujiao_clicked(){
    place_onclick(ui->btn_wujiao);
}
void MainWindow::on_btn_beicao_clicked(){
place_onclick(ui->btn_beicao);
}
void MainWindow::on_btn_diyuan_clicked(){
place_onclick(ui->btn_diyuan);
}
void MainWindow::on_btn_gongyuan_clicked(){
place_onclick(ui->btn_gongyuan);
}
void MainWindow::on_btn_huayuan_clicked(){
place_onclick(ui->btn_huayuan);
}
void MainWindow::on_btn_xinbei_clicked(){
place_onclick(ui->btn_xinbei);
}
void MainWindow::on_btn_xinnan_clicked(){
place_onclick(ui->btn_xinnan);
}
void MainWindow::on_btn_houqin_clicked(){
place_onclick(ui->btn_houqin);
}
void MainWindow::on_btn_wuziding_clicked(){
place_onclick(ui->btn_wuziding);
}
void MainWindow::on_btn_wenxin_clicked(){
place_onclick(ui->btn_wenxin);
}
void MainWindow::on_btn_haiyang_clicked(){
place_onclick(ui->btn_haiyang);
}
void MainWindow::on_btn_haike_clicked(){
place_onclick(ui->btn_haike);
}
void MainWindow::on_btn_tiyuguan_clicked(){
place_onclick(ui->btn_tiyuguan);
}
void MainWindow::on_btn_liujiao_clicked(){
place_onclick(ui->btn_liujiao);
}
void MainWindow::on_btn_tushuguan_clicked(){
place_onclick(ui->btn_tushuguan);
}
void MainWindow::on_btn_xinzilou_clicked(){
place_onclick(ui->btn_xinzilou);
}
void MainWindow::on_btn_shuyuan_clicked(){
place_onclick(ui->btn_shuyuan);
}
void MainWindow::on_btn_zhengfa_clicked(){
place_onclick(ui->btn_zhengfa);
}



