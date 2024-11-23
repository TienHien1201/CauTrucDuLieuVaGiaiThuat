
//########################################### ĐỒ THỊ VÔ HƯỚNG ##############################################
#if 0
#include <iostream>
#include<vector>
using namespace std;

/*================== ÁP DỤNG DFS VÀO KIỂM TRA CHU TRÌNH TRÊN ĐỒ THỊ VÔ HƯỚNG LIÊN THÔNG ============================

input: Nhập vào n số đỉnh của đồ     | output: Xuất ra kết quả là đồ thị có chu trình hay không(Đối input ta nhập thì kết quả của 
thị có hướng là n = 7 tức từ 1 đến   | việc kiểm tra chu trình của đồ thị là: Đồ thị có chu trình 
7, nhập vào m số cạnh của đồ thị có  | 
hướng là m = 6 gồm các cạnh:         |
									 |
				   1 2               |            
				   2 3               |
				   2 4               |
				   3 6               |
				   6 7               |
			       7 3               |
				                     |
										  */
int n, m;
vector<int> adj[20];
bool visited[20];

void inp() {
	cout << "Nhap vao n so dinh va m so canh cua do thi co huong: \n";
	cin >> n >> m;

	cout << "Nhap va hai dinh x va y noi thanh canh cua do thi vo huong: \n";
		for (short i = 0; i < m; i++)
		{
			int x, y;
			cin >> x >> y;

			adj[x].push_back(y);
			adj[y].push_back(x);
		}
		memset(visited, false, sizeof(visited));
}

bool DFS(int u, int par) {
	visited[u] = true;
	for(int v : adj[u]) {//Duyệt danh sách kề của đỉnh u( đỉnh u là đỉnh vừa đc thăm )
		if (!visited[v])//Nếu v(v là đỉnh kề với đỉnh vừa đc thăm(đỉnh vừa đc thăm là đỉnh u) tức v là con của đỉnh u) chưa đc thăm 
		{
			if (DFS(v, u))//Ta truyền v vào hàm đệ quy DFS để thăm đỉnh 
				return true;
		}
		else if(v != par){/*Nếu đỉnh v đã đc thăm tức là điều kiện if(!visited[v]) sai thì chương trình sẽ chạy xuống dòng else if này
			xét v có phải là cha trực tiếp của đỉnh u(đỉnh u là par) hay không nếu v không phải là cha trực tiếp của đỉnh u( tức là par)
			thì ta return về true tức cạnh v nối với u là cạnh ngược nghĩa là đồ thị có chu trình.
		    -> cạnh ngược là cạnh nếu có đường đi từ s đến t khi t quay lại nối trực tiếp tới s thì t nối trực tiếp tới s gọi là cạnh 
			ngược. 
	        ví dụ: ta có đồ thị vô hướng có 3 đỉnh là 1 2 3 và 3 cạnh 1 nối với 2 , 2 nối với 3 và 3 nối với 1 thì khi ta kiểm tra 
			từ 1 tới 3 có đường đi là 1 nối với 2 rồi 2 nối với 3 thì khi này 3 nối ngược lại với 1 thì cạnh 3 1 là cạnh ngược của 
			đồ thị thì ta return về hàm có cạnh ngược là true luôn vì đỉnh 1 là đỉnh mở rộng rộng ra thăm đỉnh 2 tức 1 là cha của 2
			mà đỉnh 2 lại mở rộng ra thăm đỉnh 3 tức đỉnh 2 là cha của đỉnh 3 mà đỉnh 3 lại kề với đỉnh 1 thì tức đỉnh 1 không là 
			cha trực tiếp của đỉnh 3 nên cạnh 3 nối với 1 là cạnh ngược tạo thành chu trình 1 2 3 1 tức chu trình là đường đi có đỉnh
			đầu trùng với đỉnh cuối. */
		 
			return true;
		}
	}

	return false;
}


int main()
{
	inp();
	if (DFS(1, 0))
		cout << "Do thi vo huong co chu trinh !";
	else
		cout << "Do thi vo huong khong co chu trinh !";
}
#endif // 0

