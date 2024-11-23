#if 0
#include <iostream>
#include<vector>
#include<stack>
using namespace std;

/*=======CƠ CHẾ THUẬT TOÁN KOSARAJU=============
* Thuật toán Kasaraju áp dụng thuật toán DFS và chỉ cần dùng 2 thuật toán DFS là hoàn thành đc bài toán Thành phần liên thông mạnh của 
đồ thị có hướng

- BƯỚC 1: Gọi thuật toán DFS trên đồ thị ban đầu(Là đồ thị G - Graph là đồ thị gốc mà ta vừa nhập vào lúc ban đầu) và lưu thứ tự duyệt
các đỉnh vào 1 stack(stack này là danh sách sắp xếp topo khi áp dụng thuật toán DFS vào sắp xếp topo đỉnh nào đc thăm xong thì sẽ đc đẩy
vào stack này tạo thành sắp xếp topo như ta đã học sắp xếp topo ở file bài 9.ThuatToanSapXepToPo)
_ BƯỚC 2: Xây dựng đồ thị lật ngược đồ thị ban đầu(tức là xây dựng đồ thị TG - Transpose Graph(đồ thị chuyển đổi) đồ thị TG là đồ thị 
lật ngược lại cung của đồ thị G(là đồ thị ban đầu) ví dụ ta có đồ thị có hướng G có 1 nối tới 2 nhưng khi xây dựng đồ thị TG thì phải 
lật ngược cung của đồ thị G lại thành 2 nối tới 1 tương tự cho đến khi lật ngược hết các cung của đồ G lại thị xây dựng xong đồ thị TG)
- BƯỚC 3: Lần lựơt pop các đỉnh trong stack ở bước 1 và gọi thuật toán DFS để liệt kê các thành phần liên thông mạnh : Strongly connected
componts : SCC

*Cơ chế thuật toán Kosaraju giải thích rất kỹ trong vở cấu trúc dl & giải thuật -> đồ thị 4 nếu quên hãy mở lại xem 

Bài toán áp dụng thuật toán Kosaraju: Đếm số thành phần liên thông mạnh của đồ thị có hướng.( Đối với đồ thị mà có trên 1 thành phần
liên thông mạnh thì đồ thị đó k phải là đồ thị liên thông mạnh cụ thể đồ thị của bài này là đô thị không liên thông mạnh nhưng lại
có các thành phần liên thông mạnh)
Input: chỉ 1 lần nhập ra 2 đồ thị               | Output: với input của bài thì đếm đc 3 thành phần liên thông mạnh
1.là đồ thị G(là đồ thị ban đầu là đồ thị gốc)  |+ thành phần liên thông mạnh thứ 1 : 1 4 3 2
2.là đồ thị TG(là đồ transpose graph là đò thị  |+ thành phần liên thông mạnh thứ 2 : 5
có cung ngược lại của đồ thị G)                 |+ thành phần liên thông mạnh thứ 3 : 6 8 7
Với n đỉnh = 8 là từ 1 tới 8 và m cạnh = 9 là:  |                 
                  1 2                           |
                  2 3                           |
                  3 4                           |
                  4 1                           |
                  3 5                           |
                  5 6                           | 
                  6 7                           | 
                  7 8                           |
                  8 6                           |
*/
int n, m;
int topo[20];
vector <int> adj[20], r_adj[20];/*Danh sách adj chứa danh sách kề của các đỉnh của đồ thị G(Graph - đồ thị G là đồ thị gốc), danh sách 
r_adj chứa danh sách kề của các đỉnh của đồ thị TG(là đồ thị Transpose graph là đồ thị lật ngược các cung của đồ thị G lại)*/
bool used[20];//Mảng used dùng để đáng dấu các đỉnh là đã đc thăm hay chưa giống mảng visited mà chỉ khác tên 
stack <int> st;//Stack st chứa các đỉnh sắp xếp topo

