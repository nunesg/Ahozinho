//calcula o perimetro de um poligono       
ld perimetro(vector<pv> &polygon){
	if((int)polygon.size()<=1) return 0.0;
	
	if(!(polygon[0] == polygon[(int)polygon.size()-1]))
		polygon.pb(polygon[0]);
	
	ld ans = 0.0;
	for (int i = 0; i < (int)polygon.size()-1; i++)
	{
		ans += distPt(polygon[i], polygon[i+1]);
	}
	return ans;
}

//calcula a area de um poligono    
ld area(vector<pv> &polygon){
	if((int)polygon.size()<=2) return 0.0;
	
	if(!(polygon[0] == polygon[(int)polygon.size()-1]))
		polygon.pb(polygon[0]);
	
	ld ans = 0.0;
	for (int i = 0; i < (int)polygon.size()-1; i++)
	{
		ans += cross(polygon[i], polygon[i+1]);
	}
	return fabs(ans)*0.5;
}

//gera a convex hull do vector pt    
void convexHull(vector<pv> &polygon){
	if((int)polygon.size() <= 2) return;
	pv p1[(int)polygon.size() + 2];
	pv p2[(int)polygon.size() + 2];
	int sz1 = 0, sz2 = 0;
	
	sort(polygon.begin(), polygon.end(), compareConvexHull);
	for (int i = 0; i < (int)polygon.size(); i++)
	{
		while (sz1 > 1 && ccw(p1[sz1-2], p1[sz1-1], polygon[i]))
		{
			sz1--;
		}
		p1[sz1++] = polygon[i];
		
		while (sz2 > 1 && !ccw(p2[sz2-2], p2[sz2-1], polygon[i]))
		{
			sz2--;
		}
		p2[sz2++] = polygon[i];
	}
	
	polygon.clear();
	for (int i = 0; i < sz1; i++)
	{
		polygon.pb(p1[i]);
	}
	
	for (int i = sz2-2; i >= 1; i--)
	{
		polygon.pb(p2[i]);
	}
}


//checar se ponto esta dentro de poligono em O(n) - comparação de ângulo    
bool insidePolygon(pv p, vector<pv> &polygon){
	if((int)polygon.size()<= 2) return false;
	
	if(!(polygon[0] == polygon[(int)polygon.size()-1])){
		polygon.pb(polygon[0]);
	}
	bool naBorda = false;
	
	ld ang = 0.0;
	for (int i = 0; i < polygon.size()-1; i++)
	{
		naBorda = naBorda || onSegment(p, seg(polygon[i], polygon[i+1]));
		if(ccw(p, polygon[i], polygon[i+1])){
			ang += angle2Vec(polygon[i] - p, polygon[i+1]-p);
		}else{
			ang -= angle2Vec(polygon[i] - p, polygon[i+1]-p);
		}
	}
	return igual(fabs(ang), 2.0*PI) || naBorda;//se quiser totalmente dentro tem que ver se ele ta na borda
}


//checa se um ponto esta dentro de um triangulo (a, b, c)   
bool insideTriangle(pv p, pv a, pv b, pv c){
	if(onSegment(p, seg(a, b))) return true;
	if(onSegment(p, seg(a, c))) return true;
	if(onSegment(p, seg(b, c))) return true;
	
	return sinal(cross(b-a, p-a)) == sinal(cross(c-b, p-b)) && sinal(cross(c-b, p-b)) == sinal(cross(a-c, p-c));
}

//checa se um ponto esta dentro de um polígono em O(log n)   
bool insidePolygonLogN(pv p, vector<pv> &polygon){//NAO PODE TER PONTOS COLINEARES
	//CUIDADO COM POLIGONOS DEGENERADOS
	if((int)polygon.size() == 0) return false;
	
	int sz;
	if(polygon[0] == polygon[(int)polygon.size()-1]) sz = (int)polygon.size()-1;
	else sz = (int)polygon.size();
	
	if(sz <= 2) return false;
	
	if(ccw(polygon[0], polygon[1], polygon[2])){
		if(!(polygon[0] == polygon[(int)polygon.size()-1])) polygon.pb(polygon[0]);
		reverse(polygon.begin(), polygon.end());
	}
	
	int lo = 1, hi = sz-1, mid;
	int c;
	while (lo <= hi)
	{
		mid = (lo + hi)/2;
		c = sinal(cross(polygon[mid] - polygon[0], p - polygon[0]));
		if(c < 0){
			lo = mid+1;
		}else if(c > 0){
			hi = mid-1;
		}else{
			if(mid == 1){
				return insideTriangle(p, polygon[0], polygon[mid], polygon[mid+1]);
			}else{
				return insideTriangle(p, polygon[0], polygon[mid-1], polygon[mid]);
			}
		}
	}
	mid = (lo+hi)/2;
	if(mid == 0 || mid == sz-1) return false;
	
	return insideTriangle(p, polygon[0], polygon[mid], polygon[mid+1]);
}

