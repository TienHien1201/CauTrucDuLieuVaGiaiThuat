#if 0
//=====================Đồ thị vô hướng===============================
#include <iostream>
#include<vector>
#include<string>
#include<sstream>
using namespace std;
/*Bài 6: danh sách kề sang danh sách cạnh
Cho đồ thị vô hướng G = < V,E > Được biểu diễn dưới dạng danh sách kề. Hãy viết chương trình thực hiện chuyển
đổi biểu diễn đồ thị dưới dạng danh sách cạnh. HÌNH BÀI 2 NÀY Ở TRONG VỞ CỦA BÀI 7 PHẦN 2 LA MÃ
Input: + Dòng đầu tiên chứa 1 số n là số đỉnh của đồ thị. (1 <= n <= 1000)
       + N dòng tiếp theo theo, mõi dòng là danh sách kề của các đỉnh từ 1 tới đỉnh n.
Out: In ra danh sách cạnh tương ứng
ví dụ: Bảng input là dữ liệu của ma trận kề ta nhập vào để output tức là từ ma trận kề chuyển sang danh sách cạnh, 5 là số
đỉnh của đô thị ta cho vòng lặp chạy từ 1 tới 5 tức là 5 đỉnh 1 2 3 4 5
+--------------------------------------------------+
|       Input              Output                  |
+--------------------------------------------------+
|        5           |       1 2                   |
|       1: 2 3 4     |       1 3                   | => Ở input ta chỉ nhập vào chuỗi là 2 3 4 thôi 1: là bản thân tự ký hiệu
|       2: 1 3 4 5   |       1 4                   | để khi xem lại bài ta hiểu chuỗi  2 3 4 là các đỉnh nằm trong danh sách
|       3: 1 2 4 5   |       2 3                   | cạnh kề với đỉnh 1. Tương tự các dòng bên dưới cũng vậy
|       4: 1 2 3 5   |       2 4                   |
|       5: 2 3 4     |       2 5                   |
|                    |       3 4                   |
|                    |       3 5                   |
|                    |       4 5                   |
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
vector <pair<int, int>> egde;/*Tạo ra 1 vector egde để lưu tất cả các cặp đỉnh tạo thành cạnh của đồ thị. Tức là 
vector egde chứa các phần tử kiểu pair<int, int>( pair Là một cặp giá trị nguyên(int) được đóng gói lại thành một
đối tượng dữ liệu duy nhất là pair. Mỗi pair có hai thành phần mõi thành phần là kiểu int ví dụ khi ta nhập vào 2 
đỉnh tạo thành cạnh của đồ thị thì khi push_back vào vector egde lưu dữ liệu với kiểu pair<int,int> thì khi đó ta
sẽ đưa các cặp đỉnh mà đã nhập vào thành kiểu pair<int,int> tức là mõi 1 phần tử trong vector egde là 1 cặp đỉnh
ví dụ ta thêm cặp đỉnh i = 1 và j = 2 vào vector egde thì danh sách ta lúc này phần tử đầu tiên là 1 cặp đỉnh 1 2 ) */
int main()
{
    cout << "Nhap vao n so dinh cua do thi: ";
    cin >> n;
    cin.ignore();
    for (short i = 1; i <= n; i++) {
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
        while (ss >> num) {/*Trong vòng lặp này, ss sẽ đọc từ chuỗi s và gán từng giá trị đọc đc vào biến num, khi không còn dữ
        liệu để đọc, vòng lặp sẽ kết thúc. Mõi lần đọc đc số thì số đó đang là 1 chuỗi thì ta sẽ biết đc dòng thứ i(là vòng lặp
        for và i là đỉnh đầu nối với từng giá trị của biến num sau khi đc ss đọc để tạo thành cạnh kề của đồ thị khi đó ta có danh
        sách kề mang đỉnh i với các đỉnh là giá trị đc ss đọc từ num nối với i để tạo thành cạnh kề) này có 1 cái đỉnh kề với nó
        với giá trị là num.
        - Ví dụ: sau vòng lặp này, num sẽ chứa các giá trị lần lượt 2, rồi tới 3, cuối cùng là 4 khi biến ss đọc hết các phần tử
        trong chuỗi s thì vòng lặp while này dừng lại.*/
            if (stoi(num) > i){/*Từ danh sách kề chuyển sang danh sách cạnh thì ta phải kiểm tra lần lượt các giá trị trong num( 
                các giá trị trong num tức là các các đỉnh nối với đỉnh i tạo thành các cạnh kề của đồ thị ) phải lớn hơn đỉnh i  
                ví dụ danh sách kề của đỉnh 5(i) là 5 : 2 3 4 nghĩa là 5 là đỉnh đầu lần lượt các đỉnh nối với 5 để tạo thành cạnh
                kề của đồ thị như 5 nối với 2 thành cạnh 5 2,  5 nối với 3 thành cạnh 5 3 và  5 nối với 4 thành cạnh 5 4, thì gọi
                là danh sách kề của đỉnh 5. thì 5 có danh sách kề là 2 3 4, 
                - đầu tiên chuỗi s ta nhập 1 chuỗi là các đỉnh kề với đỉnh 5(i) là 2 3 4 
                + Tiếp đến là qua biến ss để đọc luồng đầu vào của từng phần tử của chuỗi s là 2 3 4
                + đến vòng lặp while thì biến ss sẽ đọc từng phần tử 1 của chuỗi s và gán vào biến num thì num lần lượt sau mõi
                lần vòng lặp while dùng biến ss đọc và gán từng phần tử là 2 trước => thì khi ta push_back cặp đỉnh 5 2 vào danh 
                sách cạnh(danh sách cạnh đc tạo bởi vector <pair<int, int>> egde;) thì sẽ bị thừa tại vì như ở trên input thì ở
                danh sách kề của đỉnh 2 ta có nhập đỉnh 5 vào rồi và khi lưu 1 cạnh vào danh sách cạnh ở đồ thị vô hướng thì ta 
                chỉ lưu đại diện là cạnh có đỉnh đầu nhỏ hơn đỉnh cuối thôi ví dụ trong đồ thị vô hướng thì 1 cạnh nó có 2 chiều
                đỉnh 5 nối với đỉnh 2 tạo thành cạnh 5 2 thì đỉnh 2 nối với đỉnh 5 cũng là cạnh 2 5 như vậy thì nó bị thừa nên khi
                ta lưu 1 cạnh của đồ thị vào danh sách cạnh thị ta chỉ lưu cạnh có đỉnh đầu nhỏ hơn đỉnh cuối thôi tức là lưu cạnh
                2 5 thôi. Vì thế ta phải có điều kiên kiểm tra các đỉnh trong chuỗi s nối với i để tạo thành cạnh kề trong danh 
                sách kề phải nhỏ hơn đỉnh đầu của danh sách kề(tức là i cụ thể như danh sách kề của đỉnh 5 là 5 : 2 3 4 thì 5 gọi
                là đỉnh đầu của danh sách kề đỉnh 5, còn 2 3 4 là các đỉnh khi ta nhập và lưu vào biến string s là các đỉnh nối với
                đỉnh đầu để tạo thành cạnh kề đỉnh 5).
                ==>Ví dụ ở intput của đề bài ở phần danh sách kề của đỉnh 2 bao gồm 1 3 4 5 thì khi này trải qua các bước đọc và gán
                lần lượt từng phần tử của chuỗi s(1 3 4 5 ) vào biến num thì đến đỉnh 5 của danh sách kề đỉnh 2 lệnh if (stoi(num) > 
                i) kiểm tra xem đỉnh đầu có bé hơn đỉnh cuối hay không ở đây đỉnh đầu là 2(i) còn đỉnh cuối là 5(stoi(num)) tức là 5
                > 2  đúng nên ta push_back({i, stoi(num)}) tức là cặp đỉnh 2 và 5 của danh sách kề này vào danh sách cạnh egde thì 
                egde lúc này đã có cạnh 2 5 khi đó thì xuống đến danh sách cạnh kề của đỉnh 5 bao gồm các đỉnh 2 3 4 thì khi này 
                trải qua các bước đọc và gán lần lượt từng phần tử của chuỗi s(2 3 4) vào biến num thì đến đỉnh 2 của danh sách kề
                đỉnh 5 lệnh if (stoi(num) > i) kiểm tra xem đỉnh đầu có bé hơn đỉnh cuối hay không ở đây đỉnh đầu là 5(i) còn đỉnh
                cuối là 2(stoi(num)) tức là 2 > 5 ở đây thì đỉnh đầu lại lớn hơn đỉnh cuối nên không thõa thì không thể thêm cặp 
                đỉnh 5 và 2 tạo thành cạnh kề 5 2 của đồ thị vào danh sách cạnh được đồng nghĩa với việc là ở danh sách kề của đỉnh
                2 thì ta đã lưu cạnh đại diện là cạnh có đỉnh đầu bé hơn đỉnh cuối là cạnh 2 5 vào danh sách cạnh egde rồi nên khi 
                xuống danh sách kề của đỉnh 5 thì cạnh 5 2 không cần phải thêm vào danh sách cạnh egde nữa vì nếu lưu thêm cạnh 5 2
                vào ta sẽ bị thừa đối với danh sách cạnh.
                */
                egde.push_back({i,stoi(num) });
            }
            
        }
    }

    //duyệt danh sách kề và xuất ra danh sách cạnh => Tức là chuyển danh sách kề sang danh sách cạnh
    cout << "\nDanh sach canh sau khi duoc chuyen tu danh sach ke: \n";
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


//=====================Đồ thị có hướng=======================================
#if 1
#include <iostream>
#include<vector>
#include<string>
#include<sstream>
using namespace std;
/*Bài 5: danh sách kề sang danh sách cạnh
Cho đồ thị có hướng G = < V,E > Được biểu diễn dưới dạng danh sách kề. Hãy viết chương trình thực hiện chuyển
đổi biểu diễn đồ thị dưới dạng danh sách cạnh. HÌNH BÀI 2 NÀY Ở TRONG VỞ CỦA BÀI 7 PHẦN 2 LA MÃ
Input: + Dòng đầu tiên chứa 1 số n là số đỉnh của đồ thị. (1 <= n <= 1000)
       + N dòng tiếp theo theo, mõi dòng là danh sách kề của các đỉnh từ 1 tới đỉnh n.
Out: In ra danh sách cạnh tương ứng
ví dụ: Bảng input là dữ liệu của ma trận kề ta nhập vào để output tức là từ ma trận kề chuyển sang danh sách cạnh, 5 là số
đỉnh của đô thị ta cho vòng lặp chạy từ 1 tới 5 tức là 5 đỉnh 1 2 3 4 5
+--------------------------------------------------+
|       Input              Output                  |
+--------------------------------------------------+
|        5           |       1 2                   |
|       1: 2 3 4     |       1 3                   | => Ở input ta chỉ nhập vào chuỗi là 2 3 4 thôi 1: là bản thân tự ký hiệu
|       2: 3 4 5     |       1 4                   | để khi xem lại bài ta hiểu chuỗi  2 3 4 là các đỉnh nằm trong danh sách
|       3: 4 5       |       2 3                   | cạnh kề với đỉnh 1. Tương tự các dòng bên dưới cũng vậy
|       4: 5         |       2 4                   |
|       5:           |       2 5                   |
|                    |       3 4                   |
|                    |       3 5                   |
|                    |       4 5                   |
|                    |                             |
+--------------------------------------------------+

Vì là đồ thị có hướng nên 1 cạnh kề của đồ thị chỉ được tạo theo hướng từ đỉnh đầu đến đỉnh cuối mà thôi tức là cặp đỉnh 1 2 là
cạnh của đồ thị theo hướng đỉnh 1 nối tới đỉnh 2 và không thể đảo hướng lại theo hướng ngược lại 2 nối tới 1 giống đồ thị vô hướng
được......*/
int n;
int a[20][20];
vector<int> adj[20];
vector<pair<int, int>> egde;
int main() {
    cout << "Nhap vao n so dinh cua do thi: ";
    cin >> n;
    cin.ignore();
    cout << "nhap vao danh sach ke cua dinh \n ";
    for (short i = 1; i <= n; i++)
    {
        cout << i <<" : ";
        string s, num;
        getline(cin, s);/*Đối với đồ thị có hướng thì bài 6 chuyển từ danh sách kề sang danh sách cạnh ta không cần phải thêm đk
        i < stoi(num) tức vì là đồ thị vô hướng nên từ input ta nhập vào các cặp đỉnh tạo thành cạnh của đồ thị theo hai hướng 
        nên khi từ danh sách kề chuyển sang danh sách cạnh thì danh sách cạnh chỉ cần đại diện 1 cạnh có đỉnh đầu bé hơn đỉnh
        cuối thôi nên ta thêm đk i(là đỉnh đầu) < stoi(num)(đỉnh cuối). Còn đối với đồ thị có hướng thì không cần vì 1 cạnh
        của đồ thị có hướng được tạo bởi cặp đỉnh theo hướng từ đỉnh đầu nối đến đỉnh cuối tức là đỉnh đầu bé hơn đỉnh cuối và
        không có hướng ngược lại nên không cần có điều kiện i < stoi(num)*/
        stringstream ss(s);
        while (ss >> num)
        {
            egde.push_back({i , stoi(num) });
        }
    }
        
    cout << "\nDanh sach canh sau khi duoc chuyen tu danh sach ke: \n";
    for (auto it : egde) {

        cout << it.first << " " << it.second<<" \n";
    }
}
#endif // 1






