#include <iostream>
using namespace std;
/*Đề bài: Nhập danh sách Queue chứa các số nguyên, sau đó xuất ra màn hình các giá trị số nguyên đó   */

//Khai báo cấu trúc của 1 cái node  
struct node
{
    int data;//Queue đang chứa các số nguyên
    struct node* pNext;//Con trỏ liên kết giữa các node với nhau
};

//Khởi tạo 1 cái node
node* KhoiTaoNode(int x) {
    node* p = new node;
    if (p == NULL)
    {
        cout << "Cap phat khong thanh cong. Bo nho da day !";
        return NULL;
    }
    p->data = x;//Thêm giá trị của biên x vào trong data của cái node
    p->pNext = NULL;
    return p;
}

//Khai báo cấu trúc Queue
/*Vì cơ chế của Queue là FIFO - FIRT IN FIRT OUT(Vào trước ra trước) Tức là ra là ra ở đầu danh sách còn vào thì là vào 
cuối danh sách. Ví dụ ta có dãy 1 2 3 ta thêm 4 vào thì vào cuối danh sách là 1 2 3 4 còn ra là ra ở đầu danh sách 2 3 4
Nên ta tạo ra 2 con trỏ đầu và cuối để quản lí danh sách queue thuận tiện cho việc thêm vào cuối và lấy ở đầu*/
struct queue
{
    node* pHead;//Dùng con trỏ đầu để quản lí queue
    node* pTail;//Dùng con trỏ cuối để quản lí danh sách Queue
};

//Hàm khởi tạo stack
void KhoiTaoQueue(queue & q) {
     q.pHead = NULL;
     q.pTail  = NULL;
}

//===================== ISEMPTY: KIỂM TRA QUEUE CÓ RỖNG HAY KHÔNG ================================
bool IsEmpty(queue& q) {

    //Nếu danh sách rỗng
    if (q.pHead == NULL)
        return true;

    return false;//Danh sách có phần tử 
}

//===================== PUSH: THÊM PHẦN TỬ VÀO ĐẦU QUEUE - FIFO ================================
bool Push(queue& q, node* p) {

    //Bắt trường hợp p không có giá trị
    if (p == NULL)
        return false;
    //Danh sách rỗng    
    if (IsEmpty(q) == true)/*IsEmpty(s) là Hàm kiểm tra danh sách có rỗng hay không mà ta đã tạo ở bên trên và ta cho hàm 
        trả về giá trị false nếu như danh sách không rỗng còn là true thì danh sách đang rỗng*/
        q.pHead = q.pTail = p;/*Node p chính là node đầu của danh sách. Vì danh sách đang rỗng nên thêm phần tử vào thì phần tử
        được thêm cũng là phần tử đầu tiên của danh sách */
    else
    {
        /* - Vì Queue theo cơ chế FIFO - Firt In Firt Out là vào trước ra trước thêm vào cuối ra ở đầu
        + Ví dụ: danh sách ban đầu có 1 phần tử là 1. Ta muốn thêm 2 vào danh sách mà cơ chế của Queue là Firt in firt out -
        vào trước ra trước nên thêm là thêm vào cuối của phần tử đã có sẵn trong danh sách tức là danh sách bây giờ là:
        1 2
        Vậy nên bài toán trở thành thêm phần tử vào cuối danh sách của danh sách liên kết đơn*/
        q.pTail->pNext = p;//Liên kết con trỏ cuối của danh sách với phần tử p cần thêm vào 
        q.pTail = p;//Cập nhật lại con trỏ cuối là node p
    }
    return true;
}

