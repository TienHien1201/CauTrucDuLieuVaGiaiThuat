//======================== ĐỒ THỊ VÔ HƯỚNG =================================
#if 0
#include <iostream>
#include<vector>
#include<string>
#include<sstream>
using namespace std;
/*Bài 5: danh sách kề sang Ma trận kề
Cho đồ thị vô hướng G = < V,E > Được biểu diễn dưới dạng danh sách kề. Hãy viết chương trình thực hiện chuyển
đổi biểu diễn đồ thị dưới dạng Ma trận kề. HÌNH BÀI 2 NÀY Ở TRONG VỞ CỦA BÀI 7 PHẦN 2 LA MÃ
Input: + Dòng đầu tiên chứa 1 số n là số đỉnh của đồ thị. (1 <= n <= 1000)
       + N dòng tiếp theo theo, mõi dòng là danh sách kề của các đỉnh từ 1 tới đỉnh n.
Out: In ra ma trận kề tương ứng 
ví dụ: Bảng input là dữ liệu của ma trận kề ta nhập vào để output tức là từ ma trận kề chuyển sang danh sách cạnh, 5 là số
đỉnh của đô thị ta cho vòng lặp chạy từ 1 tới 5 tức là 5 đỉnh 1 2 3 4 5
+--------------------------------------------------+
|       Input              Output                  |
+--------------------------------------------------+
|        5           |       0 1 1 1 0             |
|       1: 2 3 4     |       1 0 1 1 1             | => Ở input ta chỉ nhập vào chuỗi là 2 3 4 thôi 1: là bản thân tự ký hiệu
|       2: 1 3 4 5   |       1 1 0 1 1             | để khi xem lại bài ta hiểu chuỗi  2 3 4 là các đỉnh nằm trong danh sách 
|       3: 1 2 4 5   |       1 1 1 0 1             | cạnh kề với đỉnh 1. Tương tự các dòng bên dưới cũng vậy
|       4: 1 2 3 5   |       0 1 1 1 0             |
|       5: 2 3 4     |                             |
|                    |                             |
|                    |                             |
|                    |                             |
|                    |                             |
+--------------------------------------------------+

- Chuyển danh sách kề sang ma trận kề trong trường hợp input là danh sách kề thì nó chỉ cần biết số lượng đỉnh(n) thôi.Tức là
khi nào đề bài cho intput là danh sách cạnh thì ta mới cần khái báo số cạnh(m) còn nếu cho ma trận kề thì ta chỉ cần biết số
đỉnh(n) thôi

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
vector< int> adj[1000];/*Tạo ra 1 vector adj[i] : Lưu danh sách kề của đỉnh i*/
int main()
{
    cout << "Nhap vao n so dinh cua do thi: ";
    cin >> n;
    cin.ignore();
    for (short i = 1; i <= n; i++){
        string s, num;/*Chuỗi s chính là là các đỉnh kề với i tức là các đỉnh nối với i tạo thành cạnh kề gọi là danh sách cạnh
        kề với đỉnh i, còn num dùng để lưu trữ giá trị từ chuỗi s khi ta đọc dữ liệu từ ss.*/
        cout << "Nhap vao danh sach cac dinh noi voi dinh " << i << " tao tanh canh ke: ";
        getline(cin, s);/*Nhập chuỗi các đỉnh là cạnh kề với đỉnh i 
        ví dụ: ta nhập là n = 5 tức là đồ thị này có 5 đỉnh vòng lặp chạy từ 1 đến n tức là từ đỉnh 1 đến đỉnh thứ 5
        - Đầu tiên đỉnh i = 1 thì ta nhập vào chuỗi s là các đỉnh là cạnh kề với 1 gồm 2 3 4(các đỉnh là cạnh kề ở trên input
        của đề bài)  */
        stringstream ss(s);/*Tạo ra biến ss thuộc stringstream sử dụng để biến đổi chuỗi s thành một luồng đầu vào để ta có thể
        đọc lần lượt các phần tử trong chuỗi s sau mỗi lần đọc, con trỏ trong luồng đầu vào ss sẽ tự động di chuyển đến vị trí 
        tiếp theo trong chuỗi s, cho phép bạn đọc lần lượt các phần tử trong chuỗi một cách tuần tự */
        while (ss >> num){/*Trong vòng lặp này, ss sẽ đọc từ chuỗi s và gán từng giá trị đọc đc vào biến num, khi không còn dữ 
        liệu để đọc, vòng lặp sẽ kết thúc. Mõi lần đọc đc số thì số đó đang là 1 chuỗi thì ta sẽ biết đc dòng thứ i(là vòng lặp 
        for và i là đỉnh đầu nối với từng giá trị của biến num sau khi đc ss đọc để tạo thành cạnh kề của đồ thị khi đó ta có danh 
        sách kề mang đỉnh i với các đỉnh là giá trị đc ss đọc từ num nối với i để tạo thành cạnh kề) này có 1 cái đỉnh kề với nó
        với giá trị là num.
        - Ví dụ: sau vòng lặp này, num sẽ chứa các giá trị lần lượt 2, rồi tới 3, cuối cùng là 4 khi biến ss đọc hết các phần tử
        trong chuỗi s thì vòng lặp while này dừng lại.*/
        
            a[i][stoi(num)] = 1;/*stoi chuyển chuỗi num thành từng số. Ví dụ ta nhập vào 1 chuỗi là 2 3 4 các đỉnh là cạnh kề
            với đỉnh 1(vì vòng lặp for đầu tiên thì i = 1) nên khi xuống tới đây thì vòng lặp while lại cắt chuỗi (bằng lệnh 
            ss >> num) các đỉnh(2 3 4) là cạnh kề với đỉnh 1(i) và stoi tức chuyển từng phần tử sau khi được cắt trong chuỗi 
            tức là 2 rồi tới 3 rồi tới 4 thành kiểu số và a[i][stoi(num)] = 1 mà i đang bằng 1 và stoi(num) là qua bước cắt 
            từ phần tử trong chuỗi tới stoi(num) là chuyển phần tử vừa được cắt của chuỗi ra thành kiểu số và số đầu tiên trong
            chuỗi 2 3 4 là số 2 nên tức là a[1][2] = 1, bây giờ chuỗi num còn lại 3 và 4 thì tương tự như số 2, tiếp là tới 3 
            được cắt từ chuỗi và chuyển 3 thành kiểu số nên tức là a[1][3] = 1, bây giờ chuỗi num chỉ còn lại 4 thì cũng được
            chuyển thành kiểu số nên tức là a[1][4] = 1.
            ....................cứ thế khi ta nhập chuỗi các đỉnh nối với đỉnh i tạo thành cạnh kề và mõi lần vòng lặp for chạy 
            thì i tăng lên 1 đơn vị tức là i chạy từ 1 tới 5 tương đương với 5 đỉnh của đồ thị và mõi 1 đỉnh đầu(đỉnh đầu là i)
            của vòng lặp là danh sách các cạnh nối với i tạo thành cạnh kề ví dụ cụ thể cho dễ hiểu về mõi đỉnh i của vòng lặp 
            for là danh sách các cạnh nối với i tạo thành cạnh kề: 
            - Đầu tiên i = 1 
            + mà ở trên input của đề bài thì các cạnh nối với với đỉnh 1 tạo thành cạnh kề bao gồm các đỉnh 2 3 4 danh sách cạnh
            kề của đỉnh 1 bây giờ là 1 : 2 3 4 tức là 1 là đỉnh đầu nối với 2 tạo thành cạnh kề của đồ thị, 1 là đỉnh đầu nối với
            3 tạo thành cạnh kề của đồ thị, 1 là đỉnh đầu nối với 4 tạo thành cạnh kề của đồ thị, thì sau khi qua các bước cắt 
            chuỗi thì cách phần tử trong chuỗi nối với đỉnh đầu i tạo thành cạnh kề của đồ thị thì ta cho bằng 1 tức 
            là a[1][2] = 1, a[1][3] = 1, a[1][4] = 1 để tạo thành các phần tử của ma trận kề đúng với yêu cầu của đề bài là 
            chuyển danh sách kề sang ma trận kề............ */
        }
    }

    //In ma trận kề sau khi được chuyển từ danh sách kề
    cout << "\nMa tran ke sau khi duoc chuyen tu danh sach ke: \n";
    for (short i = 1; i <= n; i++)
    {
        for (short j = 1; j <= n; j++) {
            cout << a[i][j] << " ";
        }
        cout << "\n";
    }
}

