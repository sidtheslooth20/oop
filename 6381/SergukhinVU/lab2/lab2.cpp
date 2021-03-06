#include <iostream>
#include <cstring>
#include <string>
#include <math.h>

#define PI 3.14159265358979323846264338279502884197169399375


using namespace std;

struct Point
{
	double x;
	double y;
};

class Shape 
{
protected:
	Point Center;
	string Colour;
	int Angle;

public:
	virtual void move(double x, double y) = 0;
	virtual void scale(double coef) = 0;
	virtual void turn(int angle) = 0;
	virtual ~Shape() {};
	void chooseOption(){
		int choice=0;
		string colour;
		double x, y;
		double angle = 0;
		double coeff = 0;
		
		while(choice!=5)
		{
		cout << endl << "***********************************************************" << endl;
		cout << "Please, choose the option." << endl;
		cout << "1 - To move" << endl;
		cout << "2 - To turn" << endl;
		cout << "3 - To scale" << endl;
		cout << "4 - Change color" << endl;
		cout << "5 - Exit" << endl;
		cout << "***********************************************************" << endl << endl ;
		cin.clear(); 
		cin >> choice;
		
		switch (choice){
			case 1:
				cout << "Enter new (x;y) of the center: " << endl;
				cin >> x >> y;
				this->move(x,y);
				//Circle c(0,0,1);
				cout << *this;
				
				break;
			case 2:
				cout << "Enter the angle of rotation: " << endl;
				cin >> angle;
				this->turn(angle);
				cout << *this;
		
				break;
			case 3:
				cout << "Enter the scale coefficient: " << endl;
				cin >> coeff;
				this->scale(coeff);
				cout << *this;
				
				break;
			case 4:
				cout << "Enter the new colour: " << endl;
				cin >> colour;
				this->setColour(colour);
				cout << *this;
				
				break;
			case 5:
				this->~Shape();
				return;
				break;
			default:
				cout << "Use only 1 - 5 keys!" << endl;
				
		}		
		}
	}
	void setColour(string colour){
		Colour = colour;
	}
	virtual void printInfo(ostream& out) = 0; 
	friend std::ostream& operator<<(std::ostream& outStream, Shape& shape) {
		shape.printInfo(outStream);
		return outStream;
	}
};

class Ellipse :public Shape
{
	double R1;//длина первого радиуса
	double R2;//длина второго радиуса

	public:
		Ellipse(double x0, double y0, double a, double b){
			Center = {x0, y0};
			R1 = a;
			R2 = b;
			Angle = 0;
		}	

		Ellipse(double x0, double y0, double a, double b, string colour){
			Center = {x0, y0};
			R1 = a;
			R2 = b;
			Angle = 0;
			Colour = colour;
		}

		void printInfo(ostream& out){
			out << "Shape: Ellipse" << endl;
			out << "Colour: " << Colour<< endl;
			out << "Center: " << "(" << Center.x << ";" << Center.y << ")" << endl;
			out << "First radius: " << R1 << endl;
			out << "Second radius: " << R2 << endl;
			out << "Angle of rotation: "<< Angle << endl;
	    	
		}
		void move(double x, double y) {
			Center.x =  x; 
			Center.y =  y;

		}
		void turn(int angle) {
			if (Angle == 0)
				Angle = angle % 360;
		
			else
				Angle = (Angle + (angle % 360)) % 360;
		}
		
	
		void scale(double coeff) {
			R1 = R1 * coeff;
			R2 = R2 * coeff;	
		}
		~Ellipse() = default;

};

