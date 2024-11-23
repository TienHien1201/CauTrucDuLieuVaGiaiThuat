#if 0
#include <iostream>
#include<vector>
#include<queue>
using namespace std;
/*Áp dụng thuật toán DFS và BFS trên lưới ô vuông:
Bài 1: Đếm số thành phần liên thông trên lưới.
input: nhập vào n hàng = 6 và m cột = 6 của lưới | Output: Số thành phần liên thông của đồ thị trong lưới ô vuông
ô vuông                                          |
           1 2 3 4 5 6                           |
         1 x x x o o o                           |
         2 o o x o o o                           |
         3 o x x x x o                           |
         4 o o o o o x                           |
         5 x x o x o x                           |
         6 x o x x o x                           |*/

int n, m;
bool visited[20][20];//Mảng chứa các cặp đỉnh chưa đc thăm và đc thăm của đồ thị trong lưới ô vuông - hay còn gọi là ma trận kề
char a[20][20];/*Mảng char để lưu lưới ô vuông ký tự ký tự 2 chiều hay còn gọi là ma trận ký tự. thay vì bình thường ta tạo ra 1 ma trận
kề với kiểu int chứa kiểu số nguyên thì ở đây thay kiểu int bằng char để lưu ma trận dạnh ký tự.*/
int dx[4] = {-1, 0, 0, 1};//Mảng dx là mảng chứa độ di chuyển của đỉnh i để từ ô i,j 
int dy[4] = {0, -1, 1, 0};//Mảng dy là mảng chứa độ di chuyển của đỉnh j để từ ô i,j
/* Giải thích: có thể xét để duyệt ra các ô chung cạnh xung quanh của ô i,j thứ tự giá trị của đỉnh i trong mảng dx tương ứng với thứ 
tự giá trị đỉnh j của mảng dy vì khi từ ô i,j mà di chuyển xung quanh các ô chung cạnh với i,j thì i với j là cặp đỉnh tạo thành cạnh
mà i,j di chuyển đến để xét nên mõi lần di chuyển thì giá trị của i, j phải  thay đổi tương ứng với lần di chuyển đó. Lưu ý vì là từ
ô i,j di chuyển xung quanh các ô chung cạnh với ô i,j( chung cạnh với ô i,j chỉ có 4 ô là : nằm trên i j khi di chuyển đến ô nằm ô 
trên i , j thì giá trị của i phải - 1 còn j thì giữ nguyên tức j = 0 tương ứng với cặp đầu tiên của mảng chứa độ di chuyển của đỉnh
i là dx và mảng chứa độ di chuyển của đỉnh j là dy lần lượt là -1 0 nghĩa là từ i j muốn di chuyển lên trên của i j thì độ di chuyển
phải là a[i - 1][j], nằm bên trái ô i j khi di chuyển đến ô nằm bên trái ô i, j thì giá trị của i giữ nguyên tức là i = 0 còn j thì 
trừ đi 1 tức là j = -1 tương ứng với cặp thứ 2 của mảng chứa độ di chuyển của đỉnh i là dx và mảng chứa độ di chuyển của đỉnh j là 
dy lần lượt là 0 -1 nghĩa là từ i j muốn di chuyển qua trái của i j thì độ di chuyển phải là a[i][j - 1], nằm bên phải ô i j khi di
chuyển đến ô nằm bên phải ô i, j thì giá trị của i giữ nguyên tức là i = 0 còn j thì cộng thêm 1 tức là j = 1 tương ứng với cặp 
thứ 3 của mảng chứa độ di chuyển của đỉnh i là dx và mảng chứa độ di chuyển của đỉnh j là dy lần lượt là 0 1 nghĩa là từ i j muốn 
di chuyển qua phải của i j thì độ di chuyển phải là a[i][j + 1] và nằm bên dưới ô i j khi di chuyển đến ô nằm bên dưới ô i, j thì 
giá trị của i phải trừ đi 1 tức là i = -1 còn j thì giữ nguyên tức là j = 0 tương ứng với cặp cuối của mảng chứa độ di chuyển của
đỉnh i là dx và mảng chứa độ di chuyển của đỉnh j là dy lần lượt là -1 0 nghĩa là từ i j muốn di chuyển xuống dưới của i j thì độ di 
chuyển phải là a[i - 1][j]. Lý do các ô x xung quanh x nằm giữa gọi là cạnh chunh của x nằm giữa vì như ta thấy từ 1 đỉnh mà các đỉnh
xung quanh nằm kề nó thì ta đã học đồ thị, 2 đỉnh mà nối với nhau gọi là cạnh kề tức các cạnh của đồ thị đc tạo bởi 2 đỉnh nối với nhau
nên cạnh chung là các cạnh đều có liên quan tới một đỉnh ví dụ ta có các cạnh 1 2, 2 1, 2 3, 3 2 thì như ta thấy các cạnh của đồ thị 
đều có đỉnh 2 trong đó thì các cạnh mà có liên quan tới 1 đỉnh thì đó đc gọi là cạnh chung

                                                    1 2 3
                                                   1 o x o 
                                                   2 x x x
                                                   3 o x o

thì qua đồ thị 3 đỉnh là từ 1 đến 3 và 2 cạnh là 1 2 và 2 3 như ta thấy từ cạnh 2 nó nối với 2 cạnh là 1 và 3 thì 1 và 3 gọi là cạnh 
chung của đỉnh 2 thì thành phần liên thông của đồ thị trên là 1 2 3 đc biểu diễn bằng ma trận các số nguyên, ô x nằm giữa có vị trí 
là a[2][2] thì khi a[2][2](là x nằm giữa) muốn duyệt các cạnh chung xung quanh a[2][2] thì nó chỉ cần thay đổi giá trị của i và j và 
ta đưa các giá trị của i vào mảng dx và j vào mảng dy và thứ tự các giá trị của i trong mảng dx phải tương ứng với thứ tự giá trị của
j trong mảng dy. Muốn di chuyển x ở giữa(là a[2][2]). Để duyệt cạnh chung của nó nằm ở trên thì i của x nằm giữa phải trừ đi 1 thì i 
lúc này là phần từ đầu tiên đc thêm vào danh sách dx(dx là danh sách chứa các giá trị của i khi di chuyển) là -1 còn j thì giữ nguyên 
và j lúc này là phần tử đầu tiên đc thêm vào danh sách dy(dy là danh sách chứa các giá trị của j khi di chuyển) nên thứ tự cặp đỉnh 
tương ứng(là phần tử thứ 1 của mảng dx và dy) với vị trí mà nó di chuyển tức i = -1 j = 0 thì a[i][j] sẽ di chuyển lên trên tức a[2][2]
lúc này thành a[1][2], duyệt cạnh chung nằm bên trái của a[2][2](tức là x nằm giữa) thì i của x nằm giữa giữ nguyên và i lúc này là phần
tử thứ 2 đc thêm vào danh sách dx(dx là danh sách chứa các giá trị của i khi di chuyển) là 0  còn j thì trừ đi 1 và j lúc này là phần
tử thứ 2 đc thêm vào danh sách dy(dy là danh sách chứa các giá trị của j khi di chuyển) nên thứ tự cặp đỉnh tương ứng(là phần tử thứ 2
của mảng dx và dy) với vị trí mà nó di chuyển tức i = 0 j = -1 thì a[i][j] sẽ di chuyển qua bên trái tức a[2][2] lúc này thành a[2][1],
duyệt cạnh chung nằm bên phải của a[2][2](tức là x nằm giữa) thì i của x nằm giữa giữ nguyên và i lúc này là phần tử thứ 3 đc thêm vào
danh sách dx(dx là danh sách chứa các giá trị của i khi di chuyển) là 0 còn j thì cộng thêm 1 và j lúc này là phần tử thứ 3 đc thêm vào
danh sách dy(dy là danh sách chứa các giá trị của j khi di chuyển) nên thứ tự cặp đỉnh tương ứng(là phần tử thứ 3 của mảng dx và dy) với
vị trí mà nó di chuyển tức i = 0 j = 1 thì a[i][j] sẽ di chuyển qua bên phải tức a[2][2] lúc này thành a[2][3],duyệt cạnh chung của nó 
nằm ở dưới thì i của x nằm giữa phải cộng thêm 1 thì i lúc này là phần tử thứ 4 đc thêm vào danh sách dx(dx là danh sách chứa các giá
trị của i khi di chuyển) là 1 còn j thì giữ nguyên và j lúc này là phần tử thứ 4 đc thêm vào danh sách dy(dy là danh sách chứa các giá
trị của j khi di chuyển) nên thứ tự cặp đỉnh tương ứng(là phần tử thứ 4 của mảng dx và dy) với vị trí mà nó di chuyển tức i = 1 j = 0 
thì a[i][j] sẽ di chuyển lên trên tức a[2][2] lúc này thành a[3][2]. Thì danh sách độ di chuyển của i là dx và của j là dy lúc này sẽ
là: dx {-1, 0, 0 , 1} 
    dy { 0, -1, 1, 0} 
thứ tự phần tử của i trong mảng dx phải cùng với thứ tự phần tử của j trong mảng dy thì một cặp i và j mà đúng theo thứ tự nó sẽ di 
chuyển theo giá trị của i j để xét các cạnh kề xung quanh nó. Ở đây ta đang xét các ô xung quanh chung cạnh với i j theo thứ tự lên 
trên trước, rồi tới trái, rồi tới phải và cuối cùng là dưới, thì cặp giá trị i j tương ứng duyệt lên trên là i = -1 cặp với j = 0 thì
i j sẽ duyệt lên trên tức giá trị mặc định từ vị trí của i j mà [i - 1][j] tức cộng cặp giá trị tương ứng của độ di chuyển i trước rồi 
tới j là [- 1][0]( tức là i j dang duyệt là [2][2] cộng với độ di chuyển i trước rồi tới j là [- 1][0] thì i j bây giờ [2 +(-1)][2+0] 
nghĩa là duyệt lên trên của [2][2] là [1][2] thì nó lên trên của i j duyệt, các hướng còn lại tương tự, còn trái là i = 0 và j = -1 thì 
i j duyệt qua trái tức giá trị mặc định từ vị trí của i j mà [i][j - 1] tức là cộng cặp giá trị tương ứng cặp của độ di chuyển i trước
rồi tới j là [0][-1] thì nó qua bên trái của i j duyệt, còn phải là i = 0 và j = 1 thì i j duyệt qua phải tức giá trị mặc định từ vị 
trí của i j mà [i][j + 1] tức là từ i , j cộng cặp giá trị tương ứng của độ di chuyển i trước rồi tới j là [0][1] thì nó qua bên phải 
của i j duyệt cuối cùng là bên  dưới là i = 1 cặp với j = 0 là i j duyệt xuống dưới tức giá trị mặc định từ vị trí của i j mà i + 1,
j tức cộng cặp giá trị tương ứng của độ di chuyển i trước rồi tới j là [1][0] thì nó xuống dưới của i j duyệt. Mặc định tại 1 vị trí i 
j bất kì, duyệt lên thì cặp giá trị độ di chuyển của i và j là -1 0, duyệt qua phải là 0 1, duyệt xuống dưới là 1 0 và duyệt qua trái
là 0 -1 ,đó là giá trị các cặp i j tương ứng với vị trí mà i j di chuyển tới để duyệt nếu ta không thích duyệt theo thứ tự là trên trái
phải dưới thì ta có thể thay đổi tùy ý miễn sao xét đủ 4 phía là 4 ô chứa cạnh chung xung quanh i j và mõi phía là mặc định với cặp giá
trị i và j tùy ý ta muốn duyệt theo thứ tự nào */