bool insidePolygonLogNConfiavel(pv p, vector<pv>& polygon){
	vector<pv> lower, upper;
	convexHull(polygon, lower, upper);//PRECISA QUE A CONVEX HULL RETORNE A LOWER E UPPER HULL
	ld xMax, xMin, yMax, yMin;
	ld up1, up2, dw1, dw2;
	
	
	xMax = upper[(int)upper.size()-1].x;
	xMin = upper[0].x;
	
	for (int i = 0; i < (int)upper.size(); i++)
	{
		yMax = max(yMax, upper[i].y);
		yMin = min(yMin, upper[i].y);
		if(upper[i].x == xMin){
			up1 = max(up1, upper[i].y);
			dw1 = min(dw1, upper[i].y);
		}
		if(upper[i].x == xMax){
			up2 = max(up2, upper[i].y);
			dw2 = min(dw2, upper[i].y);
		}
	}
	for (int i = 0; i < (int)lower.size(); i++)
	{
		yMax = max(yMax, lower[i].y);
		yMin = min(yMin, lower[i].y);
		if(upper[i].x == xMin){
			up1 = max(up1, lower[i].y);
			dw1 = min(dw1, lower[i].y);
		}
		if(upper[i].x == xMax){
			up2 = max(up2, lower[i].y);
			dw2 = min(dw2, lower[i].y);
		}
	}
	if(p.x < xMin || p.x > xMax || p.y < yMin || p.y > yMax) return false;
	
	if(p.x == xMin && (p.y < dw1 || p.y > up1)) return false;
	if(p.x == xMax && (p.y < dw2 || p.y > up2)) return false;
	
	//nesse momento, o ponto tem x > xMin e x < xMax
	int lo = 0, hi = (int)upper.size()-1;
	int mid;
	int ans1, ans2;
	while (lo <= hi)
	{
		mid = (lo+hi)/2;
		if(p.x >= upper[mid].x && p.x <= upper[mid+1].x){
			ans1 = mid;
			break;
		}
		if(p.x < upper[mid].x){
			hi = mid-1;
		}else{
			lo = mid+1;
		}
	}
	
	lo = 0; hi = (int)lower.size()-1;
	while (lo <= hi)
	{
		mid = (lo+hi)/2;
		if(p.x >= lower[mid].x && p.x <= lower[mid+1].x){
			ans2 = mid;
			break;
		}
		if(p.x < lower[mid].x){
			hi = mid-1;
		}else{
			lo = mid+1;
		}
	}
	
	if(onSegment(p, seg(upper[ans1], upper[ans1+1]))) return true;
	if(onSegment(p, seg(lower[ans2], lower[ans2+1]))) return true;
	
	return sinal(cross(upper[ans1+1]-upper[ans1], p - upper[ans1]))==-1 && sinal(cross(lower[ans2+1] - lower[ans2], p - lower[ans2]))==1;
}


//FUNÇÃO DO JUNIOR (% significa cross)
bool PointIsInsideConvexPolygon(vector<pv> &a, pv p) {
  pv vp = p - a[0];
  if(cross((a[1] - a[0]), vp) > 0) return 0;
  int lo = 1, hi = a.size() - 1;
  while(lo < hi) {
    int md = (lo + hi + 1) >> 1;
    if(cross((a[md] - a[0]), vp) < 0) lo = md;
    else hi = md - 1;
  }
  if(hi == a.size() - 1) return false;
  return cross(((a[lo + 1] - a[lo]), (p - a[lo]))) < 0;
}

