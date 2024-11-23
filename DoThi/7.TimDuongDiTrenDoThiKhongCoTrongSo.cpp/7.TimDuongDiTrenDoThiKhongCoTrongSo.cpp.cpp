//================================ ĐỒ THỊ VÔ HƯỚNG ==================================
#if 0
#include <iostream>
#include<vector>
#include<queue>
using namespace std;

/*Áp dụng DFS(Thuật toán tìm kiếm theo chiều sau của đồ thị) và BFS(Thuật toán tìm kiềm theo chiều rộng của đồ thị) vào bài toán tìm 
đườnh đi và truy vết đường đi của đồ thị cả vô hướng lẫn có hướng chỉ khác các input nhập vào mà thôi.

***Input và Output của đồ thị vô hướng***
Input: Là nhập  vào n đỉnh = 10 là từ    | Output : Kiểm tra xem giữa 2 đỉnh bất kì hay còn gọi là từ đỉnh s tới đỉnh t có đường đi 
1 đến 10, m cạnh = 8 và đường đi giữa    | hay không nếu có thì truy vết đường đi.
2 đỉnh bất kì gọi là từ đỉnh s tới đỉnh  |
t. 8 cạnh gồm : 1 2                      |
                2 3                      |
                2 4                      |
                3 6                      |
                3 7                      |
                6 7                      |
                5 8
                8 9
                                                                                                                                  
***Input và Output của đồ thị có hướng***
Input: Là nhập  vào n đỉnh = 10 là từ    | Output : Kiểm tra xem giữa 2 đỉnh bất kì hay còn gọi là từ đỉnh s tới đỉnh t có đường đi 
1 đến 10, m cạnh = 10 và đường đi giữa   | hay không nếu có thì truy vết đường đi.
2 đỉnh bất kì gọi là từ đỉnh s tới đỉnh  |
t. 8 cạnh gồm : 1 2                      |
                2 3                      |
                2 4                      |
                3 6                      |
                3 7                      |
                5 8                      |
                5 10
                6 7
                7 5
                8 9*/
           

int n, m, t, s;//n là số đỉnh ,m là số cạnh của đồ thị
vector<int> adj[20];//Tạo vector adj để lưu danh sách kề của đồ thị
bool visited[20];//Mảng chứa các đỉnh true(là đỉnh đó đã đc thăm) còn false(là đỉnh đó chưa đc thăm) 
int parent[20];//Mảng này chứa đỉnh cha của đỉnh vừa đc thăm 

//Hàm nhập input của đề
void inp() {
    cout << "Nhap vao n dinh va m canh cua do thi: \n";
    cin >> n >> m;

    cout << "Nhap vao dinh x va dinh y tao thanh canh cua do thi: \n";
    for (short i = 0; i < m ; i++)
    {
        int x, y;
        cin >> x >> y;

        adj[x].push_back(y);
        //adj[y].push_back(x);
    }
}

//Áp dụng DFS(thuật toán tìm kiếm theo chiều sau của đồ thị) vào tìm đường và truy vết đường đi  
void DFS(int u) {
    visited[u] = true;
    for (int v : adj[u]) {
        if (!visited[v])
        {
            parent[v] = u;/*Ghi nhận lại cha của v là u, tức là  đỉnh u đã đc thăm rồi từ đỉnh u mở rộng ra để thăm các đỉnh kề với 
            đỉnh u thì đỉnh mà kề với đỉnh u là đỉnh v thì đỉnh u là cha của đỉnh v */
            DFS(v);
        }
    }
}

//Áp dụng BFS(thuật toán tìm kiếm theo chiều rộng của đồ thị) vào tìm đường và truy vết đường đi 
void BFS(int u) {
    queue<int> q;
    q.push(u);
    visited[u] = true;

    while (!q.empty())
    {  
        int v = q.front();
        q.pop();
        for (int x : adj[v]) {
            if (!visited[x]) {
                q.push(x);
                visited[x] = true;
                parent[x] = v;
            }
        }
    }
}

