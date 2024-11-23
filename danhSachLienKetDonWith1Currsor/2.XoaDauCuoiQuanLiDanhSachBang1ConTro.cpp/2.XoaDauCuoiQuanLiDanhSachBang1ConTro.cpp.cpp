#include<iostream>
using namespace std;

//Đề bài: Nhập danh sách liên kết đơn các phân số


//Khai báo cấu trúc 1 cái phân số
struct PhanSo
{
	int tuSo;
	int mauSo;
};

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

//Hàm xóa node đầu danh sách
void XoaDau(node*& pHead) {
	if (pHead == NULL)
		return;
	else
	{
		node* p = pHead;
		pHead = pHead->pNext;
		delete p;
	}
}
//Hàm xóa node cuối danh sách
void XoaCuoi(node*& pHead) {

	//Nếu danh sách rỗng
	if (pHead == NULL)
		return;

	//Nếu danh sách chỉ có 1 phần tử
	/*Lý do ta phải bắt trường hợp này là do ở phần bên dưới ta duyệt đến phần tử kế cuối để xóa thằng cuối rồi cập nhật
	lại cho thằng kế cuối trong danh sách trỏ tới NULL và khi ta duyệt phần tử kế cuối bằng cách cho phần tử nào mà trỏ 2
	lần nữa đến NULL thì phần tử đó là phần tử kế cuối, nên việc chỉ còn 1 phần tử mà ta duyệt phần tử này bằng cách xét
	phần tử nào trỏ 2 lần nữa là đến NULL thì phần tử đó là phần tử kế cuối thì khi dùng con trỏ của phần tử duy nhất trong
	danh sách trỏ lần 1(k->pNext) tức là trỏ phần tử duy nhất trong danh sách này đến phần tử kế tiếp mà phần tử kế tiếp là
	vùng nhớ NULL mà chưa dừng lại ta lại trỏ phần tử duy nhất trong danh sách này thêm 1 lần nữa( k->pNext->pNext ) tức là
	lần 1 trỏ đến NULL sau đó trỏ thêm lần 2 là trỏ đến vùng nhớ không xác định dẫn đến việc con trỏ lúc này bị treo hiện
	tượng này gọi là "dangling pointer" nên chương trình của ta sẽ bị lỗi ở trường hợp danh sách chỉ tồn tại duy nhất một
	phần tử.*/
	if (pHead->pNext == NULL) {
		node* p = pHead;//Cho node p là node thế mạng
		pHead  = NULL;/*Cập nhập lại con trỏ đầu trỏ đến NULL, nếu không cập nhật lại con trỏ đầu là NULL thì danh sách sẽ mất
		con trỏ duy nhất quản lí danh sách là pHead dẫn đến việc thao tác với danh sách mà không có con trỏ đầu sẽ xảy ra lỗi
		là mất đi danh sách và không thể truy cập lại danh sách nữa.*/
		delete p;// Xóa phần tử duy nhất trong danh sách
	}
	else
	{
		for (node* k = pHead; ; k = k->pNext) {
			if (k->pNext->pNext == NULL)/*k->pNext->pNext là duyệt xem phần tử nào mà trỏ 2 lần nữa mới tới NULL thì đó chính
				là phần tử kế cuối vì phần tử cuối là phầ tử liên kết với NULL tức là phần tử cuối chỉ trỏ 1 lần là liên kết
				tới NULL còn phần tử kế cuối phải trỏ 2 lần mới đến NULL. Ta duyệt đến phần tử kế cuối để ta cập nhật lại cho
				phần tử kế cuối trỏ đến NULL sau khi phần tử cuối bị xóa.*/
			{
				delete k->pNext;/*Xóa phần tử cuối. Vì ta đã duyệt đến phần tử kế cuối nên ta chỉ cần lấy phần tử kế cuối mà
		 ta đã duyệt trỏ(pNext) 1 cái nữa là đến phần tử cuối trong danh sách và ta xóa phần tử cuối đi. */
				k->pNext = NULL;
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
		cout << "\n\n\t\t3.Xoa phan tu dau danh sach";
		cout << "\n\n\t\t4.Xoa phan tu cuoi danh sach";
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
			if (pHead == NULL) {
				cout << "Khong ton tai phan tu ";
				system("Pause");
			}
			else
			{
				XuatDanhSachPhanSo(pHead);
				system("Pause");
			}
		}
		else if (luaChon == 3)
		{
			XoaDau(pHead);
		}
		else if (luaChon == 4)
		{
			XoaCuoi(pHead);
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