//retorna a interseccao dos poligonos 
int interPolygon(vector<pv> &polygon1, vector<pv>& polygon2, vector<pv> &interseccao){
	
	if(!(polygon1[0] == polygon1[(int)polygon1.size() - 1])) polygon1.pb(polygon1[0]);
	if(!(polygon2[0] == polygon2[(int)polygon2.size() - 1])) polygon2.pb(polygon2[0]);
	interseccao.clear();
	
	bool tem = false;
	vector<seg> segmentos;
	pv pt;
	
	for (int i = 0; i < (int)polygon1.size()-1; i++)
	{
		segmentos.pb(seg(polygon1[i], polygon1[i+1]));
	}
	for (int i = 0; i < (int)polygon2.size()-1; i++)
	{
		segmentos.pb(seg(polygon2[i], polygon2[i+1]));
	}
	
	int res;
	for (int i = 0; i < (int)segmentos.size(); i++)
	{
		for (int j = i+1; j < (int)segmentos.size(); j++)
		{
			res = interSegmento(segmentos[i], segmentos[j], pt);
			if(res == 1){
				if(insidePolygonLogN(pt, polygon1) && insidePolygonLogN(pt, polygon2)){
					interseccao.pb(pt);
					tem = true;
				}
			}else if(res == 2){
				if(onSegment(segmentos[i].a, segmentos[j])){
					pt = segmentos[i].a;
					if(insidePolygonLogN(pt, polygon1) && insidePolygonLogN(pt, polygon2)){
						interseccao.pb(pt);
						tem = true;
					}
				}
				if(onSegment(segmentos[i].b, segmentos[j])){
					pt = segmentos[i].b;
					if(insidePolygonLogN(pt, polygon1) && insidePolygonLogN(pt, polygon2)){
						interseccao.pb(pt);
						tem = true;
					}
				}
				if(onSegment(segmentos[j].a, segmentos[i])){
					pt = segmentos[j].a;
					if(insidePolygonLogN(pt, polygon1) && insidePolygonLogN(pt, polygon2)){
						interseccao.pb(pt);
						tem = true;
					}
				}
				if(onSegment(segmentos[j].b, segmentos[i])){
					pt = segmentos[j].b;
					if(insidePolygonLogN(pt, polygon1) && insidePolygonLogN(pt, polygon2)){
						interseccao.pb(pt);
						tem = true;
					}
				}
			}
		}
		
	}
	if(!tem) return false;
	
	convexHull(interseccao);
	
	return true;
}

//funcao usada na cutPolygon para não repetir vértices em um corte
void adiciona(vector<pv> &polygon, pv pt){
	if((int)polygon.size() == 0){
		polygon.pb(pt);
	}else{
		if(!(polygon[(int)polygon.size()-1] == pt))
			polygon.pb(pt);
	}
}

//NAO ACEITA PONTOS COLINEARES
//0 - não cortou ou cortou na borda
//1 - as duas partes tem area
int cutPolygon(line r, vector<pv> &polygon, vector<pv> &lp, vector<pv> &rp){
	if(!(polygon[0] == polygon[(int)polygon.size()-1])) 
		polygon.pb(polygon[0]);
	
	lp.clear();
	rp.clear();
	int lado;
	
	int cortou = 0;
	pv pt;
	for (int i = 0; i < (int)polygon.size()-1; i++)
	{
		lado = sinal(cross(r.v, polygon[i] - r.p0));
		
		//teste de ponto
		if(lado == 1){//esta à esquerda da linha
			adiciona(lp, polygon[i]);
		}else if(lado == -1){//esta à direita da linha
			adiciona(rp, polygon[i]);
		}
		
		//teste de intersecção
		if(sinal(cross(r.v, polygon[i] - r.p0)) != sinal(cross(r.v, polygon[i+1] - r.p0))){//segmento está inteiro na reta (cortou na borda)
			//nao faz nada pois os dois vertices serão adicionados na verificacao acima
			cortou = 1;
			pt = ptInterReta(line(polygon[i], polygon[i+1]-polygon[i]), r);
			adiciona(lp, pt);
			adiciona(rp, pt);
		}
	}
	if((int)lp.size() > 2) adiciona(lp, lp[0]);
	else lp.clear();
	if((int)rp.size() > 2) adiciona(rp, rp[0]);
	else rp.clear();
	return cortou;
}
