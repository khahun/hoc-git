#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include<fstream>

typedef struct DATE
{
	int day;
	int month;
	int year;
}date;

typedef struct hocvien
{
	char mahv[20];
	char holot[30];
	char ten[20];
	DATE ngaysinh;
	char malop[20];
	float diem;
}hv;

typedef struct lophoc
{
	char malop[20];
	char tenlop[20];
	char lichhoc[20];
	float hocphi;
}lophoc;

struct node_hv
{
	hv data;
	struct node_hv* next;
};
typedef struct node_hv node_hv;

typedef struct danhsach_hv
{
	node_hv* Head = NULL;
	node_hv* Tail = NULL;
}danhsach_hv;

struct node_lophoc
{
	lophoc data;
	struct node_lophoc* next;
};
typedef struct node_lophoc node_lophoc;

typedef struct danhsach_lophoc
{
	node_lophoc* Head = NULL;
	node_lophoc* Tail = NULL;
}danhsach_lophoc;

node_hv* Khoi_tao_hv(hv x)
{
	node_hv* p = new node_hv;
	if (p == NULL)
	{
		printf("\nKO cap phat duoc");
		return NULL;
	}
	p->data = x;
	p->next = NULL;
	return p;
}

void them_hocvien(danhsach_hv& ds_hv, hv x)
{
	node_hv* p = Khoi_tao_hv(x);
	if (ds_hv.Head == NULL)
	{
		ds_hv.Head = ds_hv.Tail = p;
	}
	else
	{
		ds_hv.Tail->next = p;
		ds_hv.Tail = p;
	}
}

node_lophoc* Khoi_tao_lophoc(lophoc x)
{
	node_lophoc* p = new node_lophoc;
	if (p == NULL)
	{
		printf("\nKO cap phat duoc");
		return NULL;
	}
	p->data = x;
	p->next = NULL;
	return p;
}

void them_lophoc(danhsach_lophoc& ds_lophoc, lophoc x)
{
	node_lophoc* p = Khoi_tao_lophoc(x);
	if (ds_lophoc.Head == NULL)
	{
		ds_lophoc.Head = ds_lophoc.Tail = p;
	}
	else
	{
		ds_lophoc.Tail->next = p;
		ds_lophoc.Tail = p;
	}
}

void nhap_hocvien(hv& x)
{
	printf("Nhap ma hoc vien: ");
	fgets(x.mahv, 20, stdin);
	x.mahv[strcspn(x.mahv, "\n")] = '\0';

	printf("Nhap ho lot: ");
	fgets(x.holot, 30, stdin);
	x.holot[strcspn(x.holot, "\n")] = '\0';

	printf("Nhap ten: ");
	fgets(x.ten, 20, stdin);
	x.ten[strcspn(x.ten, "\n")] = '\0';

	printf("Nhap ngay sinh (dd/mm/yyyy): ");
	scanf("%d/%d/%d", &x.ngaysinh.day, &x.ngaysinh.month, &x.ngaysinh.year);
	getchar();

	printf("Nhap ma lop: ");
	fgets(x.malop, 20, stdin);
	x.malop[strcspn(x.malop, "\n")] = '\0';

	printf("Nhap diem: ");
	scanf("%f", &x.diem);
	getchar();
}

void xuat_hocvien(hv x)
{
	printf("Ma hoc vien: %s\n", x.mahv);
	printf("Ho lot: %s\n", x.holot);
	printf("Ten: %s\n", x.ten);
	printf("Ngay sinh: %02d/%02d/%d\n", x.ngaysinh.day, x.ngaysinh.month, x.ngaysinh.year);
	printf("Ma lop: %s\n", x.malop);
	printf("Diem: %.1f\n", x.diem);
}

void xuat_ds_hocvien(danhsach_hv ds_hv)
{
	node_hv* p = ds_hv.Head;
	while (p != NULL)
	{
		xuat_hocvien(p->data);
		p = p->next;
		printf("\n");
	}
}

