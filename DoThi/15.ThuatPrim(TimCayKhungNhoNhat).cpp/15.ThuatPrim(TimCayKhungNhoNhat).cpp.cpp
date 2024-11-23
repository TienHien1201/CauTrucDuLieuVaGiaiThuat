/*========================== THUẬT PRIM - TÌM CÂY KHUNG NHỎ NHẤT  CHƯA TỐI ƯU==================================*/
#if 0
#include <iostream>
#include<vector>
using namespace std;
/*========================== THUẬT PRIM - TÌM CÂY KHUNG NHỎ NHẤT ==================================
Phần cơ chế và các bước của PRIM đã giải thích rất rõ trong vở đồ thị 4 bài 18 nếu quên vào mở lại xem.

Bài toán tìm cây khung nhỏ nhất
input: n là số đỉnh = 6 từ 1 đến 6 | output : với input thì khung cực tiều MST là
và m là số cạnh = 8 gồm 8 cạnh và  | 3 1 : 4
trọng số của mõi cạnh              | 2 3 : 1
      1 2 : 9                      | 5 3 : 2  
      1 3 : 4                      | 4 5 : 3
      2 3 : 1                      | 6 5 : 8
      2 4 : 6                      | và tổng trọng số của khung cực tiểu MST là d = 18
      3 5 : 2                      |
      4 5 : 3                      |
      4 6 : 10                     |
      5 6 : 8                      |
*/

const int maxn = 20;/*sử dụng để định rõ một giá trị cố định trong chương trình, giúp dễ dàng quản lý và thay đổi giá trị đó mà không
cần phải tìm và sửa tất cả các vị trí sử dụng giá trị đó trong code*/
int n, m;//n là số đỉnh, m là số cạnh
vector<pair<int, int>> adj[maxn];//Vector chứa cạnh(tức <pair<int, int>>) và trọng số(adj[maxn]) của cạnh
bool used[maxn];/* Mảng dùng để đánh dấu một đỉnh bất kì đã đc đưa vào cây khung hay chưa tức là đánh dấu 1 đỉnh thuộc tập V(đỉnh) hay 
thuộc tập V(MST) bằng cách: 
- Ban đầu tất cả các đỉnh i đều là false hết vì nó thuộc tập V(đỉnh) sau đó
+ Nếu used[i] = true thì i thuộc tập V(MST) tức là đc đc đưa vào cây khung cực tiều 
+ Nếu used[i] = false thì i thuộc tập V(đỉnh) tức là i chưa đc thêm vào cây khung cực tiểu*/

/*Khởi tạo cạnh của đồ đồ thị để lưu các cạnh của cây khung nếu đề bài yêu chỉ cầu in ra trọng số của cây khung cực tiểu thì không cần
struct này*/
struct egde
{
    int x, y, w;
};

void inp() {
    cout << "Nhap vao n dinh va m canh cua do thi vo huong: \n";
    cin >> n >> m;

    cout << "Nhap vao hai dinh x va y tao thanh canh va trong so cua canh trong do thi vo huong: \n";
    for (short i = 0; i < m; i++)
    {
        int x, y, w;
        cin >> x >> y >> w;
        adj[x].push_back({y, w });
        adj[y].push_back({ x, w });
    }
    memset(used, false, sizeof(used));

}

