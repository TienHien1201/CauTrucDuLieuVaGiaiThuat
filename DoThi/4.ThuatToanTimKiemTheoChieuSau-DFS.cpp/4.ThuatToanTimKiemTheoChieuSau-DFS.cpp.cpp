//============ ĐỒ THỊ VÔ HƯỚNG =====================
/*Khi mà thuật toán DFS - Thuật toán tìm kiếm tìm kiếm theo chiều sâu chạy thì nó sẽ tạo thành 1 cái cây gọi là cái cây tìm kiếm DFS.
Thì ta đã học qua cây nhị phân cách xuất các phần tử trong cây cũng duyệt cây tương tự như thuật toán tím kiếm theo chiều sâu của đồ
thị thay vì đồ thị là nó sẽ mở rộng duyệt các đỉnh kề thì cây nhị phân nó sẽ duyệt hai nhánh con là trái phải và node cho đến khi đi
xuống tận cùng vì là đệ quy nên khi trạng thái 1 hàm đệ quy đã xong thì nó sẽ backtrack(quay lui về trạng thái kế đó cho đến khi hết
các trạng thái của hàm thì lúc đó hàm đã thực hiện xong nhiệm vụ) lên cho đến khi không còn phần từ nào nữa thì dừng.*/
#if 0
#include <iostream>
#include<vector>
using namespace std;


/*intput: là danh sách cạnh gồm | khi duyệt danh sách kề               | Output : là từ input nhập vào danh sách cạnh sau đó duyệt các
9 đỉnh(n) và 9 cạnh(m) là:      | thì đây là danh sách các             | đỉnh theo dạng danh sách kề và cuối cùng kết quả là xuất ra thứ
                                | đỉnh kề với nhau:                    | tự các đỉnh đã được thăm và xuất ra màn hình với thuật toán DFS
               1 2              | 1: 2 3 5 => đỉnh 1 kề                | tìm kiếm theo chiều sau của đồ thị với bắt đầu từ đỉnh 1 :
               1 3              | với đỉnh 2 tức là 1 nối              | DFS(1) = 1 2 4 3 6 7 9 8 5
               1 5              | với 2 thành cạnh của đồ thị          |
               2 4              | và tương tự 1 với 3 , 1 với 5....    |
               3 6              | danh sách kề của các đỉnh bên dưới   |
               3 7              | tương tự.....                        |
               5 8              |  2: 1 4                              |
               6 7              |  3: 1 6 7 9                          |
               8 9              |  5: 1 8                              |
                                |  6: 1 7                              |
                                |  8: 5 9                              |
                                |                                      |
                                |                                      |
                                |                                      |
                                |                                      |                      */


int n, m;
vector<int> adj[50];//Vector dùng để lưu danh sách kề
bool visited[20];/*Kiểm tra một cái đỉnh nào đó đã được thăm hay chưa. Nếu không có hàm visited này thì gọi hàm trong hàm(đệ quy
hàm DFS sẽ lặp vĩnh viễn)*/  

void inp() {//Hàm input để nhập vào danh sách cạnh
    cout << "Nhap vao n dinh va m canh cua do thi:\n ";
    cin >> n >> m;
    
    cout << "Nhap vao dinh x va dinh y de tao thanh canh cua do thi: \n";
    for (short i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;

        /*Chuyển danh sách cạnh(danh sách cạnh là input của đề bài) sang danh sách kề(ví dụ  danh sách kề của đỉnh 1 theo intput của
        đề bài là 1: 2 3 5)*/
        adj[x].push_back(y);
        adj[y].push_back(x);
        /*Vì là đồ thị vô hướng nên danh sách kề của cạnh nó theo 2 hướng ví dụ hai đỉnh 1 và 2 tạo thành cạnh kề của đồ thị là cạnh
        1 2 và ngược hướng lại thì đỉnh 2 nối với đỉnh 1 cũng là cạnh 2 1 nên x nối với y là cạnh thì y nối với x cũng là 1 cạnh của
        đồ thị vô hướng*/

        memset(visited, false, sizeof(visited));/*Memset được sử dụng để đặt tất cả các phần tử trong mảng vissited thành false. Điều
        này thường được sử dụng để khởi tạo hoặc đặt lại các mảng bool thành giá trị mặc định tức là ở đây ta đặt giá trị mặc định là false
        cho tất cả các phần tử trong mảng bool visited.*/
    }
}