#endif // 0

//====================== ĐỒ THỊ CÓ HƯỚNG ============================
#if 0
#include<iostream>
#include<vector>
#include<string>
#include<sstream>
using namespace std;
/*Bài 5: danh sách kề sang Ma trận kề
Cho đồ thị có hướng G = < V,E > Được biểu diễn dưới dạng danh sách kề. Hãy viết chương trình thực hiện chuyển
đổi biểu diễn đồ thị dưới dạng Ma trận kề. HÌNH BÀI 5 NÀY Ở TRONG VỞ CỦA BÀI 7 PHẦN 2 LA MÃ
Input: + Dòng đầu tiên chứa 1 số n là số đỉnh của đồ thị. (1 <= n <= 1000)
       + N dòng tiếp theo theo, mõi dòng là danh sách kề của các đỉnh từ 1 tới đỉnh n.
Out: In ra ma trận kề tương ứng
ví dụ: Bảng input là dữ liệu của ma trận kề ta nhập vào để output tức là từ ma trận kề chuyển sang danh sách cạnh, 5 là số
đỉnh của đô thị ta cho vòng lặp chạy từ 1 tới 5 tức là 5 đỉnh 1 2 3 4 5
+--------------------------------------------------+
|       Input              Output                  |
+--------------------------------------------------+
|        5           |       0 1 1 1 0             |
|       1: 2 3 4     |       0 0 1 1 1             | => Ở input ta chỉ nhập vào chuỗi là 2 3 4 thôi 1: là bản thân tự ký hiệu
|       2: 3 4 5     |       0 0 0 1 1             | để khi xem lại bài ta hiểu chuỗi  2 3 4 là các đỉnh nằm trong danh sách
|       3: 4 5       |       0 0 0 0 1             | cạnh kề với đỉnh 1. Tương tự các dòng bên dưới cũng vậy
|       4: 5         |       0 0 0 0 0             |
|       5:           |                             |
|                    |                             |
|                    |                             |
|                    |                             |
|                    |                             |
+--------------------------------------------------+

- Chuyển danh sách kề sang ma trận kề trong trường hợp input là danh sách kề thì nó chỉ cần biết số lượng đỉnh(n) thôi.Tức là
khi nào đề bài cho intput là danh sách cạnh thì ta mới cần khái báo số cạnh(m) còn nếu cho ma trận kề thì ta chỉ cần biết số
đỉnh(n) thôi

    1 2 3 4 5
    __________
  1 |0 1 1 1 0| => nghĩa là 1 nối với 1 không là cạnh nên là 0, còn 1 nối với 2 là cạnh nên là 1.... Cứ như vậy mà xét
  2 |0 0 1 1 1| => Vì là đồ thị vô hướng nên 2 nối với 1 cũng là 1 nối với 2 cũng là cạnh cạnh kề 1 với 5 ko là cạnh
  3 |0 0 0 1 1| vì ta không nhập cặp đỉnh 1 với 5 tạo thành cạnh nên 1 với 5 mang giá trị là không
  4 |0 0 0 0 1|
  5 |0 0 0 0 0|


Vì là đồ thị có hướng nên 1 cạnh kề của đồ thị chỉ được tạo theo hướng từ đỉnh đầu đến đỉnh cuối mà thôi tức là cặp đỉnh 1 2 là
cạnh của đồ thị theo hướng đỉnh 1 nối tới đỉnh 2 và không thể đảo hướng lại theo hướng ngược lại 2 nối tới 1 giống đồ thị vô hướng
được......*/

