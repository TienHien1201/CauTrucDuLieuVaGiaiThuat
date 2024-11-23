#include<iostream>
using namespace std;

//Đề bài: Nhập danh sách liên kết đơn các phân số


//Khai báo cấu trúc 1 cái phân số
struct PhanSo
{
	int tuSo;
	int mauSo;
};

//Khai báo câu trúc 1 code của danh sách liên kết đơn quản lí bằng 1 con trỏ với data là phân số
struct node
{
	PhanSo data;//Thành phần dữ liệu của 1 cái node
	node* pNext;//con trỏ dùng để giữ địa chỉ của cái node mà nó liên kết đến
};

//Hàm khởi tạo 1 cái node
node* KHoiTaoNode(PhanSo& ps) {
	node* p = new node;
	if (p == NULL) {
		cout << "Khong du bo nho !";
		return NULL;
	}

	p->data = ps;//Truyền giá trị ps và cho cái data của cái node p
	p->pNext = NULL;//Chưa liên kết thằng nào nên phải trỏ vào vùng nhớ NULL
	return p;
}

//Nhap phan so
void NhapPhanSo(PhanSo& ps) {/*Vì ta đã tạo ra 1 truct PhanSo trong struc PhanSo có 2 thuộc tính số nguyên là tuSo và maSo
	nên khi ta tạo ra hàm nhập PhanSo chỉ cần truyền vào struct PhanSo và truy xuất đến tuSo và maSo là có thể nhập đc,
	và tham chiếu để lưu lại giá trị của tuSo và mauSo sau khi nhập vào.*/
	cout << "\nNhap tu so: ";
	cin >> ps.tuSo;
	cout << "Nhap mau so: ";
	cin >> ps.mauSo;
}

//Hàm xuất phân số
void XuatPhanSo(PhanSo ps) {

	cout << ps.tuSo << "/" << ps.mauSo;
}

//Thêm node p vào đầu danh sách
void ThemVaoDau(node*& pHead, node* p) {/*vì danh sách chỉ quản lí bởi 1 con trỏ nên ta cần 1 đại diện để quản lí danh sách
	thì con trỏ đầu pHead chính là đại diện để quản lí danh sách*/

	//Nếu danh sách rỗng
	if (pHead == NULL)
		pHead = p;

	//Nếu danh sách có phần tử
	else
	{
		p->pNext = pHead;//Cho node p cần thêm kết nối đến thằng đầu danh sách
		pHead = p;//Cập nhật lại node đầu chính là node vừa thêm vào
	}
}

//Hàm thêm node vào cuối
void ThemVaoCuoi(node*& pHead, node* p) {

	//Nếu danh sách đang rỗng
	if (pHead == NULL)
		pHead = p;
	else
	{
		for (node* k = pHead; k != NULL; k = k->pNext) {
			if (k->pNext == NULL)/*nếu cái thằng đang xét mà cái pNext bên trong nó đang liên kết đến NULL ==> k chính là
				node cuối danh sách vì phần tử cuối danh sách là phần tử trỏ đến NULL nên khi duyệt đến phần tử  trỏ đến
				NULL thì phần tử đó chính là phần tử cuối của danh sách*/
			{
				k->pNext = p;
				break;
			}

		}
	}

}

//Hàm xuất danh sách các phân số
void XuatDanhSachPhanSo(node*& pHead) {/*Các phân số của ta lúc này dc lưu trữ bởi danh sách liên kết đơn mà các phần tử
	trong danh sách liên kết đơn này được quản lí bởi 1 con trỏ là pHead nên khi thao tác với danh sách liên kết đơn này,
	thao tác đến từng node trong danh sách liên kết đơn này thì ta luôn luôn thao tác với con trỏ đầu danh sách là pHead,
	nên khi xuất từng phần tử hay còn gọi là node hay còn gọi là phân số ra thì ta phải truyền vào node*& pHead*/
	for (node* k = pHead; k != NULL; k = k->pNext) {
		XuatPhanSo(k->data);
		cout << "\n";
	}

}

//Thiết kế 1 menu để thao tác trên danh sách liên kết đơn
void Menu(node*& pHead) {

	while (true)
	{
		system("Cls");
		cout << "\n\n\t\t1.Nhap phan so";
		cout << "\n\n\t\t2.Xuat danh sach";
		cout << "\n\n\t\t0.Ket thuc";

		int luaChon;
		cout << "\n\n\t\tMoi lua chon: ";
		cin >> luaChon;

		if (luaChon == 1) {
			PhanSo ps;
			cout << "Nhap phan so";
			NhapPhanSo(ps);

			node* p = KHoiTaoNode(ps);
			//ThemVaoDau(pHead, p);
			ThemVaoCuoi(pHead, p);
		}
		else if (luaChon == 2)
		{
			cout << "Danh sach phan so\n";
			XuatDanhSachPhanSo(pHead);
			system("Pause");
		}
		else if (luaChon == 0)
		{
			break;
		}
	}
}
int main() {
	node* pHead = NULL;
	Menu(pHead);
	system("Pause");

}