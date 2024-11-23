/*======================ÁP DỤNG BFS VÀO THUẬT TOÁN KIỂM TRA ĐỒ THỊ HAI PHÍA========================*/
#if 0
#include <iostream>
#include<vector>
#include<queue>
using namespace std;


/*bài toán : Kiểm tra đồ thị có là đồ thị hai phía hay không
input: n = 6, m = 5   |    output: với input đó thì kết quả là đồ thị trên là đồ thị hai phía
           2 1        |
           2 3        |
           3 4        |
           5 4        | 
           1 6        |*                                                                                */

const int maxn = 20;//biến có giá trị mặc định 
int n, m;//n là đỉnh m là cạnh của đồ thị
vector<int> adj[maxn];//Dsach kề của 1 đỉnh
int color[maxn];//Mảng tô màu đỉnh của đồ thị


void inp() {
    cout << "Nhap n dinh va m canh cua do thi: \n";
    cin >> n>> m;

    cout << "Nhap vao hai dinh x va y tao thanh canh cua do thi: \n";
    for (short i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    memset(color, -1, sizeof(color));//tất cả các đỉnh ban đầu là chưa có màu
}

//0 là red và 1 là blue
bool BFS(int u) {
    queue<int> q;
    q.push(u);
    color[u] = 0;//0 là màu red
    while (!q.empty())
    {
        int v = q.front();
        q.pop();
        for (int x : adj[v]) {
            if (color[x] == -1)//Nếu đỉnh kề với với v là đỉnh x mà chưa có màu
            {
                color[x] = 1 - color[v];/*cho color của x bằng 1 vì v(là dỉnh ở đầu hàng đợi tức là đỉnh u vừa đc truyền vào danh sách
                hàng đợi) trong hàng đợi lúc này là đang bằng 0 nên 1 -0 là bằng 1 mà 1 tức là màu blue hoặc nếu v mà bằng 1 thì x = 0
                tức tô lần lượt các đỉnh sao cho mõi lần tô là các đỉnh có màu khác nhau nếu luôn tô màu đc các đỉnh trên đồ thị vs 2 
                màu khác nhau thì đồ thị là đồ thị hai phía*/
                q.push(x);
            }
            else if (color[x] == color[v])/*Nếu x là đỉnh kề của v mà x đã đc tô màu trùng màu với v thì 2 đỉnh x và v nằm trong 1 tập 
                và đã có 2 đỉnh nối với nhau nằm chung 1 tập tức 2 đỉnh đã có chung 1 màu và nằm chung 1 tập nên đồ thị k phải là đồ 
                thị hai phía hình đồ thị trong vỡ đồ thị 5  bài thuật toán kiểm tra đồ thị hai phía*/
                return false;
        }

    }
    return true;//nếu luôn tô màu đc các đỉnh trên đồ thị vs 2 màu khác nhau thì đồ thị là đồ thị hai phía
}

//0 là màu red còn 1 là màu blue
bool DFS(int u, int par) {
    color[u] = 1 - color[par];//tức tô màu các đỉnh ngược màu nhau 1 là 0(red) 2 là 1(blue) 
    for (int v : adj[u]) {
        if (color[v] == -1)
        {
            if (!DFS(v, u))/*Nếu return về DFS(v,u) thì nó sẽ có nhánh nào đó thuộc DFS sẽ return true và có nhánh khác return false, nên
                ở đây ta kết luận nếu có nhánh return false thì ta trả về hàm DFS là false luôn tức đồ thị k là đồ thị 2 phía còn ví dụ
                ta return về true thì chưa chắc gì đó là đồ thị 2 phía vì lỡ có nhánh false nữa mà khi gặp nhánh true nó đã kết thúc 
                hàm DFS rồi.*/
                return false;
        }
        else if(color[v] == color[u])
        {
            return false;
        }
    }
    return true;//nếu luôn tô màu đc các đỉnh trên đồ thị vs 2 màu khác nhau thì đồ thị là đồ thị hai phía

}

int main()
{
    inp();
    bool check = true;
    for (short i = 1; i <= n; i++)
    {
        if (color[i] == -1) {
            if (!BFS(i)) {
                check = false; 
                break;
            }
        }
    }
    if (check)
        cout << "Do thi tren la do thi hai phia !";
    else
        cout << "Do thi tren khong la do thi hai phia !";
}


#endif // 0

/*======================ÁP DỤNG DFS VÀO THUẬT TOÁN KIỂM TRA ĐỒ THỊ HAI PHÍA========================*/
#if 1
#include <iostream>
#include<vector>
#include<queue>
using namespace std;


/*bài toán : Kiểm tra đồ thị có là đồ thị hai phía hay không
input: n = 6, m = 5   |    output: với input đó thì kết quả là đồ thị trên là đồ thị hai phía
           2 1        |
           2 3        |
           3 4        |
           5 4        |
           1 6        |*                                                                                */

const int maxn = 20;//biến có giá trị mặc định 
int n, m;//n là đỉnh m là cạnh của đồ thị
vector<int> adj[maxn];//Dsach kề của 1 đỉnh
int color[maxn];//Mảng tô màu đỉnh của đồ thị


void inp() {
    cout << "Nhap n dinh va m canh cua do thi: \n";
    cin >> n >> m;

    cout << "Nhap vao hai dinh x va y tao thanh canh cua do thi: \n";
    for (short i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    memset(color, -1, sizeof(color));//tất cả các đỉnh ban đầu là chưa có màu
}

//0 là màu red còn 1 là màu blue
bool DFS(int u, int par) {
    color[u] = 1 - color[par];//tức tô màu các đỉnh ngược màu nhau 1 là 0(red) 2 là 1(blue) 
    for (int v : adj[u]) {
        if (color[v] == -1)
        {
            if (!DFS(v, u))/*Nếu return về DFS(v,u) thì nó sẽ có nhánh nào đó thuộc DFS sẽ return true và có nhánh khác return false,
                  nên
                ở đây ta kết luận nếu có nhánh return false thì ta trả về hàm DFS là false luôn tức đồ thị k là đồ thị 2 phía còn ví dụ
                ta return về true thì chưa chắc gì đó là đồ thị 2 phía vì lỡ có nhánh false nữa mà khi gặp nhánh true nó đã kết thúc
                hàm DFS rồi.*/
                return false;
        }
        else if (color[v] == color[u])
        {
            return false;
        }
    }
    return true;//nếu luôn tô màu đc các đỉnh trên đồ thị vs 2 màu khác nhau thì đồ thị là đồ thị hai phía

}

int main()
{
    inp();
    bool check = true;
    color[0] = 1;//Cho đỉnh cha của đỉnh i ban đầu là màu 1 là màu blue hoặc là màu 0 là màu red cũng đc
    for (short i = 1; i <= n; i++)
    {
        if (color[i] == -1) {
            if (!DFS(i,0)) {
                check = false;
                break;
            }
        }
    }
    if (check)
        cout << "Do thi tren la do thi hai phia !";
    else
        cout << "Do thi tren khong la do thi hai phia !";
}


#endif // 0

