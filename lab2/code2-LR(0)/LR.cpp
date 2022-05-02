#include<iostream>
#include<string>
#include<stack>
#include<vector>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<utility>

using namespace std;


struct Gene{			// generator产生式
    char left;
    char* right;
};
vector<Gene> gene;

typedef struct action{	// Action表
    char para;
    int val;
}Action;

Action action[][16]={
    {{'S',1},{'O',0},{'O',0},{'O',0},{'O',0},{'S',5},{'O',0},{'O',0}},
    {{'O',0},{'R',8},{'R',8},{'R',8},{'R',8},{'O',0},{'R',8},{'R',8}},
    {{'O',0},{'S',6},{'S',7},{'O',0},{'O',0},{'O',0},{'O',0},{'A',0}},
    {{'O',0},{'R',3},{'R',3},{'S',8},{'S',9},{'O',0},{'R',3},{'R',3}},
    {{'O',0},{'R',6},{'R',6},{'R',6},{'R',6},{'O',0},{'R',6},{'R',6}},
    {{'S',1},{'O',0},{'O',0},{'O',0},{'O',0},{'S',5},{'O',0},{'O',0}},
    {{'S',1},{'O',0},{'O',0},{'O',0},{'O',0},{'S',5},{'O',0},{'O',0}},
    {{'S',1},{'O',0},{'O',0},{'O',0},{'O',0},{'S',5},{'O',0},{'O',0}},
    {{'S',1},{'O',0},{'O',0},{'O',0},{'O',0},{'S',5},{'O',0},{'O',0}},
    {{'S',1},{'O',0},{'O',0},{'O',0},{'O',0},{'S',5},{'O',0},{'O',0}},
    {{'O',0},{'R',5},{'R',5},{'R',5},{'R',5},{'O',0},{'R',5},{'R',5}},
    {{'O',0},{'R',4},{'R',4},{'R',4},{'R',4},{'O',0},{'R',4},{'R',4}},
    {{'O',0},{'R',7},{'R',7},{'R',7},{'R',7},{'O',0},{'R',7},{'R',7}},
    {{'O',0},{'R',1},{'R',1},{'S',8},{'S',9},{'O',0},{'R',1},{'R',1}},
	{{'O',0},{'R',2},{'R',2},{'S',8},{'S',9},{'O',0},{'R',2},{'R',2}},
    {{'O',0},{'S',6},{'S',7},{'O',0},{'O',0},{'O',0},{'S',12},{'O',0}},
};

//转移表goto
int Goto[3][10];
int num;//词法分析得到的单词个数
string Vn = "ETF";//非终结符


int i=0,j=0;
bool flag=0;
string input_str;		// 输入串
string ch;
stack<string>s;
vector< pair<int,char> > str;

void Get_G()			// 增广文法G
{
    Gene gen;
    gen.left= 'S';
    gen.right = (char*)"E";
    gene.push_back (gen);                        

    gen.left = 'E';
    gen.right = (char*)"E+T";
    gene.push_back (gen);
    gen.right = (char*)"E-T";
    gene.push_back (gen);
    gen.right = (char*)"T";
    gene.push_back (gen);

    gen.left = 'T';
    gen.right = (char*)"T*F";
    gene.push_back (gen);
    gen.right = (char*)"T/F";
    gene.push_back (gen);
    gen.right = (char*)"F";
    gene.push_back (gen);   

    gen.left = 'F';
    gen.right = (char*)"(E)";
    gene.push_back (gen);
    gen.right = (char*)"I";
    gene.push_back (gen);

}

void Init_Goto()	// 初始化GOTO表
{
    Goto[0][0]=2; Goto[0][1]=3; Goto[0][2]=4; 
    Goto[5][0]=15;Goto[5][1]=3; Goto[5][2]=4;
    Goto[6][1]=13;Goto[6][2]=4;
	Goto[7][1]=14;Goto[7][2]=4;
    Goto[8][2]=11;Goto[9][2]=10;
}


void String_to_Token()
{
	int i=0;
	while(i<(int)input_str.size())
	{
		if(input_str[i] == ' ')
            i++;
		else if( (input_str[i]>='a'&&input_str[i]<='z') || (input_str[i]>='A'&&input_str[i]<='Z') || (input_str[i]>='0'&&input_str[i]<='9') )
		{
			string tmp;
			for(;i<(int)input_str.size();i++)
			{
				if(!((input_str[i]>='a'&&input_str[i]<='z') || (input_str[i]>='A'&&input_str[i]<='Z') || (input_str[i]>='0'&&input_str[i]<='9') || (input_str[i]=='.')))
                    break;
				else
					tmp.push_back(input_str[i]);
			}
			str.push_back(make_pair(0,'I'));
		}
		else
		{
			string tmp;
			tmp.push_back(input_str[i]);
			int type;
			switch(input_str[i])
            {
				case '+':
					type = 1;
					break;
				case '-':
					type = 2;
					break;
				case '*':
					type = 3;
					break;
				case '/':
					type = 4;
					break;
				case '(':
					type = 5;
					break;
				case ')':
					type = 6;
					break;
				case '#':
					type = 7;
					break;
				default:
					type = 8;
					printf("Error: Unrecognized characters!\n"); 
					break;
        }
			str.push_back(make_pair(type,input_str[i]));
			i++;
		}
	}
}

int LR_Analysis(int num)	// num为输入单词个数
{
	int flag = 0;
	Init_Goto(); 
    Get_G();
               
    vector<int> state;		// 状态栈
    vector<char> ana;		// 分析栈
    vector<char> an;		// 输入栈
    state.push_back(0);	// 初始化栈
    ana.push_back('#');
    int i,j;
    int k=0;
    do{
        i = state[state.size()-1];  // state top      
        j = str[k].first;			// input top
        if(j==8)
            return 0;
        
        if(action[i][j].para == 'O')
            return 0;
        else if(action[i][j].para == 'S')	// 移进状态
        {                                                                       
            state.push_back(action[i][j].val);    
            ana.push_back(str[k].second);   
            an.push_back(str[k].second);
            k++;                         
        }
        else if(action[i][j].para == 'R')	// 归约状态
        {                                                               
            int tem = action[i][j].val;
			int len = strlen(gene[tem].right);
           
            while(len != 0)					// 将分析栈中的待约项规约
            {
                state.pop_back ();                          
                ana.pop_back ();                    
                len--;
            }
            
            ana.push_back(gene[action[i][j].val].left);  // 规约后的表达式入栈  
            int a = state[state.size()-1];		// 状态栈栈顶            
            char b = ana[ana.size()-1]; 		// 分析栈栈顶       
            int dex = 0;
            while(Vn[dex]!=b)
                dex++;                                  
            if(Goto[a][dex]==0)
                return 0;
            else
                state.push_back(Goto[a][dex]);         
        }
        else if(action[i][j].para=='A')
        {
            flag = 1;
            break;
        }
    }while(true);

	return flag;
}

int main() //LR(0)方法
{
	freopen("test.txt","r",stdin);
    freopen("output2.txt","w",stdout); //文件读写操作
	input_str.clear();

	Init_Goto(); 
    Get_G(); 

	while(getline(cin,input_str))
	{
		i=0;
        flag=0;
        str.clear();
		cout << input_str <<endl;
		String_to_Token();			//将输入串转换为TOKEN串

		int num = (int)str.size();
   
		flag = LR_Analysis(num);

		if(flag ==1)
			printf("Yes\n");
		else
			printf("No, Error: Parsing error!\n");

	}
	return 0;
}