class Trapeze: public Shape
{
protected:
	Point RightTop;
	Point RightBottom;
	Point LeftTop;
	Point LeftBottom;
	double dif1;
	double dif2;
	double height;
	double lenght;
	double dia;// = sqrt(pow(halfA,2)+pow(halfB,2));
	double corner;// = atan(((b/2)/(a/2)));//*180/PI);
	
public:
	Trapeze(double a, double b, double h, int ang, string colour){
		Center = {0 , 0};
		Colour = colour;
		Angle = 0;
		LeftBottom = {-a/2 , -h/2};
		RightBottom = {a/2 , -h/2};
		if (ang == 90){
			LeftTop = {-a/2 , h/2};
			dif1 = 0;
		}
		else{
			LeftTop = {LeftBottom.x + h/tan(ang*PI/180) , h/2};
			dif1 = h/tan(ang*PI/180);
		}
		RightTop = {LeftTop.x + b , h/2};
		dif2 = a/2 - RightTop.x;
		height = h;
		lenght = a; 
		dia = sqrt(pow((lenght/2),2)+pow((height/2),2));
		corner = atan((b/2)/(a/2)) / PI * 180;
		
	}
	void move(double x, double y) {
		double diffX, diffY;
		diffX = Center.x - x;
		diffY = Center.y - y;
		Center = {x, y};
		RightTop = {RightTop.x - diffX, RightTop.y - diffY};
		RightBottom = {RightBottom.x - diffX, RightBottom.y - diffY};
		LeftTop = {LeftTop.x - diffX, LeftTop.y - diffY};
		LeftBottom = {LeftBottom.x - diffX, LeftBottom.y - diffY};
	}
	void turn(int angle){
		double s = 0;
		if (Angle== 0){
			Angle= angle % 360;
		}
		else{
			Angle= (Angle+ (angle % 360)) % 360;
		}
		RightTop = 	{round((Center.x + dia*cos((Angle+ corner)*PI/180) - dif2*cos(Angle* PI / 180))*10)/10, 
					 round((Center.y + dia*sin((Angle+ corner)*PI/180) - dif2*sin(Angle* PI / 180))*10)/10};
		RightBottom = 	{round((Center.x + dia*cos((Angle- corner)*PI/180))*10)/10, 
					 round((Center.y - dia*sin((-Angle+ corner)*PI/180))*10)/10};
		LeftTop = 	{round((Center.x - dia*cos((Angle- corner)*PI/180) + dif1*cos(Angle* PI / 180))*10)/10, 
					 round((Center.y + dia*sin((-Angle+ corner)*PI/180) + dif1*sin(Angle* PI / 180))*10)/10};
		LeftBottom = 	{round((Center.x - dia*cos((Angle+ corner)*PI/180))*10)/10, 
					 round((Center.y - dia*sin((Angle+ corner)*PI/180))*10)/10};
	}
	void scale(double coeff){
		dia *= coeff;
		dif1 *= coeff;
		dif2 *= coeff;
		RightTop = 	{round((Center.x + dia*cos((Angle+ corner)*PI/180) - dif2*cos(Angle* PI / 180))*10)/10, 
					 round((Center.y + dia*sin((Angle+ corner)*PI/180) - dif2*sin(Angle* PI / 180))*10)/10};
		RightBottom = 	{round((Center.x + dia*cos((Angle- corner)*PI/180))*10)/10, 
					 round((Center.y - dia*sin((-Angle+ corner)*PI/180))*10)/10};
		LeftTop = 	{round((Center.x - dia*cos((Angle- corner)*PI/180) + dif1*cos(Angle* PI / 180))*10)/10, 
					 round((Center.y + dia*sin((-Angle+ corner)*PI/180) + dif1*sin(Angle* PI / 180))*10)/10};
		LeftBottom = 	{round((Center.x - dia*cos((Angle+ corner)*PI/180))*10)/10, 
					 round((Center.y - dia*sin((Angle+ corner)*PI/180))*10)/10};
	}
	void printInfo(ostream& out){
		out << "Shape: Trapeze" << endl;
		out << "Colour: " << Colour << endl;
		out << "Center: " << "(" << Center.x << ";" << Center.y << ")" << endl;
    	out << "Right top: " << "(" << RightTop.x << ";" << RightTop.y << ")" << endl;
    	out << "Right bottom: " << "(" << RightBottom.x << ";" << RightBottom.y << ")" << endl;
    	out << "Left top: " << "(" << LeftTop.x << ";" << LeftTop.y << ")" << endl;
    	out << "Left bottom: " << "(" << LeftBottom.x << ";" << LeftBottom.y << ")" << endl;
    	out << "Angle of rotation: "<< Angle << endl;
    	 
	}
	~Trapeze() = default;
};

class IsoscelesTrapeze : public Trapeze 
{
	public:
	IsoscelesTrapeze(double a, double b, double h, string colour) :Trapeze( a,  b,  h,  int( atan( h/((a-b)/2) ) / PI * 180) , colour){};

	void printInfo(ostream& out)
	{
		out << "Shape: Isosceles Trapeze" << endl;
		out << "Colour: " << Colour << endl;
		out << "Center: " << "(" << Center.x << ";" << Center.y << ")" << endl;
    	out << "Right top: " << "(" << RightTop.x << ";" << RightTop.y << ")" << endl;
    	out << "Right bottom: " << "(" << RightBottom.x << ";" << RightBottom.y << ")" << endl;
    	out << "Left top: " << "(" << LeftTop.x << ";" << LeftTop.y << ")" << endl;
    	out << "Left bottom: " << "(" << LeftBottom.x << ";" << LeftBottom.y << ")" << endl;
    	out << "Angle of rotation: "<< Angle << endl;
    	 
	}

};

void chooseShape();

int main(){
	chooseShape();
	return 0;
}

void chooseShape(){
	int choice=0;
	while(choice!=4)
	{
	cout << endl << "***********************************************************" <<endl;
	cout << "Please, select the shape." << endl;
	cout << "1 - Ellipse" << endl;
	cout << "2 - Trapeze" << endl;
	cout << "3 - Isosceles Trapeze" << endl;
	cout << "4 - Exit" << endl;
	cout << "***********************************************************" << endl <<endl;
	cin.clear();
	cin >> choice;
	fflush(stdin);

	switch (choice){
		case 1:{
			Ellipse e(0,1,2,3,"White");
			cout << e;
			e.chooseOption();
			break;	
		}
		case 2:{
			Trapeze t(2,1,1,90,"Blue");
			cout << t;
			t.chooseOption();
			break;	
		}
		case 3:{
			IsoscelesTrapeze it(2,1,1,"Red");
			cout << it;
			it.chooseOption();
			break;
		}
		case 4:
			return;
			break;
		default:
		cout << "Please, use 1-4 keys" << endl;
	}
	}
}