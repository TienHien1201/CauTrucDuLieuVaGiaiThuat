//========================== ĐỒ THỊ VÔ HƯỚNG =====================
#if 0
#include<iostream>
#include<vector>
using namespace std;
/*Bài 2: Danh sách cạnh sang danh sách kề
Cho đồ thị vô hướng G = < V,E > Được biểu diễn dưới dạng danh sách cạnh. Hãy viết chương trình thực hiện chuyển
đổi biểu diễn đồ thị dưới dạng danh sách kề.HÌNH BÀI 2 NÀY Ở TRONG VỞ CỦA BÀI 7 PHẦN 2 LA MÃ
Input: + Dòng đầu tiên chứa 2 số n, m là số đỉnh và số cạnh của đồ thị. (1 <= 1000, 1 <= m <= n*(n-1)/2)
       + M dòng tiếp theo theo mõi dòng là 2 số u, v biểu diễn cạnh u,v của đồ thị (1 <= u,v <= n). Các cặp cạnh được
       liệt kê theo thứ tự tăng dần của các đỉnh đầu
Output: In ra danh sách kề tương ứng của đồ thị, liệt kê theo thứ tự tăng dần của các đỉnh
ví dụ:
+--------------------------------------------------+
|       Input              Output                  |
+--------------------------------------------------+
|        5 9       |       1 : 2 3 4               | => Tức là các đỉnh nối với 1 để tạo thành cạnh kề của 1 bao gồm các 
|        1 2       |       2 : 1 3 4 5             | đỉnh 2 3 4
|        1 3       |       3 : 1 2 4 5             | =>  Tức là các đỉnh nối với 2 để tạo thành cạnh kề của 2 bao gồm các 
|        1 4       |       4 : 1 2 3 5             | đỉnh 1 3 4 5 
|        2 3       |       5 : 2 3 4               | => Tức là các đỉnh nối với 3 để tạo thành cạnh kề của 3 bao gồm các 
|        2 4       |                               | đỉnh 1 2 4 5 
|        2 5       |                               | => Tức là các đỉnh nối với 4 để tạo thành cạnh kề của 4 bao gồm các 
|        3 4       |                               | đỉnh 1 2 3 5 
|        3 5       |                               | => Tức là các đỉnh nối với 5 để tạo thành cạnh kề của 5 bao gồm các 
|        4 5       |                               | đỉnh 2 3 4 
+--------------------------------------------------+
- bảng này nghĩa là n(là đỉnh) = 5 , m(là cạnh) = 9,
+ và 5 đỉnh là từ 1 tới 5
+ và 9 cạnh gồm: 
# 1 với 1 không là cạnh vì 1 với 1 là chung 1 đỉnh không gọi là cạnh kề(cạnh kề là 2 đỉnh tạo thanh 1 cạnh) mà gọi
là khuyên(Khuyên là cạnh có đỉnh đầu và đỉnh cuối chung 1 đỉnh) tức là a[1][1] = 0
* đỉnh 1 nối với đỉnh 2 là CẠNH 1 2 tức là a[1][2] = 1
* đỉnh 1 nối với đỉnh 3 là CẠNH 1 3  tức là a[1][2] = 1
* đỉnh 1 nối với đỉnh 4 là CẠNH 1 4
# 1 với 5 không là đỉnh vì ta không nối 2 đỉnh này lại với nhau vì đồ thị là tùy thuộc vào đề bài đưa ra hình dạng
cho ta nên hình bài này là ở trong vở bài 7 phần 2 la mã thì 1 với 5 không nối với nhau nên không là cạnh kề => 1
với 5 bằng 0
* đỉnh 2 nối với đỉnh 1 là CẠNH 2 1 .Vì là đồ thị vô hướng nên 1 nối với 2 cũng là cạnh mà 2 nối với 1 cũng là cạnh
# 2 với 2 không là cạnh vì 2 với 2 là chung 1 đỉnh không gọi là cạnh kề(cạnh kề là 2 đỉnh tạo thanh 1 cạnh) mà gọi
là khuyên(Khuyên là cạnh có đỉnh đầu và đỉnh cuối chung 1 đỉnh)
* đỉnh 2 nối với đỉnh 1 là CẠNH 2 3
* đỉnh 2 nối với đỉnh 4 là CẠNH 2 4
* đỉnh 2 nối với đỉnh 5 là CẠNH 2 5
* đỉnh 3 nối với đỉnh 2 là CẠNH 3 2
* đỉnh 3 nối với đỉnh 4 là CẠNH 3 4
* đỉnh 3 nối với đỉnh 5 là CẠNH 3 5
* đỉnh 4 nối với đỉnh 5 là CẠNH 4 5

Vì là đồ thị vô hướng nên 1 nối với 2 cũng là cạnh mà 2 nối với 1 cũng là cạnh*/

