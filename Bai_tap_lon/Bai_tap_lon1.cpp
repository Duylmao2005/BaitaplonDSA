#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<list>

using namespace std;

class Diem{
	public:
		string tenSV;
		string lop;
		int maSV;
		float diemGiuaky;
		float diemCuoiky;
		float gpa;
		
		Diem() : tenSV(""), lop(""), maSV(0), diemGiuaky(0.0f), diemCuoiky(0.0f), gpa(0.0f){
		}
		
		friend istream& operator>>(istream& in, Diem& sv) {
    		cout << "Nhap ma sinh vien: ";
    		in >> sv.maSV;
    		 if (sv.maSV == -1) return in;
    		cout << "Nhap ten sinh vien: ";
    		in.ignore();
    		getline(in, sv.tenSV);
    		cout << "Nhap diem giua ky: ";
    		in >> sv.diemGiuaky;
    		cout << "Nhap diem cuoi ky: ";
    		in >> sv.diemCuoiky;
    		sv.gpa = sv.diemGiuaky*0.4 + sv.diemCuoiky*0.6;
    		return in;
		}
		
		friend ostream& operator<<(ostream& out, const Diem& sv) {
    		out << "Ma SV: " << sv.maSV << ", Ten: " << sv.tenSV << ", Diem Giua Ky: " << sv.diemGiuaky << ", Diem Cuoi Ky: " << sv.diemCuoiky << ", GPA: " << sv.gpa << endl;
    		return out;
		}
		
		bool operator<(const Diem& diem){
			return gpa < diem.gpa;
		}
};

class QuanlydanhsachdiemMSV{
	private:
		vector<Diem> dsChan;
		list<Diem> dsLe;
	public:
		//Hàm nhap danh sach sinh vien
		void nhapdanhsach(){
			Diem sv;
			while(true){
				cin >> sv;
				if(sv.maSV == -1) break;
				if(sv.maSV % 2 == 0) dsChan.push_back(sv);
				else dsLe.push_back(sv);
			}
		}
		//Hàm xuat thong tin danh sach sinh vien
		void xuatthongtin() {
    		if (!dsChan.empty()) {
        		cout << "Danh sach MSV chan:\n";
        		for (const auto& sv : dsChan) {
            	cout << sv;
        		}
    		} 
			else {
        		cout << "Khong co sinh vien nao co ma sinh vien chan.\n";
    		}
    
    		if (!dsLe.empty()) {
        		cout << "Danh sach MSV le:\n";
        		for (const auto& sv : dsLe) {
            		cout << sv;
        		}
    		}
			else {
        		cout << "Khong co sinh vien nao co ma sinh vien le.\n";
    		}
		}
		//Hàm sap xep theo GPA
		void SapxepDiemdsChan(){
			sort(dsChan.begin(), dsChan.end());
			
		}
		void SapxepDiemdsLe(){
			dsLe.sort();
		}
		//Tìm sinh viên có GPA lon nhat
		void MaxGPA() {
        	if (!dsChan.empty()) {
            	auto maxSvChan = max_element(dsChan.begin(), dsChan.end());
            	cout << "Sinh vien co GPA cao nhat trong danh sach chan:\n" << *maxSvChan;
        	} 
			else {
            	cout << "Khong co sinh vien nao trong danh sach chan.\n";
        	}

        	if (!dsLe.empty()) {
            	auto maxSvLe = max_element(dsLe.begin(), dsLe.end());
            	cout << "Sinh vien co GPA cao nhat trong danh sach le:\n" << *maxSvLe;
        	} 
			else {
            	cout << "Khong co sinh vien nao trong danh sach le.\n";
        	}
    	}
    	//Tìm sinh viên có GPA bé nhat
    	void MinGPA() {
        	if (!dsChan.empty()) {
            	auto minSvChan = min_element(dsChan.begin(), dsChan.end());
            	cout << "Sinh vien co GPA be nhat trong danh sach chan:\n" << *minSvChan;
        	} 
			else {
            	cout << "Khong co sinh vien nao trong danh sach chan.\n";
        	}

        	if (!dsLe.empty()) {
            	auto minSvLe = min_element(dsLe.begin(), dsLe.end());
            	cout << "Sinh vien co GPA be nhat trong danh sach le:\n" << *minSvLe;
        	} 
			else {
            	cout << "Khong co sinh vien nao trong danh sach le.\n";
        	}
    	}
    	//Tìm kiem sinh vien dua theo ma sinh vien
    	void TimkiemSVtheoMSV(){
    		int check = 0;
    		cout << "Vui long nhap vao ma sinh vien can tim!";
    		int MSV;
    		cin >> MSV;
    		if(MSV % 2 ==0){
    			for(auto& sv : dsChan){
    				if(MSV == sv.maSV){
    					cout << "Sinh vien can tim la: \n" << sv;
    					check = 1;
					}
				}
			}
			else{
				for(auto& sv : dsLe){
    				if(MSV == sv.maSV){
    					cout << "Sinh vien can tim la: \n" << sv;
    					check = 1;
					}
				}
			}
			if(check == 0) cout << "Khong tim thay sinh vien can tim!\n";
		}
		//Thong kê ds sinh viên có gpa >= 8
		void dsChanGPAgioi(){
			int check = 0;
			cout << "Danh sach sinh viên dat loai gioi la: \n";
			for(auto& sv : dsChan){
				if(sv.gpa >= 8 ){
					check = 1;
					cout << sv;
				}
			}
			if(check == 0) cout << "Khong co sinh vien dat loai gioi!";
			
		}
		void dsLeGPAgioi(){
			int check = 0;
			cout << "Danh sach sinh viên dat loai gioi la: \n";
			for(auto& sv : dsLe){
				if(sv.gpa >= 8 ){
					check = 1;
					cout << sv;
				}
			}
			if(check == 0) cout << "Khong co sinh vien dat loai gioi!";
			
		}

};