/*Sử dụng thuật toán DFS(thuật toán tìm kiếm theo chiều sau của đồ thị) và thăm các cạnh chung xung quanh i j để đếm số thành phần liên
thông của đồ thị trong lưới ô vuông - hay còn gọi là ma trận kề */
void DFS(int i, int j) {/*Vì đây là duyệt để thăm các cặp đỉnh của đồ thị dưới dạng ma trân kề nên phải truyền vào trong hàm DFS
                        2 tham số i và j tương đương với 2 đỉnh tạo thành cạnh của đồ thị trong ma trận kề */
 
    visited[i][j] = true;
    cout << i << " " << j<<" \n";

    /*Duyệt các đỉnh kề, tức là duyệt các ô cạnh chung xung quanh của i j nói cách khác là duyệt 4 hướng của i j nên cho k chạy từ
    0 tới 3 tức là 4 hướng của i j*/
    for (short k = 0; k < 4; k++)
    {
        /*2 biến i1 j1 dùng để lưu độ di chuyển của i j. Ví dụ ta xét i j có giá trị là [2][2] và vòng lặp for chạy để duyệt các cạnh kề
        chung của i j
        + đầu tiên k = 0 thì ta đang xét i j với giá trị i = 2 và j = 2 nên
        -> i1 = 2 + dx[k] thì trong vòng lặp for này k đang là 0 nên dx[k] là dx[0] tức là phần từ thứ 0 trong mảng dx mà phần tử thứ 0
         tức là phần tử đầu tiên trong mảng dx ta khởi tạo là bằng -1 Nghĩa là i1 = 2 - 1
        -> j1 = 2 + dx[k] thì trong vòng lặp for này k đang là 0 nên dy[k] là dy[0] tức là phần từ thứ 0 trong mảng dy mà phần tử thứ 0
        tức là phần tử đầu tiên trong mảng dy ta khởi tạo là bằng 0 Nghĩa là j1 = 2 + 0
        => i1 lúc này đc lưu là bằng 1 còn j1 đc lưu là bằng 2 tức [i1][j1] = [1][2] tức là đã duyệt lên cạnh chung nằm trên i j
        +.....Các lần duyệt k tiếp theo cũng tương tự như lần đầu tiên cho đến khi k bằng 3 thì dừng thì lúc đó đã duyệt xong 4 hướng lần
        lượt như đã khai báo các giá trị cặp i và j trong mảng dx và dy là trên trái phải dưới tức là xung quanh chung cạnh với i j(là
        [2][2]). */
        int i1 = i + dx[k];
        int j1 = j + dy[k];
        /*- Hai cặp i1 và j1 sẽ lưu độ di chuyển của i và j khi nó duyệt các ô xunh quang chung cạnh với i j. và ta đã khởi tạo ra 2 mảng
           dx là mảng lưu độ di chuyển của i và mảng dy là độ di chuyển của j
           + Trong đó dx ta lưu thứ tự các giá trị độ di chuyển của i là : phần tử thứ 0 trong mảng dx là -1, phần tử thứ 1 trong mảng
           dx là 0, phần tử thứ 2 trong mảng dx là 0 và phần tử thứ 3 trong mảng dx là 1
           + Đối với mảng dy ta lưu thứ tự các giá trị độ di chuyển của j là : phần tử thứ 0 trong mảng dy là 0, phần tử thứ 1 trong
           mảng dx là -1, phần tử thứ 2 trong mảng dx là 1 và phần tử thứ 3 trong mảng dx là 0
           => Theo thứ tự cặp i với j trong hai mảng dx và dy là phần tử thứ 0 của dx bắt buộc phải bắt cặp với phần tử thứ 0 của dy,
           tương tự phần tử thứ 1 của dx phải cặp với phần tử thứ 1 của dy, tương tự phần tử thứ 2 của dx phải cặp với phần tử thứ 2 của
           dy và phần tử thứ 3 của dx phải cặp với phần tử thứ 3 của dy thì thứ tự các cặp mà ta đã khai báo trong hai mảng dx và dy là:
           -1 0, 0 -1, 0 1, 1 0 từ vị trí i j ta lần lượt cộng giá trị của i j với cặp độ di chuyển của i j thì i j sẽ di chuyển theo thứ
           tự: cặp phần tử thứ 0 trong mảng dx và dy -1 0 là i j sẽ di chuyển lên trên , cặp phần tử thứ 1 trong mảng dx và dy 0 -1 là i j
           sẽ di chuyển qua trái, cặp phần tử thứ 2 trong mảng dx và dy 0 1 thì i j sẽ di chuyển qua phải, cuối cùng là cặp phần tử thứ
           3 trong mảng dx và dy 1 0 thì i j di chuyển xuống dưới. khi ta khai báo các phần tử lần lượt trong mảng dx { -1, 0, 0, 1 };
                                                                                và các phần tử lần lượt trong mảng dy { 0, -1, 1, 0 };
            thì thứ tự các phần tử i cặp với j theo như 2 mảng dx và dy ta đã khai báo thì i j sẽ di chuyển và duyệt theo vị trí lần lượt
            là trên trái phải dưới ta có thể thay đổi thứ tự là trên phải dưới trái hay là trên dưới phải trái gì tùy ta thay đổi thứ tự
            các cặp i và j trong mảng dx và dy miễn sao từ i j bất kì ta di chuyển qua các ô xung qanh chung cạnh với i j để xét xem nó có
            cùng kí tự với i j k nếu cùng thì những ô nào mà xunh quanh chung cạnh với i j khi đc xét sẽ là thành phần liên thông của đồ thì,
            và nhớ từ i j ta chỉ xét 4 ô xung quanh chung cạnh với i j là 4 ô trên i j phải i j dưới i j và bên trái của i j. Khi duyệt
            cạnh chunh thì ta chỉ đc phép duyệt theo 4 ô cạnh chung của i j là như vậy thôi còn các vị trí khác k còn là cạnh chung của
            i j nữa ta đã giải thích cạnh chung là như thế nào ở dòng 27 của chương trình. */

        if (i1 >= 1 && i1 <= n && j1 >= 1 && j1 <= m && a[i1][j1] == 'x' && !visited[i1][j1]) {/*Kiểm tra xem vị trí mà i j di chuyển để
        duyệt có nằm trong lưới không và các vị trí xung quanh của a[i][i] khi duyệt có ký tự là x hay không và vị trí mà i j duyệt
        tới đã đc thăm hay chưa nếu vị trí mà i j duyệt tới nằm trong ô lưới và có ký tự là x và chưa đc thăm thì gọi đệ quy hàm DFS để
        thăm vị trí đó còn ngược lại nếu vị trí mà i j duyệt tới nằm ngoài ô lưới và không phải là ký tự x và đã đc thăm hay không thõa
        mãn 1 trong 4 điều kiện thì không gọi đệ quy hàm DFS để thăm vị trí đó ví dụ có ma trận
                                               1 2 3
                                             1 0 x 0
                                             2 x x x
                                             3 0 x 0
        thì khi ta bắt đầu duyệt từ vị trí a[1][1] di chuyển đến các vị trí cạnh chung xung quanh của a[1][1] thì khi duyệt đến vị trí
        nằm trên của a[1][1] thì vị trí này không nằm trong lưới tức k thõa 1 trong 4 điều kiện của if nên k đc gọi đệ quy hàm DFS để
        thăm vị trí nằm ngoài ô lưới này....*/

            DFS(i1, j1);
        }
    }
}

