#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int main()
{
	int input;
	double v, s, a, m, k,l,t,f, sum,sum2;
	do {
		cout << "Welcome to the physics calculator. Please choose from the following:" << endl;
		cout << "1-calculate acceleration with velocity and seconds" << endl;
		cout << "2-calculate velocity with acceleration and seconds" << endl;
		cout << "3-calculate seconds with acceleration and velocity" << endl;
		cout<<endl;
        cout << "4-calculate kinetic energy with mass and velocity" << endl;
		cout << "5-calculate velocity with kinetic energy and mass" << endl;
		cout << "6-calculate mass with kinetic energy and velocity" << endl;
		cout<<endl;
		cout << "7-calculate frequency with mass, length, and tension" << endl;
		cout << "8-calculate tension with mass, length, and frequency" << endl;
		cout << "9-calculate length with mass, frequency and tension" << endl;
		cout << "10-calculate mass with length, frequency and tension" << endl;
		
		cout << "0 to quit." << endl;
		//add more options here
		cin >> input;
		switch (input) {
		case 1:
	    	cout<<"Do not put units, just the number. Then,hit enter after typing number"<<endl; 
			cout << "enter velocity"<<endl;
			cin >> v;
			cout << "enter seconds"<<endl;
			cin >> s;
			cout << "The accelearation is " << v / s << "m/s^2"<<endl;
            break;
		case 2:
		cout<<"Do not put units, just the number. Then,hit enter after typing number"<<endl;
			cout << "enter seconds" << endl;
			cin>>s;
	    	cout<<"enter acceleration"<<endl;
	    	cin>>a;
		    cout<<"The velocity is "<<a*s<<"m/s"<<endl;
	    	break;
		case 3:
		cout<<"Do not put units, just the number. Then,hit enter after typing number"<<endl;
			cout << "enter velocity" << endl;
			cin>>v;
	    	cout<<"enter acceleration"<<endl;
	    	cin>>a;
		    cout<<"The seconds is "<<v/a<<"s"<<endl;
	    	break;
		case 4:
		cout<<"Do not put units, just the number. Then,hit enter after typing number"<<endl;
			cout << "enter mass" << endl;
			cin>>m;
	    	cout<<"enter velocity"<<endl;
	    	cin>>v;
		    cout<<"The kinetic energy is "<<m/2*v*v<<"J"<<endl;
	    	break;
		case 5:
		cout<<"Do not put units, just the number. Then,hit enter after typing number"<<endl;
			cout << "enter kinetic energy" << endl;
			cin>>k;
	    	cout<<"enter mass"<<endl;
	    	cin>>m;
	    	sum=k/m/2;
		    cout<<"The velocity is "<<sum*sum<<"m/s"<<endl;
	    	break;
		case 6:
		cout<<"Do not put units, just the number. Then,hit enter after typing number"<<endl;
			cout << "enter kinetic energy" << endl;
			cin>>k;
	    	cout<<"enter velocity"<<endl;
	    	cin>>v;
		    cout<<"The mass is "<<k/v*v<<"kg"<<endl;
	    	break;
	   case 7:
            cout<<"Do not put units, just the number. Then,hit enter after typing number"<<endl;		
            cout << "enter mass" << endl;
			cin>>m;
	    	cout<<"enter length"<<endl;
	    	cin>>l;
	    	sum=m*l;
	    	cout<<"enter tension"<<endl;
	    	cin>>t;
	    	sum2=sqrt(t);
		    cout<<"The frequency is "<<sum2/sum*4<<"Hz"<<endl;
	    	break;
	   	case 8:
            cout<<"Do not put units, just the number. Then,hit enter after typing number"<<endl;		
            cout << "enter mass" << endl;
			cin>>m;
	    	cout<<"enter length"<<endl;
	    	cin>>l;
	    	sum=m*l;
	    	cout<<"enter frequency"<<endl;
	    	cin>>f;
		    cout<<"The tension is "<<sum*f*f<<"N"<<endl;
	    	break;
	   	case 9:
            cout<<"Do not put units, just the number. Then,hit enter after typing number"<<endl;		
            cout << "enter mass" << endl;
			cin>>m;
	    	cout<<"enter frequency"<<endl;
	    	cin>>f;
	    	sum=m*f*f;
	    	cout<<"enter tension"<<endl;
	    	cin>>t;
		    cout<<"The length is "<<t/sum*4<<"m"<<endl;
	    	break;
	   	case 10:
			cout<<"Do not put units, just the number. Then,hit enter after typing number"<<endl;
			cout << "Enter length" << endl;
			cin>>l;
	    	cout<<"Enter frequency"<<endl;
	    	cin>>f;
	    	sum=l*f*f;
	    	cout<<"Enter tension"<<endl;
	    	cin>>t;
		    cout<<"The mass is "<<t/sum*4<<"kg"<<endl;
	    	break;
	    	
		}//end switch
	

	} while (input != 0);

	return 0;
}