// usamos 128 porque es 2^n
#include <iostream>

using namespace std;
void disp_binary(int num){
	for(int i=128;i>0;i=i/2){
		if (num & i) {
			cout << "* ";
		} else {
			cout << "- ";
		}
	}
	cout << "\n";
}

int main(){
	int num= 54;
disp_binary(num);
}