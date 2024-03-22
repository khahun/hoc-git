#include<iostream>
using namespace std;
#include<string>
#include<fstream>
#define Max 100
struct DATE
{
	int day;
	int month;
	int year;
};
void doc_nagythangnam(ifstream &filein, DATE& date)
{
	filein >> date.day;
	filein.seekg(1, 1);
	filein >> date.month;
	filein.seekg(1, 1);
	filein >> date.year;
}
struct hocvien
{
	string mahv, ten, holot, malop;
	float diem;
	DATE ngaysinh;
};
typedef struct hocvien HOCVIEN;
struct lophoc
{
	string malop, tenlop, lichhoc;
	int hocphi;
};
typedef struct lophoc LOPHOC;
struct node
{	
	HOCVIEN data; //du lieu cua node
	struct node *pNext;
};
typedef struct node NODE;
struct Nodelh
{
	LOPHOC data; //du lieu cua node
	struct Nodelh *pNext;
};
typedef struct Nodelh NODELH;
struct list
{
	NODE *pHead;
	NODE *pTail;
};
typedef struct list LIST;
struct listlophoc
{
	NODELH *pHead;
	NODELH *pTail;
};
typedef struct listlophoc  LISTLH;
//hàm khởi tạo danh sách liên kết đơn
void Khoitaodanhsach(LIST & k)
{
	k.pHead = NULL;
	k.pTail = NULL;
}
void KhoitaodanhsachLH(LISTLH & k)
{
	k.pHead = NULL;
	k.pTail = NULL;
}
NODE *Khoitaonode(HOCVIEN  n)
{
	NODE *p = new NODE;
	if (p == NULL)
	{
		cout << "\nCap phat that bai !";
		return NULL;
	}
	p->data = n;
	p->pNext = NULL;
	return p;
}
NODELH *KhoitaonodeLH(LOPHOC  x)
{
	NODELH *p = new NODELH;
	if (p == NULL)
	{
		cout << "\nCap phat that bai !";
		return NULL;
	}
	p->data = x;
	p->pNext = NULL;
	return p;
}
typedef struct ds_hv
{
	NODE *pHead = NULL;
	NODE *pTail = NULL;
}ds_hv;
void DocThongTinClass(ifstream& file_class, LOPHOC& x)
{
	getline(file_class, x.malop, ',');
	file_class.seekg(1, 1);
	getline(file_class, x.tenlop, ',');
	file_class.seekg(1, 1);
	getline(file_class, x.lichhoc, ',');
	file_class.seekg(1, 1);
	file_class >> x.hocphi;
	string temp;
	getline(file_class, temp);
}
void ThemcuoiLH(LISTLH &l, NODELH *p)
{
	if (l.pHead == NULL)
	{
		l.pHead = l.pTail = p;
	}
	else
	{
		l.pTail->pNext = p;
		l.pTail = p;
	}
}


