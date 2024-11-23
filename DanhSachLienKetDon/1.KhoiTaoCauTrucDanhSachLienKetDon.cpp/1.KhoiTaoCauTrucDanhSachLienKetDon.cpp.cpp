#include <iostream>
using namespace std;
/*Bài toán: Nhập danh sách liên kết đơn các số nguyên. Tìm giá trị lơn nhất trong danh sách*/

//================ KHAI BÁO CẤU TRÚC DANH SÁCH LIÊN KẾT ĐƠN CÁC SỐ NGUYÊN ================== 

/*Khai báo cấu trúc 1 cái Node - nút. Một cái node luôn bất di bất dịch là có data và con trỏ
Như hình minh họa trong vở 1 cái node phải có data và con trỏ(Để liên kết các node lại vs nhau)*/

/*struct là một cách để ta tự định nghĩa một kiểu dữ liệu mới bằng cách kết hợp nhiều thành phần
khác nhau lại với nhau dưới một tên chung. Tạo một kiểu dữ liệu cụ thể như struct giúp ta tổ chức
dữ liệu một cách logic và có cấu trúc hơn.*/
struct node
{
	int data;/*Dữ liệu chứa trong 1 cái node.Vì bài là danh sách các số nguyên nên data là kiểu int, có thể thay đổi data
			 tùy vào yêu cầu đề bài vd có thể như này "SinhVien data;"*/
	struct node* pNext;//Con trỏ liên kết giữa các node với nhau
};
typedef struct node NODE;/*Thay thế struct node thành NODE vì khi sử dụng đến node thì chỉ cần lấy tên thay thế ra để sài
						  chứ không cần mõi lần sd phải gọi dài dòng là struct node. Đó là trường hợp ngôn ngữ C thường
						  phải khai báo tên thay thế như vậy để mõi lần sử dụng không cần phải gọi dài dòng là struct node
						  còn với c++ chỉ cần gọi node(Tức tên của nút đã tạo) là được không cần tên thay thế cũng được*/


						  //Khai báo cấu trúc của danh sách liên kết đơn
struct list
{
	NODE* pHead;//Node quản lí đầu danh sách. NODE chính là con trỏ 
	NODE* pTail;//Node quản lí cuối danh sách
	/* trong c++ gọi node là có thể sử dụng được cụ thể tạo con trỏ quản lí node đầu của danh sách node* pHead; là đc
	không cần phải khai báo và dùng tên thay thế vì đó chỉ dùng cho C */
};
typedef struct list LIST;//Thay thế struct list bằng tên LIST. Tuongư tự như tên thay thế của struct node


//================ KHỞI TẠO CẤU TRÚC DANH SÁCH LIÊN KẾT ĐƠN CÁC SỐ NGUYÊN ================== 
//Hàm khởi tạo danh sách liên kết đơn
void KhoiTao(LIST& l) {// Tham chiếu để lưu lại giá trị khi danh sách liên kết có sự thay đổi
	/*Mục đích của khởi tạo danh sách liên kết đơn là chứa các NODE - nút. Do danh sách chưa có phần tử nào nên dùng
	hai con trỏ(pHead và pTail) để trỏ đến NULL */
	l.pHead = NULL;
	l.pTail = NULL;
}

//Hàm khởi tạo NODE 
NODE* khoiTaoNODE(int x) {/*Hàm khởi tạo kiểu node thì giá trị trả về là node và node* là 1 con trỏ nên kiểu dữ liệu trả về
	là 1 con trỏ, vì kiểu dữ liệu(data) của 1 node là kiểu số nguyên nên truyền vào cho node là kiểu int để ra có thể truyền
	dữ liệu tương ứng với node*/
	NODE* p = new NODE; /*Cấp phát vùng nhớ cho NODE p, việc tạo con trỏ quá quen thuộc vì lập trình java opp đã làm khá nhiều
	ta cũng có thể hiểu là khởi tạo 1 đối tượng thuộc struct node dùng để truy xuất các phần tử bên trong struct node cũng đc*/
	if (p == NULL) {//Kiểm tra xem đã cấp phát bộ nhớ cho con trỏ thành công chưa, vì nếu bộ nhớ mà đầy thì không thể cấp phát được
		cout << "\nKhong du bo nho de cap phat !";
		return NULL;
	}
	p->data = x;//truyền giá trị x vào cho data
	p->pNext = NULL;//Đầu tiên khai báo node thì node đó chưa có liên kết đến node nào cà => con trỏ sẽ trỏ đến NULL
	return p;//trả về NODE p vừa khởi tạo 
}

