//===================== ĐỒ THỊ VÔ HƯỚNG ================================
#if 0
#include <iostream>
using namespace std;
/*Bài 1: Danh sách cạnh sang ma trận kề
Cho đồ thị vô hướng G = < V,E > Được biểu diễn dưới dạng danh sách cạnh. Hãy viết chương trình thực hiện chuyển
đổi biểu diễn đồ thị dưới dạng ma trận kề.HÌNH BÀI 1 NÀY Ở TRONG VỞ CỦA BÀI 7 PHẦN 2 LA MÃ
Input: + Dòng đầu tiên chứa 2 số n, m là số đỉnh và số cạnh của đồ thị. (1 <= 1000, 1 <= m <= n*(n-1)/2)
       + M dòng tiếp theo theo mõi dòng là 2 số u, v biểu diễn cạnh u,v của đồ thị (1 <= u,v <= n). Các cặp cạnh được
       liệt kê theo thứ tự tăng dần của các đỉnh đầu
Out: In ra ma trận kề tương ứng của đồ thị
ví dụ:
+--------------------------------------------------+
|       Input              Output                  |
+--------------------------------------------------+
|        5 9       |       0 1 1 1 0               |
|        1 2       |       1 0 1 1 1               |
|        1 3       |       1 1 0 1 1               |
|        1 4       |       1 1 1 0 1               |
|        2 3       |       0 1 1 1 0               |
|        2 4       |                               |
|        2 5       |                               |
|        3 4       |                               |
|        3 5       |                               |
|        4 5       |                               |
+--------------------------------------------------+
- bảng này nghĩa là n(là đỉnh) = 5 , m(là cạnh) = 9,
+ và 5 đỉnh là từ 1 tới 5
+ và 9 cạnh gồm: 1 2, 1 3, 1 4, 2 3, 2 4, 2 5, 3 4, 3 5, 4 5 đây là các cặp đỉnh ta nhập vào các cặp đỉnh này nối với nhau để tạo
thành các cạnh của đồ thị trong danh sách cạnh, vì là đồ thị vô hướng nên các cặp đỉnh đã tạo thành cạnh của đồ thị rồi vì là
đồ thị vô hướng nên đảo hướng các cặp đỉnh tạo thành cạnh của đồ thị đó lại ta lại đc thêm cạnh tức là bao gồm thêm các cạnh 2 1, 
3 1, 4 1, 3 2, 4 2, 5 2, 4 3, 5 3, 5 4. Và các cặp đỉnh không phải là cạnh của đồ thị là gồm:  1 1, 1 5,2 2, 3 3, 4 4, 5 1, 5 5
# 1 với 1 không là cạnh vì 1 với 1 là chung 1 đỉnh không gọi là cạnh kề(cạnh kề là 2 đỉnh tạo thanh 1 cạnh) mà gọi
là khuyên(Khuyên là cạnh có đỉnh đầu và đỉnh cuối chung 1 đỉnh) tức là a[1][1] = 0
* đỉnh 1 nối với đỉnh 2 là CẠNH 1 2 tức là a[1][2] = 1
* đỉnh 1 nối với đỉnh 3 là CẠNH 1 3 tức là a[1][3] = 1
* đỉnh 1 nối với đỉnh 4 là CẠNH 1 4 tức là a[1][4] = 1  
# 1 với 5 không là đỉnh vì ta không nối 2 đỉnh này lại với nhau vì đồ thị là tùy thuộc vào đề bài đưa ra hình dạng
cho ta nên hình bài này là ở trong vở bài 7 phần 2 la mã thì 1 với 5 không nối với nhau nên không là cạnh kề => 1
với 5 bằng 0 tức là a[1][5] = 0
* đỉnh 2 nối với đỉnh 1 là CẠNH 2 1 .Vì là đồ thị vô hướng nên 1 nối với 2 cũng là cạnh mà 2 nối với 1 cũng là cạnh 
=> tức là a[2][1] = 1
# 2 với 2 không là cạnh vì 2 với 2 là chung 1 đỉnh không gọi là cạnh kề(cạnh kề là 2 đỉnh tạo thanh 1 cạnh) mà gọi
là khuyên(Khuyên là cạnh có đỉnh đầu và đỉnh cuối chung 1 đỉnh) tức là a[2][2] = 0
* đỉnh 2 nối với đỉnh 1 là CẠNH 2 3 tức là a[2][3] = 1
* đỉnh 2 nối với đỉnh 4 là CẠNH 2 4 tức là a[2][4] = 1
* đỉnh 2 nối với đỉnh 5 là CẠNH 2 5 tức là a[2][5] = 1
* đỉnh 3 nối với đỉnh 2 là CẠNH 3 2 tức là a[3][2] = 1
* đỉnh 3 nối với đỉnh 4 là CẠNH 3 4 tức là a[3][4] = 1
* đỉnh 3 nối với đỉnh 5 là CẠNH 3 5 tức là a[3][5] = 1
* đỉnh 4 nối với đỉnh 5 là CẠNH 4 5 tức là a[4][5] = 1

Vì là đồ thị vô hướng nên 1 nối với 2 cũng là cạnh mà 2 nối với 1 cũng là cạnh
_  Sau đó biểu diễn thành ma trận kề cho đồ thị :

    1 2 3 4 5
    __________
  1 |0 1 1 1 0| => nghĩa là 1 nối với 1 không là cạnh nên là 0, còn 1 nối với 2 là cạnh nên là 1.... Cứ như vậy mà xét
  2 |1 0 1 1 1| => Vì là đồ thị vô hướng nên 2 nối với 1 cũng là 1 nối với 2 cũng là cạnh cạnh kề 1 với 5 ko là cạnh 
  3 |1 1 0 1 1| vì ta không nhập cặp đỉnh 1 với 5 tạo thành cạnh nên 1 với 5 mang giá trị là không
  4 |1 1 1 0 1|
  5 |0 1 1 1 0| */

