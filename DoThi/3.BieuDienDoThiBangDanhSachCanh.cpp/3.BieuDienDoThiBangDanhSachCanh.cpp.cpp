//======================= ĐỒ THỊ VÔ HƯỚNG ======================
#if 0
#include <iostream>
#include<vector>
using namespace std;
/*Bài 3: Ma trận kề sang danh sách cạnh
Cho đồ thị vô hướng G = < V,E > Được biểu diễn dưới dạng Ma trận kề. Hãy viết chương trình thực hiện chuyển
đổi biểu diễn đồ thị dưới dạng danh sách cạnh.HÌNH BÀI 3 NÀY Ở TRONG VỞ CỦA BÀI 7 PHẦN 2 LA MÃ
Input: + Dòng đầu tiên chứa 1 số n là số đỉnh của đồ thị. (1 <= n <= 1000)
       + N dòng tiếp theo theo mõi dòng N số biểu diễn ma trận kề của đồ thị.
Out: In ra danh sách cạnh tương ứng theo thứ tự đỉnh đầu tăng dần
ví dụ: Bảng input là dữ liệu của ma trận kề ta nhập vào để output tức là từ ma trận kề chuyển sang danh sách cạnh, 5 là số
đỉnh của đô thị ta cho vòng lặp chạy từ 1 tới 5 tức là 5 đỉnh 1 2 3 4 5 
+--------------------------------------------------+
|       Input              Output                  |
+--------------------------------------------------+
|        5           |       1 2                   |
|        0 1 1 1 0   |       1 3                   | 
|        1 0 1 1 1   |       1 4                   | 
|        1 1 0 1 1   |       2 3                   | 
|        1 1 1 0 1   |       2 4                   | 
|        0 1 1 1 0   |       2 5                   | 
|                    |       3 4                   |
|                    |       3 5                   | 
|                    |       4 5                   |
|                    |                             |
+--------------------------------------------------+

- Chuyển ma trận kề sang danh sách cạnh trong trường hợp input là danh sách cạnh thì nó chỉ cần biết số lượng đỉnh(n) thôi
vì từ ma trận kề ta cũng có thể biết có bao nhiêu cạnh tức là ta xét lần lượt các hàng và cột của 5 đỉnh từ 1 2 3 4 5 của
ma trận kề nếu là cặp đỉnh tạo nên cạnh của đồ thị thì là 1 còn 0 tức là cặp đỉnh đó không phải là cạnh. Tức là khi nào đề
bài cho intput là danh sách cạnh thì ta mới cần khái báo số cạnh(m) còn nếu cho ma trận kề thì ta chỉ cần biết số đỉnh(n)
thôi 
   
    1 2 3 4 5
    __________
  1 |0 1 1 1 0| => nghĩa là 1 nối với 1 không là cạnh nên là 0, còn 1 nối với 2 là cạnh nên là 1.... Cứ như vậy mà xét
  2 |1 0 1 1 1| => Vì là đồ thị vô hướng nên 2 nối với 1 cũng là 1 nối với 2 cũng là cạnh cạnh kề 1 với 5 ko là cạnh 
  3 |1 1 0 1 1| vì ta không nhập cặp đỉnh 1 với 5 tạo thành cạnh nên 1 với 5 mang giá trị là không
  4 |1 1 1 0 1|
  5 |0 1 1 1 0| 


Vì là đồ thị vô hướng nên 1 nối với 2 cũng là cạnh mà 2 nối với 1 cũng là cạnh nên khi đó ở đây là từ ma trận kề 
ta chuyển sang danh sách cạnh ta chỉ cần liệt kê cặp cạnh mà có đỉnh đầu nhỏ hơn đỉnh cuối mà thôi tức là 1 với 2
là 1 cạnh thì ta thêm 1 2 vào danh sách cạnh và nhìn vào ma trận ta cũng biết đc có bao nhiêu cạnh nên ta chỉ thêm
cặp đỉnh tạo thành cạnh mà có đỉnh đầu nhỏ hơn đỉnh cuối thôi tức là 2 1 cũng là cạnh nhưng ta không liệt kê vào 
danh sách cạnh vì cạnh 1 2 với cạnh 2 1 là 1 nên ta chỉ thêm cặp đỉnh tạo thành cạnh mà có đỉnh đầu nhỏ hơn đỉnh 
cuối thôi*/