/*Áp dụng BFS(Thuật toán tìm kiếm theo chiều rộng của đồ thị) để duyệt và thăm các ô cạnh chung xung quanh của i j. Khi áp dụng thuật
toán BFS(Thuật toán tìm kiếm theo chiều rộng của đồ thị ) vào việc di chuyển giữa 2 ô thì số lượng bước di chuyển từ ô thứ nhất sang ô
thứ 2 là ngắn nhất tức là đường đi ngắn nhất.*/
void BFS(int i, int j) {

    queue<pair<int, int>> q;
    visited[i][j] = true;
    cout << i << " " << j << "\n";
    q.push({ i, j });

    while (!q.empty())
    {
        pair<int, int> top = q.front();
        q.pop();

        /*Duyệt các đỉnh kề, tức là duyệt các ô cạnh chung xung quanh của i j nói cách khác là duyệt 4 hướng của i j nên cho k chạy từ
        0 tới 3 tức là 4 hướng của i j*/
        for (short k = 0; k < 4; k++)
        {
            int i1 = top.first + dx[k];/*Vì dữ liệu mà ta xét là giá trị của 1 cặp i j và trong ma trận nên top đc tạo ra để chứa data
           nằm ở đầu queue mà mõi data của queue là kiểu i j mà ta tạo ra i1 để chứa độ di chuyển của i nên khi cần lấy giá trị của
           i trong hàng đợi ta cần lấy biến chứa giá trị của cặp i j là biến top mà biến top đc tạo ra bởi vector chứa mõi giá trị là
           một cặp i j kiểu <int, int>(tức <i, j> ) nên chấm tới firt là giá trị đầu tiên là i*/
            int j1 = top.second + dy[k];/*Còn chấm tới second là chấm tới giá trị thứ 2 trong vector có tên là pair của queue và có kiểu
            là <int , int > tức là biến pair chứa data của queue và mõi pair là data đc lưu 1 cặp giá trị kiểu int tức chấm tới second là
            chấm tới j của pair trong queue.*/
            if (i1 >= 1 && i1 <= n && j1 >= 1 && j1 <= m && a[i1][j1] == 'x' && !visited[i1][j1])
            {  
               cout << i1 << " " << j1 << "\n";
               q.push({ i1,j1 });
               visited[i1][j1] = true;
               
            }
        }
    }
}

