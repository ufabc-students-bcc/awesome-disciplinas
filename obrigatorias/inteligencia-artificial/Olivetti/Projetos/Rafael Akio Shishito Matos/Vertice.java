import java.awt.Color;
import java.awt.Graphics;
import java.util.ArrayList;

public class Vertice {
	static int raio = 5;
	
	int x,y;
	ArrayList<Aresta> arestas= new ArrayList<>();
	
	public Vertice(int x, int y) {
		this.x = x;
		this.y = y;
	}
	
	public void drawVertice(Graphics g) {
		g.fillOval(x, y, raio*2, raio*2);
	}
}
