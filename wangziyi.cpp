#include "wangziyi.h"
#include "cstring"

wangziyi::wangziyi()
{
    starcity="";
    overcity="";
    G.arcnum = 20;
    G.vexnum = 22;

    G.places[0]="beichan";mp["beichan"]=0;
    G.places[1]="tiyuguan";mp["tiyuguan"]=1;
    G.places[2]="beichan";mp["beichan"]=2;
    G.places[3]="haike";mp["haike"]=3;
    G.places[4]="sijiao";mp["sijiao"]=4;
    G.places[5]="dongcao";mp["dongcao"]=5;
    G.places[6]="wujiao";mp["wujiao"]=6;
    G.places[7]="liujiao";mp["liujiao"]=7;
    G.places[8]="gongyuan";mp["gongyuan"]=8;
    G.places[9]="haiyang";mp["haiyang"]=9;
    G.places[10]="wuziding";mp["wuziding"]=10;
    G.places[11]="huayuan";mp["huayuan"]=11;
    G.places[12]="xinbei";mp["xinbei"]=12;
    G.places[13]="cailiao";mp["cailiao"]=13;
    G.places[14]="xinnan";mp["xinnan"]=14;
    G.places[15]="diyuan";mp["diyuan"]=15;
    G.places[16]="xinzilou";mp["xinzilou"]=16;
    G.places[17]="tushuguan";mp["tushuguan"]=17;
    G.places[18]="zhengfa";mp["zhengfa"]=18;
    G.places[19]="houqin";mp["houqin"]=19;
    G.places[20]="shuyuan";mp["shuyuan"]=20;
    G.places[21]="wenxin";mp["wenxin"]=21;

    List.push_back({0,{1,81}});List.push_back({0,{2,192}});
    List.push_back({1,{3,108}});List.push_back({1,{4,168}});
    List.push_back({2,{5,211}});List.push_back({3,{4,120}});
    List.push_back({4,{6,89}});List.push_back({2,{4,213}});
    List.push_back({5,{10,295}});List.push_back({6,{7,92}});
    List.push_back({18,{14,323}});List.push_back({7,{12,180}});
    List.push_back({7,{10,360}});List.push_back({7,{9,178}});
    List.push_back({8,{11,123}});List.push_back({8,{9,70}});
    List.push_back({9,{12,80}});List.push_back({9,{13,138}});
    List.push_back({10,{12,330}});List.push_back({11,{13,72}});
    List.push_back({12,{13,136}});List.push_back({12,{14,79}});
    List.push_back({13,{15,128}});List.push_back({14,{17,284}});
    List.push_back({14,{16,395}});List.push_back({16,{17,320}});
    List.push_back({17,{20,210}});List.push_back({17,{18,220}});
    List.push_back({18,{19,188}});List.push_back({19,{21,180}});

    for(int i=0;i<=21;i++){
        for(int j=0;j<=21;j++){
            G.arcs[i][j].path=999999;
        }
    }
    for(auto x:List){
        int nw=x.first,nx=x.second.first,dis=x.second.second;
        G.arcs[nw][nx].path=G.arcs[nx][nw].path=dis;
    }

}