void inp() {
    cout << "Nhap vao n so dinh va m so canh cua do thi vo huong: \n";
    cin >> n >> m;

    //Nhập giá trị cho lưới ô vuông
    cout << "Nhap ky tu cua hai dinh i j: \n";
    for (short i = 1; i <= n; i++)
    {
        for (short j = 1; j <= m; j++) {
            cout << i << " " << j << " = ";
            cin >> a[i][j];
        }
    }
    memset(visited, false, sizeof(visited));

    //Xuất lưới ô vuông
    cout << "Luoi o vuon sau khi dc nhap la: \n";
    for (short i = 1; i <= n; i++)
    {
       for( short j = 1; j <= m; j++){
           cout << a[i][j] << " ";

        }
       cout << "\n";
    }

    //Xử lí và xuất ra số thành phần liên thông của đồ thị trong lưới ô vuông
    int count = 0;//Biến count dùng để đếm số lượng thành phần liên thồn trong đồ thị
    for (short i = 1; i <= n; i++){
        for (short j = 1; j <= n; j++) {

            if (a[i][j] == 'x' && !visited[i][j]){/*Nếu i j có ký tự x mà chưa đc thăm thì ta truyền vào hàm DFS để hàm DFS thăm các
            cạnh chung xung quanh của i j. */
            
                cout << "Thanh phan lien thong thu " << count + 1 << " : \n";
                BFS(i, j);//Hoặc có thể sử dụng BFS cũng đc hay sử dụng DFS vì nó code ngắn hơn thôi
                ++count;/*Khi hàm DFS thăm xong tất cả các cạnh chung xung quanh của i j rồi thì biến count dùng để đếm số thành phần
                liên thông của đồ thị sẽ tăng lên tương đương đã đếm đc 1 thành phần liên thông của đồ thị */
            }
        }
    }
    cout << "So thanh phan lien thong cua do thi trong luoi o vuong la: " << count<<"\n";
}


