//======================= ĐỒ THỊ VÔ HƯỚNG ========================
#if 0
#include <iostream>
#include<vector>
#include<queue>
using namespace std;

/*Intput: là danh sách cạnh gồm | khi duyệt danh sách kề               | Output : là từ input nhập vào danh sách cạnh sau đó duyệt các
10 đỉnh(n) là từ 1 đến 10 và 11 | thì đây là danh sách các             | đỉnh theo dạng danh sách kề và cuối cùng kết quả là xuất ra thứ
cạnh(m) là:                     | đỉnh kề với nhau:                    | tự các đỉnh đã được thăm và xuất ra màn hình với thuật toán BFS
               1 2              | 1: 2 3 5 10 => đỉnh 1 kề             | tìm kiếm theo chiều rộng của đồ thị với bắt đầu từ đỉnh 1 :
               1 3              | với đỉnh 2 tức là 1 nối              | BFS(1) = 1 2 3 5 10 4 6 7 9 8
               1 5              | với 2 thành cạnh của đồ thị          |
               1 10             | và tương tự 1 với 3 , 1 với 5....    |
               2 4              | danh sách kề của các đỉnh bên dưới   |
               3 6              | tương tự.....                        |
               3 7              |  2: 1 4                              |
               3 9              |  3: 1 6 7 9                          |
               5 8              |  5: 1 8                              |
               6 7              |  6: 1 7                              |
               8 9              |  8: 5 9                              |
                                |                                      |
                                |                                      |
                                |                                      |
                                |                                      |                      */

int n, m;//n là số đỉnh của đồ thị còn m là số cạnh của đồ thị
vector <int> adj[20];//Vector danh sách kề
bool visited[20];

void inp() {
    cout << "Nhap vao n(dinh) va m(canh) cua do thi \n ";
    cin >> n >> m;

    cout << "Nhap vao dinh x va y tao thanh canh cua do thi: \n";
    for (short i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;//Nhập danh sách cạnh

        /*Lưu danh sách cạnh(danh sách cạnh là input của đề bài) về danh sách kề(ví dụ  danh sách kề của đỉnh 1 theo Intput của
        đề bài là 1: 2 3 5 10)*/
        adj[x].push_back(y); /*Vì là đồ thị vô hướng nên danh sách kề của cạnh nó theo 2 hướng ví dụ hai đỉnh 1 và 2 tạo thành cạnh kề
        của đồ thị là cạnh 1 2 và ngược hướng lại thì đỉnh 2 nối với đỉnh 1 cũng là cạnh 2 1 nên x nối với y là cạnh thì y nối với x
        cũng là 1 cạnh của đồ thị vô hướng*/
        adj[y].push_back(x);


        //Cài măc định tất cả các đỉnh trong mảng visited là false
        memset(visited, false, sizeof(visited));
    }
}

