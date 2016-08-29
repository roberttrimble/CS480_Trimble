import javax.swing.*;
import java.awt.*;
import java.awt.event.*;



public class ColorAssignment extends JFrame {
	
	public static void main (String argv[])
	{
		new ColorAssignment("Color Assignment");
	}
	
	
	public ColorAssignment(String title) 
	{
		super(title);		// call constructor of base class
		setBounds(100, 100, 250,100);
		getContentPane().setLayout(new FlowLayout());
		//Set components
		//
		JPanel ColorBox = new JPanel();
		JList SList = new JList();
		JLabel RedLabel = new JLabel();
		JLabel GreenLabel = new JLabel();
		JLabel BlueLabel = new JLabel();
		JTextField RedVal = new JTextField();
		JTextField GreenVal = new JTextField();
		JTextField BlueVal = new JTextField();
		
		
		
		
		//Set window grid
		
		
		
		
	}
	
	private class WindowDestroyer extends WindowAdapter 
	{      
		// implement only the function that you want
		public void windowClosing(WindowEvent e) 
		{    
			System.exit(0);  
		}                                                             
	}                                                              

}