void xuat_danhsach_lophoc(danhsach_lophoc ds_lophoc)
{
	printf("%-20s%-20s%-20s%s\n", "Ma lop", "Ten lop", "Lich hoc", "Hoc phi");
	node_lophoc* p = ds_lophoc.Head;
	while (p != NULL)
	{
		printf("%-20s%-20s%-20s%.f\n", p->data.malop, p->data.tenlop, p->data.lichhoc, p->data.hocphi);
		p = p->next;
	}
}

void doc_danhsach_hocvien(danhsach_hv& ds_hv)
{
	FILE* file = fopen("hocvien.txt", "r+");
	if (file == NULL)
	{
		printf("Loi mo file\n");
		return;
	}

	while (!feof(file))
	{
		hv x;
		char ngaysinh_str[12];
		fscanf(file, "%[^,],%[^,],%[^,],%[^,],%[^,],%f\n", x.mahv, x.holot, x.ten, ngaysinh_str, x.malop, &x.diem);
		sscanf(ngaysinh_str, "%d/%d/%d", &x.ngaysinh.day, &x.ngaysinh.month, &x.ngaysinh.year);
		them_hocvien(ds_hv, x);
	}

	fclose(file);
}

void doc_danhsach_lophoc(char* filename, danhsach_lophoc& ds_lophoc)
{
	FILE* f = fopen(filename, "r+");
	if (f == NULL)
	{
		printf("Khong mo duoc file");
		return;
	}
	char s[255];
	while (fgets(s, 255, f) != NULL)
	{
		lophoc lop;
		char* token = strtok(s, ",");
		strcpy(lop.malop, token);
		token = strtok(NULL, ",");
		strcpy(lop.tenlop, token);
		token = strtok(NULL, ",");
		strcpy(lop.lichhoc, token);
		token = strtok(NULL, ",");
		lop.hocphi = atof(token);
		them_lophoc(ds_lophoc, lop);
	}
}

void tim_kiem_mahocvien(danhsach_hv ds_hv)
{
	char temp[20];
	printf("Nhap ma hoc vien can tim: ");
	scanf("%s", temp);
	node_hv* p = ds_hv.Head;
	while (p != NULL)
	{
		if (strcmp(p->data.mahv, temp) == 0)
		{
			printf("Thong tin hoc vien can tim:\n");
			printf("Ma hoc vien: %s\n", p->data.mahv);
			printf("Ho va ten: %s %s\n", p->data.holot, p->data.ten);
			printf("Ngay sinh: %d/%d/%d\n", p->data.ngaysinh.day, p->data.ngaysinh.month, p->data.ngaysinh.year);
			printf("Ma lop: %s\n", p->data.malop);
			printf("Diem trung binh: %.1f\n", p->data.diem);
			return;
		}
		p = p->next;
	}
	printf("Khong tim thay hoc vien co ma %s\n", temp);
}

void tim_kiem_tenlop(danhsach_hv ds_hv, char malop[])
{
	node_hv* p = ds_hv.Head;
	int flag = 0;
	while (p != NULL)
	{
		if (strcmp(p->data.malop, malop) == 0)
		{
			printf("Thong tin hoc vien:\n");
			printf("Ma hoc vien: %s\n", p->data.mahv);
			printf("Ho va ten: %s %s\n", p->data.holot, p->data.ten);
			printf("Ngay sinh: %d/%d/%d\n", p->data.ngaysinh.day, p->data.ngaysinh.month, p->data.ngaysinh.year);
			printf("Ma lop: %s\n", p->data.malop);
			printf("Diem: %.2f\n", p->data.diem);
			flag = 1;
		}
		p = p->next;
	}
	if (flag == 0)
	{
		printf("Khong tim thay hoc vien nao thuoc lop %s\n", malop);
	}
}


