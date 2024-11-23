#if 0
#include <iostream>
#include<vector>
#include<queue>
using namespace std;
/*Áp dụng thuật toán DFS và BFS trên lưới ô vuông:
Bài 2:Kiểm tra đường đi giữa 2 điểm trên lưới.
input: nhập vào n hàng = 6 và m cột = 6 của lưới | Output: kiểm tra đc giữa 2 điểm có đường đi hay không cụ thể như hình bên input 
ô vuông                                          | thì kiểm tra đường đi từ điểm A(là điểm bắt đầu đường đi) tới điểm B(Là điểm kết
           1 2 3 4 5 6                           | thúc đường đi)
         1 A o o x o o                           |
         2 o x o o o o                           |
         3 o x o o o o                           |
         4 o o o o x x                           |
         5 B o o o x o                           |
         6 o o o x x x                           |*/

int n, m, s, t;/*n là số hàng của lưới ô vuông, m là số cột của lưới ô vuông, s là biến lưu giá trị i của điểm bắt đầu đường đi và t
là biến lưu giá trị j của điểm bắt đầu đường đi
đường đi*/
bool visited[20][20];
char a[20][20];
int dx[4] = { -1,0,0,1 };
int dy[4] = { 0,-1,1,0 };

bool DFS(int i, int j) {
    cout << i << j<<"\n";
    if (a[i][j] == 'B')//Nếu điểm cuối đường đi mà đc thăm thì từ A đến B có đường đi
    {
        return true;
    }
    visited[i][j] = true;

    for (short k = 0; k < 4; k++)
    {
        int i1 = i + dx[k];
        int j1 = j + dy[k];

        if (i1 >= 1 && i1 <= n && j1 >= 1 && j1 <= m && !visited[i1][j1] && a[i1][j1] != 'x')/*Như trên hình minh họa lưới ô vuông của
         input đề bài o là có đường còn x giống cục đá chặn đường đi vậy tức không thể đi từ A đến B khi gặp giá trị của cặp i j là x đc.
         Lý do để != x và không cho a[i1][j1] != 'o' để truyền vào đệ quy thăm là do nếu ddk của ta xét đường đi bằng o thì khi gặp điểm
         B hàm DFS sẽ không thể truyền cặp i j có giá trị là B vào đệ quy DFS để thăm đc vì đk là chỉ thăm các cặp có giá trị = o thôi nên
         ta cho đk cặp i j khác giá trị x là đc là khi gặp các cặp i j mang giá trị là A, o, B thì nó đều thỏa đk vào thực hiện việc truyền
         cặp i j mà nó duyệt tới vào DFS để thăm.
         */
        {
            
            if (DFS(i1, j1))/*kiểm tra xem nếu hàm DFS của cặp i1 j1(i1 j1 là ô được i j mở rộng ra để xét các ô chung cạnh xung quanh i j) mà 
                là true(tức là thấy điểm ở cuối đường đi là điểm B) thì hàm DFS sẽ dừng lại và trả về cho hàm DFS mang giá trị của cặp i1 j1 
                đc cho là B(tức là hàm DFS(i1,j1) đang mang trạng thái của điểm B) là true thì hàm DFS sẽ dừng lại và không mở rộng giá trị i1
                j1 mang điểm B này để duyệt nữa nên khi hàm (DFS(i1,j1)tức hàm con) mà true thì thõa đk if này và hàm DFS cha(tức là cặp i j đã 
                mở rộng ra để duyệt tới cặp i1 j1 này) sẽ đc truyền lại giá trị true từ hàm DFS mang giá trị con của hàm DFS cha 
                => ví dụ: 
                khi ta nhập vào như input và đường đi từ A đến B trong lưới ô vuông đi qua các ô sau 1 1, 1 2, 1 3, 2 3, 2 4, 2 5, 2 6, 3 6, 3 5,
                3 4, 3 3, 4 3, 4 2, 4 1, 3 1, 2 1, 5 1 thì ô 1 1 là ô mang giá trị điểm đầu đường đi tức là điểm A ô mang giá trị của điểm cuối 
                đường đi là 5 1 thì khi duyệt thấy ô 5 1 đã là điểm cuối đường đi(tức là điểm B) thì ở DFS(i, j) tức là DFS(5,1) này sẽ trả về 
                true và dừng lại không duyệt thêm các ô xung quanh của 5 1 nữa vì từ điểm A(tức là điểm đầu đường đi) duyệt các ô xung quanh điểm
                A như sau điểm A là ô 1 1 từ 1 1 duyệt xung quanh theo độ di chuyển mà ta đã khai báo ở 2 mảng dx mang giá trị độ di chuyển của i
                và dy mang giá trị của độ j nên nhớ thứ tự khai báo i trong mảng dx phải tương ứng với thứ tự khai báo j trong mảng dy thì từ 
                i j nó mới cộng cặp i j trong dx và dy và di chuyển theo thứ tự tùy ta chỉnh sửa khi khai báo trong 2 mảng dx và dy ở đây ta khai 
                báo cho i j di chuyển để duyệt theo thứ tự đầu tiên là trên i j thứ 2 là trái i j thứ 3 là phải i j và cuối cùng là dưới i j nên 
                từ điểm ở đầu đương đi là ô 1 1 khi tryền vào DFS thì nó sẽ duyệt trên 1 1 trước mà trên ô 1 1 là ô 0 0 k thõa đk vì k nằm trong
                lưới ô vuông, thứ 2 là duyệt đến bên trái ô 1 1 là ô 1 0 cũng k thõa đk vì k nằm trong lưới ô vuông, thứ 3 là ô bên phải ô 1 1 là 
                ô 1 2 thì 1 2 thõa đk nằm trong lưới ô vuông và chưa đc thăm và khác ký tự x nên truyền ô 1 2 này vào lời gọi hàm đệ quy DFS và 
                ngăn xếp lúc này chứa 2 trạng thái là DFS(1,2),DFS(1,1). Sau khi ô 1 2 đc truyền vào lời gọi hàm đệ quy DFS thì DFS sẽ đánh dấu ô 
                1 2 đã đc thăm bằng cách cập nhật lại giá trị của ô 1 2 là true và xét xem ô 1 2 có mang giá trị B không nếu có thì trả về true
                cho hàm DFS ô 1 2 là true và k duyệt thêm nữa vì là ô 1 2 không phải là giá trị B nên DFS(1,2) tiếp tục duyệt các ô xung quanh 
                chung cạnh với ô 1 2 theo thứ tự trên trái phải dưới cứ như thế khi mà mở rộng ô 1 2 ra duyệt thấy ô thõa đk là nằm trong ô lưới
                và chưa đc thăm và khác ký tự x thì truyền vào lời gọi hàm đệ quy DFS khi truyền vào thì trạng thái DFS vừa đc truyền vào giá trị
                i j thõa đk sẽ đc thêm vào đầu ngăn xếp nơi chứa các trạng thái của lời gọi hàm đệ quy và thăm ô vừa đc duyệt mà thõa đk đó và xét
                ô vừa đc duyệt đó có phải là B không vì là các bước tiếp theo giống nên k giải thích nữa cho đến khi gặp đc ô 4 1 thì lúc này ngăn 
                xếp chứa trạng thái của lời gọi hàm đệ quy DFS như sau DFS(4,1),DFS(4,2),DFS(4,3),DFS(3,3),DFS(3,4),DFS(3,5),DFS(3,6),DFS(2,6),
                DFS(2,5), DFS(2,4), DFS(2,3), DFS(1,3),DFS(1,2),DFS(1,1). thì sau khi 4 1 đc truyền vào hàm đệ quy DFS thì lúc này như ta thấy
                danh sách ngăn xếp trạng thái của hàm DFS(4,1) đc thêm vào đầu danh sách thì lúc này DFS lại xét giá trị của ô 4 1 có phải là 
                B không vì là không nên không trả về true cho hàm DFS mang trạng thái 4 1 này và tiếp tục mở rộng ô 4 1 để duyệt tìm B theo 
                thứ tự trên trái phải dưới đầu tiên là duyệt ô nằm trên ô 4 1 là ô 3 1 thì ô 3 1 thõa đk là nằm trong lưới ô vuông và chưa đc
                thăm và khác ký tự x nên truyền ô 3 1 vào lời gọi hàm DFS thì ngăn xếp lúc này sau khi đc thêm trạng thái ô 3 1 vào đầu ngăn 
                xếp thì ngăn xếp lúc này là DFS(3,1), DFS(4,1),DFS(4,2),DFS(4,3),DFS(3,3),DFS(3,4),DFS(3,5),DFS(3,6),DFS(2,6), DFS(2,5), DFS(2,4)
                ,DFS(2,3), DFS(1,3),DFS(1,2),DFS(1,1). thì sau khi 3 1 đc truyền vào hàm đệ quy DFS thì lúc này như ta thấy danh sách ngăn xếp 
                trạng thái của hàm DFS(3,1) đc thêm vào đầu danh sách thì lúc này DFS lại xét giá trị của ô 3 1 có phải là B không vì là không 
                nên không trả về true cho hàm DFS mang trạng thái 3 1 này và tiếp tục mở rộng ô 3 1 để duyệt tìm B theo thứ tự trên trái phải 
                dưới đầu tiên là duyệt ô nằm trên ô 3 1 là ô 2 1 thì ô 2 1 thõa đk là nằm trong lưới ô vuông và chưa đc thăm và khác ký tự x nên
                truyền ô 2 1 vào lời gọi hàm DFS thì ngăn xếp lúc này sau khi đc thêm trạng thái ô 2 1 vào đầu ngăn xếp thì ngăn xếp lúc này là
                DFS(2,1), DFS(3,1), DFS(4,1),DFS(4,2),DFS(4,3),DFS(3,3),DFS(3,4),DFS(3,5),DFS(3,6),DFS(2,6), DFS(2,5), DFS(2,4), DFS(2,3), 
                DFS(1,3),DFS(1,2),DFS(1,1). thì sau khi 2 1 đc truyền vào hàm đệ quy DFS thì lúc này như ta thấy
                danh sách ngăn xếp trạng thái của hàm DFS(2,1) đc thêm vào đầu danh sách thì lúc này DFS lại xét giá trị của ô 2 1 có phải là 
                B không vì là không nên không trả về true cho hàm DFS mang trạng thái 2 1 này và tiếp tục mở rộng ô 2 1 để duyệt tìm B theo 
                thứ tự trên trái phải dưới đầu tiên là duyệt ô nằm trên ô 2 1 là ô 1 1 thì ô 1 1 k thõa đk là chưa đc
                thăm và khác ký tự x nên không truyền ô 1 1 vào lời gọi hàm DFS tiếp là đến duyệt ô bên trái của ô 2 1 ô bên trái của ô 2 1 là
                ô 2 0 thì ô 2 0 không thõa đk là nằm trong lưới ô vuông nên không đc truyền vào lời gọi hàm đệ quy DFS tiếp là duyệt đến ô bên
                phải của ô 2 1 ô bên phải của 2 1 là ô 2 2 mà ô 2 2 không thỏa đk là chưa đc thăm(vì ta duyệt và đánh dấu ô vừa thăm là cập nhật
                lại giá trị cho ô vừa thăm là x nên xét tới ô 2 2 này thì ô 2 2 đang là x tức là đã đc thăm) nên không truyền vào lời gọi hàm đệ
                quy DFS cuối cùng là duyệt đến ô nằm dưới ô 2 1 là ô 3 1 thì ô 3 1 cũng đã đc thăm nên không thõa đk để đc truyền vào lời gọi 
                hàm DFS vì ở ô 2 1 này đã duyệt đủ các ô xung quanh chung cạnh với ô 2 1 mà không có ô nào thõa đk nên trạng thái DFS của ô 2 1 
                lúc này đã xong và DFS(2,1) đc đẩy ra khỏi ngăn xếp thì ngăn xếp sau khi trạng thái của hàm DFS(2,1) đc hoàn thành là : DFS(3,1),
                DFS(4,1),DFS(4,2),DFS(4,3),DFS(3,3),DFS(3,4),DFS(3,5),DFS(3,6),DFS(2,6), DFS(2,5), DFS(2,4), DFS(2,3), DFS(1,3),DFS(1,2),DFS(1,1).
                Như ta thấy danh sách ngăn xếp sau khi trạng thái của hàm DFS(2,1) đã hoàn thành và đc lấy ra khỏi ngăn xếp thì lúc này nó sẽ quay
                lui về hàm mang trạng thái ở đầu ngăn xếp tức là lấy trạng thái ở đầu ngăn xếp là DFS(3,1) ra để duyệt các các ô xung quanh chung
                cạnh với ô 3 1 thì ở hàm DFS mang trạng thái ô 3 1 cũng tương tự như hàm DFS mang trạng thái của ô 2 1 nên hàm DFS mang trạng thái
                ô 3 1 cũng hoàn thành và đẩy ra khỏi ngăn xếp thì danh sách sau khi lấy trạng thái ở đầu danh sách(là DFS(3,1)) ra của lần quay
                lui từ 2 1 về 3 1 lúc này là : DFS(4,1),DFS(4,2),DFS(4,3),DFS(3,3),DFS(3,4),DFS(3,5),DFS(3,6),DFS(2,6), DFS(2,5), DFS(2,4),
                DFS(2,3), DFS(1,3),DFS(1,2),DFS(1,1). Như ta thấy danh sách ngăn xếp sau khi trạng thái của hàm DFS(3,1) đã hoàn thành và đc lấy 
                ra khỏi ngăn xếp thì lúc này nó sẽ quay lui về hàm mang trạng thái ở đầu ngăn xếp tức là lấy trạng thái ở đầu ngăn xếp là
                DFS(4,1) ra để duyệt các các ô xung quanh chung cạnh với ô 4 1 đầu tiên là trên ô 4 1 là ô 3 1 đã đc thăm k thõa đk, tiếp là ô
                bên trái ô 4 1 là ô 4 0 thì ô 4 0 không nằm trong lưới ô vuông không thõa đk, tiếp là ô bên phải của ô 4 1 là ô 4 2 thì ô 4 2
                đã đc thăm nên không thõa đk cuối cùng là ô 5 1 thì ô 5 1 lúc này thõa đk của của ô 4 1 khi mở rộng ra duyệt là nằm trong lưới
                ô vuông và chưa đc thăm(vì ta duyệt và xét 1 ô có đc thăm hay chưa bằng cách xem nó có khác ký tự x không nếu khác là chưa đc
                thăm còn không là đc thăm rồi chứ k phải dùng mảng visited đánh dấu true false ) thì lúc này ô 5 1 đc truyên vào lời gọi hàm đệ
                quy DFS và hàm DFS mang trạng thái của ô 5 1 đc thêm vào đầu ngăn xếp nên danh sách ngăn xếp của ta lúc này: DFS(5,1), DFS(4,1),
                DFS(4,2), DFS(4,3),DFS(3,3),DFS(3,4),DFS(3,5),DFS(3,6),DFS(2,6), DFS(2,5), DFS(2,4), DFS(2,3), DFS(1,3),DFS(1,2),DFS(1,1).Sau
                khi truyền giá trị của ô 5 1 vào lời gọi hàm đệ quy DFS thì lúc này hàm DFS sẽ xét giá trị của ô 5 1 có là B không thì giá trị
                của ô 5 1 lúc này là B nên trả về cho hàm mang trạng thái của ô 5 1 là true lặp tức dừng việc mở rộng ô 5 1 để duyệt các ô xung
                quanh chung cạnh với ô 5 1 lại và nó sẽ quay lui lại và truyền giá trị true cho mõi lần quay lui về tức lấy trạng thái của của
                DFS ở đầu danh sách ngăn xếp ra xét là nếu giá trị con của lần quay lui này mà là true thì thằng mà đang quay lui về cũng đc 
                trả về true luôn cụ thể quay lui về hàm ở đầu danh sách ngăn xếp là hàm mang trạng thái của ô 4 1 tức là DFS(4,1) thì hàm 
                DFS(4,1) nó xét thằng con của nó mở rộng ơ trong danh sách ngăn xếp có đang là true hay không nếu con của ô 4 1 là true thì
                hàm mang trạng thái ô 4 1 cũng đc truyền về giá trị là true thì ô con mà đc ô 4 1 mở rộng ra xét để thăm ở trong ngăn xếp lúc 
                này là hàm mnag trạng thái ô 5 1 thì hàm mang trạng trạng thái ô 5 1 đã là true nên thõa đk if (DFS(i1, j1))(i1 j1 là ô con 
                của hàm i j chứa hàm đệ quy tức hàm cha lúc này là 4 1 chứa hàm đệ quy là 5 1) nên DFS(5,1) là true đã thõa đk nên hàm chứa 
                hàm đệ quy của ô 5 1 này là DFS(4,1) cũng đc trả về true luôn. Sau khi DFS(4,1) đc trả về true thì DFS(5,1) đc đẩy ra khỏi ngăn
                xếp và quay lui về hàm mang trạng thái của ô 4 2 sẽ xét if mà hàm con của 4 2 mà true thì thì 4 2 cũng trả về true thì con
                của hàm DFS(4, 2) là DFS(4,1) mà DFS(4,1) đang là true nên thõa đk nên hàm mang trạng thái 4 2 cũng đc trả về là true cứ như thế
                cho đến khi tất cả các trạng thái của hàm DFS đc trả về true hết thì hàm DFS này là true tức là từ điểm ở đầu đường đi là điểm
                A tới điểm ở cuối đường đi là điểm B có đường đi */
                return true;


        }
    }
    return false;/*Nếu nhánh của i1 j1 không đi đc đến ký tự B thì trả về false chỉ trả về false thôi chứ chưa đc kết luận là chưa có đường
    đi vì i1 j1 chỉ là 1 cái nhánh DFS thôi chứ không phải toàn bộ*/
}