void inp() {
    cout << "Nhap vao n dinh va m canh cua do thi co huong: \n";
        cin >> n >> m;

        cout << "Nhap vao hai dinh x va y tao thanh canh cua do thi co huong: \n";
        for (short i = 0; i < m; i++)
        {
            int x, y;
            cin >> x >> y;
            //danh sách adj là danh sách kề của đồ thị G(Draph là đồ thị gốc)
            adj[x].push_back(y);

            /*Bước 2: Xây dựng đồ thị Transpose Graph Lật ngược lại các cung của đồ thị G để hình thành đồ thị TG(Tranpose Graph) và
            đồ thị TG(Transpose Graph) đc lưu vào danh sách r_adj*/
            r_adj[y].push_back(x);           
        }
        memset(used, false, sizeof(used));
}

/*Hàm DFS1 dùng để thực hiện bước 1 của thuật toán Kosaraju là gọi tới đồ thị G(Graph - là đô thị ban đầu) để có đc 1 stack topo tức
là có đc danh sách sắp xếp topo các đỉnh của đồ thị G(Graph - là đô thị ban đầu)*/
void DFS1(int u) {
    used[u] = true;
    for (int v : adj[u]) {
        if (!used[v])
        {
            DFS1(v);
        }
    }

    /*Khi duyet xong dinh u. Vì thuật tóa kosaraju ta áp dụng sắp xết topo bằng DFS vào nữa mà sắp xếp topo bằng DFS ta đã học rất kỹ
    là mõi khi 1 đỉnh bất kì của đồ thị đc duyệt xong thì đỉnh đó sẽ dc thêm vào stack topo đỉnh nào càng duyệt xong sớm thì đỉnh đó
    trong danh sách topo có thứ tự càng ở cuối nên ta dùng stack để lưu các đỉnh đc sắp xếp topo là đúng với thứ tự vì cơ chế của 
    stack là LIFO - Last in Firt out tức là vào sau ra trước tức đỉnh nào đc duyệt xong cuối cùng là đỉnh nằm ở đầu stack tương đương
    với vị trí đỉnh đc duyệt xong cuối cùng là đứng đầu trong danh sách sắp xếp topo và đỉnh đc duyệt xong đầu tiên là đỉnh có vị trí 
    cuối cùng trong danh stack cũng như là danh sách sắp xếp topo tức stack là thêm là thêm ở đầu stack và lấy cũng ở đầu stack tương
    ứng với cơ chế LIFO - Last In Firt Out là vào sau ra trước của stack tức là mõi lần thêm là thêm vào đầu và mõi lần lấy là lấy ở 
    đầu luôn.*/
    cout << u << " ";
    st.push(u);
}

/*Hàm DFS2 dùng để: Mõi lần lấy ra 1 đỉnh ở trong danh sách topo nếu đỉnh đó ở trong đồ thị TG(là đồ thị lật ngược các cung lại của 
đồ thị G ,TG là là đồ thị Transpose Graph) mà chưa đc thăm thì sẽ đc truyền vào hàm DFS2 này để thăm các đỉnh trong đồ thị TG(Transpose
Graph) mõi lần gọi DFS2 trên đồ thị TG(Transpose Graph) thì DFS2 sẽ liệt kê các đỉnh thuộc cùng 1 thành phần liên thông mạnh tương 
ứng với đỉnh bắt đầu thuật toán DFS2*/
void DFS2(int u) {
    used[u] = true;
    cout<<u << " ";
    for (int v : r_adj[u]) {
        if (!used[v])
        {
            DFS2(v);
        }
    }
}