/*GIẢI THÍCH ngắn gọn cơ chế của hàm DFS tức là thuật toán tìm kiếm theo chiều sâu như sau: khi chạy chương trình ta truyền vào cho hàm
DFS giá trị u là 1 tức là duyệt bắt đầu từ đỉnh 1, vì trong hàm ta có thêm dòng xuất giá trị u nào mà đã đc thăm(tức là mang giá trị true)
nên số 1 lần đầu đc duyệt sẽ đc bật lên là true vì đã đc thăm và cứ thế nó duyệt xuống sâu nhất của đồ thị bằng cách duyệt lần lượt các
đỉnh kề với đỉnh đã đc thăm khi đỉnh đã đc thăm mà không đỉnh nào kề với nó mà không đc thăm(tức là không còn đỉnh nào kề với đỉnh true
mà mang giá trị là false nữa) thì đệ quy sẽ backtrack(quay lui) từ dưới đáy của đồ thị quay lên nếu gặp đỉnh nào chưa đc thăm(tức là false)
thì gọi hàm trong hàm tức là đệ quy để thăm hết các đỉnh của đồ thị và đỉnh nào đc thăm trước thì sẽ xuất ra trước. CHI TIẾT TỪNG BƯỚC CHẠY
CỦA THUẬT TOÁN TÌM KIẾM THEO CHIỀU SAU CỦA ĐỒ THỊ NẰM Ở TRONG VỞ CẤU TRÚC DỮ LIỆU & GIẢI THUẬT - ĐỒ THỊ 1 - BÀI 8.*/
void DFS(int u){
    cout << u << " ";

    //Đánh dấu là u đã đc thăm
    visited[u] = true;

    //Duyệt các đỉnh kề với đỉnh đã đc thăm xem các đỉnh kề với các đỉnh kề với các đỉnh đc thăm đã đc thăm hay chưa
    for (int v : adj[u])
    {
        //Nếu đỉnh v(đỉnh v là các đỉnh kề với đỉnh đã đc thăm) chưa được thăm
        if (!visited[v])
        {
            /*Gọi hàm DFS trong hàm DFS tức là đệ quy, mõi lần đệ quy ta tryền v(đỉnh v là các đỉnh kề với đỉnh đã đc thăm) vào hàm để
            all các đỉnh có thể đc thăm(đc thăm tức là mang giá trị true).*/
            DFS(v);
        }
    }

}

int main()
{
    inp();
    cout << "Cac dinh sau khi duoc tham(true): \n";
    DFS(1);/*bắt đầu duyệt từ đỉnh 1, theo thứ tự chạy tay thì các đỉnh lần lượt đc bật lên là true(true tức là visited là đã đc thăm)
    theo như input đề bài ta nhập vào là 1 2 4 3 6 7 9 8 5*/
}
#endif


//================= ĐỒ THỊ CÓ HƯỚNG ================================
#if 1
#include <iostream>
#include<vector>
using namespace std;

/*intput: là danh sách cạnh gồm | khi duyệt danh sách kề               | Output : là từ input nhập vào danh sách cạnh sau đó duyệt các
9 đỉnh(n) và 10 cạnh(m) là:     | thì đây là danh sách các             | đỉnh theo dạng danh sách kề và cuối cùng kết quả là xuất ra thứ  
                                | đỉnh kề với nhau:                    | tự các đỉnh đã được thăm và xuất ra màn hình với thuật toán DFS
               1 2              | 1: 2 3 5 => đỉnh 1 kề                | tìm kiếm theo chiều sau của đồ thị với bắt đầu từ đỉnh 1 : 
               1 3              | với đỉnh 2 tức là 1 nối              | DFS(1) = 1 2 4 3 6 7 5 8 9
               1 5              | với 2 thành cạnh của đồ thị          |
               2 4              | và tương tự 1 với 3 , 1 với 5....    |
               3 6              | danh sách kề của các đỉnh bên dưới   |
               3 7              | tương tự.....                        |
               5 8              |  2: 4                                |
               6 7              |  3: 6 7 9                            |
               8 9              |  5: 8                                |
               9 3              |  6: 7                                |
                                |  8: 9                                |
                                |  9: 3                                |
                                |                                      |
                                |                                      |
                                |                                      |                      */
int n, m;
vector<int> adj[50];//Vector dùng để lưu danh sách kề
bool visited[20];/*Kiểm tra một cái đỉnh nào đó đã được thăm hay chưa. Nếu không có hàm visited này thì gọi hàm trong hàm(đệ quy
hàm DFS sẽ lặp vĩnh viễn)*/

