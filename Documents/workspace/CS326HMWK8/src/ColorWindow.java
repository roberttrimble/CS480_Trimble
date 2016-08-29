import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.JList;
import java.awt.Color;
import javax.swing.JPanel;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JTextField;
import javax.swing.AbstractListModel;
import java.awt.*;
import java.io.*;
import java.util.Scanner;

public class ColorWindow {

	private JFrame frame;
	private JTextField textField;
	private JTextField textField_1;
	private JTextField textField_2;
	
	final File fileIn = new File("ColorFile.txt")  ;   
	colorWindow[] colorList;
	
	class colorWindow
    {
        String name;
        int red, green, blue;
        
        public colorWindow( String[] line )
        {
            name = line[0];
            red = Integer.parseInt( line[1] );
            green = Integer.parseInt( line[2] );
            blue = Integer.parseInt( line[3] );
        }
        
        public colorWindow( colorWindow copy )
        {
            name = copy.name;
            red = copy.red;
            green = copy.green;
            blue = copy.blue;
        }
    }

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					ColorWindow window = new ColorWindow();
					window.frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Create the application.
	 */
	public ColorWindow() {
		initialize();
		//s.setTitle("Color Window");
		colorList = new colorWindow[11];
		//readFromFile();
	}

	/**
	 * Initialize the contents of the frame.
	 */
	private void initialize() {
		frame = new JFrame();
		frame.setBounds(100, 100, 477, 391);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.getContentPane().setLayout(null);
		
		JList list = new JList();
		list.setBounds(412, 328, -103, -299);
		list.setForeground(Color.WHITE);
		list.setBackground(Color.WHITE);
		frame.getContentPane().add(list);
		
		JList list_1 = new JList();
		list_1.setModel(new AbstractListModel() {
			String[] values = new String[] {"Red", "Green", "Blue", "Yellow", "Cyan", "Magenta", "Orange", "Pink", "Grey", "Black", "White"};
			public int getSize() {
				return values.length;
			}
			public Object getElementAt(int index) {
				return values[index];
			}
		});
		list_1.setBounds(302, 11, 149, 331);
		frame.getContentPane().add(list_1);
		
		JPanel panel = new JPanel();
		panel.setBackground(Color.YELLOW);
		panel.setBounds(10, 11, 282, 151);
		frame.getContentPane().add(panel);
		
		JButton btnSave = new JButton("Save");
		btnSave.setBounds(38, 319, 89, 23);
		frame.getContentPane().add(btnSave);
		
		JButton btnReset = new JButton("Reset");
		btnReset.setBounds(137, 319, 89, 23);
		frame.getContentPane().add(btnReset);
		
		JLabel lblRed = new JLabel("Red:");
		lblRed.setBounds(10, 173, 60, 30);
		frame.getContentPane().add(lblRed);
		
		JLabel lblGreen = new JLabel("Green:");
		lblGreen.setBounds(10, 214, 60, 30);
		frame.getContentPane().add(lblGreen);
		
		JLabel lblBlue = new JLabel("Blue:");
		lblBlue.setBounds(10, 255, 60, 30);
		frame.getContentPane().add(lblBlue);
		
		textField = new JTextField();
		textField.setBounds(48, 214, 60, 30);
		frame.getContentPane().add(textField);
		textField.setColumns(10);
		
		textField_1 = new JTextField();
		textField_1.setColumns(10);
		textField_1.setBounds(48, 173, 60, 30);
		frame.getContentPane().add(textField_1);
		
		textField_2 = new JTextField();
		textField_2.setColumns(10);
		textField_2.setBounds(48, 255, 60, 30);
		frame.getContentPane().add(textField_2);
		
		JButton button = new JButton("-");
		button.setBounds(118, 218, 70, 23);
		frame.getContentPane().add(button);
		
		JButton button_1 = new JButton("-");
		button_1.setBounds(118, 177, 70, 23);
		frame.getContentPane().add(button_1);
		
		JButton button_2 = new JButton("-");
		button_2.setBounds(118, 259, 70, 23);
		frame.getContentPane().add(button_2);
		
		JButton button_3 = new JButton("+");
		button_3.setBounds(198, 177, 70, 23);
		frame.getContentPane().add(button_3);
		
		JButton button_4 = new JButton("+");
		button_4.setBounds(198, 218, 70, 23);
		frame.getContentPane().add(button_4);
		
		JButton button_5 = new JButton("+");
		button_5.setBounds(198, 259, 70, 23);
		frame.getContentPane().add(button_5);
	}
	
}	
	
	
/*	void readFromFile()
    {
        String[] line;
        colorWindow temp;
        int i = 0;
        
        try ( Scanner s = new Scanner( fileIn ) )
        {
            while ( s.hasNextLine() )
            {
                // split each line up by tabs
                line = s.nextLine().split( "\t" );
                temp = new colorWindow( line );
                
                // add to the list
                colorList[i] = new colorWindow(temp);
                
                // increment counter
                i++;
            }
            s.close();
        } catch (FileNotFoundException ex) {}
    }
    
    void writeToFile()
    {
        try ( FileWriter fw = new FileWriter( fileIn ) )
        {
            for (int i = 0; i < 11; i++)
            {
                fw.write( colorList[i].toString() );
            }
            fw.close();
        }
        catch (IOException ex) {}
    }
	
	
	
	
	
	
	
}*/