void Prim(int u) {
    //Bước 1: Khởi tạo
    vector<egde> MST;//Cây khung rỗng hay còn gọi là cây khung cực tiểu mà ta muốn tìm
    int d = 0;//Tổng trọng số của cây khung rỗng hay còn gọi là cây khung cực tiểu mà ta muốn tìm
    used[u] = true;/*cho đỉnh u vào tập V(MST) tức là tập chứa các đỉnh của cây khung cực tiểu để đánh dấu là đỉnh u này trong tập
    V(đỉnh) đã đc thăm hay hiểu đơn giản là chuyển đỉnh từ tập V(đỉnh) sang tập V(MST)*/

    //Bước 2: Lặp
    while (MST.size() < n - 1){/*Ta có thể check điều kiện với hình thức giống trong vở đồ thị 4 bài 18 là V(đỉnh) != rỗng bằng các xet
        xem các đỉnh trong mảng used có true hết chưa nếu true hết thì đã rỗng. Còn không tạo điều kiện dừng cho vòng while này bằng
        cách kiểm xem khi nào cây khung cực tiểu của ta có số lượng cạnh là n - 1 tức đã xây dựng xong cây khung thì dừng vì vòng for
        xét cạnh chạy từ 0 đến m tức có 6 cạnh thì chạy từ 0 đến 5 là đủ 6 cạnh nên khung cây rỗng chỉ cần xét đủ n - 1 cạnh tức xét
        đủ cạnh thì dừng. 2 đk dừng có ý nghĩa như nhau chỉ khác hình thức.*/

        /*Chọn cạnh e là cạnh ngắn nhất trong đó cạnh e này phải có đỉnh x thuộc tập V(đỉnh) và y thuộc tập V(MST)*/
        int min_w = INT_MAX;//Biến lưu cạnh có trọng số nhỏ nhất
    int X, Y;//Lưu 2 đỉnh của cạnh e trong đó cạnh e này phải có đỉnh x thuộc tập V(đỉnh) và y thuộc tập V(MST)
    for (short i = 1; i <= n; i++)//Duyệt tất cả các đỉnh của đồ thị
    {
        //Nếu đỉnh i thuộc tập V(MST) => Tức nếu i mà là true thì đã thuộc tập V(MST) là tập của cây khung cực tiểu
        if (used[i])
        {
            /*Duyệt danh sách kề của i(là đỉnh y tức là đỉnh thuộc tập V(MST) và lấy ra những đỉnh kề vs nó thuộc tập V(đỉnh) tức là tập
            chưa thuộc cây khung cực tiểu để tìm ra đỉnh kề với i trong tập V(đỉnh)(là đỉnh x) tạo thành cạnh có độ dài ngắn nhất.*/
            for (pair<int, int> it : adj[i]) {/*Vì cạnh nên biến pair của danh sách cạnh có 2 đỉnh tạo thành cạnh và trọng số của 2
                đỉnh tạo thành cạnh tương ứng với 2 phần tử là firt là đỉnh kề với đỉnh i tạo thành cạnh và second là trọng số */
                int j = it.first, TrongSo = it.second;
                if (!used[j] && TrongSo < min_w) {/*Đỉnh j là đỉnh kề với đỉnh i và nếu j mà chưa đc thăm tức là đỉnh j là đỉnh thuộc tập V(đỉnh) vì chọn
                    cạnh e là cạnh ngắn nhất trong đó cạnh e này phải có đỉnh x thuộc tập V(đỉnh) là đỉnh j và y thuộc tập V(MST) thì
                    đỉnh i là đỉnh x và cạnh i j này có trọng số nhỏ hơn kỷ lục */

                    min_w = TrongSo;//Cập nhật lại cạnh ngắn nhất 

                    X = j; Y = i;  //lưu lại hai đỉnh đầu và cuối của cạnh có độ dài ngắn nhất tức cạnh ngắn nhất bây giờ là X và Y
                }
            }
        }
    }
    //Cho cạnh có độ dài ngắn nhất của mõi lần while duyệt vào khung cây cực tiểu 
    MST.push_back({ X, Y, min_w });

    //Cộng độ dài của cạnh có đồ dài ngắn nhất của mõi lần duyệt vào tổng trọng số của cây khung cực tiểu
    d += min_w;

    /*Cho đỉnh X vào tập đỉnh của cây khung cực tiểu V(MST) đồng thời khi cho X vào tập đỉnh của cây khung cực tiểu V(MST) bằng cách
    cập nhật cho đỉnh X này là true thì đỉnh X này cũng đã k còn nằm trong tập V(đỉnh) nữa vì ta đã dùng mảng used kiểu bool để đánh
    dấu đỉnh chưa đc thăm(false) là đỉnh thuộc tập V(đỉnh) còn đỉnh mà đã đc thăm(true) là đỉnh thuộc tập V(MST)*/
    used[X] = true;
}
    cout << "Tong trong so cua cay khung cuc tieu vua tim: \n";
    cout << d << "\n";
    cout << "Cay khung cuc tieu la: \n";
    for (egde e : MST) {
        cout << e.x << " " <<e.y<<" : " <<e.w<<"\n";
    }
}

int main()
{
    inp();
    Prim(1);
}
#endif // 0

/*========================== THUẬT PRIM - TÌM CÂY KHUNG NHỎ NHẤT TỐI ƯU BẰNG HÀNG ĐỢI ƯU TIÊN ==================================*/
#include <iostream>
#include<vector>
#include<queue>
using namespace std;

/*Bài toán tìm cây khung nhỏ nhất
input: n là số đỉnh = 6 từ 1 đến 6 | output : với input thì khung cực tiều MST là
và m là số cạnh = 8 gồm 8 cạnh và  | 3 1 : 4
trọng số của mõi cạnh              | 2 3 : 1
      1 2 : 9                      | 5 3 : 2
      1 3 : 4                      | 4 5 : 3
      2 3 : 1                      | 6 5 : 8
      2 4 : 6                      | và tổng trọng số của khung cực tiểu MST là d = 18
      3 5 : 2                      |
      4 5 : 3                      |
      4 6 : 10                     |
      5 6 : 8                      |
*/