/*Hàm để tìm đường giữa 2 đỉnh bất kì hay gọi cho dễ hiểu là tìm đường giữa đỉnh s(là đỉnh đầu của đường đi) đến đỉnh t(là đỉnh cuối của
đường đi)*/
void Path(int s, int t) {
    cout << "Nhap vao s va t de kiem tra xem tu s den t co duong di hay khong: \n";
    cin >> s >> t;
    memset(visited, false, sizeof(visited));//Mặc định ban đầu cho tất cả các đỉnh là false(tức là chưa đc thăm)
    memset(parent, 0, sizeof(parent));/*Mặc định parent(là cha của các đỉnh) ban đầu là bằng không tức là ban đầu tất cả các đỉnh không
    có cha*/
    BFS(s);/*//DFS(s); vì là chỉ tìm đường đi thôi nên áp dụng 1 trong 2 thuật toán DFS hoặc DFS cái này cũng đc, còn đối với truy vết
    đường đi thì phải dùng DFS hoặc BFS tùy thuộc vào yêu cầu đề bài để áp dụng DFS hoặc BFS cho phù hợp với yêu cầu, đối với truy vết
    đường đi ngắn nhất của đồ thị không có trọng số thì thuật toán BFS(tìm kiếm theo chiều rộng của đồ thị) sẽ truy vết ra đc đường đi
    ngắn nhất giữa 2 đỉnh bất kì.Giải thích Dòng này: Gọi s là đỉnh đầu của đường đi và t là đỉnh kết thúc đường đi nếu đỉnh s tới đỉnh 
    t mà có đường đi thì ta chỉ cần truyền đỉnh s(là đỉnh đầu của đường đi) và hàm DFS thì trong hàm DFS nó sẽ tự động thăm tất cả các
    đỉnh trên đường đi từ s đến t còn nếu từ đỉnh s tới đỉnh t mà không có đường đi thì đỉnh t sẽ không đc thăm.*/
    if (!visited[t]) {/*Kiểm tra nếu t mà là false thì từ đỉnh s tới đỉnh t k có đường đi vì đỉnh t là đỉnh cuối kết thúc đường đi, mà
                    ta truyền vào hàm DFS là đỉnh s(là đỉnh đầu của đường đi) nếu từ s đến t mà có đường đi thì khi đỉnh s đc truyền vào
                    hàm DFS từ s sẽ mở rộng và thăm đến đỉnh t luôn, vì cơ chế thuật toán DFS(tìm kiếm theo chiều sau của đồ thị) ta đã
                    học rất kĩ là từ 1 đỉnh đc thăm nó sẽ lan rộng ra thăm các đỉnh bằng cách xét đỉnh kề với đỉnh đã đc thăm để thăm
                    tất cả các đỉnh mà kề với đỉnh đã đc thăm. từ đỉnh s đến đỉnh t mà có đường đi thì tất cả các đỉnh trên đường đi từ
                    đỉnh đầu đường đi(là đỉnh s) tới đỉnh kết thúc đường đi(là đỉnh t) đều là true đồng nghĩa với đỉnh cuối đường đi là
                    đỉnh t cũng phải true thì từ đỉnh s đến đỉnh t mới có đường đi còn đỉnh t mà chưa đc thăm tức là từ đỉnh s tới đỉnh 
                    t không có đường đi.*/
        cout << "Tu dinh " << t << " toi dinh " << s << " khong co duong     di !";
    }
    else{/*Ngược lại nếu t mà là true thì từ đỉnh s tới đỉnh t có đường đi vì đỉnh t là đỉnh cuối kết thúc đường đi, mà ta
        truyền vào hàm DFS là đỉnh s(là đỉnh đầu của đường đi) nếu từ s đến t mà có đường đi thì khi đỉnh s đc truyền vào
        hàm DFS từ s sẽ mở rộng và thăm đến đỉnh t luôn, vì cơ chế thuật toán DFS(tìm kiếm theo chiều sau của đồ thị) ta đã
        học rất kĩ là từ 1 đỉnh đc thăm nó sẽ lan rộng ra thăm các đỉnh bằng cách xét đỉnh kề với đỉnh đã đc thăm để thăm
        tất cả các đỉnh mà kề với đỉnh đã đc thăm. từ đỉnh s đến đỉnh t mà có đường đi thì tất cả các đỉnh trên đường đi từ
        đỉnh đầu đường đi(là đỉnh s) tới đỉnh kết thúc đường đi(là đỉnh t) đều là true đồng nghĩa với đỉnh cuối đường đi là
        đỉnh t cũng phải true thì từ đỉnh s đến đỉnh t mới có đường đi còn chưa đc thăm tức là từ đỉnh s tới đỉnh t không có
        đường đi.*/
    
        //Truy vết đường đi
        vector<int> path;
        while (t!= s){/*Khi truy vết đường đi thì ta phải truy vết từ đỉnh cuối của đường đi(là đỉnh t) cho đến khi gặp đc đỉnh đầu thì 
            dừng lại. bằng cách nếu từ đỉnh cuối đường đi ta xét có khác với đỉnh đầu đường đi hay không nếu khác ta xuất ra đỉnh cuối
            rồi ta lại lấy đỉnh parent(cha) của đỉnh cuối xét xem có khác đỉnh đầu đường đi hay k nếu khác thì ta lại xuất đỉnh cha của
            đỉnh vừa xét ra và lấy đỉnh parent(cha) của đỉnh vừa xét xem có khác với đỉnh đầu đường đi hay không nếu khác thì lại xuất 
            đỉnh parent(cha) của đỉnh vừa xét rồi lại lấy cha của của đỉnh vừa xét làm tương tự cứ như thế cho đến khi đỉnh parent(cha)
            của đỉnh vừa xét mà bằng đỉnh s thi ta dừng lại */
            path.push_back(t);/*path này là vector chứa các đỉnh khi truy vết đường đi, truy vết đường đi sẽ truy từ đỉnh cuối về cho 
            đến khi gặp đỉnh đầu thì dừng lại khác với hàm mà chứa nó là hàm Path hàm Path là hàm xử lí kiểm tra xem giữa 2 đỉnh bất 
            kì xem có đường đi hay không và đường đi của 2 đỉnh đó sẽ gồm những đỉnh nào(tức là truy vết đường đi)*/

            //Truy ngược lại từ đỉnh t(là đỉnh cuối đườnh đi) cho đến khi gặp đỉnh s(là đỉnh đầu) thì hoàn thành truy vết
            t = parent[t];/*Truy vết đường đi là ta truy từ đỉnh t(là đỉnh cuối của đường đi) cho đến khi gặp đỉnh s thì dừng(vòng 
            lặp while sẽ duyệt từ đỉnh t cho đến khi đỉnh t bằng đỉnh s thì dừng) bằng cách đầu tiên vô vòng lặp thì đỉnh t đang là
            đỉnh ở cuối đường đi sau đó ta push_back đỉnh t(là đỉnh cuối của đường đi) vào vector path sau đó vì thảo đk là đỉnh t 
            != s nên thõa đk nên t lúc này cho bằng parent của t tức là t lúc này chính là đỉnh đã mở rộng ra để duyệt t hay còn gọi
            là đỉnh cha của đỉnh t thì t lúc này là cha của đỉnh t cứ như vậy đỉnh cha của đỉnh t này lại quay lên vòng lặp while 
            xem nó có bằng đỉnh đầu chưa nếu chưa thì cho t vào vector path và cho t hiện tại bằng đỉnh cha của nó cứ như thế cho
            đến khi gặp t = s thì dừng lại.*/
        }   
        path.push_back(s);/*Vì là khi lần ngược lại đường đi cho đến khi gặp đỉnh s thì dừng nên đỉnh s chưa đc thêm vào danh sách
        path( là danh sách chứa các đỉnh trên đường đi từ s đến t) mà đỉnh s cũng là đỉnh đầu đường đi nên sau khi đã truy vết từ 
        đỉnh t(là đỉnh cuối của đường đi) cho đến đỉnh kề với đỉnh đầu đường đi thì ta push đỉnh đầu của đường đi vào là xong. 
        ví dụ: từ đỉnh 1 đến đỉnh 7 là có đường đi thì ta truy vết đường đi từng đỉnh 1 đến đỉnh 7 bằng cách truy ngược lại từ đỉnh 
        7 về đến đỉnh con của đỉnh s thì sau khi truy thì danh sách các đỉnh trên đường đi lúc này 7 6 3 2 còn thiếu đỉnh s( là đỉnh 
        1) vì chương trình ta truy về đến khi gặp đỉnh 2 thì dừng nên đỉnh 1 chưa đc thêm vào vector path thì sau khi truy và danh 
        sách thực hiện xong bước truy là 7 6 3 2 và ta push đỉnh s vào nữa là 7 6 3 2 1 là hoàn thành truy vết đường đi */

        reverse(path.begin(), path.end());/*Lần(đảo) ngược lại. Có nghĩa là khi ta đã biết đc đường đi của 2 đỉnh là đi qua gồm những đỉnh nào rồi thì do ta truy vết 
            đường đi bằng cách truy từ đỉnh cuối lên ngược lại đỉnh đầu nên vector path lúc này chứa các đỉnh ngược lại của đường
            đi ví dụ từ đỉnh 1 tới đỉnh 7 (như trong vở ta đã giải thích rất rõ cơ chế kiểm tra xem 2 đỉnh 1 và 7 có đường đi hay 
            không và cơ chế truy vết đường đi của đỉnh 1 tới đỉnh 7 nếu quên hãy mở vở đồ thị 2 bài 11 phần 2 la mã để xem lại) thì
            khi truy vết đường đi bắt đầu từ đỉnh 7 thì ta sẽ lưu các đỉnh trên đường đi từ đỉnh 7 cho đến khi gặp đỉnh đầu của 
            đầu của đường đi thì vòng lặp while sẽ dừng lại thì khi đó đường đi lưu trong vector path đc truy từ đỉnh 7 ngược lại 
            đỉnh 1 lúc này là 7 6 3 2 1 đây là đường đi từ đỉnh 1 tới đỉnh 7 nhưng nó bị ngược nên ta cần phải đảo nó ngược lại là
            1 2 3 6 7 mới đúng đường đi từ đỉnh 1 tới đỉnh 7.*/

        //Xuất đường đi từ đỉnh s đến đỉnh t sau khi truy vết và lần(đảo) ngược lại
        cout << "Co duong di !\n";
        cout << "Duong di sau khi truy vet la : ";
        for (int x : path) {
            cout << x << " ";
        }
    }
}

