//========================THUẬT TOÁN KIỂM TRA ĐỈNH TRỤ VÀ ĐỈNH CẦU CỦA ĐÒ THỊ ===============================================
#include <iostream>
#include<vector>
using namespace std;

/*Bài toán: Đếm xem đồ thị có bao nhiêu đỉnh trụ và cạnh cầu 
input: n = 10 đỉnh và m = 6 cạnh | output: với input đó thì đồ thị có 3 đỉnh trụ
                5 4              |  5 , 10 , 2
                5 2              |
                10 2             |
                10 7             |
                5 3              |
                10 1             |
                
Bài toán: Đếm xem đồ thị có bao nhiêu cạnh cầu
input: n = 10 đỉnh và m = 8 cạnh | output: với input đó thì đồ thị có 2 cạnh cầu là 10 9 và 10 8
                10 9             |
                10 8             |
                10 3             |
                10 4             |
                5 3              |
                10 1             |               
                5 1              |
                5 4              |*/
int n, m;//n là số đỉnh và m là số cạnh
const int maxn = 20;//Giá trị mặc định
vector<int> adj[maxn];//Danh sách kề của các đỉnh
vector<pair<int, int>> dsachCanh;

bool visited[maxn];

void inp() {
    cout << "Nhap vao n so dinh va m so canh cua do thi: \n";
    cin >> n >> m;

    cout << "Nhap vao hai dinh x va y noi thanh canh cua do thi: \n";
    for (short i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
        dsachCanh.push_back({ x,y });//Danh sách cạnh
    }
    memset(visited, false, sizeof(visited));
}

//Áp dụng thuật toán DFS để đếm số thàng phần liên thông của đồ thị để kiêm tra đỉnh trụ
void DFS(int u) {
    visited[u] = true;
    for (int v : adj[u]) {
        if (!visited[v])
        {
            DFS(v);
        }
      }
    }

/*Áp dụng thuật toán DFS để đếm số thàng phần liên thông của đồ thị để kiêm tra cạnh cầu. Thì thuật toán DFS2 này khi mở rộng đồ thị nó
sẽ không bao giờ duyệt vào cạnh s t để khi mà ta loại bỏ 1 cạnh x y nào đó thì ta chỉ cần truyền tham số x y vào tức là như loại bỏ đỉnh
thì muốn loại bỏ 1 đỉnh ta chỉ cần thăm đỉnh đó thì ở đây tương tự muốn loại bỏ 1 cạnh nào đó trong đố thị thì chỉ cần truyền cặp đỉnh
x y tạo thành cạnh của đồ thị tức là cạnh s t vào hàm DFS2 này cho DFS2 thăm tương đương với việc DFS2 sẽ k thăm lại cạnh x y đã đc thăm
nữa đồng nghĩa với việc loại bỏ cạnh x y tức s t ra khỏi đồ thị*/
void DFS2(int u, int s, int t) {
    visited[u] = true;
    for (int v : adj[u]) {
        if ((u == s && v == t) || (u == t && v == s))//Nếu ta đang xét đến cạnh mà ta muốn loại khỏi đồ thị thì ta 
            continue; //dừng lại không xét cạnh này nữa vì ta lại đỉnh này ra khỏi đồ thì mà

            if (!visited[v])
                DFS2(v, s, t);
    }
}

