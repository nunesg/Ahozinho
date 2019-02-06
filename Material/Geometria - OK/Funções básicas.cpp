bool igual(ld a, ld b){
	return fabs(a-b) < EPS;
}

bool maior(ld a, ld b){
	return a > EPS + b;
}

bool menor(ld a, ld b){
	return a + EPS < b;
}

bool maiorIgual(ld a, ld b){
	return maior(a, b) || igual(a, b);
}

bool menorIgual(ld a, ld b){
	return menor(a, b) || igual(a, b);
}

ld cross(pv a, pv b){
	return a.x * b.y - a.y * b.x;
}

ld dot(pv a, pv b){
	return a.x * b.x + a.y * b.y;
}

ld distPt(pv a, pv b){
	return hypot(a.x-b.x, a.y-b.y);
}

//norma de um vetor
ld norma(pv a){
	return sqrt(dot(a, a));
}

//retorna a menor distancia entre um ponto e uma reta
ld distPtReta(pv pt, line r){
	
	return fabs(cross(r.v, pt - r.p0)) / norma(r.v);
	
}

//retorna a menor distancia de um ponto a um segmento
ld distPtSeg(pv pt, seg r){
	if(maiorIgual(dot(pt - r.a, r.b - r.a), 0.0) && maiorIgual(dot(pt - r.b, r.a - r.b), 0.0))
		return distPtReta(pt, line(r.a, r.b-r.a));
	
	return min(distPt(pt, r.a), distPt(pt, r.b));
}


//angulo entre a reta horizontal com y = 0 e o vetor v
ld polarAngle(pv v){
	ld x = v.x;
	ld y = v.y;
	
	ld aux = atan2(y, x);
	
	if(menor(aux, 0.0)) aux += 2.0*PI;
	
	return aux;
}

//radiano para grau   
ld toDegree(ld rad){
	return rad * 180 / PI;
}

//angulo entre dois vetores (menor angulo)     
ld angle2Vec(pv v, pv u){
	ld ang1 = polarAngle(v);
	ld ang2 = polarAngle(u);
	ld ans = 0.0;
	
	ans = min(fabs(ang1 - ang2), fabs(2.0*PI+ang1 - ang2));
	ans = min(ans, fabs(2.0*PI+ang2 - ang1));

	return ans;
}

//checa se os pontos a, b, c estão em sentido anti horário  
bool ccw(pv a, pv b, pv c){
	ld aux = cross(b-a, c-b);
	
	return maior(aux, 0.0);
}

bool colinear(pv a, pv b, pv c){
	return igual(cross(b-a, c-b), 0.0);
}

//retorna o sinal de um número 
int sinal(ld res){
	if(maior(res, 0.0)) return 1;
	if(menor(res, 0.0)) return -1;
	return 0;
}