void tim_kiem_namsinh(danhsach_hv l)
{
	int temp;
	printf("Nhap nam sinh vien can tim: ");
	scanf("%d", &temp);
	node_hv *k;
	for (k = l.Head; k != NULL; k = k->next)
	{
		if (k->data.ngaysinh.day == temp)
		{
			printf("Ma HV: %s\n", k->data.mahv);
			printf("Ho lot: %s\n", k->data.holot);
			printf("Ten: %s\n", k->data.ten);
			printf("Ngay sinh: %d/%d/%d\n", k->data.ngaysinh.day, k->data.ngaysinh.month, k->data.ngaysinh.year);
			printf("Ma lop: %s\n", k->data.malop);
			printf("Diem: %.1f\n", k->data.diem);
			printf("\n");
		}
		printf("\nKhong tim thay nam sinh trung khop%s", temp);
	}
}

void menu2(danhsach_hv ds_hv, danhsach_lophoc ds_lophoc)
{
	while (true)
	{
		printf("1. Tim kiem theo ma hoc vien\n");
		printf("2. Tim kiem theo ten lop\n");
		printf("3. Tim kiem theo nam sinh\n");
		printf("\n");
		printf("Chon: ");
		int chon;
		scanf("%d", &chon);
		if (chon == 0)
			break;
		switch (chon)
		{
		case 1:
			tim_kiem_mahocvien(ds_hv);
			break;
		case 2:
			char malop[20];
			printf("Nhap ma lop: ");
			scanf("%s", malop);
			getchar();
			tim_kiem_tenlop(ds_hv, malop);
			break;
		case 3:
			tim_kiem_namsinh(ds_hv);
			break;
		default:
			printf("Ban nhap sai roi vui long nhap lai\n");
			break;
		}
	}
}

void InDanhSachHocVienTheoLop(danhsach_hv ds_hv)
{
	int i, n;
	printf("Nhap so luong lop: ");
	scanf("%d", &n);
	char tenlop[20];

	for (i = 1; i <= n; i++) {
		printf("\nNhap ten lop thu %d: ", i);
		fflush(stdin);
		gets(tenlop);

		printf("|==========Danh sach hoc vien cua lop %s :==========|\n", tenlop);
		node_hv* p = ds_hv.Head;
		while (p != NULL)
		{
			if (strcmp(p->data.malop, tenlop) == 0)
			{
				printf("\n");
				printf("\tMa HV: %s\n", p->data.mahv);
				printf("\tHo va ten: %s %s\n", p->data.holot, p->data.ten);
				printf("\tNgay sinh: %d/%d/%d\n", p->data.ngaysinh.day, p->data.ngaysinh.month, p->data.ngaysinh.year);
				printf("\tMa lop: %s\n", p->data.malop);
				printf("\tDiem: %.2f\n", p->data.diem);
				printf("\n");
			}
			p = p->next;
		}
		printf("|======================================================|\n");
	}
}

void TimHocVienDiemCaoNhat(danhsach_hv ds_hv)
{
	float diem_cao_nhat = -1;
	node_hv* node_hv_cao_nhat = NULL;
	node_hv* p = ds_hv.Head;

	while (p != NULL)
	{
		if (p->data.diem > diem_cao_nhat)
		{
			diem_cao_nhat = p->data.diem;
			node_hv_cao_nhat = p;
		}
		p = p->next;
	}

	printf("Danh sach hoc vien diem cao nhat:\n");
	p = ds_hv.Head;
	while (p != NULL)
	{
		if (p->data.diem == diem_cao_nhat)
		{
			printf("Ma HV: %s\n", p->data.mahv);
			printf("Ho va ten: %s %s\n", p->data.holot, p->data.ten);
			printf("Ngay sinh: %d/%d/%d\n", p->data.ngaysinh.day, p->data.ngaysinh.month, p->data.ngaysinh.year);
			printf("Ma lop: %s\n", p->data.malop);
			printf("Diem: %f\n", p->data.diem);
			printf("\n");
		}
		p = p->next;
	}
}

