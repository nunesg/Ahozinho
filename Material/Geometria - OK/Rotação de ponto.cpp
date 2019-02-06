//angulo deve estar em radiano
pv rotacionaHorario(pv p, double rad)
{
	rad=-rad;
	return pv(p.x * cos(rad) - p.y * sin(rad), p.x * sin(rad) + p.y * cos(rad));
}

pv rotacionaAntiHorario(pv p, double rad)
{
	return pv(p.x * cos(rad) - p.y * sin(rad), p.x * sin(rad) + p.y * cos(rad));
}

int main()
{
	//le o ponto
	//chama a funcao pra rotacionar
	return 0;
}