#if 0
/*=== ÁP DỤNG DFS VÀO KIỂM TRA CHU TRÌNH TRÊN ĐỒ THỊ VÔ HƯỚNG KHÔNG LIÊN THÔNG VÀ DÙNG MẢNG PARENT ĐỂ TRUY VẾT ĐƯỜNG ĐI CỦA CHU TRÌNH ===

input: Nhập vào n số đỉnh của đồ     | output: Xuất ra kết quả là đồ thị có chu trình hay không và truy vết đường đi của chu trình
thị có hướng là n = 8 tức từ 1 đến   | (Đối input ta nhập thì kết quả của việc kiểm tra chu trình của đồ thị là: Đồ thị có chu trình 
8, nhập vào m số cạnh của đồ thị có  | và truy vết đường đi của chu trình là: 4 5 6 4)
hướng là m = 6 gồm các cạnh:         |
									 |
				   1 2               |
				   2 3               |
				   4 5               |
				   4 6               |
				   5 6               |
				   5 7               |
									 |
như thấy các cạnh của đồ thị vô hướng|
không liên thông này có 3 thành phần | 
liên thông: thành phần liên thông thứ|
1 của đồ thị là 1 nối với 2 2 nối với|
3, thành phần liên thông thứ 2 của đồ|
 thị là 4 nối với 5 4 nối với 6 5 nối|
với 6 và 5 nối với 7, thành phần liên|
 thông thứ 3 của đồ thị là đỉnh 8    |
                                                                                                                                    */
/*Đối với phần kiểm tra chu trình của đồ thị vô hướng không liên thông khác với kiểm tra chu trình của đồ thị vô hướng liên thông 
thì kiểm tra chu trình của đồ thị vô hướng liên thông là chỉ cần truyền vào hàm DFS đỉnh ở đầu đồ thị thôi thì DFS nó sẽ thăm tất cả
các đỉnh của đồ thị để kết luận là có chu trình hay không vì liên thông là giữa 2 đỉnh bất kì trong đồ thị luôn có đường đi còn đối
với phần kiểm tra chu trình của đồ thị vô hướng không liên thông thì phải có vòng lặp for duyệt hết tất cả các đỉnh trong đồ thị tức
là duyệt qua từng thành phần liên thông của đồ thị rồi mới kết luận là có chu trình hay không. Và ở phần này không dùng tham số par 
trong hàm DFS tức DFS(int u, par) mà chỉ truyền vào DFS đỉnh u tức DFS(int u) thôi còn cha của đỉnh u sẽ đc lưu vào mảng parent đã 
tạo của phần chương trình này. Dùng biến par truyền vào hàm DFS để đánh dấu cha của đỉnh u mõi lần thực thị hàm DFS cũng đc mà dùng
mảng parent lưu đỉnh cha của đỉnh u cũng đc nhưng ở file bài 7.TimDuongDiTrenDoThiKhongCoTrongSo truy vết đường đi thì phải dùng mảng
parent để lưu lại cha của đỉnh vừa đc thăm để có thể truy vết ngược lại mảng parent để tìm đường đi của chu trình.*/
#include <iostream>
#include<vector>
using namespace std;

int n, m, start, enD;/*n là số đỉnh , m là số cạnh của đồ thị, start là biến lưu điểm đầu của chu trình, biến end là biến lưu điểm 
cuối chu trình */
vector<int> adj[20];
int parent[20];//Mảng parent dùng để lưu đỉnh cha của đỉnh đc đỉnh cha mở rộng ra thăm 
bool visited[20];

void inp() {
	cout << "Nhap vao n so dinh va m so canh cua do thi co huong: \n";
	cin >> n >> m;

	cout << "Nhap va hai dinh x va y noi thanh canh cua do thi vo huong: \n";
	for (short i = 0; i < m; i++)
	{
		int x, y;
		cin >> x >> y;

		adj[x].push_back(y);
		adj[y].push_back(x);
	}
	memset(visited, false, sizeof(visited));
}