//Hàm Dùng để đếm các thành phần liên thông mạnh của đồ thị có hướng
void SCC() {
    memset(used, false, sizeof(used));

    //Bước 1: gọi thuật toán DFS trên đồ thị G(Là đồ thị ban đầu)
    cout << "Danh sach sap xep topo: ";
    for (short i = 1; i <= n; i++)
    {
        if (!used[i]) {
            DFS1(i);
        }
    }
    cout << "\n";

    /*Bước 2: ta đã cây dựng đồ thị TG - Transpose Graph tức đồ thị TG là đồ thị lật ngược các cung của đồ thị G(là đồ thị ban đầu)
    lại thôi thì bước 2 này ta đã làm trong lúc nhập các đỉnh của đồ thị ở dòng 43. Xây dựng đồ thị Transpose Graph đơn giản như thế
    này đồ thị G là khi nhập hai đỉnh x và y để tạo thành cạnh của đồ thị thì x nối tới y đồng nghĩa với việc push y và danh sách kề
    của x còn khi xây dựng đồ thị Transpose Graph thì lật ngược cung lại thành y nối tới x đồng nghĩa với việc push x vào danh sách
    kề của y*/

    //Bước 3: Lần lựơt pop các đỉnh trong stack ở bước 1 và gọi thuật toán DFS2 để liệt kê các thành phần liên thông mạnh 
    memset(used, false, sizeof(used));/*Thì sau khi thực hiện Bước 1 các đỉnh của đồ thị G đã dc thăm hết nên khi qua đồ thị TG cũng
    là các đỉnh bên đồ thị G thôi nhưng khác cái là đồ thị TG là đồ thị có cung đảo ngược các cung lại của đồ thị G nên các đỉnh trong
    đồ thị TG lúc này cũng cũng mang giá trị là true(Là đã đc thăm) nên khi thực hiện bước 3 cần phải resest lại giá trị là false(là 
    chưa đc thăm) cho các đỉnh trong đồ thị TG.*/
    int cnt = 0;//Biến đếm số thành phần liên thông mạnh của đồ thị
    cout << "Do thi co cac thanh phan lien thong manh la: \n";
    while (!st.empty())
    {  
        int u = st.top();
        st.pop();
        if (!used[u])
        {   
            cnt++;
            cout << "Thanh phan lien thong manh thu " << cnt << " : ";
            DFS2(u);
            cout << "\n";
        }
    }
}

int main()
{
    inp();
    SCC();
}
#endif // 0

#if 1
#include <iostream>
#include<vector>
#include<stack>
using namespace std;

/*=======CƠ CHẾ THUẬT TOÁN KOSARAJU=============
* Thuật toán Kasaraju áp dụng thuật toán DFS và chỉ cần dùng 2 thuật toán DFS là hoàn thành đc bài toán Thành phần liên thông mạnh của
đồ thị có hướng.(Như ta biết đồ thị liên thông mạnh là đồ thị chỉ có 1 thành phần liên thông mạnh thì đồ thị đó đc gọi là đồ thị liên
thông mạnh vậy để kiểm tra đồ thị có liên thông mạnh hay không ta chỉ cần dùng biến đếm số thành phần liên thông mạnh của đồ thị ở
bước 3 nếu số thành phần liên thông mạnh chỉ có 1 thì đồ thị đó là đồ thị liên thông mạnh tức là hàm DFS2 chỉ đc gọi 1 lần còn đồ 
thị không liên thông mạnh là đồ thị có nhiều hơn 1 số thành phần liên thông mạnh)

- BƯỚC 1: Gọi thuật toán DFS trên đồ thị ban đầu(Là đồ thị G - Graph là đồ thị gốc mà ta vừa nhập vào lúc ban đầu) và lưu thứ tự duyệt
các đỉnh vào 1 stack(stack này là danh sách sắp xếp topo khi áp dụng thuật toán DFS vào sắp xếp topo đỉnh nào đc thăm xong thì sẽ đc đẩy
vào stack này tạo thành sắp xếp topo như ta đã học sắp xếp topo ở file bài 9.ThuatToanSapXepToPo)
_ BƯỚC 2: Xây dựng đồ thị lật ngược đồ thị ban đầu(tức là xây dựng đồ thị TG - Transpose Graph(đồ thị chuyển đổi) đồ thị TG là đồ thị
lật ngược lại cung của đồ thị G(là đồ thị ban đầu) ví dụ ta có đồ thị có hướng G có 1 nối tới 2 nhưng khi xây dựng đồ thị TG thì phải
lật ngược cung của đồ thị G lại thành 2 nối tới 1 tương tự cho đến khi lật ngược hết các cung của đồ G lại thị xây dựng xong đồ thị TG)
- BƯỚC 3: Lần lựơt pop các đỉnh trong stack ở bước 1 và gọi thuật toán DFS để liệt kê các thành phần liên thông mạnh : Strongly connected
componts : SCC

*Cơ chế thuật toán Kosaraju giải thích rất kỹ trong vở cấu trúc dl & giải thuật -> đồ thị 4 nếu quên hãy mở lại xem

Bài toán áp dụng thuật toán Kosaraju: Kiểm tra đồ thị có phải là liên thông mạnh hay không 
Input: chỉ 1 lần nhập ra 2 đồ thị               | Output: với input của bài thì đếm đc 3 thành phần liên thông mạnh
1.là đồ thị G(là đồ thị ban đầu là đồ thị gốc)  |+ thành phần liên thông mạnh thứ 1 : 1 4 3 2
2.là đồ thị TG(là đồ transpose graph là đò thị  |+ thành phần liên thông mạnh thứ 2 : 5
có cung ngược lại của đồ thị G)                 |+ thành phần liên thông mạnh thứ 3 : 6 8 7
Với n đỉnh = 8 là từ 1 tới 8 và m cạnh = 9 là:  |
                  1 2                           |
                  2 3                           |
                  3 4                           |
                  4 1                           |
                  3 5                           |
                  5 6                           |
                  6 7                           |
                  7 8                           |
                  8 6                           |
*/
int n, m;
int topo[20];
vector <int> adj[20], r_adj[20];/*Danh sách adj chứa danh sách kề của các đỉnh của đồ thị G(Graph - đồ thị G là đồ thị gốc), danh sách
r_adj chứa danh sách kề của các đỉnh của đồ thị TG(là đồ thị Transpose graph là đồ thị lật ngược các cung của đồ thị G lại)*/
bool used[20];//Mảng used dùng để đáng dấu các đỉnh là đã đc thăm hay chưa giống mảng visited mà chỉ khác tên 
stack <int> st;//Stack st chứa các đỉnh sắp xếp topo

