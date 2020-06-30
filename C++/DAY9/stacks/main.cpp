#include<iostream>
#include "stack.h"

using namespace std;

int getMaxArea(int *height, int size){
	int i = 0;
	int maxHeightIndex = 0;
	int maxWidth = 0;
	int tempArea = 0;
	int maxArea = 0;
	int n = size;
	
	Stack<int> *s = new Stack<int>();
	
	while(i < n){
		if(s->isEmpty() || height[s->top()] <= height[i]){
			s->push(i);
			i++;
		} else {
			maxHeightIndex = s->pop();
			
			if(s->isEmpty()){
				maxWidth = i;
			} else {
				maxWidth = i - s->top() - 1;
			}
		
			tempArea = height[maxHeightIndex] * maxWidth;
			if (maxArea < tempArea)
				maxArea = tempArea;
		}
	}
	
	while(!s->isEmpty()){
		maxHeightIndex = s->pop();
			
		if(s->isEmpty()){
			maxWidth = i;
		} else {
			maxWidth = i - s->top() - 1;
		}
	
		tempArea = height[maxHeightIndex] * maxWidth;
		if (maxArea < tempArea)
			maxArea = tempArea;	
	}
	delete s;
	return maxArea;
}

int main(){

	Stack<int> *s = new Stack<int>();
	int height;
	while(1){
		cout << "Enter height of sky scrapper: ";
		cin >> height;
		
		if(height == 0) break;
		
		s->push(height);
	}
	
	int size = s->size();

	int *building = new int [size];
	
	for(int i = 0; i < size; i++){
		building[i] = s->pop();
	}
	
	int maxArea = getMaxArea(building, size);
			
	cout << "Max area: " << maxArea << endl;
	
	delete building;
	delete s;	
	return 0;
}

