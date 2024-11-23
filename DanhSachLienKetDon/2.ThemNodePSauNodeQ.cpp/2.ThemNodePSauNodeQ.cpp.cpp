#include <iostream>
using namespace std;

//Đề bài: Nhập danh sách liên kết đơn các số nguyên
//=================KHAI BÁO CẤU TRÚC DANH SÁCH LIÊN KẾT ĐƠN======================
//Khai báo node - nút của danh sách 
struct node
{
	int data;//Dữ liệu của 1 node
	struct node* pNext;//Liên kết giữa các node với nhau
};


//Khai báo cấu trúc danh sách liên kết đơn
struct List
{
	node* pHead;
	node* pTail;
};

//====================KHỞI TẠO CẤU TRÚC DANH SÁCH LIÊN KẾT ĐƠN======================
void khoiTaoDSLKD(List& l) {
	//Cho hai con trỏ đầu và cuối trỏ vào vùng nhớ rỗng
	l.pHead = NULL;
	l.pTail = NULL;
}

//Khởi tạo 1 cái node. Vì node là 1 con trỏ nên khởi tạo node cũng phải là 1 con trỏ
node* khoiTaoNode(int x) {//vì để bài dữ liệu là số nguyên nên hàm khởi tạo node phải truyền vào data là số nguyên
	node* p = new node;//Tạo 1 con trỏ p để chứa dữ liệu 
	if (p == NULL){
		cout << "\nCap phat bo nho khong thanh cong. Bo nho da day !";
	return NULL;
}
	p->data = x;
	p->pNext = NULL;
	return p;
}

//Thêm node p(Tức phần tử mới) vào đầu danh sách
void themVaoDau(List& l, node* p) {
	//danh sách đang rỗng 
	if (l.pHead == NULL)
		l.pHead = l.pTail = p;
	//Danh sách không rỗng, tức đã có phần tử 
	else {
		p->pNext = l.pHead;//dùng con trỏ cua node p(Phần tử mới cần thêm vào) liên kết với l.pHead
		l.pHead = p;//Cập nhật lại l.pHead = p
	}

}


//Thêm node p vào cuối danh sách 
void themVaoCuoi(List &l , node* p){
	if (l.pTail == NULL)
		l.pHead = l.pTail = p;
	else {
		l.pTail->pNext = p;
		l.pTail = p;
	}
}

//Hàm xuất danh sách liên kêt đơn
void xuatDanhSach(List l) {
	for (node* k = l.pHead; k != NULL; k = k->pNext)
		cout << k->data<<" ";
}

