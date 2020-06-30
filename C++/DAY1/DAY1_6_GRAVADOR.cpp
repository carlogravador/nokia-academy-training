//power of 7

#include<iostream>


using std::cout;
using std::cin;
using std::endl;



int main(void){


	int input;
	
	/*	A P1
		(x1, y1)_________________
			\		\
			\     (x1, y1)	\
			\	B P1	\(p4)
			\	--------*--------
			\	\	\	\
			\_______\_______\	\
			   (p1)	*	(x4,y4) \
				\	A P4	\
				\		\
				\_______________\
						B P4
						(x4, y4)
	*/				

	//coords for rectangle A
	int rectA_x1, rectA_y1;		//P1 - RectA
	int rectA_x4, rectA_y4;		//P4 - RectA

	//coords for rectangle A
	int rectB_x1, rectB_y1;		//P1 - RectB
	int rectB_x4, rectB_y4;		//P4 - RectB
	
	//new rect coords if intersect
	int ix1 = 0, iy1 = 0;		//P1 - new rect
	int ix4 = 0, iy4 = 0;		//P4 - new rect
	
	int area;
	int length, width;
	
	int is_disjoint = 0;
	


	while(1){
		//DO YOUR WORK HERE
		
		is_disjoint = 0;
		
		cout << "INPUT x1 for the first rectangle: ";
		cin >> rectA_x1;
		cout << "INPUT y1 for the first rectangle: ";
		cin >> rectA_y1;
		
		cout << "INPUT x4 for the first rectangle: ";
		cin >> rectA_x4;
		cout << "INPUT y4 for the first rectangle: ";
		cin >> rectA_y4;
		
		cout << "INPUT x1 for the first rectangle: ";
		cin >> rectB_x1;
		cout << "INPUT y1 for the first rectangle: ";
		cin >> rectB_y1;
		
		cout << "INPUT x4 for the first rectangle: ";
		cin >> rectB_x4;
		cout << "INPUT y4 for the first rectangle: ";
		cin >> rectB_y4;
		
		
		//for Px1 of new rect
		if((rectA_x1 <= rectB_x1) && (rectA_x4 >= rectB_x1 )) {		
			ix1 = rectB_x1;
		} else if ((rectB_x1 <= rectA_x1) && (rectB_x4 >= rectA_x1)) {
			ix1 = rectA_x1;
		} else {
			is_disjoint = 1;
		}
		//for Py1
		if((rectB_y1 >= rectA_y4) && (rectB_y4 <= rectA_y4)){
			iy1 = rectA_y4;
		} else if((rectA_y1 >= rectB_y4) && (rectA_y4 <= rectB_y4)) {
			iy1 = rectB_y4;
		} else {
			is_disjoint = 1;
		}

		//for Px4
		if((rectB_x1 <= rectA_x4) && (rectB_x4 >= rectA_x4)){
			ix4 = rectA_x4;
		} else if((rectA_x1 <= rectB_x4) && (rectA_x4 >= rectB_x4)) {
			ix4 = rectB_x4;
		} else {
			is_disjoint = 1;
		}
		//for Py4,
		if((rectA_y1 >= rectB_y1) && (rectA_y4 <= rectB_y1 )) {
			iy4 = rectB_y1;
		} else if ((rectB_y1 >= rectA_y1) && (rectB_y4 <= rectA_y1)) {
			iy4 = rectA_y1;
		} else {
			is_disjoint = 1;
		}
			
		if(is_disjoint) {
			cout << "There is no intersection\n";
			continue;
		}
			
		//SOLVE
				
		cout << ix4 << " - " << ix1 << endl;
		width = ix4 - ix1;
		cout << iy4 << " - " << iy1 << endl;
		length = iy4 - iy1;
			
		cout << "WIDTH: " << width << endl;
		cout << "HEIGHT: " << length << endl;
			
		area = length * width;
		cout << "The area of the intersection of a rectangle is " << area << endl;
		
		//Again?
		cout << "Input -1 to exit: ";
		cin >> input;
		if(input == -1){
			break;
		}
	}
	
	cout << "The program will exit\n";
	

	return 0;
}
