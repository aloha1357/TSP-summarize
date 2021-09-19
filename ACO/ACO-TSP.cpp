#include <bits/stdc++.h>

using namespace std;

unsigned seed=(unsigned)time(0);

//51個城市的坐標


int CityPos[51][2];
void Readcoordinatetxt(string txtfilename)//Read the function of the city coordinate file
	{
		//Citycount = citycount;
		//city = new City[Citycount];
		ifstream myfile(txtfilename, ios::in);
		double x = 0, y = 1;
		int z = 0;
		if (!myfile.fail())
		{
			int i = 0;
			while (!myfile.eof() && (myfile >> z >> x >> y))
			{
				//CityPos[i].name = to_string(_Longlong(z));//City name is converted to string
				CityPos[i][0] = x; CityPos[i][1] = y;
				i++;
			}
		}
		else
			cout << "file does not exist";
		myfile.close();//Calculate the city distance matrix
		/*for (int i = 0; i < citycount; i++)
			for (int j = 0; j < citycount; j++)
			{
				distance[i][j] = sqrt((pow((city[i].x - city[j].x), 2) + pow((city[i].y - city[j].y), 2))/3);//Calculate the pseudo Euclidean distance between cities ij
				if (round(distance[i][j] < distance[i][j]))distance[i][j] = round(distance[i][j]) + 1;
				else distance[i][j] = round(distance[i][j]);
			}*/
	}
/*={

{37,52},

{49,49},

{52,64},

{20,26},

{40,30},

{21,47},

{17,63},

{31,62},

{52,33},

{51,21},

{42,41},

{31,32},

{5,25},

{12,42},

{36,16},

{52,41},

{27,23},

{17,33},

{13,13},

{57,58},};//{{87,7},{91,38},{83,46},{71,44},{64,60},{68,58},{83, 69},{87,76},{74,78},{71, 71},{58,69},{54,62},{51,67},{37,84},{41,94} ,{2,99},{7,64},{22,60},{25,62},{18,54},{4,50},{13,40},{18,40},{ 24,42},{25,38},{41,26},{45,21},{44,35},{58,35},{62,32}};
*/
double anas=0;

#define CITY_NUM 51 //城市數量

#define ANT_NUM 102 //蟻群數量

#define TMAC 700 //迭代最大次數

#define ROU 0.5 //誤差大小

#define ALPHA 1 //信息素重要程度的參數

#define BETA 4 //啟發式因子重要程度的參數

#define Q 100 //信息素殘留參數

const int maxn = 100;

double dis[maxn][maxn]; //距離

double info[maxn][maxn]; //信息素矩陣

double E[CITY_NUM][CITY_NUM]; //啟發因子矩陣

int vis[CITY_NUM][CITY_NUM];

double Bestlength;

double ans[CITY_NUM];

const double mmax = 10e9;



//返回指定範圍內的隨機整數

int rnd(int nLow,int nUpper)

{

    return nLow+(nUpper-nLow)*rand()/(RAND_MAX+1);

}



//返回指定範圍內的隨機浮點數

double rnd(double dbLow,double dbUpper)

{

    double dbTemp=rand()/((double)RAND_MAX+1.0);

    return dbLow+dbTemp*(dbUpper-dbLow);

}

//返回浮點數四捨五入取整後的浮點數

double ROUND(double dbA)

{

    return (double)((int)(dbA+0.5));

}



struct Ant

{



    int Path[CITY_NUM]; //螞蟻走的路徑

    double length; //路徑總長度

    int vis[CITY_NUM]; //走過城市標記

    int cur_cityno; //當前城市

    int moved_cnt; //已走的數量

    //初始化

    void Init()

    {

        memset(vis, 0, sizeof(vis));

        length = 0;

        cur_cityno = rnd(0, CITY_NUM);//隨機選擇一個出發城市

        Path[0] = cur_cityno;

        vis[cur_cityno] = 1;

        moved_cnt = 1;

        //printf("Init %d \n", cur_cityno);

    }

    //選擇下一個城市

    //返回值為城市編號

    int chooseNextCity()

    {

        int nSelectedCity=-1; //返回結果，先暫時把其設置為-1

        //計算當前城市和沒去過的城市之間的信息素總和

        double dbTotal=0.0;

        double prob[CITY_NUM]; //保存各個城市被選中的概率

        for(int i = 0; i < CITY_NUM; i++)

        {

            if (!vis[i])

            {

                prob[i]=pow(info[cur_cityno][i],ALPHA)

                        *pow(1.0/dis[cur_cityno][i], BETA);

                dbTotal += prob[i];

            }

            else

            {

                prob[i] = 0;

            }

        }

        //進行輪盤選擇

        double dbTemp=0.0;

        if (dbTotal > 0.0) //總的信息素值大於0

        {

            dbTemp = rnd(0.0, dbTotal);

            for (int i = 0; i < CITY_NUM; i++)

            {

                if (!vis[i])

                {

                    dbTemp -= prob[i];

                    if (dbTemp < 0.0)

                    {

                        nSelectedCity = i;

                        break;

                    }

                }

            }

        }

        //如果城市間的信息素非常小(小到比double能夠表示的最小的數字還要小)

        //出現這種情況，就把第一個沒去過的城市作為返回結果



        if (nSelectedCity == -1)

        {

            for (int i=0; i<CITY_NUM; i++)

            {

                if (!vis[i]) //城市沒去過

                {

                    nSelectedCity=i;

                    break;

                }

            }

        }

        return nSelectedCity;

    }



