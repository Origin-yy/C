#include <stdio.h>
#include<stdlib.h>

struct Emp
{
	char ID[10];//职工工号
	char Name[10];//职工姓名
	int age;//职工年龄
};

int main()
{
	/***************found***************/
	struct Emp e[5] = { {"20110102","Kong",36},
					{"20081025","song",41},
					{"19880722","chai",53},
					{"19961210","zhang",48},
					{"19900311","Gong",51} };
	int cnt  = 0;
	int i = 0;

	for (i = 0;i < 5;i++)
		/***************found***************/
		if (e[i].age<45)
		{
			printf("工号：%s\t姓名：%s\t年龄：%d\n", e[i].ID, e[i].Name, e[i].age);
			cnt++;
		}
	printf("年龄在45岁以下的职工数为：%d\n", cnt);

	system("pause");
	return 0;
}