int main()
{
    inp();


}
#endif // 0

//=========== CÁCH DUYỆT VÀ THĂM KHÔNG CẦN ĐÁNH DẤU LÀ TRUE OR FALSE CỦA MẢNG VISITED =============================
/*Giải thích tư duy Hàm DFS(Thuật toán tìm kiếm theo chiều sau) và hàm BFS(Thuật toán tìm kiếm theo chiều rộng) thăm và duyệt các ô 
xung quanh chung cạnh với i j mà không cần dùng mảng visited kiểu bool để đánh dấu là true khi đc thăm và false khi chưa đc thăm: 
Vì đồ thị đc biểu diễn bởi lưới ô vuông hoặc gọi cách khác là ma trận kề thì nó chỉ mang hai giá trị thì khi duyệt các ô xung quanh
chung cạnh với i j nếu các ô này có cùng 1 giá trị mà ta cho là 2 đỉnh nối nhau để tạo thành cạnh của đồ thị thì ta đánh dấu là đã
đc thăm bằng cách cho nó bằng giá trị của 2 đỉnh mà không tạo thành cạnh và xuất ra cặp đỉnh vừa đc duyệt cứ như thế cho đế khi trong
lưới ô vuông không còn giá trị của cặp đỉnh nào là giá trị mà ta cho là cạnh của đồ thị nữa thì xong. 
ví dụ ta có lưới ô vuông hay gọi là ma trận kề của đồ thị như sau         
                                                                  1 2 3
                                                                1 o x o 
                                                                2 x x x
                                                                3 o x o 
 giả sử từ cặp a[2][2] tức là x ở giữa ta duyệt các ô xung quanh chung cạnh với a[2][2] cách di chuyển của i j để duyệt và thăm như thế
 nào ta đã giải thích ở phần chương trình dùng mảng visited để duyệt ở bên trên chương trình này rồi nếu quên hãy lên đó xem lại 
 + đầu tiên là duyệt lên trên a[2][2] là a[1][2] hàm DFS hoặc BFS sẽ duyệt xem nó đã đc thăm bằng cách xem nó có phải là giá trị mà ta 
 nhập vào cặp đỉnh i j là cạnh của đồ thị không(Là cạnh khi nó mang giá trị x) nếu đúng thì hàm DFS hoặc BFS đánh dấu là đã thăm bằng 
 cách cập nhật lại cho a[1][2] bằng giá trị mà ta nhập vào cặp i j không là cạnh(Không là cạnh khi nó mang giá trị là o) của dồ thị cụ
 thể xét xem a[1][2] có phải là x(tức là cặp giá trị của i j là cạnh của đồ thị) không thì ta thấy a[1][2] = x thõa đc lúc này ta xuất
 cạnh đỉnh 1 nối với 2 tạo thành cạnh của đồ thị ra và đánh dấu a[1][2] là đã đc thăm bằng cách cập nhật lại giá trị của a[1][2] = o thì
 lưới ô vuông của ta lúc này khi đã thăm ô chung cạnh và nằm trên a[2][2] là a[1][2] lúc này như sau: 
                                                     1 2 3
                                                   1 o o o 
                                                   2 x o x
                                                   3 o x o
cứ cư như thế ta xét hướng các ô xung quanh chunh cạnh với a[2][2] thì ta đã xét phía trên nó rồi còn lại 3 ô là trái(a[2][1]) phải
(là a[2][3]) và dưới(là a[3][2]) ta di chuyển tới và làm tương tự khi xét qua các ô xung quanh mà chung cạnh với i j nếu là giá trị
của cặp i j ta di chuyển để xét tới là cạnh của đồ thị(tức là nó mang giá trị ta nhập vào là cạnh của đồ thị trong lưới ô vuông) thì
ta xuất cặp i j vừa duyệt tới ra và đánh dấu là vị trí đó i j đã di chuyển tới và duyệt rồi bằng cách cập nhật lại vị trí ta vừa duyệt
cho bằng giá trị mà ta nhập vào cặp i j không  là cạnh của đồ thị. Sau khi xét đủ 4 ô xung quanh chung cạnh với i j(a[2][2]) thì lưới
ô vuông của ta lúc này :                                           
                              1 2 3
                            1 o o o 
                            2 o o o
                            3 o o o 
vì khi truyền vào i j vào hàm DFS hoặc BFS thì cặp i j đó đã đc thăm rồi nên nó sẽ đc xuất ra đầu tiên và đánh dấu là đã đc thăm bằng 
cách cập nhật laị bằng giá trị mà ta nhập vào cặp i j không là cạnh tức a[2][2] đang là x(là giá trị của cặp i j khi ta nhập vào đc cho là cạnh của
đồ thị) sau khi duyệt và thăm ta sẽ đánh dấu a[2][2] đã đc thăm lại là bằng o cứ như thế trên lưới ô vuông của ta không còn giá trị nào
khi ta nhập vào đc là cạnh của đồ thị thì các cạnh chung xung quanh i j vừa đc thăm là thành phần liên thông của đồ thị */
#if 0
#include <iostream>
#include<vector>
#include<queue>
using namespace std;