//Áp dụng thuật toán DFS(Tìm kiếm theo chiều sâu của đồ thị) vào bài toán kiểm tra chu trình của đồ thị
bool DFS(int u) {
	visited[u] = true;
	for (int v : adj[u]) {//Duyệt danh sách kề của đỉnh u( đỉnh u là đỉnh vừa đc thăm )
		if (!visited[v])//Nếu v(v là đỉnh kề với đỉnh vừa đc thăm(đỉnh vừa đc thăm là đỉnh u) tức v là con của đỉnh u) chưa đc thăm 
		{
			parent[v] = u;
			if (DFS(v))//Ta truyền v vào hàm đệ quy DFS để thăm đỉnh 
				return true;
		}
		else if (v != parent[u]) {/*Nếu đỉnh v đã đc thăm tức là điều kiện if(!visited[v]) sai thì chương trình sẽ chạy xuống dòng 
			else if này xét v(là đỉnh kề với u nhưng đã đc thăm) có phải là cha trực tiếp của đỉnh u hay không nếu v không phải là
			cha trực tiếp của đỉnh u thì ta return về true tức cạnh v nối với u là cạnh ngược nghĩa là đồ thị có chu trình.
			-> cạnh ngược là cạnh nếu có đường đi từ s đến t khi t quay lại nối trực tiếp tới s thì t nối trực tiếp tới s gọi là cạnh
			ngược.
			ví dụ: ta có đồ thị vô hướng có 3 đỉnh là 1 2 3 và 3 cạnh 1 nối với 2 , 2 nối với 3 và 3 nối với 1 thì khi ta kiểm tra 
			từ 1 tới 3 có đường đi là 1 nối với 2 rồi 2 nối với 3 thì khi này 3 nối ngược lại với 1 thì cạnh 3 1 là cạnh ngược của 
			đồ thị thì ta return về hàm có cạnh ngược là true luôn vì đỉnh 1 là đỉnh mở rộng rộng ra thăm đỉnh 2 tức 1 là cha của 2
			mà đỉnh 2 lại mở rộng ra thăm đỉnh 3 tức đỉnh 2 là cha của đỉnh 3 mà đỉnh 3 lại kề với đỉnh 1 thì tức đỉnh 1 không là 
			cha trực tiếp của đỉnh 3 nên cạnh 3 nối với 1 là cạnh ngược tạo thành chu trình 1 2 3 1 tức chu trình là đường đi có đỉnh
			đầu trùng với đỉnh cuối.*/
			start = v;/*Biến start dùng để lưu đỉnh v(đỉnh v là đỉnh không phải cha trực tiếp của đỉnh u nhưng lại kề với u như ví dụ
			ở dòng 1 5 3 thì v là đỉnh 1 lý do nói v không phải là cha trực tiếp của 3 vì đỉnh 1 mở rộng ra thăm đỉnh 2 rồi đỉnh 2 mở
			rộng ra thăm đỉnh 3 thì đỉnh 2 là cha trực tiếp của đỉnh 3 vì đỉnh 2 nối vs đỉnh 3 mà đỉnh 3 lại kề với đỉnh cha của đỉnh
			đã mở rộng ra đỉnh 3 là đỉnh 1 suy ra đỉnh 1 không phải là cha trực tiếp của đỉnh 3) ở đầu chu trình */
			enD = u;/* Biến start dùng để lưu biến u(biến u là biến lưu đỉnh nằm ở cuối chu trình như ví dụ của dòng 153 thì u là đỉnh
			3 còn số 1 nằm sau đỉnh 3 là đỉnh nối với 3 tạo thành cạnh ngược 3 1 )*/
			return true;
		}
	}

	return false;
}