int n;
int a[1001][1001];//Lưu trữ danh sách cách cặp đỉnh tạo thành cạnh của đồ thị
vector<pair<int,int>> egde;/*Tạo ra 1 vector egde để lưu tất cả các cặp đỉnh tạo thành cạnh của đồ thị. Tức là 
vector egde chứa các phần tử kiểu pair<int, int>( pair Là một cặp giá trị nguyên(int) được đóng gói lại thành một
đối tượng dữ liệu duy nhất là pair. Mỗi pair có hai thành phần mõi thành phần là kiểu int ví dụ khi ta nhập vào 2 
đỉnh tạo thành cạnh của đồ thị thì khi push_back vào vector egde lưu dữ liệu với kiểu pair<int,int> thì khi đó ta
sẽ đưa các cặp đỉnh mà đã nhập vào thành kiểu pair<int,int> tức là mõi 1 phần tử trong vector egde là 1 cặp đỉnh
ví dụ ta thêm cặp đỉnh i = 1 và j = 2 vào vector egde thì danh sách ta lúc này phần tử đầu tiên là 1 cặp đỉnh 1 2  ) */
int main()
{
    
    cout << "Nhap vao n so dinh cua do thi: ";
    cin >> n;

    //Nhập ma trận kề các cạnh của đồ thị
     cout << "Nhap gia tri 0(i va j khong noi voi nhau thanh canh) va 1(i va j noi voi nhau thanh canh) ";
     cout<<"\ncac canh cua do thi cho ma tran ke : \n";
    for (short i = 1; i <= n; i++){
        for (short j = 1; j <= n; j++) {
            cout << i << " " << j<<" = ";
            cin >> a[i][j];
       /*Khi nhập và n(là số đỉnh của của đồ thị là 5) thì ở 2 vòng lặp này thực thi như sau cho i và j chạy từ 1 đến
       n là từ 1 đến 5 
       - đầu tiên i = 1 và j = 1 
       + ta nhập a[i][j] là a[1][1] = 0 => cặp đỉnh 1 với 1 không tạo thành cạnh nên ở điều kiện của Chuyển từ ma trận kề 
       sang danh sách cạnh là  if (a[i][j] == 1 &&  i < j) thì nó không thỏa mãn a[i][j] == 1 tức là a[1][1] == 1 vì a[1][1]
       của ta lúc này bằng nhập vào là 0 
       - Tiếp theo i = 1 và j = 2 
       + ta nhập a[i][j] là a[1][2] = 1 => cặp đỉnh 1 với 2  tạo thành cạnh nên ở điều kiện của Chuyển từ ma trận kề sang 
       danh sách cạnh là if (a[i][j] == 1 &&  i < j) thì nó  thỏa mãn a[i][j] == 1 tức là a[1][2] == 1 vì a[1][2] của ta 
       lúc này bằng nhập vào là 1 nên khối lệnh trong điều kiện if là  egde.push_back({i, j}); được thực thi tức là danh 
       sách cạnh là egde của ta lúc này đã thêm(push_back({i, j})) cặp đỉnh 1 và 2 tạo thành cạnh của đồ thị vào danh sách
       ...Tương tự cho mõi lần nhập các phần tử của ma trận kề ở bảng intPut ở trên cho đến khi 2 vòng lặp(là nhập giá trị
       0 là hai đỉnh i và j không là cạnh ngược lại 1 thì cặp đỉnh i và j là cạnh) dừng lại vì là ta nhập n bằng 5 nên vòng
       2 vòng lặp i và j sẽ chạy từ 1 cho đến 5 thì dùng lại tức ta phải nhập 25 lần tương ứng với 5 đỉnh của đồ thị*/
        }
    }

    //Xuất ma trận kề sau khi nhập giá trị 0 và 1 của các cặp đỉnh của đồ thị
    cout << "Ma tran ke sau khi nhap cac gia tri 0 va 1: \n";
    for (short i = 1; i <= n; i++)
    {
        for (short j = 1; j <= n; j++) {
            cout << a[i][j]<<" ";
        }
        cout << "\n";
    }

    //Chuyển từ ma trận kề sang danh sách cạnh 
    cout << "Danh sach canh duoc chuuyen tu ma tran ke gom cac canh : \n";
    for (short i = 1; i <= n ; i++)
    {
        for (short j = 1; j <= n; j++) {
            if (a[i][j] == 1 &&  i< j) {/*Kiểm tra nếu a[i][j] mà bằng 1 chứng tỏ đỉnh j và j nối với nhau và tạo thành
                cạnh của đồ thị. Chú ý đây là đồ thị vô hướng vì vậy nếu a[i][j] mà bằng 1 thì tức là 1 cạnh của đồ thị.
                Nhưng nếu mà ta push_Back 2 đỉnh i và j tức là 2 đỉnh tạo thành 1 cạnh của đồ thị thì sẽ có trường hợp 
                nếu ta duyệt qua ma trận ở hàng 1 và cột 4 tức là a[1][4] thì khi đó a[1][4] = 1 thì ta sẽ push_back(1
                ,4) vào danh sách cạnh kề(egde) và khi ta duyệt qua duyệt qua ma trận ở hàng 4 và cột 1 tức là a[4][1] 
                thì khi đó ta cho cạnh 4 1 và danh sách cạnh kề(egde) mà 2 cạnh {1 4} và {4 1}  là 1  mà theo quy ước ta
                chỉ liệt kê các danh sách cạnh mà đỉnh đầu nhỏ hơn đỉnh thứ 2 thôi nên ngoài điều kiện kiểm tra a[i][j]
                == 1 ra ta còn phải thêm đk i < j để không bị thừa cạnh*/

                egde.push_back({i, j});/*Ta đã có tạo ra 1 vector là egde để chứa các cạnh của đồ thị. Nên khi cặp đỉnh
                i và j tức là a[i][j] == 1 và i < j là tạo thành cạnh của đồ thị thì ta push_back(thêm vào cuối) vào danh
                sách(vector) egde mà ta đã tạo. */

            }
        }
    }

    //Xuất danh sách cạnh sau khi chuyển ma trận kề sang danh sách cạnh
    for (auto it : egde) {/*Đây là 1 vòng lặp giống y chang là vòng lặp for each bên java gọi vòng lặp này là vòng lặp dựa
        trên phạm vi. Nó được sử dụng để duyệt qua các phần tử của một dãy hoặc container như một vector, mảng, hoặc bất kỳ
        dạng dữ liệu nào hỗ trợ iterator.
        => Cách vòng lặp này hoạt động: 
        - Vòng lặp này tự động lấy mỗi phần tử từ edge một lần lượt và gán giá trị của phần tử đó cho biến it. Sau đó Vòng
        lặp sẽ thực hiện các lệnh bên trong khối vòng lặp cho mỗi phần tử trong edge Khi tất cả các phần tử đã được duyệt
        qua, vòng lặp tự động kết thúc.*/ 
        cout << it.first << " " << it.second<<"\n";/*Tức là chỉ in ra phần tử đầu là đỉnh đầu(it.first) và phần tử thứ 2
        là đỉnh cuối(it.second) các cạnh kề của đồ thị mà thôi tức là chuyển ma trận sang danh sách cạnh khi ta đưa các cặp
        đỉnh là cạnh kề của đồ thị vào trong danh sách cạnh(vector) egde thì đây là in ra danh danh sách cạnh với đỉnh đầu 
        và đỉnh cuối tạo thành cạnh của danh sách cạnh egde.*/
    }

}
#endif // 0

