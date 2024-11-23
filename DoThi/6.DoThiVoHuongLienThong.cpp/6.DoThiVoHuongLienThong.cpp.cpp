#if 0
#include <iostream>
#include<vector>
using namespace std;
/*Áp dung thuật thuật DFS(Tìm kiếm theo chiều sâu của đồ thị) và thuật toán BFS(Tìm kiếm theo chiều rộng của đồ thị) vào bài toán
Đếm số thành phần liên thông của đồ thị Hoặc bài toán kiểm tra xem đồ thị có liên thông hay không thì ta chỉ cần đếm số thành phần
liên thông của đồ thị nếu mà bằng 1 thì ta kết luận đồ thị là liên thông ngược lại thì đồ thị không liên thông vì đồ thị liên thông
khác với thành phần liên thông của đồ thị.

- THÀNH PHẦN LIÊN THÔNG CỦA ĐỒ THỊ: Là trong 1 đồ thị có các đỉnh tạo thành cạnh nhưng bị tách ra thành 1 khối riêng nhưng các đỉnh
đó vẫn nằm trong đồ thị, giống Hình trong vở cấu trúc dữ liệu & giải thuật đồ thị 2 bài 10 nếu quên hãy mở ra xem
Input: gồm 10 đỉnh(n) là từ 1 đến 10 và | Output: là số thành phần liên thông của đồ thị
8 cạnh(m) gồm:                          |
              1 2                       |
              2 3                       |
              2 4                       |
              3 6                       |
              3 7                       |
              5 8                       |
              6 7                       |  
              8 9                       |  

- ĐỒ THỊ LIÊN THÔNG: là đồ thị luôn có đường đi giữa 2 đỉnh bất kì của thị tức là nó tạo thành 1 khối và không có đỉnh nào bị tách
ra khỏi đồ thị
Input: gồm 10 đỉnh(n) là từ 1 đến 10 và | Output: là kiểm tra xem đồ thị đó có liên thông hay không
10 cạnh(m) gồm:                         |
              1 2                       |
              2 3                       |
              2 4                       |
              3 6                       |
              3 7                       |
              3 8                       |
              5 8                       |
              5 10                      |
              6 7                       |
              8 9                       |                                                                                 */
int n, m;
vector<int> adj[20];
bool visited[20];

void inp() {
    cout << "Nhap vao n dinh va m canh cua do thi: \n";
    cin >> n>> m;
    
    cout << "Nhap vao cap dinh x va y tao thanh canh cua do thi: \n";
    for (short i = 0; i < m; i++)
    {
        int x, y;
        cin >> x>> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
        memset(visited, false, sizeof(visited));
    }
}

/*Hàm DFS - Thuật toán tìm kiếm theo chiều sâu của đồ thị. Mục đích tạo ra hàm DFS để gọi trong hàm connectComponent để thăm tất các 
các đỉnh trong thành phần liên thông của đồ thị.*/
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

