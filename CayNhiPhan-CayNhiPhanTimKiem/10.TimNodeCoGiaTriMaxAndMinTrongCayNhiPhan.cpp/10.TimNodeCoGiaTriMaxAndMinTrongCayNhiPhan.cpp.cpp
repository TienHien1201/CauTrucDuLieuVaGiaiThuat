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

//Hàm xuất Duyệt cây nhị phân theo LRN - Left Right Node 
void xuatCayDuyetLRN(node* t) {
    if (t != NULL)
    {
        xuatCayDuyetLRN(t->pLeft);//Duyệt qua bên trái => Đầu tiên là Xuất dữ liệu bên trái của node vừa duyệt
        xuatCayDuyetLRN(t->pRight);//Duyệt qua bên phải => thứ 2 là xuất dữ liệu nên phải của node vừa duyệt
        cout << t->data << " ";//Xuất dữ liệu trog node => Cuối cùng là xuất dữ liệu node
        /*Duyệt Theo LRN tức là duyệt và xuất left đầu tiên, tiếp theo là đến right và cuối cùng là node. Cho đến khi hết nhánh
        left rồi duyệt hết nhánh right và cuối cùng là duyệt và xuất ra node gốc và không còn phần tử nào để duyệt nữa thì ta dừng
        => Tóm lại: Đầu tiên ta gặp node root(node gốc) trước vì ta duyệt và xuất ra theo thứ tự là LRN - Left đầu tiên, tiếp là
        right cuối cùng là node nên ta duyệt qua nhánh left trước và ở bên dưới nhánh left này cứ node nào có ít nhất 1 nhánh
        left or right hoặc đủ cả nhánh left và right luôn thì ta cứ duyệt và xuất tuần tự left trước rồi đến right cuối cùng là
        node sau khi duyệt xuống tận cùng của nhánh left của node gốc của cây nhị phân thì ta đệ quy lên, trường hợp nào chưa duyệt
        thì duyệt và xuất ra cứ tuần tự left right node. Sau khi đã duyệt và xuất hết các trường hợp left right node của nhánh left
        của node gốc rồi thì tiếp theo là duyệt đến nhánh right của node gốc, ở nhánh right này thì ta cũng duyệt và xuất ra tương
        tự như cách mà ta duyệt nhánh left của node gốc cứ node nào có ít nhất 1 nhánh left or right hoặc đủ cả nhánh left và right
        luôn thì ta cứ duyệt và xuất tuần tự left trước rồi đến right cuối cùng là node sau khi duyệt xuống tận cùng của nhánh right
        của node gốc của cây nhị phân thì ta đệ quy lên, trường hợp nào chưa duyệt thì duyệt và xuất ra cứ tuần tự left right node
        cho đến khi xuất và duyệt hết các trường hợp của nhánh right của node gốc rồi cuối cùng chỉ còn lại node gốc là ta chưa duyêt
        nên ta duyệt và xuất node gốc ra cuối cùng là xong đối đối với cách duyệt Left Right Node.*/
    }
}

////Hàm tìm Node lớn nhất trong cây nhị phân
//int TimMax(node* t) {
//    // nếu node cha mà không tồn tại cây con trái và cây con phải
//    if (t->pLeft == NULL && t->pRight == NULL)//Tức là cây nhị phân chỉ tồn tại 1 node duy nhất thì node đó là node max luôn
//        return t->data;
//         
//    
//   
//
//}

//Hàm Tìm MAX trong cây
int TimMax(TREE t)
{
    // CÁCH TỐI ƯU NHẤT
    /*nếu node cha(node root - node gốc) mà không tồn cây con phải - thì node gốc này chính là node ngoài cùng nhất của cây con phải
    - cũng chính là node có giá trị lớn nhất */
    if (t->pRight == NULL)/*Vì phần tử nào lớn hơn node gốc thì qua bên phải còn bé hơn node gốc thì trái nếu không tồn tại nhánh
    phải tức không có phần tử nào lớn hơn node gốc này nữa thì ta trả về node này luôn vì node này chính là node Max rồi*/
    {
        return t->data;
    }
    return TimMax(t->pRight); // duyệt đến node cuối cùng nhất bên cây con phải => để tìm giá trị lớn nhất
    /*Cây nhị phân có Quy tắc vàng là node nhỏ thì sang nhánh trái của node gốc còn node lớn hơn node gốc thì sang nhánh phải của
    node gốc bất di di bất dịch cứ mõi lần thêm phần tử mới vào thì phải luôn so với node gốc trước xem nó như thế nào với node 
    gốc ,nếu nhỏ hơn node gốc thì qua nhánh trái của node gốc khi qua nhánh trái này thì tiếp tục ta lại so với node kế node gốc 
    rồi duyệt tới node kế node vừa duyệt cứ lần lượt xét như vậy cho đến khi đi đến tận cùng của nhánh left(Tức là node lá) cứ 
    xét lần lượt như vậy từ node gốc xuống tận cùng của nhánh nếu xét tới node nào mà node ta thêm vào cây nhị phân lớn hơn node
    ta đang xét thì qua bên phải của node đang xét còn nhỏ hơn node đang xét thì qua trái node đang xét. khi qua nhánh phải này 
    thì tiếp tục ta lại so với node kế node gốc của nhánh right này nếu node ta thêm vào cây nhị phân lớn hơn node ta đang xét 
    thì qua bên phải của node đang xét còn nhỏ hơn node đang xét thì qua trái node đang xét và ta cứ xét như vậy cho đến khi ko
    còn node muốn thêm nữa thì ta đã hoàn thành việc khai triển và lưu dữ liệu dạng cây nhị phân rồi thì ta nhận thấy tính chất
    của của cây nhị phân thì nhỏ thì qua nhánh trái còn lớn thì qua nhánh phải thì tận cùng của nhánh trái là node nhỏ nhất còn
    tận cùng của nhánh phải là node lớn nhất 
    => Nên khi tìm node Max trong dữ liệu mà đã được khai triển và lưu dạng cây nhị phân thì nếu cây nhị phân mà không có nhánh
    phải tức chỉ có node root(node gốc) và nhánh trái thôi thì node root đó chính là node Max luôn vì node nào mà qua nhánh trái
    thì phải nhỏ hơn node root(node gốc) nên không có nhánh phải thì node gốc chính là node MAX, ngược lại nếu cây nhị phân
    mà không có nhánh left hoặc có cả 2 nhánh thì hàm này sẽ duyệt tận đến tận cùng của nhánh phải cứ còn node ở nhánh phải thì 
    ta cứ đệ quy xuống đến khi gặp NULL thì node cuối cùng của nhánh phải này chính là node Max đó là vì sao Việc tìm kiếm thì 
    cấu trúc dữ liệu dạng cây nhị phân luôn tối ưu và nhanh nhất*/
}

