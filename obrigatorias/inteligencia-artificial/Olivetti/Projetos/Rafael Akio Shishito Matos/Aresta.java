import java.awt.Graphics;

public class Aresta {
	Vertice v1,v2;
	double peso;
	
	public Aresta(Vertice v1, Vertice v2) {
		this.v1 = v1;
		this.v2 = v2;
		calculaPeso();
	}
	
	public void calculaPeso() {
		peso = Math.sqrt(Math.pow(v2.x - v1.x, 2) + Math.pow(v2.y - v1.y, 2));
	}
	
	public void drawAresta(Graphics g) {
		g.drawLine(v1.x + Vertice.raio, v1.y + Vertice.raio, v2.x + Vertice.raio, v2.y + Vertice.raio);
	}
}