int n, m;
char a[20][20];
int dx[4] = { -1, 0, 0, 1 };
int dy[4] = { 0, -1, 1, 0 };



void DFS(int i, int j) {

    a[i][j] = 'o';/*Đánh dấu i j đã đc thăm bằng cách cập nhật lại giá trị của i j bằng giá trị mà khi ta nhập vào đc cho là i nối 
    với j ko là cạnh của đồ thị cụ thể giá trị ta nhập vào cặp i j không là cạnh của đồ thị là o.*/

    cout << i << " " << j << " \n";//Xuất cặp i j đc cho là cạnh của đồ thị và vừa đc thăm ra 


    for (short k = 0; k < 4; k++)
    {

        int i1 = i + dx[k];
        int j1 = j + dy[k];

        if (i1 >= 1 && i1 <= n && j1 >= 1 && j1 <= m && a[i1][j1] == 'x'){

            DFS(i1, j1);
        }
    }
}


void BFS(int i, int j) {
    queue<pair<int, int>> q;
    q.push({ i, j });
    a[i][j] = 'o';
    cout << i << " " << j << "\n";

    while (!q.empty())    {
        pair<int, int> top = q.front();
        q.pop();

        for (short k = 0; k < 4; k++)
        {
            int i1 = top.first + dx[k];/*Vì dữ liệu mà ta xét là giá trị của 1 cặp i j và trong ma trận nên top đc tạo ra để chứa data
            nằm ở đầu queue mà mõi data của queue là kiểu i j mà ta tạo ra i1 để chứa độ di chuyển của i nên khi cần lấy giá trị của
            i trong hàng đợi ta cần lấy biến chứa giá trị của cặp i j là biến top mà biến top đc tạo ra bởi vector chứa mõi giá trị là
            một cặp i j kiểu <int, int>(tức <i, j> ) nên chấm tới firt là giá trị đầu tiên là i*/
            int j1 = top.second + dy[k];/*Còn chấm tới second là chấm tới giá trị thứ 2 trong vector có tên là pair của queue và có kiểu
            là <int , int > tức là biến pair chứa data của queue và mõi pair là data đc lưu 1 cặp giá trị kiểu int tức chấm tới second là
            chấm tới j của pair trong queue.*/
            if (i1 >= 1 && i1 <= n && j1 >= 1 && j1 <= m && a[i1][j1] == 'x')
            {
                cout << i1 << " " << j1 << "\n";
                q.push({ i1,j1 });
                a[i1][j1] = 'o';
            }
        }
    }
}

