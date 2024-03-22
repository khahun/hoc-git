#include<iostream>
using namespace std;
struct node {
	int data;
	node *left;
	node *right;
};
typedef struct node NODE;
typedef NODE* Tree;
//hàm khởi tạo cây nhị phân tìm kiếm 
void KhoiTaoCay(Tree &t)
{
	t = NULL;
}
//ham them 1 phan tu vao cay
void ThemNodeVaoCay(Tree &t, int x)
{
	if (t == NULL)
	{
		NODE *p = new node;
		p->data = x;
		p->left = NULL;
		p->right = NULL;
		t = p;
	}
	else
	{
		if (x < t->data)
		{
			ThemNodeVaoCay(t->left, x);
		}
		else if (x> t->data)
		{
			ThemNodeVaoCay(t->right, x);
		}
	}

}

//ham xuat phan tu tren cay
void Duyetcay(Tree t)
{
	if (t != NULL)
	{
		cout << t->data << "   ";
		Duyetcay(t->left);
		Duyetcay(t->right);
	}
}
bool Kiemtrasochan(int n)
{
	if (n % 2 == 0)
		return 1;
	else
		return 0;
}
// Hàm đếm số lượng phần tử chẵn trên cây nhị phân
int DemPtuChan(Tree t, int &dem)
{
	if (t != NULL)
	{
		if (Kiemtrasochan(t->data) == true)
		{
			dem++;
		}
		DemPtuChan(t->left, dem);
		DemPtuChan(t->right, dem);
	}
	return 0;
}
void Menu(Tree &t)
{
	int luachon;
	while (true)
	{
		system("cls");
		cout << "\n\n\t\t -----------------MENU-----------------";
		cout << "\n1. Nhap phan tu vao cay";
		cout << "\n2. Xuat phan tu tren cay";
		cout << "\n3. Dem so phan tu chan tren cay";
		cout << "\n0. Thoat";
		cout << "\nNhap lua chon cua ban: ";
		cin >> luachon;
		if (luachon == 1)
		{
			int x;
			cout << "\nNhap gia tri: ";
			cin >> x;
			ThemNodeVaoCay(t, x);
		}
		else if (luachon == 2)
		{
			cout << "\n Cay nhi phan tim kiem la: ";
			Duyetcay(t);
			system("pause");
		}
		else if (luachon == 3)
		{
			int dem = 0;
			DemPtuChan(t, dem);
			cout << "\nSo phan tu chan tren cay la: " << dem;
			system("pause");
		}
		else
		{
			break;
		}

	}
}
int main()
{
	Tree t;
	KhoiTaoCay(t);
	Menu(t);
	cout << "\n----------------------";
	system("pause");
	return 0;
}

