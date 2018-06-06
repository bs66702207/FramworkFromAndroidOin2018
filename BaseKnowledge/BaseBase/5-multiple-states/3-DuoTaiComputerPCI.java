/*class MainBoard
{
	public void run()
	{
		System.out.println("mainboard run");
	}
	public void useNetCard(NetCard c)
	{
		c.open();
		c.close();
	}
}

class NetCard
{
	public void open()
	{
		System.out.println("netcard open");
	}
	public void close()
	{
		System.out.println("netcard close");
	}
}*/
interface PCI
{
	public abstract void open();
	public abstract void close();
}

class MainBoard
{
	public void run()
	{
		System.out.println("mainboard run");
	}
	public void usePCI(PCI p)
	{
		if(p == null) {
			System.out.println("no devices");
			return;
		}
		p.open();
		p.close();
	}
}

class NetCard implements PCI
{
	public void open()
	{
		System.out.println("netcard open");
	}
	public void close()
	{
		System.out.println("netcard close");
	}
}

class SoundCard implements PCI
{
	public void open()
	{
		System.out.println("SoundCard open");
	}
	public void close()
	{
		System.out.println("SoundCard close");
	}
}

class DuoTaiComputerPCI
{
	public static void main(String[] args)
	{
		MainBoard mb = new MainBoard();
		mb.run();
		mb.usePCI(null);
		mb.usePCI(new NetCard());
		mb.usePCI(new SoundCard());
	}
}