bool BFS(int i, int j) {
    queue<pair<int, int>> q;

    q.push({ i,j });
    visited[i][j] = true;
    cout << i << " " << j<<"\n";
    while (!q.empty())
    {

       pair<int,int> top = q.front();
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
           if (i1 >= 1 && i1 <= n && j1 >= 1 && j1<= m && !visited[i1][j1] && a[i1][j1] != 'x')
           {
               cout << i1 << " " << j1<<"\n";
               if (a[i1][j1] == 'B') {
                   return true;
               }
               q.push({i1,j1});
               visited[i1][j1] = true;
               
           }
       }

    }

    return false;
}

void inp() {
    cout << "Nhap vao n cot va m hang cua luoi o vuong : \n";
    cin >> n >> m;

    cout << "Nhap vao gia tri cua cap i j trong luoi o vuong: \n";
    for (short i = 1; i <= n; i++)
    {
        for (short j = 1; j <= m; j++) {
            cout << i << " " << j << " = ";
            cin >> a[i][j];
            if (a[i][j] == 'A') {/*Kiểm tra nếu cặp i j là điểm bắt đầu của đường đi thì ta cho x1 giữ giá trị của i và y1 giữ giá trị của
             j tức x1 và y1 đang mang tọa độ của điểm đầu đường đi*/


                s = i;
                t = j;
            }
        }
    }
    memset(visited, false, sizeof(visited));

    cout << "\nLuoi o vuong sau khi nhap: \n";
    for (short i = 1; i <= n; i++)
    {
        for (short j = 1; j <= n; j++) {
            cout << a[i][j] << " ";
        }
        cout << "\n";
    }

   /* cout << "\nTu A den B theo thuat toan DFS thi co duong di nhu sau: \n ";*/
    cout << "\nTu A den B theo thuat toan BFS thi co duong di nhu sau: \n ";
    if (BFS(s,t))/*Kiểm tra nếu truyền vào s t tức là giá trị của cặp i j đầu đường đi và duyệt từ điểm ở đầu đường đi mà tới đc điểm
                     ở cuối đường đi thì kết luận từ điểm ở đầu đường đi đến điểm ở cuối đường đi là có đường đi. Vì ở hàm inp này trong 
                     lúc nhập giá trị của cặp i và j cho lưới ô vuông hay còn gọi là ma trận kề của đồ thị thì ta đã cho bắt trường hợp 
                     giá trị nào mà là đầu đường đi(giá trị đầu đường đi là 'A') thì ta cho biến s(là lưu giá trị của i) và t(là lưu giá
                     trị của j) để lưu lại cặp i và j mang giá trị đầu đường đi thì lúc này s và t đang lưu giá trị đầu đường đi(là 'A')
                     trong lưới ô vuông sau đó ta truyền s và t vào cho hàm DFS hoặc BFS để duyệt từ điểm ở đầu đường đi(là điểm A) mà 
                     hàm BFS và DFS ta cho kiểu bool nên khi ta cho duyệt các cạnh chung xung quanh khi bắt đầu từ điểm ở đầu đường đi
                     thì những ô nào mà khác x thì là đường đi cho đến khi gặp đc điểm ở cuối đường đi là 'B' thì ta trả về cho hàm là 
                     true còn duyệt không thấy điểm cuối đường đi(là điểm B) thì ta trả về cho hàm là false nên dk  if (DFS(s,t)) hoặc 
                     if (BFS(s,t)) là nếu DFS hoặc BFS trả về là true thì kết luận là từ điểm A đến điểm B có đường đi ngược lại !DFS(s,
                     t)) !BFS(s, t)) như thế này thì từ điểm A đến điểm B không có đường đi. 
                     */
    {
        cout << "\nTu diem A den diem B trong do thi co duong di\n";
    }
    else
    {
        cout << "\nTu diem A den diem B trong do thi khong co duong di\n";
    }
}
 
    int main() {
        inp();
    }
    