void TimHVHocLopHocPhiCaoNhat(danhsach_hv ds_hv, danhsach_lophoc ds_lh)
{
	if (ds_hv.Head == NULL || ds_lh.Head == NULL)
	{
		printf("Danh sach hoc vien hoac danh sach lop hoc rong!\n");
		return;
	}

	node_lophoc* node_lh_max = ds_lh.Head;
	float max_hp = node_lh_max->data.hocphi;
	for (node_lophoc* node_lh = ds_lh.Head->next; node_lh != NULL; node_lh = node_lh->next)
	{
		if (node_lh->data.hocphi > max_hp)
		{
			node_lh_max = node_lh;
			max_hp = node_lh->data.hocphi;
		}
	}

	int found = 0;
	for (node_hv* node_hv = ds_hv.Head; node_hv != NULL; node_hv = node_hv->next)
	{
		if (strcmp(node_hv->data.malop, node_lh_max->data.malop) == 0)
		{
			found = 1;
			printf("Ma HV: %s\n", node_hv->data.mahv);
			printf("Ho va ten: %s %s\n", node_hv->data.holot, node_hv->data.ten);
			printf("Ngay sinh: %d/%d/%d\n", node_hv->data.ngaysinh.day, node_hv->data.ngaysinh.month, node_hv->data.ngaysinh.year);
			printf("Ma lop: %s\n", node_hv->data.malop);
			printf("Diem: %.2f\n", node_hv->data.diem);
		}
	}
	if (!found)
	{
		printf("Khong tim thay hoc vien nao trong lop co hoc phi cao nhat.\n");
	}
}

void SapXepHVTheoMaLopVaDiemGiamDan(danhsach_hv &ds)
{
	node_hv* p, *q;
	hv tmp;
	for (p = ds.Head; p != NULL; p = p->next)
	{
		for (q = p->next; q != NULL; q = q->next)
		{
			if (strcmp(p->data.malop, q->data.malop) > 0 || (strcmp(p->data.malop, q->data.malop) == 0 && p->data.diem < q->data.diem))
			{
				tmp = p->data;
				p->data = q->data;
				q->data = tmp;
			}
		}
	}
	printf("Danh sach hoc vien sau khi sap xep theo ma lop va diem giam dan:\n");
	xuat_ds_hocvien(ds);
}

void InHVChuaDat(danhsach_hv ds_hv)
{
	danhsach_hv ds_chuadat;
	ds_chuadat.Head = NULL;
	ds_chuadat.Tail = NULL;

	node_hv* p = ds_hv.Head;
	while (p != NULL)
	{
		if (p->data.diem < 5)
		{
			node_hv* q = (node_hv*)malloc(sizeof(node_hv));
			q->data = p->data;
			q->next = NULL;
			if (ds_chuadat.Head == NULL)
			{
				ds_chuadat.Head = q;
				ds_chuadat.Tail = q;
			}
			else
			{
				ds_chuadat.Tail->next = q;
				ds_chuadat.Tail = q;
			}
		}
		p = p->next;
	}

	node_hv* tmp;
	node_hv* q;
	for (p = ds_chuadat.Head; p != NULL; p = p->next)
	{
		for (q = p->next; q != NULL; q = q->next)
		{
			if (strcmp(p->data.ten, q->data.ten) < 0)
			{
				tmp = (node_hv*)malloc(sizeof(node_hv));
				tmp->data = p->data;
				p->data = q->data;
				q->data = tmp->data;
				free(tmp);
			}
		}
	}

	printf("Danh sach hoc vien chua dat diem:\n");
	p = ds_chuadat.Head;
	while (p != NULL)
	{
		printf("%s %s, Diem: %.2f\n", p->data.holot, p->data.ten, p->data.diem);
		p = p->next;
	}
}


