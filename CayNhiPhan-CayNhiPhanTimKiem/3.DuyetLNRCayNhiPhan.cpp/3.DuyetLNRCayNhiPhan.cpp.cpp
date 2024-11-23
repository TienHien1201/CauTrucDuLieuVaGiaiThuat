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

//Hàm xuất Duyệt cây nhị phân theo LNR - Left Node Right tức là xuất các phần tử trong cây ra theo thứ tự từ bé đến lớn
void xuatCayDuyetLNR(node* t) {
    if (t!= NULL)
    { 
        xuatCayDuyetLNR(t->pLeft);//Duyệt qua bên trái => Đầu tiên là Xuất dữ liệu bên trái của node vừa duyệt
        cout << t->data << " ";//Xuất dữ liệu trog node => Thứ 2 là xuất dữ liệu node
        xuatCayDuyetLNR(t->pRight);//Duyệt qua bên phải => Cuối cùng là xuất dữ liệu nên phải của node vừa duyệt
        /*Duyệt left trước rồi đến node rồi đến right => tức là xuất dữ liệu của left trước rồi đến node rồi đến right. Cho
        đến khi hết nhánh left và hết node rồi chuyển sang nhánh phải chừng nào gặp NULL thì dừng lại
        => Tóm lại duyệt theo LNR - Left trước rồi đến node rồi đến right thì từ trên duyệt xuống tức là từ node gốc duyệt xuống 
        thì bằng mọi giá ta phải xuất ra được phần tử ở nhánh left trước tức là ban đầu gặp node root trước vì là duyệt LNR nên
        ta phải ưu tiên duyệt và xuất ra left trước nếu cứ gặp node mà có nhánh là lại cứ duyệt theo thứ tự left node right, nếu
        nhánh đó là nhánh đáy của cây chỉ có node và left thì ta xuất left trước rồi đệ quy lên node và tiếp là xuất node ra vì 
        không có right nên ta bỏ qua xuất right và đệ quy lên, nếu nhánh đó mà chỉ có node và right thì cũng cứ theo thứ tự left 
        trước left ko có phần tử bỏ qua xuất left và đệ quy lên node xuất node ra tiếp nữa là xuất right cuối cùng. Sau khi đã 
        duyệt hết cả 3 left node right thì ta cứ thế đệ quy lên trên duyệt các trường hợp còn lại vì là duyệt từ node gốc xuống 
        và ưu tiên left nên left ta đã duyệt rồi thì khi đệ quy lên ta chỉ duyệt các trường hợp còn lại là lần lượt node rồi mới
        right cuối cho cứ cứ đệ quy lên và duyệt các trường hợp còn lại lần lượt LNR đến khi không còn phần tử nào tức t == NULL 
        thì hoàn thành việc xuất. */
       
    }

}

//Hàm nhập dữ liệu
void Menu(node*& t) {
    while (true)
    {
        system("cls");
        cout << "\n\n\t\t1.Nhap du lieu vao cay";
        cout << "\n\n\t\t2.Xuat du lieu cay nhi phan duyet theo LNR -  Left Node Right";
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
            cout << "Danh sach cay nhi phan duyet theo LNR -  left node right: ";
            xuatCayDuyetLNR(t);
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

