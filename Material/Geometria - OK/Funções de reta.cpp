//checa se duas retas são paralelas       
bool retasParalelas(line r, line s){
	pv v = r.v;
	pv u = s.v;
	return igual(cross(v, u), 0.0);
}

//checa se duas retas são iguais      
bool retasIguais(line r, line s){
	pv p0 = r.p0;
	pv p1 = s.p0;
	pv v = r.v;
	pv u = s.v;
	
	return retasParalelas(r, s) && igual(cross(v, p1-p0), 0.0);
}

//retorna o ponto de interseccao de duas retas   
pv ptInterReta(line r, line s){
    pv v = r.v;
    pv u = s.v;
    
    pv p0 = r.p0;
    pv p1 = s.p0;
    
    long double t = (u.x * (p0.y - p1.y) + u.y * (p1.x - p0.x)) / cross(v, u);
    
    return pv(p0.x + (v.x * t), p0.y + (v.y * t));
}

//função que retorna a mediatriz 
line getMediatriz(pv a, pv b){
	pv vet, medio, perp;
	medio = (a+b)/2.0;
	vet = b-a;
	perp = pv(-vet.y, vet.x);
	
	return line(medio, perp);
}
