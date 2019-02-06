//ordena por x, se empatar por y     
bool compareConvexHull(pv a, pv b){
	if(igual(a.x, b.x)) return menor(a.y, b.y);
	return menor(a.x, b.x);
}

//função pra ordenar em relação ao angulo polar só com cross 
bool comparePolarAngle(pv a, pv b){
	if(a==b) return true;
	int q1 = a.getQuad();
	int q2 = b.getQuad();
	
	if(q1==q2){
		if(igual(cross(a, b), 0.0)) return menor(norma(a), norma(b));
		return maior(cross(a, b), 0.0);
	}
	return q1 < q2;
}