void InHocVienDatHocBong(danhsach_hv* ds_hv) {
	FILE* f = fopen("dshocbong.txt", "w");
	if (f == NULL) {
		printf("Khong the mo file dshocbong.txt");
		return;
	}

	node_hv* hb = ds_hv->Head;
	printf("Danh sach hoc vien dat hoc bong:\n");
	while (hb != NULL) {
		if (hb->data.diem >= 8.0) {
			printf("Ma HV: %s, Ho ten: %s %s, Ngay sinh: %d/%d/%d, Ma lop: %s, Diem: %.2f\n",
				hb->data.mahv, hb->data.holot, hb->data.ten,
				hb->data.ngaysinh.day, hb->data.ngaysinh.month, hb->data.ngaysinh.year,
				hb->data.malop, hb->data.diem);
			fprintf(f, "%s %s %s %d/%d/%d %s %.2f\n",
				hb->data.mahv, hb->data.holot, hb->data.ten,
				hb->data.ngaysinh.day, hb->data.ngaysinh.month, hb->data.ngaysinh.year,
				hb->data.malop, hb->data.diem);
		}
		hb = hb->next;
	}

	fclose(f);
}


int main()
{
	danhsach_hv ds_hv;
	danhsach_lophoc ds_lophoc;

	char filenamelophoc[] = "lophoc.txt";
	char filenamehocvien[] = "hocvien.txt";

	bool kt_menu = true;
	while (kt_menu == true)
	{
		printf("\t\t\tMENU\n");
		printf("|=============================================================|\n");
		printf("|1. Nhap hoc vien                                             |\n");
		printf("|2. Doc Thong Tin Hoc Vien                                    |\n");
		printf("|3. Xuat thong tin hoc vien                                   |\n");
		printf("|4. Doc Thong Tin Lop Hoc                                     |\n");
		printf("|5. Xuat thong tin lop hoc                                    |\n");
		printf("|6. Tim kiem theo tieu chi                                    |\n");
		printf("|7. Xuat thong tin theo lop hoc                               |\n");
		printf("|8. Tim hoc vien diem cao nhat                                |\n");
		printf("|9. Tim hoc vien co hoc phi cao nhat                          |\n");
		printf("|10. Sap xep theo ma lop, giam theo diem                      |\n");
		printf("|11. In hoc vien diem <5, giam theo ten                       |\n");
		printf("|12. In hoc vien dat HocBong va luu vao file                  |\n");
		printf("|0. Thoat                                                     |\n");
		printf("|=============================================================|\n");
		int lc;
		printf("Moi nhap lua chon: ");
		scanf("%d", &lc);
		printf("\n");
		switch (lc)
		{
		case 1:
		{
				  int sl;
				  printf("Nhap so luong hoc vien: ");
				  scanf("%d", &sl);
				  getchar();
				  for (int i = 1; i <= sl; i++)
				  {
					  hv x;
					  printf("\tSINH VIEN %d\n", i);
					  nhap_hocvien(x);
					  them_hocvien(ds_hv, x);
				  }
				  break;
		}
		case 2:
		{
				  doc_danhsach_hocvien(ds_hv);
				  break;
		}
		case 3:
		{
				  xuat_ds_hocvien(ds_hv);
				  break;
		}
		case 4:
		{
				  doc_danhsach_lophoc(filenamelophoc, ds_lophoc);
				  break;
		}
		case 5:
		{
				  xuat_danhsach_lophoc(ds_lophoc);
				  break;
		}
		case 6:
		{
				  menu2(ds_hv, ds_lophoc);
				  break;
		}
		case 7:
		{
				  InDanhSachHocVienTheoLop(ds_hv);
				  break;
		}
		case 8:
		{
				  TimHocVienDiemCaoNhat(ds_hv);
				  break;
		}
		case 9:
		{
				  TimHVHocLopHocPhiCaoNhat(ds_hv, ds_lophoc);
				  break;
		}
		case 10:
		{
				   SapXepHVTheoMaLopVaDiemGiamDan(ds_hv);
				   break;
		}
		case 11:
		{
				   InHVChuaDat(ds_hv);
				   break;
		}
		case 12:
		{
				   InHocVienDatHocBong(&ds_hv);
				   break;
		}
		case 0:
		{
				  kt_menu = false;
				  break;
		}
		default:
			break;
		}
	}
}
