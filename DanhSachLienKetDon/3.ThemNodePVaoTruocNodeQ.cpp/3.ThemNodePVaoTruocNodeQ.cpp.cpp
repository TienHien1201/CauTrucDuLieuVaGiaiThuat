#include <iostream>
using namespace std;


//Đề bài: Nhập danh sách liên kết đơn các số nguyên
//==============KHAI BÁO CẤU TRÚC DANH SÁCH LIÊN KẾT ĐƠN=======================

//Khai báo node
struct node
{
	int data;
	struct node* pNext;
};

//Khai báo cấu trúc danh sách liên kết đơn
struct List
{
	node* pHead;
	node* pTail;
};

//================KHỞI TẠO CẤU TRÚC DANH SÁCH LIÊN KẾT ĐƠN===============

//khởi tạo danh sách liên kết đơn
void khoiTaoDSLKD(List& l) {
	l.pHead = NULL;
	l.pTail = NULL;
}

//Khởi tạo 1 cái node
node* khoiTaoNode(int x) {
	node* p = new node;
	if (p == NULL) {
		cout << "Khoi tao khong thanh cong. Khong du bo nho !";
		return NULL;
	}
	p->data = x;
	p->pNext = NULL;
	return p;
}

//Thêm node p vào đầu danh sách
void ThemVaoDau(List& l, node* p) {
	if (l.pHead == NULL)
		l.pHead = l.pTail = p;
	else
	{
		p->pNext = l.pHead;
		l.pHead = p;
	}
}

//Thêm node p vào cuối danh sách
void ThemVaoCuoi(List& l, node* p) {
	if ( l.pTail == NULL)
		l.pHead = l.pTail = p;
	else{
		l.pTail->pNext = p;
		l.pTail = p;
	}
}

//Hàm xuất danh sách danh liên kết đơn
void XuatDanhSach(List l) {
	for (node* k = l.pHead; k != NULL; k = k->pNext)
		cout << k->data << " ";
}

//Thêm node p vào sau node q(Tức là phần tử đã tồn tại ở trong danh sách)
void ThemNodePvaoSauNodeQ(List& l, node* p) {
	int x;
	cout << "Nhap gia tri cho node q: ";
	cin >> x;
	node* q = khoiTaoNode(x);

	//Nếu danh sách chỉ có 1 phần tử và phần đó cũng chính là node q => bài toán trở thành kỹ thuật thêm vào cuối danh sách
	if (q->data == l.pHead->data && l.pHead->pNext == NULL)
		ThemVaoCuoi(l, p);

	else
	{
		//Duyệt từ đầu danh sách đến cuối danh sách để tìm node q
		for (node* k = l.pHead; k != NULL; k = k->pNext) {
			if (q->data == k->data)//Kiểm tra xem có tồn tại phần tử q trong danh sách không
			{
				node* h = khoiTaoNode(p->data);//Khởi tạo node h để thêm vào sau node q
				node* g = k->pNext;/*Cho node g trỏ đến node nằm sau node q. Con trỏ g là node giữ mối liên kết của thằng
				nằm sau node q*/
				h->pNext = g;/*Bước 1 Tạo mối liên kết từ node h đến node g <=> cũng chính là tạo mối liên kết từ
				node h đến node nằm sau node q*/
				k->pNext = h;//Bước 2 Tạo mối liên kết từ node q đến node h <=> chính là node k đến node h	
			}

		}
	}


}