int main()
{
    inp();
    Path(s, t);
        
}

#endif // 0

//=====================ĐỒ THỊ CÓ HƯỚNG============================
#include <iostream>
#include<vector>
#include<queue>
using namespace std;

/*Áp dụng DFS(Thuật toán tìm kiếm theo chiều sau của đồ thị) và BFS(Thuật toán tìm kiềm theo chiều rộng của đồ thị) vào bài toán tìm
đườnh đi và truy vết đường đi của đồ thị cả vô hướng lẫn có hướng chỉ khác các input nhập vào và đồ thị có hướng thì ở input nhập vào
danh sách cạnh và lưu dạng danh sách kề chỉ push đỉnh y vào đỉnh x thôi chứ không có hướng ngược lại mà thôi .

***Input và Output của đồ thị có hướng***
Input: Là nhập  vào n đỉnh = 10 là từ    | Output : Kiểm tra xem giữa 2 đỉnh bất kì hay còn gọi là từ đỉnh s tới đỉnh t có đường đi
1 đến 10, m cạnh = 10 và đường đi giữa   | hay không nếu có thì truy vết đường đi.
2 đỉnh bất kì gọi là từ đỉnh s tới đỉnh  |
t. 8 cạnh gồm : 1 2                      |
                2 3                      |
                2 4                      |
                3 6                      |
                3 7                      |
                5 8                      |
                5 10
                6 7
                7 5
                8 9                                                                 */


