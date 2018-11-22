import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;

import javax.swing.JPanel;

public class Tela extends JPanel{
	static int largura = 500, altura = 500;
	@Override
    public Dimension getPreferredSize() {
        return new Dimension(largura, altura);
    }
	
	@Override
    public void paintComponent(Graphics g) {
		try {
			super.paintComponent(g);
			Principal.grafo.drawGrafo(g);
			Principal.genetico.drawCaminhos(g);
		}catch (Exception e) {
		}
    }
}
