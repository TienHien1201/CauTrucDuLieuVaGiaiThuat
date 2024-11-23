//===============THUẬT TOÁN DISJSTRA TIM ĐƯỜNG ĐI NGẮN NHẤT ==================================
#if 0
#include <iostream>
#include<vector>
#include<queue>
using namespace std;

/*Bài toán: Tìm đường đi ngắn nhất từ đỉnh 1 đến các đỉnh còn lại trong đồ thị
input: n = 6, m = 8, s =1             |  output: 
với =  8 cạnh và trọng số mõi cạnh:   | 1 tới 1 = 0 
          1 2 : 7                     | 1 tới 2 = 7
		  1 3 : 12                    | 1 tới 3 = 9
		  2 3 : 2                     | 1 tới 4 = 16
		  2 4 : 9                     | 1 tới 5 = 19
		  3 5 : 10                    | 1 tới 6 = 17
		  4 6 : 1                     | 
		  5 4 : 4                     | 
		  5 6 : 6                     | */

using ll = long long;

const int maxn = 20;
int n, m, s, t;
vector<pair<int, int>> adj[maxn];

void nhap() {
	cout << "Nhap n dinh va m canh va dinh xuat phat cua do thi: \n";
	cin >> n >> m >> s;

	cout << "Nhap vao hai dinh x y ao thanh canh cua do thi va trong so cua hai dinh x va y: \n";
	for (int i = 0; i < m; i++) {
		int x, y, w; cin >> x >> y >> w;
		adj[x].push_back({ y, w });
		//adj[y].push_back({x, w}); dùng cho đồ thị vô hướng
	}
}

const int INF = 1e9;/*Là độ dài ban đầu từ đỉnh s(là đỉn xuất phát) đến các đỉnh còn lại trong đồ thị tức là ban từ đỉnh s(là đỉnh xuất
phát) mà đi đến các cạnh còn lại trong đồ thị là vô cùng tức chưa xác định*/
int pre[maxn];

void dijkstra(int s) {

	//Mang luu khoang cach duong di
	vector<ll> d(n + 1, INF);/*ban đầu cho khoảng cách từ đỉnh s(là đỉnh xuất phát) đến các đỉnh còn lại trong đồ thị là vô cùng tức 
	chưa xác định*/
	d[s] = 0;//Khoảng các từ đỉnh xuất phát tới chính nó là bằng 0

	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q;/*Dùng hàng đợi ưu tiên để lưu các cặp với mõi cặp
	là 1 phần tử của của hàng đợi ưu tiên tức mõi phần tử có kiểu pair<int, int> và tron mõi cặp là {khoang cach, dinh} tức trọng số và
	đỉnh y chang như thuật toán Prim tối ưu bằng cách sử dụng hàng đợi ưu tiên và hàng đợi ưu tiên luôn sắp xếp các phần tử có phần firt
	nhỏ nhất đứng ở đầu hàng đợi ưu tiên tức là trọng số nhỏ nhất cùng với đỉnh có trọng số nhỏ nhất thì nằm ở đầu hàng đợi */
	
	Q.push({ 0, s });/*Push Khoảng cách từ đỉnh s cho đến đỉnh xuất phát là 0 vì đỉnh ban đầu đc truyền vào hàm dijkstra là đỉnh xuất 
	phát thì khoảng các từ đỉnh xuất phát tới chính nó là = 0*/

	//Duyệt danh sách hàng đợi ưu tiên để lấy phần tử có trọng số nhỏ nhất của đỉnh có trọng số nhỏ nhất
	while (!Q.empty()) {
		//Chọn ra đỉnh có khoảng cách từ s nhỏ nhất 
		pair<int, int> top = Q.top(); Q.pop();
		int u = top.second;//là đỉnh của phần tử vừa đc lấy ra đầu hàng đợi ưu tiên tức là đỉnh có trọng số nhỏ nhất
		int kc = top.first;/*là khoảng cách của phần tử vừa đc lấy ra đầu hàng đợi ưu tiên tức là trọng số nhỏ nhất của đỉnh có trọng 
		số nhỏ nhất*/
		if (kc > d[u])/*Nếu khoảng cách từ đỉnh xuất phát đến đỉnh vừa đc lấy ra khỏi hàng đợi ưu tiên mà đc đã đc cập nhật khoảng cách
			ngắn nhất từ đỉnh xuất phát đến đỉnh vừa đc lấy ra khỏi hàng đợi ưu tiên rồi thì dừng lại không cập nhật lại nữa.*/
			continue;

		/*Nếu khoảng cách từ đỉnh xuất phát đến đỉnh vừa đc lấy ra khỏi hàng đợi ưu tiên mà chưa đc cập nhật khoảng cách ngắn nhất từ 
		đỉnh xuất phát đến đỉnh vừa đc lấy ra khỏi hàng đợi ưu tiên thì ta Relaxtion: Thông qua đỉnh u đã biết khoảng cách ngắn nhất
		tính từ s(đỉnh xuất phát), cập nhật khoảng cách với các đỉnh kề với u*/
		for (auto it : adj[u]) {//Duyệt danh sách kề của đỉnh có trọng số nhỏ nhất vừa đc lấy ra khỏi hàng đợi ưu tiên là đỉnh u
			int v = it.first;/*v là trọng số đỉnh kề với u vì mõi phần tử trong hàng đợi ưu tiên là 1 cặp nên trong cặp thì phần firt
			là phần trọng số*/
			int w = it.second;//Còn phần second là phần đỉnh 
			if (d[v] > d[u] + w) {/*Nếu khoảng cách từ đỉnh s(là đỉnh xuất phát) cho đến đỉnh kề với đỉnh vừa đc lấy ra khỏi hàng
				đợi ưu tiên là đỉnh u mà lớn hơn khoảng cách ta đi thông qua đỉnh u tức  từ s đến v mà  lớn hơn từ s đến u rồi đến v
				thì ta sẽ cập nhật đường ngắn nhất từ là từ s đến u rồi đến v */
				d[v] = d[u] + w;
				Q.push({ d[v], v });
			}
		}
	}
	//Xuất đường đi ngắn nhất từ đỉnh xuất phát đến các đỉnh còn lại trong đồ thị
	
	for (int i = 1; i <= n; i++) {
		cout << "\nKhoang cach ngan nhat tu dinh " << s<< " den dinh " << i << " la: ";
		cout << d[i] << ' ';
	}
}