int n, m, t, s;//n là số đỉnh ,m là số cạnh của đồ thị
vector<int> adj[20];//Tạo vector adj để lưu danh sách kề của đồ thị
bool visited[20];//Mảng chứa các đỉnh true(là đỉnh đó đã đc thăm) còn false(là đỉnh đó chưa đc thăm) 
int parent[20];//Mảng này chứa đỉnh cha của đỉnh vừa đc thăm 

//Hàm nhập input của đề
void inp() {
    cout << "Nhap vao n dinh va m canh cua do thi: \n";
    cin >> n >> m;

    cout << "Nhap vao dinh x va dinh y tao thanh canh cua do thi: \n";
    for (short i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;

        adj[x].push_back(y);
    }
}

//Áp dụng DFS(thuật toán tìm kiếm theo chiều sau của đồ thị) vào tìm đường và truy vết đường đi  
void DFS(int u) {
    visited[u] = true;
    for (int v : adj[u]) {
        if (!visited[v])
        {
            parent[v] = u;/*Ghi nhận lại cha của v là u, tức là  đỉnh u đã đc thăm rồi từ đỉnh u mở rộng ra để thăm các đỉnh kề với
            đỉnh u thì đỉnh mà kề với đỉnh u là đỉnh v thì đỉnh u là cha của đỉnh v */
            DFS(v);
        }
    }
}

