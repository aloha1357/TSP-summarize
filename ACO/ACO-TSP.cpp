#include <bits/stdc++.h>

using namespace std;

unsigned seed=(unsigned)time(0);

//51カГ夹


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

#define CITY_NUM 51 //カ计秖

#define ANT_NUM 102 //闷竤计秖

#define TMAC 700 //程Ω计

#define ROU 0.5 //粇畉

#define ALPHA 1 //獺璶祘把计

#define BETA 4 //币祇Α璶祘把计

#define Q 100 //獺摧痙把计

const int maxn = 100;

double dis[maxn][maxn]; //禯瞒

double info[maxn][maxn]; //獺痻皚

double E[CITY_NUM][CITY_NUM]; //币祇痻皚

int vis[CITY_NUM][CITY_NUM];

double Bestlength;

double ans[CITY_NUM];

const double mmax = 10e9;



//﹚絛瞅ず繦诀俱计

int rnd(int nLow,int nUpper)

{

    return nLow+(nUpper-nLow)*rand()/(RAND_MAX+1);

}



//﹚絛瞅ず繦诀疊翴计

double rnd(double dbLow,double dbUpper)

{

    double dbTemp=rand()/((double)RAND_MAX+1.0);

    return dbLow+dbTemp*(dbUpper-dbLow);

}

//疊翴计彼き俱疊翴计

double ROUND(double dbA)

{

    return (double)((int)(dbA+0.5));

}



struct Ant

{



    int Path[CITY_NUM]; //柯闷ǐ隔畖

    double length; //隔畖羆

    int vis[CITY_NUM]; //ǐ筁カ夹癘

    int cur_cityno; //讽玡カ

    int moved_cnt; //ǐ计秖

    //﹍て

    void Init()

    {

        memset(vis, 0, sizeof(vis));

        length = 0;

        cur_cityno = rnd(0, CITY_NUM);//繦诀匡拒祇カ

        Path[0] = cur_cityno;

        vis[cur_cityno] = 1;

        moved_cnt = 1;

        //printf("Init %d \n", cur_cityno);

    }

    //匡拒カ

    //カ絪腹

    int chooseNextCity()

    {

        int nSelectedCity=-1; //挡狦既рㄤ砞竚-1

        //璸衡讽玡カ㎝⊿筁カぇ丁獺羆㎝

        double dbTotal=0.0;

        double prob[CITY_NUM]; //玂カ砆匡い阀瞯

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

        //秈︽近絃匡拒

        double dbTemp=0.0;

        if (dbTotal > 0.0) //羆獺0

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

        //狦カ丁獺獶盽(ゑdouble镑ボ程计临璶)

        //瞷硂贺薄猵碞р材⊿筁カ挡狦



        if (nSelectedCity == -1)

        {

            for (int i=0; i<CITY_NUM; i++)

            {

                if (!vis[i]) //カ⊿筁

                {

                    nSelectedCity=i;

                    break;

                }

            }

        }

        return nSelectedCity;

    }



    //柯闷カ丁簿笆

    void Move()

    {

        int nCityno = chooseNextCity();//匡拒カ

        Path[moved_cnt] = nCityno;//玂柯闷ǐ隔畖

        vis[nCityno] = 1;//р硂カ砞竚Θ竒筁

        cur_cityno = nCityno;

        //穝ǐ隔畖

        length += dis[Path[moved_cnt-1]][Path[moved_cnt]];

        moved_cnt++;



    }

    //柯闷秈︽穓Ω

    void Search()

    {

        Init();

        //狦柯闷筁カ计秖カ计秖碞膥尿簿笆

        while(moved_cnt < CITY_NUM)

        {

            Move();

        }

        length += dis[Path[CITY_NUM-1]][Path[0]];

    }



};





struct TSP

{

    Ant ants[ANT_NUM]; //﹚竡竤柯闷

    Ant ant_best; //玂程挡狦柯闷



    void Init()

    {

        //﹍て程

        ant_best.length = mmax;

       // puts("cal dis");

        //璸衡ㄢㄢカ丁禯瞒

        for (int i = 0; i < CITY_NUM; i++)

        {

            for (int j = 0; j < CITY_NUM; j++)

            {

                double temp1=CityPos[j][0]-CityPos[i][0];

                double temp2=CityPos[j][1]-CityPos[i][1];

                dis[i][j] = sqrt(temp1*temp1+temp2*temp2);

            }

        }

        //﹍て吏挂獺

        //puts("init info");

        for (int i=0; i<CITY_NUM; i++)

        {

            for (int j=0; j<CITY_NUM; j++)

            {

                info[i][j]=1.0;

            }

        }

    }

    //穝獺,讽玡–兵隔獺单筁玂痙獺

    //–柯闷硂Ωǐ筁逞獺

    void Updateinfo()

    {

        //puts("update info");

        double tmpinfo[CITY_NUM][CITY_NUM];

        memset(tmpinfo, 0, sizeof(tmpinfo));

        int m = 0;

        int n = 0;

        //筂菌–唉柯闷

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

            //程カ㎝秨﹍カぇ丁獺

            n = ants[i].Path[0];

            tmpinfo[n][m] = tmpinfo[n][m]+Q/ants[i].length;

            tmpinfo[m][n] = tmpinfo[n][m];

        }



         //穝吏挂獺

         for (int i = 0; i < CITY_NUM; i++)

         {

             for (int j = 0; j < CITY_NUM; j++) {

                //程穝吏挂獺=痙獺+穝痙獺

                info[i][j] = info[i][j]*ROU + tmpinfo[i][j];



             }

         }

    }

    //碝т隔畖TMACΩ

    void Search()

    {



        for (int i = 0; i < TMAC; i++) {

            //printf("current iteration times %d\n", i);

            for (int j = 0; j < ANT_NUM; j++) {

                ants[j].Search();

            }

            //玂程ㄎ挡狦

            for (int j = 0; j < ANT_NUM; j++) {

                if (ant_best.length > ants[j].length) {

                    ant_best = ants[j];

                }

            }



            //穝吏挂獺

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

    //﹍て闷竤

    tsp.Init();

    //秨﹍琩т

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