//============ ĐỒ THỊ CÓ HƯỚNG ==========================
#if 0
#include<iostream>
#include<vector>
using namespace std;
/*Bài 3: Ma trận kề sang danh sách cạnh
Cho đồ thị có hướng G = < V,E > Được biểu diễn dưới dạng Ma trận kề. Hãy viết chương trình thực hiện chuyển
đổi biểu diễn đồ thị dưới dạng danh sách cạnh.HÌNH BÀI 2 NÀY Ở TRONG VỞ CỦA BÀI 7 PHẦN 2 LA MÃ
Input: + Dòng đầu tiên chứa 1 số n là số đỉnh của đồ thị. (1 <= n <= 1000)
       + N dòng tiếp theo theo mõi dòng N số biểu diễn ma trận kề của đồ thị.
Out: In ra danh sách cạnh tương ứng theo thứ tự đỉnh đầu tăng dần
ví dụ: Bảng input là dữ liệu của ma trận kề ta nhập vào để output tức là từ ma trận kề chuyển sang danh sách cạnh, 5 là số
đỉnh của đô thị ta cho vòng lặp chạy từ 1 tới 5 tức là 5 đỉnh 1 2 3 4 5
+--------------------------------------------------+
|       Input              Output                  |
+--------------------------------------------------+
|        5           |       1 2                   |
|        0 1 1 1 0   |       1 3                   |
|        0 0 1 1 1   |       1 4                   |
|        0 0 0 1 1   |       2 3                   |
|        0 0 0 0 1   |       2 4                   |
|        0 0 0 0 0   |       2 5                   |
|                    |       3 4                   |
|                    |       3 5                   |
|                    |       4 5                   |
|                    |                             |
+--------------------------------------------------+

- Chuyển ma trận kề sang danh sách cạnh trong trường hợp input là danh sách cạnh thì nó chỉ cần biết số lượng đỉnh(n) thôi
vì từ ma trận kề ta cũng có thể biết có bao nhiêu cạnh tức là ta xét lần lượt các hàng và cột của 5 đỉnh từ 1 2 3 4 5 của
ma trận kề nếu là cặp đỉnh tạo nên cạnh của đồ thị thì là 1 còn 0 tức là cặp đỉnh đó không phải là cạnh. Tức là khi nào đề
bài cho intput là danh sách cạnh thì ta mới cần khái báo số cạnh(m) còn nếu cho ma trận kề thì ta chỉ cần biết số đỉnh(n)
thôi

    1 2 3 4 5
    __________
  1 |0 1 1 1 0| => nghĩa là 1 nối với 1 không là cạnh nên là 0, còn 1 nối với 2 là cạnh nên là 1.... Cứ như vậy mà xét từng hàng
  2 |0 0 1 1 1| và từng cột vì đây là ma trận 
  3 |0 0 0 1 1| => Vì là đồ thị có hướng nên 1 nối với 2 là cạnh cạnh kề theo hướng đỉnh đầu nối với đỉnh cuối chứ không được 
  4 |0 0 0 0 1| đảo hướng tức 2 với 1 không là cạnh kề giống đồ thị vô hướng được
  5 |0 0 0 0 0|


Vì là đồ thị có hướng nên 1 cạnh kề của đồ thị chỉ được tạo theo hướng từ đỉnh đầu đến đỉnh cuối mà thôi tức là cặp đỉnh 1 2 là 
cạnh của đồ thị theo hướng đỉnh 1 nối tới đỉnh 2 và không thể đảo hướng lại theo hướng ngược lại 2 nối tới 1 giống đồ thị vô hướng 
được......*/
int n;
int a[10001][1001];
vector<pair<int, int>> egde;
int main() {
    cout << "Nhap vao so dinh n: ";
    cin >> n;
    cout << "Nhap gia tri 0(i va j khong noi voi nhau thanh canh) va 1(i va j noi voi nhau thanh canh) ";
    cout << "\ncac canh cua do thi cho ma tran ke : \n";
    for (short i = 1; i <= n; i++) {
        for (short j = 1; j <= n; j++) {
            cout << i << " " << j << " = ";
                cin >> a[i][j];

                if (a[i][j] == 1)/*vì là đồ thị có hướng nên quan trọng là cách nhập giá trị 0 và 1 của các cặp đỉnh có tạo thành
                    cạnh kề của đồ thị trong ma trận kề nếu cặp đỉnh mà tạo thành cạnh của đồ thị thì ta nhập là 1 ngược lại các
                    cặp đỉnh không tạo thành cạnh của đồ thị thì ta nhập 0 thì input ta đã có ở đề bài*/
                {
                    egde.push_back({ i,j });
                }
        }
    }

    cout << "Danh sach canh sau khi duoc chuyen tu ma tran ke: \n";
    for (auto it : egde) {
        cout << it.first << " " << it.second << "\n";
    }

}



#endif // 0





        

