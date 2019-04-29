
class IndexOutOfBoundsException
{

	private static final String[] PWR_MODE_NAME = new String[] { "OFF", "ACC", "ON" };

	public static void main(String[] args) {
		try {
			System.out.println(PWR_MODE_NAME[2]);
			System.out.println(PWR_MODE_NAME[-1]);
		} catch (ArrayIndexOutOfBoundsException e) {
			e.printStackTrace();
		}
		System.out.println(PWR_MODE_NAME[1]);
	}
}
