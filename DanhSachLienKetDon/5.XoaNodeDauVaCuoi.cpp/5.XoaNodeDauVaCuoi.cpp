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
				node* h = KhoiTaoNode(p->data);/*Mõi lần phát hiện 1 node q thì khởi tạo 1 node p mới đó là node h=> khởi
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

		//Trường hợp có 2 node q trở lên trong danh sách 
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
					//Việc thêm node p trước node q thực chất chỉ là thêm node p vào sau node g(g Tức là node nằm trước node q)
					node* h = KhoiTaoNode(p->data);/*Mõi lần phát hiện 1 node q thì khởi tạo 1 node p mới đó là node h=> khởi
					tạo h mới bằng cách lấy data của node p nhưng địa chỉ sẽ được đổi mới. Vì nếu ta mà khởi tạo node p ở ngoài
					đk if của vòng lặp thì node p chỉ được khởi tạo 1 lần và nó sẽ lấy địa chỉ cũ của node p đó liên kết với
					node q khác trong danh sách sẽ làm mất liên kết với các node và mất phần tử. Vậy nên việc ta khởi tạo 1
					node p nằm ngoài đk if của vòng lặp thì ta phải tạo 1 bản sao của node p ở trong đk if của vòng lặp for 
					để mõi khi tìm thấy node q mà trong danh sách có 2 node q trở lên thì sau lần thêm node p vào trước node
					q lần đầu tiên cứ mõi lần duyệt thấy node q mới trong mõi lần tiếp theo của danh sách thì node h sẽ tạo
					ra 1 bản sao của node p với data của node p còn địa chỉ thì hoàn toàn mới, tránh trường hợp trong danh 
					sách có 2 node q trở lên mà ta chỉ khởi tạo node p ở ngoài đk if của vòng lặp thì node p chỉ được khởi 
					tạo 1 lần và nó sẽ lấy địa chỉ cũ của node p đó liên kết với node q khác trong danh sách sẽ làm mất liên 
					kết với các node và mất phần tử*/
					h->pNext = k;//Bước 1 cho node h trỏ đến node k => Thì cũng chính là cho node h trỏ đến node q		
					g->pNext = h;//Bước 2 cho node g trỏ đến node h
				}
				g = k;/*Giữ liên kết với node nằm trước node q trong danh sách. Tức node g lúc này chính là node nằm trước node
				q trong danh sách. vì g chỉ được cập nhật khi đk if sai or xong đk if, 
				- ví dụ : danh sách ta có các phần tử 1 2 3 ta nhập p = 4 và q = 2 thì hàm thêm node p vào trước node p sẽ chạy
				như sau: 
				+ lần duyệt đầu tiên là số: k = 1 , q = 2 
				-> q = 2 không bằng k vì k = 1 đk if sai nên khối lệnh bên trong if bị bỏ qua
				=> q = k tức g = 1
				+ lần duyệt đầu tiên là số: k = 2 ,
				-> q = 2 thõa mãn k = q tức là 2 = 2 đk kiện if đúng khối lệnh bên trong if đc thực thi: 
				# node* h = KhoiTaoNode(p->data); tức là h là bản sao của p với data là của p nhưng địa chỉ mới nên lệnh này là
				khởi tạo 1 node h(được rót data của p khi ta nhập p ở ngoài vòng lặp và đk if cụ thể bài này ta nhập ở hàm menu)
				nên h = 4
				# h->pNext = k; tức là cho node muốn thêm vào là node h(p) trỏ đến(liên kết) với node k(node k lúc này = 2 và node
				k cũng chính là node q luôn)
				# g->pNext = h; sau khi đã cho node h(cũng là p) liên kết đến node k(cũng là q) thì ta sẽ cập nhật lại node g(
				g lúc này chính là node nằm trước node q vì lần duyệt 2 này đk của if đúng nên ta phải thực hiện khối lệnh trước
				nên g vẫn mang giá trị cũ của lần duyệt đầu tiên là g = 1 nên g là node nằm trước node q) trỏ đến(Liên kết) với
				node h(cũng là node p) 
				=> danh sách ta lúc này đã thêm được node p = 4 vào trước node q = 2 là: 1 4 2 3
				# sau khi thực hiện xong khối lệnh bên trong đk if thì chương trình sẽ ra đk if và đến dòng lệnh g = k; thì g 
				lúc này mới được cập nhật lại là g = 2.*/
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

	//Thêm node p vào bất kì vị trí nào trong danh sách
	//Cách 2 dùng biến cục bộ cho biến n 
	//thì hàm sẽ không có tham số n truyền vào để chứa phần tử trong danh sách nữa 
	void ThemNodePVaoViTriBatKy(List & l, node * p, int viTri) {

		//Danh sách đang rỗng. Bắt trường hợp danh sách ban đầu là rỗng
		if (l.pHead == NULL || viTri == 1)
			//Thêm node p vào đầu danh sách l
			ThemVaoDau(l, p);

		/*Bắt trường hợp muốn thêm vào cuối danh sách ban đầu chỉ có n phần
		tử nên khi thêm vào cuối thì phải tăng số khoảng n lên là n + 1 */
		 if (viTri == n + 1)
			//Thêm node p vào cuối danh sách
			ThemVaoCuoi(l, p);

		else{/*Bắt trường hợp vị trí nằm trong đoạn từ [2, n]. Vì trường hợp bắt vị trí số 1 và vị trí cuối của danh
			danh ta đã bắt rồi*/
		
			int dem = 1;//Xác định vị trí cần thêm 
			node* g = new node;//Node g chính là node giữ mối liên kết với node nằm trước node q trong danh sách	 

			//Duyệt từ đầu danh sách đến cuối danh sách để tìm node q => Chính là tìm ra vị trí cần thêm node p vào
			for (node* k = l.pHead; k != NULL; k = k->pNext) {
				if (dem == viTri)//Tìm vị trí ví trí cần thêm
				{
					/*Việc thêm node p vào vị trí bất kì trong danh sách thực chất chỉ là thêm node p vào sau node 
					g(g Tức là node nằm trước node q)*/
					node* h = KhoiTaoNode(p->data);/*Mõi lần phát hiện 1 node q thì khởi tạo 1 node p mới đó là node h=> khởi
					tạo h mới bằng cách lấy data của node p nhưng địa chỉ sẽ được đổi mới. Vì nếu ta mà khởi tạo node p ở ngoài
					đk if của vòng lặp thì node p chỉ được khởi tạo 1 lần và nó sẽ lấy địa chỉ cũ của node p đó liên kết với
					node q khác trong danh sách sẽ làm mất liên kết với các node và mất phần tử. Vậy nên việc ta khởi tạo 1
					node p nằm ngoài đk if của vòng lặp thì ta phải tạo 1 bản sao của node p ở trong đk if của vòng lặp for 
					để mõi khi tìm thấy node q mà trong danh sách có 2 node q trở lên thì sau lần thêm node p vào sau node
					g lần đầu tiên cứ mõi lần duyệt thấy node q mới trong mõi lần tiếp theo của danh sách thì node h sẽ tạo
					ra 1 bản sao của node p với data của node p còn địa chỉ thì hoàn toàn mới, tránh trường hợp trong danh 
					sách có 2 node q trở lên mà ta chỉ khởi tạo node p ở ngoài đk if của vòng lặp thì node p chỉ được khởi 
					tạo 1 lần và nó sẽ lấy địa chỉ cũ của node p đó liên kết với node q khác trong danh sách sẽ làm mất liên 
					kết với các node và mất phần tử*/
					h->pNext = k;//Bước 1 cho node h trỏ đến node k => Thì cũng chính là cho node h trỏ đến node q		
					g->pNext = h;//Bước 2 cho node g trỏ đến node h	
					break;/*Vì vị trí danh sách liên kết đơn là riêng biệt tức chỉ tồn tại 1 vị trí nhau nên sau khi tìm được
					phải thoát vòng lặp không cần duyệt nữa*/
				}
				dem++;
				g = k;//Giữ liên kết với node nằm trước node q trong danh sách
			}
		}
	}

	//Hàm xóa phần tử đầu trong danh sách 
	void XoaDau(List& l) {
		//Nếu danh sách rỗng 
		if (l.pHead == NULL){
			return;
	}
			node * p = l.pHead; //Tạo ra node p cho bằng với node đầu tiên trong danh sách. Node p là node sẽ bị xóa
			l.pHead = l.pHead->pNext;//Cập nhật lại l.pHead(tức là con trỏ đầu) là phần phần tử kế tiếp
			delete p;
	}

	//Xóa phần tử cuối trong danh sách
	void XoaCuoi(List& l) {
		//Nếu danh sách rỗng 
		if (l.pHead == NULL) {
			return;
		}
		/*Trường hợp trong danh sách chỉ có 1 phần thì vòng lặp for sẽ không biết phần tử nào là nằm kế nó(Tức không xác
		định được node kế cuối) để xóa đi thằng cuối */
		else if(l.pHead->pNext == NULL)
		{
			XoaDau(l);
			return;
		}

		/*Cách 1: Xóa phần tử ở cuối danh sách cách này bị thừa ở chỗ(Xóa đi con trỏ cuối pTail) delete l.pTail; và không tối
		ưu vì việc xóa phần tử cuối thật chất không cần dùng đến lệnh delete để xóa phần tử cuối mà ta chỉ duyệt đến phần tử
		kế cuối sau đó cho phần tử kế cuối trỏ đến NULL rồi cập nhật lại pTail trỏ đến phần tử kế cuối để đánh dấu phần tử kế
		cuối bây giờ là phần tử cuối trong danh sách, thì lúc này phần cuối không còn phần tử nào liên kết với phân tử cuối 
		tức là con trỏ giữa phần tử kế cuối và phần tử kế cuối đã bị mất từ khi ta cho phần tử kế cuối trỏ đến NULL nên không
		còn mối liên kết nào liên kết với phần tử ở cuối danh sách nữa vì vậy phần tử cuối sẽ bị đứt liên kết và biến mất chứ
		không cần phải gọi đến lệnh delete để xóa phần tử cuối chỉ cần cập nhật lại muốn liên kết là có thể xóa được phần tử 
		ở cuối danh sách, Do danh sách liên kết đơn là tập hợp các mối liên kết giữa các node với nhau nên việc thêm xóa các
		node chính là cập nhật lại các mối liên kết giữa các node với nhau mà thôi. Vì cách này đã ghi vào vỡ nên để lại đây
		để khi quên thì mở lại để nhớ, Ưu tiên xóa phần tử ở cuối danh sách bằng cách 2 vì nó tối ưu hơn.*/ 
#if 0
    //Duyệt từ đầu danh sách đến thằng kế cuối
		for (node* k = l.pHead; k != NULL; k = k->pNext) {
			//Phát hiện thằng kế cuối
			if (k->pNext == l.pTail){/*Vì phần tử cuối là phần tử được con trỏ cuối pTail trỏ đến để đánh dấu là phần tử cuối
				cùng trong danh sách(Tức là phần tử nào được con trỏ cuối pTail trỏ đến thì phần tử đó là phần tử cuối vì
				ta tạo ra con trỏ pTail để quản lí việc thêm xóa cuối cho dễ nên tạo ra pTail trỏ đến phần tử cuối là để đánh
				dấu phần tử được pTail trỏ đến là phần tử cuối của danh sách và pTail chỉ là 1 con trỏ để đánh dấu phần tử
				cuối của danh sách chứ pTail không phải là phần tử cuối của danh sách). Nên dòng này ta duyệt phần tử nào mà
				trỏ đến phần tử được pTail trỏ đến thì phần tử đó là phần tử kế cuối*/
				delete l.pTail;//Xóa đi con trỏ trỏ đến phần tử cuối
				k->pNext = NULL;//Cho con trỏ của node kế cuối trỏ đến vùng nhớ NULL
				l.pTail = k;//Cập nhật lại l.pTail là node kế cuối
				return;
				/*Sau 3 bước trên là Xóa đi con trỏ trỏ đến phần tử cuối(pTail) sau đó cho con trỏ của node kế cuối trỏ đến 
				vùng nhớ NULL cuối cùng là Cập nhật lại l.pTail là node kế cuối thì phần tử cuối cùng trong danh sách đã bị
				đứt liên kết và mất đi. Nhưng việc xóa đi pTail là thừa vì ta cập nhật lại pTail là phần tư kế cuối thì pTail
				bây giờ sẽ trỏ đến phần tử kế cuối, phần tử cuối bị đứt liên kết và mất đi nên không cần bước delete l.pTail;*/
			}
		}
#endif
		/*Cách 2: Tối ưu, Bỏ qua việc delete l.pTail; vì khi vì ta cập nhật lại pTail là phần tư kế cuối thì pTail bây giờ sẽ 
		trỏ đến phần tử kế cuối, phần tử cuối bị đứt liên kết và mất đi nên không cần bước delete l.pTail;*/

		//Duyệt từ đầu danh sách đến thằng kế cuối
		for (node* k = l.pHead; k != NULL; k = k->pNext) {
			//Phát hiện thằng kế cuối
			if (k->pNext == l.pTail) {/*Vì phần tử cuối là phần tử được con trỏ cuối pTail trỏ đến để đánh dấu là phần tử cuối
				cùng trong danh sách(Tức là phần tử nào được con trỏ cuối pTail trỏ đến thì phần tử đó là phần tử cuối vì
				ta tạo ra con trỏ pTail để quản lí việc thêm xóa cuối cho dễ nên tạo ra pTail trỏ đến phần tử cuối là để đánh
				dấu phần tử được pTail trỏ đến là phần tử cuối của danh sách và pTail chỉ là 1 con trỏ để đánh dấu phần tử
				cuối của danh sách chứ pTail không phải là phần tử cuối của danh sách). Nên dòng này ta duyệt phần tử nào mà
				trỏ đến phần tử được pTail trỏ đến thì phần tử đó là phần tử kế cuối*/
				k->pNext = NULL;//Cho con trỏ của node kế cuối trỏ đến vùng nhớ NULL
				l.pTail = k;//Cập nhật lại l.pTail là node kế cuối
				return;
				/*Sau 2 bước trên là cho con trỏ của node kế cuối trỏ đến vùng nhớ NULL cuối cùng là Cập nhật lại l.pTail là 
				node kế cuối thì phần tử cuối cùng trong danh sách đã bị đứt liên kết và mất đi.*/
			}
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
			cout << "\n\t0.Thoat chuong trinh";

			cout << "\n\n\tMoi lua chon: ";
			short luaChon;
			cin >> luaChon;
			if (luaChon < 0 || luaChon > 7) {
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
			else if(luaChon == 6)
			{
				XoaDau(l);
			}
			else if (luaChon == 7)
			{
				XoaCuoi(l);
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

	