const int maxn = 20;/*sử dụng để định rõ một giá trị cố định trong chương trình, giúp dễ dàng quản lý và thay đổi giá trị đó mà không
cần phải tìm và sửa tất cả các vị trí sử dụng giá trị đó trong code*/
int n, m;//n là số đỉnh, m là số cạnh
vector<pair<int, int>> adj[maxn];//Vector chứa cạnh(tức <pair<int, int>>) và trọng số(adj[maxn]) của cạnh
bool used[maxn];/* Mảng dùng để đánh dấu một đỉnh bất kì đã đc đưa vào cây khung hay chưa tức là đánh dấu 1 đỉnh thuộc tập V(đỉnh) hay
thuộc tập V(MST) bằng cách:
- Ban đầu tất cả các đỉnh i đều là false hết vì nó thuộc tập V(đỉnh) sau đó
+ Nếu used[i] = true thì i thuộc tập V(MST) tức là đc đc đưa vào cây khung cực tiều
+ Nếu used[i] = false thì i thuộc tập V(đỉnh) tức là i chưa đc thêm vào cây khung cực tiểu*/
int parent[maxn],d[maxn];//Dùng để truy vết các cạnh đc đưa vào cây khung cực tiểu

/*Khởi tạo cạnh của đồ đồ thị để lưu các cạnh của cây khung nếu đề bài yêu chỉ cầu in ra trọng số của cây khung cực tiểu thì không cần
struct này*/
struct egde
{
    int x, y, w;
};

void inp() {
    cout << "Nhap vao n dinh va m canh cua do thi vo huong: \n";
    cin >> n >> m;

    cout << "Nhap vao hai dinh x va y tao thanh canh va trong so cua canh trong do thi vo huong: \n";
    for (short i = 0; i < m; i++)
    {
        int x, y, w;
        cin >> x >> y >> w;
        adj[x].push_back({ y, w });
        adj[y].push_back({ x, w });
    }
    memset(used, false, sizeof(used));
    for (short i = 1; i <= n; i++)
    d[i] = INT_MAX;/*Mục đích của việc khởi tạo d với INT_MAX là thiết lập mọi giá trị(tức lúc bắt đầu với mõi đỉnh có trọng số là rất
    lớn) trong mảng d ban đầu là một giá trị rất lớn để đại diện cho việc không có đường đi nào từ đỉnh xuất phát tới các đỉnh còn lại.
    Sau khi thuật toán tìm đường đi chạy, các giá trị trong mảng d sẽ được cập nhật với các khoảng cách tối ưu từ đỉnh xuất phát tới
    các đỉnh khác.*/
}

