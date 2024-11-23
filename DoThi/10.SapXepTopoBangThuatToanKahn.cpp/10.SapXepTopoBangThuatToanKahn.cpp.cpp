#include <iostream>
#include<vector>
#include<queue>
using namespace std;

/*Áp dụng BFS vào thuật toán Kahn dùng để sắp xếp topo chỉ áp dụng đc trên đồ thị có hướng và không có chu trình

input: Nhập vào n số đỉnh của đồ     | output: Xuất ra kết quả thứ tự các đỉnh sau khi sắp xếp topo trên
thị có hướng là n = 7 tức từ 1 đến   | đồ thị là thứ tự các đỉnh trong đồ thị sau khi đc sắp xếp nằm trong
7, nhập vào m số cạnh của đồ thị có  | danh sách topo là:
hướng là m = 7 gồm các cạnh:         |
                                     |
                   1 2               |              1 7 2 6 3 4 5
                   2 3               |
                   2 4               |
                   3 5               |
                   4 5               |
                   1 6               |
                   7 6               |
                                                                                                           */

int n, m;
int in[20];//Mảng dùng để chứa số bán bậc vào của các đỉnh trong đồ thị 
bool visited[20];//Vector visited dùng để chứa và đánh dấu các đỉnh là đã ddc thăm hay chưa
vector<int> adj[20];//Vector adj chứa danh sách kề của các đỉnh trong đồ thị có hướng  
vector <int>topo;//Vector topo chứa các đỉnh sau khi đc sắp xếp

void inp() {
    cout << "Nhap vao n dinh va m canh cua do thi: \n";
    cin >> n >> m;

    cout << "Nhap vao hai dinh x va y noi voi nhau tao thanh canh cua do thi: \n";
    for (short  i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;

        adj[x].push_back(y);
        in[y]++;/*dùng để tính số bán bậc vào của các đỉnh trong đồ thị có hướng. Ví dụ ta có đồ thì có hướng 3 đỉnh là 1 2 3 và 2 cạnh
        là 1 2 và 3 2 thì ta thấy đối với cạnh 1 2 thì đỉnh 1 là x và đỉnh 2 là y thì khi 2 đc thêm vào danh sách đỉnh kề với đỉnh 1 
        thì đỉnh 2 đc tăng số bán bậc vào lên 1 bậc tức là đỉnh 2 có bán bậc vào là đỉnh 1, đối với cạnh 3 2 thì đỉnh 3 là x và đỉnh 2
        là y thì khi 2 đc thêm vào danh sách đỉnh kề với đỉnh 3 thì đỉnh 2 lại đc tăng số bán bậc vào lên 1 bậc nữa thì số bán bậc vào
        của đỉnh 2 lúc này là 2 bậc tức là đỉnh 2 có bán bậc vào là đỉnh 1 và đỉnh 3. Còn đối với đỉnh 1 và đỉnh 3 thì đỉnh thì không 
        có đỉnh nào đi vào 2 đỉnh 1 và 3 chỉ có từ đỉnh 1 và đỉnh 3 đi vào đỉnh 2 thôi tức đỉnh 1 và đỉnh 3 là đỉnh nối với đỉnh 2 theo 
        hướng từ đỉnh 1 vào đỉnh 2 và từ đỉnh 3 vào đỉnh 2 thì đỉnh 1 và đỉnh 3 không có đỉnh nào trước hai đỉnh 1 và 3 nữa nên hai 
        đỉnh 1 và đỉnh 3 có số bán bậc vào là bằng 0. Tóm lại mõi lần một đỉnh mà xuất hiện trong danh sách kề của đỉnh nào đó thì đỉnh 
        mà nằm trong danh sách kề của đỉnh khác sẽ đc tăng số bán bậc lên tương ứng với mõi lần xuất hiện 
         */

    }
    memset(visited, false, sizeof(visited));
}

