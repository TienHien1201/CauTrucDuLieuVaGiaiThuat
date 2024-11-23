/* ==ghi và đọc dữ liệu vào file Nó tương tự như cách ghi và đọc dữ liệu vào file đã học bên opp java chỉ có khác 
ngôn ngữ thôi ý nghĩa là giống nhau==

Đề bài: Khai báo cấu trúc danh sách liên kết đơn quản lí sinh viên như sau:
Định dạng trong file SINHVIEN.TXT như sau: 
- Dòng đầu tiên là thông tin của 1 sinh viên: 
+ Họ và Tên
+ Mã sinh viên 
+ Ngày tháng năm sinh: Kiểu chuỗi string định dạng kiểu MM//DD//YYY
+ Điểm trung bình học kì

vd: 
SINHVIEN.TXT 
Nguyen Van Teo, N15DCCN189, 09/06/1997, 9.0
Nguyen Van B, N14DCCN189, 10/07/1996, 8.9
Nguyen Van C, N13DCCN181, 08/09/1995, 9.5
Nguyen Van C, N13DCCN179, 10/12/1995, 8.0
Nguyen Van B, N14DCCN185, 18/10/1995, 9.5

Yêu cầu: 
1.Đọc dữ liệu từ File SINHVIEN.txt
2.Sắp xếp sinh viên tăng dần theo điểm trung bình ghi và ghi vào file SAPXEPDIEMMAX.txt
3.In danh sách sinh viên có điểm trung bình cao nhất* vào file DIEMTRUNGBINHMAX.txt
4.Tìm kiếm thông tin sinh viên dựa vào mã số sinh viên 
5.Tìm kiếm thông tin sinh viên dựa vào tên sinh viên*/
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
void DocNgayThangNam(ifstream& filein, Date& date) {/*ifstream là hàm đọc file trong thư viện fstream, tham
	chiếu cho phép ta thao tác trực tiếp với các đối tượng trong hàm và áp dụng các thay đổi đó bên ngoài
	hàm mà không cần sao chép dữ liệu. Tức là tham chiếu để khi đọc xong thì dữ liệu sau khi được đọc sẽ 
	được lưu lại*/
	filein >> date.Ngay;
	filein.seekg(1, 1);//Tại vị trí hiện tại dịch con trỏ sang phải 1 đơn vị, Để bỏ qua ký tự '/' trong file SinhVien.txt
	filein >> date.Thang;
	filein.seekg(1, 1);//Tại vị trí hiện tại dịch con trỏ sang phải 1 đơn vị, Để bỏ qua ký tự '/' trong file SinhVien.txt
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
	else {
		l.pTail->pNext = p;
		l.pTail = p;
	}

}

//===========================ĐỌC FILE=====================================================
//Hàm đọc dữ liệu 1 sinh viên từ File
void DocThongTin1SinhVien(ifstream& filein, SinhVien& sv) {/*Ta phải tạo ra hàm đọc thông tin data của 1 node(tức là 
	thông tin của sinh viên) trước rồi sau đó ta mới tạo 1 hàm có vòng lặp lặp từng data của node(tức là thông tin của
	sinh viên) để đọc từng data của node(Tức là thông sinh viên) từ file.*/
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
nên phải truyền vào 1 danh sách*/
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
		ThemVaoCuoi(l, p);
	}
}


//Ham hoán vị 2 cái data của 2 cái node cho nhau
void HoanVi(SinhVien& x, SinhVien& y) {

	/* Vì sinh viên là 1 thuộc tính mà thuộc tính bên trong sinh viên là 1 con trỏ nên ta không thể nào mà hoán vị 
	trực tiếp như thế này được, Tức là phải gán 2 cái struct trực tiếp cho nhau nếu như trong 2 sinh viên x và y không
	tồn tại con trỏ nếu tồn tại con trỏ thì k thể nào gán trực tiếp như thế này temp = x; đc*/
	SinhVien temp = x;
	x = y;
	y = temp;

}


//Hàm sắp xếp tăng dần theo điểm trung bình
void SapXepTangDan(List &l) {/*Sau khi sắp xếp tăng dần thì các sinh viên trong danh sách sẽ có sự thay đổi nên để
	lưu thay đổi đó ta cần có tham chiếu*/
	for (node* k = l.pHead; k != NULL; k = k->pNext) 
		for (node* h = k->pNext ; h != NULL; h = h->pNext) 
			if (k->data.dtb > h->data.dtb)
				HoanVi(k->data, h->data);//Hoán vị data của 2 cái node
}

