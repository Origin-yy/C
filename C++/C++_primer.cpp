#include <iostream>
#include <vector>
//#include <string>
//#include <cstdlib>
//#include <cctype>  //nullptr
//#include <cstddef> //size_t,ptrdiff_t
//#include <iterator> //begin(),end()
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
  const int m = 0; //m是一个常量表达式，编译时已知且不变，const int n = get_size()不是，运行时才知道值。
  constexpr int mf = 10; //声明为constexpr的变量一定是一个常量，必须用常量表达式（值不变，编译过程中就得到结果）初始化
  using zhengxing = int; 
  typedef char *pstring;
  const pstring cstr = 0; //不要替换为原样，这里是声明一个指向char的指针常量（指针不可修改），而不是指向的char不可修改
  struct sale{
    string bookname;  //默认初始化，类内初始值，不能用
    int id = 0;
  };
  sale a,c;

  // string 初始化
  string s;
  string *ptr = nullptr; //不能把int类型变量赋给指针，即使值为0。
  string s1("this is a string");
  string s2(10, 'c');
  string s3; //空字符串
  string s4 = s1;
  s3 = s2;
  // string s4(s2);
  string s5 = s1;
  // string操作
  if(s1 == s2 || s1.empty() || s2.size() == 0 || s2[4] == 'c')
  {
    getline(cin,s);
    string s7 = s1 + "asdf"; //每个+号两侧的运算对象至少有一个是string
    cout << "string s1中的字符串是" << s1 << '\n' << "对s1做sizeof操作得到: " << sizeof(s1) << endl;
    cin >> s2;
    bool if_empty = s1.empty();
  }
  //反复读取，直到遇到文件结尾
  while (cin >> s)
    cout << s << endl;
  //读取一行输入,读取\n并丢弃，并且终止输入
  string line;
  while (getline(cin, line))//读取一行，包括空白符
    cout << line << endl;
  auto line_t = line.size();
  // auto类型，让编译器来推断类型，这里是string::size_type;
  // s.size()的返回值是一个无符号整数，不要与int相比
  int n = -1; //有符号和无符号在一起，都转为无符号
  //int t = s.size() < n; //几乎肯定为true，负值n会转为一个比较大的无符号值

  //范围for语句， 想要修改string中字符的值，要用引用
  for(auto &c :s1){
    c = toupper(c);
  }
  string::size_type index = 0;//下标类型，无符号整数

  //decltype关键字
  decltype(s.size()) cnt = 0; //根据（）里变量的类型为类型

  // vector模板
  vector<int> ivec(10,2);
  vector<int> svec(10);  //十个元素，每个初始化为0，值初始化，各种初始化详见p89
  vector<vector<string> > file{{"asdf"," qwer","qsfe"},{"esed"}};
  //.push_back()把元素放到vector尾端
  vector<string> words;
  for(int i = 0; i<10; i++){
    string buf = "asdf";
    words.push_back(buf);
  }
  //迭代器指向容器中的某个元素
  vector<string>::iterator e =words.end(); //指向容器的尾后元素,end返回的不能解引用或递增减
  for(auto it = words.begin();it != words.end() && !isspace((*it)[0]);++it)
    (*it)[0] = toupper((*it)[0]);

  //迭代器二分搜索
  vector<int> text{1,2,3,4,5,6,7,8,9,10};
  int sought = 8;
  auto beg1 = text.begin(),end1 = text.end();
  auto mid = text.begin() + (end1 - beg1)/2;   //中间点
  while (mid != end1 && *mid != sought){
    if(sought < *mid)
      end1 = mid;
    else 
      beg1 = mid + 1;
    mid = beg1 + (end1 - beg1)/2;
  }
  //数组
  char ch[] = "C++";//自动补‘\0’
  int ia[mf] = {0,1,2,3,4,5,6,7,8,9};  //数组维度必须是常量表达式
  size_t nu = 0; //数组下标类型
  int *beg = begin(ia); //标准库函数begin和end返回数组头尾（下一个位置）的指针
  int *last = end(ia);  //指向尾元素下一个位置的指针，不存在元素，但可以得到地址，不能解引用，或者递增
  //内置（数组）的下标可以是负值，vector和string是无符号
  //const char *buf = s.c_str（）;  string的成员函数c_str把string类转为字符串（返回const char*）
  vector<int> wvec(begin(ia),end(ia)); //用数组初始化vector，给他收尾指针
  //范围for处理多维数组都用引用

  void* p = &s;
  string* q = static_cast<string*>(p);   //强制类型转换



  return 0;
}
