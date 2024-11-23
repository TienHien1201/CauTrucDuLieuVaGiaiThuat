#include<iostream>
#include<vector>
using namespace std;


const int maxn = 20;/*sử dụng để định rõ một giá trị cố định trong chương trình, giúp dễ dàng quản lý và thay đổi giá trị đó mà không
cần phải tìm và sửa tất cả các vị trí sử dụng giá trị đó trong code*/
int n, m;//n là số đỉnh, m là số cạnh
int parent[maxn], sz[maxn];/*Mảng parent dùng để lưu đại diện của cây khung ban đầu khi vừa tạo. vì ban đầu là tạo 1 khung cây rỗng
mà ta áp dụng thuật DSU - Disjoin Set Union(cấu trúc dữ liệu các tập hợp rời nhau) nên mõi đỉnh phải có đại diện là chính nó tương
đương với mõi đỉnh trong khung cây rỗng ban đầu là 1 tập hợp, mảng size dùng để lưu kích thước của 1 tập hợp để khi gộp 2 tập hợp lại
thì hàm uion sẽ tối ưu bằng cách cho đại diện của tập có kích thước nhỏ hơn thành đại diện có kích thước lớn hơn.*/

void Make_Set() {/*Mõi đỉnh ban đầu trong khung cây là mõi tập rời nhau nên cập nhật cho các đỉnh trong khung cây ban đầu có đại diện
    là chính nó tương đương với mõi đỉnh là 1 tập hợp  */
    for (short i = 1; i <= n; i++)
    {
        parent[i] = i;
        sz[i] = 1;
    }
}

int Find(int v) {//Tìm đại diện của 1 đỉnh bất kì
    if (v == parent[v])
    {
        return v;
    }
    return parent[v] = Find(parent[v]);
}

bool Union(int a, int b) {//Thực hiện việc gộp 2 đỉnh bất kì
    a = Find(a);//Tìm đại diện của đỉnh a
    b = Find(b);//Tìm đại diện của đỉnh b
    if (a == b)//Nếu đại diện của a mà bằng b tức a và b nằm trong 1 tập hợp nên k cần gộp và return false
        return false;

    /*Xuống đây là a với b khác đại diện hay nói cách khác là a và b nằm 2 tập hợp khác nhau nên có thể gộp
    a và b lại */
    if (sz[a] < sz[b]) {/*Tối ưu gộp bằng cách cho đại diện của tập có kích thước nhỏ hơn thành đại diện của
        tập có kích thước nhỏ hơn*/

        swap(a, b);
        parent[b] = a;
        sz[a] += sz[b];
        return true;
    }
}
