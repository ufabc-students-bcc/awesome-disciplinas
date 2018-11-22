import java.awt.Color;
import java.awt.Graphics;
import java.util.ArrayList;
import java.util.Comparator;

public class Caminho implements Comparable<Caminho>, Cloneable {
	ArrayList<Aresta> caminho = new ArrayList<>();
	double distancia;
	
	public static Caminho criarCaminhoAleatorio(Vertice vInicio, Vertice vFim){
		Caminho caminho = new Caminho();
		Vertice verticeAtual = vInicio;
		caminho.distancia = 0;
		
		while(verticeAtual != vFim) {
			Aresta a = verticeAtual.arestas.get((int) (Math.random() * verticeAtual.arestas.size()));
			if(!caminho.caminho.contains(a)) {
				caminho.caminho.add(a);
				caminho.distancia += a.peso;
				
				if(a.v1 != verticeAtual) {
					verticeAtual = a.v1;
				}else {
					verticeAtual = a.v2;
				}
			} else if(caminho.caminho.containsAll(verticeAtual.arestas)) {
				caminho.distancia = 999999;
				break;
			}
		}
		
		return caminho;
	}
	
	public void gerarCaminhoAPartirDe(Vertice vInicio, Vertice vFim, int indice) {
		while(caminho.size() > indice) {
			caminho.remove(caminho.size()-1);
		}
		calcularDistancia();
		
		Vertice verticeAtual;
		if(indice == 0) {
			verticeAtual = vInicio;
		} else {
			verticeAtual = caminho.get(indice-1).v2;
		}
		
		while(verticeAtual != vFim) {
			Aresta a = verticeAtual.arestas.get((int) (Math.random() * verticeAtual.arestas.size()));
			if(!caminho.contains(a)) {
				caminho.add(a);
				distancia += a.peso;
				
				if(a.v1 != verticeAtual) {
					verticeAtual = a.v1;
				}else {
					verticeAtual = a.v2;
				}
			} else if(caminho.containsAll(verticeAtual.arestas)) {
				distancia = 999999;
				break;
			}
		}
	}
	
	public void calcularDistancia() {
		distancia = 0;
		for(Aresta a: caminho) {
			distancia += a.peso;
		}
	}
	
	public void drawCaminho(Graphics g) {
		g.setColor(Color.RED);
		for(Aresta a: caminho) {
			a.drawAresta(g);
		}
	}
	
	@Override
	public int compareTo(Caminho c) {
	 	return Double.compare(distancia, c.distancia);
	}
	
	@Override
    public Caminho clone() {
        Caminho clone = new Caminho();
        for(Aresta a: caminho) {
        	clone.caminho.add(a);
        }
        clone.distancia = distancia;
        return clone;
    }
	
	public Caminho cruzarCom(Caminho c) {
		Caminho caminhoNovo = new Caminho();
		boolean achou = false;
		Aresta ultimaAresta = null;
        for(Aresta a: caminho) {
        	if(c.caminho.contains(a)) {
        		achou = true;
        		caminhoNovo.caminho.add(a);
        		ultimaAresta = a;
        	}else if(achou) {
        		break;
        	}else {
        		caminhoNovo.caminho.add(a);
        	}
        }
        
        if(achou) {
        	int indice = c.caminho.indexOf(ultimaAresta);
        	for(int i = indice; i < c.caminho.size(); i++) {
        		Aresta a = c.caminho.get(i);
        		caminhoNovo.caminho.add(a);
        	}
        }
        caminhoNovo.calcularDistancia();
        return caminhoNovo;
    }
	 
}
