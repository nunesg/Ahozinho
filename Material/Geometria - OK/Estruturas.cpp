struct pv{
	ld x, y;
	pv(){}
	pv(ld _x, ld _y){
		x = _x;
		y = _y;
	}
	
	int getQuad(){
		if(maiorIgual(x, 0.0) && maiorIgual(y, 0.0)) return 1;
		if(menor(x, 0.0) && maiorIgual(y, 0.0)) return 2;
		if(menorIgual(x, 0.0) && menor(y, 0.0)) return 3;
		return 4;
	}
	
	pv operator + (pv other){
		return pv(x+other.x, y+other.y);
	}
	
	pv operator - (pv other){
		return pv(x-other.x, y-other.y);
	}
	
	pv operator * (ld k){
		return pv(x*k, y*k);
	}
	
	pv operator / (ld k){
		return pv(x/k, y/k);
	}
	
	bool operator == (pv other){
		return igual(x, other.x) && igual(y, other.y);
	}
};

struct line{
	pv p0, v;
	line(){}
	line(pv _p0, pv _v){
		p0 = _p0;
		v = _v;
	}
};

struct seg{
	pv a, b;
	seg(){}
	seg(pv _a, pv _b){
		a = _a;
		b = _b;
	}
};

struct circle{
	pv centro;
	ld r;
	circle(){}
	circle(pv _centro, ld _r){
		centro = _centro;
		r = _r;
	}
};