//Hàm thên NODE vào đầu danh sách liên kết 
void themVaoDau(LIST& l, NODE* p) {//NODE* p là 1 cái NODE - nút để thêm vào danh sách LIST

	//Danh sách đang rỗng
	if (l.pHead == NULL)/*Ta tạo ra 2 con trỏ đầu là pHead và cuối là  pTail để quản lí danh sách LIST, Nếu danh sách đầu
	bằng NULL thì chắc chắn danh sách là rỗng*/
		l.pHead = l.pTail = p;//node đầu cũng chính là node cuối
	else
		p->pNext = l.pHead;//Cho con trỏ của node cần thêm là node p(Tức là NODE* p) liên kết đến node đầu(pHead)  
	l.pHead = p; //Cập nhật lại pHead chính là node p
}

//Hàm thêm Node p vào cuối danh sách đơn
void themVaoCuoi(LIST& l, NODE* p) {
	if (l.pTail == NULL)
		l.pHead = l.pTail = p;
	else
		l.pTail->pNext = p;//Cho con trỏ của pTail(tức là con trỏ của node cuối) liên kết nới node p
	l.pTail = p;//cập nhật lại p là node cuối
}

//Hàm xuất danh sách liên kết đơn 
void xuatDanhSach(LIST l) {

	//Danh sách liên kết thì phải duyệt tuần tự từ đầu đến cuối danh sách.
	/*Mảng thì duyệt từng phần tử bằng vòng lặp for(short i = 0 ; i < n ; i++). Ở danh sách liên kết đơn thì phải
	duyệt tuần tự các phần tử trong danh sách từ đầu đến cuối. Mà danh sách liên kết đơn(LIST) của ta đã tạo ra 2
	con trỏ đầu pHead và cuối pTail để quản lí danh sách nên ta duyệt từ đầu là từ con trỏ đầu pHead và con trỏ
	cuối pTail bằng vòng lặp for như bên dưới*/
	for (NODE* k = l.pHead; k != NULL; k = k->pNext) {/*K != NULL tức là duyệt đến cuối k có phần tử trong danh sách
	nữa thì dừng lại, còn NODE* k = l.pHead là bắt đầu từ ptu đầu danh sách là con trỏ k, k = k ->pNext tuần tự từng
	phần tử 1 cho đến cuối danh sách*/
		cout << k->data << " ";/*K là 1 node và ta muốn Xuất ra data của node thì phải k trỏ đến data vì ta đang làm việc
		data, còn muốn xuất ra node không thì chỉ cần k thôi	*/
	}
}

//Hàm tìm giá trị lơn nhất trong danh sách 
int timMax(LIST l) {//Truyền vào danh sách để duyệt và tìm ra được phần tử lớn nhất trong danh sách
	int max = l.pHead->data;/*Giả sử node đầu là phần tử lớn nhất, cũng giống mảng trong thuật toán tìm phần tử lớn nhất
	ta cũng gán giả sử 1 ptu bất kỳ là ptu lớn nhất rồi so với các phần tử trong mảng nếu ptu lớn hơn thì cập nhật lại giá
	trị. Thì ở danh sách liên kết ta giả sử phần tử đầu tiên trong danh sách là max rồi đi so với từng phần tử còn lại trong
	danh sách*/

	//Bắt đầu duyệt từ node thứ hai
	for (NODE* k = l.pHead; k != NULL; k = k->pNext)
	{
		if (max < k->data)
			max = k->data;//Cập nhật lại giá trị max
	}
	return max;
}

