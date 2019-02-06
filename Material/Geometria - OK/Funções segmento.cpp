//checa se ponto p está no segmento s   
bool onSegment(pv p, seg s){
	pv a = s.a;
	pv b = s.b;
	if(maiorIgual(dot(p-a, b-a), 0.0) && maiorIgual(dot(p-b, a-b), 0.0) && igual(cross(p-a, p-b), 0.0)) return true;
	return false;
}

//checa se 2 segmentos se cruzam (pode ser na borda)   
bool temInterSegmento(seg r, seg s){
	pv a = r.a;
	pv b = r.b;
	pv c = s.a;
	pv d = s.b;
	
	return sinal(cross(b-a, d-a)) != sinal(cross(b-a, c-a)) && sinal(cross(d-c, a-c)) != sinal(cross(d-c, b-c));
}

//checa se tem interseccao entre segmentos (0 - nao tem, 1 - tem, 2 - paralelos (SE TOCAM MAS NAO RETORNA O PONTO) )   
int interSegmento(seg r, seg s, pv &ans){
	pv a = r.a;
	pv b = r.b;
	pv c = s.a;
	pv d = s.b;
	if(retasIguais(line(a, b-a), line(c, d-c))){
		
		if(onSegment(c, r) || onSegment(d, r) || onSegment(a, s) || onSegment(b, s)){
			return 2;
		}
		return 0;
	}
	if(temInterSegmento(r, s)){
		ans = ptInterReta(line(a, b-a), line(c, d-c));
		return 1;
	}
	return 0;
}
