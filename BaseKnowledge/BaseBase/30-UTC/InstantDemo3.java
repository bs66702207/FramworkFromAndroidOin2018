import java.time.Instant;
import java.time.temporal.ChronoUnit;
import java.util.Calendar;
import java.util.Date;

public class InstantDemo3 {

	public static void main(String[] args) {

		System.out.println("Instant.now() = " + Instant.now());
		Instant expiration = Instant.now().plus(86400000, ChronoUnit.MILLIS);//+ one day

		Calendar targetDate = Calendar.getInstance();
		targetDate.setTime(Date.from(expiration));
		System.out.println("targetDate set to " +
			targetDate.get(Calendar.YEAR) + "-" +
			(targetDate.get(Calendar.MONTH) + 1) + "-" +
			targetDate.get(Calendar.DAY_OF_MONTH) + " " +
			targetDate.get(Calendar.HOUR_OF_DAY) + ":" +
			targetDate.get(Calendar.MINUTE) + ":" +
			targetDate.get(Calendar.SECOND));

	}

}