int main() {
	nhap();
	dijkstra(s);
}
#endif

//==================THUẬT TOÁN DIJKSTRA(TIM DUONG DI NGAN NHAT) TRUY VET DUONG DI ==================================
#include <iostream>
#include<vector>
#include<queue>
using namespace std;

using ll = long long;

const int maxn = 100001;
int n, m, s, t;
vector<pair<int, int>> adj[maxn];

void nhap() {
	cout << "Nhap n dinh va m canh va dinh xuat phat va dinh ket thuc duong di cua do thi: \n";
	cin >> n >> m >> s>>t;

	cout << "Nhap vao hai dinh x y ao thanh canh cua do thi va trong so cua hai dinh x va y: \n";
	for (int i = 0; i < m; i++) {
		int x, y, w; cin >> x >> y >> w;
		adj[x].push_back({ y, w });
		//adj[y].push_back({x, w}); dùng cho đồ thị vô hướng
	}
}

const int INF = 1e9;/*Là độ dài ban đầu từ đỉnh s(là đỉn xuất phát) đến các đỉnh còn lại trong đồ thị tức là ban từ đỉnh s(là đỉnh xuất
phát) mà đi đến các cạnh còn lại trong đồ thị là vô cùng tức chưa xác định*/
int pre[maxn];

void dijkstra(int s,int t) {

	//Mang luu khoang cach duong di
	vector<ll> d(n + 1, INF);/*ban đầu cho khoảng cách từ đỉnh s(là đỉnh xuất phát) đến các đỉnh còn lại trong đồ thị là vô cùng tức
	chưa xác định*/
	d[s] = 0;//Khoảng các từ đỉnh xuất phát tới chính nó là bằng 0
	pre[s] = s;

	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q;/*Dùng hàng đợi ưu tiên để lưu các cặp với mõi cặp
	là 1 phần tử của của hàng đợi ưu tiên tức mõi phần tử có kiểu pair<int, int> và tron mõi cặp là {khoang cach, dinh} tức trọng số và
	đỉnh y chang như thuật toán Prim tối ưu bằng cách sử dụng hàng đợi ưu tiên và hàng đợi ưu tiên luôn sắp xếp các phần tử có phần firt
	nhỏ nhất đứng ở đầu hàng đợi ưu tiên tức là trọng số nhỏ nhất cùng với đỉnh có trọng số nhỏ nhất thì nằm ở đầu hàng đợi */

	Q.push({ 0, s });/*Push Khoảng cách từ đỉnh s cho đến đỉnh xuất phát là 0 vì đỉnh ban đầu đc truyền vào hàm dijkstra là đỉnh xuất
	phát thì khoảng các từ đỉnh xuất phát tới chính nó là = 0*/

	//Duyệt danh sách hàng đợi ưu tiên để lấy phần tử có trọng số nhỏ nhất của đỉnh có trọng số nhỏ nhất
	while (!Q.empty()) {
		//Chọn ra đỉnh có khoảng cách từ s nhỏ nhất 
		pair<int, int> top = Q.top(); Q.pop();
		int u = top.second;//là đỉnh của phần tử vừa đc lấy ra đầu hàng đợi ưu tiên tức là đỉnh có trọng số nhỏ nhất
		int kc = top.first;/*là khoảng cách của phần tử vừa đc lấy ra đầu hàng đợi ưu tiên tức là trọng số nhỏ nhất của đỉnh có trọng
		số nhỏ nhất*/
		if (kc > d[u])/*Nếu khoảng cách từ đỉnh xuất phát đến đỉnh vừa đc lấy ra khỏi hàng đợi ưu tiên mà đc đã đc cập nhật khoảng cách
			ngắn nhất từ đỉnh xuất phát đến đỉnh vừa đc lấy ra khỏi hàng đợi ưu tiên rồi thì dừng lại không cập nhật lại nữa.*/
			continue;

		/*Nếu khoảng cách từ đỉnh xuất phát đến đỉnh vừa đc lấy ra khỏi hàng đợi ưu tiên mà chưa đc cập nhật khoảng cách ngắn nhất từ
		đỉnh xuất phát đến đỉnh vừa đc lấy ra khỏi hàng đợi ưu tiên thì ta Relaxtion: Thông qua đỉnh u đã biết khoảng cách ngắn nhất
		tính từ s(đỉnh xuất phát), cập nhật khoảng cách với các đỉnh kề với u*/
		for (auto it : adj[u]) {//Duyệt danh sách kề của đỉnh có trọng số nhỏ nhất vừa đc lấy ra khỏi hàng đợi ưu tiên là đỉnh u
			int v = it.first;/*v là trọng số đỉnh kề với u vì mõi phần tử trong hàng đợi ưu tiên là 1 cặp nên trong cặp thì phần firt
			là phần trọng số*/
			int w = it.second;//Còn phần second là phần đỉnh 
			if (d[v] > d[u] + w) {/*Nếu khoảng cách từ đỉnh s(là đỉnh xuất phát) cho đến đỉnh kề với đỉnh vừa đc lấy ra khỏi hàng
				đợi ưu tiên là đỉnh u mà lớn hơn khoảng cách ta đi thông qua đỉnh u tức  từ s đến v mà  lớn hơn từ s đến u rồi đến v
				thì ta sẽ cập nhật đường ngắn nhất từ là từ s đến u rồi đến v */
				d[v] = d[u] + w;
				Q.push({ d[v], v });
				pre[v] = u;
			}
		}
	}
	//Xuất đường đi ngắn nhất từ đỉnh xuất phát đến các đỉnh còn lại trong đồ thị
		cout << "\nKhoang cach ngan nhat tu dinh " << s << " den dinh " << t<< " la: ";
		cout << d[t] << ' ';


	//Mảng truy vết đường đi ngắn từ đỉnh s tới đỉnh t
	vector<int>path;
	while (1)
	{
		path.push_back(t);
		if (t == s)
			break;
		t = pre[t];
	}
	reverse(begin(path), end(path));

	cout << "Voi duong di la: ";
	for (int x : path) {

		cout << x << " ";
	}
}

int main() {
	nhap();
	dijkstra(s,t);
}



