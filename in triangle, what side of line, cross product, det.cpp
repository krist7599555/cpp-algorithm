
	bool cross_product(double x1,double y1,double x2,double y2,double x3,double y3){ // == det
		return (x1-x3)*(y2-y3)  < (x2-x3)*(y1-y3); // cross product
	};


	double x[3],y[3];
	
	bool isIn(double _x,double _y){
		bool temp[3];
		for(int i=0;i<3;i++)
			temp[i] = cross_product (_x,_y, x[i],y[i], x[(i+1)%3],y[(i+1)%3]);
		return count(temp,temp+3,temp[0]) == 3;
	}
};