/*GIẢI THÍCH NGẮN GỌN CƠ CHẾ CỦA THUẬT TOÁN TÌM KIẾM THEO CHIỀU RỘNG CỦA ĐỒ THỊ: đối với chương trình này giá trị truyền vào hàm BFS
là 1 thì ta bắt đầu duyệt từ đỉnh 1 trong lần đầu tiên này đỉnh 1 sẽ đc thêm vào cuối danh sách hàng đợi và đánh dấu là đỉnh 1 là 4
true(tức là 1 đã đc thăm) sau đó tiếp theo chương trình sẽ chạy đến vòng lặp while và xét xem hàng đợi có tồn tại các đỉnh ở trong danh
sách hay không nếu có thì nó sẽ lấy đỉnh ở đầu danh sách ra khỏi hàng đợi và xuất đỉnh ở đầu danh sách này ra luôn tức là xuất đỉnh ở
đầu hàng đợi là đỉnh đã dc thăm xong, sau khi xuất đỉnh ở đầu danh sách ra rồi thì nó sẽ xuống vòng lặp for để duyệt danh sách kề của 
đỉnh ở đầu danh sách hàng đợi vừa đc đẩy ra khỏi hàng đợi và xuất ra xem có đỉnh nào kề với đỉnh ở đầu danh sách hàng đợi vừa đc xuất
ra và đẩy ra khỏi hàng đợi mà chưa đc thăm hay không cụ thể ở đây là nó duyệt danh sách kề của đỉnh 1 kiểm tra lần lượt xem có đỉnh nào
kề với đỉnh 1 mà chưa đc thăm(tức là dang false)  hay không nếu duyệt lần lượt tới các đỉnh kề với đỉnh 1 mà có đỉnh chưa đc thăm(đang
false) thì nó sẽ đưa đỉnh chưa đc thăm vào hàng đợi và đánh dấu là true(nghĩa là đã đc thăm) cứ như vậy cho đến khi không còn đỉnh nào
kề với đỉnh 1 mà chưa đc thăm nữa thì nó sẽ thoát khỏi vòng lặp for và ra vòng lặp while, ở vòng lặp while nó lại tiếp tục kiểm tra hàng
đợi có đỉnh nào không tức có tồn tại phần tử nào trong hàng đợi hay là không, nếu có tồn tại đỉnh trong hàng đợi thì chương trình sẽ
lấy đỉnh ở đầu danh sách ra khỏi hàng đợi và xuất đỉnh ở đầu hàng đợi(queue) ra(danh sách queue ta tạo dùng để chứa các đỉnh đã đc thăm
ở trong đồ thị mà cơ chế của queue ta đã học ở bài danh sách liên kết đơn là FIFO - Firt In Firt Out là vào trước ra trước tức là thêm 
thì thêm ở cuối danh sách còn lấy ra thì lấy ở đầu danh sách giống như xếp hàng vậy vào trước đc mua trước và ra trước nên khi lấy đỉnh
ở đầu danh sách của hàng đợi ra thì nó đúng theo thứ tự mà các đỉnh đã đc thăm tức đỉnh nào đc thăm trước thì xuất ra trước) và sau khi
xuất đỉnh ở đầu danh sách hàng đợi ra thì nó lại tiếp tục duyệt danh sách kề của đỉnh vừa đc đẩy ra khỏi danh sách hàng đợi và xuất ra 
xem lần lượt các đỉnh có đỉnh nào kề với nó mà chưa đc thăm hay không nếu chưa(chưa đc thăm là false) thì nó sẽ đẩy đỉnh đó vào danh sách 
hàng đợi và đánh dấu là đã đc thăm(đã đc thăm thì nó sẽ đánh dấu là true) cho đến khi không còn đỉnh nào mà chưa đc thăm nữa thì nó sẽ
dừng vòng lặp for lại và ra vòng lặp while để lấy đỉnh ở đầu danh sách hàng chờ ra khỏi hàng chờ và xuất ra rồi lại tiếp tự duyệt danh
sách kề của đỉnh vừa xuất ra chứ như vậy cho đến khi các đỉnh trong đồ thị đc thăm hết và xuất ra lần lượt cho đến khi danh sách hàng 
đợi không còn đỉnh nào nữa thì hàm BFS(thuật toán tiềm kiếm theo chiều rộng của đồ thị) cũng đã hoàn thành. Đã giải thích từng bước chạy
của thuật toán BFS(Tìm kiếm theo chiều rộng của đồ thị) ở trong vở cấu trúc dữ liệu và giải thuật đồ thị 1 bài 9 nếu quên hãy mở vở ra
để xem.
*/
void BFS(int u) {
    //Khởi tạo queue để chứa các đỉnh đã đc thăm ở trong đồ thị
    queue<int> q;
    q.push(u);/*Thêm phần tử theo cơ chế của queue là FIFO - Firt In Firt Out nghĩa là vào trước ra trước tức là thêm(Push) ở cuối danh 
    sách còn lấy(Pop) thì lấy ở đầu danh sách*/
    visited[u] = true;

    //Duyệt danh sách danh sách hàng đợi xem có đỉnh nào trong hàng đợi hay không
    while ( !q.empty())
    {
        int v = q.front();//Lấy đỉnh ở đầu đợi ra. Tức là tạo ra biên v để lưu giá trị của đỉnh đầu hàng đợi 
        q.pop();/*Lấy phần tử theo cơ chế của queue là FIFO - Firt In Firt Out nghĩa là vào trước ra trước tức là thêm(Push) ở cuối danh 
        sách còn lấy(Pop) thì lấy ở đầu danh sách*/
        cout << v << " ";//Xuất đỉnh ở đầu hàng đợi ra 

        for (int x : adj[v])
        {
            if (!visited[x])
            {
                q.push(x);
                visited[x] = true;
            }
        }
    }

}   

int main()
{
    inp();
    cout << "Thu tu cac dinh sau khi dc tham voi BFS thuat toan tim kiem theo chieu rong: \n";
    BFS(1);
}
#endif

