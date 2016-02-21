import java.awt.event.ActionEvent;

import javax.swing.AbstractAction;


public class QuitAction extends AbstractAction
{
	private static final long serialVersionUID = 1L;

	public QuitAction(String name, String shortDescription, Integer mnemonic)
	{
		super(name);
		putValue(SHORT_DESCRIPTION, shortDescription);
		putValue(MNEMONIC_KEY, mnemonic);
	}
 
	public void actionPerformed(ActionEvent e)
	{
		System.exit(0);
	}
}