//=====================  POP: LẤY PHẦN TỬ ĐẦU QUEUE VÀ HỦY NÓ ĐI - FIFO ================================
bool Pop(queue & q, int& x) {/*Vì cơ chế Pop lấy ra và trả về giá trị đối tượng đầu queue nên phải truyền vào int& x,
    x chính là giá trị cần lấy trong node. truyền tham số int &x vào hàm Pop là để cho phép ta có thể lấy giá trị của 
    phần tử đầu stack ra và xem trước giá trị đó, trước khi nó bị loại bỏ khỏi stack. Nếu ta không truyền tham số cho 
    biến x(x chính là gía trị cần lấy trong node) thì ở hàm xuatStack khi ta tạo 1 biến x để truyền vào cho hàm Pop(Để 
    lấy giá tri đầu danh sách stack ra xem) thì chương trình sẽ báo lỗi ở biến x mà ta đã tạo ở hàm xuatStack là biến 
    x chưa khởi tạo giá trị vì giá trị biến x của hàm Pop là tham chiếu thì khi lấy phần tử đầu danh sách ra gán vào 
    biến x thì biến x đã được cập nhật giá trị và dùng tham chiếu đề luu lại thay đổi đó và truyền địa chỉ giá trị của 
    biến x ở hàm Pop xuống cho biến x mà ta đã tạo ở hàm xuatStack để có thể truyền tới hàm Pop ở hàm xuatStack và có 
    thể xuất giá trị x đó ra xem được.*/

    //Nếu danh sách rỗng
    if (IsEmpty(q) == true)
        return false;
    else
    {
        /* - Vì cơ chế của stack là vào sau ra trước. Nên khi lấy ra thì phải lấy thằng đầu tiên danh sách ra trước
        + Ví dụ: Danh sách ta có 3 phần tử là 3 2 1 và muốn lấy thì phải lấy phần tử đầu danh sách nên danh sách ta
        sau khi lấy phần tử đầu tiên thì sẽ con lại là :
        2 1
        Vậy nên bài toám trở thành xóa phần tử đầu của danh sách liên kết đơn.*/
        node* p = q.pHead;/*Tạo node p là node thế mạng, Tức cho node p là node đầu của danh sách khi xóa là ta node p
        chứ k phải xóa con trỏ đầu queue là phead vì giống danh sách liên kết đơn các node trong queue cũng liên kết với
        nhau thông qua con trỏ và khi con trỏ đầu mà bị xóa dẫn đến mất các node còn lại phía sau danh sách như rắn mất
        đầu. Nên nhớ queue danh sách liên kết đơn cũng được quản lí bởi 2 con trỏ đầu pHead và cuối là pTail*/
        x = p->data;/*Gán giá trị của node đầu vào biến x. Vì đây là cơ chế lấy phần tử đầu nên khi lấy thì ta phải cho nó
        bằng biến x tức là giá trị đầu tiên trong danh sách bị lấy sẽ gán vào biến x.*/
        q.pHead = q.pHead->pNext;//Cập nhật lại con trỏ đầu là pHead là phần tử tiếp theo
        delete p;/*Lấy đi phần tử đầu của danh sách => Chứ k phải lấy đi pHead vì ta đã cập nhật lại pHead là phần tử kế
        phần tử đầu trong danh sách */
    }
    return true;//Lấy phần tử đầu queue thành công
}

//===================== TOP: XEM THÔNG TIN PHẦN TỬ ĐẦU STACK - VÀ KHÔNG HỦY NÓ ĐI NHÉ ================================
bool Top(queue& q, int& x) {/*x chính là giá trị cần lấy ra để xem. Lý do cần truyền tham số vào hàm Top là để hàm
    có thể truyền lại giá trị của phần tử đầu đầu danh sách cho ta. Nếu ta không truyền tham số, hàm Top không biết 
    phải lấy giá trị của phần tử nào và trả về cho ta.*/

    //Nếu danh sách rỗng
    if (IsEmpty(q) == true)
        return false;

    x = q.pHead->data;//Lấy giá trị của phần tử đầu stack ra để xem
    return true;

}

//Hàm xuất stack
void xuatQueue(queue q)
{
    while (IsEmpty(q) == false)
    {
        int x;
        Pop(q, x);
        cout << x << " ";
    }

    /*Vì ta xuất phần tử ra bằng cơ chế Pop tức là lấy phần tử đầu danh sách ra xem và hủy nó đi nên khi lấy phần
    tử đầu của danh sách stack xuất ra màn hình cho ta xem thì các phần tử cũng bị xóa nên danh sách sẽ rỗng đây
    là thông báo cho ta biết sau khi lấy phần tử đầu danh sách ra xem thì danh sách lúc đấy là rỗng. */
    if (IsEmpty(q) == true)
        cout << "\nDanh sach dang rong !";
    else
        cout << "\nDanh sach dang ton tai phan tu !";
}

//Hàm xuất phần tử đâu danh sách ra xem - không hủy nó (Top)
void xuatPhanTuDauDanhSachQueue(queue q) {
    int x;
    Top(q, x);
    cout << "\nPhan tu dau stack la: " << x;
}

//Hàm nhập danh sách các số nguyên trong stack
void NhapQueue(queue& q) {
    short luaChon;
    while (true)
    {
        system("cls");
        //cout << "\n\n\t\tNhap sai moi ban nhap lai !";
        cout << "\n\n\t\t1.Them phan tu vao Queue - Push";
        cout << "\n\n\t\t2.Xuat danh sach ra man hinh - Pop ";
        cout << "\n\n\t\t3.Lay phan tu dau danh sach ra xem - Top";
        cout << "\n\n\t\t0.Ket Thuc ";

        cout << "\n\n\t\tMoi lua chon: ";
        cin >> luaChon;

        if (luaChon == 1)
        {
            int x;
            cout << "Nhap phan tu can them: ";
            cin >> x;

            node* p = KhoiTaoNode(x);
            Push(q, p);
        }
        else if (luaChon == 2)
        {
            xuatQueue(q);
            system("Pause");
        }
        else if (luaChon == 3)
        {
            xuatPhanTuDauDanhSachQueue(q);
            system("Pause");
        }
        else if (luaChon == 0)
        {
            break;
        }
    }
}
int main()
{
    queue q;
    KhoiTaoQueue(q);

    NhapQueue(q);

    system("Pause");
}