void inp() {
    cout << "Nhap vao n dinh va m canh cua do thi co huong: \n";
    cin >> n >> m;

    cout << "Nhap vao hai dinh x va y tao thanh canh cua do thi co huong: \n";
    for (short i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        //danh sách adj là danh sách kề của đồ thị G(Draph là đồ thị gốc)
        adj[x].push_back(y);

        /*Bước 2: Xây dựng đồ thị Transpose Graph Lật ngược lại các cung của đồ thị G để hình thành đồ thị TG(Tranpose Graph) và
        đồ thị TG(Transpose Graph) đc lưu vào danh sách r_adj*/
        r_adj[y].push_back(x);
    }
    memset(used, false, sizeof(used));
}

/*Hàm DFS1 dùng để thực hiện bước 1 của thuật toán Kosaraju là gọi tới đồ thị G(Graph - là đô thị ban đầu) để có đc 1 stack topo tức
là có đc danh sách sắp xếp topo các đỉnh của đồ thị G(Graph - là đô thị ban đầu)*/
void DFS1(int u) {
    used[u] = true;
    for (int v : adj[u]) {
        if (!used[v])
        {
            DFS1(v);
        }
    }

    /*Khi duyet xong dinh u. Vì thuật tóa kosaraju ta áp dụng sắp xết topo bằng DFS vào nữa mà sắp xếp topo bằng DFS ta đã học rất kỹ
    là mõi khi 1 đỉnh bất kì của đồ thị đc duyệt xong thì đỉnh đó sẽ dc thêm vào stack topo đỉnh nào càng duyệt xong sớm thì đỉnh đó
    trong danh sách topo có thứ tự càng ở cuối nên ta dùng stack để lưu các đỉnh đc sắp xếp topo là đúng với thứ tự vì cơ chế của
    stack là LIFO - Last in Firt out tức là vào sau ra trước tức đỉnh nào đc duyệt xong cuối cùng là đỉnh nằm ở đầu stack tương đương
    với vị trí đỉnh đc duyệt xong cuối cùng là đứng đầu trong danh sách sắp xếp topo và đỉnh đc duyệt xong đầu tiên là đỉnh có vị trí
    cuối cùng trong danh stack cũng như là danh sách sắp xếp topo tức stack là thêm là thêm ở đầu stack và lấy cũng ở đầu stack tương
    ứng với cơ chế LIFO - Last In Firt Out là vào sau ra trước của stack tức là mõi lần thêm là thêm vào đầu và mõi lần lấy là lấy ở
    đầu luôn.*/
    cout<<u << " ";
    st.push(u);
}