int main(){
	inp();

	//Duyệt hết tất cả các đỉnh trong đồ thị vô hướng không liên thông 
	for (short i = 1; i <= n; i++){
		if (!visited[i])
		{
			//if (BFS(i)){
			if (DFS(i)) {
				cout << "Do thi vo huong co chu trinh !";
				vector <int> cycle;//Vector cycle dùng để chứa các đỉnh trên đường đi khi truy vết
				cycle.push_back(start);//Thêm đỉnh ở đầu chu trình vào danh sách chứa các đỉnh khi truy vết đường đi
				while (enD != start){/*Truy vết đường đi của chu trình bằng cách truy từ đỉnh ở cuối chu trình đến đỉnh ở đầu chu trình
				thì dừng lại */
				
					cycle.push_back(enD);//Thêm biến enD là biến lưu đỉnh ở cuối đỉnh cuối đường đi của chu trình vào danh sách cycle
					enD = parent[enD];/*sau khi thêm biến enD là biến chứa đỉnh nằm ở cuối chu trình vào danh sách cycle thì đỉnh vừa
					đc thêm đc cập nhật lại lại là cha của đỉnh vừa đc thêm*/

				/*Giải thích cơ chế của vòng lặp while để truy vết đường đi của chu trình:
				Khi truy từ đỉnh cuối chu trình bằng cách dùng đk của vòng lặp while xét đỉnh cuối chu trình này có khác đỉnh ở đầu 
				chu trình hay không nếu khác thì đỉnh ở cuối chu trình này đc thêm vào danh sách cycle là danh sách chứa các đỉnh của
				chu trình, sau đó cập nhật lại đỉnh vừa đc thêm vào danh sách cyle là cha của đỉnh vừa đc thêm tức biến enD lúc này
				không còn là biến chứa đỉnh nằm ở cuối chu trình nữa mà biến enD bây giờ là đỉnh cha của đỉnh nằm ở cuối chu trình.
				cứ như thế cho đến khi gặp đỉnh nằm ở đầu chu trình thì vòng lặp while truy vết đường đi của chu trình dừng lại và 
				hoàn thành việc truy vết đường đi của chu trình. Vì là truy vết bắt đầu từ đỉnh cuối chu trình cho đến khi gặp đỉnh 
				ở đầu chu trình thì dừng lại nên đỉnh ở đầu chu trình k đc thêm và danh sách cycle(là danh sách chứa các đỉnh trên 
				đường đi của chu trình) nên trước khi dùng vòng lặp while để thực thi việc truy vết đường đi của chu trình thì ta 
				phải thêm đỉnh nằm ở đầu chu trình vào danh sách chứa các đỉnh của chu trình(là danh sách cycle) và ta biết chu trình
				là đường đi có đỉnh đầu và đỉnh cuối giống nhau nên khi kết thúc vòng lặp while truy vết chu trình của đồ thị thì cũng
				phải thêm đỉnh ở đầu chu trình vào danh sách cycle thì danh sách cycle lúc này do ta truy từ đỉnh cuối chu trình lên
				đỉnh ở đầu chu trình nên danh sách chứa đường đi của chu trình lúc này bị ngược nên ta phải thực hiện đảo ngược(reverse)
				thứ tự các đỉnh trong danh sách cycle lại thì hoàn thành việc truy vết đường đi của đồ thị và ta chỉ cần xuất các đỉnh
				trong danh sách cycle ra thì các đỉnh đc xuất từ danh sách cycle là chu trình của đồ thị
				-> Ví dụ: 
				
				*/
				}
				cycle.push_back(start);/*Tiếp tục thêm đỉnh ở đầu chu trình vào danh sách chứa các đỉnh khi truy vết đường đi 1 lần nữa
				vì như ta biết chu trình là đường đi có đỉnh đầu và đỉnh cuối đường đi giống nhau. 
				-> Ví dụ: đồ thị ta có đường đi 1 nối với 2 , 2 nối với 3 và 3 nối với 1 tạo thành chu trình 1 2 3 1 thì chu trình là 
				đường đi có đỉnh đầu và đỉnh cuối giống nhau nên khi điều kiên*/
				reverse(cycle.begin(), cycle.end());
				
				cout << "\nDuong di cua chu trinh: ";
				for (int x : cycle) {
					cout << x << " ";

				}
				return 0; /*Return 0 có tác dụng khi chạy vào đc khối lệnh mà có chứa return 0 thì khi thực hiện xong khối lệnh và dòng
				return 0 này đc thực thi để kết thúc hàm để hàm không tiếp tục thực hiện nữa*/
			}
		}
	}
		cout << "Do thi vo huong khong co chu trinh !";
}
#endif // 0	
			
#if 0
/*ÁP DỤNG BFS VÀO KIỂM TRA CHU TRÌNH TRÊN ĐỒ THỊ VÔ HƯỚNG KHÔNG LIÊN THÔNG VÀ DÙNG MẢNG PARENT NHƯNG KHÔNG TRUY VẾT ĐƯỜNG ĐI CỦA CHU
TRÌNH 

input: Nhập vào n số đỉnh của đồ     | output: Xuất ra kết quả là đồ thị có chu trình hay không và truy vết đường đi của chu trình
thị có hướng là n = 8 tức từ 1 đến   | (Đối input ta nhập thì kết quả của việc kiểm tra chu trình của đồ thị là: Đồ thị có chu trình
8, nhập vào m số cạnh của đồ thị có  | và truy vết đường đi của chu trình là: 4 5 6 4)
hướng là m = 6 gồm các cạnh:         |
									 |
				   1 2               |
				   2 3               |
				   4 5               |
				   4 6               |
				   5 6               |
				   5 7               |
									 |
như thấy các cạnh của đồ thị vô hướng|
không liên thông này có 3 thành phần |
liên thông: thành phần liên thông thứ|
1 của đồ thị là 1 nối với 2 2 nối với|
3, thành phần liên thông thứ 2 của đồ|
 thị là 4 nối với 5 4 nối với 6 5 nối|
với 6 và 5 nối với 7, thành phần liên|
 thông thứ 3 của đồ thị là đỉnh 8    |
																														*/