int n, m;
vector<int> adj[1001];//adj[i] : Lưu danh sách kề của đỉnh i
int main() {
    cout << "Nhap vao n dinh cua do thi: ";
    cin >> n;
    cout << "Nhap vao m canh cua do thi: ";
    cin >> m;

    //Nhập cặp đỉnh x và y cho đồ thị 
    cout << "Nhap vao dinh x va dinh y cua do thi: ";
    for (short i = 0; i < m; i++) {//Vòng lặp này dùng để nhập cạnh mõi 1 cạnh(m) tương ứng với cặp x và y
        int x, y;
        cin >> x >> y;

        //(push_back trong vector)Đưa các đỉnh vào danh sách kề
        adj[x].push_back(y);
        adj[y].push_back(x);
        /*Vì đây là đồ thị vô hướng nên khi đỉnh x tạo với đỉnh y thành 1 cạnh thì y tạo với x cũng là 1 cạnh nên 
        cạnh 1 2 thì đảo ngược lại 2 1 cũng là 1 cạnh tương tự 1 3 là 1 cạnh và 3 1 là 1 cạnh vì  trong hình 1 cặp
        đỉnh ấy tạo thành 1 cạnh và tương tự các trường hợp khác cũng vậy..................
        => Ví dụ ta nhập vào n cạnh = 5 và m cạnh = 9, 9 cạnh gồm : 1 với 2 tạo thành cạnh 1 2, 1 3 , 1 4, 2 3, 2 4,
        2 5, 3 4, 3 5, 4 5. Ta tạo ra 1 vector adj[1001] nghĩa là vector adj lưu được 1001 phần tử.
        - Đầu tiên khi ta nhập x bằng 1 và y bằng 2 
        + thì adj[x](Tức là tạo 1 vector mang giá trị của đỉnh x mà x ta nhập vào là 1), adj[x].push_back(y);(tức
        là ta đưa giá trị của y vào vector x) cụ thể là vector x là 1 đưa y vào vector 1 là y mà y bằng 2 thì 
        vector 1(x) của ta bây giờ sẽ chứa số 2 tức là vector x bây giờ là 1: 2 
        + thì tương tự  adj[y].push_back(x); là tạo ra 1 vector y và đưa x và vector mà x đang là 1 và y là 2 thì 
        vector y lúc này sẽ là 2: 1 
        - Tiếp theo cứ thế x = 1 , y = 3 
        + adj[x].push_back(y); tức là thêm số 3(y) vào danh sách đỉnh 1(x) mà push_back của vector là thêm vào cuối vector.
        Thì danh sách x(tức là danh sách mang đỉnh 1) vì x của ta nhập vào vẫn là 1 mà ta đã tạo ra vecor 1 rồi thì khi thêm
        đỉnh y mới vào khi x bằng 1, thì nó chỉ push giá trị mới của đỉnh y mà nối với 1 tạo thành cạnh kề của đồi thị, thì
        danh sách của đỉnh 1 lúc này lúc này 1 : 2 3 
        + adj[y].push_back(x) tức là thêm 1(x) vào danh sách đỉnh 3(y)  mà push_back của vector là thêm vào cuối vector. Và
        danh sách y mới(tức là danh sách mang đỉnh 3) của ta lúc này  3 : 1
        - Tiếp theo cứ thế x = 1 , y = 4 
        + adj[x].push_back(y); tức là thêm số 4(y) vào danh sách đỉnh 1(x) mà push_back của vector là thêm vào cuối vector.
        thì danh sách x(tức là danh sách mang đỉnh 1) của ta lúc này 1 : 2 3 4
        + adj[y].push_back(x) tức là thêm số 1(x) vào danh sách đỉnh 4(y) mà push_back của vector là thêm vào cuối vector.
        Và danh sách y mới(tức là danh sách mang đỉnh 4) của ta lúc này  4 : 1
        - Tiếp theo cứ thế x = 2 , y = 3 
        + adj[x].push_back(y); Tức là thêm số 3(y) vào danh sách của đỉnh 2(x) vì x đang bằng 2  mà push_back của vector
        là thêm vào cuối vector. Vì là khi nhập 2 đỉnh x và y lần đầu tiên thì do là đồ thị vô hướng nên x với y là 1 cạnh 
        thì y với x cũng là 1 cạnh nên khi ta nhập vào x là 1 và y là 2 thì khi ta tạo ra 1 vector x và đưa y vào cuối 
        vector x và ngược lại tạo 1 vector y đưa x vào cuối vector y thì ta đã có 2 vector x là 1: và y là 2: thì ta đã có
        sẵn vector 2 rồi nên danh sách mang đỉnh 2 bây giờ thêm giá trị mới là 3 vào tức  2: 1 3
        + adj[y].push_back(x) tức là thêm số 3(y) vào danh sách của đỉnh 2(x) mà push_back của vector là thêm vào cuối 
        vector. Và danh sách y(tức là danh sách mang đỉnh 3) đã được tạo ở trên nên danh sách mang đỉnh 3 lúc này sẽ thêm
        giá trị của x là 2 vào tức 3 : 1 2
        - Tiếp theo là x bằng 2, y bằng 4
        + adj[x].push_back(y); tức là thêm số 4(y) vào danh sách của của đỉnh 2(x) vì x đang bằng 2 mà push_back của vector
        là thêm vào cuối vector. Thì danh sách của đỉnh x là 2 lúc này là 2 : 1 3 4 
        + adj[y].push_back(x) tức là thêm số 2(x) vào dah sách của đỉnh 4(y) vì y đang bằng 4 mà push_back của vector là thêm
        vào cuối vector. Và danh sách của đỉnh y là 4 lúc này là 4 : 1 2 
        - Tiếp là x bằng 2, y bằng 5
        + adj[x].push_back(y); tức là thêm số 5(y) vào danh sách của đỉnh 2(x) mà push_back của vector là thêm vào cuối 
        vector. Thì danh sách của đỉnh x là 2 lúc này là 2 : 1 3 4 5 
        + adj[y].push_back(x); tức là thêm số 2(x) vào danh sách của đỉnh 5(y) mà push_back của vector là thêm vào cuối 
        vector. Và danh sách của đỉnh y là 5 lúc này là 5 : 2 
        ...........................TƯƠNG TỰ cho các cặp đỉnh còn lại............................................... 
        */
    }

    //Xuất đồ thị bằng danh sách kề
    cout << "danh sach ke cua do thi sau khi duoc chuyen tu danh sach canh: \n";
    for (short i = 1; i <= n; i++)
    {
        cout << i << " : ";
        for (int x : adj[i]) {

            cout << x<<" ";
        }
        cout << "\n";
    }
}

