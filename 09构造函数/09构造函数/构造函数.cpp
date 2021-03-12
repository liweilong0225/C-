#include<iostream>
#include<string>
using namespace std;

class CPerson
{
private:
	int m_nAge;
	bool m_nSex;
	string m_strName;
public:
	CPerson()
	{
		m_nAge = 1;
		m_nSex = true;
		m_strName = "Bob";
	}
	CPerson(int i,bool j,string str)
	{
		m_nAge = i;
		m_nSex = j;
		m_strName = str;
	}
public:
	void Show()
	{
		cout<<m_nAge<<endl;
		cout<<m_nSex<<endl;
		cout<<m_strName<<endl;
	}
};
int main()
{
	CPerson ps;
	ps.Show();

	CPerson ps1(1,true,"Tom");
	ps1.Show();
	system("pause");
	return 0;
}