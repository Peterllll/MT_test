//	
//

#include <iostream>

using std::cout;	using std::endl;

int main()
{
	cout << "/run/initialize" << endl;
	cout << "/tracking/verbose 0" << endl;
	//cout << "/gun/particle proton" << endl;
	cout << "/gun/particle e-" << endl;

	for (int i=1; i<=200; i++){
		cout << "/gun/energy " << 5*i << " keV" << endl;
		cout << "/run/beamOn 100000" << endl;
	}
	for (int i=21; i<=2000; i++){
		cout << "/gun/energy " << 50*i << " keV" << endl;
		cout << "/run/beamOn 100000" << endl;
	}
}