class App{
	private:
		QuanlydanhsachdiemMSV menu;
	public:
		void Menu(){
			int luachon;
			do{
				cout << "===============MENU===============\n";
				cout << "1: Nhap thong tin sinh vien\n";
				cout << "2: In ra danh sach sinh vien\n";
				cout << "3: Sap xep sinh vien co ma sinh vien chan theo gpa\n";
				cout << "4: Sap xep sinh vien co ma sinh vien le theo gpa\n";
				cout << "5: Tim kiem sinh vien theo ma sinh vien \n";
				cout << "6: In ra danh sach sinh vien co diem dat loai gioi\n";
				cout << "7: Tim sinh vien co GPA lon nhat\n";	
				cout << "8: Tim sinh vien co gpa be nhat\n";		
				cout << "0: Ket thuc\n";
				cout << "Vui long chon cac lua chon tren!\n";
				cout << "==================================\n";
			
				cin >> luachon;

            	switch (luachon){
                	case 1:
                		cout << "Nhap ma sinh vien la -1 neu muon dung viec nhap!\n";
               	     menu.nhapdanhsach();
               	     break;
                	case 2:
                	    menu.xuatthongtin();
                	    break;
               		case 3:
               	     	menu.SapxepDiemdsChan();
                    	cout << "Danh sach sinh vien co ma chan da duoc sap xep.\n";
                    	break;
                	case 4:
                    	menu.SapxepDiemdsLe();
                    	cout << "Danh sach sinh vien co ma le da duoc sap xep.\n";
                    	break;
                	case 5:
                    	menu.TimkiemSVtheoMSV();
                    	break;
                	case 6:
                    	menu.dsChanGPAgioi();
                    	menu.dsLeGPAgioi();
                    	break;
                	case 7:
                    	menu.MaxGPA();
                    	break;
                	case 8:
                    	menu.MinGPA();
                    	break;
                	case 0:
                    	cout << "Chuong trinh ket thuc!\n";
                    	break;
                	default:
                    	cout << "Lua chon khong hop le! Vui long chon lai!\n";
                    	break;
				}
			}
			while(luachon!=0);
		}
};
int main(){
	App a;
	a.Menu();
}