//Áp dụng BFS(thuật toán tìm kiếm theo chiều rộng của đồ thị) vào tìm đường và truy vết đường đi 
void BFS(int u) {
    queue<int> q;
    q.push(u);
    visited[u] = true;

    while (!q.empty())   
    {
        int v = q.front();
        q.pop();
        for (int x : adj[v]) {
            if (!visited[x]) {
                q.push(x);
                visited[x] = true;
                parent[x] = v;
            }
        }
    }
}

/*Hàm để tìm đường giữa 2 đỉnh bất kì hay gọi cho dễ hiểu là tìm đường giữa đỉnh s(là đỉnh đầu của đường đi) đến đỉnh t(là đỉnh cuối của
đường đi)*/
void Path(int s, int t) {
    cout << "Nhap vao s va t de kiem tra xem tu s den t co duong di hay khong: \n";
    cin >> s >> t;
    memset(visited, false, sizeof(visited));//Mặc định ban đầu cho tất cả các đỉnh là false(tức là chưa đc thăm)
    memset(parent, 0, sizeof(parent));/*Mặc định parent(là cha của các đỉnh) ban đầu là bằng không tức là ban đầu tất cả các đỉnh không
    có cha*/
    DFS(s);/*//DFS(s); vì là chỉ tìm đường đi thôi nên áp dụng 1 trong 2 thuật toán DFS hoặc DFS cái này cũng đc, còn đối với truy vết
    đường đi thì phải dùng DFS hoặc BFS tùy thuộc vào yêu cầu đề bài để áp dụng DFS hoặc BFS cho phù hợp với yêu cầu, đối với truy vết
    đường đi ngắn nhất của đồ thị không có trọng số thì thuật toán BFS(tìm kiếm theo chiều rộng của đồ thị) sẽ truy vết ra đc đường đi
    ngắn nhất giữa 2 đỉnh bất kì.Giải thích Dòng này: Gọi s là đỉnh đầu của đường đi và t là đỉnh kết thúc đường đi nếu đỉnh s tới đỉnh
    t mà có đường đi thì ta chỉ cần truyền đỉnh s(là đỉnh đầu của đường đi) và hàm DFS thì trong hàm DFS nó sẽ tự động thăm tất cả các
    đỉnh trên đường đi từ s đến t còn nếu từ đỉnh s tới đỉnh t mà không có đường đi thì đỉnh t sẽ không đc thăm. Trong trường hợp có 1 
    bài toán cho ta 1 cái đồ thị vô hướng và q truy vấn mõi truy vấn nó cho 2 đỉnh s và t và kiểm tra đường giữa 2 đỉnh s và t có đường 
    đi hay không nếu ta làm theo kiểu như thế này mõi truy vấn ta lại gọi DFS hoặc là BFS của s sau đó kiểm tra t có đc thăm hay không
    thì chương trình của ta sẽ không tối ưu và mất thời gian vì vậy nếu đề bài yêu cầu cho ta 1 cái đồ thị vô hướng và q truy vấn mõi 
    truy vấn nó cho 2 đỉnh s và t và kiểm tra đường giữa 2 đỉnh s và t có đường đi hay không thì ta sử dụng 1 cái map hoặc 1 cái mảng 
    để duy trì xem là các đỉnh của đồ thị nó thuộc thành phần liên thông mấy thì ta chỉ cần check xem s và t nó mà nằm cùng 1 thành 
    phần liên thông trong đồ thị thì nó có đường đi ngược lại s và t khác thành phần liên thông thì giữa 2 đỉnh s và t không có đường
    đi chứ đừng mõi lần truy vấn xem giữa 2 đỉnh s và t có đường đi hay không thì ta lại gọi hàm DFS hoặc BFS ra truy vấn lại đường đi
    nó rất lâu.
    ví dụ: (từ đỉnh 1 đến đỉnh 7 hình trong vở đồ thị 2 bài 11) khi gọi DFS hoặc BFS ta truyền vào đỉnh 1 thì nó sẽ thăm và đưa tất cả các 
    đỉnh từ kề với đỉnh 1 đến 7 vào 1 cái map hoặc cái mảng nào đó và đánh dấu tất cả các đỉnh vừa đc thăm là thành phần liên thông thứ
    1 và cứ thế truyền đỉnh s khác vào Hàm DFS hoặc BFS để thăm tất cả các đỉnh trên đường đi từ đỉnh s tới đỉnh t và lưu tất cả các 
    đỉnh vừa đc thăm vào 1 cái mảng hoặc map là thành phần liên thông thứ 2, 3 , n....... khi đó ta truy vấn giữa 2 đỉnh s và t có phải
    là đường đi hay không ta không cần phải gọi hàm DFS hoặc BFS để thăm tất cả các đỉnh trên đường đi giữa 2 đỉnh s và t nữa mà ta đã
    thăm và đánh dấu nó là thành phần liên thông thứ mấy trong mảng hoặc map của đồ thị rồi thì mõi lần truy vấn xem giữa 2 đỉnh s và t 
    có đường đi hay không ta chỉ cần xét nếu nó nằm chung trong 1 thành phần liên thông của đồ thị thì s và t có đường ngược lại s và t
    khác thành phần đồ thị liên thông thì giữa s và t không có đường đi*/
    if (!visited[t]) {/*Kiểm tra nếu t mà là false thì từ đỉnh s tới đỉnh t k có đường đi vì đỉnh t là đỉnh cuối kết thúc đường đi, mà
                    ta truyền vào hàm DFS là đỉnh s(là đỉnh đầu của đường đi) nếu từ s đến t mà có đường đi thì khi đỉnh s đc truyền vào
                    hàm DFS từ s sẽ mở rộng và thăm đến đỉnh t luôn, vì cơ chế thuật toán DFS(tìm kiếm theo chiều sau của đồ thị) ta đã
                    học rất kĩ là từ 1 đỉnh đc thăm nó sẽ lan rộng ra thăm các đỉnh bằng cách xét đỉnh kề với đỉnh đã đc thăm để thăm
                    tất cả các đỉnh mà kề với đỉnh đã đc thăm. từ đỉnh s đến đỉnh t mà có đường đi thì tất cả các đỉnh trên đường đi từ
                    đỉnh đầu đường đi(là đỉnh s) tới đỉnh kết thúc đường đi(là đỉnh t) đều là true đồng nghĩa với đỉnh cuối đường đi là
                    đỉnh t cũng phải true thì từ đỉnh s đến đỉnh t mới có đường đi còn đỉnh t mà chưa đc thăm tức là từ đỉnh s tới đỉnh
                    t không có đường đi.*/
        cout << "Tu dinh " << t << " toi dinh " << s << " khong co duong     di !";
    }
    else {/*Ngược lại nếu t mà là true thì từ đỉnh s tới đỉnh t có đường đi vì đỉnh t là đỉnh cuối kết thúc đường đi, mà ta
        truyền vào hàm DFS là đỉnh s(là đỉnh đầu của đường đi) nếu từ s đến t mà có đường đi thì khi đỉnh s đc truyền vào
        hàm DFS từ s sẽ mở rộng và thăm đến đỉnh t luôn, vì cơ chế thuật toán DFS(tìm kiếm theo chiều sau của đồ thị) ta đã
        học rất kĩ là từ 1 đỉnh đc thăm nó sẽ lan rộng ra thăm các đỉnh bằng cách xét đỉnh kề với đỉnh đã đc thăm để thăm
        tất cả các đỉnh mà kề với đỉnh đã đc thăm. từ đỉnh s đến đỉnh t mà có đường đi thì tất cả các đỉnh trên đường đi từ
        đỉnh đầu đường đi(là đỉnh s) tới đỉnh kết thúc đường đi(là đỉnh t) đều là true đồng nghĩa với đỉnh cuối đường đi là
        đỉnh t cũng phải true thì từ đỉnh s đến đỉnh t mới có đường đi còn chưa đc thăm tức là từ đỉnh s tới đỉnh t không có
        đường đi.*/

        //Truy vết đường đi
        vector<int> path;
        while (t != s) {/*Khi truy vết đường đi thì ta phải truy vết từ đỉnh cuối của đường đi(là đỉnh t) cho đến khi gặp đc đỉnh đầu thì
            dừng lại. bằng cách nếu từ đỉnh cuối đường đi ta xét có khác với đỉnh đầu đường đi hay không nếu khác ta xuất ra đỉnh cuối
            rồi ta lại lấy đỉnh parent(cha) của đỉnh cuối xét xem có khác đỉnh đầu đường đi hay k nếu khác thì ta lại xuất đỉnh cha của
            đỉnh vừa xét ra và lấy đỉnh parent(cha) của đỉnh vừa xét xem có khác với đỉnh đầu đường đi hay không nếu khác thì lại xuất
            đỉnh parent(cha) của đỉnh vừa xét rồi lại lấy cha của của đỉnh vừa xét làm tương tự cứ như thế cho đến khi đỉnh parent(cha)
            của đỉnh vừa xét mà bằng đỉnh s thi ta dừng lại */
            path.push_back(t);/*path này là vector chứa các đỉnh khi truy vết đường đi, truy vết đường đi sẽ truy từ đỉnh cuối về cho
            đến khi gặp đỉnh đầu thì dừng lại khác với hàm mà chứa nó là hàm Path hàm Path là hàm xử lí kiểm tra xem giữa 2 đỉnh bất
            kì xem có đường đi hay không và đường đi của 2 đỉnh đó sẽ gồm những đỉnh nào(tức là truy vết đường đi)*/

            //Truy ngược lại từ đỉnh t(là đỉnh cuối đườnh đi) cho đến khi gặp đỉnh s(là đỉnh đầu) thì hoàn thành truy vết
            t = parent[t];/*Truy vết đường đi là ta truy từ đỉnh t(là đỉnh cuối của đường đi) cho đến khi gặp đỉnh s thì dừng(vòng
            lặp while sẽ duyệt từ đỉnh t cho đến khi đỉnh t bằng đỉnh s thì dừng) bằng cách đầu tiên vô vòng lặp thì đỉnh t đang là
            đỉnh ở cuối đường đi sau đó ta push_back đỉnh t(là đỉnh cuối của đường đi) vào vector path sau đó vì thảo đk là đỉnh t
            != s nên thõa đk nên t lúc này cho bằng parent của t tức là t lúc này chính là đỉnh đã mở rộng ra để duyệt t hay còn gọi
            là đỉnh cha của đỉnh t thì t lúc này là cha của đỉnh t cứ như vậy đỉnh cha của đỉnh t này lại quay lên vòng lặp while
            xem nó có bằng đỉnh đầu chưa nếu chưa thì cho t vào vector path và cho t hiện tại bằng đỉnh cha của nó cứ như thế cho
            đến khi gặp t = s thì dừng lại.*/
        }
        path.push_back(s);/*Vì là khi lần ngược lại đường đi cho đến khi gặp đỉnh s thì dừng nên đỉnh s chưa đc thêm vào danh sách
        path( là danh sách chứa các đỉnh trên đường đi từ s đến t) mà đỉnh s cũng là đỉnh đầu đường đi nên sau khi đã truy vết từ
        đỉnh t(là đỉnh cuối của đường đi) cho đến đỉnh kề với đỉnh đầu đường đi thì ta push đỉnh đầu của đường đi vào là xong.
        ví dụ: từ đỉnh 1 đến đỉnh 7 là có đường đi thì ta truy vết đường đi từng đỉnh 1 đến đỉnh 7 bằng cách truy ngược lại từ đỉnh
        7 về đến đỉnh con của đỉnh s thì sau khi truy thì danh sách các đỉnh trên đường đi lúc này 7 6 3 2 còn thiếu đỉnh s( là đỉnh
        1) vì chương trình ta truy về đến khi gặp đỉnh 2 thì dừng nên đỉnh 1 chưa đc thêm vào vector path thì sau khi truy và danh
        sách thực hiện xong bước truy là 7 6 3 2 và ta push đỉnh s vào nữa là 7 6 3 2 1 là hoàn thành truy vết đường đi */

        reverse(path.begin(), path.end());/*Lần(đảo) ngược lại. Có nghĩa là khi ta đã biết đc đường đi của 2 đỉnh là đi qua gồm những đỉnh nào rồi thì do ta truy vết
            đường đi bằng cách truy từ đỉnh cuối lên ngược lại đỉnh đầu nên vector path lúc này chứa các đỉnh ngược lại của đường
            đi ví dụ từ đỉnh 1 tới đỉnh 7 (như trong vở ta đã giải thích rất rõ cơ chế kiểm tra xem 2 đỉnh 1 và 7 có đường đi hay
            không và cơ chế truy vết đường đi của đỉnh 1 tới đỉnh 7 nếu quên hãy mở vở đồ thị 2 bài 11 phần 2 la mã để xem lại) thì
            khi truy vết đường đi bắt đầu từ đỉnh 7 thì ta sẽ lưu các đỉnh trên đường đi từ đỉnh 7 cho đến khi gặp đỉnh đầu của
            đầu của đường đi thì vòng lặp while sẽ dừng lại thì khi đó đường đi lưu trong vector path đc truy từ đỉnh 7 ngược lại
            đỉnh 1 lúc này là 7 6 3 2 1 đây là đường đi từ đỉnh 1 tới đỉnh 7 nhưng nó bị ngược nên ta cần phải đảo nó ngược lại là
            1 2 3 6 7 mới đúng đường đi từ đỉnh 1 tới đỉnh 7.*/

            //Xuất đường đi từ đỉnh s đến đỉnh t sau khi truy vết và lần(đảo) ngược lại
        cout << "Co duong di !\n";
        cout << "Duong di sau khi truy vet la : ";
        for (int x : path) {
            cout << x << " ";
        }
    }
}

int main()
{
    inp();
    Path(s, t);

}

