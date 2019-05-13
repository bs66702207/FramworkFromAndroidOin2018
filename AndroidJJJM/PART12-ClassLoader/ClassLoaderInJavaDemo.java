public class ClassLoaderInJavaDemo {

    public static void sop(Object arg) {
        System.out.println(arg);
    }

    public static void main(String[] args) {
       sop(System.getProperty("sun.boot.class.path"));//Bootstrap ClassLoader
       sop(System.getProperty("java.ext.dirs"));//Extensions ClassLoader
       sop(System.getProperty("java.class.path"));//Application ClassLoader

       sop("How many ClassLoader needs to run a java elf?");
       ClassLoader loader = ClassLoaderInJavaDemo.class.getClassLoader();
       while(loader != null) {
           sop(loader);
           loader = loader.getParent();
       }
    }
}
