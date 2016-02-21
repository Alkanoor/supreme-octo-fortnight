import javax.swing.*;

import java.awt.BorderLayout;
import java.awt.event.*;

public class CustomFrame extends JFrame
{
	 private static final long serialVersionUID = 1L;
	 private JTextArea textArea;
	 private JMenuBar menuBar;
	 
	 public CustomFrame()
	 {
		 super("Telecommande");

	     WindowListener l = new WindowAdapter()
	     {
	        public void windowClosing(WindowEvent e){
	           System.exit(0);
	        }
	     };
	     addWindowListener(l);
	     
	     textArea = new JTextArea("Center");
	     JScrollPane scrollPane = new JScrollPane(textArea);
	     
	     Action quitAction = new QuitAction("Exit", "Quit application", new Integer(KeyEvent.VK_ESCAPE));
	     
	     JPanel pannel = new JPanel(); 
	     JButton button1 = new JButton("Add1");
	     pannel.add(button1);
	     JButton button2 = new JButton("Add2");
	     pannel.add(button2);
	     JButton button3 = new JButton(quitAction);
	     pannel.add(button3);
	     
	     
	     JToolBar toolBar = new JToolBar();
	     toolBar.add(new JButton("Add1"));
	     toolBar.add(new JButton("Add2"));
	     toolBar.add(new JButton(quitAction));
	     
	     add(toolBar, BorderLayout.NORTH);
	     add(scrollPane, BorderLayout.CENTER);
	     add(pannel, BorderLayout.SOUTH);
	     
	     
	     menuBar = new JMenuBar();
	     JMenu menu = new JMenu("Main menu");
	     menu.setMnemonic(KeyEvent.VK_M);
	     menuBar.add(menu);
	     
	    
	     JMenuItem menuItem = new JMenuItem("Add1");
	     menu.add(menuItem);
			
	     menuItem = new JMenuItem("Add2");
	     menu.add(menuItem);
	     
	     menu.addSeparator();
	     
	     menuItem = new JMenuItem(quitAction);
	     menu.add(menuItem);
		
	     setJMenuBar(menuBar);
	  }
}