import java.util.Timer;
import java.util.TimerTask;

import javax.swing.JFrame;

public class Principal {
	static Grafo grafo;
	
	static Genetico genetico;
	static int cont =0;
	
	public static void main(String[] args) {
		JFrame frame = new JFrame("ALgoritmo Genetico");
		Timer timer = new Timer();
		Tela tela = new Tela();
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setVisible(true);
		frame.setResizable(false);
		frame.add(tela);
		frame.pack();
		frame.setLocationRelativeTo(null);
		
		grafo = criarGrafo();
		
		genetico = new Genetico(grafo);
		
		timer.scheduleAtFixedRate(new TimerTask() {
			@Override
			public void run() {
				frame.repaint();
			}
		}, 1, 1000/60);
		
	}
	
	public static Grafo criarGrafo() {
		Grafo grafo = new Grafo();
		Vertice vAnt = null;
		for(int i = 0; i < 50; i++) {
			Vertice v1 = new Vertice((int) (Math.random() * Tela.largura), (int) (Math.random() * Tela.altura));
			grafo.adicionarVertice(v1);
			if(vAnt != null) {
				grafo.adicionarAresta(v1, vAnt);
			}
			vAnt = v1;
		}
		
		grafo.gerarArestasAleatorias();
		
		return grafo;
	}
}