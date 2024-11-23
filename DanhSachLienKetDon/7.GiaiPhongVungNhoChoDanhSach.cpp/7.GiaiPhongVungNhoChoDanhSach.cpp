#include<iostream>
using namespace std;

int n = 0;//Khai báo biến toàn cục - Chứa số lượng phần tử trong danh sách 

////Đề bài: Nhập danh sách liên kết đơn các số nguyên
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

//Khởi tạo danh sách liên kết đơn
void KhoiTaoDSLKD(List& l) {
	l.pHead = NULL;
	l.pTail = NULL;
}

//Khởi tạo 1 cái node
node* KhoiTaoNode(int x) {
	node* p = new node;
	if (p == NULL)
	{
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
	else {
		p->pNext = l.pHead;
		l.pHead = p;
	}
}

//Thêm node p vào cuối danh sách
void ThemVaoCuoi(List& l, node* p) {
	if (l.pTail == NULL)
		l.pHead = l.pTail = p;
	else
	{
		l.pTail->pNext = p;
		l.pTail = p;
	}
}

//Hàm xuất danh sách liên kết đơn
void XuatDanhSach(List l) {
	for (node* k = l.pHead; k != NULL; k = k->pNext) {
		cout << k->data << " ";
	}
}

//Thêm node p vào sau node q(Tức là phần tử đã tồn tại ở trong danh sách)
void ThemNodePvaoSauNodeQ(List& l, node* p) {
	int x;
	cout << "Nhap gia tri cho node q: ";
	cin >> x;
	node* q = KhoiTaoNode(x);

	//Nếu danh sách chỉ có 1 phần tử và phần đó cũng chính là node q => bài toán trở thành kỹ thuật thêm vào cuối danh sách
	if (q->data == l.pHead->data && l.pHead->pNext == NULL)
		ThemVaoCuoi(l, p);
	else
	{
		//Duyệt từ đầu danh sách đến cuối danh sách để tìm node q
		for (node* k = l.pHead; k != NULL; k = k->pNext) {
			if (q->data == k->data)//Kiểm tra xem có tồn tại phần tử q trong danh sách không
			{
				//=====Cách 1: đây là cách dùng node g là node trung gian để trỏ đến node nằm sau node q =======
				//node* h = KhoiTaoNode(p->data);/*Mõi lần phát hiện 1 node q thì khởi tạo 1 node p mới => khởi tạo h mới bằng
				//cách lấy data của node p nhưng địa chỉ sẽ được đổi mới*/
				//node* g = k->pNext;/*Cho node g trỏ đến node nằm sau node q. Con trỏ g là node giữ mối liên kết của thằng
				//nằm sau node q*/
				//h->pNext = g;/*Bước 1 Tạo mối liên kết từ node h đến node g <=> cũng chính là tạo mối liên kết từ
				//node h đến node nằm sau node q*/
				//k->pNext = h;//Bước 2 Tạo mối liên kết từ node q đến node h <=> chính là node k đến node h	

				/*=== Cách 2: Không cần tạo con ndoe trung gian để trỏ để node nằm sau node q mà ta dịch k(Tức là q)
				trỏ đến node kế tiếp rồi sau đó cho con trỏ của node cần thêm là node h(p) trỏ đến node nằm sau node
				q luôn. Cách này tối ưu bộ nhớ hơn vì không cần phải tạo nhiều con trỏ nên đỡ tốn vùng nhớ khi cấp
				phát cho con trỏ khi tạo ======*/
				node* h = KhoiTaoNode(p->data);/*Mõi lần phát hiện 1 node q thì khởi tạo 1 node p mới => khởi tạo h mới bằng
				//cách lấy data của node p nhưng địa chỉ sẽ được đổi mới*/
				h->pNext = k->pNext;/*Bước 1: Dùng con trỏ của node h(p) trỏ đến phần phần tử nằm sau node k => Cũng chính là
				dùng con trỏ của node h(phần tử cần thêm) trỏ đến node nằm sau node q. Vì k bây giờ bằng q mà ta dùng k->pNext
				tức node k sẽ trỏ đến phần tử kế node k dấu bằng tức là lấy con trỏ của node h trỏ đến phần tử nằm sau node k*/
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
	node* q = KhoiTaoNode(x);

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
					node* h = KhoiTaoNode(p->data);/*Mõi lần phát hiện 1 node q thì khởi tạo 1 node p mới => khởi tạo h mới bằng
					cách lấy data của node p nhưng địa chỉ sẽ được đổi mới*/
					h->pNext = k;//Bước 1 cho node h trỏ đến node k => Thì cũng chính là cho node h trỏ đến node q		
					g->pNext = h;//Bước 2 cho node g trỏ đến node h
				}
				g = k;//Giữ liên kết với node nằm trước node q trong danh sách
			}
		}
	}

	/*Cách 1 dùng vòng lặp(Tức là vòng lặp ở hàm menu ở luaChon == 5) để duyệt qua từng phần tử mõi lần thêm phần tử mới
	 vào danh sách thì n++(Tức là n tăng lên) cách này không tối ưu vì mõi lần thêm vào danh sách thì vòng lặp nó duyệt dẫn
	 đến tốn rất nhiều time ví dụ danh sách ta có 5 phần tử thì ta thêm 1 phần tử vào danh sách thì vòng lặp nó bắt đầu duyệt
	 qua từng phần tử để tăng n lên qua mõi lần duyệt. Vì vậy cách 2 dùng biến cục bộ sẽ tối ưu hơn*/
	 //Thêm node p vào bất kì vị trí nào trong danh sách
#if 0
	void ThemNodePVaoViTriBatKy(List & l, node * p, int viTri, int n) {
		/*Vì ta tạo ra 1 menu xử lí nên phần dùng vòng lặp for duyệt qua từng phân tử để tăng biến n lên chứa phần tử ở trong hàm
		là không cần thiết vì bị thừa chỉ cần thực hiện ở hàm menu là được nếu k có hàm menu thì ta phải triển khai vòng lặp ở đây
		để thực hiện việc dùng vòng lặp for duyệt qua từng phân tử để tăng biến n lên chứa phần tử*/
#if 0
		int n = 0;
		for (node* k = l.pHead; k != NULL; k = k->pNext)
			n++;
#endif

		//Danh sách đang rỗng. Bắt trường hợp danh sách ban đầu là rỗng
		if (l.pHead == NULL || viTri == 1)
			//Thêm node p vào đầu danh sách l
			ThemVaoDau(l, p);

		/*Bắt trường hợp muốn thêm vào cuối danh sách ban đầu chỉ có n phần
		tử nên khi thêm vào cuối thì phải tăng số khoảng n lên là n + 1 */
		else if (viTri == n + 1)
			//Thêm node p vào cuối danh sách
			ThemVaoCuoi(l, p);

		else/*Bắt trường hợp vị trí nằm trong đoạn từ [2, n]. Vì trường hợp bắt vị trí số 1 và vị trí cuối của danh
			danh ta đã bắt rồi*/
		{
			int dem = 0;//Xác định vị trí cần thêm 
			node* g = new node;//Node g chính là node giữ mối liên kết với node nằm trước node q trong danh sách	 

			//Duyệt từ đầu danh sách đến cuối danh sách để tìm node q => Chính là tìm ra vị trí cần thêm node p vào
			for (node* k = l.pHead; k != NULL; k = k->pNext) {
				if (dem == viTri)//Tìm vị trí ví trí muốn thêm
				{
					//Việc thêm node p trước node q thực chất chỉ là thêm node p vào sau node g(Tức là node nằm trước node q)
					node* h = KhoiTaoNode(p->data);/*Mõi lần phát hiện 1 node q thì khởi tạo 1 node p mới => khởi tạo h mới
					bằng cách lấy data của node p nhưng địa chỉ sẽ được đổi mới*/
					h->pNext = k;//Bước 1 cho node h trỏ đến node k => Thì cũng chính là cho node h trỏ đến node q		
					g->pNext = h;//Bước 2 cho node g trỏ đến node h
					break;/*Vì vị trí danh sách liên kết đơn là riêng biệt tức chỉ tồn tại 1 vị trí nhau nên sau khi tìm được
					phải thoát vòng lặp không cần duyệt nữa*/
				}
				g = k;//Giữ liên kết với node nằm trước node q trong danh sách
			}
		}

	}
#endif 

	//Cách 2 dùng biến cục bộ cho biến n 
	//thì hàm sẽ không có tham số n truyền vào để chứa phần tử trong danh sách nữa 
	void ThemNodePVaoViTriBatKy(List & l, node * p, int viTri) {


		//Danh sách đang rỗng. Bắt trường hợp danh sách ban đầu là rỗng
		if (l.pHead == NULL || viTri == 1)
			//Thêm node p vào đầu danh sách l
			ThemVaoDau(l, p);

		/*Bắt trường hợp muốn thêm vào cuối danh sách ban đầu chỉ có n phần
		tử nên khi thêm vào cuối thì phải tăng số khoảng n lên là n + 1 */
		else if (viTri == n + 1)
			//Thêm node p vào cuối danh sách
			ThemVaoCuoi(l, p);

		else/*Bắt trường hợp vị trí nằm trong đoạn từ [2, n]. Vì trường hợp bắt vị trí số 1 và vị trí cuối của danh
			danh ta đã bắt rồi*/
		{
			int dem = 0;//Xác định vị trí cần thêm 
			node* g = new node;//Node g chính là node giữ mối liên kết với node nằm trước node q trong danh sách	 

			//Duyệt từ đầu danh sách đến cuối danh sách để tìm node q => Chính là tìm ra vị trí cần thêm node p vào
			for (node* k = l.pHead; k != NULL; k = k->pNext) {
				if (dem == viTri)//Tìm vị trí ví trí cần thêm
				{
					//Việc thêm node p trước node q thực chất chỉ là thêm node p vào sau node g(Tức là node nằm trước node q)
					node* h = KhoiTaoNode(p->data);/*Mõi lần phát hiện 1 node q thì khởi tạo 1 node p mới đó là node h=> khởi
					tạo h mới bằng cách lấy data của node p nhưng địa chỉ sẽ được đổi mới*/
					h->pNext = k;//Bước 1 cho node h trỏ đến node k => Thì cũng chính là cho node h trỏ đến node q		
					g->pNext = h;//Bước 2 cho node g trỏ đến node h
					break;/*Vì vị trí danh sách liên kết đơn là riêng biệt tức chỉ tồn tại 1 vị trí nhau nên sau khi tìm được
					phải thoát vòng lặp không cần duyệt nữa*/
				}
				g = k;//Giữ liên kết với node nằm trước node q trong danh sách
			}
		}
	}

	//Hàm xóa phần tử đầu trong danh sách 
	void XoaDau(List & l) {
		//Nếu danh sách rỗng 
		if (l.pHead == NULL) {
			return;
		}
		node* p = l.pHead; //Tạo ra node p cho bằng với node đầu tiên trong danh sách. Node p là node sẽ bị xóa
		l.pHead = l.pHead->pNext;//Cập nhật lại l.pHead(tức là con trỏ đầu) là phần phần tử kế tiếp
		delete p;
	}

	//Xóa phần tử cuối trong danh sách
	void XoaCuoi(List & l) {
		//Nếu danh sách rỗng 
		if (l.pHead == NULL) {
			return;
		}
		/*Trường hợp trong danh sách chỉ có 1 phần thì vòng lặp for sẽ không biết phần tử nào là nằm kế nó(Tức không xác
		định được node kế cuối) để xóa đi thằng cuối */
		else if (l.pHead->pNext == NULL)
		{
			XoaDau(l);
			return;
		}
		//Duyệt từ đầu danh sách đến thằng kế cuối
		for (node* k = l.pHead; k != NULL; k = k->pNext) {
			//Phát hiện thằng kế cuối
			if (k->pNext == l.pTail) {
				delete l.pTail;//Xóa đi phần tử cuối
				k->pNext = NULL;//Cho con trỏ của node kế cuối trỏ đến vùng nhớ NULL
				l.pTail = k;//Cập nhật lại l.pTail là node kế cuối
				return;
			}
		}
	}

	//Xóa node nằm sau node q
	void XoaNodeSauNodeQ(List & l, node * q) {

		if (l.pHead == NULL)
		{
			return;
		}
		if (q->data == l.pHead->data && l.pHead->pNext == NULL) {
			XoaDau(l);
			return;
		}
		//Duyệt danh sách từ đầu đến cuối để tìm node q
		for (node* k = l.pHead; k != NULL; k = k->pNext) {
			if (k->data == q->data)//Phát hiện node q
			{
				node* g = k->pNext;/*Node g chính là node nằm sau node k(Node k cũng chính là node q)
				=> Node g cũng là node mà ta sẽ xóa*/
				k->pNext = g->pNext;/*Cập nhật mối liên kết giữa node k và node nằm sau node g => Cũng chính là mối liên kế giữa node
				q và node nằm sau node g*/
				delete g;//Xóa node nằm sau node q 
				return;

			}

		}
	}
	//Xóa node bất kì trong danh sách - hay còn gọi là xóa 1 node có khóa k bất kì 
	void XoaPhanTuBatKi(List & l, int x) {

		//Bắt trường hợp danh sách đang rỗng
		if (l.pHead == NULL)
		{
			return;
		}

		//Node cần xóa nằm ở đầu danh sách
		if (l.pHead->data == x)
		{
			XoaDau(l);
			return;
		}

		//Nếu node cần xóa nằm ở cuối danh sách
		if (l.pTail->data == x)
		{
			XoaCuoi(l);
			return;
		}

		node* g = new node;/*Node g là node trỏ đến node nằm trước node cần xóa. Tức là nằm trước phần tử x(x là phần tử muốn
		xóa) => g Cũng chính là node q*/

		//Duyệt danh sách từ đầu đến cuối 
		for (node* k = l.pHead; k != NULL; k = k->pNext) {
			/*Lí do ta không gọi lại hàm XoaPhanTuSauNodeQ mà làm bằng thủ công là vì trong hàm XoaPhanTuSauNodeQ có 1
			vòng lặp trong để duyệt qua các phần tử mà ở đây ta lại có thêm 1 vòng lặp nữa thì dẫn đến chương trình của
			ta sẽ xử lí rất là chậm k tối ưu*/
			if (k->data == x) {//Phát hiện phần tử cần xóa
				g->pNext = k->pNext;/*Cập nhật mối liên kết giữa node g và node nằm sau node x => Cũng chính là mối liên kế
				giữa node q và node nằm sau node x */
				delete k;//Xóa node k tức là xóa node x(ta nhập vào) 
				return;
			}
			g = k;/*Cho node g trỏ đến node k. Tức là lúc này k chính là node q ,còn khi điều kiện đúng thì trong điều kiện
			if k là node x vì khi không thỏa mãn đk or thực hiện xong đk thì g mới cập nhật lại là bằng k còn nếu điều kiện
			mà đúng thì g vẫn bằng k của vòng lặp trước. Ví dụ danh sách có 4 phần tử 1 2 3 4 , và ta nhập x tức là phần tử
			muốn xóa là 2 thì chương trình thực thi:
			- vòng lặp duyệt tuần tự từng phần tử từ đầu đến cuối
			+ Đầu tiên k = 1 không bằng x tức là 1 != 2 => không thực hiện khối lệnh bên trong if , nên chạy xuống gán g = k
			tức g = 1
			+ Tiếp k = 2 thì thỏa đk if k = x tức 2 = 2 => Khối lệnh if thực thi, dùng con trỏ của g(mà lúc này g vẫn bằng 1
			vì đang phải thực hiện khối lệnh của if nên khi thực hiện xong khối lệnh if thì g mới cập nhật lại là = 2) dấu bằng
			tức là trỏ đến phần tử phía sau(bằng cách dùng k->pNext) x, rồi xóa k(x) là xong khi xong khối lệnh của x thì g
			mới cập	nhật lại = 2.*/
		}
	}

	//Hàm giải phóng vùng nhớ trong danh sách
	void giaPhongDanhSach(List& l) {
		
		
		node* k = NULL;
		while (l.pHead != NULL) 
		{
			 k = l.pHead;/*Giải phóng bộ nhớ thì phải cập nhật lại pHead , vì nếu ta xóa luôn pHead thì chương trình
			 của ta sẽ bị lỗi nên Khi bạn giải phóng bộ nhớ của danh sách liên kết đơn mà không cập nhật con trỏ pHead,
			 có thể dẫn đến vấn đề gọi là "dangling pointer" (con trỏ treo), khi con trỏ trỏ đến một vùng nhớ không còn
			 hợp lệ.*/   
			l.pHead = l.pHead->pNext;
			delete k;
		}

	}


	//Hàm MENU - xử lí các vấn đề của bài 
	void Menu(List & l) {
		while (true) {
			system("cls");
			cout << "\n\t1.Nhap them Node(Phan tu moi) vao trong danh sach";
			cout << "\n\t2.Xuat danh sach lien ket don ";
			cout << "\n\t3.Them node p vào sau node q trong danh sach";
			cout << "\n\t4.Them node p vao truoc node q trong danh sach";
			cout << "\n\t5.Them node p vao vi tri bat ki trong danh sach";
			cout << "\n\t6.Xoa phan tu dau trong danh sach";
			cout << "\n\t7.Xoa phan tu cuoi trong danh sach";
			cout << "\n\t8.Xoa phan tu nam sau node q trong danh sach";
			cout << "\n\t9.Xoa phan tu bat ki trong danh sach";
			cout << "\n\t0.Thoat chuong trinh";

			cout << "\n\n\tMoi lua chon: ";
			short luaChon;
			cin >> luaChon;
			if (luaChon < 0 || luaChon > 9) {
				cout << "Nhap sai, can nhap lai lua chon tuon ung !";
				system("Pause");
			}
			else if (luaChon == 1) {
				n++;//Cách 2 dùng biến toàn cục để chứa phần tử sau mõi lần thêm 
				int x;
				cout << "\nNhap gia tri so nguyen: ";
				cin >> x;
				node* p = KhoiTaoNode(x);//Khởi tạo 1 cái node
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
				node* p = KhoiTaoNode(x);
				ThemNodePvaoSauNodeQ(l, p);//Them node p vào sau node q trong danh sách liên kết đơn l
			}
			else if (luaChon == 4)
			{
				int x;
				cout << "Nhap gia tri can them vao truoc node q: ";
				cin >> x;
				node* p = KhoiTaoNode(x);
				ThemNodePVaoTruocNodeQ(l, p);//Them node p vào trước node q trong danh sách liên kết đơn l
			}
			else if (luaChon == 5)
			{
				//Cách 1: 
				//Vòng lặp để đánh số cho phần tử trong danh sách liên kết
#if 0
				int n = 0;
				for (node* k = l.pHead; k != NULL; k = k->pNext)
					n++;
#endif 

				//Khởi tạo giá trị cho node cần thêm vào( là node p)
				int x, viTri;
				cout << "Nhap gia tri can them vao vi tri bat ky trong danh sach: ";
				cin >> x;
				node* p = KhoiTaoNode(x);

				//Nhập vị trí cần thêm cho node p => Cần kiểm tra điều kiện
				do {
					cout << "Nhap vi tri can them vao trong danh sach: ";
					cin >> viTri;
					if (viTri < 1 || viTri > n + 1) {
						cout << "\nVi tri can them tu 1 den " << n + 1 << " : ";
						system("Pause");
					}

				} while (viTri < 1 || viTri > n + 1);
				//Them node p vào vị trí bất kỳ trong danh sách liên kết đơn l
				//ThemNodePVaoViTriBatKy(l, p, viTri, n); Cách 1
				ThemNodePVaoViTriBatKy(l, p, viTri);/*Cách 2 dùng biến toàn cục để chứa các phần tử trong danh sách sau mõi
				lần thêm, đỡ tốn time hơn cách 1 vì cách 1 mõi lần thêm phải duyệt qua danh sách để đếm số lượng phần tử trong
				danh sách tức là n++ sau mõi lần duyệt của vòng lặp*/
				n++;
			}
			else if (luaChon == 6)
			{
				XoaDau(l);
			}
			else if (luaChon == 7)
			{
				XoaCuoi(l);
			}
			else if (luaChon == 8)
			{
				int x;
				cout << "Nhap node q: ";
				cin >> x;
				node* q = KhoiTaoNode(x);
				XoaNodeSauNodeQ(l, q);
			}
			else if (luaChon == 9)
			{
				int x;
				cout << "\nNhap phan tu muon xoa: ";
				cin >> x;
				XoaPhanTuBatKi(l, x);
			}
			else if (luaChon == 0)
				break;
		}
	}

	int main()
	{
		List l;
		KhoiTaoDSLKD(l);/*Luôn luôn gọi hàm khởi tạo danh sách liên kết đơn(vì nó có 2 con trỏ đầu và cuối để quản lí danh sách)
		trước khi thao tác với danh sách*/
		Menu(l);

		system("Pause");
	}


	