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

//Hàm xuất Duyệt cây nhị phân theo RLN - Right Left Node 
void xuatCayDuyetRLN(node* t) {
    if (t != NULL)
    {
        xuatCayDuyetRLN(t->pRight);//Duyệt qua bên phải => Đầu tiên là xuất dữ liệu nên phải của node vừa duyệt
        xuatCayDuyetRLN(t->pLeft);//Duyệt qua bên trái =>thứ 2 là Xuất dữ liệu bên trái của node vừa duyệt
        cout << t->data << " ";//Xuất dữ liệu trog node => Cuối cùng là xuất dữ liệu node
        /*Duyệt Theo RLN tức là duyệt và xuất right đầu tiên, tiếp theo là đến left và cuối cùng là node. Cho đến khi hết nhánh
        right, rồi duyệt hết nhánh left và cuối cùng là duyệt và xuất ra node gốc và không còn phần tử nào để duyệt nữa thì ta dừng
        => Tóm lại: Đầu tiên ta gặp node root(node gốc) trước vì ta duyệt và xuất ra theo thứ tự là RLN - right đầu tiên, tiếp là
        left cuối cùng là node nên ta duyệt qua nhánh right trước và ở bên dưới nhánh right này cứ node nào có ít nhất 1 nhánh
        left or right hoặc đủ cả nhánh left và right luôn thì ta cứ duyệt và xuất tuần tự right trước rồi đến left cuối cùng là
        node sau khi duyệt xuống tận cùng của nhánh right của node gốc của cây nhị phân thì ta đệ quy lên trường hợp nào chưa duyệt
        thì duyệt và xuất ra cứ tuần tự right left node. Sau khi đã duyệt và xuất hết các trường hợp right left node của nhánh right
        của node gốc rồi thì tiếp theo là duyệt đến nhánh left của node gốc, ở nhánh left này thì ta cũng duyệt và xuất ra tương
        tự như cách mà ta duyệt nhánh right của node gốc cứ node nào có ít nhất 1 nhánh left or right hoặc đủ cả nhánh left và right
        luôn thì ta cứ duyệt và xuất tuần tự right trước rồi đến left cuối cùng là node sau khi duyệt xuống tận cùng của nhánh left
        của node gốc của cây nhị phân thì ta đệ quy lên trường hợp nào chưa duyệt thì duyệt và xuất ra cứ tuần tự right left node
        cho đến khi xuất và duyệt hết các trường hợp của nhánh left của node gốc rồi cuối cùng chỉ còn lại node gốc là ta chưa duyêt
        nên ta duyệt và xuất node gốc ra cuối cùng là xong đối với cách duyệt Right Left Node.*/
    }
}

//Hàm nhập dữ liệu
void Menu(node*& t) {
    while (true)
    {
        system("cls");
        cout << "\n\n\t\t1.Nhap du lieu vao cay";
        cout << "\n\n\t\t2.Xuat du lieu cay nhi phan duyet theo RLN - Right Left Node";
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
            cout << "Danh sach cay nhi phan duyet theo RLN - Right Left Node: ";
            xuatCayDuyetRLN(t);
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