int n;
int a[1001][1001];//Lưu trữ danh sách cách cặp đỉnh tạo thành cạnh của đồ thị
vector<int> adj[1001];/*Tạo ra 1 vector adj[i] : Lưu danh sách kề của đỉnh i*/
int main() {
    cout << "Nhap vao so dinh n cua do thi: ";
    cin >> n;
    cin.ignore();

    cout << "Nhap danh sach ke:  \n";
    for (short i = 1; i <= n; i++)
    {
        string s, num;
        cout << i << " : ";
        getline(cin, s);/*Đối với chuyển danh sách kề sang ma trận kề của đồ thị có hướng cũng cách code và xử lý giống đồ thị vô 
        hướng chỉ khác là đồ thị có hướng thì cặp đỉnh tạo thành 1 cạnh của đồ thị nó sẽ theo hướng từ đỉnh đầu đến đỉnh cuối và 
        không theo hướng ngược lại được ví 1 2 là cạnh của đồ thị có hướng theo hướng từ đỉnh đầu(1) đến đỉnh cuối(2) của đồ thị
        và không thể đảo ngược hướng lại là 2 1 được. Nên quan trọng input của đề ta nhập vào thôi chứ không có gì khác với đồ thị
        vô hướng.*/
        stringstream ss(s);
        while (ss >> num) {
            a[i][stoi(num)] = 1;

        }
    }

    cout << "\nMa tran ke sau khi duoc chuyen tu danh sach ke: \n";
    for (short i = 1; i <= n; i++)
    {
        for (short j = 1; j <= n; j++) {
            cout << a[i][j] << " ";
        }
        cout << "\n";
    }
}

#endif // 1