    //螞蟻在城市間移動

    void Move()

    {

        int nCityno = chooseNextCity();//選擇下一個城市

        Path[moved_cnt] = nCityno;//保存螞蟻走的路徑

        vis[nCityno] = 1;//把這個城市設置成已經去過

        cur_cityno = nCityno;

        //更新已走路徑長度

        length += dis[Path[moved_cnt-1]][Path[moved_cnt]];

        moved_cnt++;



    }

    //螞蟻進行搜索一次

    void Search()

    {

        Init();

        //如果螞蟻去過的城市數量小於城市數量，就繼續移動

        while(moved_cnt < CITY_NUM)

        {

            Move();

        }

        length += dis[Path[CITY_NUM-1]][Path[0]];

    }



};





struct TSP

{

    Ant ants[ANT_NUM]; //定義一群螞蟻

    Ant ant_best; //保存最好結果的螞蟻



    void Init()

    {

        //初始化為最大值

        ant_best.length = mmax;

       // puts("cal dis");

        //計算兩兩城市間距離

        for (int i = 0; i < CITY_NUM; i++)

        {

            for (int j = 0; j < CITY_NUM; j++)

            {

                double temp1=CityPos[j][0]-CityPos[i][0];

                double temp2=CityPos[j][1]-CityPos[i][1];

                dis[i][j] = sqrt(temp1*temp1+temp2*temp2);

            }

        }

        //初始化環境信息素

        //puts("init info");

        for (int i=0; i<CITY_NUM; i++)

        {

            for (int j=0; j<CITY_NUM; j++)

            {

                info[i][j]=1.0;

            }

        }

    }

    //更新信息素,當前每條路上的信息素等於過去保留的信息素

    //加上每個螞蟻這次走過去剩下的信息素

    void Updateinfo()

    {

        //puts("update info");

        double tmpinfo[CITY_NUM][CITY_NUM];

        memset(tmpinfo, 0, sizeof(tmpinfo));

        int m = 0;

        int n = 0;

        //遍歷每隻螞蟻

        for (int i = 0; i < ANT_NUM; i++) {

            //puts("****");

// for (int j = 0; j < CITY_NUM; j++) {

// printf("%d ", ants[i].Path[j]);

// }

            //puts("");

            for (int j = 1; j < CITY_NUM; j++)

            {

                m = ants[i].Path[j];

                n = ants[i].Path[j-1];

                //printf("%d %d\n", m, n);

                tmpinfo[n][m] = tmpinfo[n][m]+Q/ants[i].length;

                tmpinfo[m][n] = tmpinfo[n][m];

            }

            //最后城市和開始城市之間的信息素

            n = ants[i].Path[0];

            tmpinfo[n][m] = tmpinfo[n][m]+Q/ants[i].length;

            tmpinfo[m][n] = tmpinfo[n][m];

        }



         //更新環境信息素

         for (int i = 0; i < CITY_NUM; i++)

         {

             for (int j = 0; j < CITY_NUM; j++) {

                //最新的環境信息素=留存的信息素+新留下的信息素

                info[i][j] = info[i][j]*ROU + tmpinfo[i][j];



             }

         }

    }

    //尋找路徑，迭代TMAC次

    void Search()

    {



        for (int i = 0; i < TMAC; i++) {

            //printf("current iteration times %d\n", i);

            for (int j = 0; j < ANT_NUM; j++) {

                ants[j].Search();

            }

            //保存最佳結果

            for (int j = 0; j < ANT_NUM; j++) {

                if (ant_best.length > ants[j].length) {

                    ant_best = ants[j];

                }

            }



            //更新環境信息素

            Updateinfo();



            //printf("%lf\n", ant_best.length);

            anas=ant_best.length;

        }

    }



};





void input(){

     int a=0,b=0,c=0;

     memset(CityPos,0,sizeof(int)*30*2 );

while(scanf("%d %d %d",&a,&b,&c)!=EOF || a!=0){

    CityPos[a][0]=b;

    CityPos[a][1]=c;

    //cout<<a<<b<<c<<endl;

}

}//while(scanf("%d %d %d",&a,&b,&c)!=EOF)

int main()

{
    auto start = std::chrono::system_clock::now();

    Readcoordinatetxt("cities.txt");
    for(int i=0;i<51;i++)
        cout<<CityPos[i][0]<<"\t"<<CityPos[i][1]<<endl;
    //freopen("output.txt", "w", stdout);

    //nput();

    srand(seed);

    TSP tsp;

    //初始化蟻群

    tsp.Init();

    //開始查找

    tsp.Search();

    //puts("The Minimum length route is :\n");

    for (int i = 0; i < CITY_NUM; i++) {

        if (i != 0 && i % 20 == 0) {

            //puts("");

        }

        //printf("%d ", tsp.ant_best.Path[i]);

    }

printf("%lf\n", anas);

  auto end = std::chrono::system_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	cout << "Spent"
		<< double(duration.count()) * std::chrono::microseconds::period::num / std::chrono::microseconds::period::den
		<< "seconds" << endl;
    return 0;

}
