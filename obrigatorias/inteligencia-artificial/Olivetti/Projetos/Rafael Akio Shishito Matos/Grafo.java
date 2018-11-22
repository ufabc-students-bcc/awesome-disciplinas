import java.awt.Color;
import java.awt.Graphics;
import java.util.ArrayList;

public class Grafo {
	ArrayList<Vertice> V = new ArrayList<>();
	ArrayList<Aresta> E = new ArrayList<>();
	
	public void adicionarVertice(int x, int y) {
		V.add(new Vertice(x, y));
	}
	
	public void adicionarVertice(Vertice v) {
		V.add(v);
	}
	
	public void adicionarAresta(Vertice v1, Vertice v2) {
		Aresta a = new Aresta(v1, v2);
		E.add(a);
		v1.arestas.add(a);
		v2.arestas.add(a);
	}
	
	public void drawGrafo(Graphics g) {
		g.setColor(Color.BLACK);
		for(Aresta e: E) {
			e.drawAresta(g);
		}
		
		g.setColor(Color.BLUE);
		for(Vertice v: V) {
			v.drawVertice(g);
		}
	}
	
	public void gerarArestasAleatorias() {
		for(int i = 0; i < V.size() * 2; i++) {
			Vertice v1 = V.get((int) (Math.random() * V.size()));
			Vertice v2 = V.get((int) (Math.random() * V.size()));
			if(v1 != v2) {
				adicionarAresta(v1, v2);
			}
		}
	}
}