void DanhsachClass(listlophoc&l, ifstream& file_class)
{
	while (!file_class.eof())
	{
		LOPHOC ds;
		DocThongTinClass(file_class, ds);
		ThemcuoiLH(l, KhoitaonodeLH(ds));
	}
	file_class.close();
}
void Themdau(LIST &l, NODE *p)
{
	if (l.pHead == NULL)
	{
		l.pHead = l.pTail = p;
		l.pHead = p;
	}
}
void Themcuoi(LIST &l, NODE *p)
{
	if (l.pHead == NULL)
	{
		l.pHead = l.pTail = p;
	}
	else
	{
		l.pTail->pNext = p;
		l.pTail = p;
	}
}
void doc_thongtin1hocvien(ifstream &filein,	HOCVIEN &hv)
{
	getline(filein, hv.mahv, ',');
	filein.seekg(1, 1);
	getline(filein, hv.holot, ',');
	filein.seekg(1, 1);
	getline(filein, hv.ten, ',');
	filein.seekg(1, 1);
	doc_nagythangnam(filein, hv.ngaysinh);
	filein.seekg(2, 1);
	getline(filein, hv.malop, ',');
	filein.seekg(1, 1);
	filein >> hv.diem;
	string temp;
	getline(filein, temp);
}
void doc_Danhsachhocvien(ifstream &filein, LIST &l)
{
	while (!filein.eof())
	{
		HOCVIEN hv;
		doc_thongtin1hocvien(filein, hv);
		NODE *p = Khoitaonode(hv);
		Themcuoi(l, p);
	}
}
void xuat1hv(HOCVIEN hv)
{
	cout << "\nMaSohocvien: " << hv.mahv;
	cout << "\nHotLothocvien: " << hv.holot;
	cout << "\nTenhocvien: " << hv.ten;
	cout << "\nNgayThangNamSinhhocvien: " << hv.ngaysinh.day << "/" << hv.ngaysinh.month << "/" << hv.ngaysinh.year;
	cout << "\nMaLophocvien: " << hv.malop;
	cout << "\nDiemTBhocvien: " << hv.diem;
}
void xuatdanhsachhocvien(LIST l)
{
	int dem = 1;
	for (NODE *k = l.pHead; k != NULL; k = k->pNext)
	{
		cout << "\n\n\t\t Sinh vien thu " << dem++;
		xuat1hv(k->data);
	}
}
void xuatlophoc(LOPHOC lh)
{
	{
		cout << "\nMaLop: " << lh.malop;
		cout << "\nTenLop: " << lh.tenlop;
		cout << "\nLichHoc: " << lh.lichhoc;
		cout << "\nHocPhi: " << lh.hocphi;
	}
}
void xuatdanhsachlophoc(LISTLH l)
{
	int dem = 1;
	for (NODELH *k = l.pHead; k != NULL; k = k->pNext)
	{
		cout << "\n\n\t\t Lop hoc thu " << dem++;
		xuatlophoc(k->data);
	}
}
void Themhocvien(LIST&l)
{
	HOCVIEN x;
	cout << "\nNhap Ma HV\t: ";
	getline(cin, x.mahv);
	cout << "Nhap Ho Lot\t: ";
	getline(cin, x.holot);
	cout << "Nhap Ten\t: ";
	getline(cin, x.ten);
	cout << "Nhap Ma Lop\t: ";
	getline(cin, x.malop);
	cout << "Nhap Ngay Sinh\t: ";
	cin >> x.ngaysinh.day;
	cout << "Nhap Thang Sinh\t: ";
	cin >> x.ngaysinh.month;
	cout << "Nhap namsinh\t: ";
	cin >> x.ngaysinh.year;
	cout << "Nhap Diem\t: ";
	cin >> x.diem;
	Themcuoi(l, Khoitaonode(x));
}
void ghitthocvien(ofstream &fileout, HOCVIEN hv)
{
	cout << "\nMaSohocvien: " << hv.mahv;
	cout << "\nHotLothocvien: " << hv.holot;
	cout << "\nTenhocvien: " << hv.ten;
	cout << "\nNgayThangNamSinhhocvien: " << hv.ngaysinh.day << "/" << hv.ngaysinh.month << "/" << hv.ngaysinh.year;
	cout << "\nMaLophocvien: " << hv.malop;
	cout << "\nDiemTBhocvien: " << hv.diem;
	cout << "\n";
}
void timtthocviencodiemcaonhat(LIST l)
{
	{
		float max = l.pHead->data.diem;
		for (NODE *k = l.pHead->pNext; k != NULL; k = k->pNext)
		{
			if (max < k->data.diem)
			{
				max = k->data.diem;
			}
		}
		ofstream fileout;
		fileout.open("Diemmax.txt", ios::out);
		for (NODE *k = l.pHead; k != NULL; k = k->pNext)
		{
			if (max == k->data.diem)
			{
				ghitthocvien(fileout, k->data);
			}
		}
		fileout.close();
	}
}
void tim_kiem_mahocvien(LIST l)
{
	string temp;
	cout << "Nhap ma hoc vien can tim:";
	cin >> temp;
	for (NODE *k = l.pHead; k != NULL; k = k->pNext)
	{
		if (k->data.mahv == temp)
		{
			xuat1hv(k->data);
			cout << endl << endl;
		}
	}
}
void tim_kiem_tenlop(LIST l,LISTLH ds)
{
	string temp;
	cout << "Nhap ten lop can tim:";
	getline(cin,temp);
	for (NODELH *k = ds.pHead; k != NULL; k = k->pNext)
	{
		if (k->data.tenlop == temp)
		{
			for (NODE* p= l.pHead; p != NULL; p = p->pNext)
			{
				if (p->data.malop == k->data.malop)
					xuat1hv(p->data);
			}
		}
	}
}
void tim_kiem_namsinhhocvien(LIST l)
{
	int temp;
	cout << "Nhap nam sinh vien can tim:";
	cin >> temp;
	for (NODE *k = l.pHead; k != NULL; k = k->pNext)
	{
		if (k->data.ngaysinh.year == temp)
		{
			xuat1hv(k->data);
			cout << endl << endl;
		}
	}
}
//void timtthocviencohocphicaonhat(LISTLH l)
//{
//	{
//		float max = l.pHead->data.hocphi;
//		for (NODELH *k = l.pHead->pNext; k != NULL; k = k->pNext)
//		{
//			if (max < k->data.hocphi)
//			{
//				max = k->data.hocphi;
//			}
//		}
//		ofstream fileout;
//		fileout.open("Hocphimax.txt", ios::out);
//		for (NODELH *k = l.pHead; k != NULL; k = k->pNext)
//		{
//			if (max == k->data.hocphi)
//			{
//				ghitthocvien(fileout, k->data);
//			}
//		}
//		fileout.close();
//	}
//}

