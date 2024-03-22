#include <stdio.h>
#include <conio.h>
#include <string.h>
#define Max 50
struct tailieu
{
	char matl[10], tentl[100];
	float thechap, dongia;
	int songay;
};
void nhaptl(tailieu a[], int& n)
{
	FILE* f;
	f = fopen("dstailieu.txt", "r");
	if (f == NULL)
		printf("Khong mo duoc File");
	fscanf(f, "%d\n", &n);
	for (int i = 0; i < n; i++)
	{
		fscanf(f, "%[^#]#", &a[i].matl);
		fscanf(f, "%[^#]#", &a[i].tentl);
		fscanf(f, "%d#", &a[i].songay);
		fscanf(f, "%f\n", &a[i].dongia);
	}
}
void thechaptl(tailieu a[], int n)
{
	//tinh the chap cua tat ca cac tai lieu
	for (int i = 0; i < n; i++)
	{
		a[i].thechap = ((a[i].dongia * 120) / 100);
	}
}
float tienthechap(tailieu x)
{
	//tinh the chap cua 1 tai lieu
	return ((x.dongia) * 120) / 100;
}
float tongthechap(tailieu a[], int n)
{
	float sum = 0;
	for (int i = 0; i < n; i++)
	{
		sum = sum + tienthechap(a[i]);
	}
	return sum;
}
void sapxep(tailieu a[], int n)
{
	for (int i = 1; i < n; i++)
	{
		tailieu x = a[i];
		for (int j = i - 1; (j >= 0 && a[j].dongia < x.dongia); j--)
		{
			a[j + 1] = a[j];
			a[j] = x;
		}
	}
}
void xuattlthechapnhat(tailieu a[], int n)
{
	for (int i = 1; i < n; i++)
	{
		tailieu x = a[i];
		for (int j = i - 1; (j >= 0 && a[j].thechap < x.thechap); j--)
		{
			a[j + 1] = a[j];
			a[j] = x;
		}
	}
	printf("\t\tTAI LIEU CO TIEN THE CHAP CAO NHAT: \n");
	printf("\nMa TL \t\t Ten TL \t\t\t\t So ngay muon \t Don gia \t Tien the chap\n");
	printf("\n%s \t %s \t\t %d \t\t %.3f \t %.3f\n\n", a[0].matl, a[0].tentl, a[0].songay, a[0].dongia, tienthechap(a[0]));
}
void timtl(tailieu a[], int n)
{
	char tlcantim[10];
	int dem = 0;
	fflush(stdin);
	printf("Nhap ma tai lieu can tim:");
	scanf("%s", &tlcantim);
	for (int i = 0; i < n; i++)
	{
		if (strcmpi(a[i].matl, tlcantim) == 0)
		{
			dem = dem + 1;
			printf("\n\tKet qua do tim: Co ton tai tai lieu\n\n");
		}
	}
	if (dem == 0)
		printf("\n\tKet qua do tim: Khong tim thay tai lieu\n\n");

}
void xuattl(tailieu a[], int n)
{
	printf("\nMa TL \t\t Ten TL \t\t\t\t So ngay muon \t Don gia \t Tien the chap\n");
	for (int i = 0; i < n; i++)
	{
		printf("\n%s \t %s \t\t %d \t\t %.3f \t %.3f\n", a[i].matl, a[i].tentl, a[i].songay, a[i].dongia, tienthechap(a[i]));
	}
}
void sttxuattl(tailieu a[], int n)
{
	//in ra danh sach kem so thu tu de chon
	printf("\n   Ma TL \t\t Ten TL \t\t\t\t So ngay muon \t Don gia \t Tien the chap\n");
	for (int i = 0; i < n; i++)
	{
		printf("\n %d. %s \t %s \t\t\t\t %d \t %.3f \t %.3f\n", i + 1, a[i].matl, a[i].tentl, a[i].songay, a[i].dongia, tienthechap(a[i]));
	}
}
void main()
{
	tailieu a[Max];
	int n, luachon;
	nhaptl(a, n);
	printf("--------------THUC HIEN BOI NGUYEN VAN KHANH_VU BA NHAT KHANG_NGUYEN HUU KHANH----------------");
	do
	{
		fflush(stdin);
		printf("\n=====================================================\n");
		printf("\t\tMENU\n");
		printf("1.Tinh tien the chap cua mot tai lieu\n");
		printf("2.Xuat thong tin cua tat ca tai lieu duoc muon\n");
		printf("3.Tinh tong tien the chap cua tat ca cac tai lieu\n");
		printf("4.Sap xep danh sach tai lieu giam dan theo don gia\n");
		printf("5.Xuat thong tin cua tai lieu co tien the chap cao nhat\n");
		printf("6.Tim tai lieu co ma la x\n");
		printf("7.Thoat chuong trinh\n");

		printf("Moi nhap lua chon: ");
		scanf("%d", &luachon);

		switch (luachon)
		{
		case 1:
			int b;
			sttxuattl(a, n);
			printf("Nhap so thu tu cua tai lieu muon tinh tien the chap:");
			scanf("%d", &b);
			if (b == 0)
				printf("Tai lieu ban chon khong ton tai\n\n");
			else if (b>n)
				printf("Tai lieu ban chon khong ton tai\n\n");
			else
				printf("Tien the chap cua tai lieu '%s' la: % f\n\n", a[b - 1].tentl, tienthechap(a[b - 1]));
			break;
		case 2:printf("\t\t\t\tDANH SACH TAI LIEU DA MUON\n"); xuattl(a, n); break;
		case 3:printf("\tTong tien the chap la: %f\n", tongthechap(a, n)); break;
		case 4:printf("\t\t\tDANH SACH SAP XEP THEO THU TU GIAM DAN CUA TIEN THE CHAP\n"); sapxep(a, n); xuattl(a, n); break;
		case 5:thechaptl(a, n); xuattlthechapnhat(a, n); break;
		case 6:timtl(a, n); break;
		case 7:printf("Thoat chuong trinh\n"); break;
		default:
			printf("\nBan nhap sai!!!!!!!!!!");
			break;
		}
	} while (luachon<7);
	getch();

}