//Hàm tìm MIN trong cây
int TimMin(node* t) {
    if (t->pLeft == NULL)/*Vì phần tử nào nhỏ hơn node gốc thì qua bên phải còn bé hơn node gốc thì trái nếu không tồn tại nhánh
    trái tức không có phần tử nào lớn hơn node gốc này nữa thì ta trả về node này luôn vì node này chính là node Max rồi. Còn nếu
    có tồn tại nhánh trái thì ta sẽ đệ quy đến node trái cuối cùng của nhánh trái thì node cuối cùng của nhánh trái này chính là
    node Min vì là cuối cùng nên khi data của node đang là Min thì Không còn phần tử nào nữa tức là gặp NULL điều kiện if đúng 
    nên thực thi lệnh bên trong if tức là trả về(return) node Min luôn.*/
    {
         return t->data;
    }
    return TimMin(t->pLeft);// duyệt đến node cuối cùng nhất bên cây con trái => để tìm giá trị nhỏ nhất
    /*Cây nhị phân có Quy tắc vàng là node nhỏ thì sang nhánh trái của node gốc còn node lớn hơn node gốc thì sang nhánh phải của
    node gốc bất di di bất dịch cứ mõi lần thêm phần tử mới vào thì phải luôn so với node gốc trước xem nó như thế nào với node
    gốc ,nếu nhỏ hơn node gốc thì qua nhánh trái của node gốc khi qua nhánh trái này thì tiếp tục ta lại so với node kế node gốc
    rồi duyệt tới node kế node vừa duyệt cứ lần lượt xét như vậy cho đến khi đi đến tận cùng của nhánh left(Tức là node lá) cứ
    xét lần lượt như vậy từ node gốc xuống tận cùng của nhánh nếu xét tới node nào mà node ta thêm vào cây nhị phân lớn hơn node
    ta đang xét thì qua bên phải của node đang xét còn nhỏ hơn node đang xét thì qua trái node đang xét. khi qua nhánh phải này
    thì tiếp tục ta lại so với node kế node gốc của nhánh right này nếu node ta thêm vào cây nhị phân lớn hơn node ta đang xét
    thì qua bên phải của node đang xét còn nhỏ hơn node đang xét thì qua trái node đang xét và ta cứ xét như vậy cho đến khi ko
    còn node muốn thêm nữa thì ta đã hoàn thành việc khai triển và lưu dữ liệu dạng cây nhị phân rồi thì ta nhận thấy tính chất
    của của cây nhị phân thì nhỏ thì qua nhánh trái còn lớn thì qua nhánh phải thì tận cùng của nhánh trái là node nhỏ nhất còn
    tận cùng của nhánh phải là node lớn nhất
    => Nên khi tìm node Min trong dữ liệu mà đã được khai triển và lưu dạng cây nhị phân thì nếu cây nhị phân mà không có nhánh
    trái tức chỉ có node root(node gốc) và nhánh phải thôi thì node root đó chính là node Min luôn vì node nào mà qua nhánh phải
    thì phải lớn hơn node root(node gốc) nên không có nhánh trái thì node gốc chính là node Min, ngược lại nếu cây nhị phân
    mà không có nhánh right hoặc có cả 2 nhánh thì hàm này sẽ duyệt tận đến tận cùng của nhánh trái cứ còn node ở nhánh trái thì
    ta cứ đệ quy xuống đến khi gặp NULL thì node cuối cùng của nhánh trái này chính là node Min đó là vì sao Việc tìm kiếm thì
    cấu trúc dữ liệu dạng cây nhị phân luôn tối ưu và nhanh nhất*/
}

//Hàm nhập dữ liệu
void Menu(node*& t) {
    while (true)
    {
        system("cls");
        cout << "\n\n\t\t1.Nhap du lieu vao cay";
        cout << "\n\n\t\t2.Xuat du lieu cay nhi phan duyet theo LRN -   Left Right Node";
        cout << "\n\n\t\t3.Tim node MAX trong cay";
        cout << "\n\n\t\t4.Tim node MIN trong cay";
        cout << "\n\n\t\t0.Ket Thuc ";

        int LuaChon;
        cout << "\n\n\t\tMoi lua chon ";
        cin >> LuaChon;

        if (LuaChon < 1 || LuaChon > 4)
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
            cout << "Danh sach cay nhi phan duyet theo LRN -   Left Right Node: ";
            xuatCayDuyetLRN(t);
            system("Pause");
        }
        else if(LuaChon == 3)
        {
            cout << "Node Max cua cay nhi phan la: " << TimMax(t);
            system("Pause");
        }
        else if (LuaChon == 4)
        {
            cout << "Node Min cua cay nhi phan la: " << TimMin(t);
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



