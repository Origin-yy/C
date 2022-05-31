#include <iostream>
#include <string>
#include <vector>

using namespace std;

#ifdef MIN(a, b)(a < b ? a : b)
#define MKSTR(x) #x       //"x"
#endif

#ifndef MIN(a, b)(a < b ? a : b)
#define concat(a, B) a##b // xy
#endif

int main()
{
    // string 初始化
    string s;
    string s1("value");
    string s2(10, 'c');
    string s3; //空字符串
    string s4 = s1;
    s3 = s2;
    string s4(s2);
    string s5 = s1;
    // string操作
    s1 + s2;
    s1 == s2;
    int num = s.size();

    cout << s1;
    cin >> s2;
    getline(cin, s1);
    bool if_empty = s.empty();
    int num = s.size();
    cin >> s;
    //当读取的不是一个字符串，或者遇到文件结尾，就退出循环
    while (cin >> s)
        cout << s << endl;
    //读取一行输入，直到回车，且不包含回车
    string line;
    while (getline(cin,line))
        cout << line << endl;
    auto line = line.size(); //auto类型，让编译器来推断类型，这里是string::size_type;
    //s.size()的返回值是一个无符号整数，不要与int相比
    int n = -1;//有符号和无符号在一起，都转为无符号
    s.size() < n;//几乎肯定为true，负值n会转为一个比较大的无符号值

    //vector末班
    vector<int> ivec;
    vector<vector<string>> file;

    return 0;
}