//Thêm node p vào sau node q(Tức là phần tử đã tồn tại ở trong danh sách)
void themNodePvaoSauNodeQ(List& l, node* p) {
#if 0
	int x;
	cout << "Nhap gia tri cho node q: ";
	cin >> x;
	node* q = khoiTaoNode(x);

	//Nếu danh sách chỉ có 1 phần tử và phần đó cũng chính là node q => bài toán trở thành kỹ thuật thêm vào cuối danh sách
	if (q->data == l.pHead ->data && l.pHead ->pNext == NULL)
		themVaoCuoi(l, p);
 
	else
	{ 
		//Duyệt từ đầu danh sách đến cuối danh sách để tìm node q
		for (node* k = l.pHead; k != NULL; k = k->pNext) {
			if (q->data == k->data)//Kiểm tra xem có tồn tại phần tử q trong danh sách không
			{    
				node* h = khoiTaoNode(p->data);//Khởi tạo node h để thêm vào sau node q
				node* g  = k->pNext;/*Cho node g trỏ đến node nằm sau node q. Con trỏ g là node giữ mối liên kết của thằng 
				nằm sau node q*/
				h->pNext = g;/*Bước 1 Tạo mối liên kết từ node h đến node g <=> cũng chính là tạo mối liên kết từ
				node h đến node nằm sau node q*/
				k->pNext = h;//Bước 2 Tạo mối liên kết từ node q đến node h <=> chính là node k đến node h	
			}

		}
	}
#endif
	int x;
	cout << "Nhap gia tri cho node q: ";
	cin >> x;
	node* q = khoiTaoNode(x);

	//Nếu danh sách chỉ có 1 phần tử và phần đó cũng chính là node q => bài toán trở thành kỹ thuật thêm vào cuối danh sách
	if (q->data == l.pHead ->data && l.pHead ->pNext == NULL)
		themVaoCuoi(l, p);
 
	else
	{ 
		//Duyệt từ đầu danh sách đến cuối danh sách để tìm node q
		for (node* k = l.pHead; k != NULL; k = k->pNext) {
			if (q->data == k->data)//Kiểm tra xem có tồn tại phần tử q trong danh sách không
			{    
				node* h = khoiTaoNode(p->data);/*Mõi lần phát hiện 1 node q thì khởi tạo 1 node p mới đó là node h => khởi
					tạo h mới bằng cách lấy data của node p nhưng địa chỉ sẽ được đổi mới. Vì nếu ta mà khởi tạo node p ở ngoài
					đk if của vòng lặp thì node p chỉ được khởi tạo 1 lần và nó sẽ lấy địa chỉ cũ của node p đó liên kết với
					node q khác trong danh sách sẽ làm mất liên kết với các node và mất phần tử. Vậy nên việc ta khởi tạo 1
					node p nằm ngoài đk if của vòng lặp thì ta phải tạo 1 bản sao của node p ở trong đk if của vòng lặp for
					để mõi khi tìm thấy node q mà trong danh sách có 2 node q trở lên thì sau lần thêm node p vào sau node
					q lần đầu tiên cứ mõi lần duyệt thấy node q mới trong mõi lần tiếp theo của danh sách thì node h sẽ tạo
					ra 1 bản sao của node p với data của node p còn địa chỉ thì hoàn toàn mới, tránh trường hợp trong danh
					sách có 2 node q trở lên mà ta chỉ khởi tạo node p ở ngoài đk if của vòng lặp thì node p chỉ được khởi
					tạo 1 lần và nó sẽ lấy địa chỉ cũ của node p đó liên kết với node q khác trong danh sách sẽ làm mất liên
					kết với các node và mất phần tử*/
				node* g  = k->pNext;/*Cho node g trỏ đến node nằm sau node q. Con trỏ g là node giữ mối liên kết của thằng 
				nằm sau node q*/
				h->pNext = g;/*Bước 1 Tạo mối liên kết từ node h đến node g <=> cũng chính là tạo mối liên kết từ
				node h đến node nằm sau node q*/
				k->pNext = h;//Bước 2 Tạo mối liên kết từ node q đến node h <=> chính là node k đến node h	
			}

		}
	}

}
 
//Hàm MENU - xử lí các vấn đề của bài 
void Menu(List &l) {
	while (true) {
		system("cls");
		cout << "\n\t1.Nhap them Node(Phan tu moi) vao trong danh sach";
		cout << "\n\t2.Xuat danh sach lien ket don ";
		cout << "\n\t3.Them node p vào sau node q trong danh sach";
		cout << "\n\t0.Thoat chuong trinh";

		cout << "\n\n\tMoi lua chon: ";
		short luaChon;
		cin >> luaChon;
		if (luaChon < 0 || luaChon > 3){
			cout << "Nhap sai, can nhap lai lua chon tuon ung !";
			system("Pause");	
		}
	else if (luaChon == 1)	{
				int x;
				cout << "\nNhap gia tri so nguyen: ";
				cin >> x;
				node* p = khoiTaoNode(x);//Khởi tạo 1 cái node
				themVaoCuoi(l, p);//Thêm vào đầu hay cuối danh sách gì cũng được 
				}
		else if (luaChon == 2) {
			cout << "Danh sach lien ket don: ";
			xuatDanhSach(l);
			system("Pause");
		}
		else if(luaChon == 3)
		{
			int x;
			cout << "Nhap gia tri can them vao sau node q: ";
			cin >> x;
			node* p = khoiTaoNode(x);
			themNodePvaoSauNodeQ(l, p);//Them node p vào sau node q trong danh sách liên kết đơn l
		}
		else if(luaChon == 0)
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


