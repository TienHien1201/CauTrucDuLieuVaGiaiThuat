#include <iostream>
using namespace std;
/*Đề bài: Nhập vào cây nhị phân các số nguyên. Xuất ra màn hình các phần tử của cây cây nhị phân*/

//Khai báo cấu trúc 1 node
struct node
{
    int data;//Dữ liệu của node => Dữ liệu mà node sẽ lưu trữ
    node* pLeft;//Node liên kết bên trái của cây <=> Cây con trái
    node* pRight;//Node liên kết bên phải của cây <=> Cây con phải
};
typedef node* TREE;/*Thay vì chúng ta làm việc với cây nhị nhân là ta làm việc với con trỏ là node* ở dòng này đơn giả là ta thay
thế node* thành TREE. Thì thay vì ta làm việc với cây nhị phân là ta làm việc với con trỏ là node* thì ở đây ta thay thế
cái node* lại thành 1 cái tên là TREE tác dụng cho 1 số người không thể tiếp thu được kiến thức con trỏ tức là ngán/sợ con
trỏ thì thay vì dùng node*(Tức là con trỏ) thì ta thay thế node* thành tên là TREE nhưng bản chất nó vẫn là 1 con trỏ tức là
node* và TREE node là 1 chỉ có thay vì khi sử dụng node(con trỏ) ta phải gọi tên gốc là node* thì bây giờ ta có thể gọi là TREE
. Còn đối với mình thì không cần mình có thể làm việc với con trỏ 1 cách bình thường như bên danh sách liên kết đơn là gọi tên
gốc ra sài tức là node* */

//Khởi tạo cây
//Nếu ai sợ con trỏ có thể dùng tên thay thế là : void KhoiTaoCay(TREE &t)
void KhoiTaoCay(node*& t) {/*t tức là viết tắc của tử tree - cây đây là lấy tên gốc ra sài tức là thao tác với con trỏ mà k cần
phải dùng tên thay thế.
*Giải thích: */
    t = NULL; //Cây rỗng tức là chưa có phần tử vì mới khởi tạo nên danh sách cây chưa có phần tử
}

//Hàm thêm phần tử x vào cây nhị phân
void ThemVaoCay(node*& t, int x) {
    //Nếu cây rỗng 
    if (t == NULL)
    {
        node* p = new node;//Khởi tạo 1 cái node để thêm vào cây
        p->data = x;//Thêm dữ liệu x vào data
        p->pLeft = NULL;
        p->pRight = NULL;
        t = p;// node p chính là node gốc <=> x chính là node gốc tức là phần tử đầu tiên đc thêm vào là phần tử gốc của cây
    }

    //Cây có tồn tại phần tử 
    else
    {
        //Nếu phần tử thêm vào mà nhỏ hơn node gốc => thêm node vào bên trái
        if (x < t->data)
        {
            ThemVaoCay(t->pLeft, x);/*Đây được gọi là kỹ thuật đệ quy tức là hàm đc gọi bên trong hàm, chính là hàm đó luôn
            => Duyệt qua trái để thêm phần tử x*/
        }
        //Nếu phần tử thêm vào mà lớn hơn node gốc => thêm node vào bên phải
        else if (x > t->data)
        {
            ThemVaoCay(t->pRight, x);/*Đây được gọi là kỹ thuật đệ quy tức là hàm đc gọi bên trong hàm, chính là hàm đó luôn
            => Duyệt qua phải để thêm phần tử x*/
        }
    }
}


void XuatCayDuyetNRL(node* t) {
    //Nếu cây còn phần tử thì tiếp tục duyệt
    if (t != NULL) {
        cout << t->data << " ";//Xuất dữ liệu trog node => Đầu tiên là xuất dữ liệu node
        XuatCayDuyetNRL(t->pRight);//Duyệt qua bên trái => Thứ 2 Xuất dữ liệu bên trái của node vừa duyệt
        XuatCayDuyetNRL(t->pLeft);//Duyệt qua bên phải => Cuối cùng là xuất dữ liệu nên phải của node vừa duyệt
       /*Duyệt node trước rồi đến right rồi đến left => tức là xuất dữ liệu của node trước rồi đến right rồi đến left. Cho
       đến khi hết nhánh phải và chuyển sang nhánh trái chừng nào gặp NULL thì  dừng lại
       =>Tóm lại: Đầu tiên là node root(node gốc) vì duyệt xuất theo NRL tức là xuất node trước rồi đến right rồi đến left thì
       sau khi duyệt đến node gốc và xuất node gốc đầu thì tiếp theo ta duyệt đến nhánh right của node gốc, ở nhánh right này 
       cứ node nào mà có ít nhất 1 nhánh left or right hoặc có đủ 2 nhánh left và right luôn thì ta cứ theo thứ tự duyệt xuất
       node trước sau đó duyệt đến right nếu ở nhánh right này lại có thêm ít nhất 1 nhánh hoặc có đủ cả 2 nhánh thì ta lại duyệt
       theo thứ tự duyệt xuất node trước sau đó duyệt đến right và cuối cùng là duyệt đến left cho đến khi đi đến tận cùng của 
       nhánh phải cây nhị phân thì ta đệ quy lên các trường hợp mà ta chưa duyệt tức là duyệt từ node gốc xuống ưu tiên duyệt và
       xuất node trước sau node là tới right cuối cùng là tới left nên khi đệ quy lên sẽ có trường hợp ta chỉ mới duyệt và xuất 
       ra node rồi tới right thôi còn lại left chưa duyệt thì ta cũng duyệt và xuất phần tử left ra sau khi đệ quy lên đến node
       gốc thì ở node gốc ta đã duyệt xuất node gốc và right ra rồi còn lại nhánh left của node gốc ta duyệt tương tự cứ gặp node
       nào có nhánh thì ta theo thứ tự Node trước rồi đến right cuối cùng là left cho đến khi hết luôn nhánh left của node gốc 
       thì ta đã duyệt đủ node right left và không còn phần tử nào nữa thì chương trình của ta dừng lại*/
    }
}
//Hàm nhập dữ liệu
void Menu(node*& t) {
    while (true)
    {
        system("cls");
        cout << "\n\n\t\t1.Nhap du lieu vao cay";
        cout << "\n\n\t\t2.Xuat du lieu cay nhi phan duyet theo NRL - Node Right Left ";
        cout << "\n\n\t\t0.Ket Thuc ";

        int LuaChon;
        cout << "\n\n\t\tMoi lua chon ";
        cin >> LuaChon;

        if (LuaChon < 1 || LuaChon > 2)
        {
            cout << "Lua chon khong hop le !";
            system("Pause");
        }
        else if (LuaChon == 1)
        {
            int x;
            cout << "Nhap so nguyen: ";
            cin >> x;

            ThemVaoCay(t, x);
        }
        else if (LuaChon == 2)
        {
            cout << "Danh sach cay nhi phan duyet theo NLR - node left right: ";
            XuatCayDuyetNRL(t);
            system("Pause");
        }
        else if (LuaChon == 0)
        {
            break;
        }
    }

}


int main()
{
    node* t;
    KhoiTaoCay(t);
    Menu(t);

    system("Pause");
}