//===========================GHI FILE=====================================================

//Hàm ghi thông tin 1 sinh viên vào file
/*Giống như đọc và ghi thông tin từ file của opp java.Bên c++ thì việc đọc thông tin như thế nào thì hàm ghi cấu trúc cũng
tương tự để dễ dàng cho quá trình ta thao tác(Tức ghi dữ liệu vào file sau khi ta thêm or xóa dữ liệu khi tắt mắt mở lại thì
dữ liệu của ta vẫn còn chứ k cần phải nhập dữ liệu lại giống y chang đọc và ghi dữ liệu vào file bên opp java đã học) với
file*/
void GhiThongTin1SinhVienVaoFile(ostream& fileout, SinhVien sv) {/*Ta phải tạo ra hàm ghi thông tin data của 1 node(tức là
	thông tin sinh viên) trước rồi sau đó ta mới tạo 1 hàm có vòng lặp lặp từng data của node(tức là thông tin của sinh viên)
	để ghi từng data của node(Tức là thông tin sinh viên) vào file.Nhắc lại cho nhớ node của ta bao gồm con trỏ và data mà 
	data của node có kiểu dữ liệu là sinh viên mà struct sinh viên ta là 1 thuộc tính bao gồm:  tên, mã sinh viên, ngày tháng
	năm sinh và điểm trung bình. Nên vì sao ta giải thích data của 1 node là thông tin của 1 sinh viên*/

	fileout << sv.hoTen << ", ";
	fileout << sv.maSV << ", ";
	fileout << sv.ngaySinh.Ngay << "/" << sv.ngaySinh.Thang << "/" << sv.ngaySinh.Nam << ", ";
	fileout << sv.dtb;
}

 //Sắp xếp danh sách tăng dần theo điểm trung bình sau đó lưu vào file SAPXEPDIEMMAX.txt
void LuuFileSapXepTangDanTheoDiemTrungBinh(List l) {/*Vì sắp xếp tăng dần xong thì chỉ lưu lại vào file SAPXEPDIEMMAX.txt, cái
	file thay đổi thì ta sẽ không cần lưu lại việc đó để làm gì. Vì mục đích của ta sắp xếp tăng dần xong thì chỉ lưu 
	lại vào file SAPXEPDIEMMAX.txt là xong chứ ko cần lưu lại việc sắp xếp đó để làm gì*/
	ofstream fileout;
	fileout.open("SAPXEPDIEMMAX.txt", ios::out);
	//Bước 1: Gọi lại hàm sắp xếp để sắp xếp danh sách sinh viên tăng dần theo điểm trung bình
	SapXepTangDan(l);
	//Bước 2: Dùng vòng lặp để lưu tất cả sinh viên vào file
	for (node* k = l.pHead; k != NULL; k = k->pNext) {
		GhiThongTin1SinhVienVaoFile(fileout, k->data);
		fileout << endl;

	}

	fileout.close();
}

//Hàm in danh sách sinh viên có điểm trunh bình max vào file
void GhiFileSvDiemTrungBinhMax(List l) {

	float DtbMax = l.pHead->data.dtb;//Giả sử sinh viên thứ nhất có điểm trung bình cao nhất
	//Bước 1 : Tìm ra điểm trunh bình cao nhất 
	for (node* k = l.pHead; k != NULL; k = k->pNext) {
		if (k->data.dtb > DtbMax)
		{
			DtbMax = k->data.dtb;
		}
	}
	
	//Bước 2: Tìm các sinh viên có điểm trung bình cao nhất ghi vào file
	ofstream fileout;
	fileout.open("DIEMTRUNGBINHMAX.txt", ios::out);
	for (node* k = l.pHead; k != NULL; k = k->pNext) {
		if (DtbMax == k->data.dtb)
		{
			GhiThongTin1SinhVienVaoFile(fileout, k->data);
			fileout << endl;
		}
	}
	fileout.close();
}