/*Đối với phần áp dụng BFS vào kiểm tra chu trình của đồ thị vô hướng không liên thông thì cũng có thể dùng biến par để lưu lại đỉnh
cha của đỉnh vừa đc đỉnh cha mở rộng ra thăm tức hàm BFS phải truyền vào 2 tham số là BFS(int u, int par) như chương trình ÁP DỤNG 
DFS VÀO KIỂM TRA CHU TRÌNH TRÊN ĐỒ THỊ VÔ HƯỚNG LIÊN THÔNG ở dòng 6 hoặc ta có thể dùng mảng parent để lưu lại đỉnh cha của đỉnh đc 
đỉnh cha mở rộng ra thăm và chỉ truyền vào hàm BFS 1 tham số là BFS(int u) như chương trình này nhưng đối với phần áp dụng BFS vào 
kiểm tra chu trình của đồ thị vô hướng không liên thông thì cũng dùng mảng parent để lưu đỉnh cha của đỉnh đc đỉnh cha mở rộng ra 
thăm nhưng không thể truy vết ngược lại mảng parent để biết đc chu trình của đồ thị đc vì BFS là thuật toán tìm theo chiều rộng của
đồ thị nên từ 1 đỉnh vừa đc thăm nó duyệt danh sách kề của đỉnh vừa đc thăm để thăm hết tất cả các đỉnh kề với đỉnh vừa đc thăm mà 
chưa đc thăm trong 1 lần duyệt của đỉnh vừa đc thăm nên không thể truy vết lại đc đường đi khi áp dụng BFS vào kiểm tra chu trình 
của đồ thị vô hướng không liên thông đc, chỉ có dùng DFS thì có thể truy vết đc chu trình của đồ thị.*/
#include <iostream>
#include<queue>
#include<vector>
using namespace std;

int n, m;/*n là số đỉnh , m là số cạnh của đồ thị
cuối chu trình */
vector<int> adj[20];
int parent[20];//Mảng parent dùng để lưu đỉnh cha của đỉnh đc đỉnh cha mở rộng ra thăm 
bool visited[20];

void inp() {
	cout << "Nhap vao n so dinh va m so canh cua do thi co huong: \n";
	cin >> n >> m;

	cout << "Nhap va hai dinh x va y noi thanh canh cua do thi vo huong: \n";
	for (short i = 0; i < m; i++)
	{
		int x, y;
		cin >> x >> y;

		adj[x].push_back(y);
		adj[y].push_back(x);
	}
	memset(visited, false, sizeof(visited));
}

