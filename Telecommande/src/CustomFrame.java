import javax.swing.*;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.event.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class CustomFrame extends JFrame
{
	 private static final long serialVersionUID = 1L;
	 private JTextArea textArea1, textArea2;
	 private JPanel centralPane;
	 private JMenuBar menuBar;
	 private Client client;
	 
	 public CustomFrame(Client c)
	 {
		 super("Telecommande");
		 
		 client = c;
		 
	     WindowListener l = new WindowAdapter()
	     {
	        public void windowClosing(WindowEvent e){
	           System.exit(0);
	        }
	     };
	     addWindowListener(l);
	     
	     textArea2 = new JTextArea(20,80);
	     textArea2.setEditable(false);
	     textArea2.setBackground(new Color(200,200,200));
	     JScrollPane scrollPane = new JScrollPane(textArea2);
	     
	     textArea1 = new JTextArea(3,80);
	     textArea1.setText("Enter the name of the object here (on this line)");
	     textArea1.getInputMap().put(KeyStroke.getKeyStroke("ENTER"),new NetworkAction("search",textArea2));
	     
	     
	     centralPane = new JPanel();
	     centralPane.setLayout(new BoxLayout(centralPane, BoxLayout.Y_AXIS));
	     centralPane.add(textArea1);
	     centralPane.add(scrollPane);
	     
	     Action quitAction = new QuitAction("Exit", "Quit application", new Integer(KeyEvent.VK_ESCAPE));
	     
	     JPanel pannel = new JPanel(); 
	     JButton button1 = new JButton(new NetworkAction("search",textArea2));
	     button1.setText("Search");
	     pannel.add(button1);
	     JButton button2 = new JButton(new NetworkAction("print",textArea2));
	     button2.setText("Print");
	     pannel.add(button2);
	     JButton button3 = new JButton(new NetworkAction("play",textArea2));
	     button3.setText("Play");
	     pannel.add(button3);
	     JButton button4 = new JButton(new NetworkAction("delete",textArea2));
	     button4.setText("Delete");
	     pannel.add(button4);
	     JButton button5 = new JButton(quitAction);
	     pannel.add(button5);
	     
	     
	     //Impossible de copier des boutons simplement, donc on fait quelque chose de très sale mais obligé j'ai l'impression
	     JButton button6 = new JButton(new NetworkAction("search",textArea2));
	     button6.setText("Search");
	     JButton button7 = new JButton(new NetworkAction("print",textArea2));
	     button7.setText("Print");
	     JButton button8 = new JButton(new NetworkAction("play",textArea2));
	     button8.setText("Play");
	     JButton button9 = new JButton(new NetworkAction("delete",textArea2));
	     button9.setText("Delete");
	     JMenuItem button10 = new JMenuItem(new NetworkAction("search",textArea2));
	     button10.setText("Search");
	     JMenuItem button11 = new JMenuItem(new NetworkAction("print",textArea2));
	     button11.setText("Print");
	     JMenuItem button12 = new JMenuItem(new NetworkAction("play",textArea2));
	     button12.setText("Play");
	     JMenuItem button13 = new JMenuItem(new NetworkAction("delete",textArea2));
	     button13.setText("Delete");

	     
	     JToolBar toolBar = new JToolBar();
	     toolBar.add(button6);
	     toolBar.add(button7);
	     toolBar.add(button8);
	     toolBar.add(button9);
	     toolBar.add(new JButton(quitAction));
	     
	     add(toolBar, BorderLayout.NORTH);
	     add(centralPane, BorderLayout.CENTER);
	     add(pannel, BorderLayout.SOUTH);
	     
	     
	     menuBar = new JMenuBar();
	     JMenu menu = new JMenu("Main menu");
	     menu.setMnemonic(KeyEvent.VK_M);
	     menuBar.add(menu);
	     
	    
	     menu.add(button10);
	     menu.add(button11);
	     menu.add(button12);
	     menu.add(button13);
	     
	     menu.addSeparator();
	     
	     menu.add(new JMenuItem(quitAction));
		
	     setJMenuBar(menuBar);
	  }
	 
	 class NetworkAction extends AbstractAction
	 {
		private static final long serialVersionUID = 1L;
		String prefix;
		 JTextArea textArea;
		 
		 public NetworkAction(String prefix, JTextArea area) {
			 this.prefix = prefix;
			 textArea = area;
		 }
		 
		 public void actionPerformed(ActionEvent arg0) {
			String toSend = textArea1.getText().split("\n")[0]; //on ne récupère que la seconde ligne du textInput
			String response = client.send(prefix+" "+toSend);
			parseResponse(response);
		 }
		 
		 //On parse la réponse obtenue et on rajoute les lignes nécessaires au textArea qui permet d'afficher ce qui s'est passé
		 public void parseResponse(String str)
		 {
			Pattern p = Pattern.compile("NOK internalError");
			Matcher m = p.matcher(str);
	        
			if(m.matches())
				textArea.append("Operation failed : internal server error (should not happen)\n");
			else
			{
				p = Pattern.compile("NOK badCommand");
				m = p.matcher(str);
				if(m.matches())
					textArea.append("Operation failed : bad command (should not happen)\n");
				else
				{
					p = Pattern.compile("OK noResourceFound");
					m = p.matcher(str);
					if(m.matches())
						textArea.append("Operation mixed : no such resource found\n");
					else
					{
						p = Pattern.compile("OK destructionNOK");
						m = p.matcher(str);
						if(m.matches())
							textArea.append("Operation mixed : the resource has not been deleted because it doesn't exist\n");
						else
						{
							p = Pattern.compile("OK destructionOK");
							m = p.matcher(str);
							if(m.matches())
								textArea.append("Operation succes : the resource has been removed from the list\n");
							else
							{
								p = Pattern.compile("OK resourcePlayed");
								m = p.matcher(str);
								if(m.matches())
									textArea.append("Operation succes : the resource has been played on the server\n");
								else
								{
									p = Pattern.compile("OK resourceFound");
									m = p.matcher(str);
									if(m.matches())
										textArea.append("Operation succes : the resource has been found\n");
									else
									{
										p = Pattern.compile("OK resourcePrinted (.*)");
										m = p.matcher(str);
										if(m.matches())
										{
											String toWorkOn = m.group(1);
											for(int i=0;i<toWorkOn.length();i++)
												if(toWorkOn.charAt(i)==1)
													textArea.append("\n");
												else
													textArea.append(String.valueOf(toWorkOn.charAt(i)));
											textArea.append("\n");
										}
										else
											textArea.append("Operation has no correct output : "+str+"\n");
									}
								}
							}
						}
					}
				}
			}
		 }
	 }
}