int main()
{
	LIST l;
	KhoiTao(l);//Khởi tạo danh sách liên kết đơn

	int n;
	cout << "\nNhap so luong node can them :";
	cin >> n;

	//Vòng lặp nhập n NODE - nút 
	for (short i = 1; i <= n; i++) {
		int x;
		cout << "\nNhap gia tri so nguyen: ";
		cin >> x;

		NODE* p = khoiTaoNODE(x);/*Khởi tạo ra 1 NODE số nguyên. Vì hàm khoiTaoNODE(x) trả về là 1 cái NODE - nút vì vậy
		ta phải khởi tạo 1 cái NODE* p là con trỏ để chứa nó ta khởi tạo 1 cái khoiTaoNODE và đưa dữ liệu vào data của 1 cái
		node đấy tức là x(Số nguyên) */
		themVaoDau(l, p);//Thêm NODE p vào đầu danh sách liên kết đơn
		themVaoCuoi(l, p);//Thêm NODE p vào cuối danh sách liên kết đơn
	}

	/*Do dùng Hàm thêm vào đầu danh sách liên kết đơn mõi khi có phần tử mới nên hàm xuất sẽ xuất ra 1 dãy các phần tử ngược lại
	so với thứ tự các phần tử mà ta nhập vào cụ thể nhập vào 5 4 3 2 1 xuất 1 2 3 4 5. Vì ta dùng hàm thêm vào đầu tức là thằng
	đầu tiên nhập vào là số 5 sau đó là số 4 do thêm vào đầu danh sách thì số 4 sẽ đứng trước số 5 trong danh sách và cứ thế các
	phần tử phía sau ta nhập sẽ được thêm vào tuần tự như vậy*/
	cout << "\nDANH SACH LIEN KET DON\n";
	xuatDanhSach(l);

	cout << "\nGia tri lon nhat: " << timMax(l);
	//system("Pause");
}



#if 0
#include <iostream>
using namespace std;

//================ KHAI BÁO CẤU TRÚC DANH SÁCH LIÊN KẾT ĐƠN CÁC SỐ NGUYÊN ================== 


struct node
{
	int data;
	struct node* pNext;
};
typedef struct node NODE;

//Khai báo cấu trúc của danh sách liên kết đơn
struct list
{
	NODE* pHead;
	NODE* pTail;
};
typedef struct list LIST;


//================ KHỞI TẠO CẤU TRÚC DANH SÁCH LIÊN KẾT ĐƠN CÁC SỐ NGUYÊN ================== 
//*******Hàm khởi tạo****************
void KhoiTao(LIST& l) {
	l.pHead = NULL;
	l.pTail = NULL;
}

//Hàm khởi tạo NODE 
NODE* khoiTaoNODE(int x) {
	NODE* p = new NODE;
	if (p = NULL) {
		cout << "\nKhong du bo nho de cap phat !";
		return NULL;
	}
	p->data = x;
	p->pNext = NULL;
	return p;
}

//Hàm thên NODE vào đầu danh sách liên kết 
void themVaoDau(LIST& l, NODE* p) {

	//Danh sách đang rỗng
	if (l.pHead == NULL)
		l.pHead = l.pTail = p;
	else
		p->pNext = l.pHead;
}

//Hàm thêm Node p vào cuối danh sách đơn
void themVaoCuoi(LIST& l, NODE* p) {
	if (l.pTail == NULL)
		l.pHead = l.pTail = p;
	else
		l.pTail->pNext = p;
}

//Hàm xuất danh sách liên kết đơn 
void xuatDanhSach(LIST l) {

	for (NODE* k = l.pHead; k != NULL; k = k->pNext) {
		cout << k->data << " ";
	}
}

int main()
{
	LIST l;
	KhoiTao(l);
	int n;
	cout << "\nNhap so luong node can them :";
	cin >> n;


	for (short i = 1; i <= n; i++) {
		int x;
		cout << "\nNhap gia tri so nguyen: ";
		cin >> x;

		NODE* p = khoiTaoNODE(x);
		themVaoDau(l, p);
	}

	cout << "\n\n\tDANH SACH LIEN KET DON\N";
	xuatDanhSach(l);

	system("Pause");
}
#endif