//Áp dụng thuật toán BFS(Tìm kiếm theo chiều rộng của đồ thị) vào bài toán kiểm tra chu trình của đồ thị
bool BFS(int u) {
	queue<int> q;
	q.push(u);
	visited[u] = true;
	while (!q.empty())
	{
		int v = q.front();
		q.pop();
		for (int x : adj[v]) {//Duyệt danh sách kề của đỉnh u( đỉnh u là đỉnh vừa đc thăm )
			if (!visited[x])//Nếu v(v là đỉnh kề với đỉnh vừa đc thăm(đỉnh vừa đc thăm là đỉnh u) tức v là con của đỉnh u) chưa đc thăm 
			{
				q.push(x);
				visited[x] = true;
				parent[x] = v;

			}
			else if (x != parent[v]) {/*Nếu đỉnh v đã đc thăm tức là điều kiện if(!visited[v]) sai thì chương trình sẽ chạy xuống dòng
				else if này xét v(là đỉnh kề với u nhưng đã đc thăm) có phải là cha trực tiếp của đỉnh u hay không nếu v không phải là
				cha trực tiếp của đỉnh u thì ta return về true tức cạnh v nối với u là cạnh ngược nghĩa là đồ thị có chu trình.
				-> cạnh ngược là cạnh nếu có đường đi từ s đến t khi t quay lại nối trực tiếp tới s thì t nối trực tiếp tới s gọi là cạnh
				ngược.
				ví dụ: ta có đồ thị vô hướng có 3 đỉnh là 1 2 3 và 3 cạnh 1 nối với 2 , 2 nối với 3 và 3 nối với 1 thì khi ta kiểm tra
				từ 1 tới 3 có đường đi là 1 nối với 2 rồi 2 nối với 3 thì khi này 3 nối ngược lại với 1 thì cạnh 3 1 là cạnh ngược của
				đồ thị thì ta return về hàm có cạnh ngược là true luôn vì đỉnh 1 là đỉnh mở rộng rộng ra thăm đỉnh 2 tức 1 là cha của 2
				mà đỉnh 2 lại mở rộng ra thăm đỉnh 3 tức đỉnh 2 là cha của đỉnh 3 mà đỉnh 3 lại kề với đỉnh 1 thì tức đỉnh 1 không là
				cha trực tiếp của đỉnh 3 nên cạnh 3 nối với 1 là cạnh ngược tạo thành chu trình 1 2 3 1 tức chu trình là đường đi có đỉnh
				đầu trùng với đỉnh cuối.*/
				return 0; /*return 0 có tác dụng khi chạy vào đc khối lệnh mà có chứa return 0 thì khi thực hiện xong khối lệnh và dòng
				return 0 này đc thực thi để kết thúc hàm để hàm không tiếp tục thực hiện nữa*/
			}
		}
	}

	return false;
}


int main() {
	inp();

	//Duyệt hết tất cả các đỉnh trong đồ thị vô hướng không liên thông 
	for (short i = 1; i <= n; i++) {
		if (!visited[i])
		{
			if (BFS(i)){
				cout << "Do thi vo huong co chu trinh !";
				return 0;
			}
		}
	}
	cout << "Do thi vo huong khong co chu trinh !";
}
#endif // 0	

//########################################### ĐỒ THỊ CÓ HƯỚNG ##############################################
#if 0
#include <iostream>
#include<vector>
using namespace std;

/*================== ÁP DỤNG DFS VÀO KIỂM TRA CHU TRÌNH TRÊN ĐỒ THỊ CÓ HƯỚNG KHÔNG LIÊN THÔNG ============================
* Đối với đồ thị liên thông thì không cần phải có vòng lặp for để tryền hết tất cả các đỉnh vào hàm DFS mà chỉ cần truyền đỉnh ở đầu
đồ thị vào hàm DFS hoặc BFS thì nó sẽ duyệt và thăm hết các đỉnh trong đồ thị
* Đối với đồ thị không liên thông thì khi gọi hàm DFS hoặc BFS thì ta phải tạo 1 vòng lặp for cho chạy từ đỉnh ở đầu đồ thị cho tới 
đỉnh ở cuối đồ thị tức phải xét hết các thành phần liên thông của đồ thị xem có chu trình hay không.

input: Nhập vào n số đỉnh của đồ     | output: Xuất ra kết quả là đồ thị có chu trình hay không(Đối input ta nhập thì kết quả của
thị có hướng là n = 7 tức từ 1 đến   | việc kiểm tra chu trình của đồ thị là: Đồ thị có chu trình
7, nhập vào m số cạnh của đồ thị có  |
hướng là m = 6 gồm các cạnh:         |
									 |
				   1 2               |
				   1 5               |
				   2 3               |
				   4 2               |
				   3 6               |
				   6 7               |
				   7 3               |
									 |
										  */
int n, m;//n là số đỉnh của đồ thị , m là số cạnh của đồ thị
vector<int> adj[20];//Chứa danh sách kề của các đỉnh
int color[20];/*Dùng mảng màu để kiểm tra xem các đỉnh trong đồ thị có đc thăm hay chưa với quy ước:
+ 0(chưa đc thăm) là white
+ 1(Đã đc thăm) là Grey
+ 2(đã đc duyệt xong) là black*/

void inp() {
	cout << "Nhap vao n so dinh va m so canh cua do thi co huong: \n";
	cin >> n >> m;

	cout << "Nhap va hai dinh x va y noi thanh canh cua do thi vo huong: \n";
	for (short i = 0; i < m; i++)
	{
		int x, y;
		cin >> x >> y;

		adj[x].push_back(y);
		adj[y].push_back(x);
	}
	memset(color, 0, sizeof(color));
}