/*Hàm đếm số thành phần liên thông của đồ thị. 
GIẢI THÍCH NGẮN GỌN CƠ CHẾ CỦA HÀM connectComponent - Hàm đếm số thành phần liên thông của đồ thị: Chương trình sẽ duyệt tất cả các
đỉnh của đồ thị và khi phát hiện có đỉnh mà chưa được thăm(tức là đang false) thì chương trình sẽ tăng biến lưu số thành phần liên 
thông của đồ thị lên và gọi hàm DFS(Hoặc BFS) rồi truyền đỉnh đó vào trong hàm DFS (hoặc là BFS tùy vào thuộc vào ta muốn sài cái 
nào thì 2 thuật toán BFS(tìm kiếm theo chiều rộng của đồ thị) và DFS(tìm kiếm theo chiều sâu của đồ thị) có độ phức tạp là như nhau
nhưng đc cái DFS code ngắn hơn nên ta dùng DFS) thì ở trong hàm DFS này nó sẽ duyệt tất cả các đỉnh trong thành phần liên thông của
đồ thị và đánh dấu là true(tức là đã đc thăm) cứ như thế mõi lần vòng lặp mà phát hiện đỉnh chưa đc thăm thì nó sẽ tăng biến dùng để
lưu số thành phần liên thông của đồ thị lên và truyền đỉnh đó vào hàm DFS khi đỉnh đó đc truyền vào hàm DFS thì hàm DFS sẽ thăm tất
cả các đỉnh trong thành phần liên thông của đồ thị theo các mà hàm DFS duyệt là tìm kiếm theo chiều sâu(Ví dụ thành phần liên thông 
thứ nhất gồm 3 đỉnh và 2 cạnh là 1 nối với 2, 2 nối với 3 thì khi phát hàm connectComponent phát hiện đỉnh 1 chưa đc thăm thì nó sẽ 
tăng biến dùng để lưu số thành phần liên thông của đồ thị lên và gọi hàm DFS rồi truyền đỉnh 1 vào Hàm DFS khi đỉnh 1 đc truyền vào 
hàm DFS thì Hàm DFS sẽ xử lí là đánh dấu đỉnh 1 đã đc thăm và duyệt danh sách kề của đỉnh 1 mà đỉnh kề với đỉnh 1 là đỉnh 2 nên nó
xét đỉnh 2 thì thấy đỉnh 2 chưa đc thăm nên thõa dk if của hàm DFS nên đỉnh 2 sẽ đc truyền vào gọi hàm đệ quy DFS và đỉnh 2 lại đc
đánh dấu là true(là đã đc thăm) và lại tiếp tục duyệt danh sách kề của 2 mà đỉnh kề với đỉnh 2 là đỉnh 3 thì đỉnh 3 cũng chưa đc 
thăm nên thõa dk if của hàm DFS nên đỉnh 3 sẽ đc truyền vào gọi hàm đệ quy DFS và đỉnh 3 lại đc đánh dấu là true(là đã đc thăm) thì
lúc này thành phần liên thông của ta chỉ có 3 đỉnh nên khi hàm DFS đã thăm xong cả 3 đỉnh trong thành phần liên thông của đồ thị thì
dừng lại và ra vòng lặp for của hàm connectComponent để duyệt tiếp cho hết các đỉnh của đồ thị). Có nghĩa là vòng lặp for của hàm
connectComponent thì sẽ duyệt tất cả các đỉnh của đồ thị còn gọi hàm DFS thì vòng lặp for trong hàm DFS chỉ duyệt và thăm tất cả các
đỉnh trong thành phần liên thông của đồ thị, cứ như thế mõi lần vòng lặp for của hàm connectComponent phát hiện đc đỉnh nào của đồ 
thị mà chưa đc thăm thì nó sẽ tăng biến lưu số thành phần liên thông lên tương ứng với mõi lần phát hiện và truyền đỉnh đó vào hàm
DFS để xử lí việc thăm tất cả các đỉnh trong thành phần liên thông của đỉnh đó. Chi tiết cơ chế của thuật toán DFS(Tìm kiếm theo 
chiều sâu của đồ thị) nếu quên hãy mở vở cấu trúc dữ liệu & giải thuật - đồ thị 1 - bài 8 còn chi tiết cơ chế của thuật toán BFS(Tìm 
kiếm theo chiều rộng của đồ thị) nếu quên hãy mở vở cấu trúc dữ liệu & giải thuật - đồ thị 2 - bài 9 để xem lại */
void connectComponent() {
    int ans = 0;// Tạo ra biến ans để lưu số thành phần liên thông của đồ thị 
    for (short i = 1; i <= n; i++)
    {
        if (!visited[i]) {
            ++ans;
            cout << "Cac dinh thuoc thanh phan lien thong thu " << ans << " cua do thi la: ";
            DFS(i);//BFS(i);
            cout << "\n";
        }
    }
      cout << "So thanh phan lien thong cua do thi la: " << ans;  
}

int main()
{
    inp();
    connectComponent();
}
#endif // 0


#if 1
#include <iostream>
#include<vector>
#include<queue>
using namespace std;
/* Áp dụng thuật toán DFS(Thuật toán tìm kiếm theo chiều sâu của đồ thị) và thuật toán BFS(Thuật toán tìm kiếm theo chiều rộng của 
đồ thị) và Bài toán kiểm tra xem đồ thị có liên thông hay không.
- ĐỒ THỊ LIÊN THÔNG: là đồ thị luôn có đường đi giữa 2 đỉnh bất kì của thị tức là nó tạo thành 1 khối và không có đỉnh nào bị tách
ra khỏi đồ thị
Input: gồm 10 đỉnh(n) là từ 1 đến 10 và | Output: là kiểm tra xem đồ thị đó có liên thông hay không
10 cạnh(m) gồm:                         |
              1 2                       |
              2 3                       |
              2 4                       |
              3 6                       |
              3 7                       |
              3 8                       |
              5 8                       |
              5 10                      |
              6 7                       |
              8 9                       |                                                                                 */
int n, m;
vector<int> adj[20];
bool visited[20];

void inp() {
    cout << "Nhap vao n dinh va m canh cua do thi: \n";
    cin >> n>> m;
    
    cout << "Nhap vao cap dinh x va y tao thanh canh cua do thi: \n";
    for (short i = 0; i < m; i++)
    {
        int x, y;
        cin >> x>> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
        memset(visited, false, sizeof(visited));
    }
}

/*Hàm DFS - Thuật toán tìm kiếm theo chiều sâu của đồ thị. Mục đích tạo ra hàm DFS để gọi trong hàm connectComponent để thăm tất các 
các đỉnh trong thành phần liên thông của đồ thị.*/
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
//Hàm đếm số thành phần liên thông của đồ thị
void connectComponent() {
    int ans = 0;// Tạo ra biến ans để lưu số thành phần liên thông của đồ thị 
    for (short i = 1; i <= n; i++)
    {
        if (!visited[i]) {
            ++ans;
            cout << "Cac dinh lien thong cua do thi la: ";
            DFS(i);/*BFS(i) Có thể sử dụng thuật toán BFS cũng đc vì bản chất cả 2 thuật toán DFS(Thuật toán tìm kiếm theo chiều sâu 
            của đồ thị) là dùng để thăm tất cả các đỉnh liên thông*/
            cout << "\n";
        }
    }
    if(ans == 1)
    {
        cout << "Do thi nay la do thi lien thong !";
    }
    else
    {
        cout << "Do thi nay khong la do thi lien thong !";
    }
}

int main()
{
    inp();
    connectComponent();
}

#endif // 1
