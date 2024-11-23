#include <iostream>
using namespace std;
/*Xóa 1 node bất kì trong cây nhị phân tìm kiếm
Node X là node cần xóa: 
Nếu x: 
1. Là node lá: Xóa bình thường - bởi vì lúc này node x đang là node tự do(Không tồn tại cây con trái và cây con phải)
2. Là node có 1 con: trước khi xóa node x thì ta phải cập nhật mối liên kết giữa node cha của node x với node con(con trái hoặc con
phải) của node x. 
3. Là node có 2 con: trước khi hủy thì ta phải đi tìm 1 cái node thế mạng cho node cần xóa
- tìm node thế mạng phải đảm bảo quy tắc cây nhị phân tìm kiếm tức là nhỏ nằm bên trái và lớn thì nằm bên phải
+ Tìm node trái nhất của cây con phải(cây con phải của cái node cần xóa)
+ Tìm node phải nhất của cây con trái(cây con trái của cái node cần xóa)*/
/*Đề bài: Nhập vào dãy số nguyên : 5 -5 8 7 6 15 14 13 20 khai triển dãy trên về cấu trúc dữ liệu cây nhị phân và xóa bất kì node
nào nào trong cây nhị phân*/

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

//Hàm đi tìm node thế mạng cho việc xóa node có 2 con
void DiTimNodeTheMang(node* &x, node* &y) {/*node y là node thế mạng cho node cần xóa - node này sẽ đảm nhận nhiệm vụ tìm ra node
trái nhất(TÌM NODE TRÁI NHẤT CÂY CON PHẢI) hoặc phải nhất(TÌM NODE PHẢI NHẤT CỦA CÂY CON TRÁI)*/ 

    /*CÁCH 1: Duyệt sang bên trái để tìm node trái nhất của cây con phải*/
    if (y->pLeft != NULL) {/*Duyệt sang bên trái nhất của cây con phải => Tức là khi ta tạo ra hàm DiTimNodeTheMang thì ta sẽ gọi hàm
        này ở trong hàm XoaNode cho trường hợp xóa node có 2 con, khi xóa node có 2 con trước khi xóa ta phải cập nhật lại node
        thay thế node bị xóa để đảm bảo được quy tắc của cây nhị phân là node nhỏ hơn node cha thì qua trái còn lớn hơn node cha thì
        qua phải. Thì ta có 2 cách để tìm ra node thay thế node bị xóa( là node 2 con) thì ở cách 1 là khi ta đã tìm được node cần
        xóa là node x rồi thì bắt đầu ta duyệt qua cây con phải của node bị xóa. Sau khi duyệt qua cây con phải của node muốn xóa rồi
        thì ta bắt đầu duyệt qua node trái nhất của node gọi là node cây con phải của node muốn xóa cho đến khi duyệt và tìm ra đc 
        node trái nhất của node cây con phải của node muốn xóa rồi vì là node trái nhất tức là nó là node lá rồi bên dưới không còn
        nhánh nào nữa nên duyệt thêm 1 lần trái nữa thì là đến NULL. Khi đến NULL thì khối lệnh else sẽ thực thi việc thay thế node 
        muốn xóa(là node x) đc node y thay thế và bây giơ node bị muốn xóa thì mang data của node thay thế và ta xóa thì sẽ xóa node
        y tức là xóa node trái nhất của cây con phải của node muốn xóa còn node muốn xóa(là node x) bây giờ đã mang được node y thay 
        thế.*/
   
        DiTimNodeTheMang(x, y->pLeft);/*Tìm ra node trái nhất tức là ơ bên dưới ta đã cho x là node muốn xóa rồi(node* x = t) ta muốn
        tìm node trái nhất của nhánh phải của node muốn xóa thì ở hàm xoaNOde ta đã gọi hàm DiTimNodeTheMang này bằng cách cho t trỏ
        trỏ qua cây con phải của nó nên khi vào hàm này y bây giờ đang là cây con phải của node muốn xóa nên từ cây con phải của node 
        muốn xóa này ta cho y trỏ(đệ quy) hết về left để tìm node trái nhất của cây con phải của node muốn xóa.*/
    }
    //Đã tìm ra được node trái nhất
    else /*else lúc này tương đương với y->pLeft == NULL, thì y->pLeft lúc này đang mang trên mình là node trái nhất của cây con phải
    của node muốn xóa*/
   
    {
        x->data = y->data;/*Cập nhập lại data của node cần xóa(là node x) chính là data của node thế mạng(là node y)
        ==> Tức là ở hàm XoaNodeBatKi ta có tạo ra 1 node x bằng t tức là node x này mang data của t mà t là node muốn xóa nên khi ta
        đã tạo ra node thay thế cho node muốn xóa là node y rồi thì ta cho node x ban đầu khởi tạo bằng node t thì bây giờ ta gán
        cho x(là node muốn xóa) bằng data của node thay thế cho node x chính là node y nghĩa là node muốn xóa bây giờ đã đc đổi data
        thành của node y rồi.*/
        x = y;/* tức là ta đổi lại node muốn xóa không phải là node x đc gán bằng t ban đầu nữa, mà x(là node muốn xóa) bây giờ chính 
        là node trái nhất của cây con phải của node muốn xóa rồi, đồng nghĩa là khi delete x ở hàm XoaNode thì sau khi thực hiện hàm 
        DiTimNodeTheMang thì node x bây giờ chính là node trái nhất của cây con phải của node muốn xóa.*/
        y = y->pRight;/*bản chất chỗ này chính là cập nhật lại mối liên kết cho node cha của node thế mạng(mà chúng ta sẽ xóa)
        với node con của node thế mạng => Tức là ta đã tìm ra node y là node thế mạng cho node bị xóa tức là node y là node trái
        nhất của nhánh phải của node muốn xóa nên vì y là node trái nhất của nhánh phải của node muốn xóa rồi nên nó không còn liên
        kết với bất kì node nào bên dưới nữa(tức là node lá) nên nó sẽ trỏ đến NULL nên khi ta xóa đi node x(vì qua lệnh x = y ở trên
        thì y bây giờ không còn là node trái nhất của cây con phải của node muốn xóa nữa mà đã đc dổi tên thành node x rồi) thì ban
        đầu khi tìm thấy y để thay thế cho node muốn xóa thì trên y có 1 node node đó chính là node cha của y vì node cha của y đang 
        liên kết(trỏ) tới y nên ở lệnh y = y->pRight; là ta cho y bây giờ bằng thằng y trỏ đến cây con phải của y mà y là node trái
        nhất(tức y là node lá rồi) thì y không còn nhánh con nào nữa đồng nghĩa với việc y = y->pRight; là y = NULL mà node cha của
        node y đang liên kết với y nên khi ta cập nhật lại y là bằng NULL thì node cha của node y đang trỏ đến NULL.*/
    }

    ///*CÁCH 2: Duyệt sang bên phải để tìm node phải nhất của cây con trái*/
    ////Duyệt sang bên phải nhất của cây con trái
    //if (x->pRight != NULL)/*Duyệt sang bên phải nhất của cây con phải => Tức là khi    ta tạo ra hàm DiTimNodeTheMang thì ta sẽ gọi hàm
    //này ở trong hàm XoaNode cho trường hợp xóa node có 2 con, khi xóa node có 2 con trước khi xóa ta phải cập nhật lại node
    //thay thế node bị xóa để đảm bảo được quy tắc của cây nhị phân là node nhỏ hơn node cha thì qua trái còn lớn hơn node cha thì
    //qua phải.Thì ta có 2 cách để tìm ra node thay thế node bị xóa(là node 2 con) thì ở cách 2 là khi ta đã tìm được node cần
    //xóa là node x rồi thì bắt đầu ta duyệt qua cây con trái của node bị xóa.Sau khi duyệt qua cây con trái của node muốn xóa rồi
    //thì ta bắt đầu duyệt qua node phải nhất của node gọi là node cây con trái của node muốn xóa cho đến khi duyệt và tìm ra đc
    //node phải nhất của node cây con trái của node muốn xóa rồi vì là node phải nhất tức là nó là node lá rồi bên dưới không còn
    //nhánh nào nữa nên duyệt thêm 1 lần phải nữa thì là đến NULL.Khi đến NULL thì khối lệnh else sẽ thực thi việc thay thế node
    //muốn xóa(là node x) đc node y thay thế và bây giờ node muốn xóa thì mang data của node thay thế và ta xóa thì sẽ xóa node
    //y tức là xóa node phải nhất của cây con trái của node muốn xóa còn node muốn xóa(là node x) bây giờ đã được node y thay thế.*/
    //{
    // DiTimNodeTheMang(x, y->pRight);//Tìm ra node phải nhất
    //}
    // //Đã tìm ra được node phải nhất
    //else/*else lúc này tương đương với y->pRight == NULL, thì y->pRight lúc này đang mang trên mình là node phải nhất của cây con trái
    // của node muốn xóa* /
    //{
    //    x->data = y->data;/*Cập nhập lại data của node cần xóa(là node x) chính là data của node thế mạng(là node y)
    /*    ==> Tức là ở hàm XoaNodeBatKi ta có tạo ra 1 node x bằng t tức là node x này mang data của t mà t là node muốn xóa nên khi ta
          đã tạo ra node thay thế cho node muốn xóa là node y rồi thì ta cho node x ban đầu khởi tạo bằng node t thì bây giờ ta gán
          cho x(là node muốn xóa) bằng data của node thay thế cho node x chính là node y nghĩa là node muốn xóa bây giờ đã đc đổi data
          thành của node y rồi.* /
    //    x = y;/* tức là ta đổi lại node muốn xóa không phải là node x đc gán bằng t ban đầu nữa, mà x(là node muốn xóa) bây giờ chính 
    /*    là node phải nhất của cây con trái của node muốn xóa rồi, đồng nghĩa là khi delete x ở hàm XoaNode thì sau khi thực hiện hàm
          DiTimNodeTheMang thì node x bây giờ chính là node phải nhất của cây con trái của node muốn xóa.* /
    //    y = y->pLeft;/*bản chất chỗ này chính là cập nhật lại mối liên kết cho node cha của node thế mạng(mà chúng ta sẽ xóa)
    /*    với node con của node thế mạng = > Tức là ta đã tìm ra node y là node thế mạng cho node bị xóa tức là node y là node phải
          nhất của nhánh trái của node muốn xóa nên vì y là node phải nhất của nhánh trái của node muốn xóa rồi nên nó không còn liên
          kết với bất kì node nào bên dưới nữa(tức là node lá) nên nó sẽ trỏ đến NULL nên khi ta xóa đi node x(vì qua lệnh x = y ở trên
          thì y bây giờ không còn là node phải nhất của cây con trái của node muốn xóa nữa mà đã đc dổi tên thành node x rồi) thì ban
          đầu khi tìm thấy y để thay thế cho node muốn xóa thì trên y có 1 node node đó chính là node cha của y vì node cha của y đang
          liên kết(trỏ) tới y nên ở lệnh y = y->pLeft; là ta cho y bây giờ bằng thằng y trỏ đến cây con trái của y mà y là node phải
          nhất(tức y là node lá rồi) thì y không còn nhánh con nào nữa đồng nghĩa với việc y = y->pLeft; là y = NULL mà node cha của
          node y đang liên kết với y nên khi ta cập nhật lại y là bằng NULL thì node cha của node y đang trỏ đến NULL.* /*/
    //}
}

