import java.time.Instant;
import java.time.temporal.ChronoUnit;
import java.util.Calendar;

public class InstantDemo2 {

	public static void main(String[] args) {

		//System.out.println("Instant.now() = " + Instant.now());

		Calendar targetDate = Calendar.getInstance();
		System.out.println("2018, 12 - 1, 20, 18, 30, 0");
		targetDate.set(2018, 12 - 1, 20, 18, 30, 0);
		System.out.println("targetDate set to " +
            targetDate.get(Calendar.YEAR) + "-" +
            (targetDate.get(Calendar.MONTH) + 1) + "-" +
            targetDate.get(Calendar.DAY_OF_MONTH) + " " +
            targetDate.get(Calendar.HOUR_OF_DAY) + ":" +
            targetDate.get(Calendar.MINUTE) + ":" +
            targetDate.get(Calendar.SECOND));
	}

}