/*Phần cơ chế của tối thuật toán Prim - Tìm cây khung nhỏ nhất bằng hàng đợi ưu tiên là dùng hàng đợi ưu tiên để lưu 2 cặp đỉnh x thuộc
tập v(đỉnh) và y thuộc v(MST) của cạnh ngắn nhất thì mõi cặp này thứ nhất là x thì lưu trọng số, thứ 2 là lưu đỉnh = > Tức mõi
lần vào bước lặp khi tìm cạnh có độ dài nhỏ nhất thì x là đỉnh thuộc tập V(đỉnh) cùng với trọng số của đỉnh x sẽ là cặp thứ nhất đc
đẩy vào hàng đợi ưu tiên và y là đỉnh thuộc tập V(MST) và trọng số của y là cặp thứ 2 trong hàng đợi ưu tiên tương tự như thuật toán
Prim không tối ưu là lấy đỉnh x trong tập V(đỉnh) cũng với trọng số của x xét xem đỉnh y là đỉnh thuộc tập V(MST) nào mà kề với x có
trọng số nhỏ nhất thì đó là cạnh có độ dài ngắn nhất. Hay nói 1 cách dễ hiểu hơn vì như đã giải thích ở trên là thuật toán Prim dùng 
hàng đợi ưu tiên để tối ưu mà với mõi phần tử của hàng đợi ưu tiên này là trọng số trước rồi mới tới đỉnh thuộc tập v(đỉnh) kề với đỉnh
thuộc tập v(MST) tức 1 cặp này là một phần tử trong hàng đợi sau khi chọn đc phần tử có trọng số nhỏ nhất trong hàng đợi thì phần tử đó
cũng bị loại ra khỏi hàng đợi ưu tiên vì phần tử của hàng đợi gồm 2 phần là trọng số và đỉnh thuộc tập v(đỉnh) kề với đỉnh thuộc tập 
v(MST) nên khi lấy 1 phần tử có trọng số nhỏ nhất ra thì nó lại xét xem đỉnh vừa đc lấy ra
Ví dụ : ta có đồ thị n là số đỉnh = 6 từ 1 đến 6 và m là số cạnh = 8 gồm 8 cạnh và trọng số của mõi cạnh              
      1 2 : 9                      
      1 3 : 4                      
      2 3 : 1                     
      2 4 : 6                     
      3 5 : 2                      
      4 5 : 3                      
      4 6 : 10                     
      5 6 : 8     
 và tập đỉnh v(đỉnh) = {1,2,3,4,5,6} và tập các đỉnh của khung cây cực tiểu v(MST) = {} rỗng
< ->Ban đầu ta truyền đỉnh 1 vào hàm Prim thì hàng đợi ưu tiên lúc này chỉ có 1 phần tử là đỉnh 1 thì nó tiến hành lấy đỉnh ở đầu
    hàng đợi là đỉnh 1 ra cũng với trọng số của 1 lúc đầu là 0 vì đỉnh 1 lúc này chưa kề với đỉnh nào nên có trọng số là 0 tức cặp đầu
    tiên(theo thứ tự trọng số của đỉnh trước sau đó là đỉnh) của hàng đợi là { 0, 1 } tứ mõi cặp trong hàng đợi ưu tiên thì mang giá trị trọng
    số của đỉnh trước tức là 0 rồi mới tới đỉnh là 1 vì hàng đợi ưu tiên sắp xếp theo trọng số nên phải đưa trọng số lên trước rồi mới tới
    đỉnh.Khi chọn cạnh ngắn nhất thì cạnh phải có 2 đỉnh 1 đỉnh thuộc tập V(đỉnh) là x và 1 đỉnh thuộc tập V(MST) là y thì 1 lúc này là y
    tức trong lần đầu tiên truyền đỉnh bất kì vào hàm Prim thì ta tạo ra khung cây cực tiểu và thêm đỉnh vừa truyền vào Prim vào tập V(MST)
    luôn
    Sau đó vào vòng lặp while xét thấy hàng đợi ưu tiên khác rỗng
    ->Nên lấy cặp ở đầu hàng đợi là cặp(0, 1) tức là đỉnh 1 tức là đỉnh y thuộc tập V(MST) còn 0 là trọng số của 1 xét xem có kề với đỉnh
    nào trong tập V(đỉnh) không nếu có thì xem 1 kề với đỉnh nào trong tập V(đỉnh) có độ dài ngắn nhất thì trong tập V(đỉnh) lúc này có 2
    đỉnh kề với 1 là đỉnh 2 và đỉnh 3 tức có 2 cạnh để xét độ dài là cạnh(1, 2) và(1, 3) xem 1 trong 2 cạnh(1, 2) và(1, 3) cạnh nào có độ
    dài ngắn hơn để thêm vào cây khung cực tiểu thì prim tối ưu này sẽ đẩy 2 cặp vào hàng đợi ưu tiên là :
*Cặp thứ nhất là(9, 2) với 9 là trọng số của đỉnh 1 nối tới 2 tức cạnh(1, 2) còn 2 là đỉnh thuộc tập V(đỉnh)
* Cặp thứ hai là(4, 3) với 4 là trọng số của đỉnh 1 nối tới 3 tức cạnh(1, 3) còn 3 là đỉnh thuộc tập V(đỉnh)
khi này hàng đợi của ta sẽ có 2 cặp là
queue = { (9,2) và(4,3) }

Sau đó vòng while lại xét hàng đợi ưu tiên có khác rỗng không nếu có phần tử thì lấy phần tử ở đầu hàng đợi ra tức là cặp trọng số
và đỉnh mà đỉnh đã đc thêm vào hàng đợi là đỉnh thuộc tập V(Đỉnh) để lấy ra cặp có trọng số là nhỏ nhất ra khỏi hàng đợi mà trong hàng
đợi của ta có hai cặp(9, 2) và(4, 3) thì cặp có trọng số nhỏ nhất lúc này là cặp(4, 3)
->sau đó thêm đỉnh thuộc tập V(đỉnh) là đỉnh 3 vào cặp V(MST) mà tập V(MST) ban đầu khi truyền đỉnh 1 vào hàm Prim thì đỉnh 1 đã đc
thêm vào tập các đỉnh của khung cây cực tiểu(V(MST)) rồi nên đỉnh 1 cũng đã bị xóa khỏi tập V(Đỉnh) và đồng thời cũng xóa đỉnh 3 ra
khỏi tập v(đỉnh) nên tập V(MST) của ta lúc này có 2 đỉnh là V(MST) = { 1,3 } và tập v(đỉnh) lúc này V(đỉnh) = { 2,4,5,6 } và khung cực tiểu
lúc này : MST 1 3 : 4
< ->Tiếp tục sau khi thêm 3 vào tập các đỉnh của khung cực tiểu(V(MST)) thì while lại xét danh sách kề của đỉnh 3 xem có kề với đỉnh nào
    trong tập V(Đỉnh) hay không nếu có thì thêm trọng số cùng với đỉnh đó khi nối với đỉnh 3 vào hàng đợi ưu tiên để xét xem cặp trọng số
    và đỉnh nào trong hàng đợi ưu tiên có trọng số là ngắn nhất
    ->lúc này đỉnh 3 là đỉnh thuộc V(MST) kề với các đỉnh trong tập V(Đỉnh) là 2 và 5 nên đẩy 2 cặp trọng số của 2 đỉnh và hàng đợi là :
*Cặp thứ nhất(2, 5) tức trọng số là 2 và 5 là đỉnh = > Nghĩa là 3 nối với 5 có trọng số là 2 tức cạnh(3, 5) = 2
* Cặp thứ hai(1, 2) tức trọng số là 1 và 5 là đỉnh = > Nghĩa là 3 nối với 2 có trọng số là 1 tức cạnh(3, 2) = 1
->Khi lấy phần tử trong hàng đợi là cặp(4, 3) tức trọng số của 3 là 4 và đỉnh 3 tức là lấy đỉnh thuộc tập V(MST) là đỉnh 3 ra mà trong
hàng đợi mõi 1 phần tử là 1 cặp là trọng số của đỉnh và đỉnh nên cặp(4, 3) cũng bị loại ra khỏi hàng đợi.Thì hàng đợi của ta lúc này :
queue: {(2, 5); (1, 2)}

< ->Sau đó vào vòng lặp while để xét hàng đợi xem có còn phần tử không thì hàng đợi lúc này còn nên
    ->Lấy phần tử hay gọi là cặp tức là đỉnh có trọng số ngắn nhất thì cặp có độ dài ngắn nhất trong hàng đợi lúc này là cặp(1, 2) tức 1
    là trọng số còn 2 là đỉnh đồng thời hàng đợi queue lúc này cặp(1, 2) cũng bị xóa ra khỏi hàng đợi nên hàng đợi lúc này :
queue: {(2, 5)}
-> Và xét xem đỉnh 2 này có thuộc tập V(MST) chưa nếu 2 đã thuộc tập V(MST) thì loại bỏ đỉnh 2 ra khỏi tập V(đỉnh) còn chưa thì thêm 2
vào tập V(MST).Thì đỉnh 2 lúc này đang còn thuộc tập V(đỉnh) nên thêm đỉnh 2 vào tập V(MST) đồng thời cũng loại đỉnh 2 ra khỏi tập đỉnh
V(đỉnh) luôn nên tập V(MST) của ta lúc này có 3 đỉnh là V(MST) = { 1,3,2 } và tập v(đỉnh) lúc này V(đỉnh) = { 4,5,6 } và khung cực tiểu
lúc này : MST 1 3 : 4
3 2 : 1
Sau đó lại đó lại duyệt danh sách kề của 2 tức 2 là đỉnh thuộc tập V(MST) tức là y xem có kề với đỉnh nào trong tập V(đỉnh) tức là x
không nếu có thì đẩy cặp là trọng số của 2 cùng với đỉnh kề với 2 trong tập V(đỉnh) vào hàng đợi ưu tiên thì
* Đỉnh 2 chỉ kề với đỉnh trong tập V(đỉnh) là đỉnh 4 mà trọng số của 2 nối với 4 là bằng 6 nên đẩy cặp là trọng số của 2 cùng với đỉnh
kề với 2 trong tập V(đỉnh) vào hàng đợi ưu tiên là(6, 4) tức 6 là trọng số của 2 nối với 4 còn 4 là đỉnh kề với đỉnh 2 tức cạnh(2, 4) =
6 nên lúc này cặp(6, 4) đc đẩy vào hàng đợi ưu tiên và hàng đợi của ta lúc này :
queue: {(2, 5), (9, 2), (6, 4)}
->Thì nó lấy phần tử tức là cặp trong hàng đợi có trọng số nhỏ nhất là cặp(2, 5) tức 2 là trọng số của đỉnh 3 nối với đỉnh 5 còn 2 là
đỉnh thuộc tập V(đỉnh) kề với đỉnh 3(đỉnh 3 là đỉnh thuộc tập v(MST))
->Chọn đc cạnh có độ dài ngắn nhất là(3, 5) = 2 rồi
->Thì thêm đỉnh 5 vào tập khung cây cực tiểu(tức là v(MST))
->Loại đỉnh 5 ra khỏi tập V(đỉnh)
->Đồng thời cộng trọng số của cặp(2, 5) là 2 vào tổng trọng số của khung cây cực tiểu thì đỉnh 5 bây giờ là đỉnh thuộc tập v(MST)
->Và xét đỉnh 5 xem có kề với đỉnh nào trong tập v(đỉnh) không nếu có thì đẩy trọng số cùng với đỉnh kề với đỉnh 5 trong tập v(đỉnh)vào
hàng đợi.thì khi lấy cặp có trọng số nhỏ nhất là(2, 5) tức đỉnh 5 và trọng số của đỉnh 5 nối với đỉnh 3 là 2 tức cặp(2, 5) trong hàng
đợi ra khỏi hàng đợi thì hàng đợi, tập V(đỉnh), tập v(MTS) của ta lúc này :
queue = { (9,2); (6,4) }, v(đỉnh) = { 4,6 }, v(MST) = { 1,3,2,5 }
Thì trong tập v(đỉnh) lúc này còn 2 đỉnh 4 và 6 xét thấy đỉnh 5 là đỉnh thuộc tập v(MST) đều kề với cả hai đỉnh còn lại trong tập
v(đỉnh) là đỉnh 4 và đỉnh 6 luôn nên đẩy cặp trọng số cùng với đỉnh kề với đỉnh 5 vào hàng đợi là
* cặp đầu tiên là{ 3,4 } tức 3 là trọng số của 5 nối với 4 còn 4 là đỉnh kề với 5 = > bản chất là cạnh(5, 4) = 3
* cặp thứ hai là{ 8,6 } tức 8 là trọng số của 5 nối với 6 còn 6 là đỉnh kề với 5 = > bản chất là cạnh(5, 6) = 8
Thì hàng đợi của ta lúc này :
queue = { (9,2); (6,4); {3,4}; {8,6} },
-> Sau đó nó lại chọn ta phần tử nào trong hàng đợi có giá trị top nhỏ nhất tức là giá trị đầu tiên tức là trọng số nhỏ nhất ra khỏi
khỏi hàng đợi thì lúc này phần tử trong hàng đợi có trọng số nhỏ nhất lúc này là 3 tức cặp(3, 4)*/
void Prim(int u) {

    priority_queue<pair<int, int>, vector<pair<int, int>> , greater<pair<int, int>>> Q;/*Đây là hàng đợi ưu tiên hay còn gọi là minhead
    tức là phần tử đầu tiên trong hàng đợi lúc nào cũng phần tử mà nó có phần firt là nhỏ nhất*/
    vector<egde> MST;//Khung cây rỗng hay còn gọi là cây khung cực tiểu
    int res = 0;//Đây là chiều dài của cây khung cực tiểu
    Q.push({ 0,u });/*Khi mà đẩy cặp {0,u} vào thì trọng số nhỏ nhất bởi vì hàng đợi ưu tiên này luôn chọn ra phần tử có trọng số là
    nhỏ nhất khi này trọng số đi kèm với đỉnh u là 0 nên 0 là nhỏ nhất nên khi truyền bất cứ đỉnh nào vào hàm Prim thì đỉnh ban đầu
    là đỉnh chưa có đỉnh nào kề với nó nên không có trọng số nên trọng số là 0 tức đỉnh truyền vào hàm Prim này đầu tiên thì đỉnh đó
    là đỉnh có trọng số là nhỏ nhất. Nhưng ta có thể để giá trị của trọng số của đỉnh u là gì cũng đc trong lần đầu tiên này vì khi 
    mới truyền 1 đỉnh vào thì hàng đợi ưu tiên chỉ có duy nhất 1 đỉnh mới truyền vào nên đỉnh này cùng với giá trị trọng số của đỉnh
    trong lần đầu tiên này là nhỏ nhất.*/

    while (!Q.empty())//Nếu hàng đợi ưu tiên mà chưa rỗng tức hàng đợi ưu tiên mà còn phần tử tương đương với còn cạnh để xét
    {
        pair<int, int> top = Q.top();/*top là biến truy cập tới phần tử đầu tiên trong hàng đơi ưu tiên tức hàng đợi ưu tiên là hàng
        đợi luôn có phần tử mà có phần firt tức là phần trọng số là nhỏ nhất vì ta đã tạo ra hàng đợi ưu tiên với là mõi pair kiểu int
        int( tức là 1 cặp int đầu tiên là phần firt của phần tử pair trong hàng đợi ưu tiên tức là trọng số còn int thứ 2 là phần second
        của phần tử pair trong hàng đợi ưu tiên tức là đỉnh) là mõi phần tử của hàng đợi ưu tiên */
        Q.pop();

        int trongSo = top.first;//Biến trongSo là biến lưu phần trọng số của phần tử pair trong hàng đợi ưu tiên
        int dinh = top.second;//Biến dinh là biến lưu phần đỉnh của phần tử pair trong hàng đợi ưu tiên
        if (used[dinh]){/*Nếu đỉnh mà có trọng số nhỏ nhất trong hàng đợi ưu tiên mà là true tức đã đc thăm thì như thuật Prim chưa tối
            ưu ở bên trên để phần biệt các đỉnh thuộc tập v(đỉnh) hay tập v(MST) thì đỉnh nào đã đc thăm thì đỉnh đó đã đc thêm vào
            khung cây cực tiểu tức là tập các đỉnh của khung cây cực tiểu v(MST) còn đỉnh nào mà chưa đc thăm thì đỉnh đó vẫn còn nằm
            ở tập v(đỉnh) thì ở thuật tối Prim dùng hàng đợi ưu tiên để tối ưu cũng y chang. Tóm lại nếu đỉnh vừa đc lấy ra ở đầu hàng
            đợi tức là đỉnh có trọng số nhỏ nhất vừa đc lấy ra ở đầu hàng đợi mà đã đc thăm tức đã nằm trong tập v(MST) tức là tập các
            đỉnh của khung cây cực tiểu tức là đã nằm trong khung cây cực tiểu thì*/
            continue;/*dừng lại không xét đỉnh đó nữa vì khi check các đỉnh có trọng số nhỏ nhất trong hàng đợi ưu tiên thì sẽ có lúc
            gặp lại 1 đỉnh mà nó lại có trọng số nhỏ nhất trong hàng đợi ưu tiên ví dụ ta trong hàng đợi ưu tiên có 3 cặp tức là mõi
            cặp gồm trọng số và đỉnh của trọng số như phần ví dụ của phần giải thích cơ chế thuật Prim tối ưu bằng hàng đợi ưu tiên ở
            trên đầu hàm Prim này là {(9,2);(6,4);(3,4)} thì khi này cặp trọng số và đỉnh có trọng số ngắn nhất là cặp (3 4) thì cặp
            (3,4) đc lấy ra khỏi hàng đợi và đỉnh 4 đc đánh dấu là đã đc thăm tức đỉnh 4 đã đc thêm vào tập V(MST) sau đó hàng đợi lúc
            này còn hai cặp là {(9,2);(6,4)} thì cặp có trọng số ngắn nhất lúc này lại là cặp (6,4) tức là đỉnh 4 và trọng số là 6 thì
            lúc này đỉnh 4 đã đc thăm tức đã đc thêm vào tập v(MST) là cặp (3,4) tức là cũng là 1 đỉnh khác nối với đỉnh 4 nhưng đỉnh
            nối với đỉnh 4 có trọng số là 3 ngắn hơn đỉnh nối với đỉnh 4 có trọng số là 6 vì hàng đợi ưu tiên có cơ chế các cặp nào mà
            có phần tử firt nhỏ nhất sẽ đứng ở đầu hàng đợi ưu tiên và tăng dần cho đến cuối hàng đợi.Vì vậy dòng if (used[dinh]) này
            có tác dụng là như vậy nếu đỉnh nào mà đã đc thăm tức là đã đc thêm vào tập khung cây cực tiểu rồi thị bỏ qua không xét
            để k thêm vào cây khung cực tiểu nữa.*/
    }
            res += trongSo;//Cộng trọng số của đỉnh trong hàng đợi có trọng số là nhỏ nhất vào tổng trọng số của khung cây cực tiểu
            used[dinh] = true;/*Thêm đỉnh vào tập các đỉnh của cây khung cực tiểu tức là tập v(MST) nghĩa là thêm vào trong cây khung 
            cực tiểu*/
            if (u != dinh) {/*Để duy trì tập cạnh của cây khung tức là lưu các cạnh của cây khung cực tiểu. Để lưu các cạnh ta phải 
                tránh trường hợp của lần đầu tiên truyền đỉnh u vào vì khi bắt đầu thuật toán Prim bằng 1 đỉnh u thì đỉnh u trong lần
                đầu tiên truyền vào hàm Prim sẽ không có đỉnh nào nối tới đỉnh u tức là u không có cha nên phải xét trường hợp này để
                tránh truyền cạnh không nằm trong đồ thị vào cây khung cực tiểu. ví dụ ban đầu ta truyền đỉnh 1 vào hàm prim thì đỉnh
                1 này ban đầu chưa có đỉnh nào nối tới 1 cả tức cha của đỉnh 1 ban đầu là 0 thì để tránh trường thêm cạnh (0,1) vào
                cây khung cực tiểu thì ta phảo có đk này vì trong đồ thị không tồn tại cạnh (0,1)*/
                MST.push_back({ dinh, parent[dinh], trongSo });
               
            }
            /*Duyệt danh sách kề của đỉnh có trọng số nhỏ nhất vừa đc lấy ra khỏi hàng đợi ưu tiên tức dinh là đỉnh thuộc tập V(MST)
            rồi và lấy đỉnh này xét xem trong tập v(đỉnh) có đỉnh nào kề với đỉnh có trọng số nhỏ nhất vừa đc lấy ra khỏi hàng đợi ưu
            tiên không */
            for (auto it : adj[dinh]) {

                int y = it.first;/*Đỉnh y(là đỉnh kề với dinh thuộc tập v(đỉnh)) là đỉnh kề với đỉnh dinh(tức là đỉnh có trọng số nhỏ 
                nhất vừa đc lấy ra khỏi hàng đợi ưu tiên )*/
                int w = it.second;
                if (!used[y] && w < d[y]){/*Xét xem đỉnh y này đã nằm trong cây khung hay chưa và trọng số của đỉnh kề với đỉnh có trọng
                    số nhỏ nhất vừa đc lấy ra khỏi hàng đợi ưu tiên có nhỏ hơn đỉnh có trọng số nhỏ nhất vừa đc lấy ra khỏi hàng đợi ưu
                    tiên hay không. Tức mảng d dùng để lưu trọng số của đỉnh nào mà kề với đỉnh có trọng số nhỏ nhất vừa đc lấy ra khỏi
                    hàng đợi ưu tiên, nếu ta không lưu lại cây khung thì ta không cần xét đk w < d[y] mà chỉ cần xét đỉnh y đã nằm trong
                    tập các đỉnh của cây khung hay chưa là đc*/
                    Q.push({ w,y });/*Thêm trọng số của đỉnh y cùng với đỉnh y( là đỉnh thuộc tập v(đỉnh) kề với đỉnh có trọng số nhỏ
                    nhất vừa đc lấy ra khỏi hàng đợi ưu tiên) vào hàng đợi ưu tiên   */
                    d[y] = w;/*Cập nhật lại trọng số của đỉnh kề với đỉnh dinh(là đỉnh có trọng số nhỏ nhất vừa đc lấy ra khỏi hàng đợi
                    ưu tiên ) là trọng số của đỉnh kề với đỉnh(có trọng số nhỏ nhất vừa đc lấy ra khỏi hàng đợi ưu tiên ) mà có trọng 
                    số là nhỏ nhất, vì ban đầu ta khởi tạo mảng d với để chứa các đỉnh có trọng số là lớn nhất tức giống thuật Dijkstra 
                    đã học môn toán rời rạc mõi ban đầu là mõi đỉnh có giá trị là vô hạn mõi khi đỉnh nào đc xét có độ dài nhỏ hơn sẽ
                    cập nhật lại độ dài cho đỉnh đó là độ dài nhỏ hơn vô hạn tức đã có đường đi từ 1 đỉnh nào đó tới dỉnh y này */
                    parent[y] = dinh;/*Đánh dấu cha của đỉnh kề với đỉnh dinh(là đỉnh có trọng số nhỏ nhất vừa đc lấy ra khỏi hàng
                    đợi ưu tiên) là đỉnh dinh(là đỉnh có trọng số nhỏ nhất vừa đc lấy ra khỏi hàng đợi ưu tiên) giống thuật Dijkstra 
                    đã học môn toán rời rạc phải đánh dấu đỉnh cha của đỉnh vừa đc đỉnh khác mở rộng ra duyệt để truy vết lại khung 
                    cây cực tiểu*/
                }
            }   
      }
    cout << "Tong trong so cua cay khung cuc tieu vua tim: \n";
    cout << res << "\n";
    cout << "Cay khung cuc tieu la: \n";
    for (auto it : MST) {

        cout << it.x << " " << it.y << " : " << it.w<<"\n";
    }
}

int main() {
    inp();
    Prim(1);
}
