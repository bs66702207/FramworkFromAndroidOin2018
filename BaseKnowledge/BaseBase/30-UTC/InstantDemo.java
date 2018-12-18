import java.time.Instant;
import java.time.temporal.ChronoUnit;
import java.util.Calendar;

public class InstantDemo {

	public static void main(String[] args) {

		System.out.println("Instant.now() = " + Instant.now());

		Calendar calendar = Calendar.getInstance();
		calendar.set(2018, 12 - 1, 20, 18, 30, 0);
		System.out.println("Instant.rtc() = " + calendar.toInstant());

		long save = Instant.now().until(calendar.toInstant(), ChronoUnit.SECONDS);

		System.out.println("Instant.left() = " + Instant.now().until(calendar.toInstant(), ChronoUnit.SECONDS));

		System.out.println("until all seconds = " + save/60/60/24);
	}

}