//====================== ĐỒ THỊ CÓ HƯỚNG ===============================
/*Đối với thuật toán theo chiều rộng của đồ thị có hướng chỉ khác với thuật toán theo chiều rộng của đồ thị vô hướng là cái input nhập
vào và danh sách cạnh của đồ thị vì đồ thị có hướng thì nếu x nối với y theo chiều từ x tới y tạo thành cạnh của đồ thị thì khi lưu danh 
sách cạnh thành danh sách kề chỉ cần cho đỉnh
y vào danh sách kề của x thôi ko cần phải cho x vào danh sách kề của y vì có hướng là 2 đỉnh tạo thành 1 cạnh của đồ thị chỉ 1 hướng 
duy nhất và không có ngược lại còn lại tư duy thuật toán giống nhau*/
#if 1
#include<iostream>
#include<vector>
#include<queue>
using namespace std;

/*Intput: là danh sách cạnh gồm | khi duyệt danh sách kề               | Output : là từ input nhập vào danh sách cạnh sau đó duyệt các
10 đỉnh(n) là từ 1 đến 10 và 12 | thì đây là danh sách các             | đỉnh theo dạng danh sách kề và cuối cùng kết quả là xuất ra thứ
cạnh(m) là:                     | đỉnh kề với nhau:                    | tự các đỉnh đã được thăm và xuất ra màn hình với thuật toán BFS
               1 2              | 1: 2 3 5 10 => đỉnh 1 kề             | tìm kiếm theo chiều rộng của đồ thị với bắt đầu từ đỉnh 1 :
               1 3              | với đỉnh 2 tức là 1 nối              | BFS(1) = 1 2 3 5 10 4 6 8 7 9
               1 5              | với 2 thành cạnh của đồ thị          |
               1 10             | và tương tự 1 với 3 , 1 với 5....    |
               2 4              | danh sách kề của các đỉnh bên dưới   |
               3 5              | tương tự.....                        |
               3 6              |  2: 4                                |
               5 8              |  3: 5 6                              |
               5 10             |  5: 8 10                             |
               6 7              |  6: 7                                |
               7 3              |  7: 3                                |
               8 9              |  8: 9                                |
                                |                                      |
                                |                                      |
                                |                                      |                      */

int n, m;//n là số đỉnh của đồ thị còn m là số cạnh của đồ thị
vector <int> adj[20];//Vector danh sách kề
bool visited[20];

void inp() {
    cout << "Nhap vao n(dinh) va m(canh) cua do thi \n ";
    cin >> n >> m;

    cout << "Nhap vao dinh x va y tao thanh canh cua do thi: \n";
    for (short i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;//Nhập danh sách cạnh

        /*Lưu danh sách cạnh(danh sách cạnh là input của đề bài) về danh sách kề(ví dụ  danh sách kề của đỉnh 1 theo Intput của
        đề bài là 1: 2 3 5 10)*/
        adj[x].push_back(y); /*Vì là đồ thị có hướng nên danh sách kề của cạnh nó theo 1 hướng ví dụ hai đỉnh 1 và 2 tạo thành cạnh kề
        của đồ thị là cạnh 1 2 và không có ngược hướng lại là đỉnh 2 nối với đỉnh 1 là cạnh 2 1 đc nên x nối với y là cạnh của đồ thị
        có hướng thôi vì vậy ta chỉ push y và danh sách kề của x chứ k có push x vào danh sách kề của y như đồ thị vô hướng được.*/
        
        //Cài măc định tất cả các đỉnh trong mảng visited là false
        memset(visited, false, sizeof(visited));
    }
}