/* ============ HÀM CẮT CHUỖI =====================
* Hàm cắt chuỗi subtr ta đã học ở bên opp java rồi.
- subtr(<vị trí bắt đầu cắt chuỗi>): sẽ trả về 1 chuỗi con bắt đầu tại vị trí <vị trí bắt đầu cắt chuỗi> cho đến cuối
chuỗi
vd: string str = "Pham Tien Hien" ;
cout<< str.substr(6); tức là bắt đầu cắt từ vị trí số 6
result: Tien Hien

-  subtr(<vị trí bắt đầu cắt chuỗi>, <Số lượng ký tự cần lấy>): Sẽ trả về 1 chuỗi con bắt đầu từ <Vị trí bắt đầu cắt
chuỗi> cho đến <Số lượng ký tự cần lấy>
vd: string str = "Pham Tien Hien"
cout<< str.substr(0,3); tức là lấy 6 ký tự bắt đầu từ vị trí số 0
result: Pham
*/
//Hàm tách tên trong chuỗi họ tên
string TenSinhVien(string tenSv) {

	//Bước 1: duyệt họ tên sinh viên từ cuối về đầu chuỗi nếu gặp khoảng trắng thì dừng và lấy cái vị trí tiếp theo
	int lenght = tenSv.length();/*Đếm độ dài của chuỗi(Họ và Tên) lưu vào biến lenght ví dụ ta có chuỗi: 
	"Pham Tien Hien"
	 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 độ dài chuỗi là 14 => lenght = 14*/
	int i;
	for (i = lenght - 1; i >= 0; i--) {/*Duyệt từ cuối chuỗi về đầu chuỗi gặp khoảng trắng là dừng tức ta cắt chuỗi
		lấy tên vd: Chuỗi ở trên "Pham Tien Hien" thì vòng lặp sẽ duyệt từ cuối về đầu chuỗi tức là 14 13 12 11 là Hien
		đến đk if ptu thứ 10 là khoảng trắng thì dừng lại*/
		if (tenSv[i] == ' ') {
			break;
		}
	}
	//Bước 2: Cắt chuỗi tại vị trí i + 1 về đến cuối chuỗi
	return tenSv.substr(i + 1);
}

//Hàm xuất dữ liệu
void xuat(SinhVien sv) {

	cout << "\nHo Va Ten: " << sv.hoTen;
	cout << "\nMa sinh vien: " << sv.maSV;
	cout << "\nNgay thang nam sinh: " << sv.ngaySinh.Ngay << "/" << sv.ngaySinh.Thang << "/" << sv.ngaySinh.Nam;
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

//Hàm tìm kiếm dựa vào mã sinh viên
void TimKiemDuaVaoMaSinhVien(List l, string maSv){
	for (node* k = l.pHead; k != NULL; k = k->pNext) {
		if (k->data.maSV == maSv)
		{
			cout << "\n\nThong tin sinh vien can tim: ";
			xuat(k->data);
			cout << "\n\n";
		}

}
}

//Hàm tìm kiếm dựa vào tên sinh viên 
void TimKiemDuaVaoTen(List l, string tenSv) {
	for (node* k = l.pHead; k != NULL; k = k->pNext) {
		
		//Bước 1: Cắt tên trong chuỗi họ tên của sinh viên 
		string ten = TenSinhVien(k->data.hoTen);
		if (_stricmp((char*)ten.c_str(), (char*)tenSv.c_str()) == 0) {/*So sánh tên cần tìm và tên trong danh sách có
			giống nhau hay không mà không phân biệt hoa thường , Giống hàm equalsIgnoreCase bên java. Hàm c_str()
			là hàm chuyển chuỗi từ kiểu tring sang char*  và == 0 tức là 2 tên giống nhau*/
			
			cout << "\n\nThong tin can tim: ";
			xuat(k->data);
			cout << "\n\n";	
		}
	}

}

//Hàm giải phóng vùng nhớ cho danh sách liên kết đơn
void GiaiPhongVungNho(List& l) {

	node* p = NULL;
	while (p != NULL)
	{
		p = l.pHead;
		l.pHead->pNext = l.pHead;
		delete p;
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


	//LuuFileSapXepTangDanTheoDiemTrungBinh(l);
	GhiFileSvDiemTrungBinhMax(l);

	string msv;
	cout << "\n\nNhap ma sinh vien can tim: ";
	getline(cin, msv);
	TimKiemDuaVaoMaSinhVien(l, msv);

		
	string ten;
	cout << "\n\nNhap ten can tim: ";
	getline(cin, ten);

	

	TimKiemDuaVaoTen(l, ten);

	GiaiPhongVungNho(l);
	filein.close();
	system("Pause");


}

