class OneArray
{
	int add(int x, int y)
	{
		return x+y;
	}

	int add(int x, int y, int z)
	{
		return x+y+z;
	}
	
	double add(double x, double y)
	{
		return x+y;
	}
	
	public static void main(String[] args)
	{
	
		int[] x = new int[3]; 
		int[] y = x;
		y[0] = 66;
		x[0] = 88;
		
		x = null;
		
		System.out.println(y[0]);

        long ll = 90802;
        ll = ll / 337;
        System.out.println(ll);
	
		/*for(int x=0; x<5; x++)
		{
			for(int y=x; y<5; y++)
			{
				System.out.print("-");
			}
			for(int z=0; z<=x; z++)
			{
				System.out.print("* ");
			}
			System.out.println();
		}*/
	}
}
