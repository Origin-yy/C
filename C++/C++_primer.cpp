#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

extern const int i = 123; // a文件里定义并初始化i，加extern使其能被其他文件使用

using namespace std; //头文件不应包含using声明（名字冲突）

#ifdef MIN
#define MKSTR(x) #x       //"x"
#endif

#ifndef MIN
#define MIN(a, b) (a < b ? a : b)
#define concat(a, B) a##b // xy
#endif

int main() {
  extern const int i; //a文件里声明i而非定义i，extern又表示i并非本文件独有，他的定义将在别处出现
  int const &ref = i; //引用必须初始化,用于初始化引用的必须是一个对象,且只能绑定一个。
  // 引用只是创建一个别名，没有创建对象，没有引用的引用。
  // const的值必须初始化，只在当前所在文件内有效，不同文件不共享
  // 在每个文件的每个const前加extern就可以共享一个，包括定义
  constexpr int mf = 20; //声明为constexpr的变量一定是一个常量，必须用常量表达式（值不变，编译过程中就得到结果）初始化
  using zhengxing = int; 
  typedef char *pstring;
  const pstring cstr = 0; //不要替换为原样，这里是声明一个指向char的指针常量（指针不可修改），而不是指向的char不可修改
  struct sale{
    string bookname = nullptr;  //默认初始化，类内初始值，不能用（）
    int id = 0;
  };
  sale a,b,c;
  // string 初始化
  string s;
  string *ptr = nullptr; //不能把int类型变量赋给指针，即使值为0。
  string s1("value");
  string s2(10, 'c');
  string s3; //空字符串
  string s4 = s1;
  s3 = s2;
  // string s4(s2);
  string s5 = s1;
  // string操作
  s1 + s2;
  // s1 == s2;
  int num = s.size();

  cout << s1;
  cin >> s2;
  getline(cin, s1);
  bool if_empty = s.empty();
  // int num = s.size();
  cin >> s;
  //当读取的不是一个字符串，或者遇到文件结尾，就退出循环
  while (cin >> s)
    cout << s << endl;
  //读取一行输入，直到回车，且不包含回车
  string line;
  while (getline(cin, line))
    cout << line << endl;
  // auto line = line.size();
  // //auto类型，让编译器来推断类型，这里是string::size_type;
  // s.size()的返回值是一个无符号整数，不要与int相比
  int n = -1; //有符号和无符号在一起，都转为无符号
  int t = s.size() < n; //几乎肯定为true，负值n会转为一个比较大的无符号值

  // vector末班
  vector<int> ivec;
  vector<vector<string>> file;

  return 0;
}