void DinhTru() {
    int ans = 0;//Biến ans dùng để đếm số lượng đỉnh trụ
    int tplt = 0;//Biến dùng để đếm số thành phần liên thông của đồ thị
    memset(visited, false, sizeof(visited));

    //Đếm số thành phần liên thông của đồ thị trước khi kiểm tra đỉnh hoặc cạnh trụ
    for (short i = 1; i <= n; i++)
    {
        if (!visited[i])
        {
            ++tplt;
            DFS(i);
        }
    }

    cout << "Cac dinh tru cua do thi la: ";
    //Duyệt từng đỉnh và loại đỉnh ra khỏi đồ thị
    for (short i = 1; i <= n; i++)
    {
        //Loại bỏ đỉnh i ra khỏi đồ thị bằng cách cho visited của đỉnh đó là true tức là đánh dấu đỉnh đó là đỉnh đã đc thăm
        memset(visited, false, sizeof(visited));
        visited[i] = true;/*loại bỏ lần lượt từng đỉnh trong đồ thị vì khi muốn loại bỏ 1 đỉnh nào đó trong đồ thị thì ta chỉ cần đánh 
        dấu đỉnh đó là đã đc thăm thì DFS sẽ k duyệt đỉnh đó nữa tức đã loại đỉnh đó ra khỏi đồ thị*/
        int dem = 0;//Dùng để đếm số thành phần liên thông sau khi loại bỏ đỉnh i
        
        //Đếm số thành phần liên thông của đồ thị sau khi loại 1 bỏ lần lượt từng đỉnh trong đồ thị 
        for (short j = 1 ; j <= n; j++)
        {
            if (!visited[j])/*Tức nếu đỉnh trong đồ thị mà chưa đc DFS thăm thì truyền vào cho DFS thăm để đếm số thành phần liên thông
                của đồ thị mõi lần 1 đỉnh trong đồ thị đc truyền vào hàm DFS thì tương đương với 1 thành phần liên thông */
            {
                ++dem;//tăng biến đếm số thành phần liên thông của đồ thị lên
                DFS(j);
            }
        }
        if (dem > tplt)//Sau khi lại đỉnh i bất kì mà làm cho đồ thị tăng số thành phần liên thông thì đỉnh i là đỉnh trụ
        {
            cout << i << " ";
            ++ans;//Tăng biến đếm đỉnh trụ lên
        }
    }

    cout << "\nVay do thi gom " << ans << " dinh tru    \n";
}

void CanhCau() {
    int ans = 0;//Biến ans dùng để đếm số lượng đỉnh trụ
    int tplt = 0;//Biến dùng để đếm số thành phần liên thông của đồ thị
    memset(visited, false, sizeof(visited));

    cout << "\nDo thi gom cac canh cau: \n";
    //Đếm số thành phần liên thông của đồ thị trước khi kiểm tra đỉnh hoặc cạnh trụ
    for (short i = 1; i <= n; i++)
    {
        if (!visited[i])
        {
            ++tplt;
            DFS(i);
        }
    }

    //Duyệt từng cạnh của đồ thị để loại bỏ các cạnh
    for (auto it : dsachCanh) {
        //x và y là cạnh của đồ thị trong danh sách cạnh
        int x = it.first;
        int y = it.second;

        //loại bỏ lần lượt từng cạnh x y trong đồ thị
        memset(visited, false, sizeof(visited));
        int dem = 0;//Dùng để đếm số thành phần liên thông sau khi loại bỏ cạnh x y

        //Đếm số thành phần liên thông của đồ thị sau khi loại bỏ lần lượt từng cạnh trong đồ thị 
        for (short j = 1; j <= n; j++)
        {
            if (!visited[j])/*Tức nếu đỉnh trong đồ thị mà chưa đc DFS2 thăm thì truyền vào cho DFS thăm để đếm số thành phần liên thông
                của đồ thị mõi lần 1 cạnh trong đồ thị đc truyền vào hàm DFS2 thì tương đương với 1 thành phần liên thông */
            {
                ++dem;//tăng biến đếm số thành phần liên thông của đồ thị lên
                DFS2(j, x,y);
            }
        }
        if (dem > tplt)//Sau khi lại cạnh x y bất kì mà làm cho đồ thị tăng số thành phần liên thông thì đỉnh i là đỉnh trụ
        {
            
            ++ans;//Tăng biến đếm cạnh cầu lên
            cout << x<<" " << y << "\n";
        }
    }

    cout << "Vay do thi gom " << ans << " canh cau \n";
}


int main()
{
    inp();
    DinhTru();
    CanhCau();
}