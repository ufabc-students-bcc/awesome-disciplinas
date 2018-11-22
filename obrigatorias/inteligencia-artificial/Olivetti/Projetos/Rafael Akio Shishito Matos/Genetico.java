import java.awt.BasicStroke;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Genetico{
	static Vertice vInicio, vFim;
	static int tamanhoPopulacao = 10;
	static double taxaMutacao = 0.01;
	ArrayList<Caminho> populacao = new ArrayList<>();
	Caminho melhorCaminho = null;
	double chance[];
	
	public Genetico(Grafo G) {
		chance = new double[tamanhoPopulacao];
		double chanceTorneio = 0.5;
		for(int i = 0; i < tamanhoPopulacao; i++) {
			chance[i] = chance[i]*(Math.pow(1-chance[i], i));
		}
		setVertices(G);
		criarPopulacao(G);
		evoluir();
	}
	
	public void evoluir() {
		new Thread() {
			public void run() {
				while(true) {
					selecionar();
					System.out.println("Distância do melhor caminho achado até agora: "+melhorCaminho.distancia);
					cruzar();
					mutar();
				}
			}
		}.start();
	}
	
	public void selecionar() {
		Collections.sort(populacao);
		melhorCaminho = populacao.get(0).clone();
	}
	
	public void mutar() {
		for(int i = 1; i < populacao.size(); i++) {
			Caminho caminho = populacao.get(i);
			if(Math.random() < taxaMutacao) {
				caminho.gerarCaminhoAPartirDe(vInicio, vFim, (int) (Math.random() * caminho.caminho.size()));
			}
		}
	}
	
	public void cruzar() {
		ArrayList<Caminho> populacaoNova = new ArrayList<>();
		for(int i = 0; i < tamanhoPopulacao - 1; i++) {
			Caminho individuo1 = null, individuo2 = null;
			for(int j = 0; j < tamanhoPopulacao; j++) {
				double r = Math.random();
				if(r < chance[j]) {
					individuo1 = populacao.get(j);
				} else if(j == tamanhoPopulacao -1) {
					individuo1 = populacao.get(j);
				}
			}
			
			for(int j = 0; j < tamanhoPopulacao; j++) {
				double r = Math.random();
				if(r < chance[j]) {
					individuo2 = populacao.get(j);
				} else if(j == tamanhoPopulacao -1) {
					individuo2 = populacao.get(j);
				}
			}
			populacaoNova.add(individuo1.cruzarCom(individuo2));
		}
		
		populacao.remove(populacao.size() - 1);
		populacao.add(populacao.get(0).clone());
	}
	
	
	public static void setVertices(Grafo G) {
		vInicio = G.V.get((int) (Math.random() * G.V.size()));
		do{
			vFim = G.V.get((int) (Math.random() * G.V.size()));
		}while(vInicio == vFim);
		
	}
	
	public void criarPopulacao(Grafo G) {
		for(int i = 0; i < tamanhoPopulacao; i++) {
			populacao.add(Caminho.criarCaminhoAleatorio(vInicio, vFim));
		}
	}
	
	public void drawCaminhos(Graphics g) {
		Graphics2D g2 = (Graphics2D) g;
		g2.setStroke(new BasicStroke(3));
		melhorCaminho.drawCaminho(g2);
		vInicio.drawVertice(g2);
		vFim.drawVertice(g2);
	}
}