//Xóa 1 node bất kì trong cây nhị phân tìm kiếm
void XoaNode(node*& t, int data) {//Data chính là cái giá trị của node cần xóa 
    //Nếu cây đang rỗng
    if (t == NULL)
    {
        return;//Kết thúc hàm 
    }
    else
    {
        //Nếu data(Tức là giá trị cần xóa) nhỏ hơn node gốc
        if (data < t->data)
        {
            XoaNode(t->pLeft, data);//Thì duyệt qua nhánh trái của cây
        }
            //Nếu data(Tức là giá trị cần xóa) lớn hơn node gốc
        else if (data > t->data)
        {
            XoaNode(t->pRight, data);//Thì duyệt qua nhánh phải của cây
        }
        else//data == t->data tức là đã tìm ra node cần xóa
        {
            node* x = t;//Node x chính là node thế mạng - Tức là ta sẽ xóa node x này

            /*Node cần xóa là node lá hoặc node 1 con => trước khi xóa node x thì ta phải cập nhật mối liên kết giữa node cha của 
            node x với node con(con trái hoặc con phải) của node x.*/
            //Nếu như nhánh trái bằng NULL <=> Đây là cây có 1 con chính là cây con phải
            if (t->pLeft == NULL)
            {
                t = t->pRight;/*Duyệt sang phải của node cần xóa để cập nhật mối liên kết giữa node cha của node cần xóa với node 
                con của node cần xóa
                => Nghĩa là: Khi ta đã tìm thấy node cần xóa rồi thì ta đã khởi tạo node x bằng node t thì node x bây giờ là node
                mang data của t, xóa x chính là xóa node t trong danh sách cây, khi đó node mà ta muốn xóa khi tìm thấy không phải
                là node t nữa mà ta đã đặt nó với tên khác là node x. Sau khi đã khởi tạo node thế mạng cho node muốn xóa xong thì
                t lúc này vẫn đang mang data của node muốn xóa nên khi này ta sẽ cập nhật lại mối liên kết cho node cha của node muốn 
                xóa(là node x) liên kết với node con của node muốn xóa vì đây là xóa node lá hoặc node 1 con nên khi nhánh trái của
                node muốn xóa mà không có node tức là null thì ta cập nhật lại cho cho node cha của node muốn xóa(là node x) liên 
                kết với node cây con phải của node muốn xóa bằng cách là cho (t = t->pRight) t là node muốn xóa mà ta đã tạo node 
                thế mạng cho t là x thì t bây giờ tự do không còn là node bị xóa nữa nên ta cho bằng với node cây con phải của node
                muốn xóa, mà ban đầu node cha của node muốn xóa đang liên kết với t bây giờ ta cho t bằng node cây con phải của node
                muốn xóa thì node cha của node muốn xóa vốn dĩ là đang liên kết với t nên t thây đổi thành node cây con phải của node
                muốn xóa thì node cha của node muốn xóa vẫn sẽ liên kết với node mà có tên là t nhưng t bây giờ là node cây con phải
                của node muốn xóa rồi chứ không còn là node t bị xóa nữa mà node bị xóa bây giờ là node mang tên x vì x tạo ra là
                để thế mạng để cho t cập nhật lại muốn liên kết giữa node cha của node x(là node muốn xóa) và node cây con phải của
                node x(là node muốn xóa) xong ta delete x là delete node mà ta muốn xóa trong cây*/
            }
            //Nếu như nhánh phải bằng NULL <=> Đây là cây có 1 con chính là cây con trái
            else if (t->pRight == NULL)
            {
                t = t->pLeft;/*Duyệt sang trái của node cần xóa để cập nhật mối liên kết giữa node cha của node cần xóa với node con
                của node cần xóa
                => Nghĩa là: Khi ta đã tìm thấy node cần xóa rồi thì ta đã khởi tạo node x bằng node t thì node x bây giờ là node
                mang data của t, xóa x chính là xóa node t trong danh sách cây, khi đó node mà ta muốn xóa khi tìm thấy không phải
                là node t nữa mà ta đã đặt nó với tên khác là node x. Sau khi đã khởi tạo node thế mạng cho node muốn xóa xong thì
                t lúc này vẫn đang mang data của node muốn xóa nên khi này ta sẽ cập nhật lại mối liên kết cho node cha của node muốn 
                xóa(là node x) liên kết với node con của node muốn xóa vì đây là xóa node lá hoặc node 1 con nên khi nhánh phải của
                node muốn xóa mà không có node tức là null thì ta cập nhật lại cho cho node cha của node muốn xóa(là node x) liên 
                kết với node cây con trái của node muốn xóa bằng cách là cho (t = t->pLeft) t là node muốn xóa mà ta đã tạo node 
                thế mạng cho t là x thì t bây giờ tự do không còn là node bị xóa nữa nên ta cho bằng với node cây con trái của node
                muốn xóa, mà ban đầu node cha của node muốn xóa đang liên kết với t bây giờ ta cho t bằng node cây con trái của node
                muốn xóa thì node cha của node muốn xóa vốn dĩ là đang liên kết với t nên t thây đổi thành node cây con trái của node
                muốn xóa thì node cha của node muốn xóa vẫn sẽ liên kết với node mà có tên là t nhưng t bây giờ là node cây con trái
                của node muốn xóa rồi chứ không còn là node t bị xóa nữa mà node bị xóa bây giờ là node mang tên x vì x tạo ra là
                để thế mạng để cho t cập nhật lại muốn liên kết giữa node cha của node x(là node muốn xóa) và node cây con trái của
                node x(là node muốn xóa) xong ta delete x là delete node mà ta muốn xóa trong cây*/
            }
            else{ /*node cần xóa là node có 2 con trước khi hủy thì ta phải đi tìm 1 cái node thế mạng cho node cần xóa
                - tìm node thế mạng phải đảm bảo quy tắc cây nhị phân tìm kiếm tức là nhỏ nằm bên trái và lớn thì nằm bên phải. Và có
                hai cách tìm node thế mạng khi node có 2 con: 
                + Cách 1: Tìm node trái nhất của cây con phải(cây con phải của cái node cần xóa)
                + Cách 2: Tìm node phải nhất của cây con trái(cây con trái của cái node cần xóa)*/ 
            
                // CÁCH 1: Tìm node trái nhất của cây con phải(cây con phải của cái node cần xóa)
                DiTimNodeTheMang(x, t->pRight);

                // CÁCH 2: Tìm node phải nhất của cây con trái(cây con trái của cái node cần xóa)
                //DiTimNodeTheMang(x, t->pLeft); 
            }
            delete x;//Xóa node cần xóa
        }
    }
}

//Hàm nhập dữ liệu
void Menu(node*& t) {
    while (true)
    {
        system("cls");
        cout << "\n\n\t\t1.Nhap du lieu vao cay";
        cout << "\n\n\t\t2.Xuat du lieu cay nhi phan duyet theo LRN -   Left Right Node";
        cout << "\n\n\t\t3.Xoa Node bat ki trong Cay";
        cout << "\n\n\t\t0.Ket Thuc ";

        int LuaChon;
        cout << "\n\n\t\tMoi lua chon ";
        cin >> LuaChon;

        if (LuaChon < 1 || LuaChon > 3)
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
            int data;
            cout << "Nhap gia tri cua node can xoa: ";
            cin >> data;
            XoaNode(t, data);
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




