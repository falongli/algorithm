#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <string>
#include <xstddef>
using namespace std;

void algorithm()
{
	// all_of, any_of, none_of, adjacent_find, for_each, count, count_if
	vector<string> vecString(10, "a");
	bool bValue = all_of(vecString.begin(), vecString.end(), [](string str){return str.compare("a") == 0; });
	vector<string>::iterator itor = adjacent_find(vecString.begin(), vecString.end(), [](string str1, string str2){return str1 == str2; });
	if (itor != vecString.end())
		cout << *itor << endl;
	for_each(vecString.begin(), vecString.end(), [](string str){ cout << str << endl; });
	cout<<count(vecString.begin(), vecString.end(), "b")<<endl;
	cout << count_if(vecString.begin(), vecString.end(), [](string str){return str.compare("a") == 0; }) << endl;

	vector<int> vecInt1(10, 1);
	//目标数组必须要要初始化大小  copy, copy_if, copy_n, copy_backward
	vector<int> vecInt2(10);
	vector<int>::iterator iter = copy(vecInt1.begin(), vecInt1.end(), vecInt2.begin());
	for_each(vecInt2.begin(), vecInt2.end(), [](int nValue){ cout << nValue; });
	bool bResult = iter == vecInt2.end();
	cout << endl;

	vecInt2.clear();
	vecInt2.resize(10);
	//move 左值变为右值，原有变量被移动部分为未定义
	vecInt2 = move(vecInt1);
	for_each(vecInt2.begin(), vecInt2.end(), [](int nValue){cout << " " << nValue; });
	cout << endl;
}



//std::bind1st\bind2nd
class Sum : public std::binary_function<int, int, void>
{
public:
    void operator()(int a, int b) const
    {
        std::cout << a + b << std::endl;
    }
};

void test_bind1st()
{
    Sum sum;
    vector<int> vecOrg {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::for_each(vecOrg.begin(), vecOrg.end(), std::bind1st(sum, 1));
}

void test_bind2nd()
{
    auto selfMinus = [&](int nValue)
    {
        std::cout << (std::bind2nd(std::minus<int>(), 1))(nValue) << std::endl;
    };
    vector<int> vecOrg{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    std::for_each(vecOrg.begin(), vecOrg.end(), selfMinus);
}

//std::mem_func/mee_fun_ref
class MemFuncTest
{
public:
    void func(int nValue)
    {
        std::cout << nValue << std::endl;
    }
};

void test_mem_func()
{
    MemFuncTest mem;
    vector<int> vecOrg{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }; 
    std::for_each(vecOrg.begin(), vecOrg.end(), std::bind1st(std::mem_fun(&MemFuncTest::func), &mem));
}

//std::ptr_fun
void add(int a, int b)
{
    std::cout << a + b << std::endl;
}

void test_ptr_fun()
{
    vector<int> vecOrg{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    std::for_each(vecOrg.begin(), vecOrg.end(), std::bind1st(std::ptr_fun(add), 2));
}

//remove_copy
void test_remove_copy_if()
{
    std::vector<int> vecOrg(10);
    std::generate(vecOrg.begin(), vecOrg.end(), std::rand);
    
    std::vector<int> vedDes(10);
    std::remove_copy_if(vecOrg.begin(), vecOrg.end(), vedDes.begin(), std::bind2nd(std::less<int>(), 100));
    std::cout << "des:" << std::endl;
    std::for_each(vedDes.begin(), vedDes.end(), [](int nValue) {std::cout << nValue << std::endl; });
    std::cout << "org:" << std::endl;
    std::for_each(vecOrg.begin(), vecOrg.end(), [](int nValue) {std::cout << nValue << std::endl; });
}

int main()
{
    //1.函数对象适配器
    //test_bind1st();
    //test_bind2nd();
    //test_mem_func();
    //test_ptr_fun();
    //2.vector deque list/stack queue(装饰性容器内部均使用deque实现，可以更改)/map multimap set multiset 关联式容器
    //3.for_each find find_if adjacent_find find_first_of count count_if mismatch equal search 非变易算法，不改变容器内部的值
    //4.变易算法 copy copy_if copy_backward roate tansfrom reverse fill generate remove remove_if remove_copy remove_copy_if 
    //5.排序算法
    //test_remove_copy_if();
    system("pause");
    return 0;
}