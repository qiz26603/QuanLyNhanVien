#include <iostream>
#include <conio.h>
#include <string>
#include <Windows.h>
#include <iomanip>
#include <fstream>
#include <list>
#include <stack>
#pragma warning (disable: 6386)
#pragma warning (disable: 4267)
using namespace std;
typedef struct LyLichNhanVien
{
	string id;
	string name;
	string status;
	int child = 0;
	string hocvan;
	int salary = 0;
	int nghiphep = 0;
	int nghi0phep = 0;
	int lamthem = 0;
	string kq;
	int RealSalary = 0;
}LyLich;
bool CheckExistingID(string id)
{
	ifstream docid;
	docid.open("Manager.txt", ios::app);
	if (docid.is_open())
	{
		string dong;
		while (getline(docid, dong))
		{
			size_t pos = dong.find(',');
			if (pos != SIZE_MAX && (dong.substr(0, pos) == id))
			{
				docid.close();
				return true;
			}
		}
		docid.close();
	}
	return false;
}
bool ID(string id)
{
	if (id.empty() == 1)
	{
		cout << "Ban chua nhap ID!" << endl;
		return false;
	}
	if (id.length() > 8)
	{
		cout << "Ban khong duoc nhap ID qua 8 ky tu!" << endl;
		return false;
	}
	for (int i = 0; i < id.length(); i++)
	{
		if (id[i] >= '0' && id[i] <= '9') {
			continue;
		}
		else if (id[i] >= 'a' && id[i] <= 'z' || id[i] >= 'A' && id[i] <= 'Z') {
			cout << "ID khong chua ky tu chu cai!" << endl;
			return false;
		}
		else
		{
			cout << "ID khong chua ky tu dac biet!" << endl;
			return false;
		}
	}
	return true;
}
bool CheckName(string name)
{
	if (name.empty() == 1)
	{
		cout << "Ban chua nhap ten nhan vien!" << endl;
		return false;
	}
	if (name.length() > 20)
	{
		cout << "Ban khong duoc nhap qua 20 ky tu!" << endl;
		return false;
	}
	else
	{
		for (int i = 0; i < name.length(); i++)
		{
			if (name[0] == ' ')
			{
				cout << "Ten khong duoc co dau cach o truoc ten!" << endl;
				return false;
			}
		}
		for (int i = 0; i < name.length(); i++)
		{
			if (name.back() == ' ')
			{
				cout << "Ten khong duoc co dau cach o cuoi cung!" << endl;
				return false;
			}
		}
		for (int i = 0; i < name.length(); i++)
		{
			if (name[i] == ' ' && name[i + 1] == ' ')
			{
				cout << "Giua cac ten khong duoc co nhieu hon 1 dau cach!" << endl;
				return false;
			}
		}
		for (int i = 0; i < name.length(); i++)
		{
			if (name[i] >= 'a' && name[i] <= 'z' || name[i] >= 'A' && name[i] <= 'Z' || name[i] == ' ')
			{
				continue;
			}
			else
			{
				cout << "Ten khong duoc co ky tu nao khac ky tu chu cai ALPHABET!" << endl;
				return false;
			}
		}
		return true;
	}
}
string StandardName(string& name)
{
	name[0] = toupper(name[0]);
	for (int i = 1; i < name.length(); i++)
	{
		if (name[i] == ' ')
		{
			name[i + 1] = toupper(name[i + 1]);
			i++;
		}
		else if (name[i] != ' ')
		{
			name[i] = tolower(name[i]);
		}
	}
	return name;
}
bool Status(string status)
{
	if (status.empty() == 1)
	{
		cout << "Ban chua nhap tinh trang gia dinh!" << endl;
		return false;
	}
	if (status.length() > 1)
	{
		cout << "Ban da nhap hon 1 ky tu!" << endl;
		return false;
	}
	if (status[0] != 'M' && status[0] != 'S')
	{
		cout << "Ban da nhap ky tu khong hop le!" << endl << "*LUU Y: HAY NHAP DUNG CHU M HOAC CHU S!" << endl;
		return false;
	}
	if (status[0] == 'M' || status[0] == 'S')
	{
		return true;
	}
	return false;
}
bool Children(int child)
{
	if (child >= 0 && child <= 20)
	{
		return true;
	}
	else
	{
		cout << "Ban da nhap sai!" << endl;
		return false;
	}
}
bool Hocvan(string hocvan)
{
	if (hocvan.empty() == 1)
	{
		cout << "Ban chua nhap trinh do van hoa." << endl;
		return false;
	}
	if (hocvan.length() > 2)
	{
		cout << "Ban da nhap hon 2 ky tu!" << endl;
		return false;
	}
	if (hocvan == "C1" || hocvan == "C2" || hocvan == "C3" || hocvan == "DH" || hocvan == "CH")
	{
		return true;
	}
	else
	{
		cout << "Ban da nhap sai!" << endl << "Hay nhap dung ky tu duoc cho phep!" << endl;
		return false;
	}
}
bool CheckLuong(int salary)
{
	if (salary > 0 && salary <= 1000000)
	{
		if (salary % 1000 == 0)
		{
			return true;
		}
		else
		{
			cout << "Tien luong ban nhap phai la boi so cua 1000." << endl << "Vui long nhap lai:" << endl;
			return false;
		}
	}
	else
	{
		cout << "Tien luong vua nhap lon hon 1 trieu hoac <= 0." << endl << "Vui long nhap lai:" << endl;
		return false;
	}
}
void input(list<LyLichNhanVien>& nv)
{
	LyLich Nvien;
	ofstream write;
	int choose = 0;
	float phutroi1 = 0.0, phutroi2 = 0.0, phutroi3 = 0.0;
	string ketqua;
again:
	system("cls");
	cout << "-------------- Them nhan vien, cham cong nhan vien --------------" << endl;
re_id:
	cout << "Xin moi nhap ma nhan vien:" << endl;
	getline(cin, Nvien.id);
	if (CheckExistingID(Nvien.id))
	{
		cout << "Da ton tai ma nhan vien!" << endl << "Vui long nhap lai: " << endl;
		goto re_id;
	}
	if (!ID(Nvien.id))
	{
		cout << "Vui long nhap lai: " << endl;
		goto re_id;
	}
re_name:
	cout << "Xin moi nhap ten nhan vien:" << endl;
	getline(cin, Nvien.name);
	if (CheckName(Nvien.name) == false)
	{
		cout << "Ban da nhap ten khong hop le!" << endl << "Vui long nhap lai: " << endl;
		goto re_name;
	}
	StandardName(Nvien.name);
re_status:
	cout << "Xin moi nhap tinh trang gia dinh (M = Married, S = Single):" << endl;
	getline(cin, Nvien.status);
	if (!Status(Nvien.status))
	{
		cout << "Ban da nhap sai!" << endl << "Vui long nhap lai: " << endl;
		goto re_status;
	}
re_children:
	cout << "Xin moi nhap so con" << endl << "*LUU Y: Nhap so nguyen 0 den 20:" << endl;
	cin >> Nvien.child;
	cin.ignore();
	if (!Children(Nvien.child))
	{
		cout << "Ban da nhap sai!" << endl << "Vui long nhap lai: " << endl;
		goto re_children;
	}
re_hocvan:
	cout << "Xin moi nhap trinh do van hoa" << endl << "(C1 = Cap 1; C2 = Cap 2; C3 = Cap 3; DH = Dai hoc; CH = Cao hoc):" << endl;
	getline(cin, Nvien.hocvan);
	if (!Hocvan(Nvien.hocvan))
	{
		cout << "Ban da nhap sai!" << endl << "Vui long nhap lai: " << endl;
		goto re_hocvan;
	}
re_salary:
	cout << "Xin moi nhap luong can ban (Tien luong phai <=1,000,000): " << endl;
	cin >> Nvien.salary;
	if (!CheckLuong(Nvien.salary))
	{
		goto re_salary;
	}
re_nghiphep:
	cout << "Xin moi nhap so ngay nghi co phep trong thang (<=28)" << endl;
	cin >> Nvien.nghiphep;
	if (Nvien.nghiphep < 0 || Nvien.nghiphep > 28)
	{
		cout << "So ngay nghi co phep ban nhap > 28. Vui long nhap lai." << endl;
		goto re_nghiphep;
	}
re_nghi0phep:
	cout << "Xin moi nhap so ngay nghi khong phep trong thang (<=28)" << endl;
	cin >> Nvien.nghi0phep;
	if (Nvien.nghi0phep < 0 || Nvien.nghi0phep > 28)
	{
		cout << "So ngay nghi khong phep ban nhap > 28. Vui long nhap lai." << endl;
		goto re_nghi0phep;
	}
re_lamthem:
	cout << "Xin moi nhap so ngay lam them trong thang (<=28)" << endl;
	cin >> Nvien.lamthem;
	if (Nvien.lamthem < 0 || Nvien.lamthem > 28)
	{
		cout << "So ngay lam them ban nhap > 28. Vui long nhap lai." << endl;
		goto re_lamthem;
	}
re_kq:
	cout << "Xin moi nhap ket qua cong viec (T = Tot; TB = Dat; K = Kem):" << endl;
	cin >> Nvien.kq;
	cin.ignore();
	if ((Nvien.kq).length() > 2)
	{
		cout << "Ket qua cong viec ban nhap lon hon 2 ky tu. Vui long nhap lai." << endl;
		goto re_kq;
	}
	else
	{
		if (Nvien.kq == "T" || Nvien.kq == "TB" || Nvien.kq == "K")
		{
			goto salaryreal;
		}
		else
		{
			cout << "Ket qua cong viec ban nhap khong hop le. Vui long nhap lai." << endl;
			goto re_kq;
		}
	}
salaryreal:
	cout << endl << "Dang tien hanh cham cong cho nhan vien." << endl;
	cout << "--- 1 ---" << endl;
	Sleep(1000);
	if (Nvien.child > 2)
	{
		phutroi1 = (float)(Nvien.salary * 5) / 100;
	}
	if (Nvien.hocvan == "CH")
	{
		phutroi2 = (float)(Nvien.salary * 10) / 100;
	}
	if (Nvien.lamthem > 0)
	{
		phutroi3 = (float)((Nvien.salary * 4) / 100) * (Nvien.lamthem);
	}
	Nvien.RealSalary = Nvien.salary + (int)phutroi1 + (int)phutroi2 + (int)phutroi3;
	cout << "--- 2 ---" << endl;
	Sleep(1000);
	cout << "--- 3 ---" << endl;
	Sleep(1000);
	if (Nvien.RealSalary <= 2000000)
	{
		cout << "Da cham cong cho nhan vien thanh cong." << endl;
	}
	else
	{
		cout << "Cham cong khong thanh cong vi Luong thuc linh > 2,000,000." << endl;
		cout << "Vui long nhap lai thong tin nhan vien." << endl;
		goto again;
	}
	write.open("Manager.txt", ios::app);
	if (!write)
	{
		cout << "File bi loi. Khong the mo de ghi file." << endl << "Vui long kiem tra lai file." << endl;
	}
	else
	{
		write << Nvien.id << "," << Nvien.name << "," << Nvien.status << "," << Nvien.child << "," << Nvien.hocvan << "," << Nvien.salary << "," << Nvien.nghiphep << "," << Nvien.nghi0phep << "," << Nvien.lamthem << "," << Nvien.kq << "," << Nvien.RealSalary << endl;
		write.close();
	}
	cout << "Them nhan vien thanh cong." << endl;
	nv.push_back(Nvien);
continue1:
	cout << endl << "Ban co muon nhap them thong tin nhan vien nua khong ?" << endl;
	cout << "1: Tiep tuc " << endl;
	cout << "0: Quay lai Menu " << endl;
	cin >> choose;
	cin.ignore();
	switch (choose)
	{
	case 1:
	{
		Sleep(500);
		system("cls");
		goto again;
		break;
	}
	case 0:
	{
		break;
	}
	default:
	{
		cout << "Ban da nhap SAI!" << endl << "VUI LONG NHAP LAI:" << endl;
		goto continue1;
		break;
	}
	}
}
string rutgon_ttgd(string a) {
	if (a == "M")
		return "Married";
	else
		return "Single";
}
string rutgon_hocvan(string a) {
	if (a == "C1")
		return "Cap 1";
	else if (a == "C2")
		return "Cap 2";
	else if (a == "C3")
		return "Cap 3";
	else if (a == "DH")
		return "Dai hoc";
	else
		return "Cao hoc";
}
string rutgon_ketqua(string a) {
	if (a == "T")
		return "Tot";
	else if (a == "TB")
		return "Dat";
	else
		return "Kem";
}
void docFile(list<LyLichNhanVien>& nv)
{
	ifstream read;
	LyLichNhanVien Nvien;
	read.open("Manager.txt", ios::app);
	if (!read)
	{
		cout << "File loi, khong the doc file." << endl << "Vui long kiem tra File." << endl;
	}
	else
	{
		nv.clear();
		string dong;
		while (getline(read, dong))
		{
			size_t pos = dong.find(',');				//id
			size_t pos1 = dong.find(',', pos + 1);		//name
			size_t pos2 = dong.find(',', pos1 + 1);		//ttgd
			size_t pos3 = dong.find(',', pos2 + 1);		//socon
			size_t pos4 = dong.find(',', pos3 + 1);		//hocvan
			size_t pos5 = dong.find(',', pos4 + 1);		//salary
			size_t pos6 = dong.find(',', pos5 + 1);		//nghiphep
			size_t pos7 = dong.find(',', pos6 + 1);		//nghi0phep
			size_t pos8 = dong.find(',', pos7 + 1);		//lamthem
			size_t pos9 = dong.find(',', pos8 + 1);		//kq
			size_t pos10 = dong.find('\n', pos9 + 1);	//Realsalary
			Nvien.id = dong.substr(0, pos);
			Nvien.name = dong.substr(pos + 1, pos1 - pos - 1);
			Nvien.status = dong.substr(pos1 + 1, pos2 - pos1 - 1);
			Nvien.child = stoi(dong.substr(pos2 + 1, pos3 - pos2 - 1));
			Nvien.hocvan = dong.substr(pos3 + 1, pos4 - pos3 - 1);
			Nvien.salary = stoi(dong.substr(pos4 + 1, pos5 - pos4 - 1));
			Nvien.nghiphep = stoi(dong.substr(pos5 + 1, pos6 - pos5 - 1));
			Nvien.nghi0phep = stoi(dong.substr(pos6 + 1, pos7 - pos6 - 1));
			Nvien.lamthem = stoi(dong.substr(pos7 + 1, pos8 - pos7 - 1));
			Nvien.kq = dong.substr(pos8 + 1, pos9 - pos8 - 1);
			Nvien.RealSalary = stoi(dong.substr(pos9 + 1, pos10 - pos9 - 1));
			nv.push_back(Nvien);
		}
		read.close();
	}
}
void draw_line(int size, char a) {
	cout << setfill(a);
	cout << left << setw(size) << a << endl;
	cout << setfill(' ');
}
void format(string a, int size, bool c, bool e) {
	if (!e) {
		if (!c) {
			cout << left << "| " << setw(size) << a;
		}
		else {
			cout << left << "| " << setw(size) << a << right << "|";
		}
	}
	else {
		string s = "";
		for (int i = 0; i < size / 2 - a.length() / 2; i++) {
			s = s + " ";
		}
		s = s + a;
		if (!c) {
			cout << left << "| " << setw(size) << s;
		}
		else {
			cout << left << "| " << setw(size) << s << right << "|";
		}
	}
}
string PrintCurrency(int money) {
	string moneystring = to_string(money);
	int comma = 0, locate = 0;
	comma = (moneystring.length() - 1) / 3;
	locate = moneystring.length() - comma * 3;
	while (comma > 0) {
		moneystring.insert(locate, ",");
		locate += 4;
		comma--;
	}
	return moneystring + " VND";
}
void Delete(list<LyLichNhanVien>& nv)
{
	int choose_delete, flag = 0, continue_delete;
	string idCanxoa;
	ofstream write;
	ifstream read;
	LyLichNhanVien Nvien;
	list<LyLichNhanVien>::iterator itr;
	list<LyLichNhanVien>::iterator itr2;
	read.open("Manager.txt", ios::app);
	if (!read)
	{
		cout << "File loi, khong the doc file." << endl << "Vui long kiem tra File." << endl;
	}
	else
	{
		nv.clear();
		string dong;
		while (getline(read, dong))
		{
			size_t pos = dong.find(',');				//id
			size_t pos1 = dong.find(',', pos + 1);		//name
			size_t pos2 = dong.find(',', pos1 + 1);		//ttgd
			size_t pos3 = dong.find(',', pos2 + 1);		//socon
			size_t pos4 = dong.find(',', pos3 + 1);		//hocvan
			size_t pos5 = dong.find(',', pos4 + 1);		//salary
			size_t pos6 = dong.find(',', pos5 + 1);		//nghiphep
			size_t pos7 = dong.find(',', pos6 + 1);		//nghi0phep
			size_t pos8 = dong.find(',', pos7 + 1);		//lamthem
			size_t pos9 = dong.find(',', pos8 + 1);		//kq
			size_t pos10 = dong.find('\n', pos9 + 1);	//Realsalary
			Nvien.id = dong.substr(0, pos);										//cat id tu file
			Nvien.name = dong.substr(pos + 1, pos1 - pos - 1);					//cat name tu file
			Nvien.status = dong.substr(pos1 + 1, pos2 - pos1 - 1);				//cat status tu file
			Nvien.child = stoi(dong.substr(pos2 + 1, pos3 - pos2 - 1));			//cat child tu file
			Nvien.hocvan = dong.substr(pos3 + 1, pos4 - pos3 - 1);				//cat hocvan tu file
			Nvien.salary = stoi(dong.substr(pos4 + 1, pos5 - pos4 - 1));		//cat salary tu file
			Nvien.nghiphep = stoi(dong.substr(pos5 + 1, pos6 - pos5 - 1));		//cat nghiphep tu file
			Nvien.nghi0phep = stoi(dong.substr(pos6 + 1, pos7 - pos6 - 1));		//cat nghi0phep tu file
			Nvien.lamthem = stoi(dong.substr(pos7 + 1, pos8 - pos7 - 1));		//cat lamthem tu file
			Nvien.kq = dong.substr(pos8 + 1, pos9 - pos8 - 1);					//cat kq tu file
			Nvien.RealSalary = stoi(dong.substr(pos9 + 1, pos10 - pos9 - 1));	//cat Realsalary tu file
			nv.push_back(Nvien);
		}
		read.close();
	}
Delete:
	system("cls");
	cout << "------------------------- Xoa nhan vien ------------------------" << endl;
	cout << "Xin moi nhap vao ID nhan vien can xoa: " << endl;
	cin >> idCanxoa;
	cin.ignore();
	if (!ID(idCanxoa))
	{
		cout << "Vui long nhap lai: " << endl;
		goto Delete;
	}
	auto vitrixoa = nv.begin();
	for (itr = nv.begin(); itr != nv.end(); ++itr)
	{
		if ((*itr).id == idCanxoa)
		{
			flag = 1;
			break;
		}
		vitrixoa++;
	}
	if (flag == 1)
	{
	conti_xoa:
		cout << "Ban co chac chan muon xoa nhan vien khong ?" << endl;
		cout << "1: Co" << endl;
		cout << "0: Khong" << endl;
		cin >> continue_delete;
		cin.ignore();
		if (continue_delete != 0 && continue_delete != 1)
		{
			cout << "Ban da lua chon khong hop le. Vui long chon lai." << endl;
			goto conti_xoa;
		}
		else
		{
			if (continue_delete == 0)
			{
				cout << "Khong xoa nhan vien vua tim. Quay lai menu sau 2 giay." << endl;
				Sleep(2000);
			}
			else if (continue_delete == 1)
			{
				nv.erase(vitrixoa);
				cout << "Xoa nhan vien thanh cong." << endl;
				write.open("Manager.txt");
				if (!write)
				{
					cout << "File bi loi. Khong the mo de ghi file." << endl << "Vui long kiem tra lai file." << endl;
				}
				else
				{
					for (itr2 = nv.begin(); itr2 != nv.end(); ++itr2)
					{
						write << (*itr2).id << "," << (*itr2).name << "," << (*itr2).status << "," << (*itr2).child << "," << (*itr2).hocvan << "," << (*itr2).salary << "," << (*itr2).nghiphep << "," << (*itr2).nghi0phep << "," << (*itr2).lamthem << "," << (*itr2).kq << "," << (*itr2).RealSalary << endl;
					}
					write.close();
				}
				cout << "Quay lai chon thao tac sau 2 giay." << endl;
				cout << "--- 1 ---" << endl;
				Sleep(1000);
				cout << "--- 2 ---" << endl;
				Sleep(1000);
			}
		}
	}
	else
	{
		cout << "Khong tim thay ID nhan vien: " << idCanxoa << endl;
	ChooseDelete:
		cout << "Ban co muon nhap lai ID can xoa khong ?" << endl;
		cout << "1: Co" << endl;
		cout << "0: Khong, thoat xoa" << endl;
		cin >> choose_delete;
		switch (choose_delete)
		{
		case 1:
		{
			goto Delete;
			break;
		}
		case 0:
		{
			cout << "Quay ve chon thao tac" << endl;
			break;
		}
		default:
		{
			cout << "vui long nhap lua chon hop le" << endl;
			goto ChooseDelete;
		}
		}
	}
}
void Search(list<LyLichNhanVien>& nv)
{
	ifstream read;
	LyLichNhanVien Nvien;
	int choose_search, flag = 0;
	string idCantim;
	list<LyLichNhanVien>::iterator itr;
	read.open("Manager.txt", ios::app);
	if (!read)
	{
		cout << "File loi, khong the doc file." << endl << "Vui long kiem tra File." << endl;
	}
	else
	{
		nv.clear();
		string dong;
		while (getline(read, dong))
		{
			size_t pos = dong.find(',');				//id
			size_t pos1 = dong.find(',', pos + 1);		//name
			size_t pos2 = dong.find(',', pos1 + 1);		//ttgd
			size_t pos3 = dong.find(',', pos2 + 1);		//socon
			size_t pos4 = dong.find(',', pos3 + 1);		//hocvan
			size_t pos5 = dong.find(',', pos4 + 1);		//salary
			size_t pos6 = dong.find(',', pos5 + 1);		//nghiphep
			size_t pos7 = dong.find(',', pos6 + 1);		//nghi0phep
			size_t pos8 = dong.find(',', pos7 + 1);		//lamthem
			size_t pos9 = dong.find(',', pos8 + 1);		//kq
			size_t pos10 = dong.find('\n', pos9 + 1);	//Realsalary
			Nvien.id = dong.substr(0, pos);
			Nvien.name = dong.substr(pos + 1, pos1 - pos - 1);
			Nvien.status = dong.substr(pos1 + 1, pos2 - pos1 - 1);
			Nvien.child = stoi(dong.substr(pos2 + 1, pos3 - pos2 - 1));
			Nvien.hocvan = dong.substr(pos3 + 1, pos4 - pos3 - 1);
			Nvien.salary = stoi(dong.substr(pos4 + 1, pos5 - pos4 - 1));
			Nvien.nghiphep = stoi(dong.substr(pos5 + 1, pos6 - pos5 - 1));
			Nvien.nghi0phep = stoi(dong.substr(pos6 + 1, pos7 - pos6 - 1));
			Nvien.lamthem = stoi(dong.substr(pos7 + 1, pos8 - pos7 - 1));
			Nvien.kq = dong.substr(pos8 + 1, pos9 - pos8 - 1);
			Nvien.RealSalary = stoi(dong.substr(pos9 + 1, pos10 - pos9 - 1));
			nv.push_back(Nvien);
		}
		read.close();
	}
Search:
	system("cls");
	cout << "----------------------- Tim kiem nhan vien ---------------------" << endl;
	cout << "Xin moi nhap vao ID nhan vien can tim: " << endl;
	cin >> idCantim;
	if (!ID(idCantim))
	{
		cout << "Vui long nhap lai: " << endl;
		goto Search;
	}
	for (itr = nv.begin(); itr != nv.end(); ++itr)
	{
		if ((*itr).id == idCantim)
		{
			flag = 1;
			cout << "Da tim thay ID nhan vien: " << idCantim << endl;
			draw_line(41, '~');
			cout << "THONG TIN NHAN VIEN: " << endl;
			draw_line(115, '-');
			format("Ma nhan vien ", 13, 0, 1);
			format("Ten nhan vien ", 23, 0, 1);
			format("Tinh trang gia dinh ", 20, 0, 1);
			format("So con ", 9, 0, 1);
			format("Trinh do van hoa ", 19, 0, 1);
			format("Luong can ban ", 18, 1, 1);
			cout << endl;
			draw_line(115, '-');
			format((*itr).id, 13, 0, 1);
			format((*itr).name, 23, 0, 0);
			format(rutgon_ttgd((*itr).status), 20, 0, 1);
			format(to_string((*itr).child), 9, 0, 1);
			format(rutgon_hocvan((*itr).hocvan), 19, 0, 1);
			format(PrintCurrency((*itr).salary) + ' ', 18, 1, 1);
			cout << endl;
			draw_line(115, '-');
			draw_line(41, '~');
			cout << "CHAM CONG NHAN VIEN TRONG THANG: " << endl;
			draw_line(115, '-');
			format("So ngay nghi co phep ", 23, 0, 1);
			format("So ngay nghi 0 phep ", 24, 0, 1);
			format("So ngay lam them ", 19, 0, 1);
			format("Ket qua cong viec ", 20, 0, 1);
			format("Luong thuc linh ", 18, 1, 1);
			cout << endl;
			draw_line(115, '-');
			format(to_string((*itr).nghiphep), 23, 0, 1);
			format(to_string((*itr).nghi0phep), 24, 0, 1);
			format(to_string((*itr).lamthem), 19, 0, 1);
			format(rutgon_ketqua((*itr).kq), 20, 0, 1);
			format(PrintCurrency((*itr).RealSalary) + ' ', 18, 1, 1);
			cout << endl;
			draw_line(115, '-');
			cout << "Quay lai chon thao tac: " << endl;
			system("pause");
		}
	}
	if (flag == 0)
	{
		cout << "Khong tim thay ID nhan vien: " << idCantim << endl;
	ChooseSearch:
		cout << "Ban co muon nhap lai ID can tim kiem khong ?" << endl;
		cout << "1: Co" << endl;
		cout << "0: Khong, thoat tim kiem" << endl;
		cin >> choose_search;
		switch (choose_search)
		{
		case 1:
		{
			goto Search;
			break;
		}
		case 0:
		{
			cout << "Quay ve chon thao tac" << endl;
			break;
		}
		default:
		{
			cout << "vui long nhap lua chon hop le" << endl;
			goto ChooseSearch;
		}
		}
	}
}
void output(list<LyLichNhanVien>& nv)
{
	ifstream read;
	LyLichNhanVien Nvien;
	list<LyLichNhanVien>::iterator itr;
	read.open("Manager.txt", ios::app);
	if (!read)
	{
		cout << "File loi, khong the doc file." << endl << "Vui long kiem tra File." << endl;
	}
	else
	{
		nv.clear();
		string dong;
		while (getline(read, dong))
		{
			size_t pos = dong.find(',');				//id
			size_t pos1 = dong.find(',', pos + 1);		//name
			size_t pos2 = dong.find(',', pos1 + 1);		//ttgd
			size_t pos3 = dong.find(',', pos2 + 1);		//socon
			size_t pos4 = dong.find(',', pos3 + 1);		//hocvan
			size_t pos5 = dong.find(',', pos4 + 1);		//salary
			size_t pos6 = dong.find(',', pos5 + 1);		//nghiphep
			size_t pos7 = dong.find(',', pos6 + 1);		//nghi0phep
			size_t pos8 = dong.find(',', pos7 + 1);		//lamthem
			size_t pos9 = dong.find(',', pos8 + 1);		//kq
			size_t pos10 = dong.find('\n', pos9 + 1);	//Realsalary
			Nvien.id = dong.substr(0, pos);
			Nvien.name = dong.substr(pos + 1, pos1 - pos - 1);
			Nvien.status = dong.substr(pos1 + 1, pos2 - pos1 - 1);
			Nvien.child = stoi(dong.substr(pos2 + 1, pos3 - pos2 - 1));
			Nvien.hocvan = dong.substr(pos3 + 1, pos4 - pos3 - 1);
			Nvien.salary = stoi(dong.substr(pos4 + 1, pos5 - pos4 - 1));
			Nvien.nghiphep = stoi(dong.substr(pos5 + 1, pos6 - pos5 - 1));
			Nvien.nghi0phep = stoi(dong.substr(pos6 + 1, pos7 - pos6 - 1));
			Nvien.lamthem = stoi(dong.substr(pos7 + 1, pos8 - pos7 - 1));
			Nvien.kq = dong.substr(pos8 + 1, pos9 - pos8 - 1);
			Nvien.RealSalary = stoi(dong.substr(pos9 + 1, pos10 - pos9 - 1));
			nv.push_back(Nvien);
		}
		read.close();
	}
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ DANH SACH THONG TIN CAC NHAN VIEN ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl << endl << endl;
	draw_line(115, '-');
	format("Ma nhan vien ", 13, 0, 1);
	format("Ten nhan vien ", 23, 0, 1);
	format("Tinh trang gia dinh ", 20, 0, 1);
	format("So con ", 9, 0, 1);
	format("Trinh do van hoa ", 19, 0, 1);
	format("Luong thuc linh ", 18, 1, 1);
	cout << endl;
	draw_line(115, '-');
	for (itr = nv.begin(); itr != nv.end(); ++itr)
	{
		format((*itr).id, 13, 0, 1);
		format((*itr).name, 23, 0, 0);
		format(rutgon_ttgd((*itr).status), 20, 0, 1);
		format(to_string((*itr).child), 9, 0, 1);
		format(rutgon_hocvan((*itr).hocvan), 19, 0, 1);
		format(PrintCurrency((*itr).RealSalary) + ' ', 18, 1, 1);
		cout << endl;
		draw_line(115, '-');
	}
	system("pause");
}
void outputLuong(list<LyLichNhanVien>& nv)
{
	ifstream read;
	LyLichNhanVien Nvien;
	list<LyLichNhanVien>::iterator itr;
	read.open("Manager.txt", ios::app);
	if (!read)
	{
		cout << "File loi, khong the doc file." << endl << "Vui long kiem tra File." << endl;
	}
	else
	{
		nv.clear();
		string dong;
		while (getline(read, dong))
		{
			size_t pos = dong.find(',');				//id
			size_t pos1 = dong.find(',', pos + 1);		//name
			size_t pos2 = dong.find(',', pos1 + 1);		//ttgd
			size_t pos3 = dong.find(',', pos2 + 1);		//socon
			size_t pos4 = dong.find(',', pos3 + 1);		//hocvan
			size_t pos5 = dong.find(',', pos4 + 1);		//salary
			size_t pos6 = dong.find(',', pos5 + 1);		//nghiphep
			size_t pos7 = dong.find(',', pos6 + 1);		//nghi0phep
			size_t pos8 = dong.find(',', pos7 + 1);		//lamthem
			size_t pos9 = dong.find(',', pos8 + 1);		//kq
			size_t pos10 = dong.find('\n', pos9 + 1);	//Realsalary
			Nvien.id = dong.substr(0, pos);
			Nvien.name = dong.substr(pos + 1, pos1 - pos - 1);
			Nvien.nghiphep = stoi(dong.substr(pos5 + 1, pos6 - pos5 - 1));
			Nvien.nghi0phep = stoi(dong.substr(pos6 + 1, pos7 - pos6 - 1));
			Nvien.lamthem = stoi(dong.substr(pos7 + 1, pos8 - pos7 - 1));
			Nvien.kq = dong.substr(pos8 + 1, pos9 - pos8 - 1);
			Nvien.RealSalary = stoi(dong.substr(pos9 + 1, pos10 - pos9 - 1));
			nv.push_back(Nvien);
		}
	}
	read.close();
	cout << endl << endl << endl;
	draw_line(155, '-');
	format("Ma nhan vien ", 13, 0, 1);
	format("Ten nhan vien ", 23, 0, 1);
	format("So ngay nghi co phep ", 23, 0, 1);
	format("So ngay nghi 0 phep ", 24, 0, 1);
	format("So ngay lam them ", 19, 0, 1);
	format("Ket qua cong viec ", 20, 0, 1);
	format("Luong thuc linh ", 18, 1, 1);
	cout << endl;
	draw_line(155, '-');
	for (itr = nv.begin(); itr != nv.end(); ++itr)
	{
		format((*itr).id, 13, 0, 1);
		format((*itr).name, 23, 0, 0);
		format(to_string((*itr).nghiphep), 23, 0, 1);
		format(to_string((*itr).nghi0phep), 24, 0, 1);
		format(to_string((*itr).lamthem), 19, 0, 1);
		format(rutgon_ketqua((*itr).kq), 20, 0, 1);
		format(PrintCurrency((*itr).RealSalary) + ' ', 18, 1, 1);
		cout << endl;
		draw_line(155, '-');
	}
	cout << endl << endl << endl;
	system("pause");
}
void swap(int& vt1, int& vt2) {
	int temp = vt1;
	vt1 = vt2;
	vt2 = temp;
}
int partition(int mang[], int low, int high) {
	int key = mang[high];
	int i = low - 1;

	for (int j = low; j < high; j++) {
		if (mang[j] < key) {
			i++;
			swap(mang[i], mang[j]);
		}
	}
	swap(mang[i + 1], mang[high]);
	return i + 1;
}
void LuongQuickSort(int a[], int low, int high)
{
	stack<int> ds;
	ds.push(low);
	ds.push(high);
	while (!ds.empty()) {
		high = ds.top();
		ds.pop();
		low = ds.top();
		ds.pop();
		int vitrichot = partition(a, low, high);
		if (vitrichot - 1 > low) {
			ds.push(low);
			ds.push(vitrichot - 1);
		}
		if (vitrichot + 1 < high) {
			ds.push(vitrichot + 1);
			ds.push(high);
		}
	}
}
void Menu(list<LyLichNhanVien>& nv)
{
	int option, choose;
MENU:
	system("cls");
	cout << "~~~~~~~~~~~~~~~~~~~~ QUAN LY NHAN VIEN ~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "~~~~~~~~~~~~~~ XIN MOI CHON CHUC NANG BAN MUON ~~~~~~~~~~~~~~" << endl;
	cout << "~      1: Cap nhat Ly lich nhan vien                        ~" << endl;
	cout << "~      2: Xem bang luong nhan vien                          ~" << endl;
	cout << "~      3: Sap xep nhan vien theo thu tu luong tang dan      ~" << endl;
	cout << "~      0: Thoat chuong trinh                                ~" << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "Lua chon cua ban la: " << endl;
	cin >> option;
	switch (option)
	{
	case 1:
	{
	CHOOSE:
		system("cls");
		cout << "~~~~~~~~~~~~~~~~~ CAP NHAT LY LICH NHAN VIEN ~~~~~~~~~~~~~~~~~~~~~~" << endl;
		cout << "~              Xin moi chon thao tac tiep theo:                   ~" << endl;
		cout << "~          1: Them nhan vien, cham cong nhan vien                 ~" << endl;
		cout << "~          2: Xoa nhan vien                                       ~" << endl;
		cout << "~          3: Tim kiem nhan vien                                  ~" << endl;
		cout << "~          4: Hien thi thong tin, bang luong cac nhan vien        ~" << endl;
		cout << "~          0: Quay lai Menu                                       ~" << endl;
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		cout << "Lua chon cua ban la: " << endl;
		cin >> choose;
		cin.ignore();
		switch (choose)
		{
		case 1:
		{
			input(nv);
			goto CHOOSE;
			break;
		}
		case 2:
		{
			Delete(nv);
			goto CHOOSE;
			break;
		}
		case 3:
		{
			Search(nv);
			goto CHOOSE;
			break;
		}
		case 4:
		{
			system("cls");
			cout << "--------- Hien thi thong tin, bang luong cac nhan vien ---------" << endl;
			output(nv);
			goto CHOOSE;
			break;
		}
		case 0:
		{
			goto MENU;
			break;
		}
		default:
		{
			cout << "Nhap thao tac khong hop le!" << endl << "Vui long nhap lai: " << endl;
			goto CHOOSE;
		}
		}
	}
	case 2:
	{
		system("cls");
		cout << "~~~~~~~~~~~~~~~~~ BANG LUONG NHAN VIEN ~~~~~~~~~~~~~~~~~~~~~~" << endl;
		outputLuong(nv);
		goto MENU;
		break;
	}
	case 3:
	{
		system("cls");
		cout << "~~~~~~ BANG LUONG NHAN VIEN THEO THU TU LUONG TANG DAN ~~~~~~" << endl;
		docFile(nv);
		int dem = 0, j = 0;
		for (auto& i : nv)
		{
			dem++;
		}
		int* dsach = new int[dem];
		for (auto itr = nv.begin(); itr != nv.end(); ++itr)
		{
			dsach[j] = (*itr).RealSalary;
			j++;
		}
		LuongQuickSort(dsach, 0, nv.size() - 1);
		cout << endl << endl << endl;
		draw_line(115, '-');
		format("Ma nhan vien ", 13, 0, 1);
		format("Ten nhan vien ", 23, 0, 1);
		format("Tinh trang gia dinh ", 20, 0, 1);
		format("So con ", 9, 0, 1);
		format("Trinh do van hoa ", 19, 0, 1);
		format("Luong thuc linh ", 18, 1, 1);
		cout << endl;
		draw_line(115, '-');
		auto k = nv.begin();
		for (int i = 0; i < dem; i++)
		{
			for (auto itr = nv.begin(); itr != nv.end(); ++itr)
			{
				if (dsach[i] == (*itr).RealSalary)
				{
					k = itr;
					format((*itr).id, 13, 0, 1);
					format((*itr).name, 23, 0, 0);
					format(rutgon_ttgd((*itr).status), 20, 0, 1);
					format(to_string((*itr).child), 9, 0, 1);
					format(rutgon_hocvan((*itr).hocvan), 19, 0, 1);
					format(PrintCurrency((*itr).RealSalary) + ' ', 18, 1, 1);
					cout << endl;
					draw_line(115, '-');
				}
			}
			nv.erase(k);
		}
		delete[] dsach;
		cout << endl << endl << endl;
		system("pause");
		goto MENU;
		break;
	}
	case 0:
	{
		system("cls");
		cout << "~~~~~~~~~~~~~~~~~~~ THOAT CHUONG TRINH ~~~~~~~~~~~~~~~~~~~~~~" << endl;
		cout << "Thoat sau 3 giay." << endl;
		cout << "--- 1 ---" << endl;
		Sleep(1000);
		cout << "--- 2 ---" << endl;
		Sleep(1000);
		cout << "--- 3 ---" << endl;
		Sleep(1000);
		break;
	}
	default:
	{
		cout << "Nhap thao tac khong hop le!" << endl << "Vui long nhap lai: " << endl;
		goto MENU;
	}
	}
}
int main()
{
	list< LyLichNhanVien> LyLich;
	Menu(LyLich);
	system("pause");
	return 0;
}