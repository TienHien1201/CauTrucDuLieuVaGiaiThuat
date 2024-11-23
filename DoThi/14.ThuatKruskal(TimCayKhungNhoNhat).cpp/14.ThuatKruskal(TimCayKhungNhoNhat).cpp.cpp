#include <iostream>
#include<vector>
#include<algorithm>
using namespace std;

/*========================== THUẬT KRUSKAL - TÌM CÂY KHUNG NHỎ NHẤT ==================================
Phần cơ chế và các bước của Kruskal đã giải thích rất rõ trong vở đồ thị 4 bài 17 nếu quên vào mở lại xem.

Bài toán tìm cây khung nhỏ nhất 
input: n là số đỉnh = 6 từ 1 đến 6 | output : với input thì khung cực tiều MST là  
và m là số cạnh = 9 gồm 9 cạnh và  | 2 3 : 1   
trọng số của mõi cạnh              | 3 5 : 2
      1 2 : 12                     | 4 5 : 3
      1 3 : 4                      | 1 3 : 4
      2 3 : 1                      | 5 6 : 8
      2 4 : 5                      |  và tổng trọng số của khung cực tiểu MST là d = 18
      2 5 : 3                      |
      3 5 : 2                      |
      4 5 : 3                      |
      4 6 : 10                     |
      5 6 : 8                      | 
*/



const int maxn = 20;/*sử dụng để định rõ một giá trị cố định trong chương trình, giúp dễ dàng quản lý và thay đổi giá trị đó mà không
cần phải tìm và sửa tất cả các vị trí sử dụng giá trị đó trong code*/
int n, m;//n là số đỉnh, m là số cạnh
int parent[maxn], sz[maxn];/*Mảng parent dùng để lưu đại diện của cây khung ban đầu khi vừa tạo. vì ban đầu là tạo 1 khung cây rỗng
mà ta áp dụng thuật DSU - Disjoin Set Union(cấu trúc dữ liệu các tập hợp rời nhau) nên mõi đỉnh phải có đại diện là chính nó tương
đương với mõi đỉnh trong khung cây rỗng ban đầu là 1 tập hợp, mảng size dùng để lưu kích thước của 1 tập hợp để khi gộp 2 tập hợp lại
thì hàm uion sẽ tối ưu bằng cách cho đại diện của tập có kích thước nhỏ hơn thành đại diện có kích thước lớn hơn.*/
vector<egde> canh;//Danh sách cạnh tức vector kiểu egde mà egde là 1 cấu trúc của 1 cạnh mà ta đã tạo 

//Khai báo cấu trúc của 1 cạnh trong đồ thị
struct egde
{
    int u, v;//u là đỉnh đầu của cạnh, v là đỉnh cuối của cạnh
    int w;//w là trọng số của cạnh

};


/*Áp dụng thuật DSU - Disjoin Set Union(Cấu trúc dữ liệu các tập rời nhau) vào Bước 3 của Thuật kruskal.(Và thuật DSU đã giải thích cơ
chế rất rỏ trong vở đồ thị 4 bài 16 nếu quên hãy mở lại xem.)*/
void Make_Set() {/*Mõi đỉnh ban đầu trong khung cây là mõi tập rời nhau nên cập nhật cho các đỉnh trong khung cây ban đầu có đại diện
    là chính nó tương đương với mõi đỉnh là 1 tập hợp  */
    for (short i = 1; i <= n; i++)
    {
        parent[i] = i;
        sz[i] = 1;
    }
}

int Find(int v) {//Tìm đại diện của 1 đỉnh bất kì
    if (v == parent[v])
    {
        return v;
    }
    return parent[v] = Find(parent[v]);
}

bool Union(int a, int b) {//Thực hiện việc gộp 2 đỉnh bất kì
    a = Find(a);//Tìm đại diện của đỉnh a
    b = Find(b);//Tìm đại diện của đỉnh b
    if (a == b)//Nếu đại diện của a mà bằng b tức a và b nằm trong 1 tập hợp nên k cần gộp và return false
        return false;

    /*Xuống đây là a với b khác đại diện hay nói cách khác là a và b nằm 2 tập hợp khác nhau nên có thể gộp
    a và b lại */
    if (sz[a] < sz[b]) {/*Tối ưu gộp bằng cách cho đại diện của tập có kích thước nhỏ hơn thành đại diện của
        tập có kích thước nhỏ hơn*/

        swap(a, b);
        parent[b] = a;
        sz[a] += sz[b];
        return true;
    }
}