//Thêm node p vào trước node q
void ThemNodePVaoTruocNodeQ(List& l, node* p) {
	int x;
	cout << "Nhap gia tri node q: ";
	cin >> x;
	node* q = khoiTaoNode(x);

	//Trường hợp chỉ có 1 node q trong danh sách. 
	/*Chỉ tham khảo bản chất vì đây là cơ bản phải hiểu thì mới xuống trường hợp
	bên dưới được. Không nên làm cách này vì xảy ra lỗi k đúng cho mọi trường hợp chỉ cần hiểu bản chất thôi*/
#if 0
if (l.pHead->data == q->data && l.pHead->pNext == NULL)
		ThemVaoDau(l, p);
	else
	{
		node* g = new node;//Node g chính là node giữ mối liên kết với node nằm trước node q trong danh sách	 

		//Duyệt từ đầu danh sách đến cuối danh sách để tìm node q
		for (node* k = l.pHead; k != NULL; k = k->pNext) {
			if (q->data == k->data)//Kiểm tra xem có tồn tại phần tử q trong danh sách không
			{
				//Việc thêm node p trước node q thực chất chỉ là thêm node p vào sau node g(Tức là node nằm trước node q)
				p->pNext = k;//Bước 1 cho node p trỏ đến node k => Thì cũng chính là cho node p trỏ đến node q		
				g->pNext = p;//Bước 2 cho node g trỏ đến node p


			}
			g = k;//Giữ liên kết với node nằm trước node q trong danh sách
		}
#endif 

	

	//Trường hợp chỉ có 2 node q trở lên trong danh sách 
	//Nếu danh sách chỉ có 1 phần tử và phần đó cũng chính là node q => bài toán trở thành kỹ thuật thêm vào đầu danh sách
	if (l.pHead->data == q->data && l.pHead->pNext == NULL)
		ThemVaoDau(l, p);
	else
	{
		node* g = new node;//Node g chính là node giữ mối liên kết với node nằm trước node q trong danh sách	 

		//Duyệt từ đầu danh sách đến cuối danh sách để tìm node q
		for (node* k = l.pHead; k != NULL; k = k->pNext) {
			if (q->data == k->data)//Kiểm tra xem có tồn tại phần tử q trong danh sách không
			{
			//Việc thêm node p trước node q thực chất chỉ là thêm node p vào sau node g(Tức là node nằm trước node q)
				node* h = khoiTaoNode(p->data);/*Mõi lần phát hiện 1 node q thì khởi tạo 1 node p mới => khởi tạo h mới bằng
				cách lấy data của node p nhưng địa chỉ sẽ được đổi mới*/
				h->pNext = k;//Bước 1 cho node h trỏ đến node k => Thì cũng chính là cho node h trỏ đến node q		
				g->pNext = h;//Bước 2 cho node g trỏ đến node h
				
				
			}
			g = k;//Giữ liên kết với node nằm trước node q trong danh sách
		}
	}
}

//Hàm MENU - xử lí các vấn đề của bài 
void Menu(List& l) {
	while (true) {
		system("cls");
		cout << "\n\t1.Nhap them Node(Phan tu moi) vao trong danh sach";
		cout << "\n\t2.Xuat danh sach lien ket don ";
		cout << "\n\t3.Them node p vào sau node q trong danh sach";
		cout << "\n\t4.Them node p vao truoc node q trong danh sach";
		cout << "\n\t0.Thoat chuong trinh";

		cout << "\n\n\tMoi lua chon: ";
		short luaChon;
		cin >> luaChon;
		if (luaChon < 0 || luaChon > 4) {
			cout << "Nhap sai, can nhap lai lua chon tuon ung !";
			system("Pause");
		}
		else if (luaChon == 1) {
			int x;
			cout << "\nNhap gia tri so nguyen: ";
			cin >> x;
			node* p = khoiTaoNode(x);//Khởi tạo 1 cái node
			ThemVaoCuoi(l, p);//Thêm vào đầu hay cuối danh sách gì cũng được 
		}
		else if (luaChon == 2) {
			cout << "Danh sach lien ket don: ";
			XuatDanhSach(l);
			system("Pause");
		}
		else if (luaChon == 3)
		{
			int x;
			cout << "Nhap gia tri can them vao sau node q: ";
			cin >> x;
			node* p = khoiTaoNode(x);
			ThemNodePvaoSauNodeQ(l, p);//Them node p vào sau node q trong danh sách liên kết đơn l
		}
		else if(luaChon == 4)
		{
			int x;
			cout << "Nhap gia tri can them vao truoc node q: ";
			cin >> x;
			node* p = khoiTaoNode(x);
			ThemNodePVaoTruocNodeQ(l, p);//Them node p vào trước node q trong danh sách liên kết đơn l
		}
		else if (luaChon == 0)
			break;
	}
}

int main()
{
	List l;
	khoiTaoDSLKD(l);/*Luôn luôn gọi hàm khởi tạo danh sách liên kết đơn(vì nó có 2 con trỏ đầu và cuối để quản lí danh sách)
	trước khi thao tác với danh sách*/
	Menu(l);

	system("Pause");
}