#endif // 0

//=========== CÁCH DUYỆT VÀ THĂM KHÔNG CẦN ĐÁNH DẤU LÀ TRUE OR FALSE CỦA MẢNG VISITED =============================
#if 0
#include <iostream>
#include<vector>
#include<queue>
    using namespace std;
    /*Áp dụng thuật toán DFS và BFS trên lưới ô vuông:
    Bài 2:Kiểm tra đường đi giữa 2 điểm trên lưới.
    input: nhập vào n hàng = 6 và m cột = 6 của lưới | Output: kiểm tra đc giữa 2 điểm có đường đi hay không cụ thể như hình bên input
    ô vuông                                          | thì kiểm tra đường đi từ điểm A(là điểm bắt đầu đường đi) tới điểm B(Là điểm kết
               1 2 3 4 5 6                           | thúc đường đi)
             1 A o o x o o                           |
             2 o x o o o o                           |
             3 o x o o o o                           |
             4 o o o o x x                           |
             5 B o o o x o                           |
             6 o o o x x x                           |*/

    int n, m, s, t;/*n là số hàng của lưới ô vuông, m là số cột của lưới ô vuông, s là biến lưu giá trị i của điểm bắt đầu đường đi và t
    là biến lưu giá trị j của điểm bắt đầu đường đi đường đi*/
    char a[20][20];
    int dx[4] = { -1,0,0,1 };
    int dy[4] = { 0,-1,1,0 };

    bool DFS(int i, int j) {
        cout << i << j << "\n";
        if (a[i][j] == 'B'){/*Nếu điểm cuối đường đi mà đc thăm thì từ A đến B có đường đi. Tức vì là biểu diễn đồ thị ở dạng lưới ô vuông
        nên ở hàm inp ta nhập vào các giá trị cho lưới ô vuông là dạng i j mà ở hàm inp ta đã bắt được giá trị đầu đường đi của i và j
        vào 2 biến s và t và truyền vào hàm DFS này  nên hàm DFS(thuật toán tìm kiếm theo chiều sau của đồ thị) sẽ duyệt và thăm tất cả
        các cạnh chung xung quanh khi bắt đầu từ điểm ở đầu đường đi là điểm 'A' thì cơ chế của thuật toán DFS(Thuật toán tìm kiếm theo
        chiều sau của đồ thị) đối với lưới ô vuông từ 1 cạnh chung xung quanh mà nó duyệt tới mà chưa đc thăm thì lặp tức sẽ gọi đệ quy 
        lại hàm DFS và truyền cạnh chung vừa đc thăm vào rồi từ cạnh vừa đc DFS duyệt tới và thăm thì hàm DFS lại duyệt cạnh chung với
        cạnh mà vừa đc duyệt xem có nằm trong lưới hay không, có khác ký tự không phải là đường đi(tức là x) hay không và đc thăm hay
        chưa nếu chưa nếu cạnh chung với cạnh vừa đc thăm đang đc duyệt mà nằm trong lưới ô vuông, khác ký tự x và chưa đc thăm thì cạnh
        đang dc duyệt hiện tại này sẽ lại đc truyền vào hàm đệ quy DFS và từ cạnh vừa đc duyệt đó nó lại tiếp tục duyệt các ô chung cạnh
        với nó nếu nằm trong lưới ô vuông và khác ký tự x và chưa đc thăm thì cạnh đó đc truyền vào hàm đệ quy cứ như thế cho đến khi 
        gặp đc ký tự cuối đường đi(là điểm 'B') thì ta dừng lại và hàm DFS khi gặp  */
            return true;
        }
        a[i][j] = 'x';

        for (short k = 0; k < 4; k++)
        {
            int i1 = i + dx[k];
            int j1 = j + dy[k];

            if (i1 >= 1 && i1 <= n && j1 >= 1 && j1 <= m && a[i1][j1] != 'x'){/*Như trên hình minh họa lưới ô vuông của
             input đề bài o là có đường còn x giống cục đá chặn đường đi vậy tức không thể đi từ A đến B khi gặp giá trị của cặp i j là x đc.
             Lý do để != x và không cho a[i1][j1] != 'o' để truyền vào đệ quy thăm là do nếu ddk của ta xét đường đi bằng o thì khi gặp điểm
             B hàm DFS sẽ không thể truyền cặp i j có giá trị là B vào đệ quy DFS để thăm đc vì đk là chỉ thăm các cặp có giá trị = o thôi nên
             ta cho đk cặp i j khác giá trị x là đc là khi gặp các cặp i j mang giá trị là A, o, B thì nó đều thỏa đk vào thực hiện việc truyền
             cặp i j mà nó duyệt tới vào DFS để thăm.
             */
           
                
                if (DFS(i1, j1))/*kiểm tra xem nếu hàm DFS của cặp i1 j1(i1 j1 là ô được i j mở rộng ra để xét các ô chung cạnh xung quanh i j) mà 
                là true(tức là thấy điểm ở cuối đường đi là điểm B) thì hàm DFS sẽ dừng lại và trả về cho hàm DFS mang giá trị của cặp i1 j1 
                đc cho là B(tức là hàm DFS(i1,j1) đang mang trạng thái của điểm B) là true thì hàm DFS sẽ dừng lại và không mở rộng giá trị i1
                j1 mang điểm B này để duyệt nữa nên khi hàm (DFS(i1,j1)tức hàm con) mà true thì thõa đk if này và hàm DFS cha(tức là cặp i j đã 
                mở rộng ra để duyệt tới cặp i1 j1 này) sẽ đc truyền lại giá trị true từ hàm DFS mang giá trị con của hàm DFS cha 
                => ví dụ: 
                khi ta nhập vào như input và đường đi từ A đến B trong lưới ô vuông đi qua các ô sau 1 1, 1 2, 1 3, 2 3, 2 4, 2 5, 2 6, 3 6, 3 5,
                3 4, 3 3, 4 3, 4 2, 4 1, 3 1, 2 1, 5 1 thì ô 1 1 là ô mang giá trị điểm đầu đường đi tức là điểm A ô mang giá trị của điểm cuối 
                đường đi là 5 1 thì khi duyệt thấy ô 5 1 đã là điểm cuối đường đi(tức là điểm B) thì ở DFS(i, j) tức là DFS(5,1) này sẽ trả về 
                true và dừng lại không duyệt thêm các ô xung quanh của 5 1 nữa vì từ điểm A(tức là điểm đầu đường đi) duyệt các ô xung quanh điểm
                A như sau điểm A là ô 1 1 từ 1 1 duyệt xung quanh theo độ di chuyển mà ta đã khai báo ở 2 mảng dx mang giá trị độ di chuyển của i
                và dy mang giá trị của độ j nên nhớ thứ tự khai báo i trong mảng dx phải tương ứng với thứ tự khai báo j trong mảng dy thì từ 
                i j nó mới cộng cặp i j trong dx và dy và di chuyển theo thứ tự tùy ta chỉnh sửa khi khai báo trong 2 mảng dx và dy ở đây ta khai 
                báo cho i j di chuyển để duyệt theo thứ tự đầu tiên là trên i j thứ 2 là trái i j thứ 3 là phải i j và cuối cùng là dưới i j nên 
                từ điểm ở đầu đương đi là ô 1 1 khi tryền vào DFS thì nó sẽ duyệt trên 1 1 trước mà trên ô 1 1 là ô 0 0 k thõa đk vì k nằm trong
                lưới ô vuông, thứ 2 là duyệt đến bên trái ô 1 1 là ô 1 0 cũng k thõa đk vì k nằm trong lưới ô vuông, thứ 3 là ô bên phải ô 1 1 là 
                ô 1 2 thì 1 2 thõa đk nằm trong lưới ô vuông và chưa đc thăm và khác ký tự x nên truyền ô 1 2 này vào lời gọi hàm đệ quy DFS và 
                ngăn xếp lúc này chứa 2 trạng thái là DFS(1,2),DFS(1,1). Sau khi ô 1 2 đc truyền vào lời gọi hàm đệ quy DFS thì DFS sẽ đánh dấu ô 
                1 2 đã đc thăm bằng cách cập nhật lại giá trị của ô 1 2 là ký tự x và xét xem ô 1 2 có mang giá trị B không nếu có thì trả về true
                cho hàm DFS ô 1 2 là true và k duyệt thêm nữa vì là ô 1 2 không phải là giá trị B nên DFS(1,2) tiếp tục duyệt các ô xung quanh 
                chung cạnh với ô 1 2 theo thứ tự trên trái phải dưới cứ như thế khi mà mở rộng ô 1 2 ra duyệt thấy ô thõa đk là nằm trong ô lưới
                và chưa đc thăm và khác ký tự x thì truyền vào lời gọi hàm đệ quy DFS khi truyền vào thì trạng thái DFS vừa đc truyền vào giá trị
                i j thõa đk sẽ đc thêm vào đầu ngăn xếp nơi chứa các trạng thái của lời gọi hàm đệ quy và thăm ô vừa đc duyệt mà thõa đk đó và xét
                ô vừa đc duyệt đó có phải là B không vì là các bước tiếp theo giống nên k giải thích nữa cho đến khi gặp đc ô 4 1 thì lúc này ngăn 
                xếp chứa trạng thái của lời gọi hàm đệ quy DFS như sau DFS(4,1),DFS(4,2),DFS(4,3),DFS(3,3),DFS(3,4),DFS(3,5),DFS(3,6),DFS(2,6),
                DFS(2,5), DFS(2,4), DFS(2,3), DFS(1,3),DFS(1,2),DFS(1,1). thì sau khi 4 1 đc truyền vào hàm đệ quy DFS thì lúc này như ta thấy
                danh sách ngăn xếp trạng thái của hàm DFS(4,1) đc thêm vào đầu danh sách thì lúc này DFS lại xét giá trị của ô 4 1 có phải là 
                B không vì là không nên không trả về true cho hàm DFS mang trạng thái 4 1 này và tiếp tục mở rộng ô 4 1 để duyệt tìm B theo 
                thứ tự trên trái phải dưới đầu tiên là duyệt ô nằm trên ô 4 1 là ô 3 1 thì ô 3 1 thõa đk là nằm trong lưới ô vuông và chưa đc
                thăm và khác ký tự x nên truyền ô 3 1 vào lời gọi hàm DFS thì ngăn xếp lúc này sau khi đc thêm trạng thái ô 3 1 vào đầu ngăn 
                xếp thì ngăn xếp lúc này là DFS(3,1), DFS(4,1),DFS(4,2),DFS(4,3),DFS(3,3),DFS(3,4),DFS(3,5),DFS(3,6),DFS(2,6), DFS(2,5), DFS(2,4)
                ,DFS(2,3), DFS(1,3),DFS(1,2),DFS(1,1). thì sau khi 3 1 đc truyền vào hàm đệ quy DFS thì lúc này như ta thấy danh sách ngăn xếp 
                trạng thái của hàm DFS(3,1) đc thêm vào đầu danh sách thì lúc này DFS lại xét giá trị của ô 3 1 có phải là B không vì là không 
                nên không trả về true cho hàm DFS mang trạng thái 3 1 này và tiếp tục mở rộng ô 3 1 để duyệt tìm B theo thứ tự trên trái phải 
                dưới đầu tiên là duyệt ô nằm trên ô 3 1 là ô 2 1 thì ô 2 1 thõa đk là nằm trong lưới ô vuông và chưa đc thăm và khác ký tự x nên
                truyền ô 2 1 vào lời gọi hàm DFS thì ngăn xếp lúc này sau khi đc thêm trạng thái ô 2 1 vào đầu ngăn xếp thì ngăn xếp lúc này là
                DFS(2,1), DFS(3,1), DFS(4,1),DFS(4,2),DFS(4,3),DFS(3,3),DFS(3,4),DFS(3,5),DFS(3,6),DFS(2,6), DFS(2,5), DFS(2,4), DFS(2,3), 
                DFS(1,3),DFS(1,2),DFS(1,1). thì sau khi 2 1 đc truyền vào hàm đệ quy DFS thì lúc này như ta thấy
                danh sách ngăn xếp trạng thái của hàm DFS(2,1) đc thêm vào đầu danh sách thì lúc này DFS lại xét giá trị của ô 2 1 có phải là 
                B không vì là không nên không trả về true cho hàm DFS mang trạng thái 2 1 này và tiếp tục mở rộng ô 2 1 để duyệt tìm B theo 
                thứ tự trên trái phải dưới đầu tiên là duyệt ô nằm trên ô 2 1 là ô 1 1 thì ô 1 1 k thõa đk là chưa đc
                thăm và khác ký tự x nên không truyền ô 1 1 vào lời gọi hàm DFS tiếp là đến duyệt ô bên trái của ô 2 1 ô bên trái của ô 2 1 là
                ô 2 0 thì ô 2 0 không thõa đk là nằm trong lưới ô vuông nên không đc truyền vào lời gọi hàm đệ quy DFS tiếp là duyệt đến ô bên
                phải của ô 2 1 ô bên phải của 2 1 là ô 2 2 mà ô 2 2 không thỏa đk là chưa đc thăm(vì ta duyệt và đánh dấu ô vừa thăm là cập nhật
                lại giá trị cho ô vừa thăm là x nên xét tới ô 2 2 này thì ô 2 2 đang là x tức là đã đc thăm) nên không truyền vào lời gọi hàm đệ
                quy DFS cuối cùng là duyệt đến ô nằm dưới ô 2 1 là ô 3 1 thì ô 3 1 cũng đã đc thăm nên không thõa đk để đc truyền vào lời gọi 
                hàm DFS vì ở ô 2 1 này đã duyệt đủ các ô xung quanh chung cạnh với ô 2 1 mà không có ô nào thõa đk nên trạng thái DFS của ô 2 1 
                lúc này đã xong và DFS(2,1) đc đẩy ra khỏi ngăn xếp thì ngăn xếp sau khi trạng thái của hàm DFS(2,1) đc hoàn thành là : DFS(3,1),
                DFS(4,1),DFS(4,2),DFS(4,3),DFS(3,3),DFS(3,4),DFS(3,5),DFS(3,6),DFS(2,6), DFS(2,5), DFS(2,4), DFS(2,3), DFS(1,3),DFS(1,2),DFS(1,1).
                Như ta thấy danh sách ngăn xếp sau khi trạng thái của hàm DFS(2,1) đã hoàn thành và đc lấy ra khỏi ngăn xếp thì lúc này nó sẽ quay
                lui về hàm mang trạng thái ở đầu ngăn xếp tức là lấy trạng thái ở đầu ngăn xếp là DFS(3,1) ra để duyệt các các ô xung quanh chung
                cạnh với ô 3 1 thì ở hàm DFS mang trạng thái ô 3 1 cũng tương tự như hàm DFS mang trạng thái của ô 2 1 nên hàm DFS mang trạng thái
                ô 3 1 cũng hoàn thành và đẩy ra khỏi ngăn xếp thì danh sách sau khi lấy trạng thái ở đầu danh sách(là DFS(3,1)) ra của lần quay
                lui từ 2 1 về 3 1 lúc này là : DFS(4,1),DFS(4,2),DFS(4,3),DFS(3,3),DFS(3,4),DFS(3,5),DFS(3,6),DFS(2,6), DFS(2,5), DFS(2,4),
                DFS(2,3), DFS(1,3),DFS(1,2),DFS(1,1). Như ta thấy danh sách ngăn xếp sau khi trạng thái của hàm DFS(3,1) đã hoàn thành và đc lấy 
                ra khỏi ngăn xếp thì lúc này nó sẽ quay lui về hàm mang trạng thái ở đầu ngăn xếp tức là lấy trạng thái ở đầu ngăn xếp là
                DFS(4,1) ra để duyệt các các ô xung quanh chung cạnh với ô 4 1 đầu tiên là trên ô 4 1 là ô 3 1 đã đc thăm k thõa đk, tiếp là ô
                bên trái ô 4 1 là ô 4 0 thì ô 4 0 không nằm trong lưới ô vuông không thõa đk, tiếp là ô bên phải của ô 4 1 là ô 4 2 thì ô 4 2
                đã đc thăm nên không thõa đk cuối cùng là ô 5 1 thì ô 5 1 lúc này thõa đk của của ô 4 1 khi mở rộng ra duyệt là nằm trong lưới
                ô vuông và chưa đc thăm(vì ta duyệt và xét 1 ô có đc thăm hay chưa bằng cách xem nó có khác ký tự x không nếu khác là chưa đc
                thăm còn không là đc thăm rồi chứ k phải dùng mảng visited đánh dấu true false ) thì lúc này ô 5 1 đc truyên vào lời gọi hàm đệ
                quy DFS và hàm DFS mang trạng thái của ô 5 1 đc thêm vào đầu ngăn xếp nên danh sách ngăn xếp của ta lúc này: DFS(5,1), DFS(4,1),
                DFS(4,2), DFS(4,3),DFS(3,3),DFS(3,4),DFS(3,5),DFS(3,6),DFS(2,6), DFS(2,5), DFS(2,4), DFS(2,3), DFS(1,3),DFS(1,2),DFS(1,1).Sau
                khi truyền giá trị của ô 5 1 vào lời gọi hàm đệ quy DFS thì lúc này hàm DFS sẽ xét giá trị của ô 5 1 có là B không thì giá trị
                của ô 5 1 lúc này là B nên trả về cho hàm mang trạng thái của ô 5 1 là true lặp tức dừng việc mở rộng ô 5 1 để duyệt các ô xung
                quanh chung cạnh với ô 5 1 lại và nó sẽ quay lui lại và truyền giá trị true cho mõi lần quay lui về tức lấy trạng thái của của
                DFS ở đầu danh sách ngăn xếp ra xét là nếu giá trị con của lần quay lui này mà là true thì thằng mà đang quay lui về cũng đc 
                trả về true luôn cụ thể quay lui về hàm ở đầu danh sách ngăn xếp là hàm mang trạng thái của ô 4 1 tức là DFS(4,1) thì hàm 
                DFS(4,1) nó xét thằng con của nó mở rộng ơ trong danh sách ngăn xếp có đang là true hay không nếu con của ô 4 1 là true thì
                hàm mang trạng thái ô 4 1 cũng đc truyền về giá trị là true thì ô con mà đc ô 4 1 mở rộng ra xét để thăm ở trong ngăn xếp lúc 
                này là hàm mnag trạng thái ô 5 1 thì hàm mang trạng trạng thái ô 5 1 đã là true nên thõa đk if (DFS(i1, j1))(i1 j1 là ô con 
                của hàm i j chứa hàm đệ quy tức hàm cha lúc này là 4 1 chứa hàm đệ quy là 5 1) nên DFS(5,1) là true đã thõa đk nên hàm chứa 
                hàm đệ quy của ô 5 1 này là DFS(4,1) cũng đc trả về true luôn. Sau khi DFS(4,1) đc trả về true thì DFS(5,1) đc đẩy ra khỏi ngăn
                xếp và quay lui về hàm mang trạng thái của ô 4 2 sẽ xét if mà hàm con của 4 2 mà true thì thì 4 2 cũng trả về true thì con
                của hàm DFS(4, 2) là DFS(4,1) mà DFS(4,1) đang là true nên thõa đk nên hàm mang trạng thái 4 2 cũng đc trả về là true cứ như thế
                cho đến khi tất cả các trạng thái của hàm DFS đc trả về true hết thì hàm DFS này là true tức là từ điểm ở đầu đường đi là điểm
                A tới điểm ở cuối đường đi là điểm B có đường đi */
                              
                    return true;   


            }
            }
        return false;/*Nếu nhánh của i1 j1 không đi đc đến ký tự B thì trả về false chỉ trả về false thôi chứ chưa đc kết luận là chưa có đường
        đi vì i1 j1 chỉ là 1 cái nhánh DFS thôi chứ không phải toàn bộ*/
    }

    bool BFS(int i, int j) {
        queue<pair<int, int>> q;

        q.push({ i,j });
        a[i][j] = 'x';
        cout << i << " " << j << "\n";
        while (!q.empty())
        {

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
                if (i1 >= 1 && i1 <= n && j1 >= 1 && j1 <= m && a[i1][j1] != 'x')
                {
                    cout << i1 << " " << j1 << "\n";
                    if (a[i1][j1] == 'B') {
                        return true;
                    }
                    q.push({ i1,j1 });
                    a[i1][j1] = 'x';

                }
            }

        }

        return false;
    }

    void inp() {
        cout << "Nhap vao n cot va m hang cua luoi o vuong : \n";
        cin >> n >> m;

        cout << "Nhap vao gia tri cua cap i j trong luoi o vuong: \n";
        for (short i = 1; i <= n; i++)
        {
            for (short j = 1; j <= m; j++) {
                cout << i << " " << j << " = ";
                cin >> a[i][j];
                if (a[i][j] == 'A') {/*Kiểm tra nếu cặp i j là điểm bắt đầu của đường đi thì ta cho x1 giữ giá trị của i và y1 giữ giá trị của
                 j tức x1 và y1 đang mang tọa độ của điểm đầu đường đi*/


                    s = i;
                    t = j;
                }
            }
        }

        cout << "\nLuoi o vuong sau khi nhap: \n";
        for (short i = 1; i <= n; i++)
        {
            for (short j = 1; j <= m; j++) {
                cout << a[i][j] << " ";
            }
            cout << "\n";
        }

         cout << "\nTu A den B theo thuat toan DFS thi co duong di nhu sau: \n ";
       // cout << "\nTu A den B theo thuat toan BFS thi co duong di nhu sau: \n ";
        if (DFS(s, t))/*Kiểm tra nếu truyền vào s t tức là giá trị của cặp i j đầu đường đi và duyệt từ điểm ở đầu đường đi mà tới đc điểm
                     ở cuối đường đi thì kết luận từ điểm ở đầu đường đi đến điểm ở cuối đường đi là có đường đi. Vì ở hàm inp này trong 
                     lúc nhập giá trị của cặp i và j cho lưới ô vuông hay còn gọi là ma trận kề của đồ thị thì ta đã cho bắt trường hợp 
                     giá trị nào mà là đầu đường đi(giá trị đầu đường đi là 'A') thì ta cho biến s(là lưu giá trị của i) và t(là lưu giá
                     trị của j) để lưu lại cặp i và j mang giá trị đầu đường đi thì lúc này s và t đang lưu giá trị đầu đường đi(là 'A')
                     trong lưới ô vuông sau đó ta truyền s và t vào cho hàm DFS hoặc BFS để duyệt từ điểm ở đầu đường đi(là điểm A) mà 
                     hàm BFS và DFS ta cho kiểu bool nên khi ta cho duyệt các cạnh chung xung quanh khi bắt đầu từ điểm ở đầu đường đi
                     thì những ô nào mà khác x thì là đường đi cho đến khi gặp đc điểm ở cuối đường đi là 'B' thì ta trả về cho hàm là 
                     true còn duyệt không thấy điểm cuối đường đi(là điểm B) thì ta trả về cho hàm là false nên dk  if (DFS(s,t)) hoặc 
                     if (BFS(s,t)) là nếu DFS hoặc BFS trả về là true thì kết luận là từ điểm A đến điểm B có đường đi ngược lại !DFS(s,
                     t)) !BFS(s, t)) như thế này thì từ điểm A đến điểm B không có đường đi. 
                     */
        {
            cout << "\nTu diem A den diem B trong do thi co duong di\n";
        }
        else
        {
            cout << "\nTu diem A den diem B trong do thi khong co duong di\n";
        }
    }

    int main() {
        inp();
    }
#endif // 0