//Nhập dữ liệu
void inp() {
    cout << "Nhap vao n dinh va m canh cua do thi vo huong: \n";
    cin >> n >> m;

    cout << "Nhap vao hai dinh x va y va trong so cua canh x y: \n";
    for (short i = 0; i < m; i++)
    {
        int x, y, w;//x và y là 2 đỉnh tạo thành cạnh của đồ thị còn w là trọng số của cạnh x y
        cin >> x >> y >> w;
        egde e; //e là 1 cạnh với trọng số của cạnh của mõi lần nhập
        /*Mõi lần nhập 1 cạnh thì ta lưu cạnh và trọng số của cạnh đó vào struct egde có tên là e tức mõi 1 là 1 cạnh mà mõi cạnh đều
        có trọng số. Ta đã học cấu trúc dữ liệu danh sách liên kết rồi nên quá quen với struct struct là một kiểu dữ liệu tự định nghĩa
        được sử dụng để tổ chức và lưu trữ một nhóm các biến (thành viên) có liên quan lại với nhau tạo thành 1 thành viên ví dụ như ta
        đã tạo ra 1 struct có tên là edge(cạnh) tức mõi struct egde là 1 cạnh của đồ thị mà 1 cạnh của đồ thị bao gồm đỉnh đầu và đỉnh
        cuối nối lại mới ra cạnh và trọng số của cạnh*/
        e.u = x;//Đỉnh đầu của cạnh
        e.v = y;//Đỉnh cuối của cạnh
        e.w = w;//Trọng số của cạnh
        canh.push_back(e);//Thêm e vào danh sách cạnh
    }

}

//Thuật Kruskal
//Sắp xếp các cạnh có độ dài tăng dần trong danh sách cạnh
bool Sort(egde a, egde b) {
    return a.w < b.w;
}

void Kruskal() {
    //Bước 1: Tạo khung cây rỗng để từ khung cây rỗng này tìm ra khung cây cực tiểu
    vector<egde> MST;//Khung cây rỗng
    int d = 0;//d là tổng trọng số của khung cây vì rỗng nên có trọng số = 0

    //Bước 2: Sắp xếp danh sách cạnh có chiều dài tăng dần
    sort(canh.begin(), canh.end(), Sort);

    //Bước 3: Lặp
    for (short i = 0; i < m; i++)
    {
        if (MST.size() == n - 1) {/*Vì vòng for xét cạnh chạy từ 0 đến m tức có 6 cạnh thì chạy từ 0 đến 5 là đủ 6 cạnh nên khung cây
            rỗng chỉ cần xét đủ n - 1 cạnh tức xét đủ cạnh thì dừng */
            break;
        }

        //Lấy cạnh có độ dài nhỏ nhất ra khỏi danh sách canh để duyệt
        egde e = canh[i];/*Chọn cạnh e là cạnh nhỏ nhất vì ta đã sắp xếp cách cạnh có độ dài từ bé nhất tới lớn nhất tức phần tử trong
        danh sách canh là edge e đc sắp xếp độ dài từ bé đến lớn mà vòng lặp chạy từ 0 đến m tức từ phần tử cạnh đầu tiên cho đến
        phần tử cạnh cuối cùng trong danh sách canh vì các cạnh trong danh sách canh đã đc sắp xếp theo độ dài từ bé đến lớn nên phần
        tử thứ 0 là phần từ có độ dài bé nhất và lần lượt đến m là cạnh có độ dài lớn nhất  */

        if (Union(e.u, e.v)) {/*Nếu 2 đỉnh trong đồ thị mà có thể gộp lại đc đồng nghĩa có thể thêm cạnh (e.u;e.v) vào khung cây rỗng mà
        không tạo thành chu trình, như ta biết u là đỉnh đầu của cạnh còn v là đỉnh cuối của cạnh e là biến kiểu edge mà egde là 1 cạnh
        của đồ thị tức biến e thuộc kiểu egde dùng để truy cập vào egde.*/
            MST.push_back(e);//Thêm cạnh e vào khung cây rỗng
            d += e.w;//Cộng chiều dài của cạnh e vào khung cây rỗng

        }
    }
    //Trả về kết quả 
    if (MST.size() != n - 1)
    {
        cout << "Do thi khong lien thong !\n";
    }
    else
    {
        cout << "MST: " << d << "\n";
        for (auto it : MST) {
            cout << it.u << " " << it.v << " " << it.w << "\n";
        }
    }
}

int main()
{
    inp();
    Make_Set();
    Kruskal();
}





