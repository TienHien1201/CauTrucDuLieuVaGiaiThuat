#include <iostream>
#include<vector>
using namespace std;

/*Áp dụng DFS  vào thuật toán sắp xếp TOPO chỉ áp dụng đc trên đồ thị có hướng và không có chu trình

input: Nhập vào n số đỉnh của đồ     | output: Xuất ra kết quả thứ tự các đỉnh sau khi sắp xếp topo trên 
thị có hướng là n = 7 tức từ 1 đến   | đồ thị là thứ tự các đỉnh trong đồ thị sau khi đc sắp xếp nằm trong            
7, nhập vào m số cạnh của đồ thị có  | danh sách topo là:      
hướng là m = 7 gồm các cạnh:         | 
                                     | 
                   1 2               |              7 1 6 2 4 3 5 
                   2 3               | 
                   2 4               |  
                   3 5               |
                   4 5               |
                   1 6               |
                   7 6               |
                                                                                                           */
int n, m;
bool visited[10];//Vector visited dùng để chứa và đánh dấu các đỉnh là đã ddc thăm hay chưa 
vector <int> adj[10];//Vector adj chứa danh sách kề của các đỉnh trong đồ thị có hướng  
vector <int> topo;//Vector topo chứa các đỉnh sau khi đc sắp xếp


void inp() {
    cout << "Nhap vao n dinh va m canh cua do thi co huong: \n";
    cin >> n >> m;

    cout << "Nhap vao dinh x va dinh y de noi thanh canh cua do thi co huong: \n";
    for (short i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
     
        adj[x].push_back(y);
    }
    memset(visited, false, sizeof(visited));
}

/*GIẢI THÍCH ngắn gọn: đỉnh đc duyệt xong đầu tiên thì sẽ đc push vào danh sách topo tức đỉnh nào mà sau khi đc thăm xong mở rộng ra
ra thăm cách đỉnh ở trong danh sách kề của nó mà không còn đỉnh nào kề với nó mà chưa đc thăm nữa thì đỉnh đó đc gọi là đã duyệt xong
và đc đẩy vào danh sách sắp xếp topo mà đỉnh đc thăm đầu tiên là đỉnh nằm ở cuối danh sách topo, thì thuật toán DFS(thuật toán tìm kiếm
theo chiều sau của đồ thị) nó sẽ thăm đỉnh kề với đỉnh vừa đc thăm bằng cách duyệt danh sách kề của đỉnh vừa đc thăm nếu có đỉnh nào
kề với đỉnh vừa đc thăm mà chưa đc thăm của lần duyệt trong lần phát hiện đó thì ta truyền đỉnh chưa đc thăm trong lần duyệt danh sách
kề của đỉnh vừa đc thăm này vào lời đệ quy gọi DFS cứ như thế cho đến khi đỉnh nào đc duyệt xong đầu tiên thì đỉnh vừa dc duyệt xong
đầu tiên này cũng đc push vào danh sách topo nên nó cũng là phần tử đầu tiên nằm trong danh sách topo luôn cứ như thế từ 1 đỉnh vừa 
duyệt xong đầu tiên hàm DFS sẽ backtrack về lại lời gọi hàm DFS liền với hàm DFS mang trạng thái của đỉnh vừa đc duyệt xong và thực 
hiện xong và duyệt tiếp danh sách kề của hàm mang trạng thái của đỉnh trong lần backtrack này nếu có đỉnh mà chưa đc thăm thì nó lại 
truyền đỉnh đó vào lời gọi hàm đệ quy DFS và thăm đỉnh đó cho đến khi đỉnh nào mà dc duyệt xong lại tiếp tục đc đẩy vào danh sách 
topo và thực hiện việc backtrack lại lần gọi hàm liền trước của đỉnh vừa đc duyệt xong cứ như thế lần lượt các đỉnh mà đc duyệt xong
sẽ đẩy vào danh sách topo cho đến khi hàm DFS không còn trạng thái của đỉnh nào để thực hiện nữa thì hàm DFS thực hiện xong việc sắp
xếp các đỉnh trong đồ thị có hướng vào danh sách topo, danh sách sắp xếp topo lúc này thứ tự các đỉnh đc lưu trong danh sách topo đang
bị ngược nên ta chỉ cần reverse(đảo ngược) thứ tự các đỉnh trong danh sách topo là xong. Phần giải thích cơ chế của chương trình rất 
kỹ từng bước 1  đã giải thích ở trong vở cấu trúc dữ liệu và giải thuật đồ thị 3 nếu đọc đây không nhớ bước nào hãy mở vở xem lại. */
void DFS(int u) {
    visited[u] = true;
    for (int x : adj[u]) {
        if (!visited[x])
        {
            DFS(x);
        }
    }
    topo.push_back(u);
}

int main()
{
    inp();
    for (short i = 1; i <= n; i++)
    {
        if (!visited[i])
        {
            DFS(i);
        }
    }
    reverse(topo.begin(), topo.end());
    cout << "Danh sach sap xep topo cua cac dinh trong do thi co huong: ";
    for (int x : topo)
        cout << x << " ";
}