//Ma trận kề
int n, m;//n là số đỉnh , m là số cạnh
int a[1001][1001];//Ma trận chứa 1001 đỉnh và 1001 cạnh
int main()
{
    //Nhập đồ thị ma trận 
    cout << "Nhap n dinh cua do thi: ";
    cin >> n;
    cout << "Nhap m canh cua do thi: ";
    cin >> m;
    cout << "Nhap dinh x noi voi dinh y: \n";
    for (short i = 0; i < m; i++) {//Mõi cặp đỉnh x và y tương đương với 1 cạnh(m)
        int x, y;
        cin >> x >> y;
        a[x][y] = a[y][x] = 1;/*Vì là đồ thị vô hướng nên 2 đỉnh x và y tạo thành 1 cạnh thì y và x cũng giống
        x và y. Ví dụ 2 đỉnh 1 và 2 thì khi nối hai đỉnh này lại tạo thành cạnh 1 2 cũng là cạnh 2 1.
        => Nghĩa là khi nhập vào x = 1 và y = 2 thì dòng này ta đã bắt 2 đỉnh tạo thành 1 cạnh khi đó biểu diễn
        đồ thị bằng ma trận kề thì khi ta có nhập vào x với y thì tức 1 và 2 thì đây là 2 đỉnh tạo thành cạnh kề
        thì xuất ma trận kề của a[i][j] cụ thể khi i = 1 và j bằng 2 tức tương đương với a[x][y] x đang bằng
        1 và y bằng 2 thì a[x][y](là a[1][2]) đang mang giá trị bằng 1 thì khi vào biểu diễn đồ thị bằng ma trận kề thì
        phần xuất ma trận kề a[i][j](khi i chạy = 1 và j = 2) thì a[1][2] khi xuất ra nó sẽ mang giá trị bằng 1.
        còn bằng 0 là do cặp đỉnh đó ta không nhập vào nên không là cạnh kề nên khi ở phần xuất ra đồ thị sẽ có
        cặp mang giá trị bằng 0 ví dụ những cặp đỉnh x và y sẽ tạo thành cạnh tức là mang giá trị là 1 là
        1 2, 1 3 , 1 4 , 2 3 , 2 4 , 2 5 , 3 4 , 3 5 , 4 5 vì là vô hướng nên các cặp đỉnh đó đi chiều ngược lại
        cũng là cạnh kề nên cũng mang giá trị là 1 như : 2 1, 3 1, 4 1, 3 2, 4 2, 5 2, 4 3, 5 3, 5 4. và các cặp
        ta không nhập x và y và ngược chiều của nó thì không là cạnh kề nên mang giá trị bằng 0 như : 1 1 , 1 5 ,
        2 2, 3 3 , 4 4 , 5 1 , 5 5 nghiã là ở phần xuất đồ thị thì khi a[i][j] mà bằng các cặp đỉnh này thì giá
        trị của nó sẽ xuát ra bằng 0 vì ta không nhập x và y của các cặp cạnh này nên nó không thể thực thi dòng
        a[x][y] = a[y][x] = 1; thì nó là 0, tức là khi xuất ma trận kề của đồ thị thì i chạy bằng 1 j bằng 1 là
        a[1][1] thì = 0 tương tự a[1][5] = 0 ........*/
    }

    //Xuất ma trận kề đồ thị
    cout << "Ma tran ke cua do thi: \n";
    for (short i = 1; i <= n; i++) {
        for (short j = 1; j <= n; j++) {
            cout << a[i][j] << " ";
        }
        cout << "\n";
    }
}
#endif // 0