#endif // 0

//======================= ĐỒ THỊ CÓ HƯỚNG ============================
#include<iostream>
#include<vector>
using namespace std;
/*Bài 2: Danh sách cạnh sang danh sách kề
Cho đồ thị có hướng G = < V,E > Được biểu diễn dưới dạng danh sách cạnh. Hãy viết chương trình thực hiện chuyển
đổi biểu diễn đồ thị dưới dạng danh sách kề.HÌNH BÀI 2 NÀY Ở TRONG VỞ CỦA BÀI 7 PHẦN 2 LA MÃ
Input: + Dòng đầu tiên chứa 2 số n, m là số đỉnh và số cạnh của đồ thị. (1 <= 1000, 1 <= m <= n*(n-1)/2)
       + M dòng tiếp theo theo mõi dòng là 2 số u, v biểu diễn cạnh u,v của đồ thị (1 <= u,v <= n). Các cặp cạnh được
       liệt kê theo thứ tự tăng dần của các đỉnh đầu
Output: In ra danh sách kề tương ứng của đồ thị, liệt kê theo thứ tự tăng dần của các đỉnh
ví dụ:
+--------------------------------------------------+
|       Input              Output                  |
+--------------------------------------------------+
|        5 9       |       1 : 2 3 4               | => Tức là đỉnh đầu 1 nối với các đỉnh để tạo thành cạnh kề của 1 bao gồm các
|        1 2       |       2 : 3 4 5               | đỉnh là 2 3 4
|        1 3       |       3 : 4 5                 | => Tức là đỉnh đầu 2 nối với các đỉnh để tạo thành cạnh kề của 2 bao gồm các
|        1 4       |       4 : 5                   | đỉnh là 3 4 5
|        2 3       |       5 :                     | => Tức là đỉnh đầu 3 nối với các đỉnh để tạo thành cạnh kề của 3 bao gồm các
|        2 4       |                               | đỉnh là 4 5
|        2 5       |                               | => Tức là đỉnh đầu 4 nối với các đỉnh để tạo thành cạnh kề của 4 bao gồm các
|        3 4       |                               | đỉnh là 5
|        3 5       |                               | => Tức là đỉnh đầu 5 nối với các đỉnh để tạo thành cạnh kề của 5 thì không có 
|        4 5       |                               | đỉnh nào 
+--------------------------------------------------+
- bảng này nghĩa là n(là đỉnh) = 5 , m(là cạnh) = 9,
+ và 5 đỉnh là từ 1 tới 5
+ và 9 cạnh gồm:
# 1 với 1 không là cạnh vì 1 với 1 là chung 1 đỉnh không gọi là cạnh kề(cạnh kề là 2 đỉnh tạo thanh 1 cạnh) mà gọi
là khuyên(Khuyên là cạnh có đỉnh đầu và đỉnh cuối chung 1 đỉnh) tức là a[1][1] = 0
* đỉnh 1 nối với đỉnh 2 là CẠNH 1 2 tức là a[1][2] = 1
* đỉnh 1 nối với đỉnh 3 là CẠNH 1 3  tức là a[1][2] = 1
* đỉnh 1 nối với đỉnh 4 là CẠNH 1 4
# 1 với 5 không là đỉnh vì ta không nối 2 đỉnh này lại với nhau vì đồ thị là tùy thuộc vào đề bài đưa ra hình dạng
cho ta nên hình bài này là ở trong vở bài 7 phần 2 la mã thì 1 với 5 không nối với nhau nên không là cạnh kề => 1
với 5 bằng 0
* đỉnh 2 nối với đỉnh 1 là CẠNH 2 1 .Vì là đồ thị vô hướng nên 1 nối với 2 cũng là cạnh mà 2 nối với 1 cũng là cạnh
# 2 với 2 không là cạnh vì 2 với 2 là chung 1 đỉnh không gọi là cạnh kề(cạnh kề là 2 đỉnh tạo thanh 1 cạnh) mà gọi
là khuyên(Khuyên là cạnh có đỉnh đầu và đỉnh cuối chung 1 đỉnh)
* đỉnh 2 nối với đỉnh 1 là CẠNH 2 3
* đỉnh 2 nối với đỉnh 4 là CẠNH 2 4
* đỉnh 2 nối với đỉnh 5 là CẠNH 2 5
* đỉnh 3 nối với đỉnh 2 là CẠNH 3 2
* đỉnh 3 nối với đỉnh 4 là CẠNH 3 4
* đỉnh 3 nối với đỉnh 5 là CẠNH 3 5
* đỉnh 4 nối với đỉnh 5 là CẠNH 4 5

Vì là đồ thị vô hướng nên 1 nối với 2 cũng là cạnh mà 2 nối với 1 cũng là cạnh*/