/*GIẢI THÍCH NGẮN GỌN cơ chế của thuật toán kahn(sử dụng thuật toán BFS(thuật toán tìm kiếm theo chiều rộng) để sắp xếp các đỉnh theo
topo): Đầu tiên ta phải tính số bán bậc vào của các đỉnh trong đồ thị sau đó ta tạo ra 1 vòng lặp for chạy lần lượt hết tất cả các đỉnh
trong đồ thị nếu đỉnh nào có số bán bậc vào mà bằng 0 thì ta push vào danh sách hàng chờ cho đến khi duyệt hết các đỉnh trong đồ thị 
thì thoát khỏi vòng lặp for thì lúc này trong danh sách queue đã có các đỉnh có số bán bậc vào là bằng 0 rồi nên khi này chương trình 
sẽ vào vòng lặp while để duyệt danh sách queue nếu danh sách queue khác rỗng thì lấy phần từ ở đầu danh sách hàng đợi ra khỏi hàng đợi
và thêm đỉnh vừa đc lấy ra ở đầu hàng đợi vào danh sách sắp xếp các đỉnh topo sau đó nó sẽ duyệt danh sách kề của đỉnh vừa đc lấy ra 
khởi hàng đợi và thêm vào danh sách sắp xếp topo để trừ tất cả số bán bậc vào của đỉnh kề với nó xuống 1 bậc(Lí do ta phải trừ tất số 
bán bậc vào của đỉnh kề với nó xuống 1 bậc vì như ta biết đỉnh mà có số bán bậc vào mà bằng 0 thì tức đỉnh đó không có hành động nào
trước nó tức không còn đỉnh nào đi vào nó nữa và chỉ có nó đi vào các đỉnh khác thì đỉnh nào đc nó đi vào thì gọi là đỉnh kề với nó
khi trừ số bán bậc vào của các đỉnh kề với nó xuống 1 có nghĩa là đỉnh mà vừa lấy ra khỏi danh sách hàng chờ và thêm vào danh sách
sắp xếp topo cũng bị xóa khỏi đồ thị và cả đường đi vào của nó tới các đỉnh kề với nó cũng bị xóa nên các đỉnh kề với nó mới phải trừ
số bán bậc vào xuống 1 bậc đó là lý do vì sao thuật toán kahn là áp dụng thuật toán BFS để sắp xếp topo các đỉnh thì ngoài cái tên là
kahn thì nó có 1 cái tên khác nữa là thuật toán xóa dần đỉnh) sau khi trừ số bán bậc vào của các đỉnh kề với đỉnh vừa đc lấy ra khỏi 
hàng đợi  xuống 1 bậc thì trong vòng lặp duyệt danh sách kề này khi trừ số bán bậc vào của đỉnh nào xuống 1 bậc đồng thời nó cũng kiểm
tra xem có đỉnh kề vừa đc trừ thì số bán bậc vào của đỉnh kề vừa đc trừ có bằng 0 hay không nếu bằng 0 thì thêm vào danh sách hàng chờ
còn khác 0 thì tiếp tục trừ số bán bậc vào của các đỉnh kề với đỉnh đang đc mở rộng ra để duyệt này xuống 1 bậc và đồng thời vừa trừ
xong thì xét luôn đỉnh vừa đc trừ có bằng 0 hay là không nếu có thì đc thêm vào danh sách hàng chờ cho đến khi trong danh sách kề của 
đỉnh đang đc mở rộng ra duyệt không còn đỉnh nào nữa thì dừng lại tiếp tục quay ra vòng lặp while rồi làm tương tự...... cho đến khi
danh sách hàng đợi(queue) không còn đỉnh nào trong danh sách nữa thì lúc thuật toán kahn cũng thực hiện xong việc sắp xếp topo khi áp
dụng thuật toán BFS.*/
void Kahn() {
    queue<int> q;//Dùng hàng đợi để lưu các đỉnh có số bán bặc vào bằng 0 
    for (short i = 1; i <= n; i++)/*Vòng lặp duyệt tất cả các đỉnh trong đồ thị nếu có đỉnh nào có số bán bậc vào mà bằng 0 thì ta push
    vào danh sách hàng chờ*/
    {
        if (in[i] == 0) {/*Khi hàm Kahn bắt đầu thực thi nếu đỉnh nào của đồ thị có số bán bậc vào mà bằng 0 thì đỉnh đó sẽ đc push vào
            danh sách hàng đợi. Vì sắp xếp đỉnh theo topo là phải đảm bảo đỉnh nào nằm trước thì phải xuất hiện trước khi đc thêm vào
            danh sách sắp xếp topo nên đỉnh mà có số bán bậc vào mà bằng 0 thì đồng nghĩa với việc đỉnh mà có số bán bậc vào mà bằng 0
            thì đỉnh đó không có hàng động nào trước nó tức không có đỉnh nào nằm trước nó nữa nên ban đầu đỉnh nào mà có số bán bậc vào'
            mà bằng 0 thì đỉnh đó sẽ đc thêm và nằm ở đầu danh sách sắp xếp topo.*/
            q.push(i);
        }
    }

    while (!q.empty())//Nếu hàng đợi mà khác rỗng tức có phần tử thì thỏa đk vòng lặp while
    {
        int u = q.front();//Biến u là biến dùng để lưu đỉnh nằm ở đầu danh sách hàng chờ
        q.pop();/*Lấy đỉnh ở đầu hàng đợi ra khỏi hàng đợi(queue) khi lấy ra thì đồng nghĩa với đỉnh nằm ở đầu hàng đợi vừa đc lấy ra 
        cũng bị xóa khỏi đồ thị và hàng đợi.*/
        topo.push_back(u);//Thêm đỉnh vừa dc lấy ra ở đầu danh sách queue vào danh sách 
        for (int v : adj[u]) {
            in[v]--;//Trừ bán bậc vào của đỉnh kề với đỉnh vừa đc lấy ở đầu danh sách hàng đợi(là đỉnh u) xuống 1 bậc
            if (in[v] == 0){/*Sau khi trừ bán bậc vào của tất cả các đỉnh kề với đỉnh vừa lấy ra khỏi hàng đợi xuống 1 bậc thì ta kiểm 
                tra nếu đỉnh nào có số bán bậc vào mà bằng 0 thì thêm lần lượt các đỉnh có số bán bậc vào bằng 0 vào hàng đợi vì ta biết
                ta tạo ra hàng đợi để lưu các đỉnh có bán bậc vào bằng 0 */
            
                q.push(v);
            }
        }
    }

    cout << "Danh sach topo sau khi cac dinh dc sap xep bang thuat toan Kahn: ";
    for (int x : topo) {
        cout << x << " " << " ";

    }
 }

int main()
{
    inp();
    Kahn();
}