void dshocbong(LIST l)
{
	ofstream fileout;
	fileout.open("dshocbong.txt", ios::out);
	for (NODE *k = l.pHead; k != NULL; k = k->pNext)
	{
		if (k->data.diem >=8)
		{
			ghitthocvien(fileout, k->data);
		}
	}
	fileout.close();
}
void menu2(LIST l, LISTLH ds)
{
	while (true)
	{
		system("cls");
		cout << "\t ---------------TIM KIEM HOC VIEN---------------" << endl;
		cout << "\4.1tTim kiem hoc vien theo ten lop" << endl;
		cout << "\4.2tTim kiem hoc vien theo ma so hoc vien" << endl;
		cout << "\4.3tTim kiem hoc vien theo nam sinh" << endl;
		int chon;
		cin >> chon;
		if (chon == 0)
			break;
		switch (chon)
		{
		case 1: 
			getchar();
			tim_kiem_tenlop(l,ds);
			break;
		case 2: tim_kiem_mahocvien(l);
			break;
		case 3: tim_kiem_namsinhhocvien(l);
			break;
		default: 
			cout << "\nBan da nhap sai xin moi nhap lai" << endl;
			break;
		}
		system("pause");
	}
}
int main()
{
	LIST l;
	LISTLH ds;
	ds_hv dshv;
	KhoitaodanhsachLH(ds);
	Khoitaodanhsach(l);
	ifstream filein, file_class;
	filein.open("hocvien.txt", ios::in);
	doc_Danhsachhocvien(filein, l);
	file_class.open("lophoc.txt", ios::in);
	DanhsachClass(ds, file_class);
	int n, luachon;
	do
	{
		fflush(stdin);
		printf("\t\t\tMENU\n");
		printf("\n|===========================================================|");
		printf("\n|1.Xuat danh sach hoc vien                                  |");
		printf("\n|2.Xuat danh sach lop hoc                                   |");
		printf("\n|3.Them 1 hoc vien vao danh sach                            |");
		printf("\n|4.Tim kiem hoc vien                                        |");
		printf("\n|5.In ra danh sach hoc vien theo ten lop                    |");
		printf("\n|6.Xuat hoc vien co diem cao nhat                           |");
		printf("\n|7.Thong tin cac hoc vien hoc o lop hoc co hoc phi cao nhat |");
		printf("\n|8.Sap xep danh sach hoc vien theo ma lop                   |");
		printf("\n|9.In thong tin hoc vien co diem chua dat                   |");
		printf("\n|10.Xuat danh sach sinh co hoc bong                         |");
		printf("\n|===========================================================|\n");
		printf("\nMoi nhap lua chon:");
		scanf_s("%d", &luachon);
		switch (luachon)
		{
		case 1: printf("\nDANH SACH HOC VIEN:"); xuatdanhsachhocvien(l); break;
		case 2:printf("\nDANH SACH LOP HOC:"); xuatdanhsachlophoc(ds); break;
		case 3:getchar();
			printf("\nNhap thong tin hoc vien can them");
			Themhocvien(l);
			break;
		case 4:
			menu2(l, ds);
			break;
		case 6:printf("\nHoc vien co diem cao nhat:"); timtthocviencodiemcaonhat(l); break;
		case 10:printf("\nDanh sach hoc bong gom co:"); dshocbong(l); break;
		}
	} while (luachon <11);
		filein.close();
		file_class.close();
		system("pause");
		return 0;
}