bool DFS(int u) {
	color[u] = 1;//Đánh dấu đỉnh u là 1(màu grey) là đã đc thăm 
	for (int v : adj[u]) {//Duyệt danh sách kề của đỉnh u( đỉnh u là đỉnh vừa đc thăm )
		if (color[v] == 0)//Nếu v(v là đỉnh kề với đỉnh vừa đc thăm(đỉnh vừa đc thăm là đỉnh u) tức v là con của đỉnh u) chưa đc thăm 
		{
			if (DFS(v))//Ta truyền v vào hàm đệ quy DFS để thăm đỉnh 
				return true;
		}
		else if (color[v] == 1) {

			return true;
		}
	}

	return false;
}


int main()
{
	inp();
	for (short i = 1; i <= n; i++)
	{
	if (DFS(i))
		cout << "Do thi vo huong co chu trinh !";
	return 0;
	}
		cout << "Do thi vo huong khong co chu trinh !";
}
#endif // 0

#if 1
#include<iostream>
#include<vector>
#include<queue>
using namespace std;
/*================== ÁP DỤNG THUẬT TOÁN KAHN - BFS VÀO KIỂM TRA CHU TRÌNH TRÊN ĐỒ THỊ CÓ HƯỚNG KHÔNG LIÊN THÔNG ==========================C		
* Đối với đồ thị liên thông thì không cần phải có vòng lặp for để tryền hết tất cả các đỉnh vào hàm DFS mà chỉ cần truyền đỉnh ở đầu
đồ thị vào hàm DFS hoặc BFS thì nó sẽ duyệt và thăm hết các đỉnh trong đồ thị
* Đối với đồ thị không liên thông thì khi gọi hàm DFS hoặc BFS thì ta phải tạo 1 vòng lặp for cho chạy từ đỉnh ở đầu đồ thị cho tới
đỉnh ở cuối đồ thị tức phải xét hết các thành phần liên thông của đồ thị xem có chu trình hay không.

input: Nhập vào n số đỉnh của đồ     | output: Xuất ra kết quả là đồ thị có chu trình hay không(Đối input ta nhập thì kết quả của
thị có hướng là n = 7 tức từ 1 đến   | việc kiểm tra chu trình của đồ thị là: Đồ thị có chu trình
7, nhập vào m số cạnh của đồ thị có  |
hướng là m = 6 gồm các cạnh:         |
									 |
				   1 2               |
				   1 5               |
				   2 3               |
				   4 2               |
				   3 6               |
				   6 7               |
				   7 3               |
									 |
										  */
int n, m;//n là số đỉnh của đồ thị , m là số cạnh của đồ thị
vector<int> adj[20];//Chứa danh sách kề của các đỉnh
int degree[20];

void inp() {
	cout << "Nhap vao n dinh va m canh cua do thi: \n";
	cin >> n >> m;

	cout << "Nhap vao hai dinh x va y tao thanh canh cua do thi: \n";
	for (short i = 0; i < m; i++)
	{
		int x, y;
		cin >> x >> y;

		adj[x].push_back(y);
		degree[y]++;
	}
}

/*Cơ chế của áp dụng thuật toán Kahn - BFS vào kiểm tra chu trình của đồ thị có hướng giải thích rất rỏ ở vở CẤU TRÚC DỮ LIỆU VÀ GIẢI
THUẬT -> ĐỒ THỊ 3 VÀ ĐỒ THỊ 4 ->  BÀI 14 nếu quên hãy mở vở lại xem */
bool Kahn() {
	queue<int> q;
	for (short i = 1; i <= n; i++)
	{
		if (degree[i] == 0) {
			q.push(i);
		}
	}

	int cnt = 0;//Biến đếm số đỉnh mà Kahn đã đi đến 
	while (!q.empty())
	{
		int v = q.front();
		q.pop();
		cnt++;
		for (int x : adj[v]) {
			degree[x]--;
			if (degree[x] == 0)
			{
				q.push(x);
			}
		}
	
	}
	cout << cnt<<"\n";
		if (cnt == n)
		{
			return false;
		}
		return true;
}


int main() {
	inp();
	if (Kahn()) cout << "Do thi co chu trinh\n";
	else cout << "Do thi khong co chu trinh\n";
	return 0;
}

#endif