/*Hàm DFS2 dùng để: Mõi lần lấy ra 1 đỉnh ở trong danh sách topo nếu đỉnh đó ở trong đồ thị TG(là đồ thị lật ngược các cung lại của
đồ thị G ,TG là là đồ thị Transpose Graph) mà chưa đc thăm thì sẽ đc truyền vào hàm DFS2 này để thăm các đỉnh trong đồ thị TG(Transpose
Graph) mõi lần gọi DFS2 trên đồ thị TG(Transpose Graph) thì DFS2 sẽ liệt kê các đỉnh thuộc cùng 1 thành phần liên thông mạnh tương
ứng với đỉnh bắt đầu thuật toán DFS2*/
void DFS2(int u) {
    used[u] = true;
    cout << u << " ";
    for (int v : r_adj[u]) {
        if (!used[v])
        {
            DFS2(v);
        }
    }
}

//Hàm Dùng để đếm các thành phần liên thông mạnh của đồ thị có hướng
void SCC() {
    memset(used, false, sizeof(used));

    //Bước 1: gọi thuật toán DFS trên đồ thị G(Là đồ thị ban đầu)
    cout << "Danh sach sap xep topo: ";
    for (short i = 1; i <= n; i++)
    {
        if (!used[i]) {
            DFS1(i);
        }
    }
    cout << "\n";

    /*Bước 2: ta đã cây dựng đồ thị TG - Transpose Graph tức đồ thị TG là đồ thị lật ngược các cung của đồ thị G(là đồ thị ban đầu)
    lại thôi thì bước 2 này ta đã làm trong lúc nhập các đỉnh của đồ thị ở dòng 43. Xây dựng đồ thị Transpose Graph đơn giản như thế
    này đồ thị G là khi nhập hai đỉnh x và y để tạo thành cạnh của đồ thị thì x nối tới y đồng nghĩa với việc push y và danh sách kề
    của x còn khi xây dựng đồ thị Transpose Graph thì lật ngược cung lại thành y nối tới x đồng nghĩa với việc push x vào danh sách
    kề của y*/

    //Bước 3: Lần lựơt pop các đỉnh trong stack ở bước 1 và gọi thuật toán DFS2 để liệt kê các thành phần liên thông mạnh 
    memset(used, false, sizeof(used));/*Thì sau khi thực hiện Bước 1 các đỉnh của đồ thị G đã dc thăm hết nên khi qua đồ thị TG cũng
    là các đỉnh bên đồ thị G thôi nhưng khác cái là đồ thị TG là đồ thị có cung đảo ngược các cung lại của đồ thị G nên các đỉnh trong
    đồ thị TG lúc này cũng cũng mang giá trị là true(Là đã đc thăm) nên khi thực hiện bước 3 cần phải resest lại giá trị là false(là
    chưa đc thăm) cho các đỉnh trong đồ thị TG.*/
    int cnt = 0;//Biến đếm số thành phần liên thông mạnh của đồ thị
    cout << "Do thi co cac thanh phan lien thong manh la: \n";
    while (!st.empty())
    {
        int u = st.top();
        st.pop();
        if (!used[u])
        {   cnt++;
            cout << "Thanh phan lien thong manh thu " << cnt << " : ";
            DFS2(u);
            cout << "\n";
            
        }
    }
    if (cnt == 1)
    {
        cout << "\nDo thi nay la do thi lien thong manh !\n";
    }
    else
    {
        cout << "\nDo thi nay khong la do thi lien thong manh !\n";
    }
}
int main()
{
        inp();
        SCC();
       
}

//Đây là hàm dùng biến t là biến để xét các trường hợp của đồ thị hay nói cách khác là nhập vào t đồ thị và xét t đồ thị mõi lần xét
// 1 đồ thị mới thì khi nhập inp(); và xét xong cần phải xóa hết dữ liệu dữ liệu vừa xét vào để nhập và xét đồ thị mới. 
//int main()
//{
//    int t;
//    cin >> t;
//    while (t--)
//    {
//        inp();
//       SCC();
//       for (short i = 1; i <= n; i++)
//       {
//           adj[i].clear();
//           r_adj[i].clear();
//       }
//    }
//}
#endif // 1