void inp() {
    cout << "Nhap vao n so dinh va m so canh cua do thi vo huong: \n";
    cin >> n >> m;


    cout << "Nhap ky tu cua hai dinh i j: \n";
    for (short i = 1; i <= n; i++)
    {
        for (short j = 1; j <= m; j++) {
            cout << i << " " << j << " = ";
            cin >> a[i][j];
        }
    }

    cout << "Luoi o vuon sau khi dc nhap la: \n";
    for (short i = 1; i <= n; i++)
    {
        for (short j = 1; j <= m; j++) {
            cout << a[i][j] << " ";
        }
        cout << "\n";
    }


    int count = 0;
    for (short i = 1; i <= n; i++) {
        for (short j = 1; j <= n; j++) {

            if (a[i][j] == 'x') {/*Phát hiện nếu cặp i j mà mang giá trị x(là giá trị của cặp i j đc cho là i nối với j tạo thành cạnh
                của đồ thị trong lưới ô vuông) thì ta truyền vào cho hàm DFS hoặc BFS để duyệt các ô xung quanh chung cạnh với i j mà
                cơ chế của 2 hàm DFS(Thuật toán tìm kiếm theo chiều sau của đồ thị) và BFS(thuật toán tìm kiếm theo chiều rộng của đồ
                thị) ta đã học rất kỹ rồi 
                + Đối vs DFS trong lưới ô vuông này từ 1 cặp i j mà đc duyệt và thăm thì từ cặp i j mà vừa duyệt DFS sẽ duyệt ra 
                xung quanh nó(theo thứ tự nào trước nào sau thì do ta code ví dụ phải trái trên dưới thì nó duyệt phải trước) nếu
                cặp i j mà nó duyệt tới chưa đc thăm thì nó sẽ gọi đệ quy DFS và truyền vào cặp i j mà nó vừa duyệt tới để thăm cặp i j
                đó rồi từ cặp i j vừa đc thăm đó nó lại duyệt ra xung quanh cạnh chung(xung quanh cạnh chung trong lưới ô vuông giống 
                như là các đỉnh kề với đỉnh vừa đc duyệt vậy hay còn gọi là danh sách kề của nó vì các cạnh này đều liên quan tới 1 đỉnh
                ) của cặp i j vừa đc thăm đó nếu phát hiện 1 cặp i j mà chưa đc thăm thì nó lại gọi đệ quy DFS để thăm cặp i j đó và từ
                cặp i j vừa đc thăm hiện tại lại làm như vậy cho đến khi xung quanh cạnh chung(xung quanh cạnh chung trong lưới ô vuông 
                giống như là các đỉnh kề với đỉnh vừa đc duyệt vậy hay còn gọi là danh sách kề của nó vì các cạnh này đều liên quan tới
                1 đỉnh) của cặp i j hiện tại mà nó đang duyệt không còn cặp nào mà mang giá trị là chưa đc thăm nữa thì nó quay lui về
                xét cho hết các ô xung quanh mà cặp i j chưa xét cho đến khi hết các cặp i j chưa đc thăm thì hàm DFS đã hoàn thành việc
                thăm các cặp i j đc cho là cạnh của đồ thị trong lưới ô vuông thì lúc này ta đã đếm đc 1 thành phần liên thông của đồ thị
                cứ như thế khi vòng lặp for của hàm dung để xử lí và đếm số thành phần liên thông của đồ thị mà gặp cặp i j nào chưa đc
                thăm thì nó sẽ truyền vào hàm DFS để thăm cách cạnh kề với nó trong thành phần liên thông của đồ thị và tăng biến dùng
                để đếm số thành phần liên thông của đồ thị lên cho đến khi tất cả các giá trị của cặp i j trong lưới ô vuông đc thăm hết
                thì lúc đó hàm đếm số thành phần liên thông của đồ thị trên lưới ô vuông cũng trả về số lượng thành phần liên thông của
                đồ thị và xong
                + Đối với BFS trong lưới ô vuông này từ 1 cặp i j mà đc duyệt tới mà thăm nó sẽ lan rộng ra cả 4 ô xung quanh nó 

            */

                cout << "Thanh phan lien thong thu " << count + 1 << " : \n";
                BFS(i, j);
                ++count;
            }
        }
    }
    cout << "So thanh phan lien thong cua do thi trong luoi o vuong la: " << count << "\n";
}


int main()
{
    inp();

}
#endif // 1



























