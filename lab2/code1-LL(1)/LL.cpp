#include<iostream>
#include<string>
#include<stack>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<utility>

using namespace std;


int i=0;
bool flag=0;
string input_str;
string ch;
stack<string>s;
vector< pair<string,char> > str;


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
			str.push_back(make_pair(tmp,'I'));
		}
		else
		{
			string tmp;
			tmp.push_back(input_str[i]);
			str.push_back(make_pair(tmp,input_str[i]));
			i++;
		}
	}
}

int main() //LL(1)方法
{
	freopen("test.txt","r",stdin);
    freopen("output.txt","w",stdout); //文件读写操作
	input_str.clear();

	while(getline(cin,input_str))
	{
		i=0;
        flag=0;
        str.clear();
		cout << input_str <<endl;
		String_to_Token();
        //将输入的串转换为TOKEN串
		s.push("#");
		s.push("E"); //初始化栈

		while(!s.empty() && i<(int)str.size())
		{
			ch=s.top();

			string tmp1;
			tmp1.push_back(str[i].second);

			if(ch=="#")
			{
				if(str[i].second=='#')
                {
                    s.pop();
                    flag=1;
                    break;
                }
				else
					break;
			}
			else if(ch == tmp1)
            {
                s.pop();
                i++;
            }
			else if(ch=="E") //当前栈顶元素为E
			{
				if(str[i].second=='I' || str[i].second=='(')
                {
                    s.pop();
                    s.push("A");
                    s.push("T");
                } //将1号产生式逆序压栈
				else
					break;
			}
			else if(ch=="A") //当前栈顶元素为A
			{
				if(str[i].second=='+')
                {
                    s.pop();
                    s.push("A");s.push("T");s.push("+");
                } //将2号产生式逆序压栈
				else if(str[i].second=='-')
                {
                    s.pop();
                    s.push("A");s.push("T");s.push("-");
                } //3号产生式
				else if(str[i].second==')' || str[i].second=='#'){s.pop();} //4号产生式
				else
					break;
			}
			else if(ch=="T")
			{
				if(str[i].second=='I' || str[i].second=='(')
                {
                    s.pop();
                    s.push("B");
                    s.push("F");
                } //5号产生式
				else
					break;
			}
			else if(ch=="B")
			{
				if(str[i].second=='*')
                {
                    s.pop();
                    s.push("B");s.push("F");s.push("*");
                } //6号产生式
				else if(str[i].second=='/')
                {
                    s.pop();
                    s.push("B");s.push("F");s.push("/");
                } //7号产生式
				else if(str[i].second=='+' || str[i].second=='-' || str[i].second==')' || str[i].second=='#')
                    s.pop(); //8号产生式
				else
					break;
			}
			else if(ch=="F")
			{
				if(str[i].second=='I')
				{
					s.pop();
                    s.push("I");
				} 	//9号产生式
				else if(str[i].second=='(')
                {
                    s.pop();
                    s.push(")");s.push("E");s.push("(");
                } //10号产生式
				else
					break;
			}

		}

		if(flag ==1)
			printf("Yes\n");
		else
			printf("No, Error: Parsing error!\n");

	}
	return 0;
}