int n, m;
vector<int> adj[1001];

int main() {
    cout << "Nhap n dinh cua do thi: ";
    cin >> n;
    cout << "Nhap m canh cua do thi: ";
    cin >> m;

    cout << "Nhap vao dinh x va dinh y tao thanh canh cua do thi: ";
    for (short i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;

            adj[x].push_back(y);/*Vì là đồ thị có hướng nên ta chỉ push_back các đỉnh nào mà nối với đỉnh đầu tạo thành cạnh theo
            hướng từ đỉnh đầu nối với đỉnh cuối vào danh sách kề đỉnh x thôi.
            => ví dụ ta có danh sách cạnh như phần input của đề bài: 1 2, 1 3, 1 4, 2 3, 2 4, 2 5, 3 4, 3 5, 4 5. thì chuyển sang 
            canh sách kề như sau vòng lặp for i chạy từ 0 đến m mà mõi 1 m là 1 cặp đỉnh tạo thành kề của đồ thị, m ta nhập bằng 9
            tức là là ta nhập đc 9 cặp x và y tương đương với 9 cạnh của đồ thị
            - Nhập x và y lần tượt cho đến hết vòng lặp tức là nhập 9 cặp đỉnh 1 2, 1 3, 1 4, 2 3, 2 4, 2 5, 3 4, 3 5, 4 5 thì ta 
            adj[x].push_back(y); tức là thêm y vào danh sách kề đỉnh x tức là các đỉnh y nào nối với x mà tạo thành cạnh kề thì ta
            thêm y vào danh sách kề đỉnh x, vì là đồ thị có hướng nên danh sách kề đỉnh x chỉ được chứa các đỉnh y nào là đỉnh cuối
            khi nối với đỉnh x để tạo thành cạnh kề mà thôi tức là như input đầu bài thì danh sách kề bao gồm : 
            + 1: 2 3 4 
            + 2: */
    }

    cout << "Danh sach ke sau khi duoc chuyen tu danh sach canh: \n";
    for (short i = 1; i <= n; i++)
    {
        cout << i << " : ";

        for (int x : adj[i]) {
            cout << x<<" ";
        }
        cout << "\n";
    } 

}