#include<iostream>
#include<string>
#include<fstream>//Thư viện ghi đọc file 
using namespace std;


//Khai báo cấu trúc ngày 
struct Date
{
	int Ngay;
	int Thang;
	int Nam;
};

//Hàm đọc dữ liệu ngày tháng năm từ file
void DocNgayThangNam(ifstream &filein, Date &date) {/*ifstream là hàm đọc file trong thư viện fstream, tham
	chiếu cho phép ta thao tác trực tiếp với các đối tượng trong hàm và áp dụng các thay đổi đó bên ngoài 
	hàm mà không cần sao chép dữ liệu. Tức là tham chiếu để khi đọc xong thì dữ liệu sau khi được đọc sẽ được lưu lại*/
	filein >> date.Ngay;
	filein.seekg(1,1);//Tại vị trí hiện tại dịch con trỏ sang đơn vị, Để bỏ qua ký tự '/' trong file SinhVien.txt
	filein >> date.Thang;
	filein.seekg(1, 1);//Tại vị trí hiện tại dịch con trỏ sang đơn vị, Để bỏ qua ký tự '/' trong file SinhVien.txt
	filein >> date.Nam;
}

//Khai báo cấu trúc sinh viên
struct SinhVien
{
	string hoTen;
	string maSV;
	Date ngaySinh;
	float dtb;
};

//Khai báo 1 cái node sinh viên
struct node
{
	SinhVien data;
	struct node* pNext;
};

//Cấu trúc danh sách liên kết đơn
struct List
{
	node* pHead;
	node* pTail;
};

//Khởi tạo danh danh sách liên kết đơn
void KhoiTaoDSLKD(List& l) {
	l.pHead = NULL;
	l.pTail = NULL;
}

//Khởi tạo node
node* KhoiTaoNode(SinhVien sv) {
	node* p = new node;
	if (p == NULL) {
		cout << "Khoi tao khong thanh cong. Khong du bo nho !";
	}
	p->data = sv;//Đưa dữ liệu của biến sinh viên x vào data của node p
	p->pNext = NULL;//khởi tạo node p nhưng node p chưa có liên kết với phần tử nào hết
	return p;
}

//Hàm thêm 1 node sinh viên vào đầu danh sách
void ThemVaoDau(List& l, node* p) {
	if (l.pHead == NULL)
		l.pHead = l.pTail = p;
	else
	{
		p->pNext = l.pHead;
		l.pHead = p;
	}
}

///Hàm thêm 1 node sinh viên vào cuối danh sách
void ThemVaoCuoi(List& l, node* p) {
	if (l.pTail == NULL)
		l.pHead = l.pTail = p;
	else{
		l.pTail->pNext = p;
		l.pTail = p;
	}

}

//Hàm đọc dữ liệu 1 sinh viên từ File
void DocThongTin1SinhVien(ifstream &filein, SinhVien &sv) {
	//Dọc họ và tên sinh viên
	getline(filein, sv.hoTen, ',');//Đọc đến dấu phẩy thì dừng
	filein.seekg(1, 1);/*Sau khi đọc họ và tên xong đến dấu phẩy thì dừng sau đó đến khoảng trắng nên ta dùng seekg là dùng
	để tại vị trí hiện tại dịch con trỏ sang phải 1 đơn vị để bỏ 1 khoảng trắng trong file SinhVien.txt*/

   //Đọc mã sinh viên
   getline(filein, sv.maSV, ',');//Đọc đến dấu phẩy thì dừng
   filein.seekg(1, 1);/*Sau khi đọc mã sinh viên xong đến dấu phẩy thì dừng sau đó đến khoảng trắng nên ta dùng seekg là dùng
   để tại vị trí hiện tại dịch con trỏ sang phải 1 đơn vị để bỏ 1 khoảng trắng trong file SinhVien.txt*/

   //Đọc thông tin ngày tháng năm sinh
   DocNgayThangNam(filein, sv.ngaySinh);
   filein.seekg(2, 1);/*Sau khi đọc ngày tháng năm sinh xong đến dấu phẩy sau đó đến khoảng trắng nên ta dùng seekg là dùng
  để tại vị trí hiện tại dịch con trỏ sang phải 2 đơn vị để bỏ dấu phẩy và 1 khoảng trắng trong file SinhVien.txt*/

   //Đọc điểm trung bình 
   filein >> sv.dtb;
   filein.get();
}

//Hàm đọc danh sách sinh viên từ File
void DocDanhSachSinVien(ifstream& filein, List& l) {/*Vì đọc từng thằng sinh viên và lưu và danh sách liên kết đơn
nên phải truyền vào 1 dánh sách*/
   //Vì file danh sách sinh viên không có số lượng sinh viên nên ta phải đọc từ đầu đến cuối file nên ta dùng vòng lặp while
	while (!filein.eof())/*Đọc đến cuối file thì dừng. eof() Hàm này trả về true thì con trỏ chỉ vị đang nằm cuối file, mà 
	mà hàm  eof() trả về false thì con trỏ chỉ vị đang nằm đầu danh file. Phủ định tức là cho hàm trả về fale để con trỏ 
	chỉ vị nằm ở đầu danh sách*/
	{
		//Bước 1: Đọc thông tin sinh viên
		SinhVien sv;
		DocThongTin1SinhVien(filein, sv);

		//Bước 2: Khởi tạo 1 cái node sinh viên
		//Lưu vào danh sách sinh viên và danh sách lúc này được lưu bởi danh sách liên kết đơn
		node* p = KhoiTaoNode(sv);

		//Bước 3: Thêm sinh viên(Thêm node p) vào danh sách liên kết đơn các sinh viên
		ThemVaoCuoi(l,p);
	}
}

//Hàm xuất dữ liệu
void xuat(SinhVien sv) {

	cout << "\nHo Va Ten: " << sv.hoTen;
	cout << "\nMa sinh vien: " << sv.maSV;
	cout << "\nNgay thang nam sinh: " << sv.ngaySinh.Ngay<<"/"<< sv.ngaySinh.Thang<<"/"<<sv.ngaySinh.Nam;
	cout << "\nDiem trung binh: " << sv.dtb;
}

//Hàm xuất danh sách sinh viên 
void XuatDanhSachSinhVien(List l) {
	int dem = 1;
	for (node* k = l.pHead; k != NULL; k = k->pNext) {
		cout << "\n\nSinh vien thu: " << dem++;
		xuat(k->data);/*k chính là 1 cái node trong danh sách liên kết đơn, ta muốn xuất ra thông tin sinh viên 
		nên k->data mà data là 1 sinh viên*/
	}

}
int main() {
	List l;
	KhoiTaoDSLKD(l); 
		//Mở file lên
		ifstream filein;
	filein.open("SINHVIEN.txt", ios::in);
	DocDanhSachSinVien(filein, l);
	XuatDanhSachSinhVien(l);

	filein.close();			    
	system("Pause");
}