void inp() {//Hàm input để nhập vào danh sách cạnh
    cout << "Nhap vao n dinh va m canh cua do thi:\n ";
    cin >> n >> m;

    cout << "Nhap vao dinh x va dinh y de tao thanh canh cua do thi: \n";
    for (short i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;

        /*Chuyển danh sách cạnh(danh sách cạnh là input của đề bài) sang danh sách kề(ví dụ  danh sách kề của đỉnh 1 theo intput của
        đề bài là 1: 2 3 5*/
        adj[x].push_back(y);/*Đối với đồ thị có hướng thì hai đỉnh tạo thành cạnh của đồ thị thì chỉ đc hình thành từ đỉnh đầu nối tới
        đỉnh cuối và không có hướng ngược lại như đồ thị vô hướng. Nên ta chỉ cần pushback y và danh sách kề của đỉnh x là được.*/

        memset(visited, false, sizeof(visited));/*Memset được sử dụng để đặt tất cả các phần tử trong mảng vissited thành false. Điều
        này thường được sử dụng để khởi tạo hoặc đặt lại các mảng bool thành giá trị mặc định tức là ở đây ta đặt giá trị mặc định là false
        cho tất cả các phần tử trong mảng bool visited.*/
    }
}


/*GIẢI THÍCH ngắn gọn cơ chế của hàm DFS tức là thuật toán tìm kiếm theo chiều sâu như sau: khi chạy chương trình ta truyền vào cho hàm
DFS giá trị u là 1 tức là duyệt bắt đầu từ đỉnh 1, vì trong hàm ta có thêm dòng xuất giá trị u nào mà đã đc thăm(tức là mang giá trị true)
nên số 1 lần đầu đc duyệt sẽ đc bật lên là true vì đã đc thăm và cứ thế nó duyệt xuống sâu nhất của đồ thị bằng cách duyệt lần lượt các
đỉnh kề với đỉnh đã đc thăm khi đỉnh đã đc thăm mà không đỉnh nào kề với nó mà không đc thăm(tức là không còn đỉnh nào kề với đỉnh true
mà mang giá trị là false nữa) thì đệ quy sẽ backtrack(quay lui) từ dưới đáy của đồ thị quay lên nếu gặp đỉnh nào chưa đc thăm(tức là false)
thì gọi hàm trong hàm tức là đệ quy để thăm hết các đỉnh của đồ thị và đỉnh nào đc thăm trước thì sẽ xuất ra trước. CHI TIẾT TỪNG BƯỚC CHẠY
CỦA THUẬT TOÁN TÌM KIẾM THEO CHIỀU SAU CỦA ĐỒ THỊ NẰM Ở TRONG VỞ CẤU TRÚC DỮ LIỆU & GIẢI THUẬT - ĐỒ THỊ 1 - BÀI 8.*/
void DFS(int u) {
    cout << u << " ";

    //Đánh dấu là u đã đc thăm
    visited[u] = true;

    /*Duyệt các đỉnh kề với đỉnh đã đc thăm xem các đỉnh kề với các đỉnh kề với các đỉnh đc thăm đã đc thăm hay chưa*/
    for (int v : adj[u])
    {
        //Nếu đỉnh v(đỉnh v là các đỉnh kề với đỉnh đã đc thăm) chưa được thăm
        if (!visited[v])
        {
            /*Gọi hàm DFS trong hàm DFS tức là đệ quy, mõi lần đệ quy ta tryền v(đỉnh v là các đỉnh kề với đỉnh đã đc thăm) vào hàm để
            all các đỉnh có thể đc thăm(đc thăm tức là mang giá trị true).*/
            DFS(v);
        }
    }
}

int main() {

    inp();
    cout << "Cac dinh sau khi duoc tham(true): \n";
    DFS(1);/*bắt đầu duyệt từ đỉnh 1, theo thứ tự chạy tay thì các đỉnh lần lượt đc bật lên là true(true tức là visited là đã đc thăm)
    theo như input đề bài ta nhập vào là 1 2 4 3 6 7 5 8 9. Ta có thể chạy chương trình với bất cứ đỉnh nào thì ta truyền đỉnh đó vào
    trong hàm DFS này chứ k nhất thiết là phải bắt đầu từ đỉnh 1*/
}

#endif // 1