//===================== ĐỒ THỊ CÓ HƯỚNG ==============================
#if 0
#include <iostream>
using namespace std;

/*Bài 1: Danh sách cạnh sang ma trận kề
Cho đồ thị có hướng G = < V,E > Được biểu diễn dưới dạng danh sách cạnh. Hãy viết chương trình thực hiện chuyển
đổi biểu diễn đồ thị dưới dạng ma trận kề.HÌNH BÀI 1 NÀY Ở TRONG VỞ CỦA BÀI 7 PHẦN 2 LA MÃ
Input: + Dòng đầu tiên chứa 2 số n, m là số đỉnh và số cạnh của đồ thị. (1 <= 1000, 1 <= m <= n*(n-1)/2)
       + M dòng tiếp theo theo mõi dòng là 2 số u, v biểu diễn cạnh u,v của đồ thị (1 <= u,v <= n). Các cặp cạnh được
       liệt kê theo thứ tự tăng dần của các đỉnh đầu
Out: In ra ma trận kề tương ứng của đồ thị
ví dụ: input là danh sách cạnh output là ma trận kề được chuyển từ danh sách cạnh
+--------------------------------------------------+
|       Input              Output                  |
+--------------------------------------------------+
|        5 9       |       0 1 1 1 0               |
|        1 2       |       0 0 1 1 1               |
|        1 3       |       0 0 0 1 1               |
|        1 4       |       0 0 0 0 1               |
|        2 3       |       0 0 0 0 0               |
|        2 4       |                               |
|        2 5       |                               |
|        3 4       |                               |
|        3 5       |                               |
|        4 5       |                               |
+--------------------------------------------------+
- bảng này nghĩa là n(là đỉnh) = 5 , m(là cạnh) = 9,
+ và 5 đỉnh là từ 1 tới 5
+ và 9 cạnh gồm: 1 2, 1 3, 1 4, 2 3, 2 4, 2 5, 3 4, 3 5, 4 5 đây là các cặp đỉnh ta nhập vào các cặp đỉnh này nối với nhau để tạo
thành các cạnh của đồ thị trong danh sách cạnh, vì là đồ thị có hướng nên các cạnh chỉ đc tạo theo hướng đỉnh đầu nối với đỉnh cuối
chứ không được theo hướng ngược lại, còn lại không phải là cạnh : 1 1, 2 1, 2 2, 3 1, 3 2, 3 3, 4 1, 4 2, 4 3, 4 4, 5 1, 5 2, 5 3, 
5 4, 5 5.
* 1 với 1 không là cạnh vì 1 với 1 là chung 1 đỉnh không gọi là cạnh kề(cạnh kề là 2 đỉnh tạo thanh 1 cạnh) mà gọi
là khuyên(Khuyên là cạnh có đỉnh đầu và đỉnh cuối chung 1 đỉnh) tức là a[1][1] = 0
* đỉnh 1 nối với đỉnh 2 là CẠNH 1 2 tức là a[1][2] = 1
* đỉnh 1 nối với đỉnh 3 là CẠNH 1 3 tức là a[1][3] = 1
* đỉnh 1 nối với đỉnh 4 là CẠNH 1 4 tức là a[1][4] = 1  
* 1 với 5 không là đỉnh vì ta không nối 2 đỉnh này lại với nhau vì đồ thị là tùy thuộc vào đề bài đưa ra hình dạng
cho ta nên hình bài này là ở trong vở bài 7 phần 2 la mã thì 1 với 5 không nối với nhau nên không là cạnh kề => 1
với 5 bằng 0 => Tức là a[1][5] = 0
* đỉnh 2 nối với đỉnh 1 là không là cạnh CẠNH 2 1 .Vì là đồ thị có hướng nên theo chiều chỉ 1 nối với 2 là cạnh thôi không thề như
đồ thị vô hướng mà ngược chiều của cặp đỉnh lại để thành cạnh đc nghĩa là cạnh 1 2 là cạnh theo hướng từ đỉnh 1 tới đỉnh 2 mà thôi
không có chiều ngược lại nên a[2][1] = 0.
# 2 với 2 không là cạnh vì 2 với 2 là chung 1 đỉnh không gọi là cạnh kề(cạnh kề là 2 đỉnh tạo thanh 1 cạnh) mà gọi
là khuyên(Khuyên là cạnh có đỉnh đầu và đỉnh cuối chung 1 đỉnh) nên a[2][2] = 0
* đỉnh 2 nối với đỉnh 1 là CẠNH 2 3 tức là a[2][3] = 1
* đỉnh 2 nối với đỉnh 4 là CẠNH 2 4 tức là a[2][4] = 1
* đỉnh 2 nối với đỉnh 5 là CẠNH 2 5 tức là a[2][5] = 1
* đỉnh 3 nối với đỉnh 2 không là CẠNH 3 2 vì là đồ thị có hướng nên ta đã nối 2 đỉnh 2 và 3 theo hướng từ đỉnh 2 đến đỉnh 3 nên khi
đó ở cặp đỉnh 3 2 là cạnh của đồ thị rồi nên khi đó theo hướng ngược lại của 2 3 thì 3 2 không là cạnh dc tức là a[3][2] = 0
* 3 với 3 không là cạnh vì 3 với 3 là chung 1 đỉnh không gọi là cạnh kề(cạnh kề là 2 đỉnh tạo thành 1 cạnh) mà gọi là khuyên(Khuyên
là cạnh có đỉnh đầu và đỉnh cuối chung 1 đỉnh) tức là a[3][3] = 0
* đỉnh 3 nối với đỉnh 4 là CẠNH 3 4 tức là a[3][4] = 1 
* đỉnh 3 nối với đỉnh 5 là CẠNH 3 5 tức là a[3][5] = 1
* đỉnh 4 nối với đỉnh 5 là CẠNH 4 5 tức là a[4][5] = 1
* đỉnh 5 nối với đỉnh 1 không là CẠNH 5 1 tức là a[5][1] = 0 vì ở input của đề bài thì 2 đỉnh 5 và 1 ta không nhập vào là cạnh của 
đồ thị
* đỉnh 5 nối với đỉnh 2 không là CẠNH 5 2 tức là a[5][2] = 0 vì là đồ thị có hướng nên ta đã nối 2 đỉnh 2 và 5 theo hướng từ đỉnh 
2 đến đỉnh 5 là cạnh của đồ thị rồi nên khi đó ở cặp đỉnh 5 và 2 tức là theo hướng ngược lại của 2 5 thì 5 2 không là cạnh dc tức là 
a[5][2] = 0
* đỉnh 5 nối với đỉnh 3 không là CẠNH 5 3 tức là a[5][3] = 0 vì là đồ thị có hướng nên ta đã nối 2 đỉnh 3 và 5 theo hướng từ đỉnh 
3 đến đỉnh 5 là cạnh của đồ thị rồi nên khi đó ở cặp đỉnh 5 và 3 tức là theo hướng ngược lại của 2 5 thì 5 2 không là cạnh dc tức là 
a[5][2] = 0
* đỉnh 5 nối với đỉnh 4 không là CẠNH 5 4 tức là a[5][4] = 0 vì là đồ thị có hướng nên ta đã nối 2 đỉnh 4 và 5 theo hướng từ đỉnh
4 đến đỉnh 5 là cạnh của đồ thị rồi nên khi đó ở cặp đỉnh 5 và 4 tức là theo hướng ngược lại của 4 5 thì 5 4 không là cạnh dc tức là
a[5][4] = 0
* 5 với 5 không là cạnh vì 5 với 5 là chung 1 đỉnh không gọi là cạnh kề(cạnh kề là 2 đỉnh tạo thành 1 cạnh) mà gọi là khuyên(Khuyên
là cạnh có đỉnh đầu và đỉnh cuối chung 1 đỉnh) tức là a[5][5] = 0

Vì là đồ thị có hướng nên 1 nối với 2 là cạnh có hướng từ đỉnh 1 nối với đỉnh 2  rồi nên không thể đổi hướng nối đỉnh 2 với đỉnh 1
là cạnh được
_  Sau đó biểu diễn thành ma trận kề cho đồ thị :

    1 2 3 4 5
    __________
  1 |0 1 1 1 0| => nghĩa là 1 nối với 1 không là cạnh nên là 0, còn 1 nối với 2 là cạnh nên là 1.... Cứ như vậy mà xét
  2 |0 0 1 1 1| => Vì là đồ thị có hướng nên 2 nối với 1 cũng là 1 nối với 2 cũng là cạnh cạnh kề 1 với 5 ko là cạnh
  3 |0 0 0 1 1| vì ta không nhập cặp đỉnh 1 với 5 tạo thành cạnh nên 1 với 5 mang giá trị là không
  4 |0 0 0 0 1|
  5 |0 0 0 0 0| */

int n, m;
int a[1001][1001];
int main() {
    //Nhập đồ thị ma trận 
    cout << "Nhap n dinh cua do thi: ";
    cin >> n;
    cout << "Nhap m canh cua do thi: ";
    cin >> m;
    cout << "Nhap dinh x noi voi dinh y tao thanh canh cua do thi: \n";
    for (short i = 0; i < m; i++) {//Mõi cặp đỉnh x và y tương đương với 1 cạnh(m)
        int x, y;
        cin >> x >> y;
        a[x][y] = 1;/*Vì là đồ thị có hướng nên 1 cạnh của đồ thị chỉ được tạo theo hướng từ đỉnh đầu(x) đến đỉnh cuối(y) mà thôi,
        cặp đỉnh nào mà ta nhập vào thì có giá trị là 1 tức là cạnh của đồ thị còn lại không phải là cặp x y ta nhập vào thì không 
        phải là cạnh của đồ thị thì bằng 0. các cặp đỉnh mà ta nhập là cạnh của đồ thị theo đề bài hình của đồ thị nằm trong vở */

    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}

#endif // 1