/*GIẢI THÍCH NGẮN GỌN CƠ CHẾ CỦA THUẬT TOÁN TÌM KIẾM THEO CHIỀU RỘNG CỦA ĐỒ THỊ: đối với chương trình này giá trị truyền vào hàm BFS
là 1 thì ta bắt đầu duyệt từ đỉnh 1 trong lần đầu tiên này đỉnh 1 sẽ đc thêm vào cuối danh sách hàng đợi và đánh dấu là đỉnh 1 là 4
true(tức là 1 đã đc thăm) sau đó tiếp theo chương trình sẽ chạy đến vòng lặp while và xét xem hàng đợi có tồn tại các đỉnh ở trong danh
sách hay không nếu có thì nó sẽ lấy đỉnh ở đầu danh sách ra khỏi hàng đợi và xuất đỉnh ở đầu danh sách này ra luôn tức là xuất đỉnh ở
đầu hàng đợi là đỉnh đã dc thăm xong, sau khi xuất đỉnh ở đầu danh sách ra rồi thì nó sẽ xuống vòng lặp for để duyệt danh sách kề của
đỉnh ở đầu danh sách hàng đợi vừa đc đẩy ra khỏi hàng đợi và xuất ra xem có đỉnh nào kề với đỉnh ở đầu danh sách hàng đợi vừa đc xuất
ra và đẩy ra khỏi hàng đợi mà chưa đc thăm hay không cụ thể ở đây là nó duyệt danh sách kề của đỉnh 1 kiểm tra lần lượt xem có đỉnh nào
kề với đỉnh 1 mà chưa đc thăm(tức là dang false)  hay không nếu duyệt lần lượt tới các đỉnh kề với đỉnh 1 mà có đỉnh chưa đc thăm(đang
false) thì nó sẽ đưa đỉnh chưa đc thăm vào hàng đợi và đánh dấu là true(nghĩa là đã đc thăm) cứ như vậy cho đến khi không còn đỉnh nào
kề với đỉnh 1 mà chưa đc thăm nữa thì nó sẽ thoát khỏi vòng lặp for và ra vòng lặp while, ở vòng lặp while nó lại tiếp tục kiểm tra hàng
đợi có đỉnh nào không tức có tồn tại phần tử nào trong hàng đợi hay là không, nếu có tồn tại đỉnh trong hàng đợi thì chương trình sẽ
lấy đỉnh ở đầu danh sách ra khỏi hàng đợi và xuất đỉnh ở đầu hàng đợi(queue) ra(danh sách queue ta tạo dùng để chứa các đỉnh đã đc thăm
ở trong đồ thị mà cơ chế của queue ta đã học ở bài danh sách liên kết đơn là FIFO - Firt In Firt Out là vào trước ra trước tức là thêm
thì thêm ở cuối danh sách còn lấy ra thì lấy ở đầu danh sách giống như xếp hàng vậy vào trước đc mua trước và ra trước nên khi lấy đỉnh
ở đầu danh sách của hàng đợi ra thì nó đúng theo thứ tự mà các đỉnh đã đc thăm tức đỉnh nào đc thăm trước thì xuất ra trước) và sau khi
xuất đỉnh ở đầu danh sách hàng đợi ra thì nó lại tiếp tục duyệt danh sách kề của đỉnh vừa đc đẩy ra khỏi danh sách hàng đợi và xuất ra
xem lần lượt các đỉnh có đỉnh nào kề với nó mà chưa đc thăm hay không nếu chưa(chưa đc thăm là false) thì nó sẽ đẩy đỉnh đó vào danh sách
hàng đợi và đánh dấu là đã đc thăm(đã đc thăm thì nó sẽ đánh dấu là true) cho đến khi không còn đỉnh nào mà chưa đc thăm nữa thì nó sẽ
dừng vòng lặp for lại và ra vòng lặp while để lấy đỉnh ở đầu danh sách hàng chờ ra khỏi hàng chờ và xuất ra rồi lại tiếp tự duyệt danh
sách kề của đỉnh vừa xuất ra chứ như vậy cho đến khi các đỉnh trong đồ thị đc thăm hết và xuất ra lần lượt cho đến khi danh sách hàng
đợi không còn đỉnh nào nữa thì hàm BFS(thuật toán tiềm kiếm theo chiều rộng của đồ thị) cũng đã hoàn thành. Đã giải thích từng bước chạy
của thuật toán BFS(Tìm kiếm theo chiều rộng của đồ thị) ở trong vở cấu trúc dữ liệu và giải thuật đồ thị 1 bài 9 nếu quên hãy mở vở ra
để xem.*/
void BFS(int u) {
    //Khởi tạo queue để chứa các đỉnh đã đc thăm ở trong đồ thị
    queue<int> q;
    q.push(u);/*Thêm phần tử theo cơ chế của queue là FIFO - Firt In Firt Out nghĩa là vào trước ra trước tức là thêm(Push) ở cuối danh
    sách còn lấy(Pop) thì lấy ở đầu danh sách*/
    visited[u] = true;

    //Duyệt danh sách danh sách hàng đợi xem có đỉnh nào trong hàng đợi hay không
    while (!q.empty())
    {
        int v = q.front();//Lấy đỉnh ở đầu đợi ra. Tức là tạo ra biên v để lưu giá trị của đỉnh đầu hàng đợi 
        q.pop();/*Lấy phần tử theo cơ chế của queue là FIFO - Firt In Firt Out nghĩa là vào trước ra trước tức là thêm(Push) ở cuối danh
        sách còn lấy(Pop) thì lấy ở đầu danh sách*/
        cout << v << " ";//Xuất đỉnh ở đầu hàng đợi ra 

        for (int x : adj[v])
        {
            if (!visited[x])
            {
                q.push(x);
                visited[x] = true;
            }
        }
    }
}

int main() {
    inp();
    cout << "Thu tu cac dinh duoc duyet voi thuat toan BFS tim kiem theo chieu rong cua do thi: \n";
    BFS(1);
}
#endif // 1
