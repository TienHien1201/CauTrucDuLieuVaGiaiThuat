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

//Hàm xuất Duyệt cây nhị phân theo RNL - Right Node Left tức là xuất các phần tử trong cây ra theo thứ tự từ lớn đến bé
void XuatCayDuyetRNL(node* t) {
    if (t != NULL)
    {
        XuatCayDuyetRNL(t->pRight);//Duyệt qua bên phải => Đầu tiên là xuất dữ liệu nên phải của node vừa duyệt
        cout << t->data << " ";//Xuất dữ liệu trog node => Thứ 2 là xuất dữ liệu node
        XuatCayDuyetRNL(t->pLeft);//Duyệt qua bên trái => cuối cùng là Xuất dữ liệu bên trái của node vừa duyệt
        /*Duyệt Theo RNL tức là duyệt và xuất Right đầu tiên, tiếp theo là đến node và cuối cùng là left. Cho đến khi hết nhánh 
        right rồi xuất ra node gốc cuối cùng là duyệt hết nhánh left thì không còn phần tử nào nữa ta dừng 
        => Tóm lại: Đầu tiên duyệt ta sẽ gặp node root(Node gốc trước) vì là duyệt theo RNL nên ta duyệt qua nhánh Right của node
        gốc chu trình duyệt cũng tương tự như những cách duyệt trước chỉ có cách duyệt và xuất ra là thay đổi, khi qua nhánh right
        này gặp node nào mà có ít nhất 1 nhánh left or right hoặc là đủ cả 2 nhánh left và right luôn thì ta cứ duyệt theo độ ưu 
        tiên giảm dần tức là Right trước rồi đến node cuối cùng là left cứ thế đến tận cùng của cây nhị phân thì ta xuất ra theo
        thứ tự  right node left sau khi duyệt tận cùng của nhánh phải ta đã duyệt và xuất ra cả 3 trường hợp right trước sau đó
        đến node cuối cùng là left thì ta đệ quy lên và chổ nào còn trường hợp chưa duyệt để xuất ra thì khi đệ quy lên ta sẽ 
        duyệt và xuất các trường hợp đó cho đến khi đệ quy đến đến node gốc vì là duyệt theo Right xong mới tới node nên nhánh
        right ta đã duyệt và xuất xong các trường hợp right node left của nhánh phải node gốc thì bây giờ ta sẽ duyệt đến node 
        gốc và xuất ra node gốc ra, sau khi duyệt và xuất ra nhánh right của node gốc và node gốc rồi cuối cùng chỉ còn nhánh 
        left của node gốc thì ta cũng duyệt các node của nhánh left này tương tự như nhánh right cứ gặp node nào có nhánh thì 
        ta lại duyệt theo Right Node Left cho đến khi tận cùng của nhánh left thì ta xuất theo thứ tự right node left trường 
        hợp nào không có phần tử thì ta bỏ qua việc xuất và cứ xuất theo thứ tự right trước rồi đến node cuối cùng là left rồi 
        ta đệ quy lên cho đến khi duyệt và xuất đủ cả 3 trường hợp right node left không còn phần tử để duyệt nữa thì dừng .*/
    }
}


//Hàm nhập dữ liệu
void Menu(node*& t) {
    while (true)
    {
        system("cls");
        cout << "\n\n\t\t1.Nhap du lieu vao cay";
        cout << "\n\n\t\t2.Xuat du lieu cay nhi phan duyet theo NRL -  Right Node Left";
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
            cout << "Danh sach cay nhi phan duyet theo NRL -  Right Node Left: ";
            XuatCayDuyetRNL(t);
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

