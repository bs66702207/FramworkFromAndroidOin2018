StringBuilder
JDK1.5 版本之后出现了StringBuilder.
StringBuffer是线程同步，安全的，效率低。
StringBuilder是线程不同步，不安全的，效率高。
以后开发，建议使用StringBuilder，至于多线程，你可以自己加锁，或者使用